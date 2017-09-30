#ifndef TASK_CAN_H
#define TASK_CAN_H

#include <QObject>
#include "task_com_ctrl.h"

#define		MAX_TX_CAN          ( 80 )

#define		CAN_TX_IDLE         (0)
#define		CAN_TX_WAIT         (1)
#define		CAN_TX_SEND         (2)
#define		CAN_TX_SUCCESS      (3)

#define		CAN_TX_IDRESPONSE   (0x08)
#define		CAN_TX_MAINTEST     (0x0C)
#define     CAN_TX_MAINPRG      (0x0D)

#define		CAN_RX_WRITE        (0x06)

class CTaskCan : public QObject
{
    Q_OBJECT

public:
    CTaskCan();

public:
    bool    Init_TaskCan();
    void    End_TaskCan();
    void    On_TaskCan();

    void    Create_TaskCan(unsigned char cType,unsigned char nId,unsigned short wAddr,unsigned int dwData);
    void    Destroy_TaskCan();

private:

    typedef struct tagTXCAN
    {
        unsigned char   cType;
        unsigned char   nId;
        unsigned short  wAddr;
        unsigned int    dwData;
    } TXCAN;


    unsigned char   TxState;
    unsigned char   hTask;
    unsigned char   hTail;
    unsigned char   nRetry;
    unsigned char   nCounter;
    char            cTxBuf[12];
    char            cRxBuf[12];
    TXCAN           Task[MAX_TX_CAN];
    unsigned short  wBuf[6];

private:
    void SaveRealCan();
    void Init_SendCan();
    void SendTaskCan();
    void ReceiveTaskCan();

    int mfileDeviceCan;
    int iRec;
    unsigned short iBuf;
    unsigned short myBuf[20000][5];

};

#endif  //TASK_CAN_H



