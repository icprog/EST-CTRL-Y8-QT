#include "system_advance.h"
#include "resource_manager.h"


CSystemAdvance::CSystemAdvance(QWidget *parent) :
    CSystemBase(parent)
{

    setObjectName("CSystemAdvance");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemAdvance", "Advanced settings"));

    btnShutDown = new CButtonStable(this);
    btnShutDown->setGeometry(QRect(20, 60, 160, 70));

    btnNetWork = new CButtonStable(this);
    btnNetWork->setGeometry(QRect(20, 150, 160, 70));

    btnSimCtrl = new CButtonStable(this);
    btnSimCtrl->setGeometry(QRect(20, 240, 160, 70));

    btnAutoRotate = new CButtonStable(this);
    btnAutoRotate->setGeometry(QRect(20, 330, 160, 70));

    btnCursorShow = new CButtonStable(this);
    btnCursorShow->setGeometry(QRect(200, 60, 160, 70));

    btnTubeTemp = new CButtonStable(this);
    btnTubeTemp->setGeometry(QRect(200, 150, 160, 70));

    btnGenShow = new CButtonStable(this);
    btnGenShow->setGeometry(QRect(200, 240, 160, 70));

    btnSmartShow = new CButtonStable(this);
    btnSmartShow->setGeometry(QRect(200, 330, 160, 70));

    btnKeyFilmCtrl = new CButtonStable(this);
    btnKeyFilmCtrl->setGeometry(QRect(380, 60, 160, 70));

    btnKeyScreenCtrl = new CButtonStable(this);
    btnKeyScreenCtrl->setGeometry(QRect(380, 150, 160, 70));

    btnKeyProtocol = new CButtonStable(this);
    btnKeyProtocol->setGeometry(QRect(380, 240, 160, 70));

    btnLightCurtain = new CButtonStable(this);
    btnLightCurtain->setGeometry(QRect(20, 420, 160, 70));

    btnSystemReset = new CButtonStable(this);
    btnSystemReset->setGeometry(QRect(380, 420, 160, 70));
    btnSystemReset->setStyleSheet("background-color:red ; border : 2px solid black");

    btnShutDown->setText(QApplication::translate("CSystemAdvance", "Shutdown Show"));
    btnNetWork->setText(QApplication::translate("CSystemAdvance", "Network Show"));
    btnSimCtrl->setText(QApplication::translate("CSystemAdvance", "Simulate Show"));
    btnAutoRotate->setText(QApplication::translate("CSystemAdvance", "Auto Rotate"));
    btnCursorShow->setText(QApplication::translate("CSystemAdvance", "Cursor Show"));
    btnTubeTemp->setText(QApplication::translate("CSystemAdvance", "Tube Temp. Show"));
    btnSystemReset->setText(QApplication::translate("CSystemAdvance", "System Reset"));
    btnGenShow->setText(QApplication::translate("CSystemAdvance", "Generator Show"));
    btnSmartShow->setText(QApplication::translate("CSystemAdvance", "Smart Show"));
    btnKeyFilmCtrl->setText(QApplication::translate("CSystemAdvance", "Film Key Control"));
    btnKeyScreenCtrl->setText(QApplication::translate("CSystemAdvance", "Screen Key Control"));
    btnLightCurtain->setText(QApplication::translate("CSystemAdvance", "Light Curtain"));

    connect(btnShutDown,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnNetWork,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnSimCtrl,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnAutoRotate,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnCursorShow,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnTubeTemp,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnGenShow,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnSmartShow,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnKeyFilmCtrl,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnKeyScreenCtrl,SIGNAL(pressed()),this,SLOT(OnStateChanged()));
    connect(btnKeyProtocol,SIGNAL(pressed()),this,SLOT(OnProtocolChange()));
    connect(btnLightCurtain,SIGNAL(pressed()),this,SLOT(OnLightCurtainCtrl()));

    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnButtonPressed()));
    connect(btnSystemReset,SIGNAL(pressed()),this,SLOT(OnButtonPressed()));

    translateFontSize( this );

    msgBox = new CDialogConFirm(this);
    msgBox->raise();
}

void CSystemAdvance::OnButtonPressed()
{
    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        return;
    }

    if(sender() == btnSystemReset)
    {

        if(! g_systemDb->m_bCanUpdate)
        {
             btnSystemReset->setText(QApplication::translate("CSystemAdvance", "Function Disabled"));
            return;
        }

        QString mStrTitle  = QApplication::translate("CSystemAdvance", "Critical Warning!");
        QString mStrText  = QApplication::translate("CSystemAdvance", "System reset will delete all user data!\nThis Function is for Engineer use only!\nEnd user please choose Cancel!");

        msgBox->setIcon(SYS_STR_CRITICAL);
        msgBox->setTitle(mStrTitle);
        msgBox->setText(mStrText);

        mBtnNo = msgBox->addButton(QApplication::translate("CSystemAdvance", "Cancel"));
        mBtnYes = msgBox->addButton(QApplication::translate("CSystemAdvance", "Yes"));

        msgBox->disconnect();
        connect(msgBox,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(OnConfirmClicked(QAbstractButton*)));
        msgBox->show();

        return;
    }
}
void CSystemAdvance::OnConfirmClicked(QAbstractButton * btnRes)
{
    if(mBtnYes == btnRes)
    {
        SystemReset();
    }
}

void CSystemAdvance::SystemReset()
{
    QString mStrTitle = QApplication::translate("CSystemAdvance", "Critical Warning!");
    QString mStrText  = QApplication::translate("CSystemAdvance", "No Configuration file in udisk!");

    //confirm
    QString mStrFilePath;
    switch(g_dbsys.utility.mPlatform)
    {
    case PF_CEIL_10_A:
        mStrFilePath = "/udisk/estmedcarefirmware/hmx8000";
        break;
    case PF_CEIL_10_B:
        mStrFilePath = "/udisk/estmedcarefirmware/hmx8040";
        break;
    case PF_CEIL_08_A:
        mStrFilePath = "/udisk/estmedcarefirmware/hmx8001";
        break;
    case PF_UARM_10_A:
        mStrFilePath = "/udisk/estmedcarefirmware/hmx8020";
        break;
    case PF_UARM_08_A:
        mStrFilePath = "/udisk/estmedcarefirmware/hmx8021";
        break;
    case PF_RAIL_12_A:
        mStrFilePath = "/udisk/estmedcarefirmware/hmx8010";
        break;
    case PF_RAIL_08_A:
        mStrFilePath = "/udisk/estmedcarefirmware/hmx8011";
        break;
    default:
        mStrFilePath = "/udisk/estmedcarefirmware/hmx8000";
        break;
    }

    if (! QFile::exists(mStrFilePath))
    {
        msgBox->setIcon(SYS_STR_WARNING);
        msgBox->setTitle(mStrTitle);
        msgBox->setText(mStrText);

        msgBox->disconnect();
        mBtnNo = msgBox->addButton(QApplication::translate("CSystemAdvance", "Cancel"));

        msgBox->show();
        msgBox->raise();

        return;
    }

    MySystem("rm /sdcard/home/fa/medcare.dat");
    MySystem("rm /sdcard/home/fa/medcare.ini");
    MySystem("rm /sdcard/home/fa/fastdata0.dat");
    MySystem("rm /sdcard/home/fa/fastdata1.dat");
    MySystem("rm /sdcard/home/fa/fastdata2.dat");
    MySystem("rm /etc/pointercal");

    int m_iPlatformTarget = g_dbsys.utility.mPlatform;                    //backup
    g_systemDb->Init_DataBase();

    g_dbsys.utility.mPlatform = m_iPlatformTarget;
    g_systemDb->SaveSystemCfg("utility/mPlatform",g_dbsys.utility.mPlatform);

    MySystem("reboot");
}
void CSystemAdvance::OnStateChanged()
{
    if(btnKeyFilmCtrl == sender())
    {
        if(g_dbsys.utility.mFilmKeyEnable)
        {
            g_dbsys.utility.mFilmKeyEnable = false;
            btnKeyFilmCtrl->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mFilmKeyEnable = true;
            btnKeyFilmCtrl->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mFilmKeyEnable",g_dbsys.utility.mFilmKeyEnable);
        return;
    }

    if(btnKeyScreenCtrl == sender())
    {
        if(g_dbsys.utility.mScreenKeyEnable)
        {
            g_dbsys.utility.mScreenKeyEnable = false;
            btnKeyScreenCtrl->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mScreenKeyEnable = true;
            btnKeyScreenCtrl->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mScreenKeyEnable",g_dbsys.utility.mScreenKeyEnable);
        return;
    }

    if(btnShutDown == sender())
    {
        if(g_dbsys.utility.mShutdownShow)
        {
            g_dbsys.utility.mShutdownShow = false;
            btnShutDown->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mShutdownShow = true;
            btnShutDown->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mShutdownShow",g_dbsys.utility.mShutdownShow);
        return;
    }

    if(btnNetWork == sender())
    {
        if(g_dbsys.utility.mNetShow)
        {
            g_dbsys.utility.mNetShow = false;
            btnNetWork->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mNetShow = true;
            btnNetWork->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mNetShow",g_dbsys.utility.mNetShow);
        return;
    }

    if(btnSimCtrl == sender())
    {
        if(g_dbsys.utility.mSimulate)
        {
            g_dbsys.utility.mSimulate = false;
            btnSimCtrl->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mSimulate = true;
            btnSimCtrl->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mSimulate",g_dbsys.utility.mSimulate);
        return;
    }

    if(btnAutoRotate == sender())
    {
        if(g_dbsys.utility.mAutoRotate)
        {
            g_dbsys.utility.mAutoRotate = false;
            btnAutoRotate->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mAutoRotate = true;
            btnAutoRotate->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mAutoRotate",g_dbsys.utility.mAutoRotate);
        return;
    }

    if(btnCursorShow == sender())
    {
        if(g_dbsys.utility.mCursorShow)
        {
            g_dbsys.utility.mCursorShow = false;
            btnCursorShow->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mCursorShow = true;
            btnCursorShow->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mCursorShow",g_dbsys.utility.mCursorShow);
        return;
    }

    if(btnTubeTemp == sender())
    {
        if(g_dbsys.utility.mTubeTempShow)
        {
            g_dbsys.utility.mTubeTempShow = false;
            btnTubeTemp->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mTubeTempShow = true;
            btnTubeTemp->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mTubeTempShow",g_dbsys.utility.mTubeTempShow);
        return;
    }

    if(btnGenShow == sender())
    {
        if(g_dbsys.utility.mGeneratorShow)
        {
            g_dbsys.utility.mGeneratorShow = false;
            btnGenShow->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mGeneratorShow = true;
            btnGenShow->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mGeneratorShow",g_dbsys.utility.mGeneratorShow);
        return;

    }

    if(btnSmartShow == sender())
    {
        if(g_dbsys.utility.mSmartShow)
        {
            g_dbsys.utility.mSmartShow = false;
            btnSmartShow->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        }else
        {
            g_dbsys.utility.mSmartShow = true;
            btnSmartShow->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }

        g_systemDb->SaveSystemCfg("utility/mSmartShow",g_dbsys.utility.mSmartShow);
        return;
    }

}
void CSystemAdvance::showEvent(QShowEvent *event)
{

    btnLightCurtain->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mShutdownShow)
        btnShutDown->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnShutDown->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mNetShow)
        btnNetWork->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnNetWork->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mSimulate)
        btnSimCtrl->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnSimCtrl->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mAutoRotate)
        btnAutoRotate->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnAutoRotate->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mCursorShow)
        btnCursorShow->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnCursorShow->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mTubeTempShow)
        btnTubeTemp->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnTubeTemp->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mGeneratorShow)
        btnGenShow->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnGenShow->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mSmartShow)
        btnSmartShow->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnSmartShow->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mFilmKeyEnable)
        btnKeyFilmCtrl->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnKeyFilmCtrl->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mScreenKeyEnable)
        btnKeyScreenCtrl->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnKeyScreenCtrl->setStyleSheet("background-color : lightGray ; border : 2px solid black");

    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_00)
    {
        btnKeyProtocol->setText(QApplication::translate("CSystemAdvance", "2 Channel Smart"));
        btnKeyProtocol->setStyleSheet("background-color : cyan ; border : 2px solid green");
    }
    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_01)
    {
        btnKeyProtocol->setText(QApplication::translate("CSystemAdvance", "8 Channel Smart"));
        btnKeyProtocol->setStyleSheet("background-color : cyan ; border : 2px solid green");
    }

    grabKeyboard();

    CSystemBase::showEvent(event);
}
void CSystemAdvance::hideEvent(QHideEvent *event)
{

    releaseKeyboard();

    CSystemBase::hideEvent(event);
}

void CSystemAdvance::keyPressEvent( QKeyEvent * event )
{
    int mKey = event->key();
    switch (mKey) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        break;

    case Qt::Key_Backspace:
        break;
    case Qt::Key_Close:
        break;
    case Qt::Key_Escape:
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        break;
    case Qt::Key_Tab:
        break;
    default:
        break;
    }
}

void CSystemAdvance::OnProtocolChange()
{

    if(  g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_00)
    {
        btnKeyProtocol->setText(QApplication::translate("CSystemAdvance", "8 Channel Smart"));
        btnKeyProtocol->setStyleSheet("background-color : cyan ; border : 2px solid green");
        g_dbsys.utility.mCommProtocol = COMM_PROTOCOL_01;

    }else if( g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_01)
    {
        btnKeyProtocol->setText(QApplication::translate("CSystemAdvance", "2 Channel Smart"));
        btnKeyProtocol->setStyleSheet("background-color : cyan ; border : 2px solid green");
        g_dbsys.utility.mCommProtocol = COMM_PROTOCOL_00;
    }

    g_systemDb->SaveSystemCfg("utility/mCommProtocol",g_dbsys.utility.mCommProtocol);
    return;

}

void CSystemAdvance::OnLightCurtainCtrl()
{

    if(sender() == btnLightCurtain )
    {

        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemLightCurtain);
        return;
    }

}
