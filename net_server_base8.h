#ifndef NET_SERVER_BASE8_H
#define NET_SERVER_BASE8_H

#include "net_server_base.h"


class CNetServerBase8 : public CNetServerBase
{
    Q_OBJECT
    
public:
    explicit CNetServerBase8(QWidget *parent = 0);

protected:
    virtual void OnClientNumberChange(int);
    virtual void OnCtrlChange(int ,int);

public slots:
    virtual void OnNetClientCtrl();

};

#endif // NET_SERVER_BASE8_H
