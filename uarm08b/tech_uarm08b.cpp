#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#include "tech_rail08b.h"
#include "resource_manager.h"

CTechRail08b::CTechRail08b(QWidget *parent) :
    CTechBase8(parent)
{
    setObjectName("CTechRail08b");

    OnViewDirChange(g_systemDb->g_startAngle);

}

void CTechRail08b::OnViewDirChange(int viewPoint)
{
    switch(viewPoint)
    {
    case VIEW_DIR_NORMAL:
        setGeometry(g_mainCfg->value("CTechRail08b/Geometry",QRect(0,0,SYS_WID(267),SYS_HEI(267))).toRect());
        pBtnGroup[SYS_TECH_AEC]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_NORMAL/TECH_AEC",QRect(SYS_WID(0),SYS_HEI(98),   SYS_WID(89),SYS_HEI(69))).toRect());
        pBtnGroup[SYS_TECH_MAS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_NORMAL/TECH_MAS",QRect(SYS_WID(89),SYS_HEI(98),  SYS_WID(89),SYS_HEI(69))).toRect());
        pBtnGroup[SYS_TECH_MAMS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_NORMAL/TECH_MAMS",QRect(SYS_WID(178),SYS_HEI(98),  SYS_WID(89),SYS_HEI(69))).toRect());
        break;
    case VIEW_DIR_LEFT:
        setGeometry(g_mainCfg->value("CTechRail08b/Geometry",QRect(0,0,SYS_HEI(267),SYS_WID(267))).toRect());
        pBtnGroup[SYS_TECH_AEC]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_LEFT/TECH_AEC",QRect(SYS_HEI(89),SYS_WID(44),   SYS_HEI(89),SYS_WID(60))).toRect());
        pBtnGroup[SYS_TECH_MAS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_LEFT/TECH_MAS",QRect(SYS_HEI(89),SYS_WID(104),  SYS_HEI(89),SYS_WID(60))).toRect());
        pBtnGroup[SYS_TECH_MAMS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_LEFT/TECH_MAMS",QRect(SYS_HEI(89),SYS_WID(164),SYS_HEI(89),SYS_WID(60))).toRect());
        break;
    case VIEW_DIR_RIGHT:
        setGeometry(g_mainCfg->value("CTechRail08b/Geometry",QRect(0,0,SYS_HEI(267),SYS_WID(267))).toRect());
        pBtnGroup[SYS_TECH_AEC]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_RIGHT/TECH_AEC",QRect(SYS_HEI(89),SYS_WID(44),   SYS_HEI(89),SYS_WID(60))).toRect());
        pBtnGroup[SYS_TECH_MAS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_RIGHT/TECH_MAS",QRect(SYS_HEI(89),SYS_WID(104),  SYS_HEI(89),SYS_WID(60))).toRect());
        pBtnGroup[SYS_TECH_MAMS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_RIGHT/TECH_MAMS",QRect(SYS_HEI(89),SYS_WID(164),SYS_HEI(89),SYS_WID(60))).toRect());
        break;
    case VIEW_DIR_R180:
        setGeometry(g_mainCfg->value("CTechRail08b/Geometry",QRect(0,0,SYS_WID(267),SYS_HEI(267))).toRect());
        pBtnGroup[SYS_TECH_AEC]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_R180/TECH_AEC",QRect(SYS_WID(0),SYS_HEI(98),   SYS_WID(89),SYS_HEI(69))).toRect());
        pBtnGroup[SYS_TECH_MAS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_R180/TECH_MAS",QRect(SYS_WID(89),SYS_HEI(98),  SYS_WID(89),SYS_HEI(69))).toRect());
        pBtnGroup[SYS_TECH_MAMS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_R180/TECH_MAMS",QRect(SYS_WID(178),SYS_HEI(98),  SYS_WID(89),SYS_HEI(69))).toRect());
        break;
    default:
        setGeometry(g_mainCfg->value("CTechRail08b/Geometry",QRect(0,0,SYS_WID(267),SYS_HEI(267))).toRect());
        pBtnGroup[SYS_TECH_AEC]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_NORMAL/TECH_AEC",QRect(SYS_WID(0),SYS_HEI(98),   SYS_WID(89),SYS_HEI(69))).toRect());
        pBtnGroup[SYS_TECH_MAS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_NORMAL/TECH_MAS",QRect(SYS_WID(89),SYS_HEI(98),  SYS_WID(89),SYS_HEI(69))).toRect());
        pBtnGroup[SYS_TECH_MAMS]->setGeometry(g_mainCfg->value("CTechRail08b/VIEW_DIR_NORMAL/TECH_MAMS",QRect(SYS_WID(178),SYS_HEI(98),  SYS_WID(89),SYS_HEI(69))).toRect());
        break;
    }
}
#endif //USE_RAIL_08_B
