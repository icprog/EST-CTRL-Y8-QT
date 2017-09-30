#include "main_ceil10b.h"
#include "resource_manager.h"

CMainCeil10b::CMainCeil10b(QWidget *parent) :
    CMainBase10(parent)
{
    setObjectName("CMainCeil10b");

    resize(g_sysWidth,g_sysHeight);

    this->setStyleSheet("background-color: black");

    //for xubing only 徐冰用，不输入密码的PAD控制程序
    g_dbsys.operationx.keyInstalled = true;
    lbCompletionTips->setVisible(false);

}
void CMainCeil10b::OnViewChange(int view)
{

    CMainBase10::OnViewChange(view);
    /*
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

        RsMgr->g_fastBase->setVisible(false);
        viewFast->setVisible(false);

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

        RsMgr->g_fastBase->setVisible(true);
        viewFast->setVisible(true);

        //viewPopup->setParent(this);
        //viewPopup->resetMatrix();
        //viewPopup->rotate(m_iViewSwitch[VIEW_DIR_R180][m_iViewDir]);
        //viewPopup->move(SYS_WID(400), SYS_HEI(200));
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
    */
}
