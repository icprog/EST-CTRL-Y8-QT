#include "system_network.h"
#include "resource_manager.h"
#include <QProcess>
#include <QNetworkInterface>

#define NET_EDIT_LENGTH (15)
#define NET_TEST_START  (0)
#define NET_TEST_ONE    (1)
#define NET_TEST_TWO    (2)
#define NET_TEST_END    (3)

CSystemNetWork::CSystemNetWork(QWidget *parent) :
    CSystemBase(parent)
{
    setObjectName("CSystemNetWork");

    resize(600,600);

    m_iTestState    = NET_TEST_START;
    m_iTestWait     = false;
    m_iTestCount    = 0;
    m_iFocusCurrent = -1;

    ping = new QProcess(this);

    textTitle->setText(QApplication::translate("CSystemNetWork", "System Network Settings"));

    strWorkMode = new QLabel(this);
    strWorkMode->setGeometry(QRect(0, 65, 140, 50));
    strWorkMode->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strWorkMode->setText(QApplication::translate("CSystemNetWork", "Service Mode:" ));

    btNetModeClient = new CButtonStable(this);
    btNetModeClient->setGeometry(QRect(150, 65, 100, 55));

    btNetModeServer = new CButtonStable(this);
    btNetModeServer->setGeometry(QRect(250, 65, 100, 55));

    btNetModeClient->setText(QApplication::translate("CSystemNetWork", "Client" ));
    btNetModeServer->setText(QApplication::translate("CSystemNetWork", "Server" ));

    strNetMode = new QLabel(this);
    strNetMode->setGeometry(QRect(0, 135, 140, 50));
    strNetMode->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strNetMode->setText(QApplication::translate("CSystemNetWork", "Work Mode:" ));

    btNetEth0 = new CButtonStable(this);
    btNetEth0->setGeometry(QRect(150, 135, 100, 55));
    btNetEth0->setText(QApplication::translate("CSystemNetWork", "LAN" ));

    btNetWlan0 = new CButtonStable(this);
    btNetWlan0->setGeometry(QRect(250, 135, 100, 55));
    btNetWlan0->setText(QApplication::translate("CSystemNetWork", "Wifi" ));

    //由于功能没有设计完成，暂时不显示遥控按钮//jsy20151217
    btNetRemote0 = new CButtonStable(this);
    btNetRemote0->setGeometry(QRect(350, 65, 100, 55));
    btNetRemote0->setText(QApplication::translate("CSystemNetWork", "Remote" ));
    btNetRemote0->setVisible(true);

    strIpAddr   = new QLabel(this);
    strIpAddr->setGeometry(QRect(0, 200, 140, 50));
    strIpAddr->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strIpAddr->setText(QApplication::translate("CSystemNetWork", "IP Address:" ));

    editNet[NET_EDIT_IP]   = new QLabel(this);
    editNet[NET_EDIT_IP]->setGeometry(QRect(150, 200, 200, 50));
    editNet[NET_EDIT_IP]->installEventFilter(this);
    editNet[NET_EDIT_IP]->setStyleSheet("color:blue;background-color:white; border : 1px solid black");

    strNetMask  = new QLabel(this);
    strNetMask->setGeometry(QRect(0, 250, 140, 50));
    strNetMask->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strNetMask->setText(QApplication::translate("CSystemNetWork", "NetMask:" ));

    editNet[NET_EDIT_MASK]  = new QLabel(this);
    editNet[NET_EDIT_MASK]->setGeometry(QRect(150, 250, 200, 50));
    editNet[NET_EDIT_MASK]->installEventFilter(this);
    editNet[NET_EDIT_MASK]->setStyleSheet("color:blue;background-color:white; border : 1px solid black");

    strGate     = new QLabel(this);
    strGate->setGeometry(QRect(0, 300, 140, 50));
    strGate->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strGate->setText(QApplication::translate("CSystemNetWork", "Gate:" ));

    editNet[NET_EDIT_GATE]     = new QLabel(this);
    editNet[NET_EDIT_GATE]->setGeometry(QRect(150, 300, 200, 50));
    editNet[NET_EDIT_GATE]->installEventFilter(this);
    editNet[NET_EDIT_GATE]->setStyleSheet("color:blue;background-color:white; border : 1px solid black");

    strDns      = new QLabel(this);
    strDns->setGeometry(QRect(0, 350, 140, 50));
    strDns->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strDns->setText(QApplication::translate("CSystemNetWork", "DNS:" ));

    editNet[NET_EDIT_DNS]      = new QLabel(this);
    editNet[NET_EDIT_DNS]->setGeometry(QRect(150, 350, 200, 50));
    editNet[NET_EDIT_DNS]->installEventFilter(this);
    editNet[NET_EDIT_DNS]->setStyleSheet("color:blue;background-color:white; border : 1px solid black");

    btTestGate = new CButtonStable(this);
    btTestGate->setGeometry(QRect(250, 425, 160, 55));
    btTestGate->setText(QApplication::translate("CSystemNetWork", "Gate Test" ));

    btTestInternet = new CButtonStable(this);
    btTestInternet->setGeometry(QRect(420, 425, 160, 55));
    btTestInternet->setText(QApplication::translate("CSystemNetWork", "Internet Test" ));

    strMsgNotify    = new QLabel(this);
    strMsgNotify->setGeometry(QRect(0, 425, 240, 50));
    strMsgNotify->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    btNetSave = new CButtonStable(this);
    btNetSave->setGeometry(QRect(420, 525, 100, 60));
    btNetSave->setText(QApplication::translate("CSystemNetWork", "Save" ));

    timerInternetTest = new QTimer(this);
    timerInternetTest->setInterval(200);
    connect(timerInternetTest,  SIGNAL(timeout()),this,SLOT(OnTimerInternetTest()));

    timerGateTest = new QTimer(this);
    timerGateTest->setInterval(200);
    connect(timerGateTest,  SIGNAL(timeout()),this,SLOT(OnTimerGateTest()));

    connect(btNetEth0,  SIGNAL(pressed()),this,SLOT(OnModeLan()));
    connect(btNetWlan0, SIGNAL(pressed()),this,SLOT(OnModeWifi()));
    connect(btNetRemote0, SIGNAL(pressed()),this,SLOT(OnModeRemote()));
    connect(btNetSave,  SIGNAL(pressed()),this,SLOT(OnBtnNetSave()));
    connect(btTestGate, SIGNAL(pressed()),this,SLOT(OnBtnGateTest()));
    connect(btTestInternet,     SIGNAL(pressed()),this,SLOT(OnBtnInternetTest()));
    connect(btNetModeClient,    SIGNAL(pressed()),this,SLOT(OnNetWorkPressed()));
    connect(btNetModeServer,    SIGNAL(pressed()),this,SLOT(OnNetWorkPressed()));
    connect(btnExit,            SIGNAL(pressed()),this,SLOT(OnNetWorkExit()));

    translateFontSize( this );

    getNetWorkCfg();

    if( g_dbsys.utility.mNetMode == NET_WIFI)
        FlushNetWorkCfg();
}

void CSystemNetWork::DisplayNetInfoWlan0()
{
    QNetworkInterface netInterfaceWlan = QNetworkInterface::interfaceFromName ("wlan0");
    QList<QNetworkAddressEntry> entryListWlan = netInterfaceWlan.addressEntries();
    if(!entryListWlan.isEmpty())
        entryWlan0 = entryListWlan.at(0);

    editNet[NET_EDIT_IP]->setText(entryWlan0.ip().toString());
    editNet[NET_EDIT_MASK]->setText(entryWlan0.netmask().toString());

    if(   g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        editNet[NET_EDIT_GATE]->setText("");
        editNet[NET_EDIT_DNS]->setText("");
    }else
    {
        QString cBuf;

        cBuf = g_mainCfg->value("network/svrGate","169.254.001.001").toByteArray().data();
        editNet[NET_EDIT_GATE]->setText(cBuf);

        cBuf = g_mainCfg->value("network/svrDNS","169.254.001.001").toByteArray().data();
        editNet[NET_EDIT_DNS]->setText(cBuf);
    }
}
void CSystemNetWork::DisplayNetInfoEth0()
{
    QNetworkInterface netInterfaceEth = QNetworkInterface::interfaceFromName ("eth0");
    QList<QNetworkAddressEntry> entryListEth = netInterfaceEth.addressEntries();
    if(!entryListEth.isEmpty())
        entryEth0 = entryListEth.at(0);

    editNet[NET_EDIT_IP]->setText(entryEth0.ip().toString());
    editNet[NET_EDIT_MASK]->setText(entryEth0.netmask().toString());

    if(   g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        editNet[NET_EDIT_GATE]->setText("");            //clear gate and dns info
        editNet[NET_EDIT_DNS]->setText("");
    }else
    {                                                       //set gate and dns info for arm linux
        QString cBuf;

        cBuf = g_mainCfg->value("network/svrGate","169.254.001.001").toByteArray().data();
        editNet[NET_EDIT_GATE]->setText(cBuf);

        cBuf = g_mainCfg->value("network/svrDNS","169.254.001.001").toByteArray().data();
        editNet[NET_EDIT_DNS]->setText(cBuf);
    }
}

void CSystemNetWork::showEvent(QShowEvent *event)
{

    //set remote button background color
    btNetRemote0->setStyleSheet("background-color:darkGray ; border : 1px solid black");

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        btNetModeClient->setStyleSheet("background-color:cyan ; border : 1px solid black");
        btNetModeServer->setStyleSheet("background-color:darkGray ; border : 1px solid black");
    }else if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
    {
        btNetModeClient->setStyleSheet("background-color:darkGray ; border : 1px solid black");
        btNetModeServer->setStyleSheet("background-color:cyan ; border : 1px solid black");
    }

    if(g_dbsys.utility.mNetMode == NET_LAN)
    {
        btNetWlan0->setStyleSheet("background-color:darkGray ; border : 1px solid black");
        btNetEth0->setStyleSheet("background-color:cyan ; border : 1px solid black");

        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
            DisplayNetInfoEth0();
        else
            getNetWorkCfg();
    }

    if(g_dbsys.utility.mNetMode == NET_WIFI)
    {
        btNetWlan0->setStyleSheet("background-color:cyan ; border : 1px solid black");
        btNetEth0->setStyleSheet("background-color:darkGray ; border : 1px solid black");

        if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
            DisplayNetInfoWlan0();
        else
            getNetWorkCfg();
    }


    if (g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad=new CSystemImepad(this);

    grabKeyboard();

    CSystemBase::showEvent(event);

}
void CSystemNetWork::hideEvent(QHideEvent * event)
{
    releaseKeyboard();

    CSystemBase::hideEvent(event);
}
void CSystemNetWork::OnNetWorkExit()
{
    if(sender() == btnExit )
    {

        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        return;
    }
}
void CSystemNetWork::OnNetWorkPressed()
{

    if(sender() == btNetModeClient )
    {

        if(g_systemPad)
            g_systemPad->hide();

        btNetModeClient->setStyleSheet("background-color:cyan; border : 1px solid black");
        btNetModeServer->setStyleSheet("background-color:darkGray; border : 1px solid black");

        g_dbsys.utility.mNetTcpMode = TARGET_TCP_CLIENT;
        g_systemDb->SaveSystemCfg("utility/mNetTcpMode",g_dbsys.utility.mNetTcpMode);

        btNetSave->setEnabled(false);

        if(g_dbsys.utility.mNetMode == NET_LAN)
            DisplayNetInfoEth0();
        else
            DisplayNetInfoWlan0();
    }

    if(sender() == btNetModeServer )
    {

        if(g_systemPad)
            g_systemPad->hide();

        btNetModeClient->setStyleSheet("background-color:darkGray; border : 1px solid black");
        btNetModeServer->setStyleSheet("background-color:cyan; border : 1px solid black");

        g_dbsys.utility.mNetTcpMode = TARGET_TCP_SERVER;
        g_systemDb->SaveSystemCfg("utility/mNetTcpMode",g_dbsys.utility.mNetTcpMode);

        btNetSave->setEnabled(true);

        getNetWorkCfg();
    }
}

void CSystemNetWork::keyPressEvent ( QKeyEvent * event )
{

    int mKey = event->key();
    switch (mKey) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        break;

    case Qt::Key_Backspace:

        m_strKeyBuff.chop( 1);
        editNet[m_iFocusCurrent]->setText(m_strKeyBuff);

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
        if(m_strKeyBuff.length() < NET_EDIT_LENGTH)
            m_strKeyBuff.append(event->key());

        if(m_strKeyBuff.length() == 3 || m_strKeyBuff.length() == 7 || m_strKeyBuff.length() == 11)
            m_strKeyBuff.append(".");

        editNet[m_iFocusCurrent]->setText(m_strKeyBuff);
        break;
    }

}

bool CSystemNetWork::eventFilter(QObject *watched, QEvent *event)
{

    //client mode disable ip setting function
    if(   g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(g_systemPad)
            g_systemPad->hide();
    }

    for(int mIdx = 0 ;mIdx < NET_EDIT_MAX ; mIdx++)
    {
        if(editNet[mIdx] == watched)
        {
            if(event->type()==QEvent::MouseButtonPress)
            {
                g_systemPad->move(380 ,130);

                g_systemPad->show();

                if(m_iFocusCurrent >= 0)
                    editNet[m_iFocusCurrent]->setStyleSheet("color:blue;background-color : white; border : 1px solid black");

                m_iFocusCurrent = mIdx;
                editNet[m_iFocusCurrent]->setStyleSheet("color:red;background-color : cyan; border : 1px solid black");

                m_strKeyBuff = "";

            }
        }
    }

    return QWidget::eventFilter(watched,event);
}



void CSystemNetWork::OnTimerInternetTest()
{
    if(m_iTestWait)
        return;

    switch(m_iTestState)
    {
    case NET_TEST_START:
        QHostInfo::lookupHost("www.baidu.com",this, SLOT(lookedUp(QHostInfo)));
        strMsgNotify->setText("try www.baidu.com");
        break;
    case NET_TEST_ONE:
        QHostInfo::lookupHost("www.163.com",this, SLOT(lookedUp(QHostInfo)));
        strMsgNotify->setText("try www.163.com" );
        break;
    case NET_TEST_TWO:
        QHostInfo::lookupHost("www.estmedcare.com",this, SLOT(lookedUp(QHostInfo)));
        strMsgNotify->setText("try www.estmedcare.com");
        break;
    case NET_TEST_END:
        timerInternetTest->stop();
        if(m_iTestCount >=2)
        {
            strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Test Pass!" ));
            strMsgNotify->setStyleSheet("color : green;");
        }else
        {
            strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Test Fail!" ));
            strMsgNotify->setStyleSheet("color : red;");
        }

        btTestInternet->setEnabled(true);
        break;
    }

    m_iTestWait = true;
}

void CSystemNetWork::OnBtnInternetTest()
{

    m_iTestState    = NET_TEST_START;
    m_iTestWait     = false;
    m_iTestCount    = 0;
    timerInternetTest->start();

    btTestInternet->setEnabled(false);

}
void CSystemNetWork::OnTimerGateTest()
{
    m_iTestCount++;

    if(m_iTestCount < 50)
        return ;

    ping->terminate();

    timerGateTest->stop();

    QByteArray byteRead;

    byteRead = ping->readAll();

    int mPackageNum = 0;
    int mTagPos = 0;
    int mTagFail = 0;
    int mTagSucc = 0;
    int mFailNum = 0;
    int mSuccNum = 0;

    do{
        mTagPos = byteRead.indexOf("icmp_seq=",mTagPos + 1);
        mPackageNum++;

        mTagFail = byteRead.indexOf("Unreachable",mTagFail + 1);
        if(mTagFail != -1)
            mFailNum++;

        mTagSucc = byteRead.indexOf("time=",mTagSucc + 1);
        if(mTagSucc != -1)
            mSuccNum++;

    }while(mTagPos != -1);


    if((float)mSuccNum / (float)mPackageNum > 0.75)
    {
        strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Test Pass!" ));
        strMsgNotify->setStyleSheet("color : green;");

    }else
    {
        strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Test Fail!" ));
        strMsgNotify->setStyleSheet("color : green;");
    }

    btTestGate->setEnabled(true);
}

void CSystemNetWork::OnBtnGateTest()
{
    m_iTestCount = 0;

    QString mBuf;

    mBuf = editNet[NET_EDIT_GATE]->text();
    if(!IPAdressFormat(mBuf))
    {
        strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Invalid data." ));
        strMsgNotify->setStyleSheet("color : red;");

        return;
    }

    mBuf.insert(0,"ping ");
    strMsgNotify->setText(mBuf);

    ping->start(mBuf);

    timerGateTest->start();

    btTestGate->setEnabled(false);

}

void CSystemNetWork::IPAdressPatch(QString & mStr)
{

    QString mSec0,mSec1,mSec2,mSec3;
    int mTemp,mDat0,mDat1,mDat2,mDat3;
    mTemp =  mStr.indexOf(".");
    mSec0 = mStr.left(mTemp);
    mStr.remove(0,mTemp + 1);
    mDat0 = mSec0.toUInt();

    mTemp =  mStr.indexOf(".");
    mSec1 = mStr.left(mTemp);
    mStr.remove(0,mTemp + 1);
    mDat1 = mSec1.toUInt();

    mTemp =  mStr.indexOf(".");
    mSec2 = mStr.left(mTemp);
    mStr.remove(0,mTemp + 1);
    mDat2 = mSec2.toUInt();

    mTemp =  mStr.indexOf(".");
    mSec3 = mStr.left(mTemp);
    mDat3 = mSec3.toUInt();

    mStr.sprintf("%03d.%03d.%03d.%03d",mDat0,mDat1,mDat2,mDat3);
}
int CSystemNetWork::IPAdressFormat(QString &mStr)
{
    QString mSec0,mSec1,mSec2,mSec3;
    int mTemp,mDat0,mDat1,mDat2,mDat3;
    mTemp =  mStr.indexOf(".");
    mSec0 = mStr.left(mTemp);
    mStr.remove(0,mTemp + 1);
    mDat0 = mSec0.toUInt();

    mTemp =  mStr.indexOf(".");
    mSec1 = mStr.left(mTemp);
    mStr.remove(0,mTemp + 1);
    mDat1 = mSec1.toUInt();

    mTemp =  mStr.indexOf(".");
    mSec2 = mStr.left(mTemp);
    mStr.remove(0,mTemp + 1);
    mDat2 = mSec2.toUInt();

    mTemp =  mStr.indexOf(".");
    mSec3 = mStr.left(mTemp);
    mDat3 = mSec3.toUInt();

    mStr.sprintf("%d.%d.%d.%d",mDat0,mDat1,mDat2,mDat3);

    if(mDat0 > 255 || mDat1 > 255 || mDat2 > 255 || mDat3 > 255 )
        return false;
    else
        return true;
}

void CSystemNetWork::getNetWorkCfg()
{

    QFile fileNetCfg("/etc/eth0-setting");

    if(fileNetCfg.open(QFile::ReadOnly))
    {
        QTextStream tfile(&fileNetCfg);

        QString mBuf;
        mBuf = tfile.readLine(128);
        m_strIp = mBuf.remove(0,3);
        IPAdressPatch(m_strIp);
        editNet[NET_EDIT_IP]->setText(m_strIp);

        mBuf = tfile.readLine(128);
        m_strMask = mBuf.remove(0,5);
        IPAdressPatch(m_strMask);
        editNet[NET_EDIT_MASK]->setText(m_strMask);

        mBuf = tfile.readLine(128);
        m_strGate = mBuf.remove(0,8);
        IPAdressPatch(m_strGate);
        editNet[NET_EDIT_GATE]->setText(m_strGate);

        mBuf = tfile.readLine(128);
        m_strDNS = mBuf.remove(0,4);
        IPAdressPatch(m_strDNS);
        editNet[NET_EDIT_DNS]->setText(m_strDNS);

        m_strMAC = tfile.readLine(128);

        fileNetCfg.close();
    }else
    {
        QString cBuf;

        cBuf = g_mainCfg->value("network/svrIP","169.254.001.001").toByteArray().data();
        editNet[NET_EDIT_IP]->setText(cBuf);

        cBuf = g_mainCfg->value("network/svrNetMask","169.254.001.001").toByteArray().data();
        editNet[NET_EDIT_MASK]->setText(cBuf);

        cBuf = g_mainCfg->value("network/svrGate","169.254.001.001").toByteArray().data();
        editNet[NET_EDIT_GATE]->setText(cBuf);

        cBuf = g_mainCfg->value("network/svrDNS","169.254.001.001").toByteArray().data();
        editNet[NET_EDIT_DNS]->setText(cBuf);

    }

}

void CSystemNetWork::OnBtnNetSave()
{

    m_strIp     = editNet[NET_EDIT_IP]->text();
    m_strMask   = editNet[NET_EDIT_MASK]->text();
    m_strGate   = editNet[NET_EDIT_GATE]->text();
    m_strDNS    = editNet[NET_EDIT_DNS]->text();

    if(m_strIp.length() < 15      || m_strMask.length() < 15 ||
            m_strGate.length() < 15 || m_strDNS.length() < 15 )
    {
        strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Invalid data length." ));
        strMsgNotify->setStyleSheet("color : red;");

        return;
    }
    int mValid = true;

    if(!IPAdressFormat(m_strIp))
        mValid = false;
    if(!IPAdressFormat(m_strMask))
        mValid = false;
    if(!IPAdressFormat(m_strGate))
        mValid = false;
    if(!IPAdressFormat(m_strDNS))
        mValid = false;

    if(!mValid)
    {
        strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Invalid data." ));
        strMsgNotify->setStyleSheet("color : red;");

        return;
    }

    QFile fileNetCfg("/etc/eth0-setting~");

    if(!fileNetCfg.open(QFile::WriteOnly ))
    {
        strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Config file not found." ));
        strMsgNotify->setStyleSheet("color : red;");

        g_mainCfg->setValue("network/svrIP",editNet[NET_EDIT_IP]->text());
        g_mainCfg->setValue("network/svrNetMask",editNet[NET_EDIT_MASK]->text());
        g_mainCfg->setValue("network/svrGate",editNet[NET_EDIT_GATE]->text());
        g_mainCfg->setValue("network/svrDNS", editNet[NET_EDIT_DNS]->text());

        return;
    }

    QTextStream tfile(&fileNetCfg);

    QString mBuf;

    mBuf = m_strIp;
    mBuf.insert(0,"IP=");
    tfile<<mBuf<<endl;

    mBuf = m_strMask;
    mBuf.insert(0,"Mask=");
    tfile<<mBuf<<endl;

    mBuf = m_strGate;
    mBuf.insert(0,"Gateway=");
    tfile<<mBuf<<endl;

    mBuf = m_strDNS;
    mBuf.insert(0,"DNS=");
    tfile<<mBuf<<endl;

    tfile<<m_strMAC<<endl;

    fileNetCfg.flush();
    fileNetCfg.close();

    strMsgNotify->setText(QApplication::translate("CSystemNetWork", "Save successfully!" ));
    strMsgNotify->setStyleSheet("color : green;");

    FlushNetWorkCfg();

}
void CSystemNetWork::FlushNetWorkCfg()
{
    int mRes;
    //保存和更新的IP地址必须是特定格式
    //command is safe on ubuntu system.
    system("cp -f /etc/eth0-setting~ /etc/eth0-setting");
    mRes = system("chmod 777 /etc/eth0-setting");

    if(mRes == -1)
    {
        qDebug() << "CSystemGeneral::OnButtonUpdate " << "system error!";
        return;
    }

    if( g_dbsys.utility.mNetMode == NET_LAN)
    {
        ping->start("./etc/init.d/ifconfig-eth0");
    }

    if( g_dbsys.utility.mNetMode == NET_WIFI)
    {
        ping->start("./etc/init.d/ifconfig-wlan0");
    }


}
void CSystemNetWork::lookedUp(const QHostInfo &host)
{

    m_iTestWait = false;

    if (host.error() == QHostInfo::NoError)
        m_iTestCount += 1;

    m_iTestState++;

}

void CSystemNetWork::OnModeLan()
{

    g_dbsys.utility.mNetMode = NET_LAN;

    g_systemDb->SaveSystemCfg("utility/mNetMode",g_dbsys.utility.mNetMode);

    btNetWlan0->setStyleSheet("background-color:darkGray ; border : 1px solid black");
    btNetEth0->setStyleSheet("background-color:cyan ; border : 1px solid black");

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
        DisplayNetInfoEth0();
    else
        getNetWorkCfg();

}
void CSystemNetWork::OnModeWifi()
{
    g_dbsys.utility.mNetMode = NET_WIFI;

    g_systemDb->SaveSystemCfg("utility/mNetMode",g_dbsys.utility.mNetMode);

    btNetWlan0->setStyleSheet("background-color:cyan ; border : 1px solid black");
    btNetEth0->setStyleSheet("background-color:darkGray ; border : 1px solid black");

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
        DisplayNetInfoWlan0();
    else
        getNetWorkCfg();

}

void CSystemNetWork::OnModeRemote()
{

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(!RsMgr->g_remoteClient)
            return;

        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_remoteClient);
    }

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
    {
        if(!RsMgr->g_remoteServer)
            return;

        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_remoteServer);
    }

}
