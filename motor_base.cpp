#include <QSettings>
#include <QFile>

#include "motor_base.h"
#include "resource_manager.h"

#define FOCUS_IDX_EDIT_MIN       ( 0 )
#define FOCUS_IDX_BTN_MIN        ( 1 )
#define FOCUS_IDX_EDIT_MAX       ( 2 )
#define FOCUS_IDX_BTN_MAX        ( 3 )

#define CAL_CUR           ( 0 )
#define CAL_MIN           ( 1 )
#define CAL_MAX           ( 2 )

#define CMD_UP_PRESS      ( 0 )
#define CMD_UP_RELEASE    ( 1 )
#define CMD_DOWN_PRESS    ( 2 )
#define CMD_DOWN_RELEASE  ( 3 )
#define CMD_SAVE_MIN      ( 4 )
#define CMD_SAVE_MAX      ( 5 )

CMotorBase::CMotorBase(int mPlatform,int motor,QWidget *parent) :
    CSystemBase(parent)
{

    setObjectName("CMotorBase");

    resize(600,600);

    lbSample = new QLabel(this);
    lbSample->setGeometry(QRect(330, 70, 161, 28));

    edElectronicScale = new QLabel(this);
    edElectronicScale->setGeometry(QRect(500, 70, 80, 28));
    edElectronicScale->setStyleSheet("background-color : yellow ; color : red; border : 1px solid black");
    edElectronicScale->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    lbMinSave = new QLabel(this);
    lbMinSave->setGeometry(QRect(345, 210, 150, 50));
    lbMinSave->setText(QApplication::translate("CMotorBase", "Save Successful!"));
    lbMinSave->setStyleSheet("color : red");

    lbMaxSave = new QLabel(this);
    lbMaxSave->setGeometry(QRect(345, 410, 150, 50));
    lbMaxSave->setText(QApplication::translate("CMotorBase", "Save Successful!"));
    lbMaxSave->setStyleSheet("color : red");

    lbMinTitle = new QLabel(this);
    lbMinTitle->setGeometry(QRect(20, 100, 451, 28));

    lbMinInfo1 = new QLabel(this);
    lbMinInfo1->setGeometry(QRect(20, 130, 451, 28));

    lbMinInfo2 = new QLabel(this);
    lbMinInfo2->setGeometry(QRect(110, 170, 381, 32));

    lbMaxTitle = new QLabel(this);
    lbMaxTitle->setGeometry(QRect(20, 290, 341, 28));

    lbMaxInfo1 = new QLabel(this);
    lbMaxInfo1->setGeometry(QRect(20, 320, 461, 34));

    lbMaxInfo2 = new QLabel(this);
    lbMaxInfo2->setGeometry(QRect(110, 360, 381, 32));

    QLabel * pLabel;
    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(20, 170, 80, 42));
    pLabel->setStyleSheet("background-color : white ; color : darkCyan;border : 3px solid green");
    pWidArr.push_back(pLabel);

    CButtonStable * pBtn;
    pBtn = new CButtonStable(this);
    pBtn->setGeometry(QRect(240, 205, 100, 60));
    pBtn->setText(QApplication::translate("CMotorBase", "SAVE"));
    pBtn->setStyleSheet("border : 2px solid black");
    pBtn->setFocusPolicy(Qt::NoFocus);
    connect(pBtn,SIGNAL(pressed()),this,SLOT(OnBtnClickSaveMin()) );
    pWidArr.push_back(pBtn);

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(20, 360, 80, 42));
    pLabel->setStyleSheet("background-color : white ; color : darkCyan;border : 2px solid black");
    pWidArr.push_back(pLabel);

    pWidArr.at(FOCUS_IDX_EDIT_MIN)->installEventFilter(this);
    pWidArr.at(FOCUS_IDX_EDIT_MAX)->installEventFilter(this);

    pBtn = new CButtonStable(this);
    pBtn->setGeometry(QRect(240, 405, 100, 60));
    pBtn->setText(QApplication::translate("CMotorBase", "SAVE"));
    pBtn->setStyleSheet("border : 2px solid black");
    pBtn->setFocusPolicy(Qt::NoFocus);
    connect(pBtn,SIGNAL(pressed()),this,SLOT(OnBtnClickSaveMax()) );
    pWidArr.push_back(pBtn);

    btPositionDown  = new CButtonStable(this);
    btPositionDown->setGeometry(QRect(500, 300, 80, 80));
    btPositionDown->setFocusPolicy(Qt::NoFocus);
    btPositionDown->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INDEX_DOWN"));
    connect(btPositionDown,   SIGNAL(pressed()),this,SLOT(OnButtonPressed()) );
    connect(btPositionDown,   SIGNAL(released()),this,SLOT(OnButtonReleased()) );

    btPositionUp    = new CButtonStable(this);
    btPositionUp->setGeometry(QRect(500, 200, 80, 80));
    btPositionUp->setFocusPolicy(Qt::NoFocus);
    btPositionUp->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INDEX_UP"));
    connect(btPositionUp,     SIGNAL(pressed()),this,SLOT(OnButtonPressed()) );
    connect(btPositionUp,     SIGNAL(released()),this,SLOT(OnButtonReleased()) );

    btBack = new CButtonStable(this);
    btBack->setGeometry(QRect(70, 525, 110, 60));
    btBack->setFocusPolicy(Qt::NoFocus);
    btBack->setText(QApplication::translate("CMotorBase", "BACK"));
    connect(btBack,   SIGNAL(pressed()),this,SLOT(OnBtnClickIndex()) );

    btNext = new CButtonStable(this);
    btNext->setGeometry(QRect(420, 525, 110, 60));
    btNext->setFocusPolicy(Qt::NoFocus);
    btNext->setText(QApplication::translate("CMotorBase", "NEXT"));
    connect(btNext,   SIGNAL(pressed()),this,SLOT(OnBtnClickIndex()) );

    tmDataRefresh = new QTimer();
    connect(tmDataRefresh,SIGNAL(timeout()),this,SLOT(OnMotorRefresh()));
    connect(btnExit,   SIGNAL(pressed()),this,SLOT(OnBtnClickIndex()) );

    m_iFocusCurrent         = 0;
    // m_iSaveBtnIdx       = FOCUS_IDX_NULL;
    m_iMotorIdx         = motor;

    switch(mPlatform)
    {
    case PF_NDT_8_A:
        InitNdt8aMotor(motor);                       //初始化为不同的电机
        InitNdt8aData();
        break;
    case PF_RF_8_A:
        InitRf8aMotor(motor);                       //初始化为不同的电机
        InitRf8aData();
        break;
    case PF_NDT_10_A:
    case PF_CEIL_10_A:
        InitCeil10aMotor(motor);                       //初始化为不同的电机
        InitCeil10aData();
        break;
    case PF_CEIL_10_B:
        InitCeil10bMotor(motor);                       //初始化为不同的电机
        InitCeil10bData();
        break;
    case PF_CEIL_08_A:
        InitCeil8Motor(motor);                       //初始化为不同的电机
        InitCeil8Data();
        break;
    case PF_UARM_10_A:
        InitUarm10Motor(motor);                       //初始化为不同的电机
        InitUarm10Data();
        break;
    case PF_UARM_08_A:
        InitUarm8Motor(motor);                       //初始化为不同的电机
        InitUarm8Data();
        break;
    case PF_RAIL_12_A:
        InitRail10Motor(motor);                       //初始化为不同的电机
        InitRail10Data();
        break;
    case PF_RAIL_08_A:
        InitRail8Motor(motor);                       //初始化为不同的电机
        InitRail8Data();
        break;
    default:
        InitCeil10aMotor(motor);                       //初始化为不同的电机
        InitCeil10aData();
        break;
    }

    m_iIdxCur           = m_iDataIdx[motor][CAL_CUR];
    m_iIdxMin           = m_iDataIdx[motor][CAL_MIN];
    m_iIdxMax           = m_iDataIdx[motor][CAL_MAX];

    translateFontSize( this );

    setVisible(false);

    setStyleSheet("background-color : lightGray");
}

void CMotorBase::SendCmdKey(int mKey)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = mKey;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}

void CMotorBase::SetWidgetIndex(QWidget * widNext,QWidget *widBack)
{
    pWidNext = widNext;
    pWidBack = widBack;

    if(!pWidNext)
        btNext->hide();

    if(!pWidBack)
        btBack->hide();

}
void CMotorBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    lbMaxSave->hide();
    lbMinSave->hide();

    QString mStr;
    QLabel* pLabel;
    mStr.setNum(g_systemDb->g_dbMachine.PosiData[m_iIdxMin]);

    pLabel = qobject_cast<QLabel *>(pWidArr.at(FOCUS_IDX_EDIT_MIN));
    pLabel->setText(mStr);

    mStr.setNum(g_systemDb->g_dbMachine.PosiData[m_iIdxMax]);

    pLabel = qobject_cast<QLabel *>(pWidArr.at(FOCUS_IDX_EDIT_MAX));
    pLabel->setText(mStr);

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad = new CSystemImepad(this);

    g_systemDb->g_bDataSaved = false;

    tmDataRefresh->start(TIME_SCREEN_FRESH);

    grabKeyboard();
}

void CMotorBase::hideEvent(QHideEvent *)
{

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    tmDataRefresh->stop();

    RsMgr->VisibleWidgetDel(this);

    releaseKeyboard();
}

void CMotorBase::OnMotorRefresh()
{

    QString mStr;
    mStr.setNum(g_systemDb->g_dbMachine.CurrentData[m_iIdxCur]);
    edElectronicScale->setText(mStr);

    if(g_systemDb->g_bDataSaved)
    {
        if(m_iFocusCurrent == FOCUS_IDX_BTN_MIN )
        {
            lbMinSave->show();
            g_systemDb->g_bDataSaved = false;
            //  m_iFocusCurrent = FOCUS_IDX_NULL;

            g_taskComCtrl->CreateTask(CMD_FUNC_PARAM,0,0);
        }
        if( m_iFocusCurrent == FOCUS_IDX_BTN_MAX)
        {
            lbMaxSave->show();
            g_systemDb->g_bDataSaved = false;
            //   m_iFocusCurrent = FOCUS_IDX_NULL;

            g_taskComCtrl->CreateTask(CMD_FUNC_PARAM,0,0);
        }
    }
}

void CMotorBase::OnButtonPressed()
{
    unsigned short  buf[10];
    buf[0] =0;

    if(sender() == btPositionUp )
    {
        lbMaxSave->hide();
        lbMinSave->hide();

        //buf[1] = m_iCmdUpPress;
        buf[1] = m_iComCmd[m_iMotorIdx][CMD_UP_PRESS];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);
    }

    if(sender() == btPositionDown )
    {
        lbMaxSave->hide();
        lbMinSave->hide();

        //buf[1] = m_iCmdDownPress;
        buf[1] = m_iComCmd[m_iMotorIdx][CMD_DOWN_PRESS];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);
    }
}

void CMotorBase::OnButtonReleased()
{
    unsigned short buf[10];
    buf[0] =0;

    if(sender() == btPositionUp )
    {
        //buf[1] = m_iCmdUpRelease;
        buf[1] = m_iComCmd[m_iMotorIdx][CMD_UP_RELEASE];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);
    }

    if(sender() == btPositionDown )
    {
        //buf[1] = m_iCmdDownRelease;
        buf[1] = m_iComCmd[m_iMotorIdx][CMD_DOWN_RELEASE];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);
    }
}
void CMotorBase::OnBtnClickSaveMin()
{
    unsigned short  buf[10];
    buf[0] = 0;

    QSettings * configPosition = new QSettings(QCoreApplication::applicationDirPath() +"/configPosition.ini",QSettings::IniFormat);
    QString strBuf;
    QLabel * pLabel;

    lbMinSave->hide();
    //m_iFocusCurrent = FOCUS_IDX_EDIT_MIN;
    m_iFocusCurrent = FOCUS_IDX_BTN_MIN;

    pLabel = qobject_cast<QLabel*>(pWidArr.at(FOCUS_IDX_EDIT_MIN) );
    int mPosData = pLabel->text().toInt();
    //int mPosData = edPositionMin->text().toInt();
    g_systemDb->g_dbMachine.PosiData[m_iIdxMin] = mPosData;

    //buf[1] = m_iCmdSaveMin;
    buf[1] = m_iComCmd[m_iMotorIdx][CMD_SAVE_MIN];
    buf[2] = g_systemDb->g_dbMachine.CurrentData[m_iIdxCur];
    buf[3] = mPosData;
    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);

    strBuf.setNum(buf[1]);
    strBuf.append("_min/data");

    configPosition->setValue(strBuf,buf[2]);

    strBuf.setNum(buf[1]);
    strBuf.append("_min/cali");
    configPosition->setValue(strBuf,buf[3]);

}
void CMotorBase::OnBtnClickSaveMax()
{
    unsigned short  buf[10];
    buf[0] = 0;

    QSettings * configPosition = new QSettings(QCoreApplication::applicationDirPath() +"/configPosition.ini",QSettings::IniFormat);
    QString strBuf;
    QLabel * pLabel;

    lbMaxSave->hide();
    m_iFocusCurrent = FOCUS_IDX_BTN_MAX;

    pLabel = qobject_cast<QLabel*>(pWidArr.at(FOCUS_IDX_EDIT_MAX) );
    int mPosData = pLabel->text().toInt();
    // int mPosData = edPositionMax->text().toInt();
    g_systemDb->g_dbMachine.PosiData[m_iIdxMax] = mPosData;

    //buf[1] = m_iCmdSaveMax;
    buf[1] = m_iComCmd[m_iMotorIdx][CMD_SAVE_MAX];
    buf[2] = g_systemDb->g_dbMachine.CurrentData[ m_iIdxCur ];
    buf[3] = mPosData;
    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);

    strBuf.setNum(buf[1]);
    strBuf.append("_max/data");

    configPosition->setValue(strBuf,buf[2]);

    strBuf.setNum(buf[1]);
    strBuf.append("_max/cali");
    configPosition->setValue(strBuf,buf[3]);

}
void CMotorBase::OnBtnClickIndex()
{

    if(sender() == btBack )
    {
        this->hide();
        g_mainSetting->setSceneWidget(pWidBack);
    }

    if(sender() == btNext )
    {
        this->hide();
        g_mainSetting->setSceneWidget(pWidNext);
    }

    if(sender() == btnExit )
    {

        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_motorMenu);
    }
}

//返回 -1 位置存储文件不存在
//返回 0  成功
//返回 1-10 代表相应电机参数不正确
int CMotorBase::DataValidCheck()
{

    if(!QFile::exists(QCoreApplication::applicationDirPath() +"/configPosition.ini"))
        return -1;

    unsigned short mMinCali,mMaxCali;
    //unsigned short mMinDat,mMaxDat;

    QString strBuf;

    QSettings * configPosition = new QSettings(QCoreApplication::applicationDirPath() +"/configPosition.ini",QSettings::IniFormat);

    //strBuf.setNum(m_iComCmd[m_iMotorIdx][CMD_SAVE_MIN]);
    //strBuf.append("_min/data");
    //mMinDat = configPosition->value(strBuf,0).toInt();

    strBuf.setNum(m_iComCmd[m_iMotorIdx][CMD_SAVE_MIN]);
    strBuf.append("_min/cali");

    mMinCali = configPosition->value(strBuf,0).toInt();

    if(mMinCali != g_systemDb->g_dbMachine.PosiData[m_iIdxMin])
        return (m_iMotorIdx + 1);

    //strBuf.setNum(m_iComCmd[m_iMotorIdx][CMD_SAVE_MAX]);
    //strBuf.append("_max/data");
    //mMaxDat = configPosition->value(strBuf,0).toInt();

    strBuf.setNum(m_iComCmd[m_iMotorIdx][CMD_SAVE_MAX]);
    strBuf.append("_max/cali");

    mMaxCali = configPosition->value(strBuf,0).toInt();

    if(mMaxCali != g_systemDb->g_dbMachine.PosiData[m_iIdxMax])
        return (m_iMotorIdx + 1);

    return 0;
}

bool CMotorBase::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==pWidArr.at(FOCUS_IDX_EDIT_MIN))
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            m_iFocusCurrent = FOCUS_IDX_EDIT_MIN;
            m_strKeyBuff = "";
            lbMaxSave->hide();
            lbMinSave->hide();
            g_systemPad->move(160,70);
            g_systemPad->show();
        }
    }

    if(watched== pWidArr.at(FOCUS_IDX_EDIT_MAX))
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            m_iFocusCurrent = FOCUS_IDX_EDIT_MAX;
            m_strKeyBuff = "";
            lbMaxSave->hide();
            lbMinSave->hide();
            g_systemPad->move(160,200);
            g_systemPad->show();
        }
    }

    return QWidget::eventFilter(watched,event);
}

void CMotorBase::keyReleaseEvent ( QKeyEvent * event )
{
    unsigned short buf[10];
    buf[0] =0;

    int mKey = event->key();
    event->accept();

    switch (mKey)
    {
    case Qt::Key_Up:
        buf[1] = m_iComCmd[m_iMotorIdx][CMD_UP_RELEASE];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);
        btPositionUp->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INDEX_UP"));
        break;
    case Qt::Key_Down:
        buf[1] = m_iComCmd[m_iMotorIdx][CMD_DOWN_RELEASE];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);
        btPositionDown->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INDEX_DOWN"));
        break;
    default:
        break;
    }
}
//////////////根据最近一次有效的焦点输入信息
void CMotorBase::keyPressEvent( QKeyEvent * event )
{
    QWidget * pWid;
    QLabel * pLabel;

    unsigned short  buf[10];
    buf[0] =0;

    int mKey = event->key();
    event->accept();

    switch (mKey) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if(m_iFocusCurrent == FOCUS_IDX_BTN_MIN)
            OnBtnClickSaveMin();

        if(m_iFocusCurrent == FOCUS_IDX_BTN_MAX)
            OnBtnClickSaveMax();

        break;
    case Qt::Key_Backspace:
        if(m_iFocusCurrent == FOCUS_IDX_EDIT_MIN || m_iFocusCurrent == FOCUS_IDX_EDIT_MAX)
        {
            m_strKeyBuff.chop( 1);
            pLabel = qobject_cast<QLabel*>(pWidArr.at(m_iFocusCurrent) );
            pLabel->setText(m_strKeyBuff);
        }

        break;
    case Qt::Key_Up:
        lbMaxSave->hide();
        lbMinSave->hide();

        buf[1] = m_iComCmd[m_iMotorIdx][CMD_UP_PRESS];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);
        btPositionUp->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INDEX_UP") + "border : 4px solid green;");
        break;
    case Qt::Key_Down:
        lbMaxSave->hide();
        lbMinSave->hide();

        buf[1] = m_iComCmd[m_iMotorIdx][CMD_DOWN_PRESS];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);
        btPositionDown->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INDEX_DOWN") + "border : 4px solid green;");
        break;
    case Qt::Key_PageDown:
        if(pWidNext)
        {
            this->hide();
            g_mainSetting->setSceneWidget(pWidNext);
        }
        break;
    case Qt::Key_PageUp:
        if(pWidBack)
        {
            this->hide();
            g_mainSetting->setSceneWidget(pWidBack);
        }
        break;
    case Qt::Key_Escape:
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_motorMenu);
        break;
    case Qt::Key_Tab:

        pWid = qobject_cast<QWidget*>(pWidArr.at(m_iFocusCurrent) );

        if(m_iFocusCurrent == FOCUS_IDX_EDIT_MIN || m_iFocusCurrent == FOCUS_IDX_EDIT_MAX)
            pWid->setStyleSheet("background-color : white ; color : darkCyan;border : 2px solid black");

        if(m_iFocusCurrent == FOCUS_IDX_BTN_MIN || m_iFocusCurrent == FOCUS_IDX_BTN_MAX)
            pWid->setStyleSheet("border : 2px solid black");

        if(++m_iFocusCurrent > FOCUS_IDX_BTN_MAX)
            m_iFocusCurrent = 0;

        pWid = qobject_cast<QWidget*>(pWidArr.at(m_iFocusCurrent) );

        if(m_iFocusCurrent == FOCUS_IDX_EDIT_MIN || m_iFocusCurrent == FOCUS_IDX_EDIT_MAX)
        {
            pWid->setStyleSheet("background-color : white ; color : darkCyan;border : 3px solid green");
            pLabel = qobject_cast<QLabel*>(pWidArr.at(m_iFocusCurrent) );
            m_strKeyBuff = pLabel->text();
        }

        if(m_iFocusCurrent == FOCUS_IDX_BTN_MIN || m_iFocusCurrent == FOCUS_IDX_BTN_MAX)
            pWid->setStyleSheet("border : 3px solid green");

        break;
    default:
        if(m_iFocusCurrent == FOCUS_IDX_EDIT_MIN || m_iFocusCurrent == FOCUS_IDX_EDIT_MAX)
        {
            if(m_strKeyBuff.length() < 5 &&( (mKey >= Qt::Key_0 &&  mKey <= Qt::Key_9) || ( mKey >= Qt::Key_A  &&  mKey <= Qt::Key_Z)))
                m_strKeyBuff.append(event->key());

            pLabel = qobject_cast<QLabel*>(pWidArr.at(m_iFocusCurrent) );
            pLabel->setText(m_strKeyBuff);
        }
        break;
    }



}

void CMotorBase::InitRf8aData()
{
    //////////////////////////////////////////////////////////////
    m_iComCmd[RF8A_MOTOR_FID][CMD_UP_PRESS]    = 0x0020;
    m_iComCmd[RF8A_MOTOR_FID][CMD_UP_RELEASE]  = 0x0021;
    m_iComCmd[RF8A_MOTOR_FID][CMD_DOWN_PRESS]  = 0x0022;
    m_iComCmd[RF8A_MOTOR_FID][CMD_DOWN_RELEASE]= 0x0023;
    m_iComCmd[RF8A_MOTOR_DTP][CMD_UP_PRESS]    = 0x0024;
    m_iComCmd[RF8A_MOTOR_DTP][CMD_UP_RELEASE]  = 0x0025;
    m_iComCmd[RF8A_MOTOR_DTP][CMD_DOWN_PRESS]  = 0x0026;
    m_iComCmd[RF8A_MOTOR_DTP][CMD_DOWN_RELEASE]= 0x0027;
    m_iComCmd[RF8A_MOTOR_SID][CMD_UP_PRESS]    = 0x0028;
    m_iComCmd[RF8A_MOTOR_SID][CMD_UP_RELEASE]  = 0x0029;
    m_iComCmd[RF8A_MOTOR_SID][CMD_DOWN_PRESS]  = 0x002a;
    m_iComCmd[RF8A_MOTOR_SID][CMD_DOWN_RELEASE]= 0x002b;
    m_iComCmd[RF8A_MOTOR_ANG][CMD_UP_PRESS]    = 0x002C;
    m_iComCmd[RF8A_MOTOR_ANG][CMD_UP_RELEASE]  = 0x002D;
    m_iComCmd[RF8A_MOTOR_ANG][CMD_DOWN_PRESS]  = 0x002E;
    m_iComCmd[RF8A_MOTOR_ANG][CMD_DOWN_RELEASE]= 0x002F;
    m_iComCmd[RF8A_MOTOR_PRL][CMD_UP_PRESS]    = 0x0030;
    m_iComCmd[RF8A_MOTOR_PRL][CMD_UP_RELEASE]  = 0x0031;
    m_iComCmd[RF8A_MOTOR_PRL][CMD_DOWN_PRESS]  = 0x0032;
    m_iComCmd[RF8A_MOTOR_PRL][CMD_DOWN_RELEASE]= 0x0033;
    m_iComCmd[RF8A_MOTOR_PYP][CMD_UP_PRESS]    = 0x0034;
    m_iComCmd[RF8A_MOTOR_PYP][CMD_UP_RELEASE]  = 0x0035;
    m_iComCmd[RF8A_MOTOR_PYP][CMD_DOWN_PRESS]  = 0x0036;
    m_iComCmd[RF8A_MOTOR_PYP][CMD_DOWN_RELEASE]= 0x0037;
    m_iComCmd[RF8A_MOTOR_SGH][CMD_UP_PRESS]    = 0x0038;
    m_iComCmd[RF8A_MOTOR_SGH][CMD_UP_RELEASE]  = 0x0039;
    m_iComCmd[RF8A_MOTOR_SGH][CMD_DOWN_PRESS]  = 0x003a;
    m_iComCmd[RF8A_MOTOR_SGH][CMD_DOWN_RELEASE]= 0x003b;
    m_iComCmd[RF8A_MOTOR_SGV][CMD_UP_PRESS]    = 0x003C;
    m_iComCmd[RF8A_MOTOR_SGV][CMD_UP_RELEASE]  = 0x003D;
    m_iComCmd[RF8A_MOTOR_SGV][CMD_DOWN_PRESS]  = 0x003E;
    m_iComCmd[RF8A_MOTOR_SGV][CMD_DOWN_RELEASE]= 0x003F;

    //////////////////////////////////////////////////////////////
    m_iComCmd[RF8A_MOTOR_FID][CMD_SAVE_MIN]    = 0x0030;
    m_iComCmd[RF8A_MOTOR_FID][CMD_SAVE_MAX]    = 0x0031;
    m_iComCmd[RF8A_MOTOR_DTP][CMD_SAVE_MIN]    = 0x0032;
    m_iComCmd[RF8A_MOTOR_DTP][CMD_SAVE_MAX]    = 0x0033;
    m_iComCmd[RF8A_MOTOR_SID][CMD_SAVE_MIN]    = 0x0034;
    m_iComCmd[RF8A_MOTOR_SID][CMD_SAVE_MAX]    = 0x0035;
    m_iComCmd[RF8A_MOTOR_ANG][CMD_SAVE_MIN]    = 0x0036;
    m_iComCmd[RF8A_MOTOR_ANG][CMD_SAVE_MAX]    = 0x0037;
    m_iComCmd[RF8A_MOTOR_PRL][CMD_SAVE_MIN]    = 0x0038;
    m_iComCmd[RF8A_MOTOR_PRL][CMD_SAVE_MAX]    = 0x0039;
    m_iComCmd[RF8A_MOTOR_PYP][CMD_SAVE_MIN]    = 0x003a;
    m_iComCmd[RF8A_MOTOR_PYP][CMD_SAVE_MAX]    = 0x003b;
    m_iComCmd[RF8A_MOTOR_SGH][CMD_SAVE_MIN]    = 0x003c;
    m_iComCmd[RF8A_MOTOR_SGH][CMD_SAVE_MAX]    = 0x003d;
    m_iComCmd[RF8A_MOTOR_SGV][CMD_SAVE_MIN]    = 0x003e;
    m_iComCmd[RF8A_MOTOR_SGV][CMD_SAVE_MAX]    = 0x003f;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[RF8A_MOTOR_FID][CAL_CUR] = 8;
    m_iDataIdx[RF8A_MOTOR_DTP][CAL_CUR] = 9;
    m_iDataIdx[RF8A_MOTOR_SID][CAL_CUR] = 10;
    m_iDataIdx[RF8A_MOTOR_ANG][CAL_CUR] = 11;
    m_iDataIdx[RF8A_MOTOR_PRL][CAL_CUR] = 12;
    m_iDataIdx[RF8A_MOTOR_PYP][CAL_CUR] = 13;
    m_iDataIdx[RF8A_MOTOR_SGH][CAL_CUR] = 14;
    m_iDataIdx[RF8A_MOTOR_SGV][CAL_CUR] = 15;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[RF8A_MOTOR_FID][CAL_MIN] = 0;
    m_iDataIdx[RF8A_MOTOR_FID][CAL_MAX] = 1;
    m_iDataIdx[RF8A_MOTOR_DTP][CAL_MIN] = 2;
    m_iDataIdx[RF8A_MOTOR_DTP][CAL_MAX] = 3;
    m_iDataIdx[RF8A_MOTOR_SID][CAL_MIN] = 4;
    m_iDataIdx[RF8A_MOTOR_SID][CAL_MAX] = 5;
    m_iDataIdx[RF8A_MOTOR_ANG][CAL_MIN] = 6;
    m_iDataIdx[RF8A_MOTOR_ANG][CAL_MAX] = 7;
    m_iDataIdx[RF8A_MOTOR_PRL][CAL_MIN] = 8;
    m_iDataIdx[RF8A_MOTOR_PRL][CAL_MAX] = 9;
    m_iDataIdx[RF8A_MOTOR_PYP][CAL_MIN] = 10;
    m_iDataIdx[RF8A_MOTOR_PYP][CAL_MAX] = 11;
    m_iDataIdx[RF8A_MOTOR_SGH][CAL_MIN] = 12;
    m_iDataIdx[RF8A_MOTOR_SGH][CAL_MAX] = 13;
    m_iDataIdx[RF8A_MOTOR_SGV][CAL_MIN] = 14;
    m_iDataIdx[RF8A_MOTOR_SGV][CAL_MAX] = 15;

}


void CMotorBase::InitNdt8aData()
{
    //////////////////////////////////////////////////////////////
    m_iComCmd[NDT8a_MOTOR_FID][CMD_UP_PRESS]    = 0x0020;
    m_iComCmd[NDT8a_MOTOR_FID][CMD_UP_RELEASE]  = 0x0021;
    m_iComCmd[NDT8a_MOTOR_FID][CMD_DOWN_PRESS]  = 0x0022;
    m_iComCmd[NDT8a_MOTOR_FID][CMD_DOWN_RELEASE]= 0x0023;
    m_iComCmd[NDT8a_MOTOR_X1][CMD_UP_PRESS]    = 0x0024;
    m_iComCmd[NDT8a_MOTOR_X1][CMD_UP_RELEASE]  = 0x0025;
    m_iComCmd[NDT8a_MOTOR_X1][CMD_DOWN_PRESS]  = 0x0026;
    m_iComCmd[NDT8a_MOTOR_X1][CMD_DOWN_RELEASE]= 0x0027;
    m_iComCmd[NDT8a_MOTOR_Y1][CMD_UP_PRESS]    = 0x0028;
    m_iComCmd[NDT8a_MOTOR_Y1][CMD_UP_RELEASE]  = 0x0029;
    m_iComCmd[NDT8a_MOTOR_Y1][CMD_DOWN_PRESS]  = 0x002a;
    m_iComCmd[NDT8a_MOTOR_Y1][CMD_DOWN_RELEASE]= 0x002b;
    m_iComCmd[NDT8a_MOTOR_X2][CMD_UP_PRESS]    = 0x002C;
    m_iComCmd[NDT8a_MOTOR_X2][CMD_UP_RELEASE]  = 0x002D;
    m_iComCmd[NDT8a_MOTOR_X2][CMD_DOWN_PRESS]  = 0x002E;
    m_iComCmd[NDT8a_MOTOR_X2][CMD_DOWN_RELEASE]= 0x002F;
    m_iComCmd[NDT8a_MOTOR_Y2][CMD_UP_PRESS]    = 0x0030;
    m_iComCmd[NDT8a_MOTOR_Y2][CMD_UP_RELEASE]  = 0x0031;
    m_iComCmd[NDT8a_MOTOR_Y2][CMD_DOWN_PRESS]  = 0x0032;
    m_iComCmd[NDT8a_MOTOR_Y2][CMD_DOWN_RELEASE]= 0x0033;

    //////////////////////////////////////////////////////////////
    m_iComCmd[NDT8a_MOTOR_FID][CMD_SAVE_MIN]    = 0x0030;
    m_iComCmd[NDT8a_MOTOR_FID][CMD_SAVE_MAX]    = 0x0031;
    m_iComCmd[NDT8a_MOTOR_X1][CMD_SAVE_MIN]    = 0x0032;
    m_iComCmd[NDT8a_MOTOR_X1][CMD_SAVE_MAX]    = 0x0033;
    m_iComCmd[NDT8a_MOTOR_Y1][CMD_SAVE_MIN]    = 0x0034;
    m_iComCmd[NDT8a_MOTOR_Y1][CMD_SAVE_MAX]    = 0x0035;
    m_iComCmd[NDT8a_MOTOR_X2][CMD_SAVE_MIN]    = 0x0036;
    m_iComCmd[NDT8a_MOTOR_X2][CMD_SAVE_MAX]    = 0x0037;
    m_iComCmd[NDT8a_MOTOR_Y2][CMD_SAVE_MIN]    = 0x0038;
    m_iComCmd[NDT8a_MOTOR_Y2][CMD_SAVE_MAX]    = 0x0039;


    //////////////////////////////////////////////////////////////
    m_iDataIdx[NDT8a_MOTOR_FID][CAL_CUR] = 8;
    m_iDataIdx[NDT8a_MOTOR_X1][CAL_CUR] = 9;
    m_iDataIdx[NDT8a_MOTOR_Y1][CAL_CUR] = 10;
    m_iDataIdx[NDT8a_MOTOR_X2][CAL_CUR] = 11;
    m_iDataIdx[NDT8a_MOTOR_Y2][CAL_CUR] = 12;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[NDT8a_MOTOR_FID][CAL_MIN] = 0;
    m_iDataIdx[NDT8a_MOTOR_FID][CAL_MAX] = 1;
    m_iDataIdx[NDT8a_MOTOR_X1][CAL_MIN] = 2;
    m_iDataIdx[NDT8a_MOTOR_X1][CAL_MAX] = 3;
    m_iDataIdx[NDT8a_MOTOR_Y1][CAL_MIN] = 4;
    m_iDataIdx[NDT8a_MOTOR_Y1][CAL_MAX] = 5;
    m_iDataIdx[NDT8a_MOTOR_X2][CAL_MIN] = 6;
    m_iDataIdx[NDT8a_MOTOR_X2][CAL_MAX] = 7;
    m_iDataIdx[NDT8a_MOTOR_Y2][CAL_MIN] = 8;
    m_iDataIdx[NDT8a_MOTOR_Y2][CAL_MAX] = 9;

}
void CMotorBase::InitCeil10aData()
{
    //////////////////////////////////////////////////////////////
    m_iComCmd[CEIL10a_MOTOR_FID][CMD_UP_PRESS]    = 0x0020;
    m_iComCmd[CEIL10a_MOTOR_FID][CMD_UP_RELEASE]  = 0x0021;
    m_iComCmd[CEIL10a_MOTOR_FID][CMD_DOWN_PRESS]  = 0x0022;
    m_iComCmd[CEIL10a_MOTOR_FID][CMD_DOWN_RELEASE]= 0x0023;
    m_iComCmd[CEIL10a_MOTOR_SID][CMD_UP_PRESS]    = 0x0024;
    m_iComCmd[CEIL10a_MOTOR_SID][CMD_UP_RELEASE]  = 0x0025;
    m_iComCmd[CEIL10a_MOTOR_SID][CMD_DOWN_PRESS]  = 0x0026;
    m_iComCmd[CEIL10a_MOTOR_SID][CMD_DOWN_RELEASE]= 0x0027;
    m_iComCmd[CEIL10a_MOTOR_ANG][CMD_UP_PRESS]    = 0x0028;
    m_iComCmd[CEIL10a_MOTOR_ANG][CMD_UP_RELEASE]  = 0x0029;
    m_iComCmd[CEIL10a_MOTOR_ANG][CMD_DOWN_PRESS]  = 0x002a;
    m_iComCmd[CEIL10a_MOTOR_ANG][CMD_DOWN_RELEASE]= 0x002b;
    m_iComCmd[CEIL10a_MOTOR_DTH][CMD_UP_PRESS]    = 0x002C;
    m_iComCmd[CEIL10a_MOTOR_DTH][CMD_UP_RELEASE]  = 0x002D;
    m_iComCmd[CEIL10a_MOTOR_DTH][CMD_DOWN_PRESS]  = 0x002E;
    m_iComCmd[CEIL10a_MOTOR_DTH][CMD_DOWN_RELEASE]= 0x002F;
    m_iComCmd[CEIL10a_MOTOR_DTA][CMD_UP_PRESS]    = 0x0030;
    m_iComCmd[CEIL10a_MOTOR_DTA][CMD_UP_RELEASE]  = 0x0031;
    m_iComCmd[CEIL10a_MOTOR_DTA][CMD_DOWN_PRESS]  = 0x0032;
    m_iComCmd[CEIL10a_MOTOR_DTA][CMD_DOWN_RELEASE]= 0x0033;
    m_iComCmd[CEIL10a_MOTOR_CEP][CMD_UP_PRESS]    = 0x0034;
    m_iComCmd[CEIL10a_MOTOR_CEP][CMD_UP_RELEASE]  = 0x0035;
    m_iComCmd[CEIL10a_MOTOR_CEP][CMD_DOWN_PRESS]  = 0x0036;
    m_iComCmd[CEIL10a_MOTOR_CEP][CMD_DOWN_RELEASE]= 0x0037;
    m_iComCmd[CEIL10a_MOTOR_BEH][CMD_UP_PRESS]    = 0x0038;
    m_iComCmd[CEIL10a_MOTOR_BEH][CMD_UP_RELEASE]  = 0x0039;
    m_iComCmd[CEIL10a_MOTOR_BEH][CMD_DOWN_PRESS]  = 0x003a;
    m_iComCmd[CEIL10a_MOTOR_BEH][CMD_DOWN_RELEASE]= 0x003b;
    m_iComCmd[CEIL10a_MOTOR_DTP][CMD_UP_PRESS]    = 0x003C;
    m_iComCmd[CEIL10a_MOTOR_DTP][CMD_UP_RELEASE]  = 0x003D;
    m_iComCmd[CEIL10a_MOTOR_DTP][CMD_DOWN_PRESS]  = 0x003E;
    m_iComCmd[CEIL10a_MOTOR_DTP][CMD_DOWN_RELEASE]= 0x003F;

    //////////////////////////////////////////////////////////////
    m_iComCmd[CEIL10a_MOTOR_FID][CMD_SAVE_MIN]    = 0x0030;
    m_iComCmd[CEIL10a_MOTOR_FID][CMD_SAVE_MAX]    = 0x0031;
    m_iComCmd[CEIL10a_MOTOR_SID][CMD_SAVE_MIN]    = 0x0032;
    m_iComCmd[CEIL10a_MOTOR_SID][CMD_SAVE_MAX]    = 0x0033;
    m_iComCmd[CEIL10a_MOTOR_ANG][CMD_SAVE_MIN]    = 0x0034;
    m_iComCmd[CEIL10a_MOTOR_ANG][CMD_SAVE_MAX]    = 0x0035;
    m_iComCmd[CEIL10a_MOTOR_DTH][CMD_SAVE_MIN]    = 0x0036;
    m_iComCmd[CEIL10a_MOTOR_DTH][CMD_SAVE_MAX]    = 0x0037;
    m_iComCmd[CEIL10a_MOTOR_DTA][CMD_SAVE_MIN]    = 0x0038;
    m_iComCmd[CEIL10a_MOTOR_DTA][CMD_SAVE_MAX]    = 0x0039;
    m_iComCmd[CEIL10a_MOTOR_CEP][CMD_SAVE_MIN]    = 0x003a;
    m_iComCmd[CEIL10a_MOTOR_CEP][CMD_SAVE_MAX]    = 0x003b;
    m_iComCmd[CEIL10a_MOTOR_BEH][CMD_SAVE_MIN]    = 0x003c;
    m_iComCmd[CEIL10a_MOTOR_BEH][CMD_SAVE_MAX]    = 0x003d;
    m_iComCmd[CEIL10a_MOTOR_DTP][CMD_SAVE_MIN]    = 0x003e;
    m_iComCmd[CEIL10a_MOTOR_DTP][CMD_SAVE_MAX]    = 0x003f;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[CEIL10a_MOTOR_FID][CAL_CUR] = 8;
    m_iDataIdx[CEIL10a_MOTOR_SID][CAL_CUR] = 9;
    m_iDataIdx[CEIL10a_MOTOR_ANG][CAL_CUR] = 10;
    m_iDataIdx[CEIL10a_MOTOR_DTH][CAL_CUR] = 11;
    m_iDataIdx[CEIL10a_MOTOR_DTA][CAL_CUR] = 12;
    m_iDataIdx[CEIL10a_MOTOR_CEP][CAL_CUR] = 13;
    m_iDataIdx[CEIL10a_MOTOR_BEH][CAL_CUR] = 14;
    m_iDataIdx[CEIL10a_MOTOR_DTP][CAL_CUR] = 15;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[CEIL10a_MOTOR_FID][CAL_MIN] = 0;
    m_iDataIdx[CEIL10a_MOTOR_FID][CAL_MAX] = 1;
    m_iDataIdx[CEIL10a_MOTOR_SID][CAL_MIN] = 2;
    m_iDataIdx[CEIL10a_MOTOR_SID][CAL_MAX] = 3;
    m_iDataIdx[CEIL10a_MOTOR_ANG][CAL_MIN] = 4;
    m_iDataIdx[CEIL10a_MOTOR_ANG][CAL_MAX] = 5;
    m_iDataIdx[CEIL10a_MOTOR_DTH][CAL_MIN] = 6;
    m_iDataIdx[CEIL10a_MOTOR_DTH][CAL_MAX] = 7;
    m_iDataIdx[CEIL10a_MOTOR_DTA][CAL_MIN] = 8;
    m_iDataIdx[CEIL10a_MOTOR_DTA][CAL_MAX] = 9;
    m_iDataIdx[CEIL10a_MOTOR_CEP][CAL_MIN] = 10;
    m_iDataIdx[CEIL10a_MOTOR_CEP][CAL_MAX] = 11;
    m_iDataIdx[CEIL10a_MOTOR_BEH][CAL_MIN] = 12;
    m_iDataIdx[CEIL10a_MOTOR_BEH][CAL_MAX] = 13;
    m_iDataIdx[CEIL10a_MOTOR_DTP][CAL_MIN] = 14;
    m_iDataIdx[CEIL10a_MOTOR_DTP][CAL_MAX] = 15;

}
void CMotorBase::InitCeil10bData()
{
    //////////////////////////////////////////////////////////////
    m_iComCmd[CEIL10b_MOTOR_FID][CMD_UP_PRESS]    = 0x0020;
    m_iComCmd[CEIL10b_MOTOR_FID][CMD_UP_RELEASE]  = 0x0021;
    m_iComCmd[CEIL10b_MOTOR_FID][CMD_DOWN_PRESS]  = 0x0022;
    m_iComCmd[CEIL10b_MOTOR_FID][CMD_DOWN_RELEASE]= 0x0023;
    m_iComCmd[CEIL10b_MOTOR_SID][CMD_UP_PRESS]    = 0x0024;
    m_iComCmd[CEIL10b_MOTOR_SID][CMD_UP_RELEASE]  = 0x0025;
    m_iComCmd[CEIL10b_MOTOR_SID][CMD_DOWN_PRESS]  = 0x0026;
    m_iComCmd[CEIL10b_MOTOR_SID][CMD_DOWN_RELEASE]= 0x0027;
    m_iComCmd[CEIL10b_MOTOR_ANG][CMD_UP_PRESS]    = 0x0028;
    m_iComCmd[CEIL10b_MOTOR_ANG][CMD_UP_RELEASE]  = 0x0029;
    m_iComCmd[CEIL10b_MOTOR_ANG][CMD_DOWN_PRESS]  = 0x002a;
    m_iComCmd[CEIL10b_MOTOR_ANG][CMD_DOWN_RELEASE]= 0x002b;
    m_iComCmd[CEIL10b_MOTOR_DTH][CMD_UP_PRESS]    = 0x002C;
    m_iComCmd[CEIL10b_MOTOR_DTH][CMD_UP_RELEASE]  = 0x002D;
    m_iComCmd[CEIL10b_MOTOR_DTH][CMD_DOWN_PRESS]  = 0x002E;
    m_iComCmd[CEIL10b_MOTOR_DTH][CMD_DOWN_RELEASE]= 0x002F;
    m_iComCmd[CEIL10b_MOTOR_DTA][CMD_UP_PRESS]    = 0x0030;
    m_iComCmd[CEIL10b_MOTOR_DTA][CMD_UP_RELEASE]  = 0x0031;
    m_iComCmd[CEIL10b_MOTOR_DTA][CMD_DOWN_PRESS]  = 0x0032;
    m_iComCmd[CEIL10b_MOTOR_DTA][CMD_DOWN_RELEASE]= 0x0033;
    m_iComCmd[CEIL10b_MOTOR_CEP][CMD_UP_PRESS]    = 0x0034;
    m_iComCmd[CEIL10b_MOTOR_CEP][CMD_UP_RELEASE]  = 0x0035;
    m_iComCmd[CEIL10b_MOTOR_CEP][CMD_DOWN_PRESS]  = 0x0036;
    m_iComCmd[CEIL10b_MOTOR_CEP][CMD_DOWN_RELEASE]= 0x0037;

    //////////////////////////////////////////////////////////////
    m_iComCmd[CEIL10b_MOTOR_FID][CMD_SAVE_MIN]    = 0x0030;
    m_iComCmd[CEIL10b_MOTOR_FID][CMD_SAVE_MAX]    = 0x0031;
    m_iComCmd[CEIL10b_MOTOR_SID][CMD_SAVE_MIN]    = 0x0032;
    m_iComCmd[CEIL10b_MOTOR_SID][CMD_SAVE_MAX]    = 0x0033;
    m_iComCmd[CEIL10b_MOTOR_ANG][CMD_SAVE_MIN]    = 0x0034;
    m_iComCmd[CEIL10b_MOTOR_ANG][CMD_SAVE_MAX]    = 0x0035;
    m_iComCmd[CEIL10b_MOTOR_DTH][CMD_SAVE_MIN]    = 0x0036;
    m_iComCmd[CEIL10b_MOTOR_DTH][CMD_SAVE_MAX]    = 0x0037;
    m_iComCmd[CEIL10b_MOTOR_DTA][CMD_SAVE_MIN]    = 0x0038;
    m_iComCmd[CEIL10b_MOTOR_DTA][CMD_SAVE_MAX]    = 0x0039;
    m_iComCmd[CEIL10b_MOTOR_CEP][CMD_SAVE_MIN]    = 0x003a;
    m_iComCmd[CEIL10b_MOTOR_CEP][CMD_SAVE_MAX]    = 0x003b;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[CEIL10b_MOTOR_FID][CAL_CUR] = 8;
    m_iDataIdx[CEIL10b_MOTOR_SID][CAL_CUR] = 9;
    m_iDataIdx[CEIL10b_MOTOR_ANG][CAL_CUR] = 10;
    m_iDataIdx[CEIL10b_MOTOR_DTH][CAL_CUR] = 11;
    m_iDataIdx[CEIL10b_MOTOR_DTA][CAL_CUR] = 12;
    m_iDataIdx[CEIL10b_MOTOR_CEP][CAL_CUR] = 13;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[CEIL10b_MOTOR_FID][CAL_MIN] = 0;
    m_iDataIdx[CEIL10b_MOTOR_FID][CAL_MAX] = 1;
    m_iDataIdx[CEIL10b_MOTOR_SID][CAL_MIN] = 2;
    m_iDataIdx[CEIL10b_MOTOR_SID][CAL_MAX] = 3;
    m_iDataIdx[CEIL10b_MOTOR_ANG][CAL_MIN] = 4;
    m_iDataIdx[CEIL10b_MOTOR_ANG][CAL_MAX] = 5;
    m_iDataIdx[CEIL10b_MOTOR_DTH][CAL_MIN] = 6;
    m_iDataIdx[CEIL10b_MOTOR_DTH][CAL_MAX] = 7;
    m_iDataIdx[CEIL10b_MOTOR_DTA][CAL_MIN] = 8;
    m_iDataIdx[CEIL10b_MOTOR_DTA][CAL_MAX] = 9;
    m_iDataIdx[CEIL10b_MOTOR_CEP][CAL_MIN] = 10;
    m_iDataIdx[CEIL10b_MOTOR_CEP][CAL_MAX] = 11;

}
void CMotorBase::InitCeil8Data()
{
    //////////////////////////////////////////////////////////////
    m_iComCmd[CEIL8_MOTOR_FID][CMD_UP_PRESS]    = 0x0020;
    m_iComCmd[CEIL8_MOTOR_FID][CMD_UP_RELEASE]  = 0x0021;
    m_iComCmd[CEIL8_MOTOR_FID][CMD_DOWN_PRESS]  = 0x0022;
    m_iComCmd[CEIL8_MOTOR_FID][CMD_DOWN_RELEASE]= 0x0023;
    m_iComCmd[CEIL8_MOTOR_SID][CMD_UP_PRESS]    = 0x0024;
    m_iComCmd[CEIL8_MOTOR_SID][CMD_UP_RELEASE]  = 0x0025;
    m_iComCmd[CEIL8_MOTOR_SID][CMD_DOWN_PRESS]  = 0x0026;
    m_iComCmd[CEIL8_MOTOR_SID][CMD_DOWN_RELEASE]= 0x0027;
    m_iComCmd[CEIL8_MOTOR_ANG][CMD_UP_PRESS]    = 0x0028;
    m_iComCmd[CEIL8_MOTOR_ANG][CMD_UP_RELEASE]  = 0x0029;
    m_iComCmd[CEIL8_MOTOR_ANG][CMD_DOWN_PRESS]  = 0x002a;
    m_iComCmd[CEIL8_MOTOR_ANG][CMD_DOWN_RELEASE]= 0x002b;
    m_iComCmd[CEIL8_MOTOR_DTH][CMD_UP_PRESS]    = 0x002C;
    m_iComCmd[CEIL8_MOTOR_DTH][CMD_UP_RELEASE]  = 0x002D;
    m_iComCmd[CEIL8_MOTOR_DTH][CMD_DOWN_PRESS]  = 0x002E;
    m_iComCmd[CEIL8_MOTOR_DTH][CMD_DOWN_RELEASE]= 0x002F;
    m_iComCmd[CEIL8_MOTOR_DTA][CMD_UP_PRESS]    = 0x0030;
    m_iComCmd[CEIL8_MOTOR_DTA][CMD_UP_RELEASE]  = 0x0031;
    m_iComCmd[CEIL8_MOTOR_DTA][CMD_DOWN_PRESS]  = 0x0032;
    m_iComCmd[CEIL8_MOTOR_DTA][CMD_DOWN_RELEASE]= 0x0033;

    //////////////////////////////////////////////////////////////
    m_iComCmd[CEIL8_MOTOR_FID][CMD_SAVE_MIN]    = 0x0030;
    m_iComCmd[CEIL8_MOTOR_FID][CMD_SAVE_MAX]    = 0x0031;
    m_iComCmd[CEIL8_MOTOR_SID][CMD_SAVE_MIN]    = 0x0032;
    m_iComCmd[CEIL8_MOTOR_SID][CMD_SAVE_MAX]    = 0x0033;
    m_iComCmd[CEIL8_MOTOR_ANG][CMD_SAVE_MIN]    = 0x0034;
    m_iComCmd[CEIL8_MOTOR_ANG][CMD_SAVE_MAX]    = 0x0035;
    m_iComCmd[CEIL8_MOTOR_DTH][CMD_SAVE_MIN]    = 0x0036;
    m_iComCmd[CEIL8_MOTOR_DTH][CMD_SAVE_MAX]    = 0x0037;
    m_iComCmd[CEIL8_MOTOR_DTA][CMD_SAVE_MIN]    = 0x0038;
    m_iComCmd[CEIL8_MOTOR_DTA][CMD_SAVE_MAX]    = 0x0039;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[CEIL8_MOTOR_FID][CAL_CUR] = 8;
    m_iDataIdx[CEIL8_MOTOR_SID][CAL_CUR] = 9;
    m_iDataIdx[CEIL8_MOTOR_ANG][CAL_CUR] = 10;
    m_iDataIdx[CEIL8_MOTOR_DTH][CAL_CUR] = 11;
    m_iDataIdx[CEIL8_MOTOR_DTA][CAL_CUR] = 12;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[CEIL8_MOTOR_FID][CAL_MIN] = 0;
    m_iDataIdx[CEIL8_MOTOR_FID][CAL_MAX] = 1;
    m_iDataIdx[CEIL8_MOTOR_SID][CAL_MIN] = 2;
    m_iDataIdx[CEIL8_MOTOR_SID][CAL_MAX] = 3;
    m_iDataIdx[CEIL8_MOTOR_ANG][CAL_MIN] = 4;
    m_iDataIdx[CEIL8_MOTOR_ANG][CAL_MAX] = 5;
    m_iDataIdx[CEIL8_MOTOR_DTH][CAL_MIN] = 6;
    m_iDataIdx[CEIL8_MOTOR_DTH][CAL_MAX] = 7;
    m_iDataIdx[CEIL8_MOTOR_DTA][CAL_MIN] = 8;
    m_iDataIdx[CEIL8_MOTOR_DTA][CAL_MAX] = 9;
}
void CMotorBase::InitUarm10Data()
{
}
void CMotorBase::InitUarm8Data()
{
    //////////////////////////////////////////////////////////////
    m_iComCmd[UARM8_MOTOR_HEI][CMD_UP_PRESS]    = 0x0020;
    m_iComCmd[UARM8_MOTOR_HEI][CMD_UP_RELEASE]  = 0x0021;
    m_iComCmd[UARM8_MOTOR_HEI][CMD_DOWN_PRESS]  = 0x0022;
    m_iComCmd[UARM8_MOTOR_HEI][CMD_DOWN_RELEASE]= 0x0023;
    m_iComCmd[UARM8_MOTOR_SID][CMD_UP_PRESS]    = 0x0024;
    m_iComCmd[UARM8_MOTOR_SID][CMD_UP_RELEASE]  = 0x0025;
    m_iComCmd[UARM8_MOTOR_SID][CMD_DOWN_PRESS]  = 0x0026;
    m_iComCmd[UARM8_MOTOR_SID][CMD_DOWN_RELEASE]= 0x0027;
    m_iComCmd[UARM8_MOTOR_ANG][CMD_UP_PRESS]    = 0x0028;
    m_iComCmd[UARM8_MOTOR_ANG][CMD_UP_RELEASE]  = 0x0029;
    m_iComCmd[UARM8_MOTOR_ANG][CMD_DOWN_PRESS]  = 0x002a;
    m_iComCmd[UARM8_MOTOR_ANG][CMD_DOWN_RELEASE]= 0x002b;
    m_iComCmd[UARM8_MOTOR_DTA][CMD_UP_PRESS]    = 0x002c;
    m_iComCmd[UARM8_MOTOR_DTA][CMD_UP_RELEASE]  = 0x002d;
    m_iComCmd[UARM8_MOTOR_DTA][CMD_DOWN_PRESS]  = 0x002e;
    m_iComCmd[UARM8_MOTOR_DTA][CMD_DOWN_RELEASE]= 0x002f;

    //////////////////////////////////////////////////////////////
    m_iComCmd[UARM8_MOTOR_HEI][CMD_SAVE_MIN]    = 0x0030;
    m_iComCmd[UARM8_MOTOR_HEI][CMD_SAVE_MAX]    = 0x0031;
    m_iComCmd[UARM8_MOTOR_SID][CMD_SAVE_MIN]    = 0x0032;
    m_iComCmd[UARM8_MOTOR_SID][CMD_SAVE_MAX]    = 0x0033;
    m_iComCmd[UARM8_MOTOR_ANG][CMD_SAVE_MIN]    = 0x0034;
    m_iComCmd[UARM8_MOTOR_ANG][CMD_SAVE_MAX]    = 0x0035;
    m_iComCmd[UARM8_MOTOR_DTA][CMD_SAVE_MIN]    = 0x0036;
    m_iComCmd[UARM8_MOTOR_DTA][CMD_SAVE_MAX]    = 0x0037;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[UARM8_MOTOR_HEI][CAL_CUR] = 8;
    m_iDataIdx[UARM8_MOTOR_SID][CAL_CUR] = 9;
    m_iDataIdx[UARM8_MOTOR_ANG][CAL_CUR] = 10;
    m_iDataIdx[UARM8_MOTOR_DTA][CAL_CUR] = 11;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[UARM8_MOTOR_HEI][CAL_MIN] = 0;
    m_iDataIdx[UARM8_MOTOR_HEI][CAL_MAX] = 1;
    m_iDataIdx[UARM8_MOTOR_SID][CAL_MIN] = 2;
    m_iDataIdx[UARM8_MOTOR_SID][CAL_MAX] = 3;
    m_iDataIdx[UARM8_MOTOR_ANG][CAL_MIN] = 4;
    m_iDataIdx[UARM8_MOTOR_ANG][CAL_MAX] = 5;
    m_iDataIdx[UARM8_MOTOR_DTA][CAL_MIN] = 6;
    m_iDataIdx[UARM8_MOTOR_DTA][CAL_MAX] = 7;
}
void CMotorBase::InitRail10Data()
{
    //////////////////////////////////////////////////////////////
    m_iComCmd[RAIL10_MOTOR_FID][CMD_UP_PRESS]    = 0x0020;
    m_iComCmd[RAIL10_MOTOR_FID][CMD_UP_RELEASE]  = 0x0021;
    m_iComCmd[RAIL10_MOTOR_FID][CMD_DOWN_PRESS]  = 0x0022;
    m_iComCmd[RAIL10_MOTOR_FID][CMD_DOWN_RELEASE]= 0x0023;
    m_iComCmd[RAIL10_MOTOR_SID][CMD_UP_PRESS]    = 0x0024;
    m_iComCmd[RAIL10_MOTOR_SID][CMD_UP_RELEASE]  = 0x0025;
    m_iComCmd[RAIL10_MOTOR_SID][CMD_DOWN_PRESS]  = 0x0026;
    m_iComCmd[RAIL10_MOTOR_SID][CMD_DOWN_RELEASE]= 0x0027;
    m_iComCmd[RAIL10_MOTOR_ANG][CMD_UP_PRESS]    = 0x0028;
    m_iComCmd[RAIL10_MOTOR_ANG][CMD_UP_RELEASE]  = 0x0029;
    m_iComCmd[RAIL10_MOTOR_ANG][CMD_DOWN_PRESS]  = 0x002a;
    m_iComCmd[RAIL10_MOTOR_ANG][CMD_DOWN_RELEASE]= 0x002b;
    m_iComCmd[RAIL10_MOTOR_DTH][CMD_UP_PRESS]    = 0x002c;
    m_iComCmd[RAIL10_MOTOR_DTH][CMD_UP_RELEASE]  = 0x002d;
    m_iComCmd[RAIL10_MOTOR_DTH][CMD_DOWN_PRESS]  = 0x002e;
    m_iComCmd[RAIL10_MOTOR_DTH][CMD_DOWN_RELEASE]= 0x002f;
    m_iComCmd[RAIL10_MOTOR_BEH][CMD_UP_PRESS]    = 0x0030;
    m_iComCmd[RAIL10_MOTOR_BEH][CMD_UP_RELEASE]  = 0x0031;
    m_iComCmd[RAIL10_MOTOR_BEH][CMD_DOWN_PRESS]  = 0x0032;
    m_iComCmd[RAIL10_MOTOR_BEH][CMD_DOWN_RELEASE]= 0x0033;
    m_iComCmd[RAIL10_MOTOR_DTP][CMD_UP_PRESS]    = 0x0034;
    m_iComCmd[RAIL10_MOTOR_DTP][CMD_UP_RELEASE]  = 0x0035;
    m_iComCmd[RAIL10_MOTOR_DTP][CMD_DOWN_PRESS]  = 0x0036;
    m_iComCmd[RAIL10_MOTOR_DTP][CMD_DOWN_RELEASE]= 0x0037;

    //////////////////////////////////////////////////////////////
    m_iComCmd[RAIL10_MOTOR_FID][CMD_SAVE_MIN]    = 0x0030;
    m_iComCmd[RAIL10_MOTOR_FID][CMD_SAVE_MAX]    = 0x0031;
    m_iComCmd[RAIL10_MOTOR_SID][CMD_SAVE_MIN]    = 0x0032;
    m_iComCmd[RAIL10_MOTOR_SID][CMD_SAVE_MAX]    = 0x0033;
    m_iComCmd[RAIL10_MOTOR_ANG][CMD_SAVE_MIN]    = 0x0034;
    m_iComCmd[RAIL10_MOTOR_ANG][CMD_SAVE_MAX]    = 0x0035;
    m_iComCmd[RAIL10_MOTOR_DTH][CMD_SAVE_MIN]    = 0x0036;
    m_iComCmd[RAIL10_MOTOR_DTH][CMD_SAVE_MAX]    = 0x0037;
    m_iComCmd[RAIL10_MOTOR_BEH][CMD_SAVE_MIN]    = 0x0038;
    m_iComCmd[RAIL10_MOTOR_BEH][CMD_SAVE_MAX]    = 0x0039;
    m_iComCmd[RAIL10_MOTOR_DTP][CMD_SAVE_MIN]    = 0x003A;
    m_iComCmd[RAIL10_MOTOR_DTP][CMD_SAVE_MAX]    = 0x003B;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[RAIL10_MOTOR_FID][CAL_CUR] = 8;
    m_iDataIdx[RAIL10_MOTOR_SID][CAL_CUR] = 9;
    m_iDataIdx[RAIL10_MOTOR_ANG][CAL_CUR] = 10;
    m_iDataIdx[RAIL10_MOTOR_DTH][CAL_CUR] = 11;
    m_iDataIdx[RAIL10_MOTOR_BEH][CAL_CUR] = 12;
    m_iDataIdx[RAIL10_MOTOR_DTP][CAL_CUR] = 13;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[RAIL10_MOTOR_FID][CAL_MIN] = 0;
    m_iDataIdx[RAIL10_MOTOR_FID][CAL_MAX] = 1;
    m_iDataIdx[RAIL10_MOTOR_SID][CAL_MIN] = 2;
    m_iDataIdx[RAIL10_MOTOR_SID][CAL_MAX] = 3;
    m_iDataIdx[RAIL10_MOTOR_ANG][CAL_MIN] = 4;
    m_iDataIdx[RAIL10_MOTOR_ANG][CAL_MAX] = 5;
    m_iDataIdx[RAIL10_MOTOR_DTH][CAL_MIN] = 6;
    m_iDataIdx[RAIL10_MOTOR_DTH][CAL_MAX] = 7;
    m_iDataIdx[RAIL10_MOTOR_BEH][CAL_MIN] = 8;
    m_iDataIdx[RAIL10_MOTOR_BEH][CAL_MAX] = 9;
    m_iDataIdx[RAIL10_MOTOR_DTP][CAL_MIN] = 10;
    m_iDataIdx[RAIL10_MOTOR_DTP][CAL_MAX] = 11;

}
void CMotorBase::InitRail8Data()
{
    //////////////////////////////////////////////////////////////
    m_iComCmd[RAIL8_MOTOR_FID][CMD_UP_PRESS]    = 0x0020;
    m_iComCmd[RAIL8_MOTOR_FID][CMD_UP_RELEASE]  = 0x0021;
    m_iComCmd[RAIL8_MOTOR_FID][CMD_DOWN_PRESS]  = 0x0022;
    m_iComCmd[RAIL8_MOTOR_FID][CMD_DOWN_RELEASE]= 0x0023;
    m_iComCmd[RAIL8_MOTOR_SID][CMD_UP_PRESS]    = 0x0024;
    m_iComCmd[RAIL8_MOTOR_SID][CMD_UP_RELEASE]  = 0x0025;
    m_iComCmd[RAIL8_MOTOR_SID][CMD_DOWN_PRESS]  = 0x0026;
    m_iComCmd[RAIL8_MOTOR_SID][CMD_DOWN_RELEASE]= 0x0027;
    m_iComCmd[RAIL8_MOTOR_ANG][CMD_UP_PRESS]    = 0x0028;
    m_iComCmd[RAIL8_MOTOR_ANG][CMD_UP_RELEASE]  = 0x0029;
    m_iComCmd[RAIL8_MOTOR_ANG][CMD_DOWN_PRESS]  = 0x002a;
    m_iComCmd[RAIL8_MOTOR_ANG][CMD_DOWN_RELEASE]= 0x002b;
    m_iComCmd[RAIL8_MOTOR_DTH][CMD_UP_PRESS]    = 0x002c;
    m_iComCmd[RAIL8_MOTOR_DTH][CMD_UP_RELEASE]  = 0x002d;
    m_iComCmd[RAIL8_MOTOR_DTH][CMD_DOWN_PRESS]  = 0x002e;
    m_iComCmd[RAIL8_MOTOR_DTH][CMD_DOWN_RELEASE]= 0x002f;
    m_iComCmd[RAIL8_MOTOR_BEH][CMD_UP_PRESS]    = 0x0030;
    m_iComCmd[RAIL8_MOTOR_BEH][CMD_UP_RELEASE]  = 0x0031;
    m_iComCmd[RAIL8_MOTOR_BEH][CMD_DOWN_PRESS]  = 0x0032;
    m_iComCmd[RAIL8_MOTOR_BEH][CMD_DOWN_RELEASE]= 0x0033;
    m_iComCmd[RAIL8_MOTOR_DTP][CMD_UP_PRESS]    = 0x0034;
    m_iComCmd[RAIL8_MOTOR_DTP][CMD_UP_RELEASE]  = 0x0035;
    m_iComCmd[RAIL8_MOTOR_DTP][CMD_DOWN_PRESS]  = 0x0036;
    m_iComCmd[RAIL8_MOTOR_DTP][CMD_DOWN_RELEASE]= 0x0037;

    //////////////////////////////////////////////////////////////
    m_iComCmd[RAIL8_MOTOR_FID][CMD_SAVE_MIN]    = 0x0030;
    m_iComCmd[RAIL8_MOTOR_FID][CMD_SAVE_MAX]    = 0x0031;
    m_iComCmd[RAIL8_MOTOR_SID][CMD_SAVE_MIN]    = 0x0032;
    m_iComCmd[RAIL8_MOTOR_SID][CMD_SAVE_MAX]    = 0x0033;
    m_iComCmd[RAIL8_MOTOR_ANG][CMD_SAVE_MIN]    = 0x0034;
    m_iComCmd[RAIL8_MOTOR_ANG][CMD_SAVE_MAX]    = 0x0035;
    m_iComCmd[RAIL8_MOTOR_DTH][CMD_SAVE_MIN]    = 0x0036;
    m_iComCmd[RAIL8_MOTOR_DTH][CMD_SAVE_MAX]    = 0x0037;
    m_iComCmd[RAIL8_MOTOR_BEH][CMD_SAVE_MIN]    = 0x0038;
    m_iComCmd[RAIL8_MOTOR_BEH][CMD_SAVE_MAX]    = 0x0039;
    m_iComCmd[RAIL8_MOTOR_DTP][CMD_SAVE_MIN]    = 0x003A;
    m_iComCmd[RAIL8_MOTOR_DTP][CMD_SAVE_MAX]    = 0x003B;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[RAIL8_MOTOR_FID][CAL_CUR] = 8;
    m_iDataIdx[RAIL8_MOTOR_SID][CAL_CUR] = 9;
    m_iDataIdx[RAIL8_MOTOR_ANG][CAL_CUR] = 10;
    m_iDataIdx[RAIL8_MOTOR_DTH][CAL_CUR] = 11;
    m_iDataIdx[RAIL8_MOTOR_BEH][CAL_CUR] = 12;
    m_iDataIdx[RAIL8_MOTOR_DTP][CAL_CUR] = 13;

    //////////////////////////////////////////////////////////////
    m_iDataIdx[RAIL8_MOTOR_FID][CAL_MIN] = 0;
    m_iDataIdx[RAIL8_MOTOR_FID][CAL_MAX] = 1;
    m_iDataIdx[RAIL8_MOTOR_SID][CAL_MIN] = 2;
    m_iDataIdx[RAIL8_MOTOR_SID][CAL_MAX] = 3;
    m_iDataIdx[RAIL8_MOTOR_ANG][CAL_MIN] = 4;
    m_iDataIdx[RAIL8_MOTOR_ANG][CAL_MAX] = 5;
    m_iDataIdx[RAIL8_MOTOR_DTH][CAL_MIN] = 6;
    m_iDataIdx[RAIL8_MOTOR_DTH][CAL_MAX] = 7;
    m_iDataIdx[RAIL8_MOTOR_BEH][CAL_MIN] = 8;
    m_iDataIdx[RAIL8_MOTOR_BEH][CAL_MAX] = 9;
    m_iDataIdx[RAIL8_MOTOR_DTP][CAL_MIN] = 10;
    m_iDataIdx[RAIL8_MOTOR_DTP][CAL_MAX] = 11;
}
void CMotorBase::InitCeil10aMotor(int motor)
{
    switch(motor)
    {
    case CEIL10a_MOTOR_FID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube minimum height set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube maximum height set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case CEIL10a_MOTOR_SID:
        textTitle->setText(QApplication::translate("CMotorBase", "Ceilling Position X Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Ceilling position X minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Ceilling position X maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    case CEIL10a_MOTOR_ANG:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube angle minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube angle maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        break;
    case CEIL10a_MOTOR_DTH:
        textTitle->setText(QApplication::translate("CMotorBase", "Stand Detector Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand Detector Minimum Height Set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand Detector Maximum Height Set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case CEIL10a_MOTOR_DTA:
        textTitle->setText(QApplication::translate("CMotorBase", "Stand Detector Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand detector minimum angle set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Press key to rotate the detector, when the detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree press save button." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand detector maximum angle set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Press key to rotate the detector, when the detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree press save button." ));
        break;
    case CEIL10a_MOTOR_CEP:
        textTitle->setText(QApplication::translate("CMotorBase", "Ceilling Position Y Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Ceilling position Y minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Ceilling position Y maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    case CEIL10a_MOTOR_BEH:
        textTitle->setText(QApplication::translate("CMotorBase", "Table Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table height minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust the table height; make the surface of table" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table height maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust the table height; make the surface of table" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case CEIL10a_MOTOR_DTP:
        textTitle->setText(QApplication::translate("CMotorBase", "Table Bucky Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table bucky position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table bucky position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        break;
    default:
        break;
    }
}

void CMotorBase::InitRf8aMotor(int motor)
{
    switch(motor)
    {
    case RF8A_MOTOR_FID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube minimum height set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube maximum height set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case RF8A_MOTOR_DTP:
        textTitle->setText(QApplication::translate("CMotorBase", "Table Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Ceilling position X minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Ceilling position X maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    case RF8A_MOTOR_SID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube angle minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube angle maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        break;
    case RF8A_MOTOR_ANG:
        textTitle->setText(QApplication::translate("CMotorBase", "Table Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand Detector Minimum Height Set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand Detector Maximum Height Set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case RF8A_MOTOR_PRL:
        textTitle->setText(QApplication::translate("CMotorBase", "Foot Pedal Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand detector minimum angle set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Press key to rotate the detector, when the detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree press save button." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand detector maximum angle set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Press key to rotate the detector, when the detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree press save button." ));
        break;
    case RF8A_MOTOR_PYP:
        textTitle->setText(QApplication::translate("CMotorBase", "Compressor Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Ceilling position Y minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Ceilling position Y maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    case RF8A_MOTOR_SGH:
        textTitle->setText(QApplication::translate("CMotorBase", "Collimator Horizontal Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table height minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust the table height; make the surface of table" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table height maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust the table height; make the surface of table" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case RF8A_MOTOR_SGV:
        textTitle->setText(QApplication::translate("CMotorBase", "Collimator Vertical Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table bucky position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table bucky position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        break;
    default:
        break;
    }
}

void CMotorBase::InitNdt8aMotor(int motor)
{
    switch(motor)
    {
    case NDT8a_MOTOR_FID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube minimum height set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube maximum height set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case NDT8a_MOTOR_X1:
        textTitle->setText(QApplication::translate("CMotorBase", "Panel X Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Panel position X minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Panel X position; make the center of panel" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the x start point then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Panel position X maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Panel X position; make the center of panel" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the x start point then press save." ));
        break;
    case NDT8a_MOTOR_Y1:
        textTitle->setText(QApplication::translate("CMotorBase", "Panel Y Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Panel position Y minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Panel Y position; make the center of panel" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the start Y point then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Panel position Y maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Panel Y position; make the center of panel" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the start Y point then press save." ));
        break;
    case NDT8a_MOTOR_X2:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube X Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube position X minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Tube X position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the start X point then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube position X maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Tube X position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the start X point then press save." ));
        break;
    case NDT8a_MOTOR_Y2:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Y Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube position Y minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Tube Y position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the start Y point then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube position Y maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Tube Y position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the start Y point then press save." ));
        break;  
    default:
        break;
    }
}
void CMotorBase::InitCeil10bMotor(int motor)
{
    switch(motor)
    {
    case CEIL10b_MOTOR_FID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube minimum height set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube maximum height set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case CEIL10b_MOTOR_SID:
        textTitle->setText(QApplication::translate("CMotorBase", "Ceilling Position X Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Ceilling position X minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Ceilling position X maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    case CEIL10b_MOTOR_ANG:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube angle minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube angle maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        break;
    case CEIL10b_MOTOR_DTH:
        textTitle->setText(QApplication::translate("CMotorBase", "Stand Detector Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand Detector Minimum Height Set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand Detector Maximum Height Set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case CEIL10b_MOTOR_DTA:
        textTitle->setText(QApplication::translate("CMotorBase", "Stand Detector Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand detector minimum angle set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Press key to rotate the detector, when the detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree press save button." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand detector maximum angle set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Press key to rotate the detector, when the detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree press save button." ));
        break;
    case CEIL10b_MOTOR_CEP:
        textTitle->setText(QApplication::translate("CMotorBase", "Ceilling Position Y Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Ceilling position Y minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Ceilling position Y maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    default:
        break;
    }
}
void CMotorBase::InitCeil8Motor(int motor)
{
    switch(motor)
    {
    case CEIL8_MOTOR_FID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube minimum height set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube maximum height set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case CEIL8_MOTOR_SID:
        textTitle->setText(QApplication::translate("CMotorBase", "Ceilling Position X Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Ceilling position X minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Ceilling position X maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust ceilling position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    case CEIL8_MOTOR_ANG:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube angle minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube angle maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        break;
    case CEIL8_MOTOR_DTH:
        textTitle->setText(QApplication::translate("CMotorBase", "Stand Detector Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand Detector Minimum Height Set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand Detector Maximum Height Set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case CEIL8_MOTOR_DTA:
        textTitle->setText(QApplication::translate("CMotorBase", "Stand Detector Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand detector minimum angle set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Press key to rotate the detector, when the detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree press save button." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand detector maximum angle set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Press key to rotate the detector, when the detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree press save button." ));
        break;
    default:
        break;
    }
}
void CMotorBase::InitUarm10Motor(int motor)
{
    switch(motor)
    {
    case UARM10_MOTOR_HEI:
        textTitle->setText(QApplication::translate("CMotorBase", "Uarm Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table bucky position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table bucky position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        break;
    case UARM10_MOTOR_SID:
        textTitle->setText(QApplication::translate("CMotorBase", "Uarm Fid Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table bucky position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table bucky position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        break;
    case UARM10_MOTOR_ANG:
        textTitle->setText(QApplication::translate("CMotorBase", "Uarm Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table bucky position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table bucky position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        break;
    case UARM10_MOTOR_DTA:
        textTitle->setText(QApplication::translate("CMotorBase", "Uarm Detector Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table bucky position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table bucky position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        break;
    default:
        break;
    }
}

void CMotorBase::InitUarm8Motor(int motor)
{
    switch(motor)
    {
    case UARM8_MOTOR_HEI:
        textTitle->setText(QApplication::translate("CMotorBase", "Uarm Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Uarm height minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust uarm height; make the center of uarm" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Uarm height maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust uarm height; make the center of uarm" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from ground then press save." ));
        break;
    case UARM8_MOTOR_SID:
        textTitle->setText(QApplication::translate("CMotorBase", "Uarm Fid Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from detector then press save." ));
        break;
    case UARM8_MOTOR_ANG:
        textTitle->setText(QApplication::translate("CMotorBase", "Uarm Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Uarm Angle minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust uarm angle; make the angle of uarm" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Uarm Angle maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust uarm angle; make the angle of uarm" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        break;
    case UARM8_MOTOR_DTA:
        textTitle->setText(QApplication::translate("CMotorBase", "Uarm Detector Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Detector Angle minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust detector angle; make the angle of detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree from uarm then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Detector Angle maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust detector angle; make the angle of detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree from uarm then press save." ));
        break;

    default:
        break;
    }
}
void CMotorBase::InitRail10Motor(int motor)
{
    switch(motor)
    {
    case RAIL10_MOTOR_FID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube minimum height set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube maximum height set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case RAIL10_MOTOR_SID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Position Adjustment(SID)" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    case RAIL10_MOTOR_ANG:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube angle minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube angle maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        break;
    case RAIL10_MOTOR_DTH:
        textTitle->setText(QApplication::translate("CMotorBase", "Stand Detector Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand Detector Minimum Height Set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand Detector Maximum Height Set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case RAIL10_MOTOR_DTP:
        textTitle->setText(QApplication::translate("CMotorBase", "Table Bucky Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table bucky position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table bucky position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        break;
    case RAIL10_MOTOR_BEH:
        textTitle->setText(QApplication::translate("CMotorBase", "Table Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table height minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust the table height; make the surface of table" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table height maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust the table height; make the surface of table" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    default:
        break;
    }
}
void CMotorBase::InitRail8Motor(int motor)
{
    switch(motor)
    {
    case RAIL8_MOTOR_FID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube minimum height set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube maximum height set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube height; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case RAIL8_MOTOR_SID:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Position Adjustment(SID)" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube position; make the center of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube position; make the center of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from the stand detector then press save." ));
        break;
    case RAIL8_MOTOR_ANG:
        textTitle->setText(QApplication::translate("CMotorBase", "Tube Angle Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Tube angle minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Tube angle maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust tube angle; make the angle of tube" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "degree from ground then press save." ));
        break;
    case RAIL8_MOTOR_DTH:
        textTitle->setText(QApplication::translate("CMotorBase", "Stand Detector Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Stand Detector Minimum Height Set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Stand Detector Maximum Height Set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust Detector Height; Make the center of Detector" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    case RAIL8_MOTOR_DTP:
        textTitle->setText(QApplication::translate("CMotorBase", "Table Bucky Position Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table bucky position minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table bucky position maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust table bucky position; make the center of bucky" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm from stand detector then press save." ));
        break;
    case RAIL8_MOTOR_BEH:
        textTitle->setText(QApplication::translate("CMotorBase", "Table Height Adjustment" ));
        lbMinTitle->setText(QApplication::translate("CMotorBase", "1.Table height minimum set:" ));
        lbMinInfo1->setText(QApplication::translate("CMotorBase", "Adjust the table height; make the surface of table" ));
        lbMinInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        lbMaxTitle->setText(QApplication::translate("CMotorBase", "2.Table height maximum set:" ));
        lbMaxInfo1->setText(QApplication::translate("CMotorBase", "Adjust the table height; make the surface of table" ));
        lbMaxInfo2->setText(QApplication::translate("CMotorBase", "mm over the ground then press save." ));
        break;
    default:
        break;
    }
}
