#include "debug_page2.h"

#include "resource_manager.h"

CDebugPage2::CDebugPage2(int mpf,QWidget *parent) :
    CDebugBase(parent)
{
    setObjectName("CDebugPage2");

    resize(600,600);

    textTitle->setText(QApplication::translate("CDebugBase", "Motor Debug Form B"));

    QString mStr;
    for(int mIdx = 0 ; mIdx < CHANNEL_MAX ; mIdx++)
    {
        mStr.sprintf("IN%d",2 * mIdx + 13);
        pLimitText[2 * mIdx]->setText(mStr);

        mStr.sprintf("IN%d",2 * mIdx + 14);
        pLimitText[2 * mIdx + 1]->setText(mStr);
    }

    pBtnGroup[0]->setText("G-");
    pBtnGroup[1]->setText("G+");
    pBtnGroup[2]->setText("H-");
    pBtnGroup[3]->setText("H+");
    pBtnGroup[4]->setText("I-");
    pBtnGroup[5]->setText("I+");
    pBtnGroup[6]->setText("J-");
    pBtnGroup[7]->setText("J+");
    pBtnGroup[8]->setText("K-");
    pBtnGroup[9]->setText("K+");
    pBtnGroup[10]->setText("L-");
    pBtnGroup[11]->setText("L+");

    btBack = new CButtonStable(this);
    btBack->setGeometry(QRect(420, 525, 110, 60));
    btBack->setText(QApplication::translate("CDebugBase", "BACK"));

    btTempDec = new CButtonStable(this);
    btTempDec->setGeometry(QRect(205, 420, 95, 75));
    btTempDec->setText(QApplication::translate("CDebugBase", "Dec"));

    btTempAdd = new CButtonStable(this);
    btTempAdd->setGeometry(QRect(300, 420, 95, 75));
    btTempAdd->setText(QApplication::translate("CDebugBase", "Add"));

    lbTubeTemp = new QLabel(this);
    lbTubeTemp->setGeometry(QRect(20, 420, 300, 30));
    lbTubeTemp->setText(QApplication::translate("CDebugBase", "Tube Temperature:"));
    lbTubeTemp->lower();

    lbTubeTemperature = new QLabel(this);
    lbTubeTemperature->setGeometry(QRect(40, 455, 91, 28));
    lbTubeTemperature->setStyleSheet("QLabel { background-color : yellow ; border : 1px solid black}");

    plbWarnning = new QLabel(this);
    plbWarnning->setGeometry(QRect(20, 55, 580, 40));
    plbWarnning->setStyleSheet("color : red");
    plbWarnning->lower();

    connect(btnExit,   SIGNAL(pressed()),this,SLOT(OnButtonClick()));
    connect(btBack,   SIGNAL(pressed()),this,SLOT(OnButtonClick()));
    connect(btTempAdd,SIGNAL(pressed()),this,SLOT(OnButtonClick()));
    connect(btTempDec,SIGNAL(pressed()),this,SLOT(OnButtonClick()));

    translateFontSize( this );

    debugInit(mpf);

    setVisible(false);
}


void CDebugPage2::debugInit(int mpf)
{

    switch(mpf)
    {
    case PF_RF_8_A:

        m_iMotorMax = 2;
        pKeycodePressed[0] = 0x003a;
        pKeycodePressed[1] = 0x0038;
        pKeycodePressed[2] = 0x003e;
        pKeycodePressed[3] = 0x003c;

        for(int mIdx = 0 ; mIdx < m_iMotorMax * 2 ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        break;
    case PF_CEIL_10_A:

        m_iMotorMax = 2;
        pKeycodePressed[0] = 0x003a;
        pKeycodePressed[1] = 0x0038;
        pKeycodePressed[2] = 0x003e;
        pKeycodePressed[3] = 0x003c;

        for(int mIdx = 0 ; mIdx < m_iMotorMax * 2 ; mIdx++)
        {
            pKeycodeReleased[mIdx] = pKeycodePressed[mIdx] + 1;
        }

        break;
    case PF_CEIL_10_B:

        break;
    case PF_CEIL_08_A:

        break;
    case PF_UARM_10_A:

        break;
    case PF_UARM_08_A:

        break;
    case PF_RAIL_12_A:

        break;
    case PF_RAIL_08_A:
        plbWarnning->setText(QApplication::translate("CDebugBase", "Please Caution! No distance protection in this mode."));
        break;
    default:

        break;
    }
}
void CDebugPage2::OnDebugFresh()
{

    UpdateSampleData();

    unsigned long  wData;

    wData =(unsigned short)g_systemDb->g_dbMachine.StateData[5];
    wData <<= 16;
    wData +=(unsigned short)g_systemDb->g_dbMachine.StateData[4];

    if(m_lLimitBuf == wData)
        return;

    m_lLimitBuf = wData;

    wData >>= 12;

    for (int mIdx = 0; mIdx < DEBUG_BTN_MAX ; mIdx++)
    {
        if(wData & 0x0001)
            pLimitFrame[mIdx]->setStyleSheet("QFrame { background-color : red;}");
        else
            pLimitFrame[mIdx]->setStyleSheet("QFrame { background-color : white;}");

        wData >>= 1;
    }

}

void CDebugPage2::UpdateSampleData()
{
    QString mStr;
    for(int mIdx = 0 ; mIdx < m_iMotorMax; mIdx++)
    {
        mStr.setNum(g_systemDb->g_dbMachine.CurrentData[14 + mIdx]);
        pLabelAd[mIdx]->setText(mStr);
    }

    mStr.setNum(g_systemDb->g_dbMachine.StateData[3] + g_dbsys.utility.mTemperatureAdj);

    lbTubeTemperature->setText(mStr);

}

void CDebugPage2::OnDebugPressed()
{

    for(int mIdx = 0 ;mIdx < m_iMotorMax * 2 ;mIdx++)
    {
        if(sender() ==  pBtnGroup[mIdx])
        {
            SendCmdKey(pKeycodePressed[mIdx]);
            pBtnGroup[mIdx]->setStyleSheet("background-color : cyan; border : 1px solid black");
            break;
        }
    }
}

void CDebugPage2::OnDebugReleased()
{
    for(int mIdx = 0 ;mIdx < m_iMotorMax * 2;mIdx++)
    {
        if(sender() ==  pBtnGroup[mIdx])
        {
            SendCmdKey(pKeycodeReleased[mIdx]);
            pBtnGroup[mIdx]->setStyleSheet("background-color : lightGray");
            break;
        }
    }
}

void CDebugPage2::OnButtonClick()
{

    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        return;
    }

    if(sender() == btBack )
    {

        this->hide();
        g_mainSetting->setSceneWidget(g_debugPage1);
        return;
    }

    if(sender() == btTempAdd )
    {

        g_dbsys.utility.mTemperatureAdj++;

        g_systemDb->SaveSystemCfg("utility/mTemperatureAdj",g_dbsys.utility.mTemperatureAdj);
        return;
    }

    if(sender() == btTempDec )
    {
        g_dbsys.utility.mTemperatureAdj--;
        g_systemDb->SaveSystemCfg("utility/mTemperatureAdj",g_dbsys.utility.mTemperatureAdj);
        return;
    }
}
