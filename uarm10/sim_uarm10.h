#ifndef SIM_UARM10_H
#define SIM_UARM10_H

#include "./base10/sim_base10.h"


class CSimUarm10 : public CSimBase10
{
    Q_OBJECT
    
public:
    explicit CSimUarm10(QWidget *parent = 0);
    
protected:
    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

public slots:
    virtual void OnViewDirChange(int);

};

#endif // SIM_UARM10_H
