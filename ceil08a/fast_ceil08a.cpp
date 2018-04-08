#include "fast_rail08a.h"

#ifdef USE_RAIL_08_A


CFastRail08a::CFastRail08a(QWidget *parent) :
    CFastBase8(parent)
{
    setObjectName("CFastRail08a");

    setGeometry(g_sysDb->value("CFastRail08a/Geometry",QRect(0,0,SYS_HEI(90),SYS_WID(80))).toRect());

    lbFastPosition->setGeometry(QRect(0, 0, 0, 0));
    btMotionSmart->setGeometry(g_sysDb->value("CFastRail08a/Geometry",QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(80))).toRect());
}

#endif
