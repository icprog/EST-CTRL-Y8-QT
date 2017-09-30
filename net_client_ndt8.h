#ifndef NET_CLIENT_NDT8_H
#define NET_CLIENT_NDT8_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "net_client_base8.h"


class CNetClientNdt8 : public CNetClient8
{
    Q_OBJECT

public:
    explicit CNetClientNdt8(QWidget *parent = 0);

public slots:
    virtual void OnClientReadyRead();
};

#endif // NET_CLIENT_NDT8_H
