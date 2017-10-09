#ifndef NET_SERVER_BASE10_H
#define NET_SERVER_BASE10_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "./base/net_server_base.h"


class CNetServer10 : public CNetServerBase
{
    Q_OBJECT

public:
    explicit CNetServer10(QWidget *parent = 0);

protected:
    virtual void OnClientNumberChange(int);
    virtual void OnCtrlChange(int ,int);

public slots:
    virtual void OnViewDirChange(int);
};

#endif // NET_SERVER_BASE10_H
