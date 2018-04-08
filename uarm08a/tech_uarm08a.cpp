#include "tech_rail08a.h"
#ifdef USE_RAIL_08_A


CTechRail08a::CTechRail08a(QWidget *parent) :
    CTechBase8(parent)
{
    setObjectName("CTechRail08a");

    //Tech窗口在不同角度下的大小
    pRectTechWid.append(g_mainCfg->value("CTechRail08a/VDIR_NORMAL"  ,QRect(SYS_HEI(0),SYS_WID(0),   SYS_HEI(300),SYS_WID(300))).toRect());
    pRectTechWid.append(g_mainCfg->value("CTechRail08a/VDIR_LEFT"    ,QRect(SYS_WID(0),SYS_HEI(0),   SYS_WID(300),SYS_HEI(300))).toRect());
    pRectTechWid.append(g_mainCfg->value("CTechRail08a/VDIR_RIGHT"   ,QRect(SYS_WID(0),SYS_HEI(0),   SYS_WID(300),SYS_HEI(300))).toRect());
    pRectTechWid.append(g_mainCfg->value("CTechRail08a/VDIR_REVERSE" ,QRect(SYS_HEI(0),SYS_WID(0),   SYS_HEI(300),SYS_WID(300))).toRect());

    //按钮在不同角度下的大小
    QList<QRect> tempRect;
    //normal
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_NORMAL/AEC"  ,QRect(SYS_HEI(0),SYS_WID(100),    SYS_HEI(100),SYS_WID(100))).toRect());
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_NORMAL/MAS"  ,QRect(SYS_HEI(100),SYS_WID(100),  SYS_HEI(100),SYS_WID(100))).toRect());
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_NORMAL/MAMS" ,QRect(SYS_HEI(200),SYS_WID(100),SYS_HEI(100),SYS_WID(100))).toRect());
    pRectTechBtn.append(tempRect);

    //left
    tempRect.clear();
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_LEFT/AEC"    ,QRect(SYS_WID(0),SYS_HEI(100),    SYS_WID(100),SYS_HEI(100))).toRect());
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_LEFT/MAS"    ,QRect(SYS_WID(100),SYS_HEI(100),  SYS_WID(100),SYS_HEI(100))).toRect());
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_LEFT/MAMS"   ,QRect(SYS_WID(200),SYS_HEI(100),SYS_WID(100),SYS_HEI(100))).toRect());
    pRectTechBtn.append(tempRect);

    //right
    tempRect.clear();
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_RIGHT/AEC"  ,QRect(SYS_WID(0),SYS_HEI(100),    SYS_WID(100),SYS_HEI(100))).toRect());
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_RIGHT/MAS"  ,QRect(SYS_WID(100),SYS_HEI(100),  SYS_WID(100),SYS_HEI(100))).toRect());
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_RIGHT/MAMS" ,QRect(SYS_WID(200),SYS_HEI(100),SYS_WID(100),SYS_HEI(100))).toRect());
    pRectTechBtn.append(tempRect);

    //reverse
    tempRect.clear();
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_REVERSE/AEC"  ,QRect(SYS_HEI(0),SYS_WID(100),    SYS_HEI(100),SYS_WID(100))).toRect());
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_REVERSE/MAS"  ,QRect(SYS_HEI(100),SYS_WID(100),  SYS_HEI(100),SYS_WID(100))).toRect());
    tempRect.append(g_mainCfg->value("CTechRail08a/VDIR_REVERSE/MAMS" ,QRect(SYS_HEI(200),SYS_WID(100),SYS_HEI(100),SYS_WID(100))).toRect());
    pRectTechBtn.append(tempRect);

    OnViewDirChange(g_systemDb->g_startAngle);
}

#endif
