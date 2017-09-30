#include "main_setting.h"
#include "resource_manager.h"

CMainSetting::CMainSetting(QWidget *parent) :
    QWidget(parent)
{

    setObjectName("CMainSetting");

    //resize(SYS_WID(800),SYS_HEI(600));
    resize(g_sysWidth,g_sysHeight);

    m_iCurrentAngle = -90;
    m_iViewerIdxLast = 0;
    m_iSceneCounter = 0;
    int mTemp;

    pb_left = new CButtonStable(this);
    //pb_left->setGeometry(SYS_WID(0), SYS_HEI(120), SYS_WID(80), SYS_HEI(100));
    mTemp = 3 * (g_sysHeight - 200) / 10 ;
    pb_left->setGeometry(SYS_WID(0), mTemp, SYS_WID(80), SYS_HEI(100));
    pb_left->setFocusPolicy(Qt::TabFocus);
    pb_left->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SCREEN_LEFT_01"));
    pb_left->setFlat(true);

    pb_right = new CButtonStable(this);
    //pb_right->setGeometry(SYS_WID(0), SYS_HEI(380), SYS_WID(80), SYS_HEI(100));
    mTemp = 7 * (g_sysHeight - 200) / 10 + 100;
    pb_right->setGeometry(SYS_WID(0), mTemp, SYS_WID(80), SYS_HEI(100));
    pb_right->setFocusPolicy(Qt::TabFocus);
    pb_right->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SCREEN_RIGHT_01"));
    pb_right->setFlat(true);

    lbState = new QLabel(this);
    lbState->setObjectName(QString::fromUtf8("lbState"));
    //lbState->setGeometry(SYS_WID(750), SYS_HEI(550), SYS_WID(50), SYS_HEI(50));
    lbState->setGeometry(g_sysWidth - 50, g_sysHeight - 50, SYS_WID(50), SYS_HEI(50));
    for(int mIdx = 0 ; mIdx < SETTING_SCENCE_MAX ; mIdx++)
    {
        mScene[mIdx]    = 0;
        mWidget[mIdx]   = 0;
    }

    gViewer = new QGraphicsView(this);
    gViewer->setObjectName(QString::fromUtf8("gViewer"));
    //gViewer->setGeometry(SYS_WID(100), 0, SYS_HEI(600), SYS_HEI(600));
    gViewer->setGeometry(SYS_WID(100), 0, g_sysHeight, g_sysHeight);
    gViewer->setFocusPolicy(Qt::NoFocus);
    gViewer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gViewer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gViewer->setFrameShape(QFrame::NoFrame);
    gViewer->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
    gViewer->raise();
    gViewer->scale(g_sysHeight/600.0f,g_sysHeight/600.0f);

    connect(pb_left,SIGNAL(pressed()),this,SLOT(turnPressed()) );
    connect(pb_right,SIGNAL(pressed()),this,SLOT(turnPressed()) );

    connect(pb_left,SIGNAL(released()),this,SLOT(turnReleased()) );
    connect(pb_right,SIGNAL(released()),this,SLOT(turnReleased()) );

    timerRefresh = new QTimer(this);
    timerRefresh->setInterval(TIME_DATA_FRESH);
    connect(timerRefresh,SIGNAL(timeout()),this,SLOT(OnDataRefresh()));

    this->setStyleSheet("background-color: black");

    setVisible(false);
}

void CMainSetting::OnViewChange(int view)
{
    switch(view)
    {
    case VIEW_GEN_CFG:
        setSceneWidget(RsMgr->g_genConfig);
        break;
    case VIEW_PASSWORD:
        setSceneWidget(RsMgr->g_systemPsw);
        break;
    case VIEW_CONFIRM:
        setSceneWidget(RsMgr->g_systemConfirm);
        break;
    case VIEW_INSTALL:
        setSceneWidget(RsMgr->g_systemInstall);
        break;
    default:
        break;
    }
}

void CMainSetting::turnPressed()
{

    if(sender() == pb_left)
    {

        pb_left->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SCREEN_LEFT_02"));

        m_iCurrentAngle -= 90;
        gViewer->rotate(-90);

    }else if(sender()  == pb_right)
    {

        pb_right->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SCREEN_RIGHT_02"));

        m_iCurrentAngle += 90;
        gViewer->rotate(90);
        m_iViewerIdxLast  = 2;
    }

    if(m_iCurrentAngle < 0)
        m_iCurrentAngle += 360;

    if(m_iCurrentAngle == 360)
        m_iCurrentAngle = 0;

    m_iViewerIdxLast = m_iCurrentAngle/90;

}

void CMainSetting::turnReleased()
{
    if(sender()  == pb_left)
    {
        pb_left->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SCREEN_LEFT_01"));
    }else if(sender()  == pb_right)
    {
        pb_right->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SCREEN_RIGHT_01"));
    }
}
void CMainSetting::setSceneWidget(QWidget * pWidgetNew)
{
    int mSceneIdx = -1;

    for(int mIdx = 0 ; mIdx < m_iSceneCounter ; mIdx++)
    {
        if(mWidget[mIdx]== pWidgetNew)
        {
            mSceneIdx = mIdx;
        }
    }

    if(mSceneIdx == -1)
    {
        mWidget[m_iSceneCounter] = pWidgetNew;
        mScene[m_iSceneCounter] = new QGraphicsScene(this);
        mScene[m_iSceneCounter]->addWidget(pWidgetNew);
        gViewer->setScene(mScene[m_iSceneCounter]);
        pWidgetNew->show();
        m_iSceneCounter++;
    }else
    {
        gViewer->setScene(mScene[mSceneIdx]);
        pWidgetNew->show();
    }

}

void CMainSetting::showEvent(QShowEvent *)
{

    unsigned short buf[10];
    buf[0]=0;
    buf[1]=SYS_CMD_SETTING;
    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);

    timerRefresh->start();

    RsMgr->VisibleWidgetAdd(this);
}

void CMainSetting::hideEvent(QHideEvent *)
{

    unsigned short buf[10];
    buf[0]=0;
    buf[1]=SYS_CMD_NORMAL;
    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);

    RsMgr->VisibleWidgetDel(this);

    timerRefresh->stop();
}

void CMainSetting::OnDataRefresh()
{

    if(g_systemDb->g_dbMachine.StateData[6] == SYS_STATUS_NORMAL)
    {
        lbState->setStyleSheet(g_skinBase->GetStyleMapStr("BASE_STR_NORMAL"));
    }

    if(g_systemDb->g_dbMachine.StateData[6] == SYS_STATUS_SETTING)
    {
        lbState->setStyleSheet(g_skinBase->GetStyleMapStr("BASE_STR_SETTING"));
    }

    if(g_systemDb->g_dbMachine.StateData[6] == SYS_STATUS_DEBUG)
    {
        lbState->setStyleSheet(g_skinBase->GetStyleMapStr("BASE_STR_DEBUG"));
    }

}


void CMainSetting::mousePressEvent(QMouseEvent *)
{
    qDebug()<<"CMainSetting::mousePressEvent";
}
