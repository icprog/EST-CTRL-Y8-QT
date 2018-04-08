#ifndef CURTAIN_RAIL08A_H
#define CURTAIN_RAIL08A_H

#include "./base08/curtain_base8.h"
#ifdef USE_RAIL_08_A


class CCurtainRail08a : public CCurtainBase8
{
    Q_OBJECT
    
public:
    explicit CCurtainRail08a(QWidget *parent = 0);

};

#endif  //CURTAIN_RAIL08A_H
#endif  //USE_RAIL_08_A
