#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "./system/sys_database.h"
#include "task_com_ctrl.h"
#include "resource_manager.h"

//try times
#define COMM_TX_TRY_TIMES   5

CTaskComCtrl::CTaskComCtrl()
{
    m_iLastRxPack   = 0;
    mfileDeviceCom  = -1;

    isLogStart = false;
    m_iLogIdx = 0;

    //char * cBuf = g_mainCfg->value("comCtrl","ttyS1").toByteArray().data();
    char * cBuf = g_mainCfg->value("comCtrl","/dev/ttySAC1").toByteArray().data();

    Init_TaskComm(cBuf,O_RDWR | O_NONBLOCK| O_NOCTTY);

}

void CTaskComCtrl::CreateTask(unsigned short wType,unsigned short* buf,unsigned short wcount)
{
    if(g_systemDb->g_bMotionSimulate)
    {
        //Simulate mode,send key to simulator
        if(wType == CMD_FUNC_WKEY)
            emit ComKeyCommand(buf[1]);
    }

    //TARGET_TCP_CLIENT mode,publish message through network
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(wType == CMD_FUNC_WKEY || wType == CMD_FUNC_SMART)
        {
            if(!g_netBase)
                return;

            unsigned short * keyBuf = g_netBase->getBufWrite();

            if(keyBuf == NULL)
                return;

            keyBuf[0] = wType;
            keyBuf[1] = buf[1];
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
            return;
        }
    }

    CTaskComBase::CreateTask(wType,buf,wcount);
}


void CTaskComCtrl::ProcessRxData()
{
    unsigned short  wType;
    unsigned char   htask;

    unsigned short * pBuf;

    m_taskComm.wRxPack++;

    wType = m_taskComm.wRxBuf[1];

    htask = m_taskComm.hTask;

    if (m_taskComm.wRxBuf[1] == m_taskComm.Task[htask].wType)
        m_taskComm.TxState = COMM_TX_SUCCESS;

    switch(wType)
    {
    case (CMD_FUNC_WKEY):
        break;
    case (CMD_FUNC_POSI):
        break;
    case (CMD_FUNC_SPEED):
        break;
    case CMD_FUNC_MOTO:
        for(int i=0;i<8;i++)
        {
            g_systemDb->g_dbMachine.SlowData[i]= (short)m_taskComm.wRxBuf[3+i];
        }

        if(!g_netBase)
            break;

        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
        {
            pBuf = g_netBase->getUdpBufferWrite();
            pBuf[0] = CMD_FUNC_MOTO;
            for(int i = 0 ; i < 8 ; i++ )
            {
                pBuf[i + 1]   = (short)m_taskComm.wRxBuf[3+i];
            }

            g_netBase->BroadcastMsg();
        }
        break;
    case CMD_FUNC_COMMD:
        g_systemDb->g_bDataSaved = true;
        break;
    case CMD_FUNC_STATE:
        for(int i = 0 ; i < 8 ; i++ )
        {
            g_systemDb->g_dbMachine.StateData[i]= (short)m_taskComm.wRxBuf[3+i];
        }

        if(!g_netBase)
            break;

        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
        {
            pBuf = g_netBase->getUdpBufferWrite();
            pBuf[0] = CMD_FUNC_STATE;
            for(int i = 0 ; i < 8 ; i++ )
            {
                pBuf[i + 1]   = (short)m_taskComm.wRxBuf[3+i];
            }

            g_netBase->BroadcastMsg();
        }

        break;
    case CMD_FUNC_DEBUG:
        for(int i = 0 ; i < 20 ; i++)
        {
            g_systemDb->g_dbMachine.CurrentData[i]= (short)m_taskComm.wRxBuf[3+i];
        }

        emit ChxValData((unsigned short *)(g_systemDb->g_dbMachine.CurrentData));

        if(isLogStart)
            DataLog();

        if(!g_netBase)
            break;

        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
        {
            pBuf = g_netBase->getUdpBufferWrite();
            pBuf[0] = CMD_FUNC_DEBUG;
            for(int i = 0 ; i < 20 ; i++ )
            {
                pBuf[i + 1]   = (short)m_taskComm.wRxBuf[3+i];
            }

            g_netBase->BroadcastMsg();
        }

        break;
    case CMD_FUNC_PARAM:
        for(int i = 0 ; i < SYS_POSI_DATA_LEN ; i++)
        {
            g_systemDb->g_dbMachine.PosiData[i]= (short)m_taskComm.wRxBuf[3+i];
        }

        g_systemDb->g_bPosDataValid = true;

        if(!g_netBase)
            break;

        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
        {
            pBuf = g_netBase->getUdpBufferWrite();
            pBuf[0] = CMD_FUNC_PARAM;
            for(int i = 0 ; i < SYS_POSI_DATA_LEN ; i++ )
            {
                pBuf[i + 1]   = (short)m_taskComm.wRxBuf[3+i];
            }

            g_netBase->BroadcastMsg();
        }
        break;
    case COMM_RX_RESPONSE:
        htask = m_taskComm.hTask;
        if (m_taskComm.Task[htask].wType == COMM_TX_MAINPRG)
        {
            if (m_taskComm.wRxBuf[2] == m_taskComm.Task[htask].wAddr)
            {
                g_systemDb->g_nPrgPack  = m_taskComm.Task[htask].wAddr;
                m_taskComm.TxState      = COMM_TX_SUCCESS;
            }
        }else if (m_taskComm.wRxBuf[4] == m_taskComm.Task[htask].wType)
        {
            m_taskComm.TxState = COMM_TX_SUCCESS;
        }
        break;
    case COMM_RX_NOAPP:
        g_systemDb->g_bNoApp = true;

        if((g_systemDb->packno == 1) && (m_taskComm.TxState  == COMM_TX_IDLE))
        {

            Init_TaskComm("/dev/ttySAC1",O_RDWR | O_NDELAY| O_NOCTTY);

            CreateTask(COMM_TX_MAINPRG,0, g_systemDb->packLen);
        }
        break;
    case CMD_FUNC_VER:
        firmWareVersion( &(m_taskComm.wRxBuf[3]) , g_dbsys.firmVersion);
        /*
        for(int i = 0 ; i < 4 ; i++)
        {
            pBuf = (unsigned short * )g_dbsys.firmVersion;
            pBuf[i]= (short)m_taskComm.wRxBuf[3+i];
        }*/
        break;
    case CMD_FUNC_LIGHT_CURTAIN:
        for(int mIdx = 0 ; mIdx < SYS_LIGHT_CURTAIN_PAR_LEN ; mIdx++)
        {
            g_systemDb->g_iArrLightCurtain[mIdx]= (short)m_taskComm.wRxBuf[3+mIdx];
        }
        g_systemDb->g_ctrLightCurtainMsg += 1;

        if( g_systemDb->g_iArrLightCurtain[5] == 1)
        {
            if( (g_systemDb->g_ctrLightCurtainMsg % 3 ) == 0)
                RsMgr->g_filmBase->SetKeySound();
        }
        break;
    case CMD_NDT_RUN:   //return from motor run
        htask = m_taskComm.hTask;
        if (m_taskComm.Task[htask].wType == CMD_NDT_RUN)
        {
            m_taskComm.TxState  = COMM_TX_SUCCESS;
        }
        break;
    case CMD_NDT_STATE:

        for(int mIdx = 0 ; mIdx < SYS_NDT_STATE_PAR_LEN ; mIdx++)
        {
            g_systemDb->g_iArrNdtState[mIdx]= (short)m_taskComm.wRxBuf[3+mIdx];
        }
        g_systemDb->g_ctrNdtStateMsg += 1;

        if(!g_netBase)
            break;

        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
        {
            pBuf = g_netBase->getUdpBufferWrite();
            pBuf[0] = CMD_NDT_STATE;
            for(int mIdx = 0 ; mIdx < SYS_NDT_STATE_PAR_LEN ; mIdx++ )
            {
                pBuf[1 + mIdx ]   = (short)(m_taskComm.wRxBuf[ 3 + mIdx]);
            }

            g_netBase->BroadcastMsg();
        }

        break;
    default:
        break;
    }
}
void CTaskComCtrl::firmWareVersion(unsigned short * pSrc, char *pDst)
{
    if(pSrc == NULL || pDst == NULL)
        return;

    pDst[0] = (( pSrc[0] & 0x00f0) >> 4 ) + 0x30;
    pDst[1] = (  pSrc[0] & 0x000f)  + 0x30;
    pDst[2] = (( pSrc[0] & 0xf000) >> 12 ) + 0x30;
    pDst[3] = (( pSrc[0] & 0x0f00) >> 8 ) + 0x30;

    pDst[4] = '.';

    pDst[5] = (( pSrc[1] & 0x00f0) >> 4 ) + 0x30;
    pDst[6] = (  pSrc[1] & 0x000f)  + 0x30;
    pDst[7] = (( pSrc[1] & 0xf000) >> 12 ) + 0x30;
    pDst[8] = (( pSrc[1] & 0x0f00) >> 8 ) + 0x30;

    pDst[9] = 0;

}
void CTaskComCtrl::SendTaskComm()
{ 
    unsigned short  wDataTemp[0x80];
    unsigned short  wBuf[8];
    unsigned short  *pData;
    unsigned short  wCount,i;
    unsigned char htask;

    if ((m_taskComm.TxState == COMM_TX_SEND) && ((unsigned char)(g_nCounter - m_taskComm.nCounter) > COM_RETRY_INTERVAL))
    {
        m_taskComm.TxState = COMM_TX_WAIT;
        m_taskComm.nRetry++;

        if  (m_taskComm.nRetry == COMM_TX_TRY_TIMES)
            Init_SendComm();
    }
    
    if (m_taskComm.TxState == COMM_TX_SUCCESS )
    {
        Destroy_TaskComm();
    }
    
    if (m_taskComm.TxState != COMM_TX_WAIT)
        return;
    
    m_taskComm.wTxPack++;
    
    htask   = m_taskComm.hTask;
    wBuf[0] = 0xEB90;
    wBuf[1] = m_taskComm.Task[htask].wType;
    wBuf[2] = m_taskComm.Task[htask].wCount+4;
    
    if (m_taskComm.Task[htask].wType == COMM_TX_MAINPRG)
    {
        wBuf[2] = g_systemDb->packno;
        wBuf[3] = g_systemDb->packLen + 5;
        WriteComm(wBuf,4);

        m_taskComm.Task[htask].wAddr = g_systemDb->packno;
        pData = g_systemDb->g_wPrgBuf;
    }else
    {
        WriteComm(wBuf,3);
        pData = m_taskComm.Task[htask].wBuf;
    }

    memcpy(&wDataTemp,pData,m_taskComm.Task[htask].wCount*2);
    
    WriteComm(pData,m_taskComm.Task[htask].wCount);
    
    wCount  = m_taskComm.Task[htask].wCount;

    if (m_taskComm.Task[htask].wType == COMM_TX_MAINPRG)
        wBuf[0] = wBuf[1]^wBuf[2]^wBuf[3];
    else
        wBuf[0] = wBuf[1]^wBuf[2];

    for( i = 0 ; i < wCount ; i++)
        wBuf[0] ^= *(pData+i);
    
    WriteComm(wBuf,1);

    if (m_taskComm.Task[htask].wType == CMD_KEEP_ALIVE_HEADER)
        m_taskComm.TxState = COMM_TX_SUCCESS;
    else
        m_taskComm.TxState = COMM_TX_SEND;
    
    m_taskComm.nCounter = g_nCounter;
    
} 

void CTaskComCtrl::ReceiveTaskComm()
{ 
    unsigned short * pwData;
    unsigned short wCount,nNum,i,wCode;
    while (true)
    {
        if (m_taskComm.wRxCount < 4)
        {
            nNum = 1;
        }else
        {
            if(( m_taskComm.wRxBuf[1] == COMM_RX_NOAPP) || (m_taskComm.wRxBuf[1] == COMM_RX_RESPONSE))
                m_iPackLenIdx = 3;
            else
                m_iPackLenIdx = 2;

            if ((m_taskComm.wRxBuf[m_iPackLenIdx] < 4) || (m_taskComm.wRxBuf[m_iPackLenIdx] > MAX_RX_BUF))
            {
                m_taskComm.wRxCount=0;
                return;
            }

            nNum = m_taskComm.wRxBuf[m_iPackLenIdx] - m_taskComm.wRxCount;

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

