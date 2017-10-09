#ifndef STATUS_MGR_H
#define STATUS_MGR_H

#include "./base/status_base.h"


class CStatusMgr : public QObject
{
    Q_OBJECT
public:
    explicit CStatusMgr();

    CStatusBase * statusInit(int);

private:
    CStatusBase * mStatusBase;
    
};

#endif // STATUS_MGR_H
