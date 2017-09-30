#include "system_platform.h"
#include "resource_manager.h"
#include <qmath.h>

#define BTN_COLUMN  ( 4 )
#define BTN_SPACE   ( 10 )
#define BTN_WIDTH   ( 150 )
#define BTN_HEIGHT  ( 120 )
#define BTN_LEFT    ( 0 )

CSystemPlatform::CSystemPlatform(QWidget *parent) :
    CSystemBase(parent)
{

    setObjectName("CSystemPlatform");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemPlatform", "System Platform Change"));

    lbMessage = new QLabel(this);
    lbMessage->setGeometry(QRect(0, 460, 600, 40));
    lbMessage->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
    lbMessage->setAlignment(Qt::AlignCenter);

    int btnIdx = 0;
    bool initFinished = false;
    for(int ctrRows = 0 ; ctrRows <= qFloor(PLATFORM_MAX / BTN_COLUMN) ; ctrRows++)
    {
        if(initFinished)
            break;

        for(int ctrColumn = 0 ; ctrColumn < BTN_COLUMN ;ctrColumn++)
        {
            pBtnGroup[btnIdx] = new CButtonStable(this);
            pBtnGroup[btnIdx]->setGeometry(QRect(BTN_LEFT + ctrColumn * BTN_WIDTH, 60 + ctrRows * (BTN_HEIGHT + BTN_SPACE), BTN_WIDTH, BTN_HEIGHT));
            pBtnGroup[btnIdx]->setText(QApplication::translate("CSystemPlatform", "Set"));
            connect(pBtnGroup[btnIdx],SIGNAL(pressed()),this,SLOT(OnPlatformPressed()));
            pBtnGroup[btnIdx]->setEnabled(true);
            pBtnGroup[btnIdx]->setFocusPolicy(Qt::NoFocus);
            pBtnGroup[btnIdx]->setStyleSheet( "background-color:lightGray ; border : 2px solid black;");

            btnIdx++;

            if(btnIdx == PLATFORM_MAX)
            {
                initFinished = true;
                break;
            }
        }
    }

    pBtnGroup[0]->setText(QApplication::translate("CSystemPlatform", "Ceilling\n10\" Screen\nLift Table"));
    pBtnGroup[1]->setText(QApplication::translate("CSystemPlatform", "Ceilling\n8\" Screen\nMobile table"));
    pBtnGroup[2]->setText(QApplication::translate("CSystemPlatform", "U-Arm\n10\" Screen\nMobile table"));
    pBtnGroup[3]->setText(QApplication::translate("CSystemPlatform", "U-Arm\n8\" Screen\nMobile table"));
    pBtnGroup[4]->setText(QApplication::translate("CSystemPlatform", "Rail\n12\" Screen\nLift Table"));
    pBtnGroup[5]->setText(QApplication::translate("CSystemPlatform", "Rail\n8\" Screen\nLift Table"));
    pBtnGroup[6]->setText(QApplication::translate("CSystemPlatform", "Ceilling\n10\" Screen\nMobile table"));
    pBtnGroup[7]->setText(QApplication::translate("CSystemPlatform", "NDT \n10'"));
    pBtnGroup[8]->setText(QApplication::translate("CSystemPlatform", "NDT \n8'"));
    pBtnGroup[9]->setText(QApplication::translate("CSystemPlatform", "RF \n8'"));

    btReboot = new CButtonStable(this);
    btReboot->setGeometry(QRect(30, 525, 100, 60));
    btReboot->setVisible(false);
    btReboot->setStyleSheet("color : red  ; border : 1px solid black");
    btReboot->setText(QApplication::translate("CSystemPlatform", "Reboot"));

    lbMessage->setText("");

    connect(btnExit,    SIGNAL(pressed()),this,SLOT(OnBtnExit()));
    connect(btReboot,   SIGNAL(pressed()),this,SLOT(OnBtnReboot()));

    translateFontSize(this);

    msgBox = new CDialogConFirm(this);
    msgBox->raise();
}

void CSystemPlatform::showEvent(QShowEvent *event)
{

    m_iFocusCurrent = g_dbsys.utility.mPlatform;

    if(m_iFocusCurrent >= 0 && m_iFocusCurrent < PLATFORM_MAX)
        pBtnGroup[g_dbsys.utility.mPlatform]->setStyleSheet( "background-color:cyan ; border : 3px solid green;");

    lbMessage->setText("");

    grabKeyboard();

    CSystemBase::showEvent(event);

}
void CSystemPlatform::hideEvent(QHideEvent *event)
{
    releaseKeyboard();

    CSystemBase::hideEvent(event);
}

void CSystemPlatform::keyPressEvent( QKeyEvent * event )
{
    int mKey = event->key();
    switch (mKey) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        BtnPressed(m_iFocusCurrent);
        break;

    case Qt::Key_Close:
        break;
    case Qt::Key_Escape:
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        break;
    case Qt::Key_Tab:
        PlatformIndex();
        break;
    default:
        break;
    }
}
//mpf = 1,2,4,8,16,32
bool CSystemPlatform::BootBurn(int mpf)
{

    QString mStrFilePath;
    if(mpf == PF_CEIL_08_A || mpf == PF_UARM_08_A || mpf == PF_RAIL_08_A)
    {
        if(g_dbsys.utility.mPlatform == PF_CEIL_08_A || g_dbsys.utility.mPlatform == PF_UARM_08_A ||g_dbsys.utility.mPlatform == PF_RAIL_08_A)
            return true;

        mStrFilePath = "/sdcard/kernel6410/hmx5800";
    }

    if(mpf == PF_CEIL_10_A || mpf == PF_UARM_10_A || mpf == PF_CEIL_10_B || mpf == PF_RAIL_12_A)
    {
        if(g_dbsys.utility.mPlatform == PF_CEIL_10_A || g_dbsys.utility.mPlatform == PF_UARM_10_A ||g_dbsys.utility.mPlatform == PF_RAIL_12_A)
            return true;

        mStrFilePath = "/sdcard/kernel6410/hmx2010";
    }


    if (! QFile::exists(mStrFilePath))
    {
        lbMessage->setText(QApplication::translate("CSystemPlatform", "No Boot Kernel File In System!"));
        return false;
    }

    lbMessage->setText(QApplication::translate("CSystemPlatform", "Refresh Boot Kernel Start..."));
    lbMessage->repaint();

    QApplication::processEvents();

    int mRes = MySystem(mStrFilePath.toLatin1().data());

    if(0 == mRes)
        return true;
    else
        return false;

}

void CSystemPlatform::OnPlatformConfirm(QAbstractButton * btnRes)
{

    if(mBtnYes != btnRes)
        return;

    pBtnGroup[m_iFocusCurrent]->setStyleSheet( "background-color:lightGray ; border : 2px solid black;");

    //PlatformCheck(g_dbsys.utility.mPlatform,false);
    //m_iFocusCurrent = 1 << m_iPlatformTarget;                      //switch idx to platform
    //m_iFocusCurrent = m_iPlatformTarget;                      //switch idx to platform

    if(!BootBurn(m_iFocusCurrent))
    {
        lbMessage->setText(QApplication::translate("CSystemPlatform", "Burn Boot Section Failed!"));
        lbMessage->repaint();

        QApplication::processEvents();
    }

    //m_iPlatformTarget = g_dbsys.utility.mPlatform;                    //backup
    g_dbsys.utility.mPlatform = m_iFocusCurrent;

    g_systemDb->SaveSystemCfg("utility/mPlatform",g_dbsys.utility.mPlatform);

    btReboot->setVisible(true);
    lbMessage->setText(QApplication::translate("CSystemPlatform", "Platform change successfully.Take effect after reboot."));

    pBtnGroup[m_iFocusCurrent]->setStyleSheet( "background-color:cyan ; border : 3px solid green;");

    //PlatformCheck(m_iFocusCurrent,true);

    for(int mIdx = 0 ; mIdx < PLATFORM_MAX; mIdx++)
        pBtnGroup[mIdx]->setEnabled(false);

    //
    pBtnGroup[PF_NDT_10_A]->setVisible(false);

    btnExit->setEnabled(false);
}

void CSystemPlatform::BtnPressed(int iFocus)
{

    //去除掉目前不支持的系统平台 20150901 jsy
    if(iFocus == PF_UARM_10_A || iFocus == PF_NDT_10_A)
        return;

    if(iFocus == PF_NDT_8_A ||   iFocus == PF_RF_8_A)
        return;

    if(iFocus == -1 || iFocus == g_dbsys.utility.mPlatform)
    {
        lbMessage->setText(QApplication::translate("CSystemPlatform", "Invalid Platform Selected!"));
        return;
    }

    QString mStrTitle  = QApplication::translate("CSystemPlatform", "Critical Warning!");
    QString mStrText  = QApplication::translate("CSystemPlatform", "This Function is for Engineer use only!\nEnd user please choose Cancel!");

    msgBox->setIcon(SYS_STR_CRITICAL);
    msgBox->setTitle(mStrTitle);
    msgBox->setText(mStrText);

    mBtnNo = msgBox->addButton(QApplication::translate("CSystemPlatform", "Cancel"));
    mBtnYes = msgBox->addButton(QApplication::translate("CSystemPlatform", "Yes"));

    connect(msgBox,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(OnPlatformConfirm(QAbstractButton*)));
    msgBox->show();
}
void CSystemPlatform::OnPlatformPressed()
{

    pBtnGroup[g_dbsys.utility.mPlatform]->setStyleSheet( "background-color:cyan ; border : 2px solid black;");
    pBtnGroup[m_iFocusCurrent]->setStyleSheet( "background-color:lightGray ; border : 2px solid black;");

    for(int mIdx = 0 ; mIdx < PLATFORM_MAX; mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
        {
            m_iFocusCurrent = mIdx;
            break;
        }
    }

    pBtnGroup[g_dbsys.utility.mPlatform]->setStyleSheet( "background-color:cyan ; border : 2px solid black;");
    pBtnGroup[m_iFocusCurrent]->setStyleSheet( "background-color:lightGray ; border : 3px solid green;");

    BtnPressed(m_iFocusCurrent);
}
void CSystemPlatform::PlatformIndex()
{

    if(g_dbsys.utility.mPlatform == m_iFocusCurrent)
        pBtnGroup[m_iFocusCurrent]->setStyleSheet( "background-color:cyan ; border : 2px solid black;");
    else
        pBtnGroup[m_iFocusCurrent]->setStyleSheet( "background-color:lightGray ; border : 2px solid black;");

    if(++m_iFocusCurrent >= PLATFORM_MAX )
        m_iFocusCurrent = 0;

    if(m_iFocusCurrent == PF_UARM_10_A  || m_iFocusCurrent == PF_NDT_10_A )
        m_iFocusCurrent += 1;

    if(m_iFocusCurrent >= PLATFORM_MAX )
        m_iFocusCurrent = 0;

    if(g_dbsys.utility.mPlatform == m_iFocusCurrent)
        pBtnGroup[m_iFocusCurrent]->setStyleSheet( "background-color:cyan ; border : 3px solid green;");
    else
        pBtnGroup[m_iFocusCurrent]->setStyleSheet( "background-color:lightGray ; border : 3px solid green;");

}

void CSystemPlatform::OnBtnExit()
{
    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
    }
}

void CSystemPlatform::OnBtnReboot()
{
    if(sender() == btReboot)
    {
        RsMgr->g_filmBase->SetLCD(false);
        MySystem("reboot");
    }
}

/*
void CSystemPlatform::PlatformCheck(int mPf, bool chk)
{

    for(int mIdx = 0 ; mIdx < PLATFORM_MAX ; mIdx++)
    {
        if((1 << mIdx) == mPf)
        {
            if(chk)
                pBtnGroup[mIdx]->setStyleSheet( "QPushButton {background-color:cyan  ; border : 3px solid green; }");
            else
                pBtnGroup[mIdx]->setStyleSheet( "QPushButton {background-color:lightGray ; border : 2px solid black;}");
        }
    }
}
*/
