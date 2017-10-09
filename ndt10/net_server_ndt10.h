#ifndef NET_SERVER_NDT10_H
#define NET_SERVER_NDT10_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "./base/net_server_base.h"


class CNetServerNdt10 : public CNetServerBase
{
    Q_OBJECT

public:
    explicit CNetServerNdt10(QWidget *parent = 0);

private:
    QFrame          * mFrame;
    QGraphicsScene  * mScene;
    QGraphicsView   * mView;

protected:
    virtual void OnClientNumberChange(int);
    virtual void OnCtrlChange(int ,int);
    virtual void ProcessNetMessage(unsigned short *);

};

#endif // NET_SERVER_NDT10_H
