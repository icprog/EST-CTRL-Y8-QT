#ifndef NET_CLIENT_BASE8_H
#define NET_CLIENT_BASE8_H

#include "./base/net_client_base.h"


class CNetClient8 : public CNetClientBase
{
    Q_OBJECT
    
public:
    explicit CNetClient8(QWidget *parent = 0);
    
public slots:
    virtual void OnClientReadyRead();
    virtual void OnClientDisconnected();

};

#endif // NET_CLIENT_BASE8_H
