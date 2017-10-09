#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "task_can.h"
#include "resource_manager.h"

#define CAN_CPU_KIND ( 1 )
#define CAN_ERULER_KIND ( 2 )
#define CAN_HSPDIO_KIND ( 3 )
#define CAN_SERVO_KIND ( 4 )
#define CAN_DA_KIND ( 5 )
#define CAN_CODE_KIND ( 6 )
#define CAN_LSPDIO_KIND ( 7 )
#define CAN_RELAY_KIND ( 8 )
#define CAN_TEMP_KIND ( 9 )
#define CAN_PANEL_KIND ( 10 )
#define CAN_SIMPLE_KIND ( 15 )

#define CAN_NMT_RAD_CODE 0x0 
#define CAN_NMT_SYNC_CODE 0x2 
#define CAN_TIME_STAMP_CODE 0x5 
#define CAN_EMERGENCY_CODE 0x2 
#define CAN_PDO_TX_CODE 0x6 
#define CAN_PDO_RE_CODE 0x7 
#define CAN_SDO_TX_CODE 0x8 
#define CAN_SDO_RE_CODE 0x9 
#define CAN_NMT_CTRL_CODE 0x0E 

#define SERVO_ID 0x1
#define PANEL_ID 0x1
#define CPU_ID 0x1

CTaskCan::CTaskCan()
{
    iRec = 0;
    iBuf = 0;
    mfileDeviceCan = -1;
}

void CTaskCan::SaveRealCan()
{
    int i,ii;
    FILE *stream;

    stream = fopen( "sdcard/home/fa/rr.dat", "w" );

    if( stream == NULL )
        printf( "The file r.dat was not opened\n" );
    else
    {
        i=0;
        while(i<iRec){
            ii=myBuf[i][0]; fprintf( stream, "%d, ",ii);
            ii=myBuf[i][1]; fprintf( stream, "%d, ",ii);
            ii=myBuf[i][2]; fprintf( stream, "%d, ",ii);
            ii=myBuf[i][3]; fprintf( stream, "%d, ",ii);
            ii=myBuf[i][4]; fprintf( stream, "%d,\n ",ii);
            i++;
        }
        fclose( stream );

    }

}
bool CTaskCan::Init_TaskCan()
{ 
    mfileDeviceCan = ::open("/dev/wcan", O_RDWR);

    if (mfileDeviceCan<0)
        return false;

    hTask=0;
    hTail=0;
    nRetry=0;
    TxState=CAN_TX_IDLE;

    return false;
} 

void CTaskCan::End_TaskCan()
{ if (mfileDeviceCan<0)
        return;

    close(mfileDeviceCan);
}
void CTaskCan::Init_SendCan()
{ 
    hTask=0;
    hTail=0;
    nRetry=0;
    TxState=CAN_TX_IDLE;

} 

void CTaskCan::Create_TaskCan(unsigned char cType,unsigned char nId,unsigned short wAddr,unsigned int dwData)
{ 
    unsigned char htask;

    htask=hTail;

    hTail++;
    if (hTail==MAX_TX_CAN) hTail=0;

    Task[htask].cType =cType;
    Task[htask].nId =nId;
    Task[htask].wAddr =wAddr;
    Task[htask].dwData =dwData;

    if (TxState==CAN_TX_IDLE)
        TxState=CAN_TX_WAIT;

} 

void CTaskCan::Destroy_TaskCan()
{ 
    hTask++;
    if (hTask==MAX_TX_CAN) hTask=0;

    nRetry=0;

    if (hTask==hTail)
        TxState=CAN_TX_IDLE;
    else TxState=CAN_TX_WAIT;

} 

void CTaskCan::SendTaskCan()
{ 
    //unsigned char cCount,cBytes,i,j,k;
    //unsigned int dwData;
    unsigned char i,j,k;
    unsigned char htask;
    unsigned short wCode;
    ssize_t mLen ;
    //cCount = 0; //jsy20140814
    //cBytes = 0; //jsy20140814
    //dwData = 0; //jsy20140814

    if ((TxState==CAN_TX_SEND) && ((unsigned char)(g_nCounter - nCounter) >50))
    {
        TxState=CAN_TX_WAIT;
        nRetry++;
        if (nRetry==3) Init_SendCan();

    }

    if (TxState==CAN_TX_SUCCESS )
    {
        Destroy_TaskCan();
    }


    if (TxState!=CAN_TX_WAIT) return;

    htask=hTask;
    cTxBuf[0]=8;
    if (Task[htask].cType==CAN_TX_IDRESPONSE){
        cTxBuf[1]=(CAN_NMT_CTRL_CODE << 4) | (CAN_SERVO_KIND);
        cTxBuf[2]=Task[htask].nId << 5;
        cTxBuf[3]=(CAN_PANEL_KIND << 3) | (PANEL_ID & 0x07);
        cTxBuf[4]=0x02;

        mLen = write(mfileDeviceCan,cTxBuf,11);
        if(mLen < 11 )
            qDebug() << "CTaskCan::SendTaskCan" << "write(mfileDeviceCan,cTxBuf,11)" << "fail.";

        Destroy_TaskCan();
    }
    else if (Task[htask].cType==CAN_TX_MAINTEST){
        cTxBuf[1]=(CAN_PDO_TX_CODE << 4) | (CAN_CPU_KIND);
        cTxBuf[2]=(CPU_ID << 5);
        cTxBuf[3]=((CAN_PANEL_KIND << 3) | (PANEL_ID & 0x07));
        cTxBuf[4]=Task[htask].dwData;

        mLen =  write(mfileDeviceCan,cTxBuf,11);
        if(mLen < 11 )
            qDebug() << "CTaskCan::SendTaskCan" << "write(mfileDeviceCan,cTxBuf,11)" << "fail.";

        Destroy_TaskCan();
    }
    else if (Task[htask].cType == CAN_TX_MAINPRG)
    {
        cTxBuf[1]=(CAN_SDO_TX_CODE<< 4) | (CAN_CPU_KIND);
        cTxBuf[2]=(CPU_ID << 5);
        cTxBuf[3]=(CAN_PANEL_KIND << 3) | (PANEL_ID & 0x07);
        cTxBuf[4]=0;
        cTxBuf[5]=0xEB;
        cTxBuf[6]=0x90;
        cTxBuf[7]=0x11;
        cTxBuf[8]=0x90;
        cTxBuf[9]=Task[htask].wAddr>>8;
        cTxBuf[10]=Task[htask].wAddr;

        mLen =  write(mfileDeviceCan,cTxBuf,11);
        if(mLen < 11 )
            qDebug() << "CTaskCan::SendTaskCan" << "write(mfileDeviceCan,cTxBuf,11)" << "fail.";

        cTxBuf[5]=(Task[htask].dwData+5)>>8;
        cTxBuf[6]=Task[htask].dwData+5;
        k=7;
        j=0;
        while(j<Task[htask].dwData){
            cTxBuf[k++]=g_systemDb->g_wPrgBuf[j]>>8;
            cTxBuf[k++]=g_systemDb->g_wPrgBuf[j];
            j++;
            if (k>10) {
                mLen = write(mfileDeviceCan,cTxBuf,11);
                k=5;
            }
        }

        wCode=0x1190^Task[htask].wAddr^(Task[htask].dwData+5);
        for(i=0;i<Task[htask].dwData;i++) wCode^=g_systemDb->g_wPrgBuf[i];

        cTxBuf[k++]=wCode>>8;
        cTxBuf[k]=wCode;

        mLen =  write(mfileDeviceCan,cTxBuf,11);
        if(mLen < 11 )
            qDebug() << "CTaskCan::SendTaskCan" << "write(mfileDeviceCan,cTxBuf,11)" << "fail.";

        TxState=CAN_TX_SEND;
        nCounter = g_nCounter;
        //g_wTemp2++;

    }
    else{
        cTxBuf[1]=(CAN_PDO_TX_CODE << 4) | (CAN_SERVO_KIND);
        cTxBuf[2]=Task[htask].nId << 5;
        cTxBuf[3]=(CAN_PANEL_KIND << 3) | (PANEL_ID & 0x07);
        cTxBuf[4]=0;
        cTxBuf[5]=0;
        cTxBuf[6]=Task[htask].cType;
        cTxBuf[7]=Task[htask].wAddr>>8;
        cTxBuf[8]=Task[htask].wAddr;
        cTxBuf[9]=Task[htask].dwData>>8;
        cTxBuf[10]=Task[htask].dwData;

        mLen =  write(mfileDeviceCan,cTxBuf,11);
        if(mLen < 11 )
            qDebug() << "CTaskCan::SendTaskCan" << "write(mfileDeviceCan,cTxBuf,11)" << "fail.";

        if (Task[htask].wAddr!=0x8001)
        {
            TxState=CAN_TX_SEND;
            nCounter = g_nCounter;
        }
        else Destroy_TaskCan();

    }
}
void CTaskCan::ReceiveTaskCan()
{ 
    //unsigned short wData,wAddr,i,nServoId,wCode;
    //unsigned char cType,cBytes,cCanType;

    unsigned short i,nServoId,wCode;
    unsigned char cType,cCanType;
    unsigned char htask;

    // wData = 0; //jsy20140814
    //wAddr = 0; //jsy20140814
    //cBytes = 0; //jsy20140814
    while (1){
        if (!read(mfileDeviceCan,cRxBuf,12)) return;

        htask=hTask;

        cCanType=cRxBuf[1]>>4;
        if (cCanType == CAN_SDO_RE_CODE){

            for(i=0;i<3;i++){
                wBuf[iBuf++]=((unsigned short)cRxBuf[5+i*2]<<8) | (unsigned short)cRxBuf[6+i*2];
            }
            if (wBuf[0] != 0xEB90)
                iBuf=0;

            if (iBuf>=6)
            {
                iBuf=0;
                wCode=0;

                for(i=1;i<6;i++)
                    wCode ^= wBuf[i];

                if (!wCode)
                {
                    if (wBuf[2] == Task[htask].wAddr)
                    {
                        g_systemDb->g_nPrgPack = Task[htask].wAddr;
                        if (TxState == CAN_TX_SEND)
                            TxState = CAN_TX_SUCCESS;
                    }
                }
            }
            return;
        }

        cCanType = cRxBuf[3];

        if (cCanType == ((CAN_CPU_KIND << 3) | (CPU_ID & 0x07)))
        {
            return;
        }

        nServoId = cRxBuf[3] & 0x07;
        cCanType = cRxBuf[1] >> 4;

        if (cCanType == CAN_NMT_CTRL_CODE)
        {
            Create_TaskCan(CAN_TX_IDRESPONSE,nServoId,0,0x02);
            return;
        }

        cType = cRxBuf[6];

        switch (cType)
        {
        case CAN_RX_WRITE:
            if (TxState==CAN_TX_SEND)
            {
                if (((cRxBuf[7]<<8) | cRxBuf[8])==Task[htask].wAddr)
                    TxState=CAN_TX_SUCCESS;
            }
            break;
        }
    }
} 

void CTaskCan::On_TaskCan()
{ 
    if (mfileDeviceCan<0)
        return;

    ReceiveTaskCan();
    SendTaskCan();
    ioctl(mfileDeviceCan, 0, 0);

} 


