#ifndef QUICK_MGR_H
#define QUICK_MGR_H

#include <QObject>

#include "quick_base.h"

class CQuickMgr : public QObject
{
    Q_OBJECT
public:
    explicit CQuickMgr();
    
    CQuickBase * quickInit(int);

private:
    CQuickBase * mQuickBase;

    
};

#endif // QUICK_MGR_H
