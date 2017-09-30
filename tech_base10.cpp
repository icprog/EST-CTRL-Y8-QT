#include "tech_base10.h"
#include "resource_manager.h"

CTechBase10::CTechBase10(QWidget *parent) :
    CTechBase(parent)
{
    setObjectName("CTechBase10");

    resize(SYS_HEI(300),SYS_WID(80));

    pBtnGroup[SYS_TECH_AEC]->setGeometry( SYS_HEI(0),   0,SYS_HEI(100), SYS_WID(80));
    pBtnGroup[SYS_TECH_MAS]->setGeometry( SYS_HEI(100), 0,SYS_HEI(100), SYS_WID(80));
    pBtnGroup[SYS_TECH_MAMS]->setGeometry(SYS_HEI(200), 0,SYS_HEI(100), SYS_WID(80));

    setStyleSheet("background-color : lightGray");
}

