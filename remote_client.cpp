#include "remote_client.h"
#include "resource_manager.h"
#include <QSettings>

#include <QSqlDriver>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QTextCodec>

#define TCP_SLAVE_PORT      52430

CRemoteClient::CRemoteClient(QWidget *parent) :
    CRemoteBase(parent)
{

    setObjectName("CRemoteClient");

    resize(600,600);

    textTitle->setText(QApplication::translate("CRemoteBase", "Remote Slave Setting"));

    strServerAddr = new QLabel(this);
    strServerAddr->setGeometry(QRect(10, 70, 160, 40));
    strServerAddr->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strServerAddr->setText(QApplication::translate("CRemoteBase", "Server Addr.:" ));

    strClientId = new QLabel(this);
    strClientId->setGeometry(QRect(10, 110, 160, 40));
    strClientId->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strClientId->setText(QApplication::translate("CRemoteBase", "Client ID:" ));

    strOrganization = new QLabel(this);
    strOrganization->setGeometry(QRect(10, 150, 160, 40));
    strOrganization->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strOrganization->setText(QApplication::translate("CRemoteBase", "Agency:" ));

    strAddress = new QLabel(this);
    strAddress->setGeometry(QRect(10, 190, 160, 40));
    strAddress->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strAddress->setText(QApplication::translate("CRemoteBase", "Address:" ));

    strContacts = new QLabel(this);
    strContacts->setGeometry(QRect(10, 230, 160, 40));
    strContacts->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strContacts->setText(QApplication::translate("CRemoteBase", "Contacts:" ));

    strPhone = new QLabel(this);
    strPhone->setGeometry(QRect(10, 270, 160, 40));
    strPhone->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strPhone->setText(QApplication::translate("CRemoteBase", "Telephone:" ));

    strManager = new QLabel(this);
    strManager->setGeometry(QRect(10, 310, 160, 40));
    strManager->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strManager->setText(QApplication::translate("CRemoteBase", "Manager:" ));

    strState = new QLabel(this);
    strState->setGeometry(QRect(10, 350, 160, 40));
    strState->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    strState->setText(QApplication::translate("CRemoteBase", "State:" ));

    pLbServerAddr = new QLabel(this);
    pLbServerAddr->setGeometry(QRect(185, 70, 360, 40));
    pLbServerAddr->setStyleSheet("QFrame { background-color : white; border : 1px solid black}");
    pLbServerAddr->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pLbClientId = new QLabel(this);
    pLbClientId->setGeometry(QRect(185, 110, 360, 40));
    pLbClientId->setStyleSheet("QFrame { background-color : white; border : 1px solid black}");
    pLbClientId->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pLbOrganization = new QLabel(this);
    pLbOrganization->setGeometry(QRect(185, 150, 360, 40));
    pLbOrganization->setStyleSheet("QFrame { background-color : white; border : 1px solid black}");
    pLbOrganization->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pLbAddress = new QLabel(this);
    pLbAddress->setGeometry(QRect(185, 190, 360, 40));
    pLbAddress->setStyleSheet("QFrame { background-color : white; border : 1px solid black}");
    pLbAddress->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pLbContacts = new QLabel(this);
    pLbContacts->setGeometry(QRect(185, 230, 360, 40));
    pLbContacts->setStyleSheet("QFrame { background-color : white; border : 1px solid black}");
    pLbContacts->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pLbPhone = new QLabel(this);
    pLbPhone->setGeometry(QRect(185, 270, 360, 40));
    pLbPhone->setStyleSheet("QFrame { background-color : white; border : 1px solid black}");
    pLbPhone->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pLbManager = new QLabel(this);
    pLbManager->setGeometry(QRect(185, 310, 360, 40));
    pLbManager->setStyleSheet("QFrame { background-color : white; border : 1px solid black}");
    pLbManager->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pLbState = new QLabel(this);
    pLbState->setGeometry(QRect(185, 350, 160, 40));
    pLbState->setStyleSheet("QFrame { background-color : white; border : 1px solid black}");
    pLbState->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pLbMessage = new QLabel(this);
    pLbMessage->setGeometry(QRect(0, 390, 600, 40));
    pLbMessage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    pLbMessage->setStyleSheet("color : red;");

    btnCheckNetWork = new CButtonStable(this);
    btnCheckNetWork->setGeometry(QRect(170, 435, 130, 60));
    btnCheckNetWork->setText(QApplication::translate("CRemoteBase", "Check Net" ));

    btnUpdate = new CButtonStable(this);
    btnUpdate->setGeometry(QRect(300, 435, 130, 60));
    btnUpdate->setText(QApplication::translate("CRemoteBase", "Update Info" ));

    if(QFile::exists(QCoreApplication::applicationDirPath() +"/clientinfo.ini"))     //读取网络服务器地址
    {
        QSettings * configClientInfo = new QSettings(QCoreApplication::applicationDirPath() +"/clientinfo.ini",QSettings::IniFormat);
        mStrServerAddr      = configClientInfo->value("/server/address").toString();
    }

    m_iUpdateState = UPDATE_STATE_CONNECT;

    m_timerConnect = new QTimer(this);
    m_timerConnect->setInterval(200);

    if(!mStrServerAddr.isEmpty())      //如果服务器地址为空，不启动定时器
    {
        InitNetworkClient();
        m_timerConnect->start();
    }

    m_timerBufferCheck = new QTimer(this);

    connect(btnUpdate,SIGNAL(pressed()),this,SLOT(OnUpdateInfo()));
    connect(m_timerConnect,SIGNAL(timeout()),this,SLOT(OnUpdateToServer()));

    translateFontSize( this );

    //database connection is too slow, use thread instead.
    //DbInit();
}

void CRemoteClient::DbInit()
{
    if(!QFile::exists(QCoreApplication::applicationDirPath() +"/clientinfo.ini"))
    {

        return;
    }

    mMainDb = QSqlDatabase::addDatabase("QMYSQL");
    mMainDb.setDatabaseName("db_cloud_001");
    mMainDb.setHostName("169.254.1.81");
    mMainDb.setUserName("db_cloud_user_de");
    mMainDb.setPassword("Db_Cloud_Dev");
    bool ok = mMainDb.open();

    if(ok)
    {
        //ui->label->setText("data base connect successfully");
        qDebug() << "data base connect successfully";

    }else
    {
        //ui->label->setText("data base connect fail");
        qDebug()<<"data base connect fail";
        qDebug() << mMainDb.lastError();
    }

}

void CRemoteClient::InitNetworkClient()
{
    tcpClient = new QTcpSocket();

    connect(tcpClient,SIGNAL(connected()),this,SLOT(OnConnected()));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT(OnClientDisconnected()));
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(OnClientReadyRead()));

    tcpClient->connectToHost(mStrServerAddr,TCP_SLAVE_PORT);
}
void CRemoteClient::OnConnected()
{
    m_iUpdateState = UPDATE_STATE_ID;
}
void CRemoteClient::OnClientDisconnected()
{
    m_iUpdateState = UPDATE_STATE_CONNECT;
}
void CRemoteClient::OnClientReadyRead()
{

}

int CRemoteClient::PutStrToBuf(QString & pStr,unsigned short * mBuf)
{
    QByteArray ba = pStr.toLatin1();
    const char *c_str2 = ba.data();
    strcpy((char *)mBuf,c_str2);

    return strlen((char *)mBuf);
}
void CRemoteClient::OnUpdateToServer()
{
    int mSendLen = 0;

    switch(m_iUpdateState)
    {
    case UPDATE_STATE_CONNECT:
        tcpClient->abort();
        tcpClient->connectToHost(mStrServerAddr,TCP_SLAVE_PORT);
        break;
    case UPDATE_STATE_ID:
        mBufSendToServer[0] = UPDATE_STATE_ID;
        mSendLen = PutStrToBuf(mStrClientId,&mBufSendToServer[1]);
        tcpClient->write((char *)mBufSendToServer,mSendLen);
        break;
    case UPDATE_STATE_AGENY:
        mBufSendToServer[0] = UPDATE_STATE_AGENY;
        mSendLen = PutStrToBuf(mStrClientAgency,&mBufSendToServer[1]);
        tcpClient->write((char *)mBufSendToServer,mSendLen);
        break;
    case UPDATE_STATE_ADDR:
        mBufSendToServer[0] = UPDATE_STATE_ADDR;
        mSendLen = PutStrToBuf(mStrClientAddr,&mBufSendToServer[1]);
        tcpClient->write((char *)mBufSendToServer,mSendLen);
        break;
    case UPDATE_STATE_CONTACT:
        mBufSendToServer[0] = UPDATE_STATE_CONTACT;
        mSendLen = PutStrToBuf(mStrClientContacts,&mBufSendToServer[1]);
        tcpClient->write((char *)mBufSendToServer,mSendLen);
        break;
    case UPDATE_STATE_PHONE:
        mBufSendToServer[0] = UPDATE_STATE_PHONE;
        mSendLen = PutStrToBuf(mStrClientPhone,&mBufSendToServer[1]);
        tcpClient->write((char *)mBufSendToServer,mSendLen);
        break;
    case UPDATE_STATE_MANAGER:
        mBufSendToServer[0] = UPDATE_STATE_MANAGER;
        mSendLen = PutStrToBuf(mStrClientManager,&mBufSendToServer[1]);
        tcpClient->write((char *)mBufSendToServer,mSendLen);
        break;
    case UPDATE_STATE_ALIVE:
        break;
    default:
        m_timerConnect->stop();
    }

}

void CRemoteClient::showEvent(QShowEvent *)
{
    DisplayInfo();

    grabKeyboard();

}

void CRemoteClient::hideEvent(QHideEvent *)
{
    releaseKeyboard();
}

void CRemoteClient::OnUpdateInfo()
{
    //判断文件存在
    if(!QFile::exists("/udisk/estmedcarefirmware/clientinfo/clientinfo.ini"))
        return;

    MySystem("cp -f /udisk/estmedcarefirmware/clientinfo/clientinfo.ini /sdcard/home/fa/clientinfo.ini");

    DisplayInfo();
}

void CRemoteClient::DisplayInfo()
{
    //判断文件存在
    if(!QFile::exists(QCoreApplication::applicationDirPath() +"/clientinfo.ini"))
    {
        pLbMessage->setText(QApplication::translate("CRemoteBase", "Client Configure file not exist!"));
        return;
    }

    QTextCodec *codec = QTextCodec::codecForName("GB18030");
     //codec->toUnicode(encodedString);
    QSettings * configClientInfo = new QSettings(QCoreApplication::applicationDirPath() +"/clientinfo.ini",QSettings::IniFormat);
    mStrServerAddr      = configClientInfo->value("/server/address").toString();
    mStrClientId        = configClientInfo->value("/client/id").toString();
    //mStrClientAgency    = codec->toUnicode(configClientInfo->value("/client/agency").toByteArray());
    QByteArray encodedString = codec->fromUnicode(configClientInfo->value("/client/agency").toByteArray());
    mStrClientAgency    =QString::fromLocal8Bit( configClientInfo->value("/client/agency").toByteArray());
    mStrClientAddr      = QString::fromUtf8(configClientInfo->value("/client/address").toByteArray());
    mStrClientContacts  = QString::fromUtf8(configClientInfo->value("/client/contacts").toByteArray());
    mStrClientPhone     = configClientInfo->value("/client/phnoe").toString();
    mStrClientManager   = QString::fromUtf8(configClientInfo->value("/client/manager").toByteArray());

    pLbServerAddr->setText(mStrServerAddr);
    pLbClientId->setText(mStrClientId);
    pLbOrganization->setText(mStrClientAgency);
    pLbAddress->setText(mStrClientAddr);
    pLbContacts->setText(mStrClientContacts);
    pLbPhone->setText(mStrClientPhone);
    pLbManager->setText(mStrClientManager);
}
