#ifndef NET_SERVER_CEIL_12A_H
#define NET_SERVER_CEIL_12A_H

#include "./base12/net_server_base12.h"

#ifdef USE_CEIL_12_A


class CNetServerCeil12a : public CNetServer12
{
    Q_OBJECT

public:
    explicit CNetServerCeil12a(QWidget *parent = 0);

protected:
    //virtual void OnClientNumberChange(int);
    virtual void OnCtrlChange(int ,int);

public slots:
    virtual void OnNetClientCtrl();

};

#endif  //NET_SERVER_CEIL_12A_H
#endif  //USE_CEIL_12_A
