#ifndef SIM_BASE12_H
#define SIM_BASE12_H

#include "./base/sim_base.h"

class CSimBase12 : public CSimBase
{
    Q_OBJECT
public:
    explicit CSimBase12(QWidget *parent = 0);

    
public slots:
    virtual void OnSimPressed();
    virtual void OnViewDirChange(int);
};

#endif // SIM_BASE12_H
