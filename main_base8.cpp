#include "main_base8.h"
#include "resource_manager.h"

CMainBase8::CMainBase8(QWidget *parent) :
    CMainBase(parent)
{

    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT//VIEW_DIR_R180
    m_iViewDir      = VIEW_DIR_NORMAL;

    myViewInit();               //视图对象初始化
    mySceneInit();              //场景初始化

    QPalette pal = palette();   //设置背景色
    pal.setColor(QPalette::Background, QColor(208,235,245));
    setPalette(pal);

    if(lbCompletionTips)
    {
        lbCompletionTips->setGeometry(0,0,240,50);
        lbCompletionTips->move(100,510);
        if(g_dbsys.operationx.keyInstalled == 1)
            lbCompletionTips->setVisible(false);
    }
}

//隐藏弹出框
void CMainBase8::OnPopupHide(QWidget *pop)
{
    if(!isVisible())
        return;

    if(pop)
        pop->hide();

    viewPopup->hide();
}
//显示弹出框
void CMainBase8::OnPopupShow(int popIdx)
{
    QWidget * pWidget;

    if(!isVisible())
        return;

    switch(popIdx)
    {
    case SYS_POPUP_FOCUS:               //弹出焦点选择
        pWidget = RsMgr->g_genFocus;
        break;
    case SYS_POPUP_AEC:                 //弹出AEC选择
        pWidget = RsMgr->g_genAec;
        break;
    case SYS_POPUP_REQUEST:             //弹出网络链接请求
        pWidget = RsMgr->g_systemClient;
        break;
    case SYS_POPUP_PARAM:               //弹出发生器参数
        pWidget = RsMgr->g_genParamMgr;
        break;
    case SYS_POPUP_SMART:               //弹出快捷动作控制
        pWidget = RsMgr->g_smartBase;
        break;
    default:
        return;
    }

    viewPopup->setScene(pSceneArray[popIdx]);
    viewPopup->setGeometry(PopInfoPos[popIdx][m_iViewDir]);

    pWidget->show();
    viewPopup->raise();
    viewPopup->show();

}
void CMainBase8::myViewInit()
{
    CMainBase::myViewInit();

    //主界面菜单
    viewMenu = new QGraphicsView(this);
    viewMenu->setObjectName(QString::fromUtf8("viewMenu"));
    viewMenu->setGeometry(PopInfoPos[SYS_POPUP_MENU][m_iViewDir]);
    viewMenu->setFocusPolicy(Qt::NoFocus);
    viewMenu->setFrameShape(QFrame::NoFrame);
    viewMenu->setFrameShadow(QFrame::Plain);
    viewMenu->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewMenu->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewMenu->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
    viewMenu->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //标题栏
    viewTitle   = new QGraphicsView(this);
    viewTitle->setObjectName(QString::fromUtf8("viewTitle"));
    viewTitle->setGeometry(PopInfoPos[SYS_POPUP_TITLE][m_iViewDir]);
    viewTitle->setFocusPolicy(Qt::NoFocus);
    viewTitle->setFrameShape(QFrame::NoFrame);
    viewTitle->setFrameShadow(QFrame::Plain);
    viewTitle->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewTitle->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewTitle->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
    viewTitle->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    viewTitle->setStyleSheet("background: transparent");

    //液晶按键
    viewKey = new QGraphicsView(this);
    viewKey->setObjectName(QString::fromUtf8("viewKey"));
    viewKey->setGeometry(PopInfoPos[SYS_POPUP_KEY][m_iViewDir]);
    viewKey->setFocusPolicy(Qt::NoFocus);
    viewKey->setFrameShape(QFrame::NoFrame);
    viewKey->setFrameShadow(QFrame::Plain);
    viewKey->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewKey->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewKey->setAlignment( Qt::AlignLeft | Qt::AlignTop);
    viewKey->setStyleSheet("background:transparent");

    viewStatus->raise();
    viewInfo->raise();

}
void CMainBase8::mySceneInit()
{

    CMainBase::mySceneInit();

    //菜单视图
    pSceneArray[SYS_POPUP_MENU] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_MENU]->addWidget(RsMgr->g_menuBase);

    //标题视图
    pSceneArray[SYS_POPUP_TITLE] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_TITLE]->addWidget(RsMgr->g_titleBase);

    //液晶屏按钮
    pSceneArray[SYS_POPUP_KEY] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_KEY]->addWidget(RsMgr->g_keyBase);

    //液晶屏按钮
    pSceneArray[SYS_POPUP_FAST] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_FAST]->addWidget(RsMgr->g_fastBase);

    viewMenu->setScene(pSceneArray[SYS_POPUP_MENU]);
    viewTitle->setScene(pSceneArray[SYS_POPUP_TITLE]);
    viewInfo->setScene(pSceneArray[SYS_POPUP_INFO]);
    viewStatus->setScene(pSceneArray[SYS_POPUP_STATUS]);
    viewKey->setScene(pSceneArray[SYS_POPUP_KEY]);
    viewFast->setScene(pSceneArray[SYS_POPUP_FAST]);
}

void CMainBase8::showEvent(QShowEvent *event)
{
    //是否显示快捷按钮
    if(g_dbsys.utility.mSmartShow)
    {
        RsMgr->g_fastBase->show();
        RsMgr->g_fastBase->raise();
    }else
    {
        RsMgr->g_fastBase->hide();
        RsMgr->g_fastBase->disconnect();
    }

    //显示菜单
    RsMgr->g_techBase->setParent(RsMgr->g_menuBase);
    RsMgr->g_techBase->raise();

    //显示快捷按钮
    RsMgr->g_quickBase->setParent(RsMgr->g_menuBase);
    RsMgr->g_quickBase->raise();
    RsMgr->g_quickBase->show();

    //显示标题栏
    RsMgr->g_simBase->setParent(RsMgr->g_titleBase);
    RsMgr->g_simBase->move(SYS_WID(400),SYS_HEI(0));

    //显示关机按钮
    RsMgr->g_exitBase->setParent(RsMgr->g_titleBase);
    RsMgr->g_exitBase->move(SYS_WID(500),SYS_HEI(0));

    RsMgr->g_curtainBase->setParent(RsMgr->g_titleBase);
    RsMgr->g_curtainBase->move(SYS_WID(200),SYS_HEI(0));

    //判断显示网络链接
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(g_netBase)
        {
            g_netBase->setParent(RsMgr->g_titleBase);
            g_netBase->move(SYS_WID(300),SYS_HEI(0));

            if(g_dbsys.utility.mNetShow)
                g_netBase->setVisible(true);
        }
    }else if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
    {
        if(g_netBase)
        {
            g_netBase->setParent(RsMgr->g_titleBase);
            g_netBase->move(SYS_WID(300),SYS_HEI(0));

            if(g_dbsys.utility.mNetShow)
                g_netBase->setVisible(true);
        }
    }

    CMainBase::showEvent(event);
}
void CMainBase8::hideEvent(QHideEvent *event)
{

    CMainBase::hideEvent(event);
}
//显示视角切换
void CMainBase8::OnViewDirChange(int viewPoint)
{
    m_iViewDir = viewPoint;

    if((viewPoint < 0 ) || (viewPoint >= VIEW_DIR_MAX))
        return;

    int iRotateDegree = m_iViewSwitch[m_iViewDirBuf][viewPoint];

    //旋转标题栏
    viewTitle->rotate(iRotateDegree);
    viewTitle->setGeometry(PopInfoPos[SYS_POPUP_TITLE][m_iViewDir]);

    //旋转发生器界面
    viewGen->rotate(iRotateDegree);
    viewGen->setGeometry(PopInfoPos[SYS_POPUP_GEN][m_iViewDir]);

    //根据安装位置，切换动画显示界面
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        viewMotion->rotate(iRotateDegree * -1.0f);
        viewMotion->setGeometry(PopInfoPos[SYS_POPUP_MOTION][m_iViewDir]);
    }else
    {
        viewMotion->rotate(iRotateDegree);
        viewMotion->setGeometry(PopInfoPos[SYS_POPUP_MOTION][m_iViewDir]);
    }

    //旋转快捷显示区域
    viewFast->rotate(iRotateDegree);
    viewFast->setGeometry(PopInfoPos[SYS_POPUP_FAST][m_iViewDir]);

    //旋转主界面菜单
    viewMenu->rotate(iRotateDegree);
    viewMenu->setGeometry(PopInfoPos[SYS_POPUP_MENU][m_iViewDir]);

    //旋转主界面消息提示
    viewInfo->rotate(iRotateDegree);
    viewInfo->setGeometry(PopInfoPos[SYS_POPUP_INFO][m_iViewDir]);

    //旋转主界面状态栏
    int mWidth,mHeight;
    mWidth = PopInfoPos[SYS_POPUP_STATUS][m_iViewDir].width();
    mHeight = PopInfoPos[SYS_POPUP_STATUS][m_iViewDir].height();
    viewStatus->rotate(iRotateDegree);
    viewStatus->setGeometry(PopInfoPos[SYS_POPUP_STATUS][m_iViewDir]);
    pSceneArray[SYS_POPUP_STATUS]->setSceneRect(0,0,mWidth,mHeight);

    //旋转按键界面
    viewKey->rotate(iRotateDegree);
    viewKey->setGeometry(PopInfoPos[SYS_POPUP_KEY][m_iViewDir]);

    //旋转弹出框
    viewPopup->hide();
    viewPopup->rotate(iRotateDegree);

    m_iViewDirBuf = viewPoint;
}

void CMainBase8::OnViewChange(int view)
{

    switch(view)
    {
    case VIEW_GEN_CFG:                                  //发生器参数配置模式
        m_iViewDirBuf = m_iViewDir;                     //记录当前视角
        hide();                                         //隐藏自身
        viewGen->setParent(RsMgr->g_genConfig);      //将viewGen的父亲设置为g_systemGenCfg
        viewPopup->setParent(RsMgr->g_genConfig);    //将viewPopup的父亲设置为g_systemGenCfg

        RsMgr->g_genConfig->viewPopup = viewPopup;   //初始化g_systemGenCfg
        RsMgr->g_genConfig->viewGen = viewGen;
        RsMgr->g_genConfig->pSceneArray[SYS_POPUP_PARAM_CFG] = pSceneArray[SYS_POPUP_PARAM];
        RsMgr->g_genConfig->pSceneArray[SYS_POPUP_AEC_CFG] = pSceneArray[SYS_POPUP_AEC];
        RsMgr->g_genConfig->pSceneArray[SYS_POPUP_FOCUS_CFG] = pSceneArray[SYS_POPUP_FOCUS];

        emit ViewChange(VIEW_GEN_CFG);      //切换到发生器参数设置页面
        break;
    case VIEW_PASSWORD:                     //密码界面模式
        viewMotion->hide();                 //隐藏动画界面
        viewStatus->hide();                 //隐藏状态栏界面
        viewGen->hide();                    //隐藏发生器界面
        viewPopup->hide();                  //隐藏弹出框界面
        viewInfo->hide();                   //隐藏消息框界面

        emit ViewChange(VIEW_PASSWORD);
        break;
    case VIEW_CONFIRM:                      //密码到期模式
        viewMotion->hide();                 //隐藏动画界面
        viewInfo->hide();                   //隐藏消息框界面
        viewGen->hide();                    //隐藏发生器界面
        viewPopup->hide();                  //隐藏弹出框界面

        emit ViewChange(VIEW_CONFIRM);
        break;
    case VIEW_INSTALL:                      //密码到期模式
        viewMotion->hide();                 //隐藏动画界面
        viewInfo->hide();                   //隐藏消息框界面
        viewGen->hide();                    //隐藏发生器界面
        viewPopup->hide();                  //隐藏弹出框界面

        emit ViewChange(VIEW_INSTALL);
        break;
    case VIEW_GEN:                          //发生器显示模式
        RsMgr->g_techBase->show();
        RsMgr->g_quickBase->hide();
        viewFast->hide();
        viewMotion->hide();                 //隐藏动画界面
        viewStatus->show();                 //显示状态栏界面
        viewGen->show();                    //显示发生器界面
        viewPopup->hide();                  //隐藏弹出框界面
        m_iViewer = VIEW_GEN;

        emit ViewChange(VIEW_GEN);
        break;
    case VIEW_MOTION:                       //动画显示模式
        RsMgr->g_techBase->hide();
        RsMgr->g_quickBase->show();
        viewFast->show();
        viewMotion->show();                 //显示动画界面
        viewStatus->show();                 //显示状态栏界面
        viewGen->hide();                    //隐藏发生器界面
        viewPopup->hide();                  //隐藏弹出框界面
        m_iViewer = VIEW_MOTION;
        emit ViewChange(VIEW_MOTION);
        break;
    case VIEW_MAIN:                         //主界面显示模式
        m_iViewDir =   m_iViewDirBuf;
        viewStatus->show();                 //显示状态栏
        viewInfo->show();                   //显示信息栏
        viewGen->setParent(this);           //设置viewGen父亲
        viewGen->resetMatrix();             //重置viewGen显示方向
        viewGen->setGeometry(PopInfoPos[SYS_POPUP_GEN][m_iViewDir]);
        viewGen->rotate(m_iViewSwitch[VIEW_DIR_R180][m_iViewDir]);

        viewPopup->setParent(this);
        viewPopup->resetMatrix();
        viewPopup->rotate(m_iViewSwitch[VIEW_DIR_R180][m_iViewDir]);

        if(m_iViewer == VIEW_MOTION)
        {
            viewMotion->show();
            viewGen->hide();
        }
        if(m_iViewer == VIEW_GEN)
        {
            viewGen->show();
            viewMotion->hide();
        }
        g_mainFrame->setRotate(0);
        g_mainFrame->setSceneWidget(this);
        g_mainSetting->hide();
        RsMgr->g_menuBase->show();

        emit ViewChange(VIEW_MAIN);

        break;
    default:
        break;
    }
}
void CMainBase8::myPopupPosInit()
{

    //角度切换数据初始化
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_NORMAL]= 0;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_LEFT]  = -90;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_RIGHT] = 90;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_R180]  = 0;

    m_iViewSwitch[VIEW_DIR_LEFT][VIEW_DIR_NORMAL]= 90;
    m_iViewSwitch[VIEW_DIR_LEFT][VIEW_DIR_LEFT]  = 0;
    m_iViewSwitch[VIEW_DIR_LEFT][VIEW_DIR_RIGHT] = 0;
    m_iViewSwitch[VIEW_DIR_LEFT][VIEW_DIR_R180]  = 0;

    m_iViewSwitch[VIEW_DIR_RIGHT][VIEW_DIR_NORMAL]= -90;
    m_iViewSwitch[VIEW_DIR_RIGHT][VIEW_DIR_LEFT]  = -180;
    m_iViewSwitch[VIEW_DIR_RIGHT][VIEW_DIR_RIGHT] = 0;
    m_iViewSwitch[VIEW_DIR_RIGHT][VIEW_DIR_R180]  = 0;

    m_iViewSwitch[VIEW_DIR_R180][VIEW_DIR_NORMAL]= 0;
    m_iViewSwitch[VIEW_DIR_R180][VIEW_DIR_LEFT]  = -90;
    m_iViewSwitch[VIEW_DIR_R180][VIEW_DIR_RIGHT] = 0;
    m_iViewSwitch[VIEW_DIR_R180][VIEW_DIR_R180]  = 0;

    //控制位置数据初始化
    PopInfoPos[SYS_POPUP_MENU][VIEW_DIR_R180]     = QRect(SYS_WID(500),SYS_HEI(400),SYS_WID(300),SYS_HEI(200));
    PopInfoPos[SYS_POPUP_MENU][VIEW_DIR_NORMAL]   = QRect(SYS_WID(500),SYS_HEI(400),SYS_WID(300),SYS_HEI(200));
    PopInfoPos[SYS_POPUP_MENU][VIEW_DIR_LEFT]     = QRect(SYS_WID(600),SYS_HEI(0),SYS_WID(200),SYS_HEI(300));
    PopInfoPos[SYS_POPUP_MENU][VIEW_DIR_RIGHT]    = QRect(SYS_WID(0),SYS_HEI(300),SYS_WID(200),SYS_HEI(300));

    PopInfoPos[SYS_POPUP_TITLE][VIEW_DIR_R180]    = QRect(SYS_WID(0),SYS_HEI(0),SYS_WID(800),SYS_HEI(50));
    PopInfoPos[SYS_POPUP_TITLE][VIEW_DIR_NORMAL]  = QRect(SYS_WID(0),SYS_HEI(0),SYS_WID(800),SYS_HEI(50));
    PopInfoPos[SYS_POPUP_TITLE][VIEW_DIR_LEFT]    = QRect(SYS_WID(0),SYS_HEI(0),SYS_WID(50),SYS_HEI(600));
    PopInfoPos[SYS_POPUP_TITLE][VIEW_DIR_RIGHT]   = QRect(SYS_WID(750),SYS_HEI(0),SYS_WID(50),SYS_HEI(600));

    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_R180]   = QRect(SYS_WID(0),SYS_HEI(90),SYS_WID(450),SYS_HEI(450));
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_NORMAL] = QRect(SYS_WID(0),SYS_HEI(75),SYS_WID(450),SYS_HEI(450));
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_LEFT]   = QRect(SYS_WID(100),SYS_HEI(150),SYS_WID(450),SYS_HEI(450));
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_RIGHT]  = QRect(SYS_WID(250),SYS_HEI(0),SYS_WID(450),SYS_HEI(450));

    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_R180]      = QRect(SYS_WID(0),SYS_HEI(75),SYS_WID(450),SYS_HEI(450));
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_NORMAL]    = QRect(SYS_WID(0),SYS_HEI(75),SYS_WID(450),SYS_HEI(450));
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_LEFT]      = QRect(SYS_WID(100),SYS_HEI(150),SYS_WID(450),SYS_HEI(450));
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_RIGHT]     = QRect(SYS_WID(250),SYS_HEI(0),SYS_WID(450),SYS_HEI(450));

    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_R180]     = QRect(SYS_WID(110),SYS_HEI(225),SYS_WID(380),SYS_HEI(330));
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_NORMAL]   = QRect(SYS_WID(0),SYS_HEI(550),SYS_WID(500),SYS_HEI(50));
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_LEFT]     = QRect(SYS_WID(750),SYS_HEI(300),SYS_WID(50),SYS_HEI(300));
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_RIGHT]    = QRect(SYS_WID(0),SYS_HEI(0),SYS_WID(50),SYS_HEI(300));

    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_R180]    = QRect(SYS_WID(80),SYS_HEI(20),SYS_WID(310),SYS_HEI(600));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_NORMAL]  = QRect(SYS_WID(15),SYS_HEI(20),SYS_WID(310),SYS_HEI(600));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_LEFT]    = QRect(SYS_WID(55),SYS_HEI(280),SYS_WID(600),SYS_HEI(310));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_RIGHT]   = QRect(SYS_WID(200),SYS_HEI(15),SYS_WID(600),SYS_HEI(310));

    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_R180]    = QRect(SYS_WID(125),SYS_HEI(225),SYS_WID(200),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_NORMAL]  = QRect(SYS_WID(120),SYS_HEI(200),SYS_WID(200),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_LEFT]    = QRect(SYS_WID(223),SYS_HEI(280),SYS_WID(100),SYS_HEI(200));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_RIGHT]   = QRect(SYS_WID(475),SYS_HEI(120),SYS_WID(100),SYS_HEI(200));

    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_R180]      = QRect(SYS_WID(25),SYS_HEI(150),SYS_WID(300),SYS_HEI(280));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_NORMAL]    = QRect(SYS_WID(20),SYS_HEI(150),SYS_WID(300),SYS_HEI(280));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_LEFT]      = QRect(SYS_WID(180),SYS_HEI(280),SYS_WID(280),SYS_HEI(300));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_RIGHT]     = QRect(SYS_WID(335),SYS_HEI(20),SYS_WID(280),SYS_HEI(300));

    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_R180]  = QRect(SYS_WID(120),SYS_HEI(190),SYS_WID(360),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_NORMAL]= QRect(SYS_WID(120),SYS_HEI(190),SYS_WID(360),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_LEFT]  = QRect(SYS_WID(190),SYS_HEI(158),SYS_WID(360),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_RIGHT] = QRect(SYS_WID(190),SYS_HEI(158),SYS_WID(360),SYS_HEI(360));

    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_R180]    = QRect(SYS_WID(60),SYS_HEI(180),SYS_WID(380),SYS_HEI(330));
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_NORMAL]  = QRect(SYS_WID(60),SYS_HEI(180),SYS_WID(380),SYS_HEI(330));
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_LEFT]    = QRect(SYS_WID(200),SYS_HEI(160),SYS_WID(330),SYS_HEI(380));
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_RIGHT]   = QRect(SYS_WID(270),SYS_HEI(60),SYS_WID(330),SYS_HEI(380));

}

