#include "exit_base8.h"
#include "resource_manager.h"

CExitBase8::CExitBase8(QWidget *parent) :
    CExitBase(parent)
{

    setObjectName("CExitBase8");

    resize(SYS_WID(90),SYS_HEI(50));

    pbSystemExit->setGeometry(SYS_WID(0), 0, SYS_WID(90), SYS_HEI(50));

    setGeometry(SYS_WID(500), SYS_HEI(0), SYS_WID(90), SYS_HEI(50));

}

