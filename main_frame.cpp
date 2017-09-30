#include <QFile>
#include <QMessageBox>
#include <QFontDatabase>

#include "main_frame.h"
#include "resource_manager.h"

CMainFrame::CMainFrame( QWidget* parent):
    QWidget(parent)
{

    setObjectName("CMainFrame");

    setGeometry(0,0,g_sysWidth,g_sysWidth);

    MySystem("hwclock -s");

    g_mainFrame = this;

    m_iSceneCount = 0;
    for(int mIdx = 0 ; mIdx < MAINFRAME_SCENE_MAX ; mIdx++)
    {
        pSceneFrame[mIdx]   = 0;
        pSceneWidget[mIdx]  = 0;
    }

    pViewFrame = new QGraphicsView(this);
    pViewFrame->setFrameShape(QFrame::NoFrame);
    pViewFrame->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pViewFrame->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pViewFrame->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    setSceneWidget(g_faceBase);

    pViewFrame->setGeometry(0,0,g_sysWidth,g_sysWidth);

    pViewFrame->rotate(g_sysFrameRotate);
    pViewFrame->show();

    internalTimer = new QTimer(this);
    connect( internalTimer, SIGNAL(timeout()), SLOT(OnMainFresh()));

    pFrTest = new QFrame(this);
    pFrTest->setStyleSheet("background-color:white;");
    pFrTest->setGeometry(0,0,10,10);
    pFrTest->setVisible(false);
}

void CMainFrame::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"CMainFrame::mousePressEvent";
    pFrTest->move(event->x(),event->y());
}
void CMainFrame::OnViewChange(int view)
{

    switch(view)
    {
    case VIEW_INSTALL:
    case VIEW_GEN_CFG:              //发生器参数配置模式
    case VIEW_PASSWORD:             //密码界面模式
    case VIEW_CONFIRM:              //密码到期模式
        setSceneWidget(g_mainSetting);
        break;
    case VIEW_GEN:                  //发生器显示模式
    case VIEW_MOTION:               //动画显示模式
        break;
    case VIEW_MAIN:                 //主界面显示模式
        setSceneWidget(RsMgr->g_mainBase);
        break;
    case  VIEW_CONSOLE:
        setSceneWidget(RsMgr->g_systemConsole);
        break;
    default:
        break;
    }
}

void CMainFrame::setRotate(int mRot)
{
    pViewFrame->rotate(mRot);
    m_iRotate = mRot;
}
void CMainFrame::OnMainFresh()
{
    if(RsMgr->g_filmBase)
    {
        RsMgr->g_filmBase->filmTask();
        RsMgr->g_filmBase->filmLed();
    }

    if(g_taskComKey)
        g_taskComKey->On_TaskComm();

    if(g_taskComCtrl)
        g_taskComCtrl->On_TaskComm();

    if(g_taskCan)
        g_taskCan->On_TaskCan();

    if(g_taskMonitor)
        g_taskMonitor->On_TaskMonitor();

}
void CMainFrame::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    //    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
    //    {
    //        internalTimer->start( 20 );
    //    }else if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    //    {
    //        internalTimer->start( 100 );
    //    }

    //because the key scan is done by mcu,so slow the control speed.
    internalTimer->start( 100 );

}
void CMainFrame::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}

void CMainFrame::setSceneWidget(QWidget * pWidgetNew)
{
    int mSceneIdx = -1;

    for(int mIdx = 0 ; mIdx < m_iSceneCount ; mIdx++)
    {
        if(pSceneWidget[mIdx] == pWidgetNew)
        {
            mSceneIdx = mIdx;
        }
    }

    if(mSceneIdx == -1)
    {
        pSceneWidget[m_iSceneCount] = pWidgetNew;
        pSceneFrame[m_iSceneCount] = new QGraphicsScene(this);
        pSceneFrame[m_iSceneCount]->addWidget(pWidgetNew);
        pViewFrame->setScene(pSceneFrame[m_iSceneCount]);
        pWidgetNew->raise();
        pWidgetNew->show();
        m_iSceneCount++;
    }else
    {
        pViewFrame->setScene(pSceneFrame[mSceneIdx]);
        pWidgetNew->raise();
        pWidgetNew->show();
    }
}
