#include "main_base12.h"
#include "resource_manager.h"

CMainBase12::CMainBase12(QWidget *parent) :
    CMainBase(parent)
{

    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT//VIEW_DIR_R180
    m_iViewDir      = VIEW_DIR_NORMAL;
    m_iViewDirBuf   = VIEW_DIR_R180;        //初始化显示角度
    myViewInit();               //视图对象初始化
    mySceneInit();              //场景初始化

    frameBack = new QFrame(this);
    frameBack->setGeometry(0,0,g_sysWidth,g_sysHeight);
    frameBack->setStyleSheet("QFrame{ border-image: url(:/QRes/8010/png00/background-v.png);}");
    frameBack->lower();
}

//隐藏弹出框
void CMainBase12::OnPopupHide(QWidget *pop)
{
    if(!isVisible())
        return;

    if(pop)
        pop->hide();

    viewPopup->hide();

    if(pop == RsMgr->g_smartBase)           //如果是SmartBase隐藏掉了，显示动画区域
        viewMotion->setVisible(true);       //显示动画区域

}
//显示弹出框
void CMainBase12::OnPopupShow(int popIdx)
{
    QWidget * pWidget = NULL;

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
        viewMotion->setVisible(false);      //隐藏动画区域
        break;
    case SYS_POPUP_SMART_HIDE:
        viewPopup->hide();
        viewMotion->setVisible(true);       //显示动画区域
        return;                             //此处必须返回
    case SYS_POPUP_SIM_HIDE:
        g_systemDb->g_bMotionSimulate = false;
        viewSim->setVisible(false);
        return;                             //此处必须返回
    default:
        return;
    }

    viewPopup->setScene(pSceneArray[popIdx]);
    viewPopup->setGeometry(PopInfoPos[popIdx][m_iViewDir]);

    if(pWidget)
        pWidget->show();

    viewPopup->raise();
    viewPopup->show();

}
void CMainBase12::myViewInit()
{
    CMainBase::myViewInit();

    //消除发生器人体模型的背景色
    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        g_GenMain->setStyleSheet("background:transparent");
    }else
    {
        //设置背景色
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(208,100,245));
        g_GenMain->setPalette(pal);
    }

    //viewMotion->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //viewMotion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //viewTech->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //viewTech->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //viewStatus->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //viewStatus->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    viewStatus->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewInfo->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewTech->setResizeAnchor( QGraphicsView::AnchorViewCenter);

    //主界面菜单
    viewMenu = new QGraphicsView(this);
    viewMenu->setObjectName(QString::fromUtf8("viewMenu"));
    viewMenu->setGeometry(PopInfoPos[SYS_POPUP_MENU][m_iViewDir]);
    viewMenu->setFocusPolicy(Qt::NoFocus);
    viewMenu->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewMenu->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewMenu->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewMenu->setAlignment( Qt::AlignLeft | Qt::AlignTop);
    viewMenu->setStyleSheet("background:transparent");

    //标题栏
    viewTitle   = new QGraphicsView(this);
    viewTitle->setObjectName(QString::fromUtf8("viewTitle"));
    viewTitle->setGeometry(PopInfoPos[SYS_POPUP_TITLE][m_iViewDir]);
    viewTitle->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewTitle->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewTitle->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewTitle->setStyleSheet("background: transparent");

    //液晶按键
    viewKey = new QGraphicsView(this);
    viewKey->setObjectName(QString::fromUtf8("viewKey"));
    viewKey->setGeometry(PopInfoPos[SYS_POPUP_KEY][m_iViewDir]);
    viewKey->setFocusPolicy(Qt::NoFocus);
    viewKey->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewKey->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewKey->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewKey->setAlignment( Qt::AlignLeft | Qt::AlignTop);
    viewKey->setStyleSheet("background:transparent");

    viewQuick = new QGraphicsView(this);
    viewQuick->setObjectName(QString::fromUtf8("viewQuick"));
    viewQuick->setGeometry(PopInfoPos[SYS_POPUP_QUICK][m_iViewDir]);
    viewQuick->setFocusPolicy(Qt::NoFocus);
    viewQuick->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewQuick->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewQuick->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewQuick->setAlignment( Qt::AlignLeft | Qt::AlignTop);
    viewQuick->setStyleSheet("background:transparent");

    viewNet = new QGraphicsView(this);
    viewNet->setObjectName(QString::fromUtf8("viewNet"));
    viewNet->setGeometry(PopInfoPos[SYS_POPUP_NET][m_iViewDir]);
    viewNet->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewNet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewNet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewNet->setStyleSheet("background:transparent");

    viewPower = new QGraphicsView(this);
    viewPower->setObjectName(QString::fromUtf8("viewPower"));
    viewPower->setGeometry(PopInfoPos[SYS_POPUP_POWER][m_iViewDir]);
    viewPower->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewPower->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewPower->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewPower->setStyleSheet("background:transparent");

    viewSim = new QGraphicsView(this);
    viewSim->setObjectName(QString::fromUtf8("viewSim"));
    viewSim->setGeometry(PopInfoPos[SYS_POPUP_SIM][m_iViewDir]);
    viewSim->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewSim->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewSim->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
        viewSim->setStyleSheet("background:transparent");
    else
        viewSim->setStyleSheet("background-color:yellow");
    viewSim->setVisible(false);

    viewCurtain = new QGraphicsView(this);
    viewCurtain->setObjectName(QString::fromUtf8("viewCurtain"));
    viewCurtain->setGeometry(PopInfoPos[SYS_POPUP_CURTAIN][m_iViewDir]);
    viewCurtain->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewCurtain->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewCurtain->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewCurtain->setStyleSheet("background:transparent");
    viewCurtain->setVisible(false);

    viewNotify = new QGraphicsView(this);
    viewNotify->setObjectName(QString::fromUtf8("viewNotify"));
    viewNotify->setGeometry(PopInfoPos[SYS_POPUP_NOTIFY][m_iViewDir]);
    viewNotify->setResizeAnchor( QGraphicsView::AnchorViewCenter);
    viewNotify->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewNotify->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
        viewNotify->setStyleSheet("background:transparent");
    else
        viewNotify->setStyleSheet("background-color:cyan");

    viewStatus->setStyleSheet("background: transparent");
    viewStatus->raise();
    viewInfo->raise();
    //viewInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //viewInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //viewInfo->setStyleSheet("background-color:black");
    //viewInfo->setVisible(false);        //关闭info显示
    //viewTitle->setVisible(false);       //关闭Title显示
    viewMotion->setStyleSheet("background: transparent");
    viewGen->setStyleSheet("background: transparent");
    viewTech->setStyleSheet("background: transparent");
}
void CMainBase12::mySceneInit()
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
    pSceneArray[SYS_POPUP_QUICK] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_QUICK]->addWidget(RsMgr->g_quickBase);

    //液晶屏按钮
    pSceneArray[SYS_POPUP_FAST] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_FAST]->addWidget(RsMgr->g_fastBase);

    //液晶屏按钮
    pSceneArray[SYS_POPUP_NET] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_NET]->addWidget(g_netBase);

    //液晶屏按钮
    pSceneArray[SYS_POPUP_POWER] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_POWER]->addWidget(RsMgr->g_exitBase);

    //运动模拟模块
    pSceneArray[SYS_POPUP_SIM] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_SIM]->addWidget(RsMgr->g_simBase);

    //光幕控制模块
    pSceneArray[SYS_POPUP_CURTAIN] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_CURTAIN]->addWidget(RsMgr->g_curtainBase);

    //光幕控制模块
    pSceneArray[SYS_POPUP_TECH] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_TECH]->addWidget(RsMgr->g_techBase);

    //光幕控制模块
    lbCompletionTips->setParent(NULL);
    lbCompletionTips->setGeometry(0,0,240,50);
    pSceneArray[SYS_POPUP_NOTIFY] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_NOTIFY]->addWidget(lbCompletionTips);


    viewMenu->setScene(pSceneArray[SYS_POPUP_MENU]);
    viewTitle->setScene(pSceneArray[SYS_POPUP_TITLE]);
    viewInfo->setScene(pSceneArray[SYS_POPUP_INFO]);
    viewStatus->setScene(pSceneArray[SYS_POPUP_STATUS]);
    viewKey->setScene(pSceneArray[SYS_POPUP_KEY]);
    viewFast->setScene(pSceneArray[SYS_POPUP_FAST]);
    viewQuick->setScene(pSceneArray[SYS_POPUP_QUICK]);
    viewNet->setScene(pSceneArray[SYS_POPUP_NET]);
    viewPower->setScene(pSceneArray[SYS_POPUP_POWER]);
    viewSim->setScene(pSceneArray[SYS_POPUP_SIM]);
    viewCurtain->setScene(pSceneArray[SYS_POPUP_CURTAIN]);
    viewTech->setScene(pSceneArray[SYS_POPUP_TECH]);
    viewNotify->setScene(pSceneArray[SYS_POPUP_NOTIFY]);
}

void CMainBase12::showEvent(QShowEvent *event)
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

    //基础菜单
    RsMgr->g_menuBase->raise();
    RsMgr->g_menuBase->show();

    RsMgr->g_techBase->show();

    //显示快捷按钮
    RsMgr->g_quickBase->raise();
    RsMgr->g_quickBase->show();

    //显示标题栏
    if(g_dbsys.utility.mSimulate == FUNC_SIMULATE_ON)
    {
        viewSim->setVisible(true);
        RsMgr->g_simBase->raise();
        RsMgr->g_simBase->show();
    }

    //光幕开关
    if(g_mainCfg->value("utility/LightCurtainShow","0").toInt())
        viewCurtain->setVisible(true);

    //判断显示网络链接
    if(g_netBase)
    {
        if(g_dbsys.utility.mNetShow)
            g_netBase->setVisible(true);
    }

    CMainBase::showEvent(event);


    if(g_dbsys.operationx.keyInstalled == 1)
    {
        viewNotify->setVisible(false);
    }else
    {
        viewNotify->raise();
        viewNotify->setVisible(true);
    }


}
void CMainBase12::hideEvent(QHideEvent *event)
{

    CMainBase::hideEvent(event);
}
//显示视角切换
void CMainBase12::OnViewDirChange(int viewPoint)
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
    viewStatus->rotate(iRotateDegree);
    viewStatus->setGeometry(PopInfoPos[SYS_POPUP_STATUS][m_iViewDir]);

    //旋转按键界面
    viewKey->rotate(iRotateDegree);
    viewKey->setGeometry(PopInfoPos[SYS_POPUP_KEY][m_iViewDir]);

    //旋转按键界面
    viewQuick->rotate(iRotateDegree);
    viewQuick->setGeometry(PopInfoPos[SYS_POPUP_QUICK][m_iViewDir]);

    //旋转按键界面
    viewNet->rotate(iRotateDegree);
    viewNet->setGeometry(PopInfoPos[SYS_POPUP_NET][m_iViewDir]);

    //旋转按键界面
    viewPower->rotate(iRotateDegree);
    viewPower->setGeometry(PopInfoPos[SYS_POPUP_POWER][m_iViewDir]);

    //旋转按键界面
    viewSim->rotate(iRotateDegree);
    viewSim->setGeometry(PopInfoPos[SYS_POPUP_SIM][m_iViewDir]);

    //旋转按键界面
    viewCurtain->rotate(iRotateDegree);
    viewCurtain->setGeometry(PopInfoPos[SYS_POPUP_CURTAIN][m_iViewDir]);

    //旋转按键界面
    viewTech->rotate(iRotateDegree);
    viewTech->setGeometry(PopInfoPos[SYS_POPUP_TECH][m_iViewDir]);

    //旋转按键界面
    viewNotify->rotate(iRotateDegree);
    viewNotify->setGeometry(PopInfoPos[SYS_POPUP_NOTIFY][m_iViewDir]);

    //旋转弹出框
    viewPopup->hide();
    viewPopup->rotate(iRotateDegree);

    m_iViewDirBuf = viewPoint;
}

void CMainBase12::OnViewChange(int view)
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
        viewTech->show();
        viewQuick->hide();
        viewMotion->hide();                 //隐藏动画界面
        viewStatus->show();                 //显示状态栏界面
        viewGen->show();                    //显示发生器界面
        viewPopup->hide();                  //隐藏弹出框界面
        m_iViewer = VIEW_GEN;

        emit ViewChange(VIEW_GEN);
        break;
    case VIEW_MOTION:                       //动画显示模式
        viewTech->hide();
        viewQuick->show();
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
void CMainBase12::myPopupPosInit()
{

    //角度切换数据初始化

    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_NORMAL]= 0;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_LEFT]  = -90;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_RIGHT] = 90;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_R180]  = 0;

    m_iViewSwitch[VIEW_DIR_LEFT][VIEW_DIR_NORMAL]= 90;
    m_iViewSwitch[VIEW_DIR_LEFT][VIEW_DIR_LEFT]  = 0;
    m_iViewSwitch[VIEW_DIR_LEFT][VIEW_DIR_RIGHT] = 180;
    m_iViewSwitch[VIEW_DIR_LEFT][VIEW_DIR_R180]  = 0;

    m_iViewSwitch[VIEW_DIR_RIGHT][VIEW_DIR_NORMAL]= -90;
    m_iViewSwitch[VIEW_DIR_RIGHT][VIEW_DIR_LEFT]  = 0;
    m_iViewSwitch[VIEW_DIR_RIGHT][VIEW_DIR_RIGHT] = 0;
    m_iViewSwitch[VIEW_DIR_RIGHT][VIEW_DIR_R180]  = 0;

    m_iViewSwitch[VIEW_DIR_R180][VIEW_DIR_NORMAL]= 90;
    m_iViewSwitch[VIEW_DIR_R180][VIEW_DIR_LEFT]  = 0;
    m_iViewSwitch[VIEW_DIR_R180][VIEW_DIR_RIGHT] = 180;
    m_iViewSwitch[VIEW_DIR_R180][VIEW_DIR_R180]  = 0;

    //立柱右侧安装时动画旋转角度初始化

    m_iDirRight[VIEW_DIR_NORMAL][VIEW_DIR_NORMAL]= 0;
    m_iDirRight[VIEW_DIR_NORMAL][VIEW_DIR_LEFT]  = 90;
    m_iDirRight[VIEW_DIR_NORMAL][VIEW_DIR_RIGHT] = -90;
    m_iDirRight[VIEW_DIR_NORMAL][VIEW_DIR_R180]  = 0;

    m_iDirRight[VIEW_DIR_LEFT][VIEW_DIR_NORMAL]= -90;
    m_iDirRight[VIEW_DIR_LEFT][VIEW_DIR_LEFT]  = 0;
    m_iDirRight[VIEW_DIR_LEFT][VIEW_DIR_RIGHT] = 180;
    m_iDirRight[VIEW_DIR_LEFT][VIEW_DIR_R180]  = 0;

    m_iDirRight[VIEW_DIR_RIGHT][VIEW_DIR_NORMAL]= 90;
    m_iDirRight[VIEW_DIR_RIGHT][VIEW_DIR_LEFT]  = 0;
    m_iDirRight[VIEW_DIR_RIGHT][VIEW_DIR_RIGHT] = 0;
    m_iDirRight[VIEW_DIR_RIGHT][VIEW_DIR_R180]  = 0;

    m_iDirRight[VIEW_DIR_R180][VIEW_DIR_NORMAL]= 90;
    m_iDirRight[VIEW_DIR_R180][VIEW_DIR_LEFT]  = 0;
    m_iDirRight[VIEW_DIR_R180][VIEW_DIR_RIGHT] = 180;
    m_iDirRight[VIEW_DIR_R180][VIEW_DIR_R180]  = 0;


    //控制位置数据初始化
    PopInfoPos[SYS_POPUP_MENU][VIEW_DIR_R180]     = QRect(SYS_WID(500),SYS_HEI(400),SYS_WID(300),SYS_HEI(200));
    PopInfoPos[SYS_POPUP_MENU][VIEW_DIR_NORMAL]   = QRect(SYS_WID(371),SYS_HEI(625),SYS_WID(230),SYS_HEI(111));   //竖屏,正屏
    PopInfoPos[SYS_POPUP_MENU][VIEW_DIR_LEFT]     = QRect(SYS_WID(666),SYS_HEI(668),SYS_WID(330),SYS_HEI(80));//向左转90度
    PopInfoPos[SYS_POPUP_MENU][VIEW_DIR_RIGHT]    = QRect(SYS_WID(28),SYS_HEI(20),SYS_WID(330),SYS_HEI(80));//向右转90度

    PopInfoPos[SYS_POPUP_TITLE][VIEW_DIR_R180]    = QRect(SYS_WID(0),SYS_HEI(0),SYS_WID(800),SYS_HEI(50));
    PopInfoPos[SYS_POPUP_TITLE][VIEW_DIR_NORMAL]  = QRect(SYS_WID(925),SYS_HEI(18),SYS_WID(80),SYS_HEI(208)); //竖屏,正屏
    PopInfoPos[SYS_POPUP_TITLE][VIEW_DIR_LEFT]    = QRect(SYS_WID(10),SYS_HEI(12),SYS_WID(235),SYS_HEI(90));//向左转90度
    PopInfoPos[SYS_POPUP_TITLE][VIEW_DIR_RIGHT]   = QRect(SYS_WID(779),SYS_HEI(666),SYS_WID(235),SYS_HEI(90));//向右90度

    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_R180]   = QRect(SYS_WID(0),SYS_HEI(90),SYS_WID(450),SYS_HEI(450));
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_NORMAL] = QRect(SYS_WID(460),SYS_HEI(50),SYS_WID(450),SYS_HEI(450)); //竖屏
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_LEFT]   = QRect(SYS_WID(50),SYS_HEI(114),SYS_WID(450),SYS_HEI(450));//向左90度
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_RIGHT]  = QRect(SYS_WID(524),SYS_HEI(204),SYS_WID(450),SYS_HEI(450));//向右90度

    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_R180]   = QRect(SYS_WID(0),SYS_HEI(90),SYS_WID(450),SYS_HEI(450));
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_NORMAL] = QRect(SYS_WID(450),SYS_HEI(50),SYS_WID(450),SYS_HEI(450)); //竖屏
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_LEFT]   = QRect(SYS_WID(50),SYS_HEI(105),SYS_WID(450),SYS_HEI(450));//向左90度
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_RIGHT]  = QRect(SYS_WID(524),SYS_HEI(213),SYS_WID(450),SYS_HEI(450));//向右90度

    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_R180]     = QRect(SYS_WID(110),SYS_HEI(225),SYS_WID(380),SYS_HEI(330));
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_NORMAL]   = QRect(SYS_WID(400),SYS_HEI(28),SYS_WID(72),SYS_HEI(500));//竖屏
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_LEFT]     = QRect(SYS_WID(28),SYS_HEI(550),SYS_WID(500),SYS_HEI(72));//向左90度
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_RIGHT]    = QRect(SYS_WID(496),SYS_HEI(146),SYS_WID(500),SYS_HEI(72));//向右90度

    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_R180]    = QRect(SYS_WID(80),SYS_HEI(20),SYS_WID(310),SYS_HEI(600));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_NORMAL]  = QRect(SYS_WID(350),SYS_HEI(60),SYS_WID(600),SYS_HEI(310));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_LEFT]    = QRect(SYS_WID(60),SYS_HEI(102),SYS_WID(310),SYS_HEI(600));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_RIGHT]   = QRect(SYS_WID(654),SYS_HEI(66),SYS_WID(310),SYS_HEI(600));

    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_R180]    = QRect(SYS_WID(125),SYS_HEI(225),SYS_WID(200),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_NORMAL]  = QRect(SYS_WID(675),SYS_HEI(165),SYS_WID(100),SYS_HEI(200));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_LEFT]    = QRect(SYS_WID(165),SYS_HEI(230),SYS_WID(200),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_RIGHT]   = QRect(SYS_WID(659),SYS_HEI(438),SYS_WID(200),SYS_HEI(100));

    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_R180]      = QRect(SYS_WID(25),SYS_HEI(150),SYS_WID(300),SYS_HEI(280));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_NORMAL]    = QRect(SYS_WID(583),SYS_HEI(65),SYS_WID(280),SYS_HEI(300));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_LEFT]      = QRect(SYS_WID(65),SYS_HEI(140),SYS_WID(300),SYS_HEI(280));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_RIGHT]     = QRect(SYS_WID(659),SYS_HEI(348),SYS_WID(300),SYS_HEI(280));

    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_R180]  = QRect(SYS_WID(120),SYS_HEI(190),SYS_WID(360),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_NORMAL]= QRect(SYS_WID(520),SYS_HEI(190),SYS_WID(360),SYS_HEI(360));//竖屏，主
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_LEFT]  = QRect(SYS_WID(290),SYS_HEI(258),SYS_WID(360),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_RIGHT] = QRect(SYS_WID(374),SYS_HEI(150),SYS_WID(360),SYS_HEI(360));

    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_R180]    = QRect(SYS_WID(60),SYS_HEI(180),SYS_WID(380),SYS_HEI(330));
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_NORMAL]  = QRect(SYS_WID(390),SYS_HEI(30),SYS_WID(505),SYS_HEI(525));//竖屏，主
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_LEFT]    = QRect(SYS_WID(22),SYS_HEI(105),SYS_WID(505),SYS_HEI(525));//向左90度
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_RIGHT]   = QRect(SYS_WID(497),SYS_HEI(138),SYS_WID(505),SYS_HEI(525));//向右90度

    PopInfoPos[SYS_POPUP_NET][VIEW_DIR_R180]    = QRect(SYS_WID(60),SYS_HEI(180),SYS_WID(100),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_NET][VIEW_DIR_NORMAL]  = QRect(SYS_WID(930),SYS_HEI(226),SYS_WID(72),SYS_HEI(90));//竖屏，主
    PopInfoPos[SYS_POPUP_NET][VIEW_DIR_LEFT]    = QRect(SYS_WID(236),SYS_HEI(20),SYS_WID(90),SYS_HEI(72));//向左90度
    PopInfoPos[SYS_POPUP_NET][VIEW_DIR_RIGHT]   = QRect(SYS_WID(698),SYS_HEI(676),SYS_WID(90),SYS_HEI(72));//向右90度

    PopInfoPos[SYS_POPUP_SIM][VIEW_DIR_R180]    = QRect(SYS_WID(60),SYS_HEI(180),SYS_WID(100),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_SIM][VIEW_DIR_NORMAL]  = QRect(SYS_WID(930),SYS_HEI(316),SYS_WID(72),SYS_HEI(90));//竖屏，主
    PopInfoPos[SYS_POPUP_SIM][VIEW_DIR_LEFT]    = QRect(SYS_WID(331),SYS_HEI(20),SYS_WID(90),SYS_HEI(72));//向左90度
    PopInfoPos[SYS_POPUP_SIM][VIEW_DIR_RIGHT]   = QRect(SYS_WID(603),SYS_HEI(676),SYS_WID(90),SYS_HEI(72));//向右90度

    PopInfoPos[SYS_POPUP_CURTAIN][VIEW_DIR_R180]    = QRect(SYS_WID(60),SYS_HEI(180),SYS_WID(100),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_CURTAIN][VIEW_DIR_NORMAL]  = QRect(SYS_WID(930),SYS_HEI(406),SYS_WID(72),SYS_HEI(90));//竖屏，主
    PopInfoPos[SYS_POPUP_CURTAIN][VIEW_DIR_LEFT]    = QRect(SYS_WID(426),SYS_HEI(20),SYS_WID(90),SYS_HEI(72));//向左90度
    PopInfoPos[SYS_POPUP_CURTAIN][VIEW_DIR_RIGHT]   = QRect(SYS_WID(508),SYS_HEI(676),SYS_WID(90),SYS_HEI(72));//向右90度

    PopInfoPos[SYS_POPUP_POWER][VIEW_DIR_R180]    = QRect(SYS_WID(60),SYS_HEI(180),SYS_WID(100),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_POWER][VIEW_DIR_NORMAL]  = QRect(SYS_WID(930),SYS_HEI(496),SYS_WID(72),SYS_HEI(90));//竖屏，主
    PopInfoPos[SYS_POPUP_POWER][VIEW_DIR_LEFT]    = QRect(SYS_WID(521),SYS_HEI(20),SYS_WID(90),SYS_HEI(72));//向左90度
    PopInfoPos[SYS_POPUP_POWER][VIEW_DIR_RIGHT]   = QRect(SYS_WID(413),SYS_HEI(676),SYS_WID(90),SYS_HEI(72));//向右90度

    PopInfoPos[SYS_POPUP_TECH][VIEW_DIR_R180]      = QRect(SYS_WID(635),SYS_HEI(90),SYS_WID(150),SYS_HEI(375));
    PopInfoPos[SYS_POPUP_TECH][VIEW_DIR_NORMAL]    = QRect(SYS_WID(609),SYS_HEI(623),SYS_WID(230),SYS_HEI(111));//竖屏，正屏
    PopInfoPos[SYS_POPUP_TECH][VIEW_DIR_LEFT]      = QRect(SYS_WID(666),SYS_HEI(590),SYS_WID(330),SYS_HEI(80));    //向左，90度
    PopInfoPos[SYS_POPUP_TECH][VIEW_DIR_RIGHT]     = QRect(SYS_WID(28),SYS_HEI(90),SYS_WID(330),SYS_HEI(80));//向右，90度

    PopInfoPos[SYS_POPUP_NOTIFY][VIEW_DIR_R180]      = QRect(SYS_WID(635),SYS_HEI(90),SYS_WID(150),SYS_HEI(375));
    PopInfoPos[SYS_POPUP_NOTIFY][VIEW_DIR_NORMAL]    = QRect(SYS_WID(850),SYS_HEI(200),SYS_WID(60),SYS_HEI(280));//竖屏，正屏
    PopInfoPos[SYS_POPUP_NOTIFY][VIEW_DIR_LEFT]      = QRect(SYS_WID(200),SYS_HEI(114),SYS_WID(280),SYS_HEI(60));    //向左，90度
    PopInfoPos[SYS_POPUP_NOTIFY][VIEW_DIR_RIGHT]     = QRect(SYS_WID(544),SYS_HEI(594),SYS_WID(280),SYS_HEI(60));//向右，90度

}

