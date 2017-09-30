
#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QSettings>

#include "sys_database.h"
#include "resource_manager.h"

#define SYS_APR_DEFAULT_PATH "/sdcard/home/fa/genapr.ini"

CSystemDataBase::CSystemDataBase()
{
    m_iInitErrCode  = 0;
    m_iInitParam    = 0;
    m_iInitState    = INIT_STATE_NORMAL;    //初始化状态

    g_bCommunicate  = false;
    m_bAutoRun      = false;
    g_bDataSaved    = false;
    g_bPosDataValid = false;
    g_bNoApp        = false;
    g_bMotionSimulate = false;
    g_bAutoRunOpen = false;
    m_SelfRunInterval = 3;
    packLen         = 0;
    g_nPrgPack      = 0;

    //default keyNeed is false
    g_dbsys.operationx.keyNeed = false;
    g_dbsys.operation.bTimeout = false;             //default time out true
    g_dbsys.operation.bTimeNeedSet = false;     //only the year less than 2015 ,be true
    g_dbsys.operation.bStopRunMach=false;       //be true by other setting,such as time out,year less than 2015
    mDateJulian = 0;                                                //if mDateJulian, the date save function will not check.

    //init all ndt array to 0
    for(int mIdx = 0 ; mIdx < MAX_NDT_SMART_RECORD ; mIdx++)
        for(int mCtr = 0 ; mCtr < MAX_NDT_SMART_MOTOR ; mCtr++)
            m_ArrNdtData.push_back(0);


    memset(&g_dbMachine ,0,sizeof(DB_MACHINE));

    memset(g_iArrLightCurtain,0,SYS_LIGHT_CURTAIN_PAR_LEN*2);
    g_ctrLightCurtainMsg = 0;

    memset(g_iArrNdtState,0,SYS_NDT_STATE_PAR_LEN * 2);
    g_ctrNdtStateMsg = 0;

    //init the control board version to 0000.0000
    memset(g_dbsys.firmVersion,0x30,16);
    g_dbsys.firmVersion[4] = '.';
    g_dbsys.firmVersion[9] = 0;

    //默认启动时，Pop Smart 没有显示
    m_bIsPopSmartShow = false;
}

CSystemDataBase::~CSystemDataBase()
{

}
int CSystemDataBase::getPopSmartShowState()
{
    return m_bIsPopSmartShow;
}
void CSystemDataBase::setPopSmartShowState(int isShow)
{
    m_bIsPopSmartShow = isShow;
}
unsigned int CSystemDataBase::getInitState()
{
    return m_iInitState;
}
unsigned int CSystemDataBase::getInitError()
{
    return m_iInitErrCode;
}
unsigned int CSystemDataBase::getInitParam()
{
    return m_iInitParam;
}

//设置初始化错误与参数
//只记录等级最高的错误
void CSystemDataBase::setInitState(unsigned int state,unsigned int err,unsigned int param)
{
    if(state > m_iInitState)
    {
        m_iInitState    = state;
    }else
    {
        return;
    }

    if(m_iInitState >= INIT_STATE_CLEAR)
        m_iInitState = INIT_STATE_NORMAL;

    m_iInitErrCode  = err;
    m_iInitParam    = param;

}
void CSystemDataBase::Init_DataBase()
{
    Q_ASSERT(g_mainCfg != NULL);

    if(!ReadSystem(g_mainCfg))
    {
        setInitState(INIT_STATE_WARNING,INIT_WARNING_DATA_BASE);
    }

    NdtSmartDataLoad();
    FastDataInit();
    GeneratorParameterLoad();                   //加载发生器页面参数
}

bool CSystemDataBase::ReadSystem(QSettings * cfgFile)
{
    if(!cfgFile)
    {
        SaveSystem(SYS_MAIN_CFG_FILE);

        return false;
    }

    char * cBuf;

    g_dbsys.wMarkUsed = cfgFile->value("wMarkUsed","0").toInt();
    if(g_dbsys.wMarkUsed != MARK_USED)
        return false;

    g_dbsys.dbsystem.language  = cfgFile->value("dbsystem/language",_CHINESE).toInt();

    QFile fileMechCode(QCoreApplication::applicationDirPath() +"/MachCode");
    char mBufCode[MACHINE_CODE_LEN + 1];
    memset(mBufCode,0,MACHINE_CODE_LEN + 1);

    //display the machine code in the file
    if(fileMechCode.exists())
    {
        fileMechCode.open(QFile::ReadOnly);
        fileMechCode.read(mBufCode,MACHINE_CODE_LEN);
        fileMechCode.close();
        strcpy(g_dbsys.dbsystem.machine2,mBufCode);
    }else
    {
        cBuf = cfgFile->value("dbsystem/machine2","00000000").toByteArray().data();
        if(strlen(cBuf) <= 8)
            strcpy(g_dbsys.dbsystem.machine2,cBuf);
    }

    //正常显示  //左转显示  //右转显示//旋转180度显示
    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT//VIEW_DIR_R180
    g_startAngle = cfgFile->value("StartAngle",VIEW_DIR_NORMAL).toInt();

    g_dbsys.dbsystem.mMaintenanceTime = cfgFile->value("dbsystem/mMaintenanceTime","5000").toInt();

    g_dbsys.dbsystem.mOperationTime = cfgFile->value("dbsystem/mOperationTime","0").toInt();

    g_dbsys.dbsystem.mTotalTime = cfgFile->value("dbsystem/mTotalTime","0").toInt();

    unsigned int mStartUpTimes = cfgFile->value("dbsystem/mStartUpTimes","0").toInt();
    cfgFile->setValue("dbsystem/mStartUpTimes",++mStartUpTimes);                       //add 1 every start up

    g_dbsys.dbsystem.mSelfRunTime = cfgFile->value("dbsystem/mSelfRunTime","0").toInt();

    g_dbsys.dbsystem.mSelfRunTotal = cfgFile->value("dbsystem/mSelfRunTotal","1440").toInt();

    g_dbsys.operation.bTimeout = cfgFile->value("operation/bTimeout","0").toInt();

    g_dbsys.operationx.cState = cfgFile->value("operationx/cState","0").toInt();

    g_dbsys.operationx.cPeriods = cfgFile->value("operationx/cPeriods","4").toInt();

    g_dbsys.operationx.cPeriodLength = cfgFile->value("operationx/cPeriodLength","3").toInt();

    g_dbsys.operationx.tHour = cfgFile->value("operationx/tHour","0").toInt();

    g_dbsys.operationx.tMinute = cfgFile->value("operationx/tMinute","0").toInt();

    g_dbsys.operationx.keyInstalled = cfgFile->value("operationx/keyInstalled","0").toInt();

    g_dbsys.dateOut.year = cfgFile->value("dateOut/year","15").toInt();

    g_dbsys.dateOut.month = cfgFile->value("dateOut/month","1").toInt();

    g_dbsys.dateOut.day = cfgFile->value("dateOut/day","1").toInt();

    g_dbsys.dateStart.year = cfgFile->value("dateStart/year","15").toInt();

    g_dbsys.dateStart.month = cfgFile->value("dateStart/month","1").toInt();

    g_dbsys.dateStart.day = cfgFile->value("dateStart/day","1").toInt();

    g_dbsys.operationx.wInterval = cfgFile->value("operationx/wInterval","1").toInt();

    g_dbsys.operationx.cAlarmDays = cfgFile->value("operationx/cAlarmDays","0").toInt();

    g_dbsys.operationx.cStopDays = cfgFile->value("operationx/cStopDays","1").toInt();

    g_dbsys.operationx.wIdentifyCode = cfgFile->value("operationx/wIdentifyCode","0").toInt();

    g_dbsys.operationx.dwPassword = cfgFile->value("operationx/dwPassword","12995").toInt();

    g_dbsys.operationx.cNowNum = cfgFile->value("operationx/cNowNum","0").toInt();

    g_dbsys.utility.autoRunMinute = cfgFile->value("utility/autoRunMinute","0").toInt();

    g_dbsys.utility.keySound = cfgFile->value("utility/keySound","1").toInt();

    g_dbsys.utility.keyTestPass = cfgFile->value("utility/keyTestPass","0").toInt();

    g_dbsys.utility.mSkinIdx = cfgFile->value("utility/mSkinIdx","0").toInt();

    g_dbsys.utility.mTemperatureAdj = cfgFile->value("utility/mTemperatureAdj","0").toInt();

    g_dbsys.utility.mPlatform = cfgFile->value("utility/mPlatform","1").toInt();

    g_dbsys.utility.mDetectorStandDir = cfgFile->value("utility/mDetectorStandDir","0").toInt();//DETECTOR_STAND_LEFT

    g_dbsys.utility.mNetTcpMode = cfgFile->value("utility/mNetTcpMode","0").toInt();  //TARGET_TCP_SERVER

    g_dbsys.utility.mNetShow = cfgFile->value("utility/mNetShow","0").toInt();

    g_dbsys.utility.mSimulate = cfgFile->value("utility/mSimulate","0").toInt();  //FUNC_SIMULATE_OFF

    g_dbsys.utility.mShutdownShow = cfgFile->value("utility/mShutdownShow","0").toInt();

    g_dbsys.utility.mFilmKeyEnable = cfgFile->value("utility/mFilmKeyEnable","1").toInt();

    g_dbsys.utility.mScreenKeyEnable = cfgFile->value("utility/mScreenKeyEnable","1").toInt();

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mAutoRotate = cfgFile->value("utility/mAutoRotate","1").toInt();
#else
    g_dbsys.utility.mAutoRotate = cfgFile->value("utility/mAutoRotate","0").toInt();
#endif

    g_dbsys.utility.mCursorShow = cfgFile->value("utility/mCursorShow","0").toInt();

    g_dbsys.utility.mTubeTempShow = cfgFile->value("utility/mTubeTempShow","0").toInt();

    g_dbsys.utility.mGeneratorShow = cfgFile->value("utility/mGeneratorShow","0").toInt();

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mConfigShow = cfgFile->value("utility/mConfigShow","1").toInt();
#else
    g_dbsys.utility.mConfigShow = cfgFile->value("utility/mConfigShow","0").toInt();
#endif

    g_dbsys.utility.mSmartShow = cfgFile->value("utility/mSmartShow","1").toInt();

    g_dbsys.utility.mTryTimes = cfgFile->value("utility/mTryTimes","12").toInt();

    g_dbsys.utility.mCommProtocol = cfgFile->value("utility/mCommProtocol","1").toInt();  //COMM_PROTOCOL_00

    g_dbsys.utility.mNetMode = cfgFile->value("utility/mNetMode","0").toInt();    //NET_LAN

    memset(g_dbsys.softVersion,0,16);
    cBuf = cfgFile->value("softVersion","2.3.1.0").toByteArray().data();
    if(strlen(cBuf) <= 16)
        strcpy(g_dbsys.softVersion,cBuf);

    return true;
}

bool CSystemDataBase::SaveSystem(QString file)
{

    QSettings * configMedcare = new QSettings(file,QSettings::IniFormat);

    g_dbsys.wMarkUsed =0xEB90 ;        //0xEB90
    configMedcare->setValue("wMarkUsed",g_dbsys.wMarkUsed);

    g_dbsys.dbsystem.language            = _CHINESE;
    configMedcare->setValue("dbsystem/language",_CHINESE);

    memset(g_dbsys.dbsystem.machine2,'0',8);
    g_dbsys.dbsystem.machine2[8]         = 0;
    configMedcare->setValue("dbsystem/machine2",g_dbsys.dbsystem.machine2);

    g_dbsys.dbsystem.mMaintenanceTime    = 5000;
    configMedcare->setValue("dbsystem/mMaintenanceTime",g_dbsys.dbsystem.mMaintenanceTime);

    g_dbsys.dbsystem.mOperationTime      = 0;
    configMedcare->setValue("dbsystem/mOperationTime",g_dbsys.dbsystem.mOperationTime);

    g_dbsys.dbsystem.mTotalTime      = 0;
    configMedcare->setValue("dbsystem/mTotalTime",g_dbsys.dbsystem.mTotalTime);

    g_dbsys.dbsystem.mSelfRunTime        = 0;
    configMedcare->setValue("dbsystem/mSelfRunTime",g_dbsys.dbsystem.mSelfRunTime);

    g_dbsys.dbsystem.mSelfRunTotal       = 1440;
    configMedcare->setValue("dbsystem/mSelfRunTotal",g_dbsys.dbsystem.mSelfRunTotal);

    configMedcare->setValue("operation/bTimeout",g_dbsys.operation.bTimeout);

    g_dbsys.operationx.cState            = 0;
    configMedcare->setValue("operationx/cState",g_dbsys.operationx.cState);

    g_dbsys.operationx.cPeriods          = 4;
    configMedcare->setValue("operationx/cPeriods",g_dbsys.operationx.cPeriods);

    g_dbsys.operationx.cPeriodLength     = 3;
    configMedcare->setValue("operationx/cPeriodLength",g_dbsys.operationx.cPeriodLength);

    g_dbsys.operationx.tHour             = 15;
    configMedcare->setValue("operationx/tHour",g_dbsys.operationx.tHour);

    g_dbsys.operationx.tMinute           = 0;
    configMedcare->setValue("operationx/tMinute",g_dbsys.operationx.tMinute);

    g_dbsys.dateOut.year      = 15;
    configMedcare->setValue("dateOut/year",g_dbsys.dateOut.year);

    g_dbsys.dateOut.month     = 1;
    configMedcare->setValue("dateOut/month",g_dbsys.dateOut.month);

    g_dbsys.dateOut.day       = 1;
    configMedcare->setValue("dateOut/day",g_dbsys.dateOut.day);

    g_dbsys.dateStart.year    = 15;
    configMedcare->setValue("dateStart/year",g_dbsys.dateStart.year);

    g_dbsys.dateStart.month   = 1;
    configMedcare->setValue("dateStart/month",g_dbsys.dateStart.month);

    g_dbsys.dateStart.day     = 1;
    configMedcare->setValue("dateStart/day",g_dbsys.dateStart.day);

    g_dbsys.operationx.wInterval         = 1;
    configMedcare->setValue("operationx/wInterval",g_dbsys.operationx.wInterval);

    g_dbsys.operationx.cAlarmDays        = 0;
    configMedcare->setValue("operationx/cAlarmDays",g_dbsys.operationx.cAlarmDays);

    g_dbsys.operationx.cStopDays         = 1;
    configMedcare->setValue("operationx/cStopDays",g_dbsys.operationx.cStopDays);

    g_dbsys.operationx.wIdentifyCode     = 0;
    configMedcare->setValue("operationx/wIdentifyCode",g_dbsys.operationx.wIdentifyCode);

    g_dbsys.operationx.dwPassword        = 12995;
    configMedcare->setValue("operationx/dwPassword",g_dbsys.operationx.dwPassword);

    g_dbsys.operationx.cNowNum           = 0;
    configMedcare->setValue("operationx/cNowNum",g_dbsys.operationx.cNowNum);

    g_dbsys.utility.autoRunMinute        = 0;
    configMedcare->setValue("utility/autoRunMinute",g_dbsys.utility.autoRunMinute);

    g_dbsys.utility.keySound             = 1;
    configMedcare->setValue("utility/keySound",g_dbsys.utility.keySound);

    g_dbsys.utility.keyTestPass          = 0;
    configMedcare->setValue("utility/keyTestPass",g_dbsys.utility.keyTestPass);

    g_dbsys.utility.mSkinIdx             = 0;
    configMedcare->setValue("utility/mSkinIdx",g_dbsys.utility.mSkinIdx);

    g_dbsys.utility.mTemperatureAdj      = 0;
    configMedcare->setValue("utility/mTemperatureAdj",g_dbsys.utility.mTemperatureAdj);

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mPlatform            = PF_CEIL_10_A;
#else
    g_dbsys.utility.mPlatform            = PF_RAIL_12_A;
#endif
    configMedcare->setValue("utility/mPlatform",g_dbsys.utility.mPlatform);

    g_dbsys.utility.mDetectorStandDir    = DETECTOR_STAND_LEFT;
    configMedcare->setValue("utility/mDetectorStandDir",g_dbsys.utility.mDetectorStandDir);

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mNetTcpMode          = TARGET_TCP_SERVER;
#else
    g_dbsys.utility.mNetTcpMode          = TARGET_TCP_CLIENT;
#endif
    configMedcare->setValue("utility/mNetTcpMode",g_dbsys.utility.mNetTcpMode );

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mNetShow          = false;
#else
    g_dbsys.utility.mNetShow          = true;
#endif
    configMedcare->setValue("utility/mNetShow",g_dbsys.utility.mNetShow );

    g_dbsys.utility.mSimulate            = FUNC_SIMULATE_OFF;
    configMedcare->setValue("utility/mSimulate",g_dbsys.utility.mSimulate);

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mShutdownShow        = false;
#else
    g_dbsys.utility.mShutdownShow        = true;
#endif    
    configMedcare->setValue("utility/mShutdownShow",g_dbsys.utility.mShutdownShow);

    g_dbsys.utility.mFilmKeyEnable       = true;
    configMedcare->setValue("utility/mFilmKeyEnable",g_dbsys.utility.mFilmKeyEnable);

    g_dbsys.utility.mScreenKeyEnable     = true;
    configMedcare->setValue("utility/mScreenKeyEnable",g_dbsys.utility.mScreenKeyEnable);

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mAutoRotate          = true;
#else
    g_dbsys.utility.mAutoRotate          = false;
#endif
    configMedcare->setValue("utility/mAutoRotate",g_dbsys.utility.mAutoRotate);

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mCursorShow          = false;
#else
    g_dbsys.utility.mCursorShow          = true;
#endif
    configMedcare->setValue("utility/mCursorShow",g_dbsys.utility.mCursorShow);

    g_dbsys.utility.mTubeTempShow        = false;
    configMedcare->setValue("utility/mTubeTempShow",g_dbsys.utility.mTubeTempShow);

    g_dbsys.utility.mGeneratorShow       = false;
    configMedcare->setValue("utility/mGeneratorShow",g_dbsys.utility.mGeneratorShow);

#ifdef QT_ARCH_ARM
    g_dbsys.utility.mConfigShow       = true;
#else
    g_dbsys.utility.mConfigShow       = true;       //PAD配置左手，右手，通过出厂密码进入
#endif
    configMedcare->setValue("utility/mConfigShow",g_dbsys.utility.mConfigShow);

    g_dbsys.utility.mSmartShow           = true;
    configMedcare->setValue("utility/mSmartShow",g_dbsys.utility.mSmartShow);

    g_dbsys.utility.mTryTimes            = 12;
    configMedcare->setValue("utility/mTryTimes",g_dbsys.utility.mTryTimes);

    g_dbsys.utility.mCommProtocol        = COMM_PROTOCOL_01;    //0
    configMedcare->setValue("utility/mCommProtocol",g_dbsys.utility.mCommProtocol);

    g_dbsys.utility.mNetMode             = NET_LAN;             //0
    configMedcare->setValue("utility/mNetMode",g_dbsys.utility.mNetMode);

    strcpy(g_dbsys.softVersion,"2.4.1.0");
    configMedcare->setValue("softVersion",g_dbsys.softVersion);

    configMedcare->setValue("network/svrIP","169.254.001.080");
    configMedcare->setValue("network/svrNetMask","255.255.000.000");
    configMedcare->setValue("network/svrGate","169.254.001.001");
    configMedcare->setValue("network/svrDNS","169.254.001.001");

    configMedcare->setValue("network/clientIP","169.254.001.080");
    configMedcare->setValue("network/clientNetMask","255.255.000.000");
    configMedcare->setValue("network/clientGate","169.254.001.001");
    configMedcare->setValue("network/clientDNS","169.254.001.001");

    return true;
}
void CSystemDataBase::SaveSystemCfg(QString  key,QVariant value)
{

    g_mainCfg->setValue(key,value);
    g_mainCfg->sync();

}
QVariant CSystemDataBase::getSystemCfg(const QString & key, const QVariant & defaultValue )
{

    return g_mainCfg->value(key,defaultValue);

}
bool CSystemDataBase::isAutoRun()
{
    return m_bAutoRun;
}
void CSystemDataBase::SetAutoRun(bool autoRun)
{
    m_bAutoRun = autoRun;

}

void CSystemDataBase::GeneratorParameterLoad()
{

    char * genAprFileName = NULL;

    Q_ASSERT(g_mainCfg != 0);
    genAprFileName = g_mainCfg->value("AprFile",SYS_APR_DEFAULT_PATH).toByteArray().data();

    if(!QFile::exists(genAprFileName))
    {
        GeneratorParameterDefault();
        return;
    }

    QSettings * configGenApr = new QSettings(genAprFileName,QSettings::IniFormat);
    Q_ASSERT(configGenApr != 0);

    QString mStr;

    for(int mIdxA = 0 ;mIdxA < GEN_PAR_MAX;mIdxA++)
    {

        mStr.sprintf("APR%02d/KV",mIdxA);
        m_sBody[mIdxA].mKv = configGenApr->value(mStr,70).toInt();

        mStr.sprintf("APR%02d/FOCUS",mIdxA);
        m_sBody[mIdxA].mFocus = configGenApr->value(mStr,SYS_FOCUS_SMALL).toInt();

        mStr.sprintf("APR%02d/AEC",mIdxA);
        m_sBody[mIdxA].mAec = configGenApr->value(mStr,4).toInt();

        mStr.sprintf("APR%02d/MAS",mIdxA);
        m_sBody[mIdxA].mMas = configGenApr->value(mStr,30).toInt();

        mStr.sprintf("APR%02d/MS",mIdxA);
        m_sBody[mIdxA].mMs = configGenApr->value(mStr,40).toInt();

        mStr.sprintf("APR%02d/MA",mIdxA);
        m_sBody[mIdxA].mMa = configGenApr->value(mStr,30).toInt();

        mStr.sprintf("APR%02d/TECH",mIdxA);
        m_sBody[mIdxA].mTech = configGenApr->value(mStr,1).toInt();
    }

    memcpy(m_sBodyBuf,m_sBody,sizeof(BodyPar) * GEN_PAR_MAX);

}
void CSystemDataBase::GeneratorParameterDefault()
{
    char * genAprFileName = NULL;

    Q_ASSERT(g_mainCfg != 0);
    genAprFileName = g_mainCfg->value("AprFile",SYS_APR_DEFAULT_PATH).toByteArray().data();

    QSettings * configGenApr = new QSettings(genAprFileName,QSettings::IniFormat);
    Q_ASSERT(configGenApr != 0);

    QString mStr;

    for(int mIdxA = 0 ;mIdxA < GEN_PAR_MAX;mIdxA++)
    {
        m_sBody[mIdxA].mKv = 70;
        mStr.sprintf("APR%02d/KV",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mKv);

        m_sBody[mIdxA].mFocus = SYS_FOCUS_SMALL;
        mStr.sprintf("APR%02d/FOCUS",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mFocus);

        m_sBody[mIdxA].mAec = 4;
        mStr.sprintf("APR%02d/AEC",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mAec);

        m_sBody[mIdxA].mMas = 30;
        mStr.sprintf("APR%02d/MAS",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mMas);

        m_sBody[mIdxA].mMs = 40;
        mStr.sprintf("APR%02d/MS",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mMs);

        m_sBody[mIdxA].mMa = 30;
        mStr.sprintf("APR%02d/MA",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mMa);

        m_sBody[mIdxA].mTech = 1;
        mStr.sprintf("APR%02d/TECH",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mTech);
    }

    memcpy(m_sBodyBuf,m_sBody,sizeof(BodyPar) * GEN_PAR_MAX);
}

void CSystemDataBase::GenParamSave()
{

    char * genAprFileName = NULL;

    Q_ASSERT(g_mainCfg != 0);
    genAprFileName = g_mainCfg->value("AprFile",SYS_APR_DEFAULT_PATH).toByteArray().data();

    QSettings * configGenApr = new QSettings(genAprFileName,QSettings::IniFormat);
    Q_ASSERT(configGenApr != 0);

    QString mStr;

    memcpy(m_sBody,m_sBodyBuf,sizeof(BodyPar) * GEN_PAR_MAX);

    for(int mIdxA = 0 ;mIdxA < GEN_PAR_MAX ; mIdxA++)
    {
        mStr.sprintf("APR%02d/KV",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mKv);

        m_sBody[mIdxA].mFocus = SYS_FOCUS_SMALL;
        mStr.sprintf("APR%02d/FOCUS",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mFocus);

        mStr.sprintf("APR%02d/AEC",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mAec);

        mStr.sprintf("APR%02d/MAS",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mMas);

        mStr.sprintf("APR%02d/MS",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mMs);

        mStr.sprintf("APR%02d/MA",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mMa);

        mStr.sprintf("APR%02d/TECH",mIdxA);
        configGenApr->setValue(mStr,m_sBody[mIdxA].mTech);
    }
}

int CSystemDataBase::NdtSmartDataLoad()
{

    QSettings * configNdt = new QSettings(QCoreApplication::applicationDirPath() + "/ndtConfig.ini",QSettings::IniFormat);
    QString mStrKeyVal;

    //init all ndt array to 0
    for(int mCh = 0 ; mCh < MAX_NDT_SMART_RECORD ; mCh++)
    {
        for(int mIdx = 0 ; mIdx < MAX_NDT_SMART_MOTOR ; mIdx++)
        {
            mStrKeyVal.sprintf("SMART/CH%02d/MOTOR%02d",mCh,mIdx);
            m_ArrNdtData[mCh * MAX_NDT_SMART_MOTOR + mIdx] =  configNdt->value(mStrKeyVal,"0").toUInt();
        }
    }
    return true;
}

int CSystemDataBase::NdtSmartDataGet(int channel , int index)
{
    return m_ArrNdtData[channel * MAX_NDT_SMART_MOTOR + index];
}
int CSystemDataBase::NdtSmartDataSave(unsigned int ch,unsigned short *dat)
{

    if(ch >= MAX_NDT_SMART_RECORD)
        return -1;

    QSettings * configNdt = new QSettings(QCoreApplication::applicationDirPath() + "/ndtConfig.ini",QSettings::IniFormat);
    QString mStrKeyVal;

    //init all ndt array to 0
    for(int mIdx = 0 ; mIdx < MAX_NDT_SMART_MOTOR ; mIdx++)
    {
        m_ArrNdtData[ch * MAX_NDT_SMART_MOTOR + mIdx] = dat[mIdx];
        mStrKeyVal.sprintf("SMART/CH%02d/MOTOR%02d",ch,mIdx);
        configNdt->setValue(mStrKeyVal,dat[mIdx]);
    }

    return true;
}

int CSystemDataBase::FastDataSave(unsigned int channel,unsigned short *mBuf)
{

    if( channel >= (MAX_FAST_RECORD - 1))
        return -1;

    QString mKey;
    QSettings * cfgFileFast = new QSettings("/sdcard/home/fa/fastdata.ini",QSettings::IniFormat);

    for(int mIdx = 0 ; mIdx < MAX_FAST_MOTOR ; mIdx++)
    {

        mKey.sprintf("FAST%d/data%d",channel,mIdx);
        cfgFileFast->setValue(mKey,mBuf[mIdx]);
    }

    mKey.sprintf("CHECK/CH%d",channel);
    cfgFileFast->setValue(mKey,23130);

    return true;
}

unsigned short * CSystemDataBase::FastDataGet(unsigned int idx)
{
    if(idx >= (MAX_FAST_RECORD - 1))
        return 0;

    if(m_FastData[MAX_FAST_RECORD - 1][idx] != 0x5a5a)
        return 0;

    return m_FastData[idx];

}
int CSystemDataBase::FastDataInit()
{

    memset(m_FastData,0x00,MAX_FAST_RECORD * MAX_FAST_MOTOR * 2);              //clear memory
    /*
    QString mKey;
    QSettings * cfgFileFast = new QSettings("/sdcard/home/fa/fastdata.ini",QSettings::IniFormat);

    for(int mIdx = 0 ; mIdx < MAX_FAST_RECORD - 1; mIdx++)
    {
        for(int mCtr = 0 ; mCtr < MAX_FAST_MOTOR ; mCtr++)
        {
            mKey.sprintf("FAST%d/data%d",mIdx,mCtr);
            m_FastData[mIdx][mCtr] = cfgFileFast->value(mKey,3000).toUInt();
        }

        mKey.sprintf("CHECK/CH%d",mIdx);
        m_FastData[MAX_FAST_RECORD - 1][mIdx]  = cfgFileFast->value(mKey,0).toUInt();
    }
*/
    return 0;
}
