#include "net_client_base.h"
#include "resource_manager.h"
#include <QTest>

CNetClientBase::CNetClientBase(QWidget *parent) :
    CNetBase(parent)
{

    udpClient = new QUdpSocket(this);
    udpClient->bind(UDP_CLIENT_PORT, QUdpSocket::ShareAddress);
    connect(udpClient, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    connectStatus = false;

    timerReconnect = new QTimer(this);
    connect(timerReconnect, SIGNAL(timeout()),this,SLOT(OnReConnect()));
    timerReconnect->setInterval(NET_RE_CONNECT_TIME);

    m_iFunctionCurrent = CLIENT_FUNC_NULL;
    m_iClientIdx = -1;
    m_iTryTimes = 0;

    //arm linux ip config file
    QFile fileNetCfg("/etc/eth0-setting");

    if(fileNetCfg.open(QFile::ReadOnly))
    {
        //for arm linux
        QTextStream tfile(&fileNetCfg);

        QString mBuf;
        mBuf = tfile.readLine(128);
        m_IpAddr = mBuf.remove(0,3);

        fileNetCfg.close();
    }else
    {
        m_IpAddr ="169.254.1.80";
    }

    setVisible(false);
}

//读取解析服务器发送过来的消息
void CNetClientBase::processPendingDatagrams()
{
    int mDatSize;

    while (udpClient->hasPendingDatagrams())
    {
        mDatSize = udpClient->readDatagram((char *)mUdpBufRead, PKG_DEFAULT_SIZE);

        if(mDatSize < PKG_DEFAULT_SIZE)
            continue;

        switch(mUdpBufRead[CMD_FUNC_ADDR])
        {
        case CMD_FUNC_DEBUG:
            for(int i=0;i<20;i++)
            {
                g_systemDb->g_dbMachine.CurrentData[i]=mUdpBufRead[1 + i];
            }
            break;
        case CMD_FUNC_STATE:
            for(int i=0;i<8;i++)
            {
                g_systemDb->g_dbMachine.StateData[i]= mUdpBufRead[1 + i];
            }
            break;
        case CMD_FUNC_PARAM:
            for(int i = 0 ; i < SYS_POSI_DATA_LEN ; i++)
            {
                g_systemDb->g_dbMachine.PosiData[i]= mUdpBufRead[1 + i];
            }
            break;
        case CMD_NDT_STATE:
            for(int mIdx = 0 ; mIdx < SYS_NDT_STATE_PAR_LEN ; mIdx++)
            {
                g_systemDb->g_iArrNdtState[mIdx]=mUdpBufRead[1 + mIdx];
            }
            g_systemDb->g_ctrNdtStateMsg += 1;
            break;
        case NET_CMD_KEY_PAGE:
            emit RemotePageChange(mUdpBufRead[FUNC_WKEY_ADDR]);
            RsMgr->g_filmBase->SetKeySound();
            break;
        default:
            break;
        }
    }
}

//重新连接
void CNetClientBase::OnReConnect()
{

    if(!connectStatus)
    {
        tcpClient.abort();
        tcpClient.connectToHost(m_IpAddr,TCP_SERVER_PORT);

        if(m_iTryTimes == 0)
            pbCtrlRequest->setText(QApplication::translate("CNetClientBase", "Trying\n." ));

        if(m_iTryTimes == 1)
            pbCtrlRequest->setText(QApplication::translate("CNetClientBase", "Trying\n.." ));

        if(m_iTryTimes == 2)
            pbCtrlRequest->setText(QApplication::translate("CNetClientBase", "Trying\n..." ));

        m_iTryTimes++;
        if(m_iTryTimes > 2)
            m_iTryTimes = 0;

    }else
    {
        timerReconnect->stop();
    }
}
//初始化网络
void CNetClientBase::InitNetworkClient()
{

    connect(&tcpClient,SIGNAL(connected()),this,SLOT(OnConnected()));
    connect(&tcpClient,SIGNAL(disconnected()),this,SLOT(OnClientDisconnected()));
    connect(&tcpClient,SIGNAL(readyRead()),this,SLOT(OnClientReadyRead()));
    connect(&tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(OnConError(QAbstractSocket::SocketError)));

    tcpClient.connectToHost(m_IpAddr,TCP_SERVER_PORT);

}

//错误消息打印
void CNetClientBase::OnConError ( QAbstractSocket::SocketError socketError )
{

    switch(socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:
        fprintf(stderr, "QAbstractSocket::ConnectionRefusedError.\n");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        fprintf(stderr, "QAbstractSocket::RemoteHostClosedError.\n");
        break;
    case QAbstractSocket::HostNotFoundError:
        fprintf(stderr, "QAbstractSocket::HostNotFoundError.\n");
        break;
    case QAbstractSocket::SocketAccessError:
        fprintf(stderr, "QAbstractSocket::SocketAccessError.\n");
        break;
    case QAbstractSocket::SocketResourceError:
        fprintf(stderr, "QAbstractSocket::SocketResourceError.\n");
        break;
    case QAbstractSocket::SocketTimeoutError:
        fprintf(stderr, "QAbstractSocket::SocketTimeoutError.\n");
        break;
    case QAbstractSocket::DatagramTooLargeError:
        fprintf(stderr, "QAbstractSocket::DatagramTooLargeError.\n");
        break;
    case QAbstractSocket::NetworkError:
        fprintf(stderr, "QAbstractSocket::NetworkError.\n");
        break;
    case QAbstractSocket::AddressInUseError:
        fprintf(stderr, "QAbstractSocket::AddressInUseError.\n");
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        fprintf(stderr, "QAbstractSocket::SocketAddressNotAvailableError.\n");
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        fprintf(stderr, "QAbstractSocket::UnsupportedSocketOperationError.\n");
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        fprintf(stderr, "QAbstractSocket::ProxyAuthenticationRequiredError.\n");
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        fprintf(stderr, "QAbstractSocket::SslHandshakeFailedError.\n");
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        fprintf(stderr, "QAbstractSocket::UnfinishedSocketOperationError.\n");
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        fprintf(stderr, "QAbstractSocket::ProxyConnectionRefusedError.\n");
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        fprintf(stderr, "QAbstractSocket::ProxyConnectionClosedError.\n");
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        fprintf(stderr, "QAbstractSocket::ProxyConnectionTimeoutError.\n");
        break;
    case  QAbstractSocket::ProxyNotFoundError:
        fprintf(stderr, "QAbstractSocket::ProxyNotFoundError.\n");
        break;
    case QAbstractSocket::ProxyProtocolError:
        fprintf(stderr, "QAbstractSocket::ProxyProtocolError.\n");
        break;
    case QAbstractSocket::UnknownSocketError:
    default:
        fprintf(stderr, "QAbstractSocket::UnknownSocketError.\n");
        break;
    }
}

void CNetClientBase::OnClientReadyRead()
{
    QString mStrIdx,mStrInfo;

    if(tcpClient.state() != QAbstractSocket::ConnectedState)
        return;

    int mDatLen = tcpClient.read((char *)mTcpBufRead,PKG_DEFAULT_SIZE);

    if(mDatLen <PKG_DEFAULT_SIZE )
        return;

    switch(mTcpBufRead[CMD_FUNC_ADDR])
    {
    case CMD_FUNC_DEBUG:
        for(int i=0;i<20;i++)
        {
            g_systemDb->g_dbMachine.CurrentData[i]=mTcpBufRead[1 + i];
        }
        break;
    case CMD_FUNC_STATE:
        for(int i=0;i<8;i++)
        {
            g_systemDb->g_dbMachine.StateData[i]= mTcpBufRead[1 + i];
        }
        break;
    case MSG_CLIENT_IDX:
        m_iClientIdx = mTcpBufRead[1];
        mStrIdx.setNum(m_iClientIdx);
        mStrInfo = QApplication::translate("CNetClientBase","Index:");
        mStrInfo += "\n";
        mStrInfo += mStrIdx;
        pbCtrlIndex->setText(mStrInfo);
        pbCtrlIndex->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));

        m_iFunctionCurrent = mTcpBufRead[2];
        if(m_iFunctionCurrent == CLIENT_FUNC_READ)
        {
            mStrInfo = "Mode:\nView";
        }else if(m_iFunctionCurrent == CLIENT_FUNC_RUN)
        {
            mStrInfo = "Mode:\nRun";
        }else if(m_iFunctionCurrent == CLIENT_FUNC_SET)
        {
            mStrInfo = "Mode:\nSetting";
        }
        pbCtrlRequest->setText(QApplication::translate("CNetClientBase",mStrInfo.toUtf8() ));
        pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));

        mStrInfo = "Connect to server successfully！\n";
        mStrInfo += "Client Index:";
        mStrInfo += mStrIdx;
        mStrInfo += "\n";
        mStrInfo += "Click the 'mode' button to change working mode!";

        //QMessageBox::information(0,"System Information!",mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_REQUEST:
        m_iFunctionCurrent = mTcpBufRead[2];
        if(m_iFunctionCurrent == CLIENT_FUNC_READ)
        {
            mStrInfo = "Mode:\nView";
        }else if(m_iFunctionCurrent == CLIENT_FUNC_RUN)
        {
            mStrInfo += "Mode:\nRun";
        }else if(m_iFunctionCurrent == CLIENT_FUNC_SET)
        {
            mStrInfo += "Mode:\nSetting";
        }
        pbCtrlRequest->setText(QApplication::translate("CNetClientBase",mStrInfo.toUtf8() ));
        break;
    case MSG_CTRL_BUSY:
        mStrIdx.setNum(mTcpBufRead[3]);
        mStrInfo = "Server is controled by another controler！\n";
        mStrInfo += "Controler Index:";
        mStrInfo += mStrIdx;
        mStrInfo += "\n";
        mStrInfo += "Click 'Remote' button on the system can release current Controler!";

        //   QMessageBox::information(0,"System Information!",mStrInfo,QMessageBox::Yes);
        break;

    case MSG_CTRL_LIMIT:
        mStrInfo = "The server disable any remote!\n";
        mStrInfo += "Please tye remote control after open the remote control function!\n";
        mStrInfo += "Click the remote button on the machine can open remote control function!";
        //    QMessageBox::information(0,"System Information!",mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_COLLISION:
        mStrInfo = "The server is connecting!\n";
        mStrInfo += "Please wait for the end of current connecting!\n";
        //   QMessageBox::information(0,"System Information!",mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_REJECT:
        mStrInfo = "Your request was rejected!\n";
        mStrInfo += "OR the connection request timeout, please try again!\n";
        //   QMessageBox::information(0,"System Information!",mStrInfo,QMessageBox::Yes);
        break;

    default:
        break;
    }

}

unsigned short * CNetClientBase::getBufWrite()
{
    return mTcpBufWrite;
}
//发送消息到网络
void CNetClientBase::PublishMessage()
{
    switch(mTcpBufWrite[CMD_FUNC_ADDR])
    {
    case CMD_FUNC_COMMD:
        break;
    case CMD_FUNC_PARAM:
        break;
    case CMD_FUNC_MOTO:
        break;
    case CMD_FUNC_WKEY:
        break;
    case CMD_FUNC_REBOOT:
        break;
    default:
        break;

    }

    if(connectStatus)
        tcpClient.write((char *)mTcpBufWrite,PKG_DEFAULT_SIZE);

    QTest::qSleep(100);         //增加延时，防止Pad，手机等遥控端发送键码过快
}
//连接断开
void CNetClientBase::OnClientDisconnected()
{
    connectStatus = false;
    timerReconnect->start();

    pbCtrlIndex->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));
    pbCtrlIndex->setText(QApplication::translate("CNetClientBase","Comm\nFail" ));

    pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));
    pbCtrlRequest->setText(QApplication::translate("CNetClientBase","Trying\n...." ));
}
//连接成功
void CNetClientBase::OnConnected()
{
    connectStatus = true;
}
//连接状态
bool CNetClientBase::isConnected()
{
    return connectStatus;
}
//显示
void CNetClientBase::showEvent(QShowEvent *)
{
    InitNetworkClient();
    timerReconnect->start();
    RsMgr->VisibleWidgetAdd(this);
}
void CNetClientBase::hideEvent(QHideEvent *)
{
    timerReconnect->stop();
    RsMgr->VisibleWidgetDel(this);
}
void CNetClientBase::OnClientCtrlPressed()
{

    qDebug() << "CNetClientBase pressed.";

    if(sender() == pbCtrlIndex)
    {
        return;
    }

    if(sender() == pbCtrlRequest)
    {
        int  mCtrlNew;

        mCtrlNew = m_iFunctionCurrent;
        mCtrlNew += 1;

        if((mCtrlNew < CLIENT_FUNC_NULL) || (mCtrlNew > CLIENT_FUNC_RUN) )
            mCtrlNew = CLIENT_FUNC_READ;

        mTcpBufWrite[0] = MSG_CTRL_REQUEST;
        mTcpBufWrite[1] = m_iClientIdx ;
        mTcpBufWrite[2] = mCtrlNew;

        PublishMessage();
    }
}
