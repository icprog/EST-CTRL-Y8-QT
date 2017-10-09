#ifndef NET_SERVER_BASE12_H
#define NET_SERVER_BASE12_H

#include "./base/net_server_base.h"


class CNetServer12 : public CNetServerBase
{
    Q_OBJECT

public:
    explicit CNetServer12(QWidget *parent = 0);

protected:
    virtual void OnClientNumberChange(int);
    virtual void OnCtrlChange(int ,int);

public slots:
    virtual void OnNetClientCtrl();
 virtual void OnViewDirChange(int);
};

#endif // NET_SERVER_BASE12_H
