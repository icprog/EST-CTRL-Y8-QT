#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "./system/sys_database.h"
#include "task_com_key.h"
#include "resource_manager.h"

CTaskComKey::CTaskComKey()
{
    m_iLastRxPack   = 0;
    mfileDeviceCom  = -1;

    isLogStart = false;
    m_iLogIdx = 0;

    Init_TaskComm("/dev/ttySAC2",O_RDWR | O_NDELAY);

}

void CTaskComKey::ProcessRxData()
{

    unsigned short  wType;
    unsigned char   htask;

    m_taskComm.wRxPack++;

    wType = m_taskComm.wRxBuf[1];

    htask = m_taskComm.hTask;

    if (m_taskComm.wRxBuf[1] == m_taskComm.Task[htask].wType)
        m_taskComm.TxState = COMM_TX_SUCCESS;

    switch(wType)
    {
    case COMM_RX_TOUCH_PRESS:
        //qInfo("COMM_RX_TOUCH_PRESS");
        break;
    case COMM_RX_TOUCH_RELEASE:
        //qInfo("COMM_RX_TOUCH_RELEASE");
        break;
    case COMM_RX_KEY:

        //qInfo("ProcessCommRxData2 key code = %d",g_TaskComm2.wRxBuf[2]);
        RsMgr->g_filmBase->filmImport(m_taskComm.wRxBuf[2]);
        //qDebug() << "filmImport" << m_taskComm.wRxBuf[2];
        break;
    case COMM_RX_KEYCONNECT:
        //qInfo("COMM_RX_KEYCONNECT");  //message will return after led control
        break;
    case COMM_RX_RESPONSE:
        //qInfo("COMM_RX_RESPONSE");
        break;
    default:
        //qInfo("type = %d | buf[2] = %d buf[3] = %d",m_taskComm.wRxBuf[1],m_taskComm.wRxBuf[2],m_taskComm.wRxBuf[3]);
        break;
    }

}

void CTaskComKey::SendTaskComm()
{ 

    unsigned short  wBuf[8];
    unsigned short  wCount,i;
    unsigned char htask;
    
    if (m_taskComm.TxState != COMM_TX_WAIT)
        return;
    
    m_taskComm.wTxPack++;
    
    htask   = m_taskComm.hTask;
    wBuf[0] = 0xEB90;
    wBuf[1] = m_taskComm.Task[htask].wType;

    wCount  = m_taskComm.Task[htask].wCount;

    for(int mIdx = 0 ; mIdx < wCount - 3 ; mIdx++)
        wBuf[mIdx + 2] = m_taskComm.Task[htask].wBuf[mIdx];

    wBuf[wCount - 1] = wBuf[1];

    for( i = 1 ; i < wCount - 2; i++)
        wBuf[wCount - 1] ^= wBuf[ i + 1];

    //    if(m_taskComm.Task[htask].wType == COMM_TX_KEY)
    //        for(int mIdx = 0 ; mIdx < wCount ; mIdx++)
    //            fprintf(stderr,"COMM_TX_KEY-----------wBuf[%d]=%d\n",mIdx,wBuf[mIdx]);
    //    else
    //        for(int mIdx = 0 ; mIdx < wCount ; mIdx++)
    //            fprintf(stderr,"----------------------wBuf[%d]=%d\n",mIdx,wBuf[mIdx]);

    WriteComm(wBuf,wCount);

    Destroy_TaskComm();

    //m_taskComm.TxState = COMM_TX_WAIT;
    
} 

void CTaskComKey::ReceiveTaskComm()
{ 

    //  3、 按键发送  STC→ARM
    //      3.1、数据格式
    //          EB 90 F0 04 XX XX YY YY
    //          EB 90——包头；
    //          F0 04——类型码，表示当前发送的是按键功能码，04表示数据长度，表示4个16位二进制数据；
    //          XX XX——数据，表示程序功能码，其中锁键时，数据XX XX最高位置1；
    //          YY YY——异或校验码，F0 04与XX XX按位异或后得到YY YY。

    unsigned short * pwData;
    unsigned short wCount,nNum,i,wCode;
    while (true)
    {
        if (m_taskComm.wRxCount < 2)
        {
            nNum = 1;
        }else
        {

            nNum = (m_taskComm.wRxBuf[1] & 0x00ff)- m_taskComm.wRxCount;

            if (nNum == 0)
            {
                //计算校验码
                pwData = m_taskComm.wRxBuf + 1;

                wCode = *pwData++;

                for( i = 1; i < m_taskComm.wRxCount - 2; i++ )
                    wCode ^= *pwData++;

                if (wCode == *pwData)
                    ProcessRxData();

                nNum=1;
                m_taskComm.wRxCount=0;
            }
        }
        
        pwData = m_taskComm.wRxBuf + m_taskComm.wRxCount;

        wCount = ReadComm( pwData , nNum);

        if (wCount == 0)
            return;

        m_taskComm.wRxCount += wCount;
    }
} 

