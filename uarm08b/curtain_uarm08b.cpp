#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#include "curtain_rail08b.h"
#include "resource_manager.h"

CCurtainRail08b::CCurtainRail08b(QWidget *parent) :
    CCurtainBase8(parent)
{
    setObjectName("CCurtainRail08b");

    m_iDisplayText = g_mainCfg->value("CCurtainRail08b/DisplayText",false).toInt();

    OnViewDirChange(g_systemDb->g_startAngle);

}

void CCurtainRail08b::OnViewDirChange(int sAngle)
{
    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        setGeometry(g_mainCfg->value("CCurtainRail08b/Geometry",QRect(0,0,SYS_WID(70),SYS_HEI(70))).toRect());
        pbCurtainSwitch->setGeometry(g_mainCfg->value("CCurtainRail08b/pbCurtainSwitch/VIEW_DIR_NORMAL",QRect(SYS_WID(0), SYS_HEI(7), SYS_WID(70), SYS_HEI(56))).toRect());
        break;
    case VIEW_DIR_LEFT:
        setGeometry(g_mainCfg->value("CCurtainRail08b/Geometry",QRect(0,0,SYS_HEI(70),SYS_WID(70))).toRect());
        pbCurtainSwitch->setGeometry(g_mainCfg->value("CCurtainRail08b/pbCurtainSwitch/VIEW_DIR_LEFT",QRect(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56))).toRect());
        break;
    case VIEW_DIR_RIGHT:
        setGeometry(g_mainCfg->value("CCurtainRail08b/Geometry",QRect(0,0,SYS_HEI(70),SYS_WID(70))).toRect());
        pbCurtainSwitch->setGeometry(g_mainCfg->value("CCurtainRail08b/pbCurtainSwitch/VIEW_DIR_RIGHT",QRect(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56))).toRect());
        break;
    case VIEW_DIR_R180:
        setGeometry(g_mainCfg->value("CCurtainRail08b/Geometry",QRect(0,0,SYS_WID(70),SYS_HEI(70))).toRect());
        pbCurtainSwitch->setGeometry(g_mainCfg->value("CCurtainRail08b/pbCurtainSwitch/VIEW_DIR_R180",QRect(SYS_WID(0), SYS_HEI(7), SYS_WID(70), SYS_HEI(56))).toRect());
        break;
    default:
        setGeometry(g_mainCfg->value("CCurtainRail08b/Geometry",QRect(0,0,SYS_WID(70),SYS_HEI(70))).toRect());
        pbCurtainSwitch->setGeometry(g_mainCfg->value("CCurtainRail08b/pbCurtainSwitch/VIEW_DIR_NORMAL",QRect(SYS_WID(0), SYS_HEI(7), SYS_WID(70), SYS_HEI(56))).toRect());
        break;
    }

}
#endif //USE_RAIL_08_B
