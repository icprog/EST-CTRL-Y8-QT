#ifndef SIM_NDT8_H
#define SIM_NDT8_H

#include "./base08/sim_base8.h"


class CSimNdt8 : public CSimBase8
{
    Q_OBJECT
    
public:
    explicit CSimNdt8(QWidget *parent = 0);
    
protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

public slots:
    void OnSimFresh();
};

#endif // SIM_NDT8_H
