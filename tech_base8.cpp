#include "tech_base8.h"
#include "resource_manager.h"

CTechBase8::CTechBase8(QWidget *parent) :
    CTechBase(parent)
{
    setObjectName("CTechBase8");

    resize(SYS_WID(300),SYS_HEI(100));

    pBtnGroup[SYS_TECH_AEC]->setGeometry(SYS_WID(0), 0, SYS_WID(100),SYS_HEI(100));
    pBtnGroup[SYS_TECH_MAS]->setGeometry(SYS_WID(100), 0, SYS_WID(100),SYS_HEI(100));
    pBtnGroup[SYS_TECH_MAMS]->setGeometry(SYS_WID(200), 0, SYS_WID(100),SYS_HEI(100));

    pBtnGroup[SYS_TECH_AEC]->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_SYSTEM_UP"));
    pBtnGroup[SYS_TECH_MAS]->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_SYSTEM_UP"));
    pBtnGroup[SYS_TECH_MAMS]->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_SYSTEM_UP"));
}
