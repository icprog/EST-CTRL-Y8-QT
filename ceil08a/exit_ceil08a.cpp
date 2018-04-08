
#include "exit_rail08a.h"

#ifdef USE_RAIL_08_A


CExitRail08a::CExitRail08a(QWidget *parent) :
    CExitBase8(parent)
{

    setObjectName("CExitRail08a");

    pRectExitWid.append(g_sysDb->value("CExitRail08a/VDIR_NORMAL"  ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(70), SYS_WID(70))).toRect());
    pRectExitWid.append(g_sysDb->value("CExitRail08a/VDIR_LEFT"    ,QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(70), SYS_HEI(70))).toRect());
    pRectExitWid.append(g_sysDb->value("CExitRail08a/VDIR_RIGHT"   ,QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(70), SYS_HEI(70))).toRect());
    pRectExitWid.append(g_sysDb->value("CExitRail08a/VDIR_REVERSE" ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(70), SYS_WID(70))).toRect());

    pRectExitBtn.append(g_sysDb->value("CExitRail08a/VDIR_NORMAL/BTN"  ,QRect(SYS_HEI(0), SYS_WID(10), SYS_HEI(70), SYS_WID(50))).toRect());
    pRectExitBtn.append(g_sysDb->value("CExitRail08a/VDIR_LEFT/BTN"    ,QRect(SYS_HEI(0), SYS_WID(10), SYS_HEI(70), SYS_WID(50))).toRect());
    pRectExitBtn.append(g_sysDb->value("CExitRail08a/VDIR_RIGHT/BTN"   ,QRect(SYS_HEI(0), SYS_WID(10), SYS_HEI(70), SYS_WID(50))).toRect());
    pRectExitBtn.append(g_sysDb->value("CExitRail08a/VDIR_REVERSE/BTN" ,QRect(SYS_HEI(0), SYS_WID(10), SYS_HEI(70), SYS_WID(50))).toRect());

    OnViewDirChange(g_sysDb->g_startAngle);

    if(g_sysDb->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,100,245)");
    }
}


#endif
