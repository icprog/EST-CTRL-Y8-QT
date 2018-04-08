#include "exit_rail08b.h"
#include "resource_manager.h"

CExitRail08b::CExitRail08b(QWidget *parent) :
    CExitBase8(parent)
{

    setObjectName("CExitRail08b");

    resize(SYS_WID(70),SYS_HEI(70));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,100,245)");
    }

    OnViewDirChange(g_systemDb->g_startAngle);
}

void CExitRail08b::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:

        pbSystemExit->setGeometry(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56));
        break;
    case VIEW_DIR_LEFT:

        pbSystemExit->setGeometry(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56));
        break;
    case VIEW_DIR_RIGHT:

        pbSystemExit->setGeometry(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }
}
