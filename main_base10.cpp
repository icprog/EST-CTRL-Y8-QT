#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTransform>
#include <QMessageBox>

#include "main_base10.h"
#include "sys_database.h"
#include "resource_manager.h"

CMainBase10::CMainBase10(QWidget *parent) :
    CMainBase(parent)
{

    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT//VIEW_DIR_R180
    m_iViewDir      = VIEW_DIR_NORMAL;      //默认显示角度
    m_iViewDirBuf   = VIEW_DIR_R180;        //初始化显示角度

    myPopupPosInit();           //初始化弹出框位置

    myViewInit();               //初始化视图
    mySceneInit();              //初始化场景

    OnViewDirChange(m_iViewDir);//切换到默认视角

    if(lbCompletionTips)
    {
        lbCompletionTips->move(560,105);
        if(g_dbsys.operationx.keyInstalled)     //already installed password
            lbCompletionTips->setVisible(false);
    }
}

void CMainBase10::showEvent(QShowEvent * event)
{
    //判断是否显示g_frameFastBase
    if(!g_dbsys.utility.mSmartShow)
    {
        RsMgr->g_fastBase->disconnect();
    }

    //设置部分控件的父亲与位置
    RsMgr->g_quickBase->setParent(RsMgr->g_mainBase);
    RsMgr->g_quickBase->move(SYS_WID(0),SYS_HEI(114));
    RsMgr->g_quickBase->setVisible(true);
    RsMgr->g_menuBase->setParent(RsMgr->g_mainBase);
    RsMgr->g_menuBase->move(SYS_WID(376),SYS_HEI(0));
    RsMgr->g_keyBase->setParent(RsMgr->g_mainBase);
    RsMgr->g_keyBase->move(SYS_WID(0),SYS_HEI(0));
    RsMgr->g_titleBase->setParent(RsMgr->g_mainBase);
    RsMgr->g_titleBase->move(SYS_WID(602),SYS_HEI(0));
    RsMgr->g_simBase->setParent(RsMgr->g_titleBase);
    RsMgr->g_simBase->move(SYS_WID(20),SYS_HEI(8));
    RsMgr->g_exitBase->setParent(RsMgr->g_titleBase);
    RsMgr->g_exitBase->move(SYS_WID(107),SYS_HEI(5));
    RsMgr->g_curtainBase->setParent(RsMgr->g_titleBase);
    RsMgr->g_curtainBase->move(SYS_WID(20),SYS_HEI(8));

    //设置g_tcpClient的父亲
    if(g_netBase)
    {
        g_netBase->setParent(RsMgr->g_titleBase);
        g_netBase->move(SYS_WID(0),SYS_HEI(510));
    }

    //先判断是否显示光幕按钮
    if(g_mainCfg->value("utility/LightCurtainShow","0").toInt() == 1)
    {

        RsMgr->g_curtainBase->setVisible(true);
        RsMgr->g_curtainBase->raise();

        //强制关闭温度显示
        RsMgr->g_simBase->setVisible(false);
    }

    CMainBase::showEvent(event);

}
void CMainBase10::hideEvent(QHideEvent * event)
{

    CMainBase::hideEvent(event);
}

void CMainBase10::OnViewChange(int view)
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
        viewMotion->hide();                 //隐藏动画界面
        viewStatus->show();                 //显示状态栏界面
        viewGen->show();                    //显示发生器界面
        viewPopup->hide();                  //隐藏弹出框界面
        m_iViewer = VIEW_GEN;

        emit ViewChange(VIEW_GEN);
        break;
    case VIEW_MOTION:                       //动画显示模式
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
void CMainBase10::OnViewDirChange(int viewPoint)
{

    if((viewPoint < 0 )|| (viewPoint >= VIEW_DIR_MAX))
        return;

    m_iViewDir = viewPoint;

    //获取旋转角度
    int iRotateDegree = m_iViewSwitch[m_iViewDirBuf][viewPoint];

    //旋转发生器页面
    viewGen->rotate(iRotateDegree);

    //判断安装位置，旋转动画区域
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        viewMotion->rotate(m_iDirRight[m_iViewDirBuf][viewPoint]);
    }else
    {
        viewMotion->rotate(iRotateDegree);
    }

    //旋转信息显示区域
    viewInfo->rotate(iRotateDegree);
    viewInfo->setGeometry(PopInfoPos[SYS_POPUP_INFO][m_iViewDir]);

    //旋转发生器技术显示区域
    viewTech->rotate(iRotateDegree);
    viewTech->setGeometry(PopInfoPos[SYS_POPUP_TECH][m_iViewDir]);

    //旋转快捷显示区域
    viewFast->rotate(iRotateDegree);
    viewFast->setGeometry(PopInfoPos[SYS_POPUP_FAST][m_iViewDir]);

    //旋转状态显示区域
    viewStatus->rotate(iRotateDegree);
    viewStatus->setGeometry(PopInfoPos[SYS_POPUP_STATUS][m_iViewDir]);

    //旋转弹出提示显示区域
    viewPopup->hide();
    viewPopup->rotate(iRotateDegree);

    m_iViewDirBuf = viewPoint;
}

void CMainBase10::OnPopupHide(QWidget *)
{
    if(!isVisible())
        return;

    viewPopup->hide();
}

void CMainBase10::OnPopupShow(int popIdx)
{
    QWidget * pWidget;

    if(!isVisible())
        return;

    switch(popIdx)
    {
    case SYS_POPUP_FOCUS:       //显示焦点选择
        pWidget = RsMgr->g_genFocus;
        break;
    case SYS_POPUP_AEC:         //显示AEC选择
        pWidget = RsMgr->g_genAec;
        break;
    case SYS_POPUP_REQUEST:     //显示网络链接
        pWidget = RsMgr->g_systemClient;
        break;
    case SYS_POPUP_PARAM:       //显示发生器参数
        pWidget = RsMgr->g_genParamMgr;
        break;
    case SYS_POPUP_SMART:       //显示快捷按钮
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
void CMainBase10::mySceneInit()
{

    CMainBase::mySceneInit();

    //快捷显示
    //pSceneArray[SYS_POPUP_FAST] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_FAST] = new QGraphicsScene();
    pSceneArray[SYS_POPUP_FAST]->addWidget(RsMgr->g_fastBase);

    //曝光技术
    pSceneArray[SYS_POPUP_TECH] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_TECH]->addWidget(RsMgr->g_techBase);

    //发生器控制页面
    viewGen->setScene(pSceneArray[SYS_POPUP_GEN]);
    viewGen->raise();
    viewGen->hide();

    //信息提示界面
    RsMgr->g_infoBase->show();
    viewInfo->setScene(pSceneArray[SYS_POPUP_INFO]);
    viewInfo->raise();
    viewInfo->show();

    //状态栏界面
    RsMgr->g_statusBase->show();
    viewStatus->setScene(pSceneArray[SYS_POPUP_STATUS]);
    viewStatus->raise();
    viewStatus->show();

    //快捷按钮
    //RsMgr->g_fastBase->setParent(this);
    RsMgr->g_fastBase->show();
    viewFast->setScene(pSceneArray[SYS_POPUP_FAST]);
    viewFast->raise();
    viewFast->show();

    //曝光技术界面
    RsMgr->g_techBase->show();
    viewTech->setScene(pSceneArray[SYS_POPUP_TECH]);
    viewTech->raise();
    viewTech->show();
}

void CMainBase10::myViewInit()
{                             

    CMainBase::myViewInit();

    //判断安装位置，镜像动画界面
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        QTransform Tmatrax;
        Tmatrax.setMatrix(1,0,0,0,-1,0,0,600,1);
        viewMotion->setTransform(Tmatrax);
    }

}
void CMainBase10::myPopupPosInit()
{

    //视角切换角度初始化
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

    //部分控件位置初始化
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_R180]    = QRect(SYS_WID(585),SYS_HEI(185),SYS_WID(100),SYS_HEI(200));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_NORMAL]  = QRect(SYS_WID(585),SYS_HEI(185),SYS_WID(100),SYS_HEI(200));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_LEFT]    = QRect(SYS_WID(470),SYS_HEI(200),SYS_WID(200),SYS_HEI(100));
    PopInfoPos[SYS_POPUP_FOCUS][VIEW_DIR_RIGHT]   = QRect(SYS_WID(490),SYS_HEI(300),SYS_WID(200),SYS_HEI(100));

    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_R180]      = QRect(SYS_WID(395),SYS_HEI(85),SYS_WID(280),SYS_HEI(300));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_NORMAL]    = QRect(SYS_WID(395),SYS_HEI(85),SYS_WID(280),SYS_HEI(300));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_LEFT]      = QRect(SYS_WID(370),SYS_HEI(178),SYS_WID(300),SYS_HEI(280));
    PopInfoPos[SYS_POPUP_AEC][VIEW_DIR_RIGHT]     = QRect(SYS_WID(490),SYS_HEI(120),SYS_WID(300),SYS_HEI(280));

    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_R180]     = QRect(SYS_WID(290),SYS_HEI(120),SYS_WID(220),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_NORMAL]   = QRect(SYS_WID(290),SYS_HEI(120),SYS_WID(220),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_LEFT]     = QRect(SYS_WID(190),SYS_HEI(158),SYS_WID(360),SYS_HEI(220));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_RIGHT]    = QRect(SYS_WID(190),SYS_HEI(158),SYS_WID(360),SYS_HEI(220));

    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_R180]    = QRect(SYS_WID(200),SYS_HEI(80),SYS_WID(600),SYS_HEI(310));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_NORMAL]  = QRect(SYS_WID(200),SYS_HEI(80),SYS_WID(600),SYS_HEI(310));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_LEFT]    = QRect(SYS_WID(370),SYS_HEI(20),SYS_WID(310),SYS_HEI(600));
    PopInfoPos[SYS_POPUP_PARAM][VIEW_DIR_RIGHT]   = QRect(SYS_WID(490),SYS_HEI(20),SYS_WID(310),SYS_HEI(600));

    //PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_R180]    = QRect(SYS_WID(110),SYS_HEI(110),SYS_WID(330),SYS_HEI(380));
    //PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_NORMAL]  = QRect(SYS_WID(110),SYS_HEI(110),SYS_WID(330),SYS_HEI(380));

    //PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_RIGHT]   = QRect(SYS_WID(115),SYS_HEI(135),SYS_WID(380),SYS_HEI(330));

    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_R180]    = QRect(SYS_HEI(110),SYS_WID(110),SYS_HEI(330),SYS_WID(380));
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_NORMAL]  = QRect(SYS_WID(110),SYS_HEI(110),SYS_WID(330),SYS_HEI(380));
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_LEFT]    = QRect(SYS_WID(135),SYS_HEI(135),SYS_WID(380),SYS_HEI(330));
    PopInfoPos[SYS_POPUP_SMART][VIEW_DIR_RIGHT]   = QRect(SYS_HEI(115),SYS_WID(135),SYS_HEI(380),SYS_WID(330));

    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_R180]      = QRect(SYS_WID(376), SYS_HEI(90), SYS_WID(424), SYS_HEI(420));
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_NORMAL]    = QRect(SYS_WID(376), SYS_HEI(90), SYS_WID(424), SYS_HEI(420));
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_LEFT]      = QRect(SYS_WID(376), SYS_HEI(90), SYS_WID(424), SYS_HEI(420));
    PopInfoPos[SYS_POPUP_GEN][VIEW_DIR_RIGHT]     = QRect(SYS_WID(376), SYS_HEI(90), SYS_WID(424), SYS_HEI(420));

    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_R180]   = QRect(SYS_WID(376), SYS_HEI(90), SYS_WID(424), SYS_HEI(420));
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_NORMAL] = QRect(SYS_WID(376), SYS_HEI(90), SYS_WID(424), SYS_HEI(420));
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_LEFT]   = QRect(SYS_WID(376), SYS_HEI(90), SYS_WID(424), SYS_HEI(420));
    PopInfoPos[SYS_POPUP_MOTION][VIEW_DIR_RIGHT]  = QRect(SYS_WID(376), SYS_HEI(90), SYS_WID(424), SYS_HEI(420));

    //在pad界面下，无法和其他控件对齐，目前没有找到原因
    //PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_R180]   = QRect(SYS_WID(80), SYS_HEI(156), SYS_WID(83), SYS_HEI(300));
    //PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_NORMAL] = QRect(SYS_WID(80), SYS_HEI(156), SYS_WID(83), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_R180]   = QRect(SYS_WID(80), SYS_HEI(150), SYS_WID(83), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_NORMAL] = QRect(SYS_WID(80), SYS_HEI(150), SYS_WID(83), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_LEFT]   = QRect(SYS_WID(76), SYS_HEI(363), SYS_WID(300), SYS_HEI(83));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_RIGHT]  = QRect(SYS_WID(76), SYS_HEI(154), SYS_WID(300), SYS_HEI(83));

    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_R180]     = QRect(SYS_WID(165), SYS_HEI(150), SYS_WID(73), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_NORMAL]   = QRect(SYS_WID(165), SYS_HEI(150), SYS_WID(73), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_LEFT]     = QRect(SYS_WID(76), SYS_HEI(288), SYS_WID(300), SYS_HEI(73));
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_RIGHT]    = QRect(SYS_WID(76), SYS_HEI(239), SYS_WID(300), SYS_HEI(73));

    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_R180]     = QRect(SYS_WID(240), SYS_HEI(150), SYS_WID(50), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_NORMAL]   = QRect(SYS_WID(240), SYS_HEI(150), SYS_WID(50), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_LEFT]     = QRect(SYS_WID(76), SYS_HEI(236), SYS_WID(300), SYS_HEI(50));
    PopInfoPos[SYS_POPUP_INFO][VIEW_DIR_RIGHT]    = QRect(SYS_WID(76), SYS_HEI(314), SYS_WID(300), SYS_HEI(50));

    PopInfoPos[SYS_POPUP_TECH][VIEW_DIR_R180]     = QRect(SYS_WID(293), SYS_HEI(150), SYS_WID(80), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_TECH][VIEW_DIR_NORMAL]   = QRect(SYS_WID(293), SYS_HEI(150), SYS_WID(80), SYS_HEI(300));
    PopInfoPos[SYS_POPUP_TECH][VIEW_DIR_LEFT]     = QRect(SYS_WID(76), SYS_HEI(154), SYS_WID(300), SYS_HEI(80));
    PopInfoPos[SYS_POPUP_TECH][VIEW_DIR_RIGHT]    = QRect(SYS_WID(76), SYS_HEI(366), SYS_WID(300), SYS_HEI(80));

}
