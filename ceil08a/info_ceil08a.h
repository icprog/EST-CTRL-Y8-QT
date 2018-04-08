#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_A

#ifndef INFO_RAIL08A_H
#define INFO_RAIL08A_H

#include "./base08/info_base8.h"


class CInfoRail08a : public CInfoBase8
{
    Q_OBJECT
    
public:
    explicit CInfoRail08a(QWidget *parent = 0);

};

#endif  //INFO_RAIL08A_H
#endif  //USE_RAIL_08_A
