#include "fast_base10.h"
#include "resource_manager.h"

CFastBase10::CFastBase10(QWidget *parent) :
    CFastBase(parent)
{

    setObjectName("CFastBase10");

    resize(SYS_HEI(300),SYS_WID(72));

    lbFastPosition->setGeometry(SYS_HEI(89), SYS_WID(4), SYS_HEI(211), SYS_WID(60));
    btMotionSmart->setGeometry( SYS_HEI(0),  SYS_WID(0), SYS_HEI(86),  SYS_WID(72));

    setStyleSheet("background-color : lightGray");
}
