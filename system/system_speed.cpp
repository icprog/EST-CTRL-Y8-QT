#include <QSettings>

#include "system_speed.h"
#include "sys_database.h"
#include "resource_manager.h"

CSystemSpeed::CSystemSpeed( unsigned short mPlatform,QWidget* parent ):
    CSystemBase(parent)
{     

    setObjectName("CSystemSpeed");

    resize(600,600);

    m_iFocusCurrent = 0;

    for(int mIdx = 0 ; mIdx < SPEED_BTN_SLOW ; mIdx++)
    {
        pFrameLine[mIdx] = new QFrame(this);
        pFrameLine[mIdx]->setGeometry(QRect(20, 100 + mIdx * 50, 560, 10));
        pFrameLine[mIdx]->setFrameShape(QFrame::HLine);
        pFrameLine[mIdx]->setFrameShadow(QFrame::Sunken);

        pLabel[mIdx] = new QLabel(this);
        pLabel[mIdx]->setGeometry(QRect(10, 60 + mIdx * 50, 201, 40));

        pLabelGroup[mIdx] = new QLabel(this);
        pLabelGroup[mIdx]->setGeometry(QRect(330, 60 + mIdx * 50, 111, 40));
        pLabelGroup[mIdx]->setText(QApplication::translate("CSystemSpeed", "Max power:"));

        pEditSpeed[mIdx] = new QLabel(this);
        pEditSpeed[mIdx]->setGeometry(QRect(210, 60 + mIdx * 50, 115, 40));
        pEditSpeed[mIdx]->setStyleSheet("background-color: white;border : 2px solid black;");
        pEditSpeed[mIdx]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //pEditSpeed[mIdx]->setFrameShape(QFrame::Panel);
        //pEditSpeed[mIdx]->setLineWidth(2);
        pEditSpeed[mIdx]->installEventFilter(this);

        pEditMax[mIdx] = new QLabel(this);
        pEditMax[mIdx]->setGeometry(QRect(450, 60 + mIdx * 50, 115, 40));
        pEditMax[mIdx]->setStyleSheet("background-color : yellow ; color : darkBlue; border : 1px solid black;");
        pEditMax[mIdx]->setFrameShape(QFrame::Panel);
        pEditMax[mIdx]->setLineWidth(2);

    }
    pEditSpeed[0]->setStyleSheet("background-color: white;border : 3px solid green;");

    btSave = new CButtonStable(this);
    btSave->setGeometry(QRect(425, 525, 100, 60));
    btSave->setText(QApplication::translate("CSystemSpeed", "SAVE"));
    btSave->setFocusPolicy(Qt::NoFocus);

    lbSave = new QLabel(this);
    lbSave->setGeometry(QRect(0, 460, 600, 40));
    lbSave->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbSave->setStyleSheet("color : red");
    lbSave->setText(QApplication::translate("CSystemSpeed", "Save Successful!"));

    timerSpeedFresh = new QTimer();
    connect(timerSpeedFresh,SIGNAL(timeout()),this,SLOT(OnSpeedFresh()));

    connect(btSave,SIGNAL(pressed()),this,SLOT(OnSpeedClickSave()));
    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnSpeedClickIndex()) );

    textTitle->setText(QApplication::translate("CSystemSpeed", "Motor Speed setting"));

    InitSpeedCfg(mPlatform);

    translateFontSize( this );

    setVisible(false);
}

void CSystemSpeed::InitSpeedCfg(unsigned short mPf)
{
    switch(mPf)
    {
    case PF_NDT_8_A:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Tube height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Panel Posi.X:" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Panel Posi.Y:" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Tube Posi.X:" ));
        pLabel[4]->setText(QApplication::translate("CSystemSpeed", "Tube Posi.Y:" ));
        for(int mIdx = 5 ; mIdx < SPEED_BTN_SLOW ; mIdx++)
        {
            pLabel[mIdx]->setVisible(false);
            pLabelGroup[mIdx]->setVisible(false);
            pEditMax[mIdx]->setVisible(false);
            pEditSpeed[mIdx]->setVisible(false);
        }
        mMotorMax = 5;
        break;
    case PF_CEIL_10_A:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Tube height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Ceilling X(SID):" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Tube angle(ANG):" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Detector height(DTH):" ));
        pLabel[4]->setText(QApplication::translate("CSystemSpeed", "Detector angle(DTA):" ));
        pLabel[5]->setText(QApplication::translate("CSystemSpeed", "Ceilling Y(CEP):" ));
        pLabel[6]->setText(QApplication::translate("CSystemSpeed", "Table height(BEH):" ));
        pLabel[7]->setText(QApplication::translate("CSystemSpeed", "Table Bucky(DTP):" ));
        mMotorMax = 8;
        break;
    case PF_RF_8_A:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Tube height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Table Posi.(DTP):" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Tube Posi.(SID):" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Table Angle(ANG):" ));
        pLabel[4]->setText(QApplication::translate("CSystemSpeed", "Foot Pedal(PRL):" ));
        pLabel[5]->setText(QApplication::translate("CSystemSpeed", "Compressor(PYP):" ));
        pLabel[6]->setText(QApplication::translate("CSystemSpeed", "Collimator H(SGH):" ));
        pLabel[7]->setText(QApplication::translate("CSystemSpeed", "Collimator V(SGV):" ));
        mMotorMax = 8;
        break;
    case PF_CEIL_10_B:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Tube height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Ceilling X(SID):" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Tube angle(ANG):" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Detector height(DTH):" ));
        pLabel[4]->setText(QApplication::translate("CSystemSpeed", "Detector angle(DTA):" ));
        pLabel[5]->setText(QApplication::translate("CSystemSpeed", "Ceilling Y(CEP):" ));
        for(int mIdx = 6 ; mIdx < SPEED_BTN_SLOW ; mIdx++)
        {
            pLabel[mIdx]->setVisible(false);
            pLabelGroup[mIdx]->setVisible(false);
            pEditMax[mIdx]->setVisible(false);
            pEditSpeed[mIdx]->setVisible(false);
        }
        mMotorMax = 6;
        break;
    case PF_CEIL_08_A:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Tube height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Ceilling X(SID):" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Tube angle(ANG):" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Detector height(DTH):" ));
        pLabel[4]->setText(QApplication::translate("CSystemSpeed", "Detector angle(DTA):" ));
        for(int mIdx = 5 ; mIdx < SPEED_BTN_SLOW ; mIdx++)
        {
            pLabel[mIdx]->setVisible(false);
            pLabelGroup[mIdx]->setVisible(false);
            pEditMax[mIdx]->setVisible(false);
            pEditSpeed[mIdx]->setVisible(false);
        }
        mMotorMax = 5;
        break;
    case PF_UARM_10_A:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Uarm height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Tube position(SID):" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Uarm angle(ANG):" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Detector angle(DTA):" ));
        for(int mIdx = 4 ; mIdx < SPEED_BTN_SLOW ; mIdx++)
        {
            pLabel[mIdx]->setVisible(false);
            pLabelGroup[mIdx]->setVisible(false);
            pEditMax[mIdx]->setVisible(false);
            pEditSpeed[mIdx]->setVisible(false);
        }
        mMotorMax = 4;
        break;
    case PF_UARM_08_A:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Uarm height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Tube position(SID):" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Uarm angle(ANG):" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Detector angle(DTA):" ));
        for(int mIdx = 4 ; mIdx < SPEED_BTN_SLOW ; mIdx++)
        {
            pLabel[mIdx]->setVisible(false);
            pLabelGroup[mIdx]->setVisible(false);
            pEditMax[mIdx]->setVisible(false);
            pEditSpeed[mIdx]->setVisible(false);
        }
        mMotorMax = 4;
        break;
    case PF_RAIL_12_A:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Tube height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Tube Distance(SID):" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Tube angle(ANG):" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Detector height(DTH):" ));
        pLabel[4]->setText(QApplication::translate("CSystemSpeed", "Table height(BEH):" ));
        pLabel[5]->setText(QApplication::translate("CSystemSpeed", "Table Bucky(DTP):" ));
        for(int mIdx = 6 ; mIdx < SPEED_BTN_SLOW ; mIdx++)
        {
            pLabel[mIdx]->setVisible(false);
            pLabelGroup[mIdx]->setVisible(false);
            pEditMax[mIdx]->setVisible(false);
            pEditSpeed[mIdx]->setVisible(false);
        }
        mMotorMax = 6;
        break;
    case PF_RAIL_08_A:
        pLabel[0]->setText(QApplication::translate("CSystemSpeed", "Tube height(FID):" ));
        pLabel[1]->setText(QApplication::translate("CSystemSpeed", "Tube Distance(SID):" ));
        pLabel[2]->setText(QApplication::translate("CSystemSpeed", "Tube angle(ANG):" ));
        pLabel[3]->setText(QApplication::translate("CSystemSpeed", "Detector height(DTH):" ));
        pLabel[4]->setText(QApplication::translate("CSystemSpeed", "Table height(BEH):" ));
        pLabel[5]->setText(QApplication::translate("CSystemSpeed", "Table Bucky(DTP):" ));
        for(int mIdx = 6 ; mIdx < SPEED_BTN_SLOW ; mIdx++)
        {
            pLabel[mIdx]->setVisible(false);
            pLabelGroup[mIdx]->setVisible(false);
            pEditMax[mIdx]->setVisible(false);
            pEditSpeed[mIdx]->setVisible(false);
        }
        mMotorMax = 6;
        break;
    default:
        mMotorMax = 0;
        break;
    }
}

void CSystemSpeed::showEvent(QShowEvent * event)
{  

    QString mStr;
    for(int mIdx = 0 ;mIdx < SPEED_BTN_SLOW ;mIdx++)
    {
        mStr.setNum(g_systemDb->g_dbMachine.SlowData[mIdx]);
        pEditSpeed[mIdx]->setText(mStr);
        pEditMax[mIdx]->setText("99");
    }

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad = new CSystemImepad(this);

    g_systemDb->g_bDataSaved = false;
    lbSave->hide();

    timerSpeedFresh->start(TIME_SCREEN_FRESH);


    CSystemBase::showEvent(event);
}

void CSystemSpeed::hideEvent(QHideEvent *event)
{

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    timerSpeedFresh->stop();

    releaseKeyboard();

    CSystemBase::hideEvent(event);
}

void CSystemSpeed::OnSpeedFresh()
{
    if(g_systemDb->g_bDataSaved)
    {
        lbSave->show();
        g_systemDb->g_bDataSaved=false;
    }
}
void CSystemSpeed::OnSpeedClickSave()
{
    unsigned short  buf[10];
    int mIdx;

    QString strBuf;

    lbSave->hide();

    buf[0] =0;
    buf[1] =0x0040;

    QSettings * iniSpeed = new QSettings(QCoreApplication::applicationDirPath() + "/speed_setting.ini",QSettings::IniFormat);

    for(mIdx = 0 ;mIdx < SPEED_BTN_SLOW ; mIdx++)
    {
        g_systemDb->g_dbMachine.SlowData[mIdx] = pEditSpeed[mIdx]->text().toInt();
        buf[2 +mIdx] = g_systemDb->g_dbMachine.SlowData[mIdx];

        strBuf.sprintf("data/slow_%02d",mIdx);

        iniSpeed->setValue(strBuf,buf[2 +mIdx]);
    }

    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);


}
void CSystemSpeed::OnSpeedClickIndex()
{

    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
    }
} 

bool CSystemSpeed::eventFilter(QObject *watched, QEvent *event)
{

    for(int mIdx = 0 ;mIdx < SPEED_BTN_SLOW ; mIdx++)
    {
        if(pEditSpeed[mIdx] == watched)
        {
            if(event->type()==QEvent::MouseButtonPress)
            {
                g_systemPad->move(340 ,60 + mIdx * 15);

                g_systemPad->show();
                m_iFocusCurrent = mIdx;
                m_strKeyBuff = "";
            }
        }
    }

    return QWidget::eventFilter(watched,event);
}

void CSystemSpeed::keyPressEvent ( QKeyEvent * event )
{
    int mKey = event->key();
    switch (mKey)
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        OnSpeedClickSave();
        break;
    case Qt::Key_Backspace:
        m_strKeyBuff.chop( 1);
        pEditSpeed[m_iFocusCurrent]->setText(m_strKeyBuff);
        break;
    case Qt::Key_Escape:
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        break;
    case Qt::Key_Tab:
        pEditSpeed[m_iFocusCurrent]->setStyleSheet("background-color: white;border: 2px solid black;");
        if(++m_iFocusCurrent >= mMotorMax)
            m_iFocusCurrent = 0;
        pEditSpeed[m_iFocusCurrent]->setStyleSheet("background-color: white;border: 3px solid green;");
        m_strKeyBuff = pEditSpeed[m_iFocusCurrent]->text();
        break;
    default:
        if(m_strKeyBuff.length() < 3 &&( (mKey >= Qt::Key_0 &&  mKey <= Qt::Key_9) || ( mKey >= Qt::Key_A  &&  mKey <= Qt::Key_Z)))
            m_strKeyBuff.append(event->key());

        pEditSpeed[m_iFocusCurrent]->setText(m_strKeyBuff);
        break;
    }
}
