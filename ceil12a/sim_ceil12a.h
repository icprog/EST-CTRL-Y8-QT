#ifndef SIM_CEIL_12A_H
#define SIM_CEIL_12A_H

#include "./base12/sim_base12.h"

#ifdef USE_CEIL_12_A


class CSimCeil12a : public CSimBase12
{
    Q_OBJECT

public:
    explicit CSimCeil12a(QWidget *parent = 0);

protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

};

#endif  //SIM_CEIL_12A_H
#endif  //USE_CEIL_12_A
