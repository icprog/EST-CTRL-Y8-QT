#ifndef NET_CLIENT_BASE_H
#define NET_CLIENT_BASE_H

#include <QWidget>
#include <QTimer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QAbstractSocket>
#include <QMessageBox>

#include "net_base.h"
#include "./system/system_defines.h"
#include "button_stable.h"


class CNetClientBase : public CNetBase
{
    Q_OBJECT
public:
    explicit CNetClientBase(QWidget *parent = 0);
    
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

public:
    CButtonStable *pbCtrlIndex;
    CButtonStable *pbCtrlRequest;

    unsigned short * getBufWrite();     //获取向主机发送信息的缓冲区
    void PublishMessage();              //向主机发送信息

    bool connectStatus;
    bool isConnected();

    QTcpSocket tcpClient;
    QUdpSocket * udpClient;

    void InitNetworkClient();

    unsigned short mTcpBufRead[PKG_DEFAULT_SIZE];
    unsigned short mTcpBufWrite[PKG_DEFAULT_SIZE];

    unsigned short mUdpBufRead[PKG_DEFAULT_SIZE];

    QTimer   *timerReconnect;
    unsigned long m_iAckCounter;

    int m_iFunctionCurrent;
    int m_iClientIdx;

    int m_iTryTimes;

    QString m_IpAddr;

public slots:
    virtual void OnClientReadyRead();
    virtual void OnClientDisconnected();

    void OnConnected();

    virtual void OnReConnect();

    void OnConError ( QAbstractSocket::SocketError socketError );

    void processPendingDatagrams();

    void OnClientCtrlPressed();
    
};

#endif // NET_CLIENT_BASE_H
