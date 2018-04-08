#ifndef NET_CLIENT_CEIL_12A_H
#define NET_CLIENT_CEIL_12A_H


#include "./base12/net_client_base12.h"
#ifdef USE_CEIL_12_A


class CNetClientCeil12a : public CNetClient12
{
    Q_OBJECT

public:
    explicit CNetClientCeil12a(QWidget *parent = 0);

};

#endif  //NET_CLIENT_CEIL_12A_H
#endif  //USE_CEIL_12_A
