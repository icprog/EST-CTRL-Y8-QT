#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#ifndef FAST_RAIL08B_H
#define FAST_RAIL08B_H

#include "./base08/fast_base8.h"


class CFastRail08b : public CFastBase8
{
    Q_OBJECT
    
public:
    explicit CFastRail08b(QWidget *parent = 0);

public slots:
    virtual void OnViewDirChange(int);      //显示视角切换

};

#endif // FAST_RAIL08B_H
#endif //USE_RAIL_08_B
