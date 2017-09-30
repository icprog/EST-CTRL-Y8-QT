
#include "system_smart.h"
#include "sys_database.h"
#include "resource_manager.h"

#define SYSTEM_SMART_LINE   ( 2 )       /*行*/
#define SYSTEM_SMART_COL    ( 4 )       /*列*/

CSystemSmart::CSystemSmart(  int mPlatform,QWidget* parent ):
    CSystemBase(parent)
{     

    setObjectName("CSystemSmart");

    resize(600,600);

    m_iFocusCurrent = 0;
    m_iMotorMax = 0;
    m_iBtnSaveIdx = -1;

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

    for(int mIdx = 0 ; mIdx < FAST_POSI_MAX ; mIdx++)
    {
        pLabelChannel[mIdx] = new QLabel(this);
        pLabelChannel[mIdx]->setGeometry(mIdx * 75 + 2 ,95,70,40);
        pLabelChannel[mIdx]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        pLabelAd[mIdx]      = new QLabel(this);
        pLabelAd[mIdx]->setGeometry(mIdx * 75 + 2 ,135,70,40);
        pLabelAd[mIdx]->setStyleSheet("background-color : yellow ;  color : blue ; border : 1px solid black");
        pLabelAd[mIdx]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        pLabelData[mIdx]    = new QLabel(this);
        pLabelData[mIdx]->setGeometry(mIdx * 75  + 2,185,70,40);
        pLabelData[mIdx]->setStyleSheet("background-color : yellow ;  color : green ; border : 1px solid black");
        pLabelData[mIdx]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    int mLine,mCol;

    for(int mIdx = 0 ; mIdx < FAST_POSI_MAX; mIdx++)
    {
        mLine = mIdx / SYSTEM_SMART_COL;
        mCol = mIdx - mLine * SYSTEM_SMART_COL;

        pBtnGroup[mIdx]     = new CButtonStable(this);
        pBtnGroup[mIdx]->setGeometry(QRect(mCol * 146 + 16, 250 + mLine * 85,  130, 75));
        pBtnGroup[mIdx]->setText(QApplication::translate("CSystemSmart", "SAVE"));
        pBtnGroup[mIdx]->setFocusPolicy(Qt::NoFocus);
        //pBtnGroup[mIdx]->setStyleSheet("background-color: white;border: 2px solid black;");
    }

    pFrameGroup0  = new QFrame(this);
    pFrameGroup0->setGeometry(QRect(20, 90 ,  560, 10));
    pFrameGroup0->setFrameShape(QFrame::HLine);
    pFrameGroup0->setFrameShadow(QFrame::Sunken);
    pFrameGroup0->raise();

    pFrameGroup1  = new QFrame(this);
    pFrameGroup1->setGeometry(QRect(20, 235 ,  560, 10));
    pFrameGroup1->setFrameShape(QFrame::HLine);
    pFrameGroup1->setFrameShadow(QFrame::Sunken);
    pFrameGroup1->raise();


    InitCfg(mPlatform);

    timerRefesh = new QTimer();
    connect(timerRefesh,SIGNAL(timeout()),this,SLOT(OnTime()));

    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnFastPressed()));

    translateFontSize( this );

    setVisible(false);

    mSmartNdt = new CSystemSmartNdt();
}


void CSystemSmart::InitCfg(int mPf)
{
    switch(mPf)
    {
    case PF_NDT_8_A:
    case PF_RF_8_A:
        m_iFastPosiCode[0] = 0x0050;
        m_iFastPosiCode[1] = 0x0051;
        m_iFastPosiCode[2] = 0x0052;
        m_iFastPosiCode[3] = 0x0053;
        m_iFastPosiCode[4] = 0x0054;
        m_iFastPosiCode[5] = 0x0055;
        m_iFastPosiCode[6] = 0x0056;
        m_iFastPosiCode[7] = 0x0057;

        pLabelChannel[0]->setText("FID");
        pLabelChannel[1]->setText("DTP");
        pLabelChannel[2]->setText("SID");
        pLabelChannel[3]->setText("ANG");
        pLabelChannel[4]->setText("RPL");
        pLabelChannel[5]->setText("PYP");
        pLabelChannel[6]->setText("SGH");
        pLabelChannel[7]->setText("SGV");

        break;
    case PF_NDT_10_A:
        pBtnNdtShow = new CButtonStable(this);
        pBtnNdtShow->setGeometry(50,525,150,60);
        pBtnNdtShow->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));"));
        pBtnNdtShow->show();
        connect(pBtnNdtShow,SIGNAL(pressed()),this,SLOT(OnNdtSmartShow()) );
        pBtnNdtShow->setText(QApplication::translate("CSystemSmart", "NDT Smart Cali." ));
        break;
    case PF_CEIL_10_A:
        m_iFastPosiCode[0] = 0x0050;
        m_iFastPosiCode[1] = 0x0051;
        m_iFastPosiCode[2] = 0x0052;
        m_iFastPosiCode[3] = 0x0053;
        m_iFastPosiCode[4] = 0x0054;
        m_iFastPosiCode[5] = 0x0055;
        m_iFastPosiCode[6] = 0x0056;
        m_iFastPosiCode[7] = 0x0057;

        pLabelChannel[0]->setText("FID");
        pLabelChannel[1]->setText("SID");
        pLabelChannel[2]->setText("ANG");
        pLabelChannel[3]->setText("DTH");
        pLabelChannel[4]->setText("DTA");
        pLabelChannel[5]->setText("CEP");
        pLabelChannel[6]->setText("BEH");
        pLabelChannel[7]->setText("DTP");

        for( int mIdx = 0 ;mIdx < FAST_POSI_MAX ; mIdx++)
        {
            connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnFastPressed()));
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + mIdx + 1)  + "border:2px solid black");
        }
        pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + 0 + 1)  + "border:3px solid blue" );
        m_iMotorMax = FAST_POSI_MAX;
        break;
    case PF_CEIL_10_B:
        m_iFastPosiCode[0] = 0x0050;
        m_iFastPosiCode[1] = 0x0051;
        m_iFastPosiCode[2] = 0x0052;
        m_iFastPosiCode[3] = 0x0053;
        m_iFastPosiCode[4] = 0x0054;
        m_iFastPosiCode[5] = 0x0055;

        pLabelChannel[0]->setText("FID");
        pLabelChannel[1]->setText("SID");
        pLabelChannel[2]->setText("ANG");
        pLabelChannel[3]->setText("DTH");
        pLabelChannel[4]->setText("DTA");
        pLabelChannel[5]->setText("CEP");

        for( int mIdx = 0 ;mIdx < FAST_POSI_MAX ; mIdx++)
        {
            connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnFastPressed()));
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + mIdx + 1)  + "border:2px solid black" );
        }

        pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + 0 + 1)  + "border:3px solid blue" );
        m_iMotorMax = FAST_POSI_MAX;
        pLabelAd[6]->setVisible(false);
        pLabelAd[7]->setVisible(false);
        pBtnGroup[6]->setVisible(false);
        pBtnGroup[7]->setVisible(false);
        pLabelData[6]->setVisible(false);
        pLabelData[7]->setVisible(false);

        break;
    case PF_CEIL_08_A:
        m_iFastPosiCode[0] = 0x0058;
        m_iFastPosiCode[1] = 0x0051;
        m_iFastPosiCode[2] = 0x0053;
        m_iFastPosiCode[3] = 0x0057;
        m_iFastPosiCode[4] = 0x0059;
        m_iFastPosiCode[5] = 0x005b;
        m_iFastPosiCode[6] = 0x005d;

        pLabelChannel[0]->setText("FID");
        pLabelChannel[1]->setText("SID");
        pLabelChannel[2]->setText("ANG");
        pLabelChannel[3]->setText("DTH");
        pLabelChannel[4]->setText("DTA");
        pLabelChannel[5]->setText("CEP");

        for( int mIdx = 0 ;mIdx < FAST_POSI_MAX ; mIdx++)
        {
            connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnFastPressed()));
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + mIdx + 1)  + "border:2px solid black" );
        }

        pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + 0 + 1)  + "border:3px solid blue" );
        m_iMotorMax = FAST_POSI_MAX;
        pBtnGroup[6]->setVisible(false);
        pBtnGroup[7]->setVisible(false);
        pLabelAd[5]->setVisible(false);
        pLabelAd[6]->setVisible(false);
        pLabelAd[7]->setVisible(false);
        pLabelData[5]->setVisible(false);
        pLabelData[6]->setVisible(false);
        pLabelData[7]->setVisible(false);
        pLabelChannel[5]->setVisible(false);
        pLabelChannel[6]->setVisible(false);
        pLabelChannel[7]->setVisible(false);

        break;
    case PF_UARM_10_A:
        m_iFastPosiCode[0] = 0x0050;
        m_iFastPosiCode[1] = 0x0051;
        connect(pBtnGroup[0],SIGNAL(pressed()),this,SLOT(OnFastPressed()));
        pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_STR_SMART_21)  + "border:2px solid black" );
        connect(pBtnGroup[1],SIGNAL(pressed()),this,SLOT(OnFastPressed()));
        pBtnGroup[1]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_STR_SMART_25)  + "border:2px solid black" );

        for(int mIdx = 2 ; mIdx < FAST_POSI_MAX ; mIdx++)
        {
            pBtnGroup[mIdx]->setVisible(false);
            pLabelData[mIdx]->setVisible(false);
        }

        break;
    case PF_UARM_08_A:
        m_iFastPosiCode[0] = 0x0050;
        m_iFastPosiCode[1] = 0x0051;
        m_iFastPosiCode[2] = 0x0052;
        m_iFastPosiCode[3] = 0x0053;
        m_iFastPosiCode[4] = 0x0054;
        m_iFastPosiCode[5] = 0x0055;
        m_iFastPosiCode[6] = 0x0056;

        pLabelChannel[0]->setText("FID");
        pLabelChannel[1]->setText("SID");
        pLabelChannel[2]->setText("ANG");
        pLabelChannel[3]->setText("DTA");

        for( int mIdx = 0 ;mIdx < FAST_POSI_MAX ; mIdx++)
        {
            connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnFastPressed()));
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + mIdx + 1)  + "border:2px solid black" );
        }
        pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + 0 + 1)  + "border:3px solid blue" );
        m_iMotorMax = FAST_POSI_MAX;
        pBtnGroup[6]->setVisible(false);
        pBtnGroup[7]->setVisible(false);
        pLabelAd[4]->setVisible(false);
        pLabelAd[5]->setVisible(false);
        pLabelAd[6]->setVisible(false);
        pLabelAd[7]->setVisible(false);
        pLabelData[4]->setVisible(false);
        pLabelData[5]->setVisible(false);
        pLabelData[6]->setVisible(false);
        pLabelData[7]->setVisible(false);
        pLabelChannel[4]->setVisible(false);
        pLabelChannel[5]->setVisible(false);
        pLabelChannel[6]->setVisible(false);
        pLabelChannel[7]->setVisible(false);
        break;
    case PF_RAIL_12_A:
        m_iFastPosiCode[0] = 0x0050;
        m_iFastPosiCode[1] = 0x0051;
        m_iFastPosiCode[2] = 0x0052;
        m_iFastPosiCode[3] = 0x0053;
        m_iFastPosiCode[4] = 0x0054;
        m_iFastPosiCode[5] = 0x0055;
        m_iFastPosiCode[6] = 0x0056;
        m_iFastPosiCode[7] = 0x0057;

        pLabelChannel[0]->setText("FID");
        pLabelChannel[1]->setText("SID");
        pLabelChannel[2]->setText("ANG");
        pLabelChannel[3]->setText("DTH");
        pLabelChannel[4]->setText("BEH");
        pLabelChannel[5]->setText("DTP");

        for( int mIdx = 0 ;mIdx < FAST_POSI_MAX ; mIdx++)
        {
            connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnFastPressed()));
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + mIdx + 1)  + "border:2px solid black" );
        }
        pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + 0 + 1)  + "border:3px solid blue" );
        m_iMotorMax = FAST_POSI_MAX;
        pBtnGroup[7]->setVisible(false);
        pLabelAd[6]->setVisible(false);
        pLabelAd[7]->setVisible(false);
        pLabelData[6]->setVisible(false);
        pLabelData[7]->setVisible(false);
        pLabelChannel[6]->setVisible(false);
        pLabelChannel[7]->setVisible(false);
        break;
    case PF_RAIL_08_A:
        m_iFastPosiCode[0] = 0x0050;
        m_iFastPosiCode[1] = 0x0051;
        m_iFastPosiCode[2] = 0x0052;
        m_iFastPosiCode[3] = 0x0053;
        m_iFastPosiCode[4] = 0x0054;
        m_iFastPosiCode[5] = 0x0055;
        m_iFastPosiCode[6] = 0x0056;
        m_iFastPosiCode[7] = 0x0057;

        pLabelChannel[0]->setText("FID");
        pLabelChannel[1]->setText("SID");
        pLabelChannel[2]->setText("ANG");
        pLabelChannel[3]->setText("DTH");
        pLabelChannel[4]->setText("BEH");
        pLabelChannel[5]->setText("DTP");

        for( int mIdx = 0 ;mIdx < FAST_POSI_MAX ; mIdx++)
        {
            connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnFastPressed()));
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + mIdx + 1)  + "border:2px solid black" );
        }
        pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + 0 + 1)  + "border:3px solid blue" );
        m_iMotorMax = FAST_POSI_MAX;
        pBtnGroup[7]->setVisible(false);
        pLabelAd[6]->setVisible(false);
        pLabelAd[7]->setVisible(false);
        pLabelData[6]->setVisible(false);
        pLabelData[7]->setVisible(false);
        pLabelChannel[6]->setVisible(false);
        pLabelChannel[7]->setVisible(false);
        break;
    default:

        break;
    }
}
void CSystemSmart::showEvent(QShowEvent *event)
{

    g_systemDb->g_bDataSaved = false;
    labelMsg->setVisible(false);

    timerRefesh->start(300);

    grabKeyboard();

    CSystemBase::showEvent(event);
}

void CSystemSmart::hideEvent(QHideEvent *event)
{

    timerRefesh->stop();

    releaseKeyboard();

    CSystemBase::hideEvent(event);
}


void CSystemSmart::keyPressEvent( QKeyEvent * event )
{
    event->accept();

    switch(event->key())
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        OnFastPressedSave();
        break;
    case Qt::Key_Tab:
        pBtnGroup[m_iFocusCurrent]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + m_iFocusCurrent + 1)  + "border:2px solid black" );

        if(++m_iFocusCurrent >= m_iMotorMax)
            m_iFocusCurrent = 0;

        pBtnGroup[m_iFocusCurrent]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + m_iFocusCurrent + 1)  + "border:3px solid blue" );

        break;
    case Qt::Key_Escape:
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        this->hide();
        return;
    default:
        break;
    }
}

void CSystemSmart::OnTime()
{   

    QString mStr;

    for(int mIdx = 0 ; mIdx < FAST_POSI_MAX ; mIdx++)
    {
        unsigned short mSampleData = g_systemDb->g_dbMachine.CurrentData[mIdx + 8];
        mStr.setNum(mSampleData);
        pLabelAd[mIdx]->setText(mStr);

        if(mSampleData > 15000 || mSampleData < 1000)
            pLabelAd[mIdx]->setStyleSheet("background-color : red ;  color : blue ; border : 2px dotted yellow");
        else
            pLabelAd[mIdx]->setStyleSheet("background-color : yellow ;  color : blue ; border : 1px solid black");

        mStr.setNum(g_systemDb->g_dbMachine.CurrentData[mIdx]);
        pLabelData[mIdx]->setText(mStr);
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

void CSystemSmart::OnFastPressedSave()
{

    unsigned short  buf[10];
    buf[0] =0;
    buf[2] =g_systemDb->g_dbMachine.CurrentData[8];
    buf[3] =g_systemDb->g_dbMachine.CurrentData[9];
    buf[4] =g_systemDb->g_dbMachine.CurrentData[10];
    buf[5] =g_systemDb->g_dbMachine.CurrentData[11];
    buf[6] =g_systemDb->g_dbMachine.CurrentData[12];
    buf[7] =g_systemDb->g_dbMachine.CurrentData[13];
    buf[8] =g_systemDb->g_dbMachine.CurrentData[14];
    buf[9] =g_systemDb->g_dbMachine.CurrentData[15];

    buf[1] = m_iFastPosiCode[m_iFocusCurrent];
    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);
    g_systemDb->FastDataSave(m_iFocusCurrent + 1,&(buf[2]));
    m_iBtnSaveIdx = m_iFocusCurrent;

}
void CSystemSmart::OnFastPressed()
{

    if(sender() == btnExit )
    {
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        this->hide();
        return;
    }

    unsigned short  buf[10];
    buf[0] =0;
    buf[2] =g_systemDb->g_dbMachine.CurrentData[8];
    buf[3] =g_systemDb->g_dbMachine.CurrentData[9];
    buf[4] =g_systemDb->g_dbMachine.CurrentData[10];
    buf[5] =g_systemDb->g_dbMachine.CurrentData[11];
    buf[6] =g_systemDb->g_dbMachine.CurrentData[12];
    buf[7] =g_systemDb->g_dbMachine.CurrentData[13];
    buf[8] =g_systemDb->g_dbMachine.CurrentData[14];
    buf[9] =g_systemDb->g_dbMachine.CurrentData[15];

    int mBtnPos = -1;
    for(int mIdx = 0 ; mIdx < FAST_POSI_MAX ; mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
        {
            mBtnPos = mIdx;

            buf[1] = m_iFastPosiCode[mBtnPos];
            g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);
            g_systemDb->FastDataSave(mBtnPos + 1,&(buf[2]));
            m_iBtnSaveIdx = mBtnPos;

            pBtnGroup[m_iFocusCurrent]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + m_iFocusCurrent + 1)  + "border:2px solid black" );
            m_iFocusCurrent =m_iBtnSaveIdx;
            pBtnGroup[m_iFocusCurrent]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE2 + m_iFocusCurrent + 1)  + "border:3px solid blue" );
            break;
        }
    }
}

void CSystemSmart::OnNdtSmartShow()
{
    if(sender() == pBtnNdtShow)
    {
        this->hide();
        g_mainSetting->setSceneWidget(mSmartNdt);
    }
}
