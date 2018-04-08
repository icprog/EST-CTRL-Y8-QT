#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_A

#include "info_rail08a.h"
#include "resource_manager.h"

CInfoRail08a::CInfoRail08a(QWidget *parent) :
    CInfoBase8(parent)
{

    setObjectName("CInfoRail08a");

    setGeometry(g_mainCfg->value("CInfoRail08a/Geometry",QRect(0,0,SYS_HEI(300),SYS_WID(50))).toRect());

    lbMsgIcon->setGeometry(SYS_WID(0),  SYS_HEI(0), SYS_WID(50), SYS_HEI(50));
    lbMsgInfo->setGeometry(SYS_WID(50), SYS_HEI(0), SYS_WID(250), SYS_HEI(50));

}

#endif
