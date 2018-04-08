#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#include "fast_rail08b.h"
#include "resource_manager.h"

CFastRail08b::CFastRail08b(QWidget *parent) :
    CFastBase8(parent)
{
    setObjectName("CFastRail08b");

    lbFastPosition->setGeometry(QRect(0, 0, 0, 0));

    OnViewDirChange(g_systemDb->g_startAngle);

}

void CFastRail08b::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        setGeometry(g_mainCfg->value("CFastRail08a/Geometry",QRect(0,0,SYS_WID(98),SYS_HEI(98))).toRect());
        btMotionSmart->setGeometry(g_mainCfg->value("CFastRail08b/VIEW_DIR_NORMAL/btMotionSmart",QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(98), SYS_HEI(98))).toRect());
        break;
    case VIEW_DIR_LEFT:
        setGeometry(g_mainCfg->value("CFastRail08a/Geometry",QRect(0,0,SYS_HEI(98),SYS_WID(98))).toRect());
        btMotionSmart->setGeometry(g_mainCfg->value("CFastRail08b/VIEW_DIR_LEFT/btMotionSmart",QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(98), SYS_WID(98))).toRect());
        break;
    case VIEW_DIR_RIGHT:
        setGeometry(g_mainCfg->value("CFastRail08a/Geometry",QRect(0,0,SYS_HEI(98),SYS_WID(98))).toRect());
        btMotionSmart->setGeometry(g_mainCfg->value("CFastRail08b/VIEW_DIR_RIGHT/btMotionSmart",QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(98), SYS_WID(98))).toRect());
        break;
    case VIEW_DIR_R180:
        setGeometry(g_mainCfg->value("CFastRail08a/Geometry",QRect(0,0,SYS_WID(98),SYS_HEI(98))).toRect());
        btMotionSmart->setGeometry(g_mainCfg->value("CFastRail08b/VIEW_DIR_NORMAL/btMotionSmart",QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(98), SYS_HEI(98))).toRect());
        break;
    default:
        setGeometry(g_mainCfg->value("CFastRail08a/Geometry",QRect(0,0,SYS_WID(98),SYS_HEI(98))).toRect());
        btMotionSmart->setGeometry(g_mainCfg->value("CFastRail08b/VIEW_DIR_NORMAL/btMotionSmart",QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(98), SYS_HEI(98))).toRect());
        break;
    }
}


#endif //USE_RAIL_08_B
