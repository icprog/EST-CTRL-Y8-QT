#include "exit_base12.h"
#include "resource_manager.h"

CExitBase12::CExitBase12(QWidget *parent) :
    CExitBase(parent)
{

    setObjectName("CExitBase12");

    OnViewDirChange(g_systemDb->g_startAngle);

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,100,245)");
    }
}

void CExitBase12::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(90),SYS_WID(90));
        pbSystemExit->setGeometry(SYS_HEI(0), SYS_WID(6), SYS_HEI(90), SYS_WID(72));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(90),SYS_HEI(90));
        pbSystemExit->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(90),SYS_HEI(90));
        pbSystemExit->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }
}
