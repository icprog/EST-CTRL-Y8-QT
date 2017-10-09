#ifndef     TASK_COM_BASE_H
#define     TASK_COM_BASE_H

#include <QObject>
#include <QFile>


#define     _KEY_NULL           0x00F0  //空键
#define     COM_RETRY_INTERVAL  ( 100 )

#define		MAX_TXBUF           (8*256)		//unsigned char 4
#define		MAX_RXBUF           (32*256)     //unsigned char 16

#define		MAX_TX_COMM         48           // 32

#define		MAX_TX_BUF          128+6		//unsigned short
#define		MAX_RX_BUF          128			//unsigned short

#define		COMM_TX_IDLE        0           //任务空闲，
#define		COMM_TX_WAIT        1           //有任务需要发送
#define		COMM_TX_SEND        2
#define		COMM_TX_SUCCESS     3

#define     COMM_TX_LCD         0xFA05
#define		COMM_TX_LED			0xF805
#define		COMM_TX_KEY			0xF905
#define		COMM_RX_KEY			0xF004
#define     COMM_RX_KEYCONNECT  0xF104
#define		COMM_TX_MAINPRG     0x1190
#define     COMM_RX_RESPONSE    0x1100
#define     COMM_RX_NOAPP       0x112a
#define     COMM_RX_TOUCH_PRESS 0xF105
#define     COMM_RX_TOUCH_RELEASE  0xF205

#define		OUTOP_NULL          0x0

/*===========================================================================+
|           Type definition                                                  |
+===========================================================================*/
typedef struct tagTXCOMM 
{
    unsigned short    wType;
    unsigned short    wAddr;
    unsigned short    wCount;
    unsigned short    wData;
    unsigned short    wBuf[20];

} TXCOMM;

typedef struct tagICOMM 
{
    unsigned short    iRxHead;
    unsigned short    iRxTail;
    char 	cRxBuf[MAX_RXBUF];

    unsigned short    iTxHead;
    unsigned short 	iTxTail;
    char 	cTxBuf[MAX_TXBUF];

} ICOMM;

typedef struct tagTASKCOMM 
{
    unsigned char    TxState;
    unsigned char   hTask;
    unsigned char   hTail;
    unsigned short    nRetry;
    unsigned char    nCounter;
    TXCOMM  Task[MAX_TX_COMM];

    unsigned short    wPanelKey;
    unsigned char    nOutputOP;

    unsigned short    wRxCount;                 //byte received
    unsigned short    wTxPack;
    unsigned short    wRxPack;

    unsigned short    wRxBuf[MAX_RX_BUF];       //Receive buffer
    unsigned short    wTxBuf[MAX_TX_BUF];

    unsigned short    wRAM[4],wROM[4];

} TASKCOMM;


class CTaskComBase :public QObject
{
    Q_OBJECT
public:
    CTaskComBase();

public:
    bool Init_TaskComm(const char * dev,int flag);
    void On_TaskComm();
    void CreateTask(unsigned short wType,unsigned short* buf,unsigned short wcount);

    bool isPacketChanged();


    void DataLogStart();        //start to log data to file
    void DataLogStop();         //stop log data

    bool devValid();
public:
    TASKCOMM  m_taskComm;
    ICOMM g_IComm;

    int mfileDeviceCom;
    int m_iPackLenIdx;
    int m_iLogIdx;

    unsigned short  m_iLastRxPack;          //保存最后一次数据包ID
    bool isLogStart;            //label

    QFile mfileLog;

protected:

    void DataLog();             //Log data to disk.

    void WriteComm(unsigned short * pData, unsigned char nCount);
    unsigned char ReadComm(unsigned short * pData, unsigned char nCount);

    int  OpenDev(const char *Dev,int flag);
    void Init_SendComm();

    void SerialCommRx();
    void SerialCommTx();

    virtual void SendTaskComm();

    virtual void ReceiveTaskComm();
    virtual void ProcessRxData();

    void Destroy_TaskComm();

signals:
    void ComKeyCommand(unsigned short );    //for motion simulate

    void ChxValData(unsigned short *);
};


#endif  //TASK_COM_BASE_H



