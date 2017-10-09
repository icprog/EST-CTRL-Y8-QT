#include "quick_rail8.h"
#include "resource_manager.h"

CQuickRail8::CQuickRail8(QWidget *parent) :
    CQuickBase8(parent)
{
    setObjectName("CQuickRail8");

    m_codeQuickDown[QUICK_BTN_00] = 0x0058;
    m_codeQuickDown[QUICK_BTN_01] = 0x0058;
    m_codeQuickDown[QUICK_BTN_02] = 0x0057;

    m_codeQuickLong[QUICK_BTN_00] = SMART_POS_01;
    m_codeQuickLong[QUICK_BTN_01] = SMART_POS_05;
    m_codeQuickLong[QUICK_BTN_02] = SMART_POS_07;
}

void CQuickRail8::quickPressed()
{

    //通过配置文件，关闭快捷运动按钮
    if(g_mainCfg->value("isQuickEnable",true).toInt() == false)
        return;

    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_00)
        quickPressed00();

    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_01)
        quickPressed01();

}
void CQuickRail8::quickPressed01()
{
    if(sender() == pBtnQuick[QUICK_BTN_00])
    {
        SendCmdKey(m_codeQuickDown[QUICK_BTN_00]);

        m_iQuickIdx = QUICK_BTN_00;
        timerLongPress->start();

        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_00"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));

    }

    if(sender() == pBtnQuick[QUICK_BTN_01])
    {
        SendCmdKey(m_codeQuickDown[QUICK_BTN_01]);

        m_iQuickIdx = QUICK_BTN_01;
        timerLongPress->start();

        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_02"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));

    }

    if(sender() == pBtnQuick[QUICK_BTN_02])
    {
        SendCmdKey(m_codeQuickDown[QUICK_BTN_02]);

        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_04"));
    }
}
void CQuickRail8::quickPressed00()
{
    if(sender() == pBtnQuick[QUICK_BTN_00])
    {
        SendCmdKey(m_codeQuickDown[QUICK_BTN_00]);

        m_iQuickIdx = QUICK_BTN_00;
        timerLongPress->start();

        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_00"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));

    }

    if(sender() == pBtnQuick[QUICK_BTN_01])
    {
        SendCmdKey(m_codeQuickDown[QUICK_BTN_01]);

        m_iQuickIdx = QUICK_BTN_01;
        timerLongPress->start();

        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_02"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));

    }

    if(sender() == pBtnQuick[QUICK_BTN_02])
    {
        SendCmdKey(m_codeQuickDown[QUICK_BTN_02]);

        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_04"));
    }
}

//快捷状态改变
void CQuickRail8::OnStatusChange(int pos,QPushButton * )
{

    switch(pos)
    {
    case SMART_POS_00:
        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));
        break;
    case SMART_POS_01:
    case SMART_POS_02:
        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_00"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));
        break;
    case SMART_POS_03:
    case SMART_POS_04:
        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_00"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_03"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_04"));
        break;
    case SMART_POS_05:
        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_02"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_05"));
        break;
    case SMART_POS_06:
        pBtnQuick[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_01"));
        pBtnQuick[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_02"));
        pBtnQuick[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_STR_SMART_04"));
        break;
    }
}
