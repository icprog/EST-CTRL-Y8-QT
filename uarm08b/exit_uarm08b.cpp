#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#include "exit_rail08b.h"
#include "resource_manager.h"

CExitRail08b::CExitRail08b(QWidget *parent) :
    CExitBase8(parent)
{

    setObjectName("CExitRail08b");

    OnViewDirChange(g_systemDb->g_startAngle);
}

void CExitRail08b::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        setGeometry(g_mainCfg->value("CExitRail08b/Geometry",QRect(0,0,SYS_WID(70),SYS_HEI(70))).toRect());
        pbSystemExit->setGeometry(g_mainCfg->value("CExitRail08b/VIEW_DIR_NORMAL/pbSystemExit",QRect(SYS_WID(0), SYS_HEI(7), SYS_WID(70), SYS_HEI(56))).toRect());
        break;
    case VIEW_DIR_LEFT:
        setGeometry(g_mainCfg->value("CExitRail08b/Geometry",QRect(0,0,SYS_HEI(70),SYS_WID(70))).toRect());
        pbSystemExit->setGeometry(g_mainCfg->value("CExitRail08b/VIEW_DIR_LEFT/pbSystemExit",QRect(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56))).toRect());
        break;
    case VIEW_DIR_RIGHT:
        setGeometry(g_mainCfg->value("CExitRail08b/Geometry",QRect(0,0,SYS_HEI(70),SYS_WID(70))).toRect());
        pbSystemExit->setGeometry(g_mainCfg->value("CExitRail08b/VIEW_DIR_RIGHT/pbSystemExit",QRect(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56))).toRect());
        break;
    case VIEW_DIR_R180:
        setGeometry(g_mainCfg->value("CExitRail08b/Geometry",QRect(0,0,SYS_WID(70),SYS_HEI(70))).toRect());
        pbSystemExit->setGeometry(g_mainCfg->value("CExitRail08b/VIEW_DIR_R180/pbSystemExit",QRect(SYS_WID(0), SYS_HEI(7), SYS_WID(70), SYS_HEI(56))).toRect());
        break;
    default:
        setGeometry(g_mainCfg->value("CExitRail08b/Geometry",QRect(0,0,SYS_WID(70),SYS_HEI(70))).toRect());
        pbSystemExit->setGeometry(g_mainCfg->value("CExitRail08b/VIEW_DIR_NORMAL/pbSystemExit",QRect(SYS_WID(0), SYS_HEI(7), SYS_WID(70), SYS_HEI(56))).toRect());
        break;
    }
}


#endif //USE_RAIL_08_B
