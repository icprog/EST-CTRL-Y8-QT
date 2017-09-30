#ifndef SIM_UARM8_H
#define SIM_UARM8_H

#include "sim_base8.h"

class CSimUarm8 : public CSimBase8
{
    Q_OBJECT
    
public:
    explicit CSimUarm8(QWidget *parent = 0);
    
protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

};

#endif // SIM_UARM8_H
