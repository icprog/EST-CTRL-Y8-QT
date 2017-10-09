#ifndef NET_CLIENT_BASE12_H
#define NET_CLIENT_BASE12_H

#include "./base/net_client_base.h"


class CNetClient12 : public CNetClientBase
{
    Q_OBJECT

public:
    explicit CNetClient12(QWidget *parent = 0);

public slots:
    virtual void OnClientReadyRead();
    virtual void OnClientDisconnected();
    virtual void OnViewDirChange(int);

    virtual void OnReConnect();
};

#endif // NET_CLIENT_BASE12_H
