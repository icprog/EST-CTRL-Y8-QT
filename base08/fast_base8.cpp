#include "fast_base8.h"
#include "resource_manager.h"

CFastBase8::CFastBase8(QWidget *parent) :
    CFastBase(parent)
{
    setObjectName("CFastBase8");

    resize(SYS_WID(90),SYS_HEI(80));

    lbFastPosition->setGeometry(QRect(0, 0, 0, 0));
    btMotionSmart->setGeometry(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(80));

    setStyleSheet("background : transparent");
}

