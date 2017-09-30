#include "system_light_curtain.h"
#include "sys_database.h"
#include "resource_manager.h"

CSystemLightCurtain::CSystemLightCurtain( QWidget* parent ):
    CSystemBase(parent)
{     

    setObjectName("CSystemLightCurtain");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemLightCurtain", "Light Curtain Setting"));

    m_iLightCurtainState    =   0;       //on == 1 ; off == 0
    m_iLightCurtainHold     = 0;       //on == 1 ; off == 0
    m_iLightCurtainShow     = 0;       //on == 1 ; off == 0

    m_iLCHeightBase     = 0;
    m_iLCSample             = 0;
    m_iLCHumanHeight    = 0;
    m_iLCChestHeight    = 0;

    staticMsgReceive = new QLabel(this);
    staticMsgReceive->setGeometry(20,550,145,50);

    btnLightCurtainOn = new CButtonStable(this);
    btnLightCurtainOn->setGeometry(40,80,100,60);
    btnLightCurtainOn->setText(QApplication::translate("CSystemLightCurtain", "ON"));

    btnLightCurtainOff = new CButtonStable(this);
    btnLightCurtainOff->setGeometry(180,80,100,60);
    btnLightCurtainOff->setText(QApplication::translate("CSystemLightCurtain", "OFF"));

    btnLightCurtainHold = new CButtonStable(this);
    btnLightCurtainHold->setGeometry(320,80,100,60);
    btnLightCurtainHold->setText(QApplication::translate("CSystemLightCurtain", "HOLD"));

    btnLightCurtainShow = new CButtonStable(this);
    btnLightCurtainShow->setGeometry(460,80,100,60);
    btnLightCurtainShow->setText(QApplication::translate("CSystemLightCurtain", "SHOW"));

    staticHeightBase = new QLabel(this);
    staticHeightBase->setGeometry(20,180,145,55);
    staticHeightBase->setText(QApplication::translate("CSystemLightCurtain", "BASE HEIGHT:"));

    pEditArr[LC_INDEX_HEIGHT_BASE] = new QLabel(this);
    pEditArr[LC_INDEX_HEIGHT_BASE]->setGeometry(200,180,100,45);
    pEditArr[LC_INDEX_HEIGHT_BASE]->setStyleSheet("color : green ; background-color : white ;border : 2px solid blue");
    pEditArr[LC_INDEX_HEIGHT_BASE]->installEventFilter(this);

    staticCM_0 = new QLabel(this);
    staticCM_0->setGeometry(310,180,145,55);
    staticCM_0->setText(QApplication::translate("CSystemLightCurtain", "CM"));

    btSave = new CButtonStable(this);
    btSave->setGeometry(460,177,100,50);
    btSave->setText(QApplication::translate("CSystemLightCurtain", "SAVE"));

    staticSampleValue = new QLabel(this);
    staticSampleValue->setGeometry(20,240,145,55);
    staticSampleValue->setText(QApplication::translate("CSystemLightCurtain", "SAMPLE:"));

    strSampleValue = new QLabel(this);
    strSampleValue->setGeometry(200,240,100,45);
    strSampleValue->setStyleSheet("color : green ; background-color : yellow ;border : 1px solid black");

    staticHumanHeight = new QLabel(this);
    staticHumanHeight->setGeometry(20,300,145,55);
    staticHumanHeight->setText(QApplication::translate("CSystemLightCurtain", "HUMAN HEIGHT:"));

    strHumanHeight = new QLabel(this);
    strHumanHeight->setGeometry(200,300,100,45);
    strHumanHeight->setStyleSheet("color : green ; background-color : yellow ;border : 1px solid black");

    staticCM_1 = new QLabel(this);
    staticCM_1->setGeometry(310,300,145,55);
    staticCM_1->setText(QApplication::translate("CSystemLightCurtain", "CM"));

    staticChestHeight = new QLabel(this);
    staticChestHeight->setGeometry(20,360,145,55);
    staticChestHeight->setText(QApplication::translate("CSystemLightCurtain", "CHEST HEIGHT:"));

    strChestHeight = new QLabel(this);
    strChestHeight->setGeometry(200,360,100,45);
    strChestHeight->setStyleSheet("color : green ; background-color : yellow ;border : 1px solid black");

    staticCM_2 = new QLabel(this);
    staticCM_2->setGeometry(310,360,145,55);
    staticCM_2->setText(QApplication::translate("CSystemLightCurtain", "CM"));

    strMessage = new QLabel(this);
    strMessage->setGeometry(0,420,600,55);
    strMessage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    m_tmLightCurtain = new QTimer(this);
    m_tmLightCurtain->setInterval(SYS_LIGHT_CURTAIN_FRESH);

    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnBtnExit()));
    connect(m_tmLightCurtain,SIGNAL(timeout()),this,SLOT(OnTimerLightCurtain()));
    connect(btnLightCurtainOn,SIGNAL(pressed()),this,SLOT(OnBtnCtrl()));
    connect(btnLightCurtainOff,SIGNAL(pressed()),this,SLOT(OnBtnCtrl()));
    connect(btnLightCurtainHold,SIGNAL(pressed()),this,SLOT(OnBtnCtrl()));
    connect(btnLightCurtainShow,SIGNAL(pressed()),this,SLOT(OnBtnCtrl()));
    connect(btSave,SIGNAL(pressed()),this,SLOT(OnBtnSaveData()));

    translateFontSize( this );

    setVisible(false);
}


void CSystemLightCurtain::showEvent(QShowEvent * event)
{  

    m_iLightCurtainState = g_mainCfg->value("utility/LightCurtainState","0").toInt();
    m_iLightCurtainHold = g_mainCfg->value("utility/LightCurtainHold","0").toInt();
    m_iLightCurtainShow = g_mainCfg->value("utility/LightCurtainShow","0").toInt();

    if(m_iLightCurtainState == 1)
    {
        btnLightCurtainOn->setStyleSheet("background-color : cyan ; border : 2px solid green");
        btnLightCurtainOff->setStyleSheet("background-color : lightGray");
    }else
    {
        btnLightCurtainOn->setStyleSheet("background-color : lightGray");
        btnLightCurtainOff->setStyleSheet("background-color : cyan ; border : 2px solid green");
    }

    if(m_iLightCurtainHold == 1)
        btnLightCurtainHold->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnLightCurtainHold->setStyleSheet("background-color : lightGray");

    if(m_iLightCurtainShow == 1)
        btnLightCurtainShow->setStyleSheet("background-color : cyan ; border : 2px solid green");
    else
        btnLightCurtainShow->setStyleSheet("background-color : lightGray");

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad = new CSystemImepad(this);

    g_systemDb->g_bDataSaved = false;

    m_tmLightCurtain->start();//start the fresh timer.

    m_iBaseHeightFreshEnable = true;    //default enable base height fresh

    g_systemDb->g_ctrLightCurtainMsg = 0;

    CSystemBase::showEvent(event);
}

void CSystemLightCurtain::hideEvent(QHideEvent *event)
{


    m_tmLightCurtain->stop();

    CSystemBase::hideEvent(event);
}
bool CSystemLightCurtain::eventFilter(QObject *watched, QEvent *event)
{

    for(int mIdx = 0 ;mIdx < LC_EDIT_MAX ; mIdx++)
    {
        if(pEditArr[mIdx] == watched)
        {
            if(event->type()==QEvent::MouseButtonPress)
            {
                g_systemPad->move(220 ,220 + mIdx * 15);

                g_systemPad->show();

                m_iFocusCurrent = mIdx;
                m_strKeyBuff = "";
                strMessage->setText("");    //clear error when new input

                m_iBaseHeightFreshEnable = false;   //stop fresh of base height
            }
        }
    }

    return QWidget::eventFilter(watched,event);
}

void CSystemLightCurtain::keyPressEvent ( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Backspace)                                                              //判断是否是退格键
    {
        int iStrLen = m_strKeyBuff.length();

        if(iStrLen > 0)
        {
            m_strKeyBuff.remove( iStrLen - 1,1);
            pEditArr[m_iFocusCurrent]->setText(m_strKeyBuff);
        }else
            pEditArr[m_iFocusCurrent]->setText("");

    }else if(event->key() == Qt::Key_Close)
    {
    }else
    {
        if(m_strKeyBuff.length() <LC_MAX_LENGTH)
            m_strKeyBuff.append(event->key());

        pEditArr[m_iFocusCurrent]->setText(m_strKeyBuff);
    }

    strMessage->setText("");    //clear error when new input
}

void CSystemLightCurtain::OnBtnSaveData()
{
    unsigned short  buf[16];

    m_iBaseHeightFreshEnable = true;    //enable base height fresh

    if(sender() == btSave)
    {

        buf[0] =0;
        buf[1] =LC_CMD_SAVE;
        buf[2] =pEditArr[LC_INDEX_HEIGHT_BASE]->text().toInt();
        //check height base data valid.
        if(buf[2] <1 || buf[2] > 5000)
        {
            strMessage->setStyleSheet("color : red;");
            strMessage->setText(QApplication::translate("CSystemLightCurtain", "Invalid input data!"));
            return;
        }
        g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

    }
}
void CSystemLightCurtain::OnBtnExit()
{
    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemAdvance);
    }
}
void CSystemLightCurtain::OnBtnCtrl()
{
    unsigned short  buf[16];

    if(sender() == btnLightCurtainOn)
    {
        m_iLightCurtainState = 1;
        btnLightCurtainOn->setStyleSheet("background-color : cyan ; border : 2px solid green");
        btnLightCurtainOff->setStyleSheet("background-color : lightGray");

        buf[0] =0;
        buf[1] =LC_CMD_ON;
        g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

        g_mainCfg->setValue("utility/LightCurtainState",m_iLightCurtainState);
    }

    if(sender() == btnLightCurtainOff)
    {
        m_iLightCurtainState = 0;
        btnLightCurtainOn->setStyleSheet("background-color : lightGray");
        btnLightCurtainOff->setStyleSheet("background-color : cyan ; border : 2px solid green");

        buf[0] =0;
        buf[1] =LC_CMD_OFF;
        g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

        g_mainCfg->setValue("utility/LightCurtainState",m_iLightCurtainState);
    }

    if(sender() == btnLightCurtainHold)
    {
        if(m_iLightCurtainHold == 0)
        {
            m_iLightCurtainHold = 1;
            btnLightCurtainHold->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }else
        {
            m_iLightCurtainHold = 0;
            btnLightCurtainHold->setStyleSheet("background-color : lightGray");
        }
        g_mainCfg->setValue("utility/LightCurtainHold",m_iLightCurtainHold);
    }

    if(sender() == btnLightCurtainShow)
    {
        if(m_iLightCurtainShow == 0)
        {
            m_iLightCurtainShow = 1;
            btnLightCurtainShow->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }else
        {
            m_iLightCurtainShow = 0;
            btnLightCurtainShow->setStyleSheet("background-color : lightGray");
        }
        g_mainCfg->setValue("utility/LightCurtainShow",m_iLightCurtainShow);
    }
}

void CSystemLightCurtain::OnTimerLightCurtain()
{

    unsigned short  buf[16];
    buf[0] =0;
    buf[1] =LC_CMD_FRESH;
    g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

    if(m_iBaseHeightFreshEnable)
    {
        m_iLCHeightBase = g_systemDb->g_iArrLightCurtain[0];
        pEditArr[LC_INDEX_HEIGHT_BASE]->setText(QString::number(m_iLCHeightBase));
    }
    /*
    if(!g_systemPad->isVisible())
    {
        m_iLCHeightBase = g_systemDb->g_iArrLightCurtain[0];
        pEditArr[LC_INDEX_HEIGHT_BASE]->setText(QString::number(m_iLCHeightBase));
    }
    */
    /*
    if(m_iLCHeightBase != g_systemDb->g_iArrLightCurtain[0])
    {
        m_iLCHeightBase = g_systemDb->g_iArrLightCurtain[0];
        pEditArr[LC_INDEX_HEIGHT_BASE]->setText(QString::number(m_iLCHeightBase));
    }
*/
    if(m_iLightCurtainState != g_systemDb->g_iArrLightCurtain[1])
    {
        m_iLightCurtainState = g_systemDb->g_iArrLightCurtain[1];

        if(m_iLightCurtainState == 1)
        {
            btnLightCurtainOn->setStyleSheet("background-color : cyan ; border : 2px solid green");
            btnLightCurtainOff->setStyleSheet("background-color : lightGray");
        }else
        {
            btnLightCurtainOn->setStyleSheet("background-color : lightGray");
            btnLightCurtainOff->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }
    }

    m_iLCSample = g_systemDb->g_iArrLightCurtain[2];
    strSampleValue->setText(QString::number(m_iLCSample));

    m_iLCHumanHeight = g_systemDb->g_iArrLightCurtain[3];
    strHumanHeight->setText(QString::number(m_iLCHumanHeight));

    m_iLCChestHeight = g_systemDb->g_iArrLightCurtain[4];
    strChestHeight->setText(QString::number(m_iLCChestHeight));

    staticMsgReceive->setText(QApplication::translate("CSystemLightCurtain", "MSG Counter:") + QString::number(g_systemDb->g_ctrLightCurtainMsg));
}
