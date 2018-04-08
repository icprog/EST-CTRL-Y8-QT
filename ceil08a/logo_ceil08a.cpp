#include "logo_rail08a.h"

CLogoRail08a::CLogoRail08a(QWidget *parent) :
    CLogoBase8(parent)
{   

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("QWidget {background-color:rgb(108,20,0);}");

    }

    pRectLogoLabel.append(g_mainCfg->value("CLogoRail08a/LOGO/VDIR_NORMAL"  ,QRect(SYS_HEI(0),   SYS_WID(0), SYS_HEI(90), SYS_WID(55))).toRect());
    pRectLogoLabel.append(g_mainCfg->value("CLogoRail08a/LOGO/VDIR_LEFT"    ,QRect(SYS_WID(0),   SYS_HEI(0), SYS_WID(90), SYS_HEI(55))).toRect());
    pRectLogoLabel.append(g_mainCfg->value("CLogoRail08a/LOGO/VDIR_RIGHT"   ,QRect(SYS_WID(0),   SYS_HEI(0), SYS_WID(90), SYS_HEI(55))).toRect());
    pRectLogoLabel.append(g_mainCfg->value("CLogoRail08a/LOGO/VDIR_REVERSE" ,QRect(SYS_HEI(0),   SYS_WID(0), SYS_HEI(90), SYS_WID(55))).toRect());

    pRectLogoWid.append(g_mainCfg->value("CLogoRail08a/VDIR_NORMAL"  ,QRect(SYS_HEI(0),   SYS_WID(0), SYS_HEI(90), SYS_WID(55))).toRect());
    pRectLogoWid.append(g_mainCfg->value("CLogoRail08a/VDIR_LEFT"    ,QRect(SYS_WID(0),   SYS_HEI(0), SYS_WID(90), SYS_HEI(55))).toRect());
    pRectLogoWid.append(g_mainCfg->value("CLogoRail08a/VDIR_RIGHT"   ,QRect(SYS_WID(0),   SYS_HEI(0), SYS_WID(90), SYS_HEI(55))).toRect());
    pRectLogoWid.append(g_mainCfg->value("CLogoRail08a/VDIR_REVERSE" ,QRect(SYS_HEI(0),   SYS_WID(0), SYS_HEI(90), SYS_WID(55))).toRect());

    OnViewDirChange(g_systemDb->g_startAngle);
}
