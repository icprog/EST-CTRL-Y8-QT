#include "logo_rail08b.h"

CLogoRail08b::CLogoRail08b(QWidget *parent) :
    CLogoBase8(parent)
{   

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("QWidget {background-color:rgb(108,20,0);}");

    }

    pRectLogoWid.append(g_mainCfg->value("CLogoRail08b/VDIR_NORMAL"  ,QRect(SYS_HEI(0),   SYS_WID(0), SYS_HEI(90), SYS_WID(90))).toRect());
    pRectLogoWid.append(g_mainCfg->value("CLogoRail08b/VDIR_LEFT"    ,QRect(SYS_WID(0),   SYS_HEI(0), SYS_WID(90), SYS_HEI(90))).toRect());
    pRectLogoWid.append(g_mainCfg->value("CLogoRail08b/VDIR_RIGHT"   ,QRect(SYS_WID(0),   SYS_HEI(0), SYS_WID(90), SYS_HEI(90))).toRect());
    pRectLogoWid.append(g_mainCfg->value("CLogoRail08b/VDIR_REVERSE" ,QRect(SYS_HEI(0),   SYS_WID(0), SYS_HEI(90), SYS_WID(90))).toRect());

    pRectLogoLabel.append(g_mainCfg->value("CLogoRail08b/LOGO/VDIR_NORMAL"  ,QRect(SYS_HEI(0),   SYS_WID(17), SYS_HEI(90), SYS_WID(56))).toRect());
    pRectLogoLabel.append(g_mainCfg->value("CLogoRail08b/LOGO/VDIR_LEFT"    ,QRect(SYS_WID(0),   SYS_HEI(17), SYS_WID(90), SYS_HEI(56))).toRect());
    pRectLogoLabel.append(g_mainCfg->value("CLogoRail08b/LOGO/VDIR_RIGHT"   ,QRect(SYS_WID(0),   SYS_HEI(17), SYS_WID(90), SYS_HEI(56))).toRect());
    pRectLogoLabel.append(g_mainCfg->value("CLogoRail08b/LOGO/VDIR_REVERSE" ,QRect(SYS_HEI(0),   SYS_WID(17), SYS_HEI(90), SYS_WID(56))).toRect());

    OnViewDirChange(g_systemDb->g_startAngle);
}
