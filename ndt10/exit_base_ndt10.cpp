#include "exit_base_ndt10.h"
#include "resource_manager.h"

CExitBaseNdt::CExitBaseNdt(QWidget *parent) :
    CExitBase(parent)
{

    setObjectName("CExitBaseNdt");

    resize(SYS_WID(74),SYS_HEI(100));

    pbSystemExit->setGeometry(SYS_WID(1), SYS_HEI(14), SYS_WID(70), SYS_HEI(80));

    setGeometry(SYS_WID(710), SYS_HEI(10), SYS_WID(74), SYS_HEI(100));
}
