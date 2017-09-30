#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "sys_database.h"
#include "task_com_base.h"
#include "resource_manager.h"

CTaskComBase::CTaskComBase()
{
    m_iLastRxPack   = 0;
    mfileDeviceCom  = -1;

    isLogStart = false;
    m_iLogIdx = 0;
}

int CTaskComBase::OpenDev(const char *Dev,int flag)
{
    int mfd;
    struct termios options;

    mfd = ::open( Dev,flag,0);         //| O_NOCTTY | O_NDELAY

    if (mfd<0)
        return -1;

    memset(&options, 0, sizeof(struct termios));
    options.c_iflag = IGNPAR;
    options.c_cflag = B19200 | HUPCL | CS8 | CREAD | CLOCAL;

    options.c_cc[VMIN] = 0;
    tcflush(mfd,TCIOFLUSH);
    tcsetattr(mfd,TCSANOW,&options);

    return mfd;
    
}

void CTaskComBase::SerialCommRx()
{
    unsigned char ch[8];

    if(mfileDeviceCom < 0)
        return;

    while ( read(mfileDeviceCom,ch,1) == 1)
    {
        g_IComm.cRxBuf[ g_IComm.iRxTail++ ] = ch[0];

        if(g_IComm.iRxTail == MAX_RXBUF)
        {
            g_IComm.iRxTail = 0;
        }
    }
}

void CTaskComBase::SerialCommTx()
{
    ssize_t mSize;

    if(mfileDeviceCom < 0)
        return;

    int mTtCtr = 0;
    char mTtStr[MAX_TXBUF];
    memset(mTtStr,0,MAX_TXBUF);

    while (g_IComm.iTxHead != g_IComm.iTxTail)
    {
        mTtStr[mTtCtr++] = g_IComm.cTxBuf[g_IComm.iTxHead];

        mSize = write(mfileDeviceCom,&g_IComm.cTxBuf[g_IComm.iTxHead++],1);

        if(mSize != 1)
        {
         //   qDebug() << "CSystemGeneral::OnButtonUpdate " << "system error!";
         //   return;
        }

        if (g_IComm.iTxHead == MAX_TXBUF)
        {
            g_IComm.iTxHead = 0;
        }
    }

    QFile mtttt;

    mtttt.setFileName("/opt/works/test.dat");
    mtttt.open(QIODevice::WriteOnly);
    mtttt.write(mTtStr,mTtCtr);
    mtttt.flush();
    mtttt.close();
}

bool CTaskComBase::Init_TaskComm(const char * dev,int flag)
{ 

    g_IComm.iTxHead     = 0;
    g_IComm.iTxTail     = 0;
    g_IComm.iRxHead     = 0;
    g_IComm.iRxTail     = 0;

    m_taskComm.hTask    = 0;
    m_taskComm.hTail    = 0;
    m_taskComm.nRetry   = 0;
    m_taskComm.TxState  = COMM_TX_IDLE;

    m_taskComm.wRxCount = 0;
    m_taskComm.wTxPack  = 0;
    m_taskComm.wRxPack  = 0;

    m_taskComm.wPanelKey = _KEY_NULL;
    m_taskComm.nOutputOP = OUTOP_NULL;

    if(mfileDeviceCom > 0)
    {
        ::close(mfileDeviceCom);
        mfileDeviceCom = -1;
    }

    mfileDeviceCom = OpenDev(dev,flag);

    if (mfileDeviceCom < 0)
    {
        fprintf(stderr, "Open Device Failed: %s\n", dev);
        //printf("Open Device Failed:%s",dev);
        return false;
    }
    return true;
} 
bool CTaskComBase::devValid()
{
    if(mfileDeviceCom < 0)
        return false;
    else
        return true;
}
void CTaskComBase::WriteComm(unsigned short * pData, unsigned char nCount)
{ 
    unsigned short i,index;
    unsigned char * pcData=(unsigned char*)pData;

    if(mfileDeviceCom < 0)
        return;

    index = g_IComm.iTxTail;

    for(i = 0 ; i < nCount ; i++)
    {
        g_IComm.cTxBuf[index++] = *(pcData+1);
        g_IComm.cTxBuf[index++] = *pcData;

        pcData++; pcData++;

        if (index == MAX_TXBUF)
            index=0;
    }

    g_IComm.iTxTail = index;

} 

unsigned char CTaskComBase::ReadComm(unsigned short * pData, unsigned char nCount)
{ 
    unsigned short iHead,iTail;
    unsigned short* pwData;
    unsigned char nRead=0;
    unsigned char cHi,cLo;
    iHead=g_IComm.iRxHead;
    iTail=g_IComm.iRxTail;

    if(mfileDeviceCom < 0)
        return 0;

    bool bExit = false;

    while(!bExit)
    {
        pwData = pData;
        if ((iTail-iHead) % 2)
        {
            if (iTail==0)
                iTail = MAX_RXBUF-1;
            else
                iTail--;
        }

        while (iHead != iTail && nRead < nCount)
        {
            cHi=g_IComm.cRxBuf[iHead++];

            if (iHead==MAX_RXBUF)
                iHead=0;

            cLo=g_IComm.cRxBuf[iHead++];

            if (iHead==MAX_RXBUF)
                iHead=0;

            *pwData++=((unsigned short)cHi<<8) | cLo;
            nRead++;
        }

        if ((nRead > 0) && ( m_taskComm.wRxBuf[0] != 0xEB90))
        {
            if (iHead == 0)
                iHead = MAX_RXBUF-1;
            else
                iHead--;

            nRead=0;
        }else
            bExit = true;

    }

    g_IComm.iRxHead = iHead;

    return nRead;
} 


void CTaskComBase::Init_SendComm()
{ 
    m_taskComm.hTask    = 0;
    m_taskComm.hTail    = 0;
    m_taskComm.nRetry   = 0;
    m_taskComm.TxState  = COMM_TX_IDLE;
    
    m_taskComm.wPanelKey=_KEY_NULL;
    
} 

void CTaskComBase::CreateTask(unsigned short wType,unsigned short* buf,unsigned short wcount)
{

    //normal mode
    unsigned char htask;
    htask = m_taskComm.hTail;

    m_taskComm.hTail++;
    if (m_taskComm.hTail == MAX_TX_COMM)
    {
        m_taskComm.hTail = 0;
    }

    m_taskComm.Task[htask].wType  = wType;
    m_taskComm.Task[htask].wCount = wcount;

    if(buf)
    {
        for(int i = 0 ; i < wcount ; i++)
        {
            m_taskComm.Task[htask].wBuf[i] = buf[i];
        }
    }

    if (m_taskComm.TxState == COMM_TX_IDLE)
        m_taskComm.TxState = COMM_TX_WAIT;

}

void CTaskComBase::Destroy_TaskComm()
{ 
    m_taskComm.hTask++;
    if (m_taskComm.hTask==MAX_TX_COMM)
        m_taskComm.hTask=0;
    
    m_taskComm.nRetry=0;
    
    if (m_taskComm.hTask == m_taskComm.hTail)
        m_taskComm.TxState = COMM_TX_IDLE;
    else
        m_taskComm.TxState = COMM_TX_WAIT;
    
} 

void CTaskComBase::ProcessRxData()
{
    //null,20160226,leave the process task to child class
}

void CTaskComBase::SendTaskComm()
{ 
    //null,20160226,leave the process task to child class
} 

void CTaskComBase::ReceiveTaskComm()
{ 
    //null,20160226,leave the task to child class
} 
bool CTaskComBase::isPacketChanged()
{
    if(m_taskComm.wRxPack == m_iLastRxPack)
        return false;
    else
        m_iLastRxPack = m_taskComm.wRxPack;

    return true;
}

void CTaskComBase::DataLogStart()
{
    isLogStart = true;

    if(mfileLog.isOpen())
        mfileLog.close();

    QString mFileName;
    mFileName.sprintf( "sdcard/home/fa/logData%03d.dat",m_iLogIdx);

    mfileLog.setFileName(mFileName);

    if(mfileLog.exists())
        mfileLog.remove();

    mfileLog.open(QIODevice::WriteOnly);

    m_iLogIdx++;

}

void CTaskComBase::DataLogStop()
{
    isLogStart = false;

}

void CTaskComBase::DataLog()
{

    if(!mfileLog.isOpen())
        return;

    char mTempBuf[64];
    for(int mIdx = 0 ; mIdx < 20 ; mIdx++)
    {
        mTempBuf[2 * mIdx] = g_systemDb->g_dbMachine.CurrentData[mIdx] & 0x00ff;
        mTempBuf[2 * mIdx + 1] = g_systemDb->g_dbMachine.CurrentData[mIdx] >> 8;
    }

    mfileLog.write(mTempBuf,40);
    mfileLog.flush();

}
void CTaskComBase::On_TaskComm()
{ 

    if(mfileDeviceCom <= 0)
        return;

    SerialCommRx();
    ReceiveTaskComm();          //读取串口消息，校验

    SendTaskComm();
    SerialCommTx();
} 
