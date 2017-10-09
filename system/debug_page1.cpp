
#include "debug_page1.h"
#include "sys_database.h"
#include "resource_manager.h"

CDebugPage1::CDebugPage1( int mpf , QWidget* parent ):
    CDebugBase(parent)
{     

    setObjectName("CDebugPage1");

    resize(600,600);

    textTitle->setText(QApplication::translate("CDebugBase", "Motor Debug Form A"));

    plbMessage[0] = new QLabel(this);
    plbMessage[0]->setGeometry(QRect(20, 400, 245, 40));
    plbMessage[0]->setText(QApplication::translate("CDebugBase", "Electromagnetic brake:"));
    plbMessage[0]->lower();

    plbMessage[1] = new QLabel(this);
    plbMessage[1]->setGeometry(QRect(360, 400, 161, 40));
    plbMessage[1]->setText(QApplication::translate("CDebugBase", "Switch input:"));
    plbMessage[1]->lower();

    plbMessage[2] = new QLabel(this);
    plbMessage[2]->setGeometry(QRect(20, 55, 580, 40));
    plbMessage[2]->setStyleSheet("color : red");
    plbMessage[2]->lower();

    QString mStr;
    for(int mIdx = CHANNEL_MAX ; mIdx < DEBUG_LIMIT_MAX / 2 ; mIdx ++)
    {
        pLimitFrame[mIdx * 2] = new QFrame(this);
        pLimitFrame[mIdx * 2]->setGeometry(QRect(355 + (mIdx - CHANNEL_MAX) * 95, 440, 20, 20));
        pLimitFrame[mIdx * 2]->setStyleSheet("QFrame { background-color : white;}");

        pLimitFrame[mIdx * 2 + 1] = new QFrame(this);
        pLimitFrame[mIdx * 2 + 1]->setGeometry(QRect(355 + (mIdx - CHANNEL_MAX) * 95, 470, 20, 20));
        pLimitFrame[mIdx * 2 + 1]->setStyleSheet("QFrame { background-color : white;}");

        pLimitText[mIdx * 2] = new QLabel(this);
        pLimitText[mIdx * 2]->setGeometry(QRect(295 + (mIdx - CHANNEL_MAX) * 95, 440, 61, 20));

        pLimitText[mIdx * 2 + 1] = new QLabel(this);
        pLimitText[mIdx * 2 + 1]->setGeometry(QRect(295 + (mIdx - CHANNEL_MAX) * 95, 470, 61, 20));

        mStr.sprintf("IN%d",mIdx * 2 + 1);
        pLimitText[mIdx * 2]->setText(mStr);
        mStr.sprintf("IN%d",mIdx * 2 + 2);
        pLimitText[mIdx * 2+1]->setText(mStr);
    }

    pBtnGroup[0]->setText("A-");
    pBtnGroup[1]->setText("A+");
    pBtnGroup[2]->setText("B-");
    pBtnGroup[3]->setText("B+");
    pBtnGroup[4]->setText("C-");
    pBtnGroup[5]->setText("C+");
    pBtnGroup[6]->setText("D-");
    pBtnGroup[7]->setText("D+");
    pBtnGroup[8]->setText("E-");
    pBtnGroup[9]->setText("E+");
    pBtnGroup[10]->setText("F-");
    pBtnGroup[11]->setText("F+");

    QFont font;
    font.setPixelSize(SYS_FONT(32));
    pBtnBrake[BRAKE_A] = new CButtonStable(this);
    pBtnBrake[BRAKE_A]->setGeometry(QRect(30, 435, 100, 61));
    pBtnBrake[BRAKE_A]->setStyleSheet("background-color : darkGray ; color : red ; border : 1px solid black");
    pBtnBrake[BRAKE_A]->setText("A");
    pBtnBrake[BRAKE_A]->setFont(font);
    pBtnBrake[BRAKE_B] = new CButtonStable(this);
    pBtnBrake[BRAKE_B]->setGeometry(QRect(170, 435, 100, 61));
    pBtnBrake[BRAKE_B]->setStyleSheet("background-color : darkGray ; color : red; border : 1px solid black");
    pBtnBrake[BRAKE_B]->setText("B");
    pBtnBrake[BRAKE_B]->setFont(font);

    btNext = new CButtonStable(this);
    btNext->setGeometry(QRect(420, 525, 110, 60));
    btNext->setText(QApplication::translate("CDebugBase", "NEXT"));

    btDebugCtrl = new CButtonStable(this);
    btDebugCtrl->setGeometry(QRect(70, 525, 110, 60));
    btDebugCtrl->setText(QApplication::translate("CDebugBase", "DEBUG"));

    m_bBrakeState[BRAKE_A] = false;
    m_bBrakeState[BRAKE_B] = false;

    m_bDebugEnable = false;

    connect(pBtnBrake[BRAKE_A],   SIGNAL(pressed()),this,SLOT(OnBrakePressed()));
    connect(pBtnBrake[BRAKE_B],   SIGNAL(pressed()),this,SLOT(OnBrakePressed()));

    connect(btnExit,    SIGNAL(pressed()),this,SLOT(OnDebug1Click()));
    connect(btNext,     SIGNAL(pressed()),this,SLOT(OnDebug1Click()));
    connect(btDebugCtrl,SIGNAL(pressed()),this,SLOT(OnDebug1Click()));

    translateFontSize( this );

    InitPlatform(mpf);

    setVisible(false);
}

void CDebugPage1::InitPlatform(int mpf)
{

    switch(mpf)
    {
    case PF_NDT_8_A:
    case PF_RF_8_A:
        m_iMotorMax = 6;

        plbMessage[2]->setText(QApplication::translate("CDebugBase", "Keep Break B pressed when lifting frame up and down!"));

        pKeycodePressed[0] = 0x0022;
        pKeycodePressed[1] = 0x0020;
        pKeycodePressed[2] = 0x0026;
        pKeycodePressed[3] = 0x0024;
        pKeycodePressed[4] = 0x002a;
        pKeycodePressed[5] = 0x0028;
        pKeycodePressed[6] = 0x002e;
        pKeycodePressed[7] = 0x002c;
        pKeycodePressed[8] = 0x0032;
        pKeycodePressed[9] = 0x0030;
        pKeycodePressed[10]= 0x0036;
        pKeycodePressed[11]= 0x0034;

        for(int mIdx = 0 ; mIdx < m_iMotorMax * 2 ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        pKeycodeBrake[2 * BRAKE_A ]     = 0x0040;
        pKeycodeBrake[2 * BRAKE_A + 1]  = 0x0041;
        pKeycodeBrake[2 * BRAKE_B ]     = 0x0042;
        pKeycodeBrake[2 * BRAKE_B + 1]  = 0x0043;

        pLimitFrame[12]->setVisible(false);
        pLimitText[12]->setVisible(false);
        pLimitFrame[13]->setVisible(false);
        pLimitText[13]->setVisible(false);
        pLimitFrame[14]->setVisible(false);
        pLimitText[14]->setVisible(false);
        pLimitFrame[15]->setVisible(false);
        pLimitText[15]->setVisible(false);
        break;
    case PF_NDT_10_A:
    case PF_CEIL_10_A:
        m_iMotorMax = 6;

        plbMessage[2]->setText(QApplication::translate("CDebugBase", "Keep Break B pressed when lifting frame up and down!"));

        pKeycodePressed[0] = 0x0022;
        pKeycodePressed[1] = 0x0020;
        pKeycodePressed[2] = 0x0026;
        pKeycodePressed[3] = 0x0024;
        pKeycodePressed[4] = 0x002a;
        pKeycodePressed[5] = 0x0028;
        pKeycodePressed[6] = 0x002e;
        pKeycodePressed[7] = 0x002c;
        pKeycodePressed[8] = 0x0032;
        pKeycodePressed[9] = 0x0030;
        pKeycodePressed[10]= 0x0036;
        pKeycodePressed[11]= 0x0034;

        for(int mIdx = 0 ; mIdx < m_iMotorMax * 2 ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        pKeycodeBrake[2 * BRAKE_A ]     = 0x0040;
        pKeycodeBrake[2 * BRAKE_A + 1]  = 0x0041;
        pKeycodeBrake[2 * BRAKE_B ]     = 0x0042;
        pKeycodeBrake[2 * BRAKE_B + 1]  = 0x0043;

        pLimitFrame[12]->setVisible(false);
        pLimitText[12]->setVisible(false);
        pLimitFrame[13]->setVisible(false);
        pLimitText[13]->setVisible(false);
        pLimitFrame[14]->setVisible(false);
        pLimitText[14]->setVisible(false);
        pLimitFrame[15]->setVisible(false);
        pLimitText[15]->setVisible(false);
        break;
    case PF_CEIL_10_B:

        plbMessage[2]->setText(QApplication::translate("CDebugBase", "Keep Break B pressed when lifting frame up and down!"));

        pKeycodePressed[0] = 0x0022;
        pKeycodePressed[1] = 0x0020;
        pKeycodePressed[2] = 0x0026;
        pKeycodePressed[3] = 0x0024;
        pKeycodePressed[4] = 0x002a;
        pKeycodePressed[5] = 0x0028;
        pKeycodePressed[6] = 0x002e;
        pKeycodePressed[7] = 0x002c;
        pKeycodePressed[8] = 0x0032;
        pKeycodePressed[9] = 0x0030;
        pKeycodePressed[10]= 0x0036;
        pKeycodePressed[11]= 0x0034;

        for(int mIdx = 0 ; mIdx < BTN_MAX ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        pKeycodeBrake[2 * BRAKE_A ]     = 0x0040;
        pKeycodeBrake[2 * BRAKE_A + 1]  = 0x0041;
        pKeycodeBrake[2 * BRAKE_B ]     = 0x0042;
        pKeycodeBrake[2 * BRAKE_B + 1]  = 0x0043;

        m_iMotorMax = 6;

        break;
    case PF_CEIL_08_A:
        plbMessage[2]->setText(QApplication::translate("CDebugBase", "Keep Break B pressed when lifting frame up and down!"));
        pKeycodePressed[0] = 0x0022;
        pKeycodePressed[1] = 0x0020;
        pKeycodePressed[2] = 0x0026;
        pKeycodePressed[3] = 0x0024;
        pKeycodePressed[4] = 0x002a;
        pKeycodePressed[5] = 0x0028;
        pKeycodePressed[6] = 0x002e;
        pKeycodePressed[7] = 0x002c;
        pKeycodePressed[8] = 0x0032;
        pKeycodePressed[9] = 0x0030;

        for(int mIdx = 0 ; mIdx < BTN_MAX ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        pKeycodeBrake[2 * BRAKE_A ]     = 0x0040;
        pKeycodeBrake[2 * BRAKE_A + 1]  = 0x0041;
        pKeycodeBrake[2 * BRAKE_B ]     = 0x0042;
        pKeycodeBrake[2 * BRAKE_B + 1]  = 0x0043;

        m_iMotorMax = 5;
        break;
    case PF_UARM_10_A:
        plbMessage[2]->setText(QApplication::translate("CDebugBase", "Keep Break B pressed when turning uarm angle!"));
        pKeycodePressed[0] = 0x0022;
        pKeycodePressed[1] = 0x0020;
        pKeycodePressed[2] = 0x0026;
        pKeycodePressed[3] = 0x0024;
        pKeycodePressed[4] = 0x002a;
        pKeycodePressed[5] = 0x0028;
        pKeycodePressed[6] = 0x002e;
        pKeycodePressed[7] = 0x002c;

        for(int mIdx = 0 ; mIdx < BTN_MAX ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        pKeycodeBrake[2 * BRAKE_A ]     = 0x0040;
        pKeycodeBrake[2 * BRAKE_A + 1]  = 0x0041;
        pKeycodeBrake[2 * BRAKE_B ]     = 0x0042;
        pKeycodeBrake[2 * BRAKE_B + 1]  = 0x0043;

        m_iMotorMax = 4;
        break;
    case PF_UARM_08_A:
        plbMessage[2]->setText(QApplication::translate("CDebugBase", "Keep Break B pressed when turning uarm angle!"));
        pKeycodePressed[0] = 0x0022;
        pKeycodePressed[1] = 0x0020;
        pKeycodePressed[2] = 0x0026;
        pKeycodePressed[3] = 0x0024;
        pKeycodePressed[4] = 0x002a;
        pKeycodePressed[5] = 0x0028;
        pKeycodePressed[6] = 0x002e;
        pKeycodePressed[7] = 0x002c;

        for(int mIdx = 0 ; mIdx < BTN_MAX ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        pKeycodeBrake[2 * BRAKE_A ]     = 0x0040;
        pKeycodeBrake[2 * BRAKE_A + 1]  = 0x0041;
        pKeycodeBrake[2 * BRAKE_B ]     = 0x0042;
        pKeycodeBrake[2 * BRAKE_B + 1]  = 0x0043;

        m_iMotorMax = 4;
        break;
    case PF_RAIL_12_A:
        plbMessage[2]->setText(QApplication::translate("CDebugBase", "Please Caution! No distance protection in this mode."));
        pKeycodePressed[0] = 0x0022;
        pKeycodePressed[1] = 0x0020;
        pKeycodePressed[2] = 0x0026;
        pKeycodePressed[3] = 0x0024;
        pKeycodePressed[4] = 0x002a;
        pKeycodePressed[5] = 0x0028;
        pKeycodePressed[6] = 0x002e;
        pKeycodePressed[7] = 0x002c;
        pKeycodePressed[8] = 0x0032;
        pKeycodePressed[9] = 0x0030;
        pKeycodePressed[10]= 0x0036;
        pKeycodePressed[11]= 0x0034;

        for(int mIdx = 0 ; mIdx < BTN_MAX ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        pKeycodeBrake[2 * BRAKE_A ]     = 0x0040;
        pKeycodeBrake[2 * BRAKE_A + 1]  = 0x0041;
        pKeycodeBrake[2 * BRAKE_B ]     = 0x0042;
        pKeycodeBrake[2 * BRAKE_B + 1]  = 0x0043;

        m_iMotorMax = 6;
        break;
    case PF_RAIL_08_A:
        plbMessage[2]->setText(QApplication::translate("CDebugBase", "Please Caution! No distance protection in this mode."));
        pKeycodePressed[0] = 0x0022;
        pKeycodePressed[1] = 0x0020;
        pKeycodePressed[2] = 0x0026;
        pKeycodePressed[3] = 0x0024;
        pKeycodePressed[4] = 0x002a;
        pKeycodePressed[5] = 0x0028;
        pKeycodePressed[6] = 0x002e;
        pKeycodePressed[7] = 0x002c;
        pKeycodePressed[8] = 0x0032;
        pKeycodePressed[9] = 0x0030;
        pKeycodePressed[10]= 0x0036;
        pKeycodePressed[11]= 0x0034;

        for(int mIdx = 0 ; mIdx < BTN_MAX ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        pKeycodeBrake[2 * BRAKE_A ]     = 0x0040;
        pKeycodeBrake[2 * BRAKE_A + 1]  = 0x0041;
        pKeycodeBrake[2 * BRAKE_B ]     = 0x0042;
        pKeycodeBrake[2 * BRAKE_B + 1]  = 0x0043;

        m_iMotorMax = 6;
        break;
    default:
        break;
    }
}

void CDebugPage1::OnDebugFresh()
{   	
    UpdateSampleData();

    unsigned long  wData;

    wData =(unsigned short)g_systemDb->g_dbMachine.StateData[5] << 16;
    wData +=(unsigned short)g_systemDb->g_dbMachine.StateData[4];

    if(m_lLimitBuf == wData)
        return;

    m_lLimitBuf = wData;

    for (int mIdx = 0; mIdx < DEBUG_LIMIT_MAX ; mIdx++)
    {
        if(wData & 0x0001)
            pLimitFrame[mIdx]->setStyleSheet("QFrame { background-color : red;}");
        else
            pLimitFrame[mIdx]->setStyleSheet("QFrame { background-color : white;}");

        wData >>= 1;
    }
} 

void CDebugPage1::UpdateSampleData()
{
    QString mStr;

    for(int mIdx = 0 ; mIdx < m_iMotorMax ; mIdx++)
    {
        mStr.setNum(g_systemDb->g_dbMachine.CurrentData[mIdx + 8]);
        pLabelAd[mIdx]->setText(mStr);
    }

}

void CDebugPage1::OnDebugPressed()
{

    for(int mIdx = 0 ;mIdx < m_iMotorMax * 2 ;mIdx++)
    {
        if(sender() ==  pBtnGroup[mIdx])
        {
            SendCmdKey(pKeycodePressed[mIdx]);
            pBtnGroup[mIdx]->setStyleSheet("background-color : cyan ; border : 1px solid black");
            m_iBtnIdx = mIdx;
            break;
        }
    }
}

void CDebugPage1::OnDebugReleased()
{

    for(int mIdx = 0 ;mIdx < m_iMotorMax * 2 ;mIdx++)
    {
        if(sender() ==  pBtnGroup[mIdx])
        {
            SendCmdKey(pKeycodeReleased[mIdx]);
            pBtnGroup[mIdx]->setStyleSheet("background-color : lightGray");
            return;
        }
    }
}

void CDebugPage1::OnDebug1Click()
{

    if(sender() == btnExit )
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
    }

    if(sender() == btNext )
    {
        this->hide();
        g_mainSetting->setSceneWidget(g_debugPage2);
    }

    if(sender() == btDebugCtrl )
    {

        if(m_bDebugEnable == false)
        {
            bufComMessage[0]=0;
            bufComMessage[1]=SYS_CMD_DEBUG;
            g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,bufComMessage,SYS_CMD_LENGTH);

            m_bDebugEnable = true;
            btDebugCtrl->setStyleSheet("background-color : cyan ; border : 2px solid green");
        }else
        {
            bufComMessage[0]=0;
            bufComMessage[1]=SYS_CMD_SETTING;
            g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,bufComMessage,SYS_CMD_LENGTH);

            m_bDebugEnable = false;
            btDebugCtrl->setStyleSheet("background-color : lightGray");
        }
    }
}

void CDebugPage1::OnBrakePressed()
{

    int mBrakePos = -1;

    for(int mIdx = 0 ; mIdx < BRAKE_MAX ; mIdx++)
    {
        if(sender() == pBtnBrake[mIdx])
        {
            mBrakePos = mIdx;
            break;
        }
    }

    if(mBrakePos == -1)
        return;

    if(!m_bBrakeState[mBrakePos])
    {

        SendCmdKey(pKeycodeBrake[ mBrakePos * 2]);
        pBtnBrake[mBrakePos]->setStyleSheet("background-color : cyan ; color : red; border : 1px solid black");
        m_bBrakeState[mBrakePos] = true;
    }else
    {
        SendCmdKey(pKeycodeBrake[ mBrakePos * 2 + 1]);
        pBtnBrake[mBrakePos]->setStyleSheet("background-color : darkGray ; color : red; border : 1px solid black");
        m_bBrakeState[mBrakePos] = false;
    }
}
