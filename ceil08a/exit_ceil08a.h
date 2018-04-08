#ifndef EXIT_RAIL08A_H
#define EXIT_RAIL08A_H

#include "./base08/exit_base8.h"
#ifdef USE_RAIL_08_A


class CExitRail08a : public CExitBase8
{
    Q_OBJECT
    
public:
    explicit CExitRail08a(QWidget *parent = 0);

};

#endif  //EXIT_RAIL08A_H
#endif  //USE_RAIL_08_A
