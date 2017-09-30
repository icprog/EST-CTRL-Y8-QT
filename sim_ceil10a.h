#ifndef SIM_CEIL10_A_H
#define SIM_CEIL10_A_H

#include "sim_base10.h"


class CSimCeil10a : public CSimBase10
{
    Q_OBJECT
    
public:
    explicit CSimCeil10a(QWidget *parent = 0);

protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

public slots:
    virtual void OnViewDirChange(int);
};

#endif // SIM_CEIL10_A_H
