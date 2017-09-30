#ifndef NET_SERVER_NDT8_H
#define NET_SERVER_NDT8_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "net_server_base8.h"


class CNetServerNdt8 : public CNetServerBase8
{
    Q_OBJECT

public:
    explicit CNetServerNdt8(QWidget *parent = 0);

protected:
    virtual void OnClientNumberChange(int);
    virtual void OnCtrlChange(int ,int);
    virtual void ProcessNetMessage(unsigned short *);

};

#endif // NET_SERVER_NDT8_H
