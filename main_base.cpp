#include "main_base.h"
#include "resource_manager.h"

CMainBase::CMainBase(QWidget *parent) :
    QWidget(parent)
{

    m_iViewer       = VIEW_MOTION;          //初始化显示动画
    m_iViewDirBuf   = VIEW_DIR_R180;        //初始化备份为  VIEW_DIR_R180

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    //只有密码模式为2时，才显示该提示框
    lbCompletionTips = NULL;
    if(RsMgr->g_PwdVersion == PWD_VERSION_2)
    {
        lbCompletionTips = new QPushButton(this);
        lbCompletionTips->setGeometry(0,0,240,50);
        lbCompletionTips->setText(QApplication::translate("CMainBase", "Completion Tips" ));
        lbCompletionTips->setStyleSheet("background-color:white;color:red");
        lbCompletionTips->setFont(font);
        connect(lbCompletionTips,SIGNAL(pressed()),this,SLOT(OnCompletionTip()));
    }

    setVisible(false);                      //初始化不可见
}
void CMainBase::OnPageChange(int)
{

}
void CMainBase::OnFilmKeyDown(int )
{

}
void CMainBase::OnFilmKeyUp(int )
{

}
void CMainBase::OnCompletionTip()
{
    if(sender() == lbCompletionTips)
    {
        OnViewChange(VIEW_INSTALL);
        return;
    }
}
void CMainBase::showEvent(QShowEvent *)
{
    RsMgr->g_titleBase->show();             //显示Title
    RsMgr->g_titleBase->lower();            //显示Title，放到底层
    RsMgr->g_keyBase->show();               //显示Key
    RsMgr->g_keyBase->lower();              //将Key放到底层
    RsMgr->g_menuBase->show();         //显示Menu
    RsMgr->g_menuBase->lower();        //显示Menu，放到底层

    if( g_dbsys.utility.mShutdownShow )     //判断是否显示关机按钮
    {
        RsMgr->g_exitBase->setVisible(true);
        RsMgr->g_exitBase->raise();
    }
    //先判断是否显示光幕按钮
    if(g_mainCfg->value("utility/LightCurtainShow","0").toInt())
    {

        RsMgr->g_curtainBase->setVisible(true);
        RsMgr->g_curtainBase->raise();

        //强制关闭温度显示
        g_dbsys.utility.mTubeTempShow = false;
    }

    //判断是否显示模拟按钮
    if(g_dbsys.utility.mSimulate == FUNC_SIMULATE_ON)
    {
        if( !g_systemDb->g_bCommunicate)
        {
            RsMgr->g_simBase->setVisible(true);
            RsMgr->g_simBase->raise();
        }
    }
    //判断是否显示网络图标
    if(g_dbsys.utility.mNetShow)
    {                                  //显示客户端
        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
        {
            if(g_netBase)
            {
                g_netBase->setVisible(true);
                g_netBase->raise();
            }
        }else if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
        {                                   //显示服务器端
            if(g_netBase)
            {
                g_netBase->setVisible(true);
                g_netBase->raise();
            }
        }
    }
    //告诉下位机，进入正常模式
    unsigned short buf[10];
    buf[0]=0;
    buf[1]=SYS_CMD_NORMAL;
    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);

    RsMgr->VisibleWidgetAdd(this);

    if(lbCompletionTips)
        lbCompletionTips->raise();

    grabKeyboard();
}

void CMainBase::hideEvent(QHideEvent *)
{
    if(viewPopup)
        viewPopup->hide();

    RsMgr->VisibleWidgetDel(this);

    releaseKeyboard();
}

void CMainBase::keyPressEvent( QKeyEvent * event )
{
    event->accept();

    switch(event->key())
    {
    case Qt::Key_C:
        OnViewChange(VIEW_PASSWORD);
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        OnPopupShow(SYS_POPUP_SMART);
        break;
    case Qt::Key_F1:
    case Qt::Key_F2:
    case Qt::Key_F3:
    case Qt::Key_F4:
    case Qt::Key_F5:
    case Qt::Key_F6:
    case Qt::Key_F7:
    case Qt::Key_F8:
    case Qt::Key_F9:
        emit SmartPressed(event->key() - Qt::Key_F1);
        break;
    default:
        break;
    }
}

void CMainBase::OnViewChange(int)
{

}


void CMainBase::myViewInit()
{
    //动画区域
    viewMotion = new QGraphicsView(this);
    viewMotion->setObjectName(QString::fromUtf8("viewMotion"));
    viewMotion->setGeometry(PopInfoPos[SYS_POPUP_MOTION][m_iViewDir]);
    viewMotion->setFocusPolicy(Qt::NoFocus);
    viewMotion->setFrameShape(QFrame::NoFrame);
    viewMotion->setFrameShadow(QFrame::Plain);
    viewMotion->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewMotion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewMotion->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    viewMotion->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    viewMotion->setStyleSheet("background-color: rgb(46, 49, 56)");

    //发生器
    viewGen = new QGraphicsView(this);
    viewGen->setObjectName(QString::fromUtf8("viewGen"));
    viewGen->setGeometry(PopInfoPos[SYS_POPUP_GEN][m_iViewDir]);
    viewGen->setFocusPolicy(Qt::NoFocus);
    viewGen->setFrameShape(QFrame::NoFrame);
    viewGen->setFrameShadow(QFrame::Plain);
    viewGen->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewGen->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewGen->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    viewGen->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    viewGen->setStyleSheet("background-color: rgb(46, 49, 56)");
    viewGen->hide();

    //信息提示
    viewInfo = new QGraphicsView(this);
    viewInfo->setObjectName(QString::fromUtf8("viewInfo"));
    viewInfo->setGeometry(PopInfoPos[SYS_POPUP_INFO][m_iViewDir]);
    viewInfo->setFocusPolicy(Qt::NoFocus);
    viewInfo->setFrameShape(QFrame::NoFrame);
    viewInfo->setFrameShadow(QFrame::Plain);
    viewInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewInfo->setAlignment(Qt::AlignLeft);
    viewInfo->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    viewInfo->setStyleSheet("background: transparent");

    //状态数据
    viewStatus = new QGraphicsView(this);
    viewStatus->setObjectName(QString::fromUtf8("viewStatus"));
    viewStatus->setGeometry(PopInfoPos[SYS_POPUP_STATUS][m_iViewDir]);
    viewStatus->setFocusPolicy(Qt::NoFocus);
    viewStatus->setFrameShape(QFrame::NoFrame);
    viewStatus->setFrameShadow(QFrame::Plain);
    viewStatus->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewStatus->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewStatus->setAlignment(Qt::AlignLeft | Qt::AlignLeft | Qt::AlignTop);
    viewStatus->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //快捷按钮
    viewFast = new QGraphicsView(this);
    viewFast->setObjectName(QString::fromUtf8("viewFast"));
    viewFast->setGeometry(PopInfoPos[SYS_POPUP_FAST][m_iViewDir]);
    viewFast->setFrameShape(QFrame::NoFrame);
    viewFast->setFrameShadow(QFrame::Plain);
    viewFast->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewFast->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewFast->setStyleSheet("background:transparent");
    viewFast->setInteractive(true);

    //信息提示
    viewTech = new QGraphicsView(this);
    viewTech->setGeometry(PopInfoPos[SYS_POPUP_TECH][m_iViewDir]);
    viewTech->setFocusPolicy(Qt::NoFocus);
    viewTech->setFrameShape(QFrame::NoFrame);
    viewTech->setFrameShadow(QFrame::Plain);
    viewTech->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewTech->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //弹出信息
    viewPopup   = new QGraphicsView(this);
    viewPopup->setObjectName(QString::fromUtf8("viewPopup"));
    viewPopup->setGeometry(PopInfoPos[SYS_POPUP_SMART][m_iViewDir]);
    viewPopup->setFocusPolicy(Qt::NoFocus);
    viewPopup->setFrameShape(QFrame::NoFrame);
    viewPopup->setFrameShadow(QFrame::Plain);
    viewPopup->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewPopup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewPopup->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
    viewPopup->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    viewPopup->setStyleSheet("background:transparent");
    viewPopup->raise();
    viewPopup->hide();

}

void CMainBase::mySceneInit()
{
    pSceneArray[SYS_POPUP_FOCUS] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_FOCUS]->addWidget(RsMgr->g_genFocus);
    RsMgr->g_genFocus->setVisible(true);

    pSceneArray[SYS_POPUP_AEC] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_AEC]->addWidget(RsMgr->g_genAec);

    //pSceneArray[SYS_POPUP_SMART] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_SMART] = new QGraphicsScene();
    pSceneArray[SYS_POPUP_SMART]->addWidget(RsMgr->g_smartBase);

    pSceneArray[SYS_POPUP_REQUEST] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_REQUEST]->addWidget(RsMgr->g_systemClient);

    pSceneArray[SYS_POPUP_GEN] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_GEN]->addWidget(g_GenMain);
    viewGen->setScene(pSceneArray[SYS_POPUP_GEN]);
    g_GenMain->show();

    pSceneArray[SYS_POPUP_MOTION] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_MOTION]->addWidget(RsMgr->g_motionBase);
    RsMgr->g_motionBase->setVisible(true);
    viewMotion->setScene(pSceneArray[SYS_POPUP_MOTION]);
    viewMotion->raise();

    pSceneArray[SYS_POPUP_INFO] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_INFO]->addWidget(RsMgr->g_infoBase);
    RsMgr->g_infoBase->setVisible(true);

    pSceneArray[SYS_POPUP_PARAM] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_PARAM]->addWidget(RsMgr->g_genParamMgr);

    pSceneArray[SYS_POPUP_STATUS] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_STATUS]->addWidget(RsMgr->g_statusBase);
    RsMgr->g_statusBase->setVisible(true);

    viewFast->raise();
}
//发生器技术条件变更
void CMainBase::OnGenTechChange(int tech)
{
    switch(tech)
    {
    case SYS_TECH_AEC:
    case SYS_TECH_MAS:
    case SYS_TECH_MAMS:
        if(viewMotion)      //隐藏动画界面
        {
            viewMotion->hide();
        }
        if(viewGen)         //显示发生器界面
        {
            viewGen->show();
        }
        break;
    default:
        break;
    }
}

void CMainBase::OnPopupShow(int )
{

}
void CMainBase::OnPopupHide(QWidget *)
{

}
void CMainBase::OnViewDirChange(int )
{

}
void CMainBase::mousePressEvent(QMouseEvent *event)
{

    if(event->type() == QEvent::MouseButtonPress)
    {
        unsigned short keyBuf[2];
        keyBuf[0] =0;
        keyBuf[1] = EMG_STOP_V1;
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
    }
}
