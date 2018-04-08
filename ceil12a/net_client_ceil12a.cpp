#include "net_client_rail12a.h"

#ifdef USE_CEIL_12_A


CNetClientCeil12a::CNetClientCeil12a(QWidget *parent) :
    CNetClient12(parent)
{
    setObjectName("CNetClientCeil12a");

    m_iDisplayText = g_sysDb->value("CNetClientCeil12a/DisplayText",false).toInt();

    pRectNetWid.append(g_sysDb->value("CNetClientRail08b/VDIR_NORMAL"  ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(90), SYS_WID(90))).toRect());
    pRectNetWid.append(g_sysDb->value("CNetClientRail08b/VDIR_LEFT"    ,QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(90))).toRect());
    pRectNetWid.append(g_sysDb->value("CNetClientRail08b/VDIR_RIGHT"   ,QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(90))).toRect());
    pRectNetWid.append(g_sysDb->value("CNetClientRail08b/VDIR_REVERSE" ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(90), SYS_WID(90))).toRect());

    pRectNetBtn.append(g_sysDb->value("CNetClientRail08b/VDIR_NORMAL/ICON"  ,QRect(SYS_HEI(0), SYS_WID(6), SYS_HEI(90), SYS_WID(72))).toRect());
    pRectNetBtn.append(g_sysDb->value("CNetClientRail08b/VDIR_LEFT/ICON"    ,QRect(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72))).toRect());
    pRectNetBtn.append(g_sysDb->value("CNetClientRail08b/VDIR_RIGHT/ICON"   ,QRect(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72))).toRect());
    pRectNetBtn.append(g_sysDb->value("CNetClientRail08b/VDIR_REVERSE/ICON" ,QRect(SYS_HEI(0), SYS_WID(6), SYS_HEI(90), SYS_WID(72))).toRect());

    OnViewDirChange(g_sysDb->g_startAngle);
}

#endif
