#include <QTransform>
#include <QMessageBox>
#include <QVector3D>

#include "main_base_ndt8.h"
#include "./system/sys_database.h"
#include "resource_manager.h"

#define NDT8_KEY_FID_UP_PRESS      0x0020
#define NDT8_KEY_FID_DOWN_PRESS    0x0022
#define NDT8_KEY_X1_UP_PRESS       0x0024
#define NDT8_KEY_X1_DOWN_PRESS     0x0026
#define NDT8_KEY_Y1_UP_PRESS       0x0028
#define NDT8_KEY_Y1_DOWN_PRESS     0x002a
#define NDT8_KEY_X2_UP_PRESS       0x002c
#define NDT8_KEY_X2_DOWN_PRESS     0x002e
#define NDT8_KEY_Y2_UP_PRESS       0x0030
#define NDT8_KEY_Y2_DOWN_PRESS     0x0032
#define NDT8_KEY_X3_UP_PRESS       0x0034
#define NDT8_KEY_X3_DOWN_PRESS     0x0036
#define NDT8_KEY_Y3_UP_PRESS       0x0038
#define NDT8_KEY_Y3_DOWN_PRESS     0x003a
#define NDT8_KEY_EXP_PRESS         0x003c
#define NDT8_KEY_colli_press       0x003e

#define NDT8_KEY_FID_UP_RELEASE    0x0021
#define NDT8_KEY_FID_DOWN_RELEASE  0x0023
#define NDT8_KEY_X1_UP_RELEASE     0x0025
#define NDT8_KEY_X1_DOWN_RELEASE   0x0027
#define NDT8_KEY_Y1_UP_RELEASE     0x0029
#define NDT8_KEY_Y1_DOWN_RELEASE   0x002b
#define NDT8_KEY_X2_UP_RELEASE     0x002d
#define NDT8_KEY_X2_DOWN_RELEASE   0x002f
#define NDT8_KEY_Y2_UP_RELEASE     0x0031
#define NDT8_KEY_Y2_DOWN_RELEASE   0x0033
#define NDT8_KEY_X3_UP_RELEASE     0x0035
#define NDT8_KEY_X3_DOWN_RELEASE   0x0037
#define NDT8_KEY_Y3_UP_RELEASE     0x0039
#define NDT8_KEY_Y3_DOWN_RELEASE   0x003b
#define NDT8_KEY_EXP_RELEASE       0x003d
#define NDT8_KEY_colli_release     0x003f


#define NDT8A_KEY_DELAY_LONG     550
#define NDT8A_KEY_DELAY_SHORT    100

#define NDT8A_FRESH_INTERVAL 200

#define NDT8A_X_PT_START SYS_WID(166)
#define NDT8A_X_PT_WIDTH SYS_WID(350)
#define NDT8A_Y_PT_START SYS_HEI(502)
#define NDT8A_Y_PT_WIDTH SYS_HEI(530)
#define NDT8A_PANEL_PT 68
#define NDT8A_REAL_X_MAX 2000
#define NDT8A_REAL_Y_MAX 3000


#define NDT8A_DIR_NULL      0
#define NDT8A_DIR_LEFT      1
#define NDT8A_DIR_RIGHT     2
#define NDT8A_DIR_DOWN      3
#define NDT8A_DIR_UP        4

CMainBaseNdt8::CMainBaseNdt8(QWidget *parent) :
    CMainBase(parent)
{

    //resize frame size
    resize(g_sysWidth,g_sysHeight);

    this->setAutoFillBackground(true);

    /*
    QPalette palette;
#ifdef QT_ARCH_ARM
    palette.setBrush(QPalette::Background, QBrush(QPixmap(g_skinBase->GetStyleMapStr("NDT8_BACK_GROUND"))));
#else
    QImage image(":/QRes/8080/png00/background.png");
    palette.setBrush(QPalette::Background, QBrush(image.scaled(g_sysWidth,g_sysHeight, Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    //palette.setBrush(QPalette::Background, QBrush(QPixmap(g_skinBase->GetStyleMapStr("NDT8_BACK_GROUND"))));
#endif
    this->setPalette(palette);
*/
    frameBack = new QFrame(this);
    frameBack->setGeometry(0,0,g_sysWidth,g_sysHeight);
    frameBack->setStyleSheet("QFrame{ border-image: url(:/QRes/8080/png00/background.png);}");
    frameBack->lower();

    OnMoveCtrlInit();

    mySceneInit();              //场景初始化

    tmDataFresh = new QTimer(this);
    tmDataFresh->setInterval(NDT8A_FRESH_INTERVAL);
    connect(tmDataFresh,SIGNAL(timeout()),this,SLOT(OnNdt8aDataFresh()));

    //disable tips for medical system
    if(lbCompletionTips)
        lbCompletionTips->setVisible(false);

    mPreDirBuf = NDT8A_DIR_NULL;
    mKeepAliveCtr = 0;
}


void CMainBaseNdt8::OnMoveCtrlInit()
{

    QFont font;
    font.setPixelSize(40);      //change display number size

    btnSetting = new CButtonStable(this);
    btnSetting->setGeometry(SYS_WID(2),SYS_HEI(524) ,SYS_WID(89),SYS_HEI(74));
    btnSetting->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_SETTING"));
    btnSetting->setVisible(true);
    btnSetting->setFocusPolicy(Qt::NoFocus);
    connect(btnSetting,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnSetting,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnSetting);

    btnYaxisAdd = new CButtonStable(this);
    btnYaxisAdd->setGeometry(SYS_WID(554),SYS_HEI(202) ,SYS_WID(106),SYS_HEI(74));
    btnYaxisAdd->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_YAXIS_ADD"));
    btnYaxisAdd->setVisible(true);
    btnYaxisAdd->setFocusPolicy(Qt::NoFocus);
    connect(btnYaxisAdd,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnYaxisAdd,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnYaxisAdd);

    btnYaxisDec = new CButtonStable(this);
    btnYaxisDec->setGeometry(SYS_WID(554),SYS_HEI(275) ,SYS_WID(106),SYS_HEI(74));
    btnYaxisDec->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_DEC_BACK_COLOR"));
    btnYaxisDec->setVisible(true);
    btnYaxisDec->setFocusPolicy(Qt::NoFocus);
    connect(btnYaxisDec,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnYaxisDec,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    btnYaxisDec->setFont(font);
    arrBtnMoveCtrl.push_back(btnYaxisDec);

    btnXaxisAdd = new CButtonStable(this);
    btnXaxisAdd->setGeometry(SYS_WID(554),SYS_HEI(400) ,SYS_WID(106),SYS_HEI(74));
    btnXaxisAdd->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_XAXIS_ADD"));
    btnXaxisAdd->setVisible(true);
    btnXaxisAdd->setFocusPolicy(Qt::NoFocus);
    connect(btnXaxisAdd,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnXaxisAdd,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnXaxisAdd);

    btnXaxisDec = new CButtonStable(this);
    btnXaxisDec->setGeometry(SYS_WID(554),SYS_HEI(474) ,SYS_WID(106),SYS_HEI(74));
    btnXaxisDec->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_DEC_BACK_COLOR"));
    btnXaxisDec->setVisible(true);
    btnXaxisDec->setFocusPolicy(Qt::NoFocus);
    connect(btnXaxisDec,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnXaxisDec,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    btnXaxisDec->setFont(font);
    arrBtnMoveCtrl.push_back(btnXaxisDec);

    btnFidUp = new CButtonStable(this);
    btnFidUp->setGeometry(SYS_WID(554),SYS_HEI(10) ,SYS_WID(106),SYS_HEI(74));
    btnFidUp->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_FID_UP"));
    btnFidUp->setVisible(true);
    btnFidUp->setFocusPolicy(Qt::NoFocus);
    connect(btnFidUp,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnFidUp,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnFidUp);

    btnFidDown = new CButtonStable(this);
    btnFidDown->setGeometry(SYS_WID(554),SYS_HEI(84) ,SYS_WID(106),SYS_HEI(74));
    btnFidDown->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_DEC_BACK_COLOR"));
    btnFidDown->setVisible(true);
    btnFidDown->setFocusPolicy(Qt::NoFocus);
    connect(btnFidDown,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnFidDown,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    btnFidDown->setFont(font);
    arrBtnMoveCtrl.push_back(btnFidDown);

    btnPanel = new CButtonStable(this);
    btnPanel->setGeometry(SYS_WID(365),SYS_HEI(265) ,SYS_WID(NDT8A_PANEL_PT),SYS_HEI(NDT8A_PANEL_PT));
    btnPanel->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_PANEL_NULL"));
    btnPanel->setVisible(true);
    btnPanel->setFocusPolicy(Qt::NoFocus);
    connect(btnPanel,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnPanel,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnPanel);

    btnBottom = new CButtonStable(this);
    btnBottom->setGeometry(SYS_WID(714),SYS_HEI(0) ,SYS_WID(86),SYS_HEI(600));
    btnBottom->setStyleSheet(g_skinBase->GetStyleMapStr("NDT8_BOTTOM"));
    btnBottom->setVisible(true);
    btnBottom->setFocusPolicy(Qt::NoFocus);
    connect(btnBottom,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnBottom,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnBottom);
}
void CMainBaseNdt8::SendNdt8Cmd(unsigned short key)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = key;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}
void CMainBaseNdt8::OnBtnMovePressed()
{
    if(sender() == btnSetting)
    {
        emit ViewChange(VIEW_PASSWORD);
        return;
    }

    if(sender() == btnYaxisAdd)
    {//1
        SendNdt8Cmd(NDT8_KEY_Y1_UP_PRESS);
        return;
    }

    if(sender() == btnYaxisDec)
    {//2
        SendNdt8Cmd(NDT8_KEY_Y1_DOWN_PRESS);
        return;
    }

    if(sender() == btnXaxisAdd)
    {//3
        SendNdt8Cmd(NDT8_KEY_X1_UP_PRESS);
        return;
    }

    if(sender() == btnXaxisDec)
    {//4
        SendNdt8Cmd(NDT8_KEY_X1_DOWN_PRESS);
        return;
    }

    if(sender() == btnFidUp)
    {//5
        SendNdt8Cmd(NDT8_KEY_FID_UP_PRESS);
        return;
    }

    if(sender() == btnFidDown)
    {//6
        SendNdt8Cmd(NDT8_KEY_FID_DOWN_PRESS);
        return;
    }

}
void CMainBaseNdt8::OnBtnMoveReleased()
{
    if(sender() == btnYaxisAdd)
    {//1
        SendNdt8Cmd(NDT8_KEY_Y1_UP_RELEASE);

        return;
    }

    if(sender() == btnYaxisDec)
    {//2
        SendNdt8Cmd(NDT8_KEY_Y1_DOWN_RELEASE);

        return;
    }

    if(sender() == btnXaxisAdd)
    {//3
        SendNdt8Cmd(NDT8_KEY_X1_UP_RELEASE);

        return;
    }

    if(sender() == btnXaxisDec)
    {//4
        SendNdt8Cmd(NDT8_KEY_X1_DOWN_RELEASE);

        return;
    }

    if(sender() == btnFidUp)
    {//5
        SendNdt8Cmd(NDT8_KEY_FID_UP_RELEASE);
        return;
    }

    if(sender() == btnFidDown)
    {//6
        SendNdt8Cmd(NDT8_KEY_FID_DOWN_RELEASE);
        return;
    }

}

void CMainBaseNdt8::mySceneInit()
{

    RsMgr->g_infoBase->setParent(this);
    RsMgr->g_infoBase->move(SYS_WID(714), SYS_HEI(0));
    RsMgr->g_infoBase->setVisible(true);
    RsMgr->g_infoBase->raise();
    RsMgr->g_infoBase->setStyleSheet("QWidget{background : transparent;}");

}
void CMainBaseNdt8::myViewInit()
{


}


void CMainBaseNdt8::mousePressEvent(QMouseEvent *event)
{
    //print left button down point.
    qDebug()<< event->pos().x() << event->pos().y();


}


void CMainBaseNdt8::paintEvent(QPaintEvent *)
{

}


void CMainBaseNdt8::OnPopupShow(int )
{

}


void CMainBaseNdt8::showEvent(QShowEvent * )
{
    //判断是否显示网络图标
    if(g_netBase && g_dbsys.utility.mNetShow)
    {
        g_netBase->setParent(this);
        g_netBase->move(SYS_WID(2),SYS_HEI(472));
        g_netBase->setVisible(true);
        g_netBase->raise();
    }

    tmDataFresh->start();

    grabKeyboard();

}
void CMainBaseNdt8::hideEvent(QHideEvent * )
{
    tmDataFresh->stop();

    releaseKeyboard();

}

void CMainBaseNdt8::OnViewChange(int view)
{
    switch(view)
    {
    case VIEW_GEN_CFG:                                  //发生器参数配置模式

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
        //viewMotion->hide();                 //隐藏动画界面
        //viewInfo->hide();                   //隐藏消息框界面
        //viewGen->hide();                    //隐藏发生器界面
        //viewPopup->hide();                  //隐藏弹出框界面

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

        g_mainFrame->setRotate(0);
        g_mainFrame->setSceneWidget(this);
        g_mainSetting->hide();

        emit ViewChange(VIEW_MAIN);

        break;
    default:
        break;
    }
}

void CMainBaseNdt8::keyPressEvent(QKeyEvent * event)
{
    //ignore repeat key message.
    if(event->isAutoRepeat())
    {
        event->ignore();
        return;
    }

    RsMgr->g_filmBase->SetKeySound();

    if(g_dbsys.operation.bTimeout)              //如果系统认为过期，不进行后续操作
        return;

    SendNdt8KeyPress(event->key());
}

void CMainBaseNdt8::keyReleaseEvent(QKeyEvent *event)
{
    SendNdt8KeyRelease( event->key());
}

void CMainBaseNdt8::SendNdt8KeyPress(int mKey)
{
    qDebug()<<"key pressed"<<mKey<<endl;

    switch(mKey)
    {
    case Qt::Key_A:         //C1//0x41//65
        SendNdt8Cmd(NDT8_KEY_Y3_UP_PRESS);
        if(mPreDirBuf == NDT8A_DIR_DOWN)
        {
            btnPanel->setStyleSheet("QPushButton{border-image: url(:/QRes/8080/png00/panel-null.png);}");
            mPreDirBuf = NDT8A_DIR_NULL;
        }else
        {
            btnPanel->setStyleSheet("QPushButton{border-image: url(:/QRes/8080/png00/panel-up.png);}");
            mPreDirBuf = NDT8A_DIR_UP;
        }
        break;
    case Qt::Key_D:         //C2//0x44//68
        SendNdt8Cmd(NDT8_KEY_Y3_DOWN_PRESS);
        if(mPreDirBuf == NDT8A_DIR_UP)
        {
            btnPanel->setStyleSheet("QPushButton{border-image: url(:/QRes/8080/png00/panel-null.png);}");
            mPreDirBuf = NDT8A_DIR_NULL;
        }else
        {
            btnPanel->setStyleSheet("QPushButton{border-image: url(:/QRes/8080/png00/panel-down.png);}");
            mPreDirBuf = NDT8A_DIR_DOWN;
        }
        break;
    case Qt::Key_J:         //C4//0x4a//74
        SendNdt8Cmd(NDT8_KEY_X3_DOWN_PRESS);
        if(mPreDirBuf == NDT8A_DIR_RIGHT)
        {
            btnPanel->setStyleSheet("QPushButton{border-image: url(:/QRes/8080/png00/panel-null.png);}");
            mPreDirBuf = NDT8A_DIR_NULL;
        }else
        {
            btnPanel->setStyleSheet("QPushButton{border-image: url(:/QRes/8080/png00/panel-left.png);}");
            mPreDirBuf = NDT8A_DIR_LEFT;
        }
        break;
    case Qt::Key_Semicolon: //C13//;//0x3b//59
        SendNdt8Cmd(NDT8_KEY_X3_UP_PRESS);
        if(mPreDirBuf == NDT8A_DIR_LEFT)
        {
            btnPanel->setStyleSheet("QPushButton{border-image: url(:/QRes/8080/png00/panel-null.png);}");
            mPreDirBuf = NDT8A_DIR_NULL;
        }else
        {
            btnPanel->setStyleSheet("QPushButton{border-image: url(:/QRes/8080/png00/panel-right.png);}");
            mPreDirBuf = NDT8A_DIR_RIGHT;
        }
        break;
    case Qt::Key_Escape:    //C0//0x01000000//16777216
        SendNdt8Cmd(NDT8_KEY_Y2_UP_PRESS);
        break;
    case Qt::Key_F4:        //C2//0x01000033//16777267
        SendNdt8Cmd(NDT8_KEY_Y2_DOWN_PRESS);
        break;
    case Qt::Key_H:         //C4//0x48//72
        SendNdt8Cmd(NDT8_KEY_X2_DOWN_PRESS);
        break;
    case Qt::Key_Apostrophe:    //C13//'//0x27//39
        SendNdt8Cmd(NDT8_KEY_X2_UP_PRESS);
        break;
    case Qt::Key_Q:         //C0//0x51//81
        SendNdt8Cmd(NDT8_KEY_Y1_UP_PRESS);
        break;
    case Qt::Key_E:         //C2//0x45//69
        SendNdt8Cmd(NDT8_KEY_Y1_DOWN_PRESS);
        break;
    case Qt::Key_U:         //C4//0x55//85
        SendNdt8Cmd(NDT8_KEY_X1_DOWN_PRESS);
        break;
    case Qt::Key_P:         //C13//0x50//80
        SendNdt8Cmd(NDT8_KEY_X1_UP_PRESS);
        break;
    case Qt::Key_1:         //C0//0x31//49
        SendNdt8Cmd(NDT8_KEY_FID_UP_PRESS);
        break;
    case Qt::Key_3:         //C2//0x34//52
        SendNdt8Cmd(NDT8_KEY_FID_DOWN_PRESS);
        break;
    default:

        break;
    }
}
void CMainBaseNdt8::SendNdt8KeyRelease(int mKey)
{
    qDebug()<<"key released"<<mKey;

    switch(mKey)
    {
    case Qt::Key_A:         //C1
        SendNdt8Cmd(NDT8_KEY_Y3_UP_RELEASE);
        break;
    case Qt::Key_D:         //C2
        SendNdt8Cmd(NDT8_KEY_Y3_DOWN_RELEASE);
        break;
    case Qt::Key_J:         //C4
        SendNdt8Cmd(NDT8_KEY_X3_DOWN_RELEASE);
        break;
    case Qt::Key_Semicolon: //C13//;//0x3b
        SendNdt8Cmd(NDT8_KEY_X3_UP_RELEASE);
        break;
    case Qt::Key_Escape:    //C0
        SendNdt8Cmd(NDT8_KEY_Y2_UP_RELEASE);
        break;
    case Qt::Key_F4:        //C2
        SendNdt8Cmd(NDT8_KEY_Y2_DOWN_RELEASE);
        break;
    case Qt::Key_H:         //C4
        SendNdt8Cmd(NDT8_KEY_X2_DOWN_RELEASE);
        break;
    case Qt::Key_Apostrophe:    //C13//'//0x27
        SendNdt8Cmd(NDT8_KEY_X2_UP_RELEASE);
        break;
    case Qt::Key_Q:         //C0
        SendNdt8Cmd(NDT8_KEY_Y1_UP_RELEASE);
        break;
    case Qt::Key_E:         //C2
        SendNdt8Cmd(NDT8_KEY_Y1_DOWN_RELEASE);
        break;
    case Qt::Key_U:         //C4
        SendNdt8Cmd(NDT8_KEY_X1_DOWN_RELEASE);
        break;
    case Qt::Key_P:         //C13
        SendNdt8Cmd(NDT8_KEY_X1_UP_RELEASE);
        break;
    case Qt::Key_1:         //C0
        SendNdt8Cmd(NDT8_KEY_FID_UP_RELEASE);
        break;
    case Qt::Key_3:         //C2
        SendNdt8Cmd(NDT8_KEY_FID_DOWN_RELEASE);
        break;
    default:

        break;
    }

}

void CMainBaseNdt8::OnNdt8aDataFresh()
{

    //fprintf(stderr, "Heart beat error%d\n",g_systemDb->g_dbMachine.CurrentData[NDT8a_MOTOR_FID]);


    QString mBuf;

    mBuf.sprintf("%d",g_systemDb->g_dbMachine.CurrentData[NDT8a_MOTOR_FID]);
    btnFidDown->setText(mBuf);

    mBuf.sprintf("%d",g_systemDb->g_dbMachine.CurrentData[NDT8a_MOTOR_X1]);
    btnXaxisDec->setText(mBuf);

    mBuf.sprintf("%d",g_systemDb->g_dbMachine.CurrentData[NDT8a_MOTOR_Y1]);
    btnYaxisDec->setText(mBuf);

    //update panel position
    unsigned short mXposData,mYposData,mXposScreen,mYposScreen;
    mXposData = g_systemDb->g_dbMachine.CurrentData[NDT8a_MOTOR_X1];
    mYposData = g_systemDb->g_dbMachine.CurrentData[NDT8a_MOTOR_Y1];

    //ack every 200ms
    //no heart ack for net client
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
    {
        unsigned short keyBuf[8];
        keyBuf[0] = CMD_KEEP_ALIVE_DATA;
        g_taskComCtrl->CreateTask(CMD_KEEP_ALIVE_HEADER,keyBuf,1);
    }

    //不能放在心跳包前面，否在会造成心跳不发
    if(mXposData > NDT8A_REAL_X_MAX || mYposData >NDT8A_REAL_Y_MAX)
        return;

    mXposScreen = (NDT8A_X_PT_WIDTH - NDT8A_PANEL_PT) * mXposData / NDT8A_REAL_X_MAX + NDT8A_X_PT_START;
    mYposScreen = NDT8A_Y_PT_START - (NDT8A_Y_PT_WIDTH - NDT8A_PANEL_PT) * mYposData / NDT8A_REAL_Y_MAX;

    btnPanel->move(mXposScreen,mYposScreen);

}

