#include "curtain_base8.h"
#include "resource_manager.h"

CCurtainBase8::CCurtainBase8(QWidget *parent) :
    CCurtainBase(parent)
{

    setObjectName("CCurtainBase8");

    resize(SYS_WID(90),SYS_HEI(50));

    pbCurtainSwitch->setGeometry(SYS_WID(0), 0, SYS_WID(90), SYS_HEI(50));

    setGeometry(SYS_WID(500), SYS_HEI(0), SYS_WID(90), SYS_HEI(50));

}

