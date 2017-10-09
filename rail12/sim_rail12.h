#ifndef SIM_RAIL12_H
#define SIM_RAIL12_H

#include "./base12/sim_base12.h"


class CSimRail12 : public CSimBase12
{
    Q_OBJECT

public:
    explicit CSimRail12(QWidget *parent = 0);

protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

public slots:
    void OnSimFresh();
};

#endif // SIM_RAIL12_H
