#ifndef NET_MGR_H
#define NET_MGR_H

#include <QWidget>


class CNetMgr : public QObject
{
    Q_OBJECT
public:
    explicit CNetMgr();
    
    void netWorkInit(int);
    
};

#endif // NET_MGR_H
