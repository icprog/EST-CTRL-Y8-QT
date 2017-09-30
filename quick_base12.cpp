#include "quick_base12.h"

#include "resource_manager.h"

CQuickBase12::CQuickBase12(QWidget *parent) :
    CQuickBase(parent)
{

    pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
    pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
    pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));

    OnViewDirChange(g_systemDb->g_startAngle);

    pBtnQuick[QUICK_BTN_00]->setFlat(true);
    pBtnQuick[QUICK_BTN_01]->setFlat(true);
    pBtnQuick[QUICK_BTN_02]->setFlat(true);

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,0,100)");
    }
}

void CQuickBase12::quickReleased()
{
    timerLongPress->stop();
}

void CQuickBase12::OnKeyLongPress()
{

    emit SmartChange( m_codeQuickLong[m_iQuickIdx]);     //发送一键命令给下位机

    RsMgr->g_filmBase->SetKeySound();
}
void CQuickBase12::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(330),  SYS_WID(330));
        pBtnQuick[QUICK_BTN_00]->setGeometry(SYS_HEI(110),SYS_WID(50),   SYS_HEI(111),SYS_WID(73));
        pBtnQuick[QUICK_BTN_01]->setGeometry(SYS_HEI(109),SYS_WID(128),  SYS_HEI(111),SYS_WID(73));
        pBtnQuick[QUICK_BTN_02]->setGeometry(SYS_HEI(109),SYS_WID(204),  SYS_HEI(111),SYS_WID(73));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(330),  SYS_HEI(330));
        pBtnQuick[QUICK_BTN_00]->setGeometry(SYS_WID(2),  SYS_HEI(130),  SYS_WID(111),SYS_HEI(73));
        pBtnQuick[QUICK_BTN_01]->setGeometry(SYS_WID(110),SYS_HEI(131),  SYS_WID(111),SYS_HEI(73));
        pBtnQuick[QUICK_BTN_02]->setGeometry(SYS_WID(219),SYS_HEI(130),  SYS_WID(111),SYS_HEI(73));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(330),  SYS_HEI(330));
        pBtnQuick[QUICK_BTN_00]->setGeometry(SYS_WID(2),  SYS_HEI(130),  SYS_WID(111),SYS_HEI(73));
        pBtnQuick[QUICK_BTN_01]->setGeometry(SYS_WID(110),SYS_HEI(131),  SYS_WID(111),SYS_HEI(73));
        pBtnQuick[QUICK_BTN_02]->setGeometry(SYS_WID(219),SYS_HEI(130),  SYS_WID(111),SYS_HEI(73));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;
    }
}
