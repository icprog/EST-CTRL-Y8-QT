#ifndef SIM_RAIL8_H
#define SIM_RAIL8_H

#include "./base08/sim_base8.h"


class CSimRail8 : public CSimBase8
{
    Q_OBJECT
    
public:
    explicit CSimRail8(QWidget *parent = 0);
    
protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

public slots:
    void OnSimFresh();
};

#endif // SIM_RAIL8_H
