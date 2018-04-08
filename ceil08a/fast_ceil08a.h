#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_A

#ifndef FAST_RAIL08A_H
#define FAST_RAIL08A_H

#include "./base08/fast_base8.h"


class CFastRail08a : public CFastBase8
{
    Q_OBJECT
    
public:
    explicit CFastRail08a(QWidget *parent = 0);
    

};

#endif // FAST_RAIL08A_H
#endif //USE_RAIL_08_A

