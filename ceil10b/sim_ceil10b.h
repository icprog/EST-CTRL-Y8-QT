#ifndef SIM_CEIL10_B_H
#define SIM_CEIL10_B_H

#include "./base10/sim_base10.h"


class CSimCeil10b : public CSimBase10
{
    Q_OBJECT
    
public:
    explicit CSimCeil10b(QWidget *parent = 0);

protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

public slots:
    virtual void OnViewDirChange(int);
};

#endif // SIM_CEIL10_B_H
