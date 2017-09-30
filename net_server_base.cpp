#include "net_server_base.h"
#include "resource_manager.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#define HEART_ACK_NORMAL    ( 0 )   /*normal */
#define HEART_ACK_INIT      ( 1 )   /*normal */
#define HEART_ACK_WARNNING  ( 2 )   /*warnning */
#define HEART_ACK_LOST      ( 3 )   /*disable movement*/
#define HEART_ACK_ERROR     ( 4 )   /*init network */

CNetServerBase::CNetServerBase(QWidget *parent) :
    CNetBase(parent)
{

    m_iHeartAckCounter  = 0;
    m_iHeartAckChecker = 0;
    m_iHeartAckState    = HEART_ACK_NORMAL;

    for(int mIdx = 0 ; mIdx < MAX_CLIENT_NUM ; mIdx++)
    {
        tcpSocketClient[mIdx] = -1;
    }
    //timerHeartBeat = new QTimer(this);
    //timerHeartBeat->setInterval(1000);       //每隔500ms检测一次遥控端是否存在
    //connect(timerHeartBeat,SIGNAL(timeout()),this,SLOT(OnTimerHeartBeat()));

    m_iCurrentConnection = 0;      //for connecting
    m_iClientOnLine = 0;           //for data send.

    for(int mIdx = 0 ;mIdx < MAX_CLIENT_NUM ;mIdx++)
    {
        clientFunctionArray[mIdx] = CLIENT_FUNC_READ;
        clientState[mIdx] = QAbstractSocket::ConnectingState;
        tcpClientState[mIdx] = TCP_STATE_EMPTY;
        tcpClientConnection[mIdx] = 0;
    }

    timerBufRead = new QTimer(this);
    timerBufRead->setInterval(50);
    connect(timerBufRead,SIGNAL(timeout()),this,SLOT(OnBufferCheck()));

    m_bSkipRunCheck = false;
    m_iPendingRequest = -1;
    m_iCurrentControl = -1;
    m_bAcceptNewConnect = true;
    m_bStopPublishMsg   = false;

    InitNetworkServer();

    setVisible(false);
}

void CNetServerBase::SendCmdKey(int mKey)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = mKey;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}
void CNetServerBase::showEvent(QShowEvent *)
{
    timerBufRead->start();
    RsMgr->VisibleWidgetAdd(this);
}
void CNetServerBase::hideEvent(QHideEvent *)
{
    timerBufRead->stop();

    RsMgr->VisibleWidgetDel(this);
}
void CNetServerBase::OnClientNumberChange(int )
{
}
void CNetServerBase::OnCtrlChange(int ,int )
{
}
void CNetServerBase::OnViewDirChange(int)
{

}
void CNetServerBase::OnNewConnection()
{
    int mIdx = 0;

    //qDebug() << "OnNewConnection in ";

    while(mIdx < MAX_CLIENT_NUM && tcpServer->hasPendingConnections())
    {
        if( tcpClientState[mIdx] != TCP_STATE_EMPTY )
        {
            mIdx++;
            continue;
        }

        tcpClientConnection[mIdx] = tcpServer->nextPendingConnection();

        //connect(tcpClientConnection[mIdx], SIGNAL(readyRead()),this, SLOT(OnReadyRead()));
        connect(tcpClientConnection[mIdx], SIGNAL(connected()),this, SLOT(OnConnected()));
        connect(tcpClientConnection[mIdx], SIGNAL(disconnected()),this, SLOT(OnDisconnected()));
        connect(tcpClientConnection[mIdx], SIGNAL(stateChanged ( QAbstractSocket::SocketState  )),this, SLOT(OnStateChanged ( QAbstractSocket::SocketState )));
        connect(tcpClientConnection[mIdx], SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(OnError(QAbstractSocket::SocketError)));

        if(tcpClientConnection[mIdx]->waitForConnected(CONNECT_WAIT_TIME))
        {
            tcpClientState[mIdx] = TCP_STATE_USING;
            m_iClientOnLine += 1;
            mTcpBufWrite[0] = MSG_CLIENT_IDX;
            mTcpBufWrite[1] = mIdx;                                //tell the client its number idx
            mTcpBufWrite[2] = CLIENT_FUNC_READ;

            SendMessage(mIdx);

            //qDebug() << "SendMessage mIdx ";
        }

        m_iCurrentConnection++;

        OnClientNumberChange(m_iCurrentConnection);
    }
}
void CNetServerBase::InitNetworkServer()
{

    //qDebug() << "InitNetworkServer in ";

    udpBroadCast = new QUdpSocket(this);

    tcpSocketServer = socket(AF_INET,SOCK_STREAM,0);

    if(tcpSocketServer == -1)
    {
        emit InfoMsgCtrl(INFO_CTRL_ADD, MSG_NET_START_FAIL);
        return;
    }

    //qDebug() << "tcpSocketServer ok ";

    HostAddr.sin_family=AF_INET;
    HostAddr.sin_port=htons(12801);
    HostAddr.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(tcpSocketServer,(struct sockaddr *)& HostAddr,sizeof(struct sockaddr))<0)
    {
        emit InfoMsgCtrl(INFO_CTRL_ADD, MSG_NET_START_FAIL);
        return;
    }

    //qDebug() << "tcpSocketServer bind ok ";

    if( listen(tcpSocketServer,MAX_CLIENT_NUM) < 0 )
    {
        emit InfoMsgCtrl(INFO_CTRL_ADD, MSG_NET_START_FAIL);
        return;
    }

    //qDebug() << "tcpSocketServer listen ok ";

    fcntl( tcpSocketServer, F_SETFL, O_NONBLOCK);

    tcpServer = new QTcpServer(this);

    //connect(tcpServer,SIGNAL(newConnection()),this,SLOT(OnNewConnection()));
    connect(this->tcpServer,SIGNAL(newConnection()),this,SLOT(OnNewConnection()));
    tcpServer->setMaxPendingConnections(MAX_CLIENT_NUM);

    if(!tcpServer->isListening())
    {
        if(!tcpServer->listen(QHostAddress::Any,TCP_SERVER_PORT))
        {
            emit InfoMsgCtrl(INFO_CTRL_ADD, MSG_NET_START_FAIL);
            //qDebug() << "InitNetworkServer error ";
        }
        //qDebug() << "isListening start! ";
    }

    //connect(tcpServer,SIGNAL(newConnection()),this,SLOT(OnNewConnection()));

    //qDebug() << "InitNetworkServer out ";
}
void CNetServerBase::OnBufferCheck()
{

    //if(m_iClientOnLine <= 0)                //没有用户在线，不广播数据
    if(m_iClientOnLine <= MAX_CLIENT_NUM)                //没有用户在线，不广播数据，测试多点连接
    {
        socklen_t sin_size = sizeof(struct sockaddr);
        int mIdx;

        for( mIdx= 0 ; mIdx < MAX_CLIENT_NUM ; mIdx++)
        {
            if(tcpSocketClient[mIdx] == -1)
            {
                tcpSocketClient[mIdx] = accept(tcpSocketServer,(sockaddr *)&ClientAddr,&sin_size);
                break;
            }
        }

        if(tcpSocketClient[mIdx] > 0)
        {
            m_iClientOnLine += 1;

            tcpClientState[0] = TCP_STATE_USING;

            mTcpBufWrite[0] = MSG_CLIENT_IDX;
            //mTcpBufWrite[1] = 0;                                //tell the client its number idx
            mTcpBufWrite[1] = mIdx;                                //tell the client its number idx
            mTcpBufWrite[2] = CLIENT_FUNC_READ;

            send(tcpSocketClient[mIdx],(char *)mTcpBufWrite,PKG_DEFAULT_SIZE,MSG_DONTWAIT | MSG_DONTROUTE);

            OnClientNumberChange(m_iClientOnLine);
        }
    }

    OnReadyRead();

}
void CNetServerBase::OnReadyRead()
{
    int isPackageValid = false;

    for( int mIdx= 0 ; mIdx < MAX_CLIENT_NUM ; mIdx++)
    {
        if(tcpSocketClient[mIdx] == -1)
            continue;

        int bufSize = recv(tcpSocketClient[mIdx],(char *) mTcpBufRead, PKG_DEFAULT_SIZE,MSG_DONTWAIT);

        if(bufSize == 0)
        {
            //qDebug()<< "Client closed.";
            ::close(tcpSocketClient[mIdx]);
            tcpSocketClient[mIdx] = -1;
            m_iClientOnLine -= 1;
            m_iCurrentControl = -1;
            clientFunctionArray[0] = CLIENT_FUNC_NULL;
            OnClientNumberChange(m_iClientOnLine);
        }

        if(bufSize == -1 || bufSize < PKG_DEFAULT_SIZE)
        {
            continue;
        }

        m_iCurrentTcpSender = mTcpBufRead[1];
        isPackageValid = true;
        //for NDT only
        //ProcessNetMessage(mTcpBufRead);
        if(m_bSkipRunCheck)
        {
            ProcessNetMessage(mTcpBufRead);
            return;
        }
    }

    if(!isPackageValid)
        return;

    if(FunctionControl())
        return;

    if(clientFunctionArray[0] == CLIENT_FUNC_RUN)
    {
        ProcessNetMessage(mTcpBufRead);
        return;
    }

    if(clientFunctionArray[0] == CLIENT_FUNC_READ)
    {
        return;
    }

    if(clientFunctionArray[0] == CLIENT_FUNC_SET)
    {
        return;
    }

}
bool CNetServerBase::FunctionControl()
{
    if(mTcpBufRead[CMD_FUNC_ADDR] == MSG_CTRL_REQUEST )
    {
        if(!m_bAcceptNewConnect)
        {
            mTcpBufWrite[0] = MSG_CTRL_LIMIT;

            SendMessage(mTcpBufRead[1]);
            return true;
        }

        if(m_iPendingRequest >= 0)
        {
            mTcpBufWrite[0] = MSG_CTRL_COLLISION;

            SendMessage(mTcpBufRead[1]);
            return true;
        }

        if(mTcpBufRead[2] == CLIENT_FUNC_RUN )
        {
            if(m_iCurrentTcpSender > MAX_CLIENT_NUM)
                return false;

            if(clientFunctionArray[m_iCurrentTcpSender] == CLIENT_FUNC_RUN)
            {
                mTcpBufWrite[0] = MSG_CTRL_REQUEST;
                mTcpBufWrite[1] = m_iCurrentTcpSender;
                mTcpBufWrite[2] = CLIENT_FUNC_READ;

                clientFunctionArray[m_iCurrentTcpSender] = CLIENT_FUNC_READ;
                SendMessage(m_iCurrentTcpSender);
            }else if(m_iCurrentControl != -1)
            {
                mTcpBufWrite[0] = MSG_CTRL_BUSY;
                mTcpBufWrite[3] = m_iCurrentControl;
                SendMessage(m_iCurrentTcpSender);
            }else
            {
                m_iPendingRequest = m_iCurrentTcpSender;
                m_bStopPublishMsg = true;
                emit PopupShow( SYS_POPUP_REQUEST );
            }
            return true;
        }

        if(mTcpBufRead[2] == CLIENT_FUNC_READ)
        {
            mTcpBufWrite[0] = MSG_CTRL_REQUEST;
            mTcpBufWrite[1] = mTcpBufRead[1];
            mTcpBufWrite[2] = CLIENT_FUNC_READ;

            clientFunctionArray[mTcpBufRead[1]] = CLIENT_FUNC_READ;
            SendMessage(mTcpBufRead[1]);
            //send(tcpSocketClient,(char *)mTcpBufWrite,PKG_DEFAULT_SIZE,MSG_DONTWAIT | MSG_DONTROUTE);

            if(m_iCurrentControl ==  mTcpBufRead[1])
                m_iCurrentControl = -1;

            OnCtrlChange(-1,CLIENT_FUNC_READ);
        }
        if(mTcpBufRead[2] == CLIENT_FUNC_SET)
        {
            mTcpBufWrite[0] = MSG_CTRL_REQUEST;
            mTcpBufWrite[1] = mTcpBufRead[1];
            mTcpBufWrite[2] = CLIENT_FUNC_SET;
            SendMessage(mTcpBufRead[1]);

            if(m_iCurrentControl ==  mTcpBufRead[1])
                m_iCurrentControl = -1;

            return true;
        }
        return true;
    }

    return false;
}

int CNetServerBase::GetPendingRequest()
{
    return m_iPendingRequest;
}
void CNetServerBase::OnClientAck(int ack)
{
    switch(ack)
    {
    case CLIENT_ACK_REJECT:
    case CLIENT_ACK_TIMEOUT:
        mTcpBufWrite[0] = MSG_CTRL_REJECT;
        mTcpBufWrite[1] = m_iPendingRequest;
        mTcpBufWrite[2] = CLIENT_FUNC_READ;
        SendMessage(m_iPendingRequest);

        m_iPendingRequest = -1;

        m_bStopPublishMsg = false;
        break;
    case CLIENT_ACK_ACCEPT:
        clientFunctionArray[m_iPendingRequest] = CLIENT_FUNC_RUN;

        OnCtrlChange(m_iPendingRequest,CLIENT_FUNC_RUN);

        mTcpBufWrite[0] = MSG_CTRL_REQUEST;
        mTcpBufWrite[1] = m_iPendingRequest;
        mTcpBufWrite[2] = CLIENT_FUNC_RUN;
        SendMessage(m_iPendingRequest);

        //send(tcpSocketClient,(char *)mTcpBufWrite,PKG_DEFAULT_SIZE,MSG_DONTWAIT | MSG_DONTROUTE);

        m_iCurrentControl = m_iPendingRequest;
        m_iPendingRequest = -1;

        m_bStopPublishMsg = false;
        m_iHeartAckChecker = m_iHeartAckCounter;
        //timerHeartBeat->start();
        break;
    default:
        break;
    }
    return;
}


void CNetServerBase::ProcessNetMessage(unsigned short * pCmdBuf)
{
    unsigned short m_buf[2];

    switch(pCmdBuf[CMD_FUNC_ADDR])
    {
    case CMD_FUNC_SMART:
        emit SmartChange(pCmdBuf[FUNC_WKEY_ADDR]);
        break;
    case CMD_FUNC_WKEY:
        if(m_iHeartAckState > HEART_ACK_LOST)
            break;

        m_buf[0] = 0;
        m_buf[1] = pCmdBuf[FUNC_WKEY_ADDR];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,m_buf,2);

        break;
    case CMD_FUNC_COMMD:
        break;
    case CMD_FUNC_PARAM:
        break;
    case CMD_FUNC_MOTO:
        break;
    case CMD_FUNC_REBOOT:
        RsMgr->g_filmBase->SetLCD(false);
        MySystem("reboot");
        break;
    case MSG_CTRL_HEARTBEAT:
        m_iHeartAckCounter++;
        m_iHeartAckChecker = m_iHeartAckCounter;
        break;
    default:
        break;
    }
}

unsigned short * CNetServerBase::getUdpBufferRead()
{
    return mUdpBufRead;
}
unsigned short * CNetServerBase::getUdpBufferWrite()
{
    return mUdpBufWrite;
}
unsigned short * CNetServerBase::getTcpBufferRead()
{
    return mTcpBufRead;

}
unsigned short * CNetServerBase::getTcpBufferWrite()
{
    return mTcpBufWrite;
}
void CNetServerBase::SendMessage(int iClient)
{
    if(iClient >= MAX_CLIENT_NUM )
        return;

    for(int mIdx = 0 ; mIdx < MAX_CLIENT_NUM ; mIdx++)
    {
        if(tcpSocketClient[mIdx] <= 0)
            continue;

        send(tcpSocketClient[mIdx],(char *)mTcpBufWrite,PKG_DEFAULT_SIZE,MSG_DONTWAIT | MSG_DONTROUTE);
    }
    //  if((tcpClientConnection[iClient])->state() == QAbstractSocket::ConnectedState)
    //    {
    //        (tcpClientConnection[iClient])->write((char *)mTcpBufWrite,PKG_DEFAULT_SIZE);
    //    }
}
//将收到的数据通过UDP协议发送给所有在线的遥控器
void CNetServerBase::BroadcastMsg()
{
    // if(m_iClientOnLine <= 0)                //没有用户在线，不广播数据
    //    return;

    udpBroadCast->writeDatagram((const char *)mUdpBufWrite,PKG_DEFAULT_SIZE,
                                QHostAddress::Broadcast, UDP_CLIENT_PORT);

}
void CNetServerBase::tcpSendMsg()
{
    if(m_bStopPublishMsg)
        return;

    switch(mTcpBufWrite[CMD_FUNC_ADDR])
    {
    case CMD_FUNC_DEBUG:

        break;
    case CMD_FUNC_STATE:

        break;
    default:
        break;
    }

    for(int mIdx = 0 ; mIdx < m_iClientOnLine ;mIdx++)
    {
        if((tcpClientConnection[mIdx])->state() == QAbstractSocket::ConnectedState)
        {
            (tcpClientConnection[mIdx])->write((char *)mTcpBufWrite,PKG_DEFAULT_SIZE);
        }
    }
}
void CNetServerBase::OnDisconnected()
{
    int mClientPos = -1;

    for(int mIdx = 0 ;mIdx < MAX_CLIENT_NUM ;mIdx++)
    {
        if((QObject*)tcpClientConnection[mIdx] == sender())
        {
            mClientPos = mIdx;
            break;
        }
    }

    if(mClientPos == -1)
        return;

    tcpClientState[mClientPos] = TCP_STATE_EMPTY;
    clientState[mClientPos] = QAbstractSocket::ConnectingState;
    clientFunctionArray[mClientPos] = CLIENT_FUNC_NULL;
    tcpClientConnection[mClientPos] = 0;

    if(m_iCurrentControl == mClientPos)
    {
        m_iCurrentControl = -1;
        OnCtrlChange(m_iCurrentControl,CLIENT_FUNC_READ);
    }
    m_iCurrentConnection -= 1;
    m_iClientOnLine      -= 1;

    OnClientNumberChange(m_iCurrentConnection);

}
void CNetServerBase::OnConnected()
{
    int mClientPos = -1;

    for(int mIdx = 0 ;mIdx < MAX_CLIENT_NUM ;mIdx++)
    {
        if((QObject*)tcpClientConnection[mIdx] == sender())
        {
            mClientPos = mIdx;
            break;
        }
    }

    if(mClientPos == -1)
        return;

    clientState[mClientPos] = QAbstractSocket::ConnectedState;
    m_iClientOnLine +=1;

}
bool CNetServerBase::isConnected()
{
    for(int mIdx = 0 ;mIdx < MAX_CLIENT_NUM ;mIdx++)
    {
        if(clientState[mIdx] == true)
            return true;
    }
    return false;
}

void CNetServerBase::OnNetClientRemote()
{
    if(m_bAcceptNewConnect)
    {
        //timerHeartBeat->stop();
        ClearInfoMsg();
        m_bAcceptNewConnect = false;
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));
    }else
    {
        //timerHeartBeat->start();
        m_bAcceptNewConnect = true;
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));
    }
}

void CNetServerBase::OnNetClientCtrl()
{

    if(m_iCurrentControl >= 0)
    {
        mTcpBufWrite[0] = MSG_CTRL_REQUEST;
        mTcpBufWrite[1] = m_iCurrentControl;
        mTcpBufWrite[2] = CLIENT_FUNC_READ;

        clientFunctionArray[m_iCurrentControl] = CLIENT_FUNC_READ;
        SendMessage(m_iCurrentControl);

        m_iCurrentControl = -1;
        OnCtrlChange(-1,CLIENT_FUNC_READ);
    }

}
void CNetServerBase::ClearInfoMsg()
{
    emit InfoMsgCtrl(INFO_CTRL_DEL , MSG_NET_SIGNAL_WARN);

    emit InfoMsgCtrl(INFO_CTRL_DEL , MSG_NET_REMOTE_LOST);

    emit InfoMsgCtrl(INFO_CTRL_DEL , MSG_NET_RESTART);

}
//每秒钟判断一次，遥控端是否存在
//连续2个单位，收不到遥控端信号，则发送警告信息，提示用户网络信号不佳
//连续3个单位，收不到遥控端信号，则认为遥控端丢失，取消由遥控端发出的命令
//连续4个单位，收不到遥控端信号，则认为网络错误，重新初始化网络模块
void CNetServerBase::OnTimerHeartBeat()
{
    if(m_iCurrentControl < 0)       //没有任何远程控制端
    {
        ClearInfoMsg();
        return;
    }

    if(clientFunctionArray[m_iCurrentControl] != CLIENT_FUNC_RUN)
    {
        ClearInfoMsg();
        return;                     //如果不处于遥控状态，则不进行心跳检测
    }

    m_iHeartAckChecker++;
    int mAckLevel = m_iHeartAckChecker - m_iHeartAckCounter;

    unsigned short buf[10];
    buf[0]=0;

    switch(mAckLevel)
    {
    case HEART_ACK_INIT:
        ClearInfoMsg();
        break;
    case HEART_ACK_WARNNING:
        emit InfoMsgCtrl(INFO_CTRL_ADD , MSG_NET_SIGNAL_WARN);
        m_iHeartAckState = HEART_ACK_WARNNING;
        break;
    case HEART_ACK_LOST:
        emit InfoMsgCtrl(INFO_CTRL_ADD , MSG_NET_REMOTE_LOST);
        m_iHeartAckState = HEART_ACK_LOST;
        buf[1]=SYS_CMD_SETTING;
        g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);
        buf[1]=SYS_CMD_NORMAL;
        g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);
        break;
    case HEART_ACK_ERROR:
        emit InfoMsgCtrl(INFO_CTRL_ADD , MSG_NET_RESTART);
        m_iHeartAckState = HEART_ACK_ERROR;
        OnNetClientCtrl();
        break;
    default:
        break;
    }

}
void CNetServerBase::OnStateChanged ( QAbstractSocket::SocketState socketState )
{
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        fprintf(stderr, "The socket is not connected.\n");
        break;
    case QAbstractSocket::HostLookupState:
        fprintf(stderr, "The socket is performing a host name lookup.\n");
        break;
    case QAbstractSocket::ConnectingState:
        fprintf(stderr, "The socket has started establishing a connection.\n");
        break;
    case QAbstractSocket::ConnectedState:
        fprintf(stderr, "A connection is established.\n");
        break;
    case  QAbstractSocket::BoundState:
        fprintf(stderr, "The socket is bound to an address and port (for servers).\n");
        break;
    case QAbstractSocket::ClosingState:
        fprintf(stderr, "The socket is about to close (data may still be waiting to be written).\n");
        break;
    case QAbstractSocket::ListeningState:
        fprintf(stderr, "For internal use only.\n");
        break;
    }

}
void CNetServerBase::OnError(QAbstractSocket::SocketError err)
{
    switch(err)
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

