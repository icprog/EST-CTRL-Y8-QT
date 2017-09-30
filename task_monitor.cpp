
#include "task_monitor.h"
#include "sys_database.h"
#include "resource_manager.h"

#define MONITOR_HOURS_BEFORE_INSTALL    (300)

CTaskMonitor::CTaskMonitor()
{

    m_iOneTimeVersionGet = false;
}

void CTaskMonitor::InitDog()
{
}

void CTaskMonitor::Dogging()
{

}

void CTaskMonitor::TimeoutMonitor()
{
    if (!g_dbsys.operationx.cState)
        return;

    //start date
    QDateTime dtStart(QDate(2000+g_dbsys.dateStart.year,g_dbsys.dateStart.month,g_dbsys.dateStart.day));
    dtStart = dtStart.addSecs(g_dbsys.operationx.tHour*3600 + g_dbsys.operationx.tMinute*60);

    //time out date
    QDateTime dTimeout = dtStart.addMonths((g_dbsys.operationx.cNowNum-1) * g_dbsys.operationx.cPeriodLength);
    QDateTime dToday = QDateTime::currentDateTime();

    //time out and cPeriods > 0
    if (( dToday >= dTimeout ) && ( g_dbsys.operationx.cPeriods > 0 ))
    {
        g_dbsys.operation.bTimeout = true;  //change ram
        g_systemDb->SaveSystemCfg("operation/bTimeout",g_dbsys.operation.bTimeout);     //save to disk
    }
}
void CTaskMonitor::InstallMonitor()
{
    //如果已经输入过识别码，不再验证300个小时是否到
    if(g_dbsys.operationx.keyInstalled == 1)
        return;

    if( g_dbsys.dbsystem.mTotalTime > MONITOR_HOURS_BEFORE_INSTALL)
    {
        g_dbsys.operationx.keyNeed = true;
    }
}
void CTaskMonitor::DateLostMonitor()
{
    //如果已经输入过识别码，并且分期付款已经结束,不再查看电池信息
    if(g_dbsys.operationx.keyInstalled == 1)
        if (!g_dbsys.operationx.cState)
            return;

    //如果开启分期付款，且时间早于2015，则认为需要输入密码
    QDate dt = QDate::currentDate();

    //check at start up only
    if(dt.year() <= 2016)
    {
        g_dbsys.operation.bTimeNeedSet = true;
        g_dbsys.operation.bStopRunMach = true;
    }
}
void   	CTaskMonitor::Init_TaskMonitor()
{
    InitDog() ;

    m_lCounter  = 0;
    timerSecond = 0;
    //timerMinute = 0;
    timerMinute = g_systemDb->getSystemCfg("dbsystem/mTimerMinute",0).toUInt();  //load minute from disk
    timerTick.start();

    DateLostMonitor();      //check if the date is lost
    TimeoutMonitor();       //period monitor
    InstallMonitor();           //install monitor

}

void CTaskMonitor::On_TaskMonitor()
{

    //g_nCounter   10ms
    g_nCounter = timerTick.elapsed()/10;

    if (g_nCounter - m_lCounter < 100)
        return;

    m_lCounter = g_nCounter;

    Dogging();

    timerSecond++;
    if(timerSecond == 60)
    {
        timerSecond = 0;
        timerMinute++ ;
        g_systemDb->SaveSystemCfg("dbsystem/mTimerMinute",timerMinute);  //save minute from disk

        //autorun mode,save mSelfRunTime every 1 minute.
        if(g_systemDb->isAutoRun())
        {
            g_dbsys.dbsystem.mSelfRunTime++;
            g_systemDb->SaveSystemCfg("dbsystem/mSelfRunTime",g_dbsys.dbsystem.mSelfRunTime);
        }
    }

    if(timerMinute >= 60)
    {
        timerMinute=0;

        //mOperationTime save every 1 hour.
        g_dbsys.dbsystem.mOperationTime++;
        g_systemDb->SaveSystemCfg("dbsystem/mOperationTime",g_dbsys.dbsystem.mOperationTime);

        //total time ,save every 1 hour
        g_dbsys.dbsystem.mTotalTime++;
        g_systemDb->SaveSystemCfg("dbsystem/mTotalTime",g_dbsys.dbsystem.mTotalTime);

        TimeoutMonitor();       //period monitor //check every hour ,for period password
        InstallMonitor();           //install monitor  //check every hour ,for install password
    }

    //net client mode;g_bCommunicate is detected by network
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(g_netBase)
        {
            if(g_netBase->isConnected())
            {
                g_systemDb->g_bCommunicate = true;
                RsMgr->g_simBase->setVisible(false);
                return;
            }
        }

        g_systemDb->g_bCommunicate = false;
        return;
    }

    //g_bMotionSimulate mode; do not detected g_bCommunicate
    if(g_systemDb->g_bMotionSimulate)
        return;

    //other mode; use comm as g_bCommunicate source
    if (g_taskComCtrl->isPacketChanged())
        g_systemDb->g_bCommunicate = true;
    else
        g_systemDb->g_bCommunicate = false;

    if(!m_iOneTimeVersionGet)
    {
        if(g_taskComCtrl)
        {

            if(g_dbsys.utility.mPlatform == PF_NDT_10_A)
                return;

            g_taskComCtrl->CreateTask(CMD_FUNC_VER,NULL,0);
            m_iOneTimeVersionGet = true;
        }
    }
}


