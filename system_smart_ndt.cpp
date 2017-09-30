
#include "system_smart_ndt.h"
#include "sys_database.h"
#include "resource_manager.h"

#define NDT_POSI_MAX           ( 11 )

CSystemSmartNdt::CSystemSmartNdt(  QWidget* parent ):
    CSystemBase(parent)
{     

    setObjectName("CSystemSmartNdt");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemSmart", "One Key Position Set"));

    labelInfo = new QLabel(this);
    labelInfo->setGeometry(QRect(20, 50, 560, 50));
    labelInfo->setText(QApplication::translate("CSystemSmart", "Run all the motors to fast position, then click the save button."));
    labelInfo->setStyleSheet("color : blue");
    labelInfo->lower();

    labelMsg = new QLabel(this);
    labelMsg->setGeometry(QRect(20, 450, 565, 50));
    labelMsg->setStyleSheet("color : red");
    labelMsg->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel * pLbTemp;
    for(int mIdx = 0 ; mIdx < NDT_POSI_MAX ; mIdx++)
    {
        pLbTemp = new QLabel(this);
        pLbTemp->setGeometry(mIdx * 54 + 3 ,95,53,40);
        pLbTemp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        arrLbChannel.push_back(pLbTemp);

        //        pLbTemp     = new QLabel(this);
        //        pLbTemp->setGeometry(mIdx * 54 + 3 ,135,53,40);
        //        pLbTemp->setStyleSheet("background-color : yellow ;  color : blue ; border : 1px solid black");
        //        pLbTemp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //        arrLbAd.push_back(pLbTemp);

        pLbTemp   = new QLabel(this);
        //pLbTemp->setGeometry(mIdx * 54  + 3,185,53,40);
        pLbTemp->setGeometry(mIdx * 54  + 3,135,53,40);
        pLbTemp->setStyleSheet("background-color : yellow ;  color : green ; border : 1px solid black");
        pLbTemp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        arrLbData.push_back(pLbTemp);
    }

    arrLbChannel.at(NDT_KEY_IDX_FID)->setText("FID");
    arrLbChannel.at(NDT_KEY_IDX_SID)->setText("SID");
    arrLbChannel.at(NDT_KEY_IDX_ANG)->setText("ANG");
    arrLbChannel.at(NDT_KEY_IDX_CEP)->setText("CEP");
    arrLbChannel.at(NDT_KEY_IDX_UID)->setText("UID");
    arrLbChannel.at(NDT_KEY_IDX_DTA)->setText("DTA");
    arrLbChannel.at(NDT_KEY_IDX_ROL)->setText("ROL");
    arrLbChannel.at(NDT_KEY_IDX_SRL)->setText("SRL");
    arrLbChannel.at(NDT_KEY_IDX_RMV)->setText("RMV");
    arrLbChannel.at(NDT_KEY_IDX_LMV)->setText("LMV");
    arrLbChannel.at(NDT_KEY_IDX_HEI)->setText("HEI");

    CButtonStable * pBtnTemp;

    pBtnTemp     = new CButtonStable(this);
    pBtnTemp->setGeometry(QRect( 15, 200,  180, 75));
    pBtnTemp->setText(QApplication::translate("CSystemSmart", "Long Table Start"));
    connect(pBtnTemp,SIGNAL(pressed()),this,SLOT(OnNdtSavePressed()));
    arrBtnGroup.push_back(pBtnTemp);

    pBtnTemp     = new CButtonStable(this);
    pBtnTemp->setGeometry(QRect(210, 200,  180, 75));
    pBtnTemp->setText(QApplication::translate("CSystemSmart", "LRound Table Flat"));
    connect(pBtnTemp,SIGNAL(pressed()),this,SLOT(OnNdtSavePressed()));
    arrBtnGroup.push_back(pBtnTemp);

    pBtnTemp     = new CButtonStable(this);
    pBtnTemp->setGeometry(QRect(405, 200,  180, 75));
    pBtnTemp->setText(QApplication::translate("CSystemSmart", "SRound Table Start"));
    connect(pBtnTemp,SIGNAL(pressed()),this,SLOT(OnNdtSavePressed()));
    arrBtnGroup.push_back(pBtnTemp);

    pBtnTemp     = new CButtonStable(this);
    pBtnTemp->setGeometry(QRect(15, 300,  180, 75));
    pBtnTemp->setText(QApplication::translate("CSystemSmart", "LRound Table Angle"));
    connect(pBtnTemp,SIGNAL(pressed()),this,SLOT(OnNdtSavePressed()));
    arrBtnGroup.push_back(pBtnTemp);

    pBtnTemp     = new CButtonStable(this);
    pBtnTemp->setGeometry(QRect(210, 300,  180, 75));
    pBtnTemp->setText(QApplication::translate("CSystemSmart", "Arm Position Start"));
    connect(pBtnTemp,SIGNAL(pressed()),this,SLOT(OnNdtSavePressed()));
    arrBtnGroup.push_back(pBtnTemp);

    pFrameGroup0  = new QFrame(this);
    pFrameGroup0->setGeometry(QRect(20, 90 ,  560, 10));
    pFrameGroup0->setFrameShape(QFrame::HLine);
    pFrameGroup0->setFrameShadow(QFrame::Sunken);
    pFrameGroup0->raise();

    pFrameGroup1  = new QFrame(this);
    pFrameGroup1->setGeometry(QRect(20, 185 ,  560, 10));
    pFrameGroup1->setFrameShape(QFrame::HLine);
    pFrameGroup1->setFrameShadow(QFrame::Sunken);
    pFrameGroup1->raise();

    timerRefesh = new QTimer();
    connect(timerRefesh,SIGNAL(timeout()),this,SLOT(OnTime()));

    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnNdtExitPressed()));

    m_iBtnSaveIdx = -1;

    translateFontSize( this );

    setVisible(false);
}

void CSystemSmartNdt::showEvent(QShowEvent *event)
{

    g_systemDb->g_bDataSaved = false;
    labelMsg->setVisible(false);

    timerRefesh->start(300);

    CSystemBase::showEvent(event);
}

void CSystemSmartNdt::hideEvent(QHideEvent *event)
{

    timerRefesh->stop();

    CSystemBase::hideEvent(event);
}

void CSystemSmartNdt::OnTime()
{   

    QString mStr;

    for(int mIdx = 0 ; mIdx < NDT_POSI_MAX ; mIdx++)
    {
        unsigned short mSampleData = g_systemDb->g_iArrNdtState[mIdx];
        mStr.setNum(mSampleData);
        arrLbData.at(mIdx)->setText(mStr);
    }

    if(m_iBtnSaveIdx == -1 )
        return;

    if( g_systemDb->g_bDataSaved)
    {
        mStr.sprintf("Position %d save success.",m_iBtnSaveIdx + 1);
        labelMsg->setText(QApplication::translate("CSystemSmart", mStr.toLocal8Bit().data()));
        labelMsg->show();
        g_systemDb->g_bDataSaved=false;

        m_iBtnSaveIdx = -1;
    }
} 
void CSystemSmartNdt::OnNdtExitPressed()
{
    if(sender() == btnExit )
    {
        g_mainSetting->setSceneWidget( RsMgr->g_systemSmart);
        this->hide();
        return;
    }
}

void CSystemSmartNdt::OnNdtSavePressed()
{            
    //index pos
    int mBtnPos = -1;

    //get data from task com
    unsigned short  mBuf[SYS_NDT_STATE_PAR_LEN + 16];
    for(int mIdx = 0 ; mIdx < SYS_NDT_STATE_PAR_LEN ; mIdx++)
        mBuf[mIdx] =g_systemDb->g_iArrNdtState[mIdx];

    //check button index
    for(int mIdx = 0 ; mIdx < arrBtnGroup.size() ; mIdx++)
    {
        if(sender() == arrBtnGroup.at(mIdx))
            mBtnPos = mIdx;
    }

    if(mBtnPos == -1)
        return;

    int mRes = g_systemDb->NdtSmartDataSave(mBtnPos,mBuf);

    if(mRes == true)
        g_systemDb->g_bDataSaved = true;

    m_iBtnSaveIdx = mBtnPos;

}

