#ifndef SMART_MGR_H
#define SMART_MGR_H

#include "./base/smart_base.h"


class CSmartMgr : public QObject
{
    Q_OBJECT
public:
    explicit CSmartMgr();

    CSmartBase * smartInit(int);

private:
    CSmartBase * mSmartBase;

    
};

#endif // SMART_MGR_H
