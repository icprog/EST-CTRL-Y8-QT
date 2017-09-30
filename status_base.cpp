#include "status_base.h"
#include "resource_manager.h"

CStatusBase::CStatusBase(QWidget *parent) :
    QWidget(parent)
{

    for(int mIdx = 0 ; mIdx < SYS_MOTOR_MAX; mIdx++)
    {
        lbIcon[mIdx]    = new QFrame(this);
        lbIcon[mIdx]->setVisible(false);

        lcd[mIdx]   = new QLCDNumber(this);
        lcd[mIdx]->setLineWidth(0);
        lcd[mIdx]->setSegmentStyle(QLCDNumber::Flat);
        lcd[mIdx]->setStyleSheet("color : blue");
        lcd[mIdx]->lower();
        lcd[mIdx]->setVisible(false);

    }

    timerStatusFresh = new QTimer(this);
    connect(timerStatusFresh,SIGNAL(timeout()),this,SLOT(OnStatusFresh()));
    timerStatusFresh->setInterval(TIME_INFO_FRESH);

    setVisible(false);
}

void CStatusBase::showEvent(QShowEvent *)
{
    timerStatusFresh->start();
    RsMgr->VisibleWidgetAdd(this);
}
void CStatusBase::hideEvent(QHideEvent *)
{
    timerStatusFresh->stop();
    RsMgr->VisibleWidgetDel(this);
}
void CStatusBase::OnViewDirChange(int)
{

}
void CStatusBase::OnStatusFresh()
{

    int mDirTemp = m_iViewDir;
    //界面根据角度切换
    if( g_systemDb->g_dbMachine.CurrentData[2] + 50 < 0)
    {

        if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
            mDirTemp = VIEW_DIR_LEFT;
        else
            mDirTemp = VIEW_DIR_RIGHT;
    }else if( g_systemDb->g_dbMachine.CurrentData[2] - 50 < 0)
    {
        mDirTemp = VIEW_DIR_NORMAL;
    }else if(g_systemDb->g_dbMachine.CurrentData[2] > 50)
    {

        if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
            mDirTemp = VIEW_DIR_RIGHT;
        else
            mDirTemp = VIEW_DIR_LEFT;
    }

    if(mDirTemp != m_iViewDir)
    {
        if(!g_dbsys.utility.mAutoRotate)
            return;

        m_iViewDir = mDirTemp;

        OnViewDirChange(m_iViewDir);
        emit ViewDirChange(m_iViewDir);
    }
}

void CStatusBase::mousePressEvent(QMouseEvent *event)
{
     qDebug()<<"CTitleBase::mousePressEvent";
    if(event->type() == QEvent::MouseButtonPress)
    {
        unsigned short keyBuf[2];
        keyBuf[0] =0;
        keyBuf[1] = EMG_STOP_V1;
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
    }
}
