#ifndef EXIT_MGR_H
#define EXIT_MGR_H

#include "exit_base.h"


class CExitMgr : public QObject
{
    Q_OBJECT
public:
    explicit CExitMgr();

    CExitBase * exitInit(int );

private:
    CExitBase * mPowerBase;
    
};

#endif // EXIT_MGR_H
