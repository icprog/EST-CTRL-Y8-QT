#include "quick_base8.h"

#include "resource_manager.h"

CQuickBase8::CQuickBase8(QWidget *parent) :
    CQuickBase(parent)
{

    pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
    pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
    pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));

    pBtnQuick[QUICK_BTN_00]->setGeometry(SYS_WID(0),  SYS_HEI(0),  SYS_WID(100),SYS_HEI(100));
    pBtnQuick[QUICK_BTN_01]->setGeometry(SYS_WID(100),SYS_HEI(0),  SYS_WID(100),SYS_HEI(100));
    pBtnQuick[QUICK_BTN_02]->setGeometry(SYS_WID(200),SYS_HEI(0),  SYS_WID(100),SYS_HEI(100));

    pBtnQuick[QUICK_BTN_00]->setFlat(true);
    pBtnQuick[QUICK_BTN_01]->setFlat(true);
    pBtnQuick[QUICK_BTN_02]->setFlat(true);
}

void CQuickBase8::quickReleased()
{
    timerLongPress->stop();
}

void CQuickBase8::OnKeyLongPress()
{

    emit SmartChange( m_codeQuickLong[m_iQuickIdx]);     //发送一键命令给下位机

    RsMgr->g_filmBase->SetKeySound();
}
