#ifndef SIM_CEIL8_H
#define SIM_CEIL8_H

#include "./base08/sim_base8.h"


class CSimCeil8 : public CSimBase8
{
    Q_OBJECT
    
public:
    explicit CSimCeil8(QWidget *parent = 0);
    
protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

};

#endif // SIM_CEIL8_H
