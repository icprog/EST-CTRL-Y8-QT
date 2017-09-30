#include "system_general.h"
#include "resource_manager.h"
#include <QSettings>
#include <QFileInfo>

CSystemGeneral::CSystemGeneral(QWidget *parent) :
    CSystemBase(parent)
{
    setObjectName("CSystemGeneral");

    resize(600, 600);

    for(int mIdx = 0 ; mIdx < 6 ; mIdx++)
    {
        pFrameLine[mIdx] = new QFrame(this);
        pFrameLine[mIdx]->setFrameShape(QFrame::HLine);
        pFrameLine[mIdx]->setFrameShadow(QFrame::Sunken);
    }

    pFrameLine[0]->setGeometry(QRect(30, 120, 500, 10));
    pFrameLine[1]->setGeometry(QRect(30, 190, 500, 10));
    pFrameLine[2]->setGeometry(QRect(30, 400, 500, 10));
    pFrameLine[3]->setGeometry(QRect(30, 260, 500, 10));
    pFrameLine[4]->setGeometry(QRect(30, 330, 500, 10));
    pFrameLine[5]->setGeometry(QRect(295, 265, 10, 69));
    pFrameLine[5]->setFrameShape(QFrame::VLine);

    for(int  mIdx = 0 ; mIdx < 14 ; mIdx++)
    {
        strCtrl[mIdx] = new QLabel(this);
        strCtrl[mIdx]->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        strCtrl[mIdx]->setWordWrap(false);
    }

    strCtrl[0]->setGeometry(QRect(30, 60, 180, 50));
    strCtrl[0]->setText(QApplication::translate("CSystemGeneral", "Key Sound:"));

    strCtrl[1]->setGeometry(QRect(30, 130, 191, 50));
    strCtrl[1]->setText(QApplication::translate("CSystemGeneral", "System Skin:"));

    strCtrl[2]->setGeometry(QRect(30, 435, 560, 35));
    strCtrl[2]->setText(QApplication::translate("CSystemGeneral", "Address: Building 2,Lane 1135,Baotou RD,Yangpu,Shanghai,China"));

    strCtrl[3]->setGeometry(QRect(30, 465, 560, 35));
    strCtrl[3]->setText(QApplication::translate("CSystemGeneral", "Tel: +86-400-089-6518 (86-021-65248601)"));

    strCtrl[4]->setGeometry(QRect(30, 405, 560, 35));
    strCtrl[4]->setText(QApplication::translate("CSystemGeneral", "Manufacturer: EST(Shanghai) Medical Equipment CO..,LTD"));

    strCtrl[5]->setGeometry(QRect(30, 210, 381, 35));
    strCtrl[5]->setText(QApplication::translate("CSystemGeneral", "New system skin will take effect after system reboot."));

    strCtrl[6]->setGeometry(QRect(20, 285, 160, 35));
    strCtrl[6]->setText(QApplication::translate("CSystemGeneral", "Software version:"));

    strCtrl[7]->setGeometry(QRect(180, 285, 115, 35));
    strCtrl[7]->setText(g_dbsys.softVersion);

    strCtrl[8]->setGeometry(QRect(305, 285, 160, 35));
    strCtrl[8]->setText(QApplication::translate("CSystemGeneral", "Build Date:"));

    //   QFileInfo * pMainProgram = new QFileInfo("/sdcard/home/fa/w6410");
    QFileInfo * pMainProgram = new QFileInfo(QCoreApplication::applicationFilePath());

    if(pMainProgram->exists())
    {
        QDateTime mDate = pMainProgram->lastModified();

        strCtrl[9]->setGeometry(QRect(470, 285, 130, 35));
        strCtrl[9]->setText(mDate.toString(Qt::ISODate).left(10));
    }

    strCtrl[10]->setGeometry(QRect(30, 338, 160, 31));
    strCtrl[10]->setText(QApplication::translate("CSystemGeneral", "Hospital Name:"));

    strCtrl[11]->setGeometry(QRect(200, 338, 400, 31));
    strCtrl[11]->setStyleSheet("background-color:white");

    strCtrl[12]->setGeometry(QRect(30, 371, 160, 31));
    strCtrl[12]->setText(QApplication::translate("CSystemGeneral", "Hospital Addr:"));

    strCtrl[13]->setGeometry(QRect(200, 371, 400, 31));
    strCtrl[13]->setStyleSheet("background-color:white");

    UpdateClientInfo();

    btReboot = new QPushButton(this);
    btReboot->setGeometry(QRect(470, 200, 100, 60));
    btReboot->setFocusPolicy(Qt::StrongFocus);
    btReboot->setAutoDefault(false);
    btReboot->setText(QApplication::translate("CSystemGeneral", "Reboot"));
    btReboot->setStyleSheet("QPushButton:focus{background-color:cyan}");

    btInfoUpdate = new CButtonStable(this);
    btInfoUpdate->setGeometry(QRect(425, 525, 100, 60));
    btInfoUpdate->setFocusPolicy(Qt::StrongFocus);
    btInfoUpdate->setAutoDefault(false);
    btInfoUpdate->setText(QApplication::translate("CSystemGeneral", "Update"));

    textTitle->setText(QApplication::translate("CSystemGeneral", "System General Setting"));

    pBtnGroup[0] = new CButtonStable(this);
    pBtnGroup[0]->setGeometry(QRect(470, 130, 100, 60));
    pBtnGroup[0]->setStyleSheet("QPushButton:focus{background-color:cyan}");
    pBtnGroup[0]->setText(QApplication::translate("CSystemGeneral", "Scheme 1"));

    pBtnGroup[1] = new CButtonStable(this);
    pBtnGroup[1]->setGeometry(QRect(350, 130, 100, 60));
    pBtnGroup[1]->setStyleSheet("QPushButton:focus{background-color:cyan}");
    pBtnGroup[1]->setText(QApplication::translate("CSystemGeneral", "Scheme 2"));
    pBtnGroup[1]->setEnabled(false);

    pBtnGroup[2] = new CButtonStable(this);
    pBtnGroup[2]->setGeometry(QRect(230, 130, 100, 60));
    pBtnGroup[2]->setStyleSheet("QPushButton:focus{background-color:cyan}");
    pBtnGroup[2]->setText(QApplication::translate("CSystemGeneral", "Scheme 3"));
    pBtnGroup[2]->setEnabled(false);

    //only U-ARM system have 2 scheme
    if(g_dbsys.utility.mPlatform == PF_UARM_08_A)
    {
        pBtnGroup[1]->setEnabled(true);
    }

    btKeySound = new CButtonStable(this);
    btKeySound->setGeometry(QRect(470, 60, 100, 60));
    btKeySound->setStyleSheet("QPushButton:focus{background-color:cyan}");

    if(g_dbsys.utility.keySound == 0)
    {
        btKeySound->setText(QApplication::translate("CSystemGeneral", "OFF"));
        btKeySound->setStyleSheet( "background-color:lightGray");
    }else
    {
        btKeySound->setText(QApplication::translate("CSystemGeneral", "ON"));
        btKeySound->setStyleSheet( "background-color:cyan");
    }

    for(int mIdx = 0 ; mIdx < 3 ;mIdx++)
    {
        connect(pBtnGroup[mIdx],    SIGNAL(pressed()),this,SLOT(OnButtonPressed()));
        pBtnGroup[mIdx]->setStyleSheet( "background-color:lightGray");
    }

    int mSkin = g_dbsys.utility.mSkinIdx;
    if(mSkin >=0 && mSkin < 3)
        pBtnGroup[mSkin]->setStyleSheet( "background-color:cyan");

    m_iRebootCount = 0;

    connect(btKeySound,     SIGNAL(pressed()),this,SLOT(OnButtonPressed()));
    connect(btnExit,        SIGNAL(pressed()),this,SLOT(OnButtonControl()));
    connect(btReboot,       SIGNAL(pressed()),this,SLOT(OnButtonControl()));
    connect(btInfoUpdate,   SIGNAL(pressed()),this,SLOT(OnButtonUpdate()));

    translateFontSize(this);
}


void CSystemGeneral::OnButtonPressed()
{

    if(sender() ==  btKeySound )
    {

        if( g_dbsys.utility.keySound == 0)
        {
            g_dbsys.utility.keySound = 1;
            btKeySound->setText(QApplication::translate("CSystemGeneral", "ON"));
            btKeySound->setStyleSheet( "background-color:cyan ; border : 2px solid green");
        }else
        {
            g_dbsys.utility.keySound = 0;
            btKeySound->setText(QApplication::translate("CSystemGeneral", "OFF"));
            btKeySound->setStyleSheet( "background-color:lightGray; border : 2px solid green");
        }

        m_iRebootCount++;

        if(m_iRebootCount > 3)
            btReboot->setVisible(true);
    }

    int mSkinNew = -1;
    for(int mIdx = 0 ; mIdx < 3 ;mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
            mSkinNew = mIdx;
    }

    if(mSkinNew >= 0 && mSkinNew < 3)
    {

        for(int mIdx = 0 ; mIdx < 3 ;mIdx++)
        {
            pBtnGroup[mIdx]->setStyleSheet( "background-color:lightGray ; border : 2px solid green");
        }

        pBtnGroup[mSkinNew]->setStyleSheet( "background-color:cyan ; border : 2px solid green");
        g_dbsys.utility.mSkinIdx = mSkinNew;
    }

    g_systemDb->SaveSystemCfg("utility/mSkinIdx",g_dbsys.utility.mSkinIdx);
}
void CSystemGeneral::OnButtonControl()
{

    if(sender() == btnExit)
    {
        this->hide();
        emit ViewChange(VIEW_MAIN);
        return;
    }

    if(sender() == btReboot )
    {
        RsMgr->g_filmBase->SetLCD(false);

        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
        {
            if(!g_netBase)
                return;

            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = CMD_FUNC_REBOOT;
            keyBuf[1] = CMD_FUNC_REBOOT;
            g_netBase->PublishMessage();
        }else
        {

            RsMgr->g_filmBase->SetLCD(false);

            MySystem("reboot");
        }
    }
}

void CSystemGeneral::OnButtonUpdate()
{
    int mRes;

    if(sender() == btInfoUpdate)
    {
        if(QFile::exists("/udisk/estmedcarefirmware/clientinfo.ini"))
        {
            mRes =  system("cp -f /udisk/estmedcarefirmware/clientinfo.ini /sdcard/home/fa/clientinfo.ini");

            if(mRes == -1)
            {
                qDebug() << "CSystemGeneral::OnButtonUpdate " << "system error!";
                return;
            }

            UpdateClientInfo();
        }else
        {
            strCtrl[11]->setText("/udisk/estmedcarefirmware/clientinfo.ini not found!");
            strCtrl[11]->setStyleSheet("color : red;background-color:white");
        }
    }
}

void CSystemGeneral::UpdateClientInfo()
{
    QSettings * configClientInfo = new QSettings("/sdcard/home/fa/clientinfo.ini",QSettings::IniFormat);
    QString mStrClientName    = QString::fromUtf8(configClientInfo->value("/client/HospitalName").toByteArray());
    QString mStrClientAddr      = QString::fromUtf8(configClientInfo->value("/client/address").toByteArray());

    strCtrl[11]->setStyleSheet("color : black;background-color:white");
    strCtrl[11]->setText(mStrClientName);
    strCtrl[13]->setText(mStrClientAddr);

}
void CSystemGeneral::showEvent(QShowEvent *)
{

    btReboot->setVisible(false);

    RsMgr->VisibleWidgetAdd(this);
}

void CSystemGeneral::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}

