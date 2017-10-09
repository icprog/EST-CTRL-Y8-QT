#ifndef NET_CLIENT_NDT10_H
#define NET_CLIENT_NDT10_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "./base10/net_client_base10.h"


class CNetClientNdt10 : public CNetClient10
{
    Q_OBJECT

public:
    explicit CNetClientNdt10(QWidget *parent = 0);

private:
    QFrame          * mFrame;
    QGraphicsScene  * mScene;
    QGraphicsView   * mView;

};

#endif // NET_CLIENT_NDT10_H
