#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_A

#include "curtain_rail08a.h"
#include "resource_manager.h"

CCurtainRail08a::CCurtainRail08a(QWidget *parent) :
    CCurtainBase8(parent)
{
    setObjectName("CCurtainRail08a");

    m_iDisplayText = g_mainCfg->value("CCurtainRail08a/DisplayText",true).toInt();

    pRectCurtainWid.append(g_mainCfg->value("CCurtainRail08a/VDIR_NORMAL"  ,QRect(SYS_HEI(0),SYS_WID(0),   SYS_HEI(90),SYS_WID(50))).toRect());
    pRectCurtainWid.append(g_mainCfg->value("CCurtainRail08a/VDIR_LEFT"    ,QRect(SYS_WID(0),SYS_HEI(0),   SYS_WID(90),SYS_HEI(50))).toRect());
    pRectCurtainWid.append(g_mainCfg->value("CCurtainRail08a/VDIR_RIGHT"   ,QRect(SYS_WID(0),SYS_HEI(0),   SYS_WID(90),SYS_HEI(50))).toRect());
    pRectCurtainWid.append(g_mainCfg->value("CCurtainRail08a/VDIR_REVERSE" ,QRect(SYS_HEI(0),SYS_WID(0),   SYS_HEI(90),SYS_WID(50))).toRect());

    pRectBtn.append(g_mainCfg->value("CCurtainRail08a/BTN/VDIR_NORMAL"  ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(90), SYS_WID(50))).toRect());
    pRectBtn.append(g_mainCfg->value("CCurtainRail08a/BTN/VDIR_LEFT"    ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(90), SYS_WID(50))).toRect());
    pRectBtn.append(g_mainCfg->value("CCurtainRail08a/BTN/VDIR_RIGHT"   ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(90), SYS_WID(50))).toRect());
    pRectBtn.append(g_mainCfg->value("CCurtainRail08a/BTN/VDIR_REVERSE" ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(90), SYS_WID(50))).toRect());


    OnViewDirChange(g_systemDb->g_startAngle);

}


#endif
