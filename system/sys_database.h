#ifndef     D__DATABASE
#define     D__DATABASE

#include <QSettings>
#include <qdatetime.h>
#include "./base/task_com_ctrl.h"


//宏定义

#define MARK_USED                 ( 0xEB90 )

#define SYS_CMD_LENGTH              ( 10 )
#define SYS_CMD_NORMAL              ( 0x0020 )
#define SYS_CMD_SETTING             ( 0x0021 )
#define SYS_CMD_DEBUG               ( 0x0022 )
#define SYS_STATUS_NORMAL           ( 0x0000 )
#define SYS_STATUS_SETTING          ( 0x0001 )
#define SYS_STATUS_DEBUG            ( 0x0002 )

#define GEN_PAR_MAX               ( 20 )
#define GEN_PAR_OPT               ( 10 )
#define SYS_CURRENT_DATA_SIZE     ( 20 )
#define SYS_POSI_DATA_LEN         ( 16 )
#define SYS_STAT_DATA_LEN         ( 8 )
#define SYS_SLOW_DATA_LEN         ( 8 )

#define MAX_FAST_RECORD           (10)
#define MAX_FAST_MOTOR            (8)

#define MAX_NDT_SMART_RECORD           (6)
#define MAX_NDT_SMART_MOTOR            (11)

#define SYS_LIGHT_CURTAIN_PAR_LEN   8

//原来为13，在最后一位增加了电机是否保护的标识位
#define SYS_NDT_STATE_PAR_LEN   14

typedef struct  __attribute__((aligned(4)))  tagOPERATION
{
    bool    bTimeout;           //stop working
    bool    bTimeNeedSet;   //if the year less than 2015,be ture
    bool    bStopRunMach;   //disable all movement;
} OPERATION;

typedef struct __attribute__((aligned(4))) tagDATE
{
    unsigned char       year;               // years
    unsigned char       month;              // months since January - [0~11]
    unsigned char       day;                // day of the month - [1~31]
} DATE;

typedef struct  __attribute__((aligned(4)))  tagOPERATIONX
{
    unsigned char       cState;
    unsigned char       cPeriods;
    unsigned char       cPeriodLength;
    unsigned char       tHour;
    unsigned char       tMinute;
    unsigned short      wInterval;
    unsigned char       cAlarmDays;
    unsigned char       cStopDays;
    unsigned short      wIdentifyCode;
    unsigned int          dwPassword;
    unsigned char       cNowNum;
    unsigned char       keyInstalled;
    unsigned char       keyNeed;
} OPERATIONX;

typedef struct  __attribute__((aligned(4)))   tagDB_SYSTEM
{
    unsigned char       language;
    char                machine2[8+1];
    unsigned short      mMaintenanceTime;
    unsigned int          mOperationTime;         //section run time,can reset to 0
    unsigned int          mTotalTime;                 //total run time,hours,can't reset
    //unsigned int          mStartUpTimes;          //record start up times
    unsigned short      mSelfRunTime;
    unsigned short      mSelfRunTotal;
} DB_SYSTEM;

typedef struct __attribute__((aligned(4))) tagDB_UTILITY
{
    unsigned short  keySound;
    unsigned short  keyTestPass;
    unsigned short  mSkinIdx;
    unsigned short  autoRunMinute;
    short           mTemperatureAdj;
    unsigned short  mPlatform;                  //PF_CEIL_10_A
    unsigned short  mDetectorStandDir;          //DETECTOR_STAND_LEFT
    unsigned short  mNetTcpMode;
    unsigned short  mNetUdpMode;
    unsigned short  mNetShow;
    unsigned short  mSimulate;
    unsigned short  mShutdownShow;
    unsigned short  mFilmKeyEnable;
    unsigned short  mScreenKeyEnable;
    unsigned short  mAutoRotate;
    unsigned short  mCursorShow;
    unsigned short  mTubeTempShow;
    unsigned short  mGeneratorShow;
    unsigned short  mConfigShow;
    unsigned short  mSmartShow;
    unsigned short  mTryTimes;
    unsigned short  mCommProtocol;
    unsigned short  mNetMode;           //lan(eth0),wifi(wlan0)
} DB_UTILITY;

typedef struct  __attribute__((aligned(4)))  tagDB_SYS
{
    unsigned short  wMarkUsed;
    DB_SYSTEM       dbsystem;
    OPERATION       operation;
    OPERATIONX      operationx;
    DB_UTILITY      utility;
    DATE            dateOut;                    /*not used*/
    DATE            dateStart;                  /*分期付款的首次停机日期*/
    char            softVersion[16];        /*软件版本 xx.xx.xx.xx*/
    char            firmVersion[16];        /*control board version xxxx.xxxx*/
    //char            telManufacture[16];     /*工厂电话*/
    //char            telSeller[16];          /*销售电话*/
    //char            hostpitalName[128];
    //char            hostpitalAddr[128];
} DB_SYS;

typedef struct tagDB_MACHINE
{
    short               CurrentData[SYS_CURRENT_DATA_SIZE];
    short               PosiData[SYS_POSI_DATA_LEN];
    short               SlowData[SYS_SLOW_DATA_LEN];
    short               StateData[SYS_STAT_DATA_LEN];

} DB_MACHINE;


typedef struct SBodyPar
{
    unsigned char mKv;
    unsigned char mFocus;
    unsigned char mAec;
    unsigned char mMas;
    unsigned char mMs;
    unsigned char mMa;
    unsigned char mTech;
}BodyPar;

class CSystemDataBase
{
public:
    CSystemDataBase();
    ~CSystemDataBase();

    unsigned int  getInitError();       //return m_iInitErrCode
    unsigned int  getInitParam();       //return m_iInitParam
    unsigned int  getInitState();
    bool SaveSystem(QString);            //保存系统参数

private:

    bool ReadSystem(QSettings * );            //读取系统参数


    bool m_bAutoRun;              //自运行标记
    int m_bIsPopSmartShow;         //Smart Popup 是否正在显示
    unsigned int m_iInitState;       //初始化状态
    unsigned int m_iInitParam;       //初始化状态参数
    unsigned int m_iInitErrCode;     //初始化状态代码

    void GeneratorParameterDefault();              //发生器参数复位

public:
    int getPopSmartShowState();             //获取Smart Pop 是否正在显示
    void setPopSmartShowState(int);         //设置Smart Pop 是否正在显示
    int FastDataSave(unsigned int ,unsigned short *);
    unsigned short * FastDataGet(unsigned int);
    int FastDataInit();

    int NdtSmartDataSave(unsigned int,unsigned short *);
    int NdtSmartDataLoad();
    int NdtSmartDataGet(int,int);
    QList <unsigned short> m_ArrNdtData;
    // unsigned short m_NdtData[MAX_NDT_SMART_RECORD][MAX_NDT_SMART_MOTOR];       //0.blank,1-8.data,9.check

private:
    unsigned short m_FastData[MAX_FAST_RECORD][MAX_FAST_MOTOR];       //0.blank,1-8.data,9.check

public:

    void Init_DataBase();                          //初始化数据库
    void setInitState(unsigned int state,unsigned int err,unsigned int param = 0);
    void SaveSystemCfg(QString ,QVariant );
    QVariant getSystemCfg(const QString & key, const QVariant & defaultValue  );
    bool isAutoRun();                              //自运行判断
    void SetAutoRun(bool );                        //自运行控制

    void GeneratorParameterLoad();                 //发生器参数加载

    void GenParamSave();                 //发生器参数保存

    int g_startAngle;               //存储启动的角度
    bool           g_bCommunicate;                 //通信状态标记
    bool           g_bDataSaved;                   //数据回馈标记
    bool           g_bPosDataValid;                //位置数据有效标记
    bool           g_bNoApp;                       //下位机程序丢失
    bool           g_bMotionSimulate;               //simulate
    bool           g_bAutoRunOpen;
    int             g_iAutoRunMode;             //auto run mode for test ,fast ,soft ,switch ,
    unsigned short m_SelfRunInterval;

    DB_MACHINE     g_dbMachine;                    //通信数据

    unsigned short g_iArrLightCurtain[SYS_LIGHT_CURTAIN_PAR_LEN];
    unsigned long g_ctrLightCurtainMsg;

    unsigned short g_iArrNdtState[SYS_NDT_STATE_PAR_LEN];       //NDT buffer
    unsigned long g_ctrNdtStateMsg;

    BodyPar        m_sBody[GEN_PAR_MAX];           //APR参数数据
    BodyPar        m_sBodyBuf[GEN_PAR_MAX];        //APR参数数据

    long           packno;                         //下位机更新数据包编号
    unsigned short packLen;                        //下位机更新数据包长度

    unsigned short 	       g_nPrgPack;              //下位机返回的数据包编号
    unsigned short 	       g_wPrgBuf[MAX_TX_BUF];

    bool m_bCanSaveDate;      //save date function
    bool m_bCanUpdate;          //update function
    int mDateJulian; //for date change check
};

#endif                          


