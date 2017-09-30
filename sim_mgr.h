#ifndef SIM_MGR_H
#define SIM_MGR_H

#include "sim_base.h"


class CSimMgr : public QObject
{
    Q_OBJECT
public:
    explicit CSimMgr();

    CSimBase * simInit(int);

private:

     CSimBase * mSimBase;

};

#endif // SIM_MGR_H
