#include <QTransform>
#include <QMessageBox>
#include <QVector3D>

#include "main_base_rf8a.h"
#include "./system/sys_database.h"
#include "resource_manager.h"

#define RF8A_KEY_TUBE_UP_PRESS          0x20
#define RF8A_KEY_TUBE_DOWN_PRESS        0x22
#define RF8A_KEY_TABLE_RIGHT_PRESS      0x24
#define RF8A_KEY_TABLE_LEFT_PRESS       0x26
#define RF8A_KEY_TUBE_LEFT_PRESS        0x28
#define RF8A_KEY_TUBE_RIGHT_PRESS       0x2a
#define RF8A_KEY_ANGLE_LEFT_PRESS       0x2c
#define RF8A_KEY_ANGLE_RIGHT_PRESS      0x2e
#define RF8A_KEY_PEDAL_LEFT_PRESS       0x30
#define RF8A_KEY_PEDAL_RIGHT_PRESS      0x32
#define RF8A_KEY_COMPRESSOR_UP_PRESS    0x34
#define RF8A_KEY_COMPRESSOR_DOWN_PRESS  0x36
#define RF8A_KEY_COLI_Y_OPEN_PRESS      0x38
#define RF8A_KEY_COLI_Y_CLOSE_PRESS     0x3a
#define RF8A_KEY_COLI_X_OPEN_PRESS      0x3c
#define RF8A_KEY_COLI_X_CLOSE_PRESS     0x3e


#define RF8A_KEY_TUBE_UP_RELEASE          0x21
#define RF8A_KEY_TUBE_DOWN_RELEASE        0x23
#define RF8A_KEY_TABLE_RIGHT_RELEASE      0x25
#define RF8A_KEY_TABLE_LEFT_RELEASE       0x27
#define RF8A_KEY_TUBE_LEFT_RELEASE        0x29
#define RF8A_KEY_TUBE_RIGHT_RELEASE       0x2b
#define RF8A_KEY_ANGLE_LEFT_RELEASE       0x2d
#define RF8A_KEY_ANGLE_RIGHT_RELEASE      0x2f
#define RF8A_KEY_PEDAL_LEFT_RELEASE       0x31
#define RF8A_KEY_PEDAL_RIGHT_RELEASE      0x33
#define RF8A_KEY_COMPRESSOR_UP_RELEASE    0x35
#define RF8A_KEY_COMPRESSOR_DOWN_RELEASE  0x37
#define RF8A_KEY_COLI_Y_OPEN_RELEASE      0x39
#define RF8A_KEY_COLI_Y_CLOSE_RELEASE     0x3b
#define RF8A_KEY_COLI_X_OPEN_RELEASE      0x3d
#define RF8A_KEY_COLI_X_CLOSE_RELEASE     0x3f


#define RF8A_KEY_DELAY_LONG     550
#define RF8A_KEY_DELAY_SHORT    100

#define RF8A_FRESH_INTERVAL 200

CMainBaseRf8a::CMainBaseRf8a(QWidget *parent) :
    CMainBase(parent)
{

    //resize frame size
    resize(g_sysWidth,g_sysHeight);

    this->setAutoFillBackground(true);

    QPalette palette;
#ifdef QT_ARCH_ARM
    //palette.setBrush(QPalette::Background, QBrush(QPixmap(QString("/sdcard/home/fa") + "/8060/png00/background.png")));
    palette.setBrush(QPalette::Background, QBrush(QColor(218,218,218)));
#else
    palette.setBrush(QPalette::Background, QBrush(QColor(218,218,218)));
#endif
    this->setPalette(palette);

    OnMoveCtrlInit();

    OnTextLabelInit();
    mKeyBufPress = 0;
    tmKeyReleaseCheck = new QTimer(this);
    tmKeyReleaseCheck->setInterval(RF8A_KEY_DELAY_LONG);
    connect(tmKeyReleaseCheck,SIGNAL(timeout()),this,SLOT(OnKeyReleaseCheck()));

    mySceneInit();              //场景初始化

    tmDataFresh = new QTimer(this);
    tmDataFresh->setInterval(RF8A_FRESH_INTERVAL);
    connect(tmDataFresh,SIGNAL(timeout()),this,SLOT(OnRf8aDataFresh()));

    mKeepAliveCtr = 0;
}


void CMainBaseRf8a::OnMoveCtrlInit()
{

    btnTitle = new CButtonStable(this);
    btnTitle->setGeometry(SYS_WID(0),SYS_HEI(0) ,SYS_WID(800),SYS_HEI(74));
    btnTitle->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btSetting.png);}");
    btnTitle->setText("RF SYSTEM");
    btnTitle->setVisible(true);
    connect(btnTitle,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTitle,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTitle);

    btnTableRight = new CButtonStable(this);
    btnTableRight->setGeometry(SYS_WID(30),SYS_HEI(124) ,SYS_WID(106),SYS_HEI(74));
    btnTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btTabeRight.png);}");
    btnTableRight->setVisible(true);
    connect(btnTableRight,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTableRight,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTableRight);

    btnTableLeft = new CButtonStable(this);
    btnTableLeft->setGeometry(SYS_WID(282),SYS_HEI(124) ,SYS_WID(106),SYS_HEI(74));
    btnTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btTabeLeft.png);}");
    btnTableLeft->setVisible(true);
    connect(btnTableLeft,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTableLeft,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTableLeft);

    btnTableRotateLeft = new CButtonStable(this);
    btnTableRotateLeft->setGeometry(SYS_WID(412),SYS_HEI(124) ,SYS_WID(106),SYS_HEI(74));
    btnTableRotateLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btTabeRotateLeft.png);}");
    btnTableRotateLeft->setVisible(true);
    connect(btnTableRotateLeft,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTableRotateLeft,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTableRotateLeft);

    btnTableRotateRight = new CButtonStable(this);
    btnTableRotateRight->setGeometry(SYS_WID(664),SYS_HEI(124) ,SYS_WID(106),SYS_HEI(74));
    btnTableRotateRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btTabeRotateRight.png);}");
    btnTableRotateRight->setVisible(true);
    connect(btnTableRotateRight,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTableRotateRight,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTableRotateRight);

    btnColiYOpen = new CButtonStable(this);
    btnColiYOpen->setGeometry(SYS_WID(30),SYS_HEI(212) ,SYS_WID(106),SYS_HEI(74));
    btnColiYOpen->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btColi1.png);}");
    btnColiYOpen->setVisible(true);
    connect(btnColiYOpen,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnColiYOpen,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnColiYOpen);

    btnColiYClose = new CButtonStable(this);
    btnColiYClose->setGeometry(SYS_WID(282),SYS_HEI(212) ,SYS_WID(106),SYS_HEI(74));
    btnColiYClose->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btColi2.png);}");
    btnColiYClose->setVisible(true);
    connect(btnColiYClose,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnColiYClose,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnColiYClose);

    btnColiXOpen = new CButtonStable(this);
    btnColiXOpen->setGeometry(SYS_WID(412),SYS_HEI(212) ,SYS_WID(106),SYS_HEI(74));
    btnColiXOpen->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btColi3.png);}");
    btnColiXOpen->setVisible(true);
    connect(btnColiXOpen,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnColiXOpen,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnColiXOpen);

    btnColiXClose = new CButtonStable(this);
    btnColiXClose->setGeometry(SYS_WID(664),SYS_HEI(212) ,SYS_WID(106),SYS_HEI(74));
    btnColiXClose->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btColi4.png);}");
    btnColiXClose->setVisible(true);
    connect(btnColiXClose,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnColiXClose,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnColiXClose);

    btnCompressorUp = new CButtonStable(this);
    btnCompressorUp->setGeometry(SYS_WID(30),SYS_HEI(302) ,SYS_WID(106),SYS_HEI(74));
    btnCompressorUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btCompressorUp.png);}");
    btnCompressorUp->setVisible(true);
    connect(btnCompressorUp,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnCompressorUp,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnCompressorUp);

    btnCompressorDown = new CButtonStable(this);
    btnCompressorDown->setGeometry(SYS_WID(282),SYS_HEI(302) ,SYS_WID(106),SYS_HEI(74));
    btnCompressorDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btCompressorDown.png);}");
    btnCompressorDown->setVisible(true);
    connect(btnCompressorDown,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnCompressorDown,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnCompressorDown);

    btnRotaryPedalLeft = new CButtonStable(this);
    btnRotaryPedalLeft->setGeometry(SYS_WID(412),SYS_HEI(302) ,SYS_WID(106),SYS_HEI(74));
    btnRotaryPedalLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btRotaryPedal1.png);}");
    btnRotaryPedalLeft->setVisible(true);
    connect(btnRotaryPedalLeft,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnRotaryPedalLeft,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnRotaryPedalLeft);

    btnRotaryPedalRight = new CButtonStable(this);
    btnRotaryPedalRight->setGeometry(SYS_WID(664),SYS_HEI(302) ,SYS_WID(106),SYS_HEI(74));
    btnRotaryPedalRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btRotaryPedal2.png);}");
    btnRotaryPedalRight->setVisible(true);
    connect(btnRotaryPedalRight,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnRotaryPedalRight,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnRotaryPedalRight);

    btnTubeUp = new CButtonStable(this);
    btnTubeUp->setGeometry(SYS_WID(30),SYS_HEI(397) ,SYS_WID(106),SYS_HEI(74));
    btnTubeUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btTubeUp.png);}");
    btnTubeUp->setVisible(true);
    connect(btnTubeUp,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTubeUp,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTubeUp);

    btnTubeDown = new CButtonStable(this);
    btnTubeDown->setGeometry(SYS_WID(282),SYS_HEI(397) ,SYS_WID(106),SYS_HEI(74));
    btnTubeDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btTubedown.png);}");
    btnTubeDown->setVisible(true);
    connect(btnTubeDown,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTubeDown,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTubeDown);

    btnTubeLeft = new CButtonStable(this);
    btnTubeLeft->setGeometry(SYS_WID(412),SYS_HEI(397) ,SYS_WID(106),SYS_HEI(74));
    btnTubeLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btTubeLeft.png);}");
    btnTubeLeft->setVisible(true);
    connect(btnTubeLeft,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTubeLeft,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTubeLeft);

    btnTubeRight = new CButtonStable(this);
    btnTubeRight->setGeometry(SYS_WID(664),SYS_HEI(397) ,SYS_WID(106),SYS_HEI(74));
    btnTubeRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btTubeRight.png);}");
    btnTubeRight->setVisible(true);
    connect(btnTubeRight,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnTubeRight,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnTubeRight);

    btnBottom = new CButtonStable(this);
    btnBottom->setGeometry(SYS_WID(0),SYS_HEI(526) ,SYS_WID(800),SYS_HEI(74));
    btnBottom->setStyleSheet("QPushButton{border-image: url(:/QRes/8060/png00/btBottom.png);}");
    btnBottom->setVisible(true);
    connect(btnBottom,SIGNAL(pressed()),this,SLOT(OnBtnMovePressed()));
    connect(btnBottom,SIGNAL(released()),this,SLOT(OnBtnMoveReleased()));
    arrBtnMoveCtrl.push_back(btnBottom);
}
void CMainBaseRf8a::SendRf8Cmd(unsigned short key)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = key;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}
void CMainBaseRf8a::OnBtnMovePressed()
{
    if(sender() == btnTitle)
    {
        emit ViewChange(VIEW_PASSWORD);
        return;
    }

    if(sender() == btnTableLeft)
    {//1
        SendRf8Cmd(RF8A_KEY_TABLE_LEFT_PRESS);
        return;
    }

    if(sender() == btnTableRight)
    {//2
        SendRf8Cmd(RF8A_KEY_TABLE_RIGHT_PRESS);
        return;
    }

    if(sender() == btnTableRotateLeft)
    {//3
        SendRf8Cmd(RF8A_KEY_ANGLE_LEFT_PRESS);
        return;
    }

    if(sender() == btnTableRotateRight)
    {//4
        SendRf8Cmd(RF8A_KEY_ANGLE_RIGHT_PRESS);
        return;
    }

    if(sender() == btnColiYOpen)
    {//5
        SendRf8Cmd(RF8A_KEY_COLI_Y_OPEN_PRESS);
        return;
    }

    if(sender() == btnColiYClose)
    {//6
        SendRf8Cmd(RF8A_KEY_COLI_Y_CLOSE_PRESS);
        return;
    }

    if(sender() == btnColiXOpen)
    {//7
        SendRf8Cmd(RF8A_KEY_COLI_X_OPEN_PRESS);
        return;
    }

    if(sender() == btnColiXClose)
    {//8
        SendRf8Cmd(RF8A_KEY_COLI_X_CLOSE_PRESS);
        return;
    }

    if(sender() == btnCompressorUp)
    {//9
        SendRf8Cmd(RF8A_KEY_COMPRESSOR_UP_PRESS);
        return;
    }


    if(sender() == btnCompressorDown)
    {//10
        SendRf8Cmd(RF8A_KEY_COMPRESSOR_DOWN_PRESS);
        return;
    }

    if(sender() == btnRotaryPedalLeft)
    {//11
        SendRf8Cmd(RF8A_KEY_PEDAL_LEFT_PRESS);
        return;
    }

    if(sender() == btnRotaryPedalRight)
    {//12
        SendRf8Cmd(RF8A_KEY_PEDAL_RIGHT_PRESS);
        return;
    }

    if(sender() == btnTubeUp)
    {//13
        SendRf8Cmd(RF8A_KEY_TUBE_UP_PRESS);
        return;
    }

    if(sender() == btnTubeDown)
    {//14
        SendRf8Cmd(RF8A_KEY_TUBE_DOWN_PRESS);
        return;
    }

    if(sender() == btnTubeLeft)
    {//15
        SendRf8Cmd(RF8A_KEY_TUBE_LEFT_PRESS);
        return;
    }

    if(sender() == btnTubeRight)
    {//16
        SendRf8Cmd(RF8A_KEY_TUBE_RIGHT_PRESS);
        return;
    }


}
void CMainBaseRf8a::OnBtnMoveReleased()
{
    if(sender() == btnTableLeft)
    {//1
        SendRf8Cmd(RF8A_KEY_TABLE_LEFT_RELEASE);
        return;
    }

    if(sender() == btnTableRight)
    {//2
        SendRf8Cmd(RF8A_KEY_TABLE_RIGHT_RELEASE);
        return;
    }

    if(sender() == btnTableRotateLeft)
    {//3
        SendRf8Cmd(RF8A_KEY_ANGLE_LEFT_RELEASE);
        return;
    }

    if(sender() == btnTableRotateRight)
    {//4
        SendRf8Cmd(RF8A_KEY_ANGLE_RIGHT_RELEASE);
        return;
    }

    if(sender() == btnColiYOpen)
    {//5
        SendRf8Cmd(RF8A_KEY_COLI_Y_OPEN_RELEASE);
        return;
    }

    if(sender() == btnColiYClose)
    {//6
        SendRf8Cmd(RF8A_KEY_COLI_Y_CLOSE_RELEASE);
        return;
    }

    if(sender() == btnColiXOpen)
    {//7
        SendRf8Cmd(RF8A_KEY_COLI_X_OPEN_RELEASE);
        return;
    }

    if(sender() == btnColiXClose)
    {//8
        SendRf8Cmd(RF8A_KEY_COLI_X_CLOSE_RELEASE);
        return;
    }

    if(sender() == btnCompressorUp)
    {//9
        SendRf8Cmd(RF8A_KEY_COMPRESSOR_UP_RELEASE);
        return;
    }


    if(sender() == btnCompressorDown)
    {//10
        SendRf8Cmd(RF8A_KEY_COMPRESSOR_DOWN_RELEASE);
        return;
    }

    if(sender() == btnRotaryPedalLeft)
    {//11
        SendRf8Cmd(RF8A_KEY_PEDAL_LEFT_RELEASE);
        return;
    }

    if(sender() == btnRotaryPedalRight)
    {//12
        SendRf8Cmd(RF8A_KEY_PEDAL_RIGHT_RELEASE);
        return;
    }

    if(sender() == btnTubeUp)
    {//13
        SendRf8Cmd(RF8A_KEY_TUBE_UP_RELEASE);
        return;
    }

    if(sender() == btnTubeDown)
    {//14
        SendRf8Cmd(RF8A_KEY_TUBE_DOWN_RELEASE);
        return;
    }

    if(sender() == btnTubeLeft)
    {//15
        SendRf8Cmd(RF8A_KEY_TUBE_LEFT_RELEASE);
        return;
    }

    if(sender() == btnTubeRight)
    {//16
        SendRf8Cmd(RF8A_KEY_TUBE_RIGHT_RELEASE);
        return;
    }

}
void CMainBaseRf8a::OnTextLabelInit()
{
    lbTablePosi = new QLabel(this);
    lbTablePosi->setGeometry(SYS_WID(136),SYS_HEI(124) ,SYS_WID(146),SYS_HEI(74));
    lbTablePosi->setStyleSheet("background-color : white ; color : green ;font-size: 36px");
    lbTablePosi->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbTablePosi->setVisible(true);

    lbTableAngle = new QLabel(this);
    lbTableAngle->setGeometry(SYS_WID(518),SYS_HEI(124) ,SYS_WID(146),SYS_HEI(74));
    lbTableAngle->setStyleSheet("background-color : white ; color : green ;font-size: 36px");
    lbTableAngle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbTableAngle->setVisible(true);

    lbColiXPosi = new QLabel(this);
    lbColiXPosi->setGeometry(SYS_WID(136),SYS_HEI(212) ,SYS_WID(146),SYS_HEI(74));
    lbColiXPosi->setStyleSheet("background-color : white ; color : green ;font-size: 36px");
    lbColiXPosi->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbColiXPosi->setVisible(true);

    lbColiYPosi = new QLabel(this);
    lbColiYPosi->setGeometry(SYS_WID(518),SYS_HEI(212) ,SYS_WID(146),SYS_HEI(74));
    lbColiYPosi->setStyleSheet("background-color : white ; color : green ;font-size: 36px");
    lbColiYPosi->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbColiYPosi->setVisible(true);

    lbCompressor = new QLabel(this);
    lbCompressor->setGeometry(SYS_WID(136),SYS_HEI(302) ,SYS_WID(146),SYS_HEI(74));
    lbCompressor->setStyleSheet("background-color : white ; color : green ;font-size: 36px");
    lbCompressor->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbCompressor->setVisible(true);

    lbRotaryPadel = new QLabel(this);
    lbRotaryPadel->setGeometry(SYS_WID(518),SYS_HEI(302) ,SYS_WID(146),SYS_HEI(74));
    lbRotaryPadel->setStyleSheet("background-color : white ; color : green ;font-size: 36px");
    lbRotaryPadel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbRotaryPadel->setVisible(true);

    lbTubeHeight = new QLabel(this);
    lbTubeHeight->setGeometry(SYS_WID(136),SYS_HEI(398) ,SYS_WID(146),SYS_HEI(74));
    lbTubeHeight->setStyleSheet("background-color : white ; color : green ;font-size: 36px");
    lbTubeHeight->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbTubeHeight->setVisible(true);

    lbTubePosi = new QLabel(this);
    lbTubePosi->setGeometry(SYS_WID(518),SYS_HEI(398) ,SYS_WID(146),SYS_HEI(74));
    lbTubePosi->setStyleSheet("background-color : white ; color : green ;font-size: 36px");
    lbTubePosi->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbTubePosi->setVisible(true);

    lbTextArr.append(lbTubeHeight);
    lbTextArr.append(lbTablePosi);
    lbTextArr.append(lbTubePosi);
    lbTextArr.append(lbTableAngle);
    lbTextArr.append(lbRotaryPadel);
    lbTextArr.append(lbCompressor);
    lbTextArr.append(lbColiXPosi);
    lbTextArr.append(lbColiYPosi);


}
void CMainBaseRf8a::mySceneInit()
{

    RsMgr->g_infoBase->setParent(this);
    RsMgr->g_infoBase->setGeometry( QRect(SYS_WID(0), SYS_HEI(537), SYS_WID(800), SYS_HEI(50)));
    RsMgr->g_infoBase->setVisible(true);
    RsMgr->g_infoBase->raise();
    RsMgr->g_infoBase->setStyleSheet("QWidget{background : transparent;}");


}
void CMainBaseRf8a::myViewInit()
{



}


void CMainBaseRf8a::OnFilmKeyDown(int )
{

}

void CMainBaseRf8a::OnFilmKeyUp(int )
{


}


void CMainBaseRf8a::mousePressEvent(QMouseEvent *event)
{
    //print left button down point.
    qDebug()<< event->pos().x() << event->pos().y();

}


void CMainBaseRf8a::paintEvent(QPaintEvent *)
{

}


void CMainBaseRf8a::OnPopupShow(int )
{

}

void CMainBaseRf8a::OnKeyReleaseCheck()
{

    QDateTime mDt(QDate::currentDate(),QTime::currentTime());
    qint64 mTemp = mDt.toMSecsSinceEpoch();

    if(mTemp - tmKeyReleaseCheck->interval() > mTimeCounter)
    {
        SendRf8KeyRelease(mKeyBufPress);
        tmKeyReleaseCheck->stop();
        mKeyBufPress = 0;
    }
}


void CMainBaseRf8a::keyPressEvent(QKeyEvent * event)
{

    int mKey = event->key();

    QDateTime mDt(QDate::currentDate(),QTime::currentTime());
    mTimeCounter = mDt.toMSecsSinceEpoch();

    if(mKeyBufPress == mKey)
    {
        if(tmKeyReleaseCheck->interval() != RF8A_KEY_DELAY_SHORT)
            tmKeyReleaseCheck->setInterval(RF8A_KEY_DELAY_SHORT);

        return;
    }

    RsMgr->g_filmBase->SetKeySound();

    tmKeyReleaseCheck->setInterval(RF8A_KEY_DELAY_LONG);

    tmKeyReleaseCheck->start();

    if(mKeyBufPress != 0)
        SendRf8KeyRelease(mKeyBufPress);

    mKeyBufPress = mKey;

    SendRf8KeyPress(mKeyBufPress);

}

void CMainBaseRf8a::keyReleaseEvent(QKeyEvent *)
{

    QDateTime mDt(QDate::currentDate(),QTime::currentTime());
    mTimeCounter = mDt.toMSecsSinceEpoch();

}

void CMainBaseRf8a::SendRf8KeyPress(int mKey)
{
    qDebug()<<"key pressed"<<mKey;

    switch(mKey)
    {
    case Qt::Key_A:         //C1
        SendRf8Cmd(RF8A_KEY_TABLE_RIGHT_PRESS);
        break;
    case Qt::Key_D:         //C2
        SendRf8Cmd(RF8A_KEY_TABLE_LEFT_PRESS);
        break;
    case Qt::Key_H:         //C4
        SendRf8Cmd(RF8A_KEY_ANGLE_LEFT_PRESS);
        break;
    case Qt::Key_Apostrophe:    //C13//'//0x27
        SendRf8Cmd(RF8A_KEY_ANGLE_RIGHT_PRESS);
        break;
    case Qt::Key_Q:         //C0
        SendRf8Cmd(RF8A_KEY_COLI_X_OPEN_PRESS);
        break;
    case Qt::Key_E:         //C2
        SendRf8Cmd(RF8A_KEY_COLI_X_CLOSE_PRESS);
        break;
    case Qt::Key_U:         //C4
        SendRf8Cmd(RF8A_KEY_COLI_Y_OPEN_PRESS);
        break;
    case Qt::Key_P:         //C13
        SendRf8Cmd(RF8A_KEY_COLI_Y_CLOSE_PRESS);
        break;
    case Qt::Key_1:         //C0
        SendRf8Cmd(RF8A_KEY_COMPRESSOR_UP_PRESS);
        break;
    case Qt::Key_3:         //C2
        SendRf8Cmd(RF8A_KEY_COMPRESSOR_DOWN_PRESS);
        break;
    case Qt::Key_7:         //C4
        SendRf8Cmd(RF8A_KEY_PEDAL_LEFT_PRESS);
        break;
    case Qt::Key_0:         //C13
        SendRf8Cmd(RF8A_KEY_PEDAL_RIGHT_PRESS);
        break;
    case Qt::Key_Escape:    //C0
        SendRf8Cmd(RF8A_KEY_TUBE_UP_PRESS);
        break;
    case Qt::Key_F4:        //C2
        SendRf8Cmd(RF8A_KEY_TUBE_DOWN_PRESS);
        break;
    case Qt::Key_J:         //C4
        SendRf8Cmd(RF8A_KEY_TUBE_LEFT_PRESS);
        break;
    case Qt::Key_Semicolon: //C13//;//0x3b
        SendRf8Cmd(RF8A_KEY_TUBE_RIGHT_PRESS);
        break;
    default:

        break;
    }
}
void CMainBaseRf8a::SendRf8KeyRelease(int mKey)
{
    qDebug()<<"key released"<<mKey;

    switch(mKey)
    {
    case Qt::Key_A:
        SendRf8Cmd(RF8A_KEY_TABLE_RIGHT_RELEASE);
        break;
    case Qt::Key_D:
        SendRf8Cmd(RF8A_KEY_TABLE_LEFT_RELEASE);
        break;
    case Qt::Key_H:
        SendRf8Cmd(RF8A_KEY_ANGLE_LEFT_RELEASE);
        break;
    case Qt::Key_Apostrophe:
        SendRf8Cmd(RF8A_KEY_ANGLE_RIGHT_RELEASE);
        break;
    case Qt::Key_Q:
        SendRf8Cmd(RF8A_KEY_COLI_X_OPEN_RELEASE);
        break;
    case Qt::Key_E:
        SendRf8Cmd(RF8A_KEY_COLI_X_CLOSE_RELEASE);
        break;
    case Qt::Key_U:
        SendRf8Cmd(RF8A_KEY_COLI_Y_OPEN_RELEASE);
        break;
    case Qt::Key_P:
        SendRf8Cmd(RF8A_KEY_COLI_Y_CLOSE_RELEASE);
        break;
    case Qt::Key_1:
        SendRf8Cmd(RF8A_KEY_COMPRESSOR_UP_RELEASE);
        break;
    case Qt::Key_3:
        SendRf8Cmd(RF8A_KEY_COMPRESSOR_DOWN_RELEASE);
        break;
    case Qt::Key_7:
        SendRf8Cmd(RF8A_KEY_PEDAL_LEFT_RELEASE);
        break;
    case Qt::Key_0:
        SendRf8Cmd(RF8A_KEY_PEDAL_RIGHT_RELEASE);
        break;
    case Qt::Key_Escape:
        SendRf8Cmd(RF8A_KEY_TUBE_UP_RELEASE);
        break;
    case Qt::Key_F4:
        SendRf8Cmd(RF8A_KEY_TUBE_DOWN_RELEASE);
        break;
    case Qt::Key_J:
        SendRf8Cmd(RF8A_KEY_TUBE_LEFT_RELEASE);
        break;
    case Qt::Key_Semicolon:
        SendRf8Cmd(RF8A_KEY_TUBE_RIGHT_RELEASE);
        break;
    default:

        break;
    }

}
void CMainBaseRf8a::showEvent(QShowEvent * )
{

    tmDataFresh->start();

    grabKeyboard();
}
void CMainBaseRf8a::hideEvent(QHideEvent * )
{
    tmDataFresh->stop();

    releaseKeyboard();
}

void CMainBaseRf8a::OnViewChange(int view)
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


void CMainBaseRf8a::OnRf8aDataFresh()
{

    if(++mKeepAliveCtr >= 4)
    {
        unsigned short keyBuf[8];
        keyBuf[0] = CMD_KEEP_ALIVE_DATA;
        g_taskComCtrl->CreateTask(CMD_KEEP_ALIVE_HEADER,keyBuf,1);

        mKeepAliveCtr = 0;
    }


    lbTubeHeight->setNum(g_systemDb->g_dbMachine.CurrentData[RF8A_MOTOR_FID]);
    lbTablePosi->setNum(g_systemDb->g_dbMachine.CurrentData[RF8A_MOTOR_DTP]);
    lbTubePosi->setNum(g_systemDb->g_dbMachine.CurrentData[RF8A_MOTOR_SID]);
    lbTableAngle->setNum(g_systemDb->g_dbMachine.CurrentData[RF8A_MOTOR_ANG]);
    lbRotaryPadel->setNum(g_systemDb->g_dbMachine.CurrentData[RF8A_MOTOR_PRL]);
    lbCompressor->setNum(g_systemDb->g_dbMachine.CurrentData[RF8A_MOTOR_PYP]);
    lbColiXPosi->setNum(g_systemDb->g_dbMachine.CurrentData[RF8A_MOTOR_SGH]);
    lbColiYPosi->setNum(g_systemDb->g_dbMachine.CurrentData[RF8A_MOTOR_SGV]);
}
