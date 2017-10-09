#ifndef NET_SERVER_BASE_H
#define NET_SERVER_BASE_H

#include <QWidget>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QAbstractSocket>
#include <sys/socket.h>
#include <netinet/in.h>

#include "net_base.h"
#include "./system/system_defines.h"
#include "button_stable.h"


class CNetServerBase : public CNetBase
{
    Q_OBJECT
public:
    explicit CNetServerBase(QWidget *parent = 0);
    
    CButtonStable *pbCtrl;
    CButtonStable *pbRemote;

    void InitNetworkServer();
    virtual void BroadcastMsg();            //广播消息，向遥控端
    void tcpSendMsg();

    unsigned short * getUdpBufferRead();
    unsigned short * getUdpBufferWrite();       //获取向遥控端发送数据的缓冲区

    unsigned short * getTcpBufferRead();
    unsigned short * getTcpBufferWrite();

    bool isConnected();
    virtual int GetPendingRequest();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

protected:
    QUdpSocket     * udpBroadCast;

    int tcpSocketServer;
    int tcpSocketClient[MAX_CLIENT_NUM];
    struct sockaddr_in HostAddr;
    struct sockaddr_in ClientAddr;

    QTcpServer     * tcpServer;                                   //服务器套接字
    QTcpSocket     * tcpClientConnection[MAX_CLIENT_NUM];       //连接后服务器返回的套接字
    int              tcpClientState[MAX_CLIENT_NUM];

    int             m_iCurrentTcpSender;
    int            clientFunctionArray[MAX_CLIENT_NUM];
    int            m_iPendingRequest;

    QAbstractSocket::SocketState clientState[MAX_CLIENT_NUM];

    unsigned short mUdpBufRead[PKG_DEFAULT_SIZE];
    unsigned short mUdpBufWrite[PKG_DEFAULT_SIZE];

    unsigned short mTcpBufRead[PKG_DEFAULT_SIZE];
    unsigned short mTcpBufWrite[PKG_DEFAULT_SIZE];

    int m_iCurrentConnection;
    int m_iCurrentControl;                  //当前具有控制权限的客户端
    int m_iClientOnLine;

    int m_bAcceptNewConnect;

    int m_bStopPublishMsg;

    int m_bSkipRunCheck;

    int m_iHeartAckState;       //心跳状态
    unsigned long m_iHeartAckCounter;     //心跳计数器，每次心跳会自动加1
    unsigned long m_iHeartAckChecker;         //心跳计数器缓冲，每次成功收到心跳，则将缓冲重新赋值
    //QTimer * timerHeartBeat;
    QTimer * timerBufRead;                  //轮询缓冲区

    virtual void ProcessNetMessage(unsigned short *);
    void SendMessage(int iClient);

    bool FunctionControl();

    virtual void OnClientNumberChange(int);
    virtual void OnCtrlChange(int ,int);

    void SendCmdKey(int);               //发送给下位机的命令

    void ClearInfoMsg();

private slots:
    virtual void OnNetClientCtrl();
    virtual void OnNetClientRemote();

    void OnTimerHeartBeat();

    virtual void OnReadyRead();
    void OnDisconnected();
    void OnConnected();
    void OnBufferCheck();

public slots:
    void OnNewConnection();

    void OnClientAck( int);
    void OnViewDirChange(int);

    void OnError(QAbstractSocket::SocketError err);
    void OnStateChanged ( QAbstractSocket::SocketState socketState );

};

#endif // NET_SERVER_BASE_H
