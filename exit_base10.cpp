#include "exit_base10.h"
#include "resource_manager.h"

CExitBase10::CExitBase10(QWidget *parent) :
    CExitBase(parent)
{

    setObjectName("CExitBase10");

    resize(SYS_WID(90),SYS_HEI(90));

    pbSystemExit->setGeometry(SYS_WID(0), 0, SYS_WID(75), SYS_HEI(75));

    setGeometry(SYS_WID(710), SYS_HEI(10), SYS_WID(90), SYS_HEI(90));
}
