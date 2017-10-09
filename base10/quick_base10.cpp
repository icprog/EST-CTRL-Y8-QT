#include "quick_base10.h"

#include "resource_manager.h"

CQuickBase10::CQuickBase10(QWidget *parent) :
    CQuickBase(parent)
{
    resize(SYS_WID(80),SYS_HEI(372));

    pBtnQuick[QUICK_BTN_00]->setGeometry(0, SYS_HEI(0), SYS_WID(76), SYS_HEI(124));
    pBtnQuick[QUICK_BTN_01]->setGeometry(0, SYS_HEI(124), SYS_WID(76), SYS_HEI(124));
    pBtnQuick[QUICK_BTN_02]->setGeometry(0, SYS_HEI(248), SYS_WID(76), SYS_HEI(124));

    OnViewDirChange(m_iViewDir);

}

void CQuickBase10::OnViewDirChange(int viewerDir)
{

    for(int mIdx = 0 ;mIdx < QUICK_BTN_MAX ; mIdx++)
    {
        if(pBtnQuick[mIdx]->isDown())
        {
            pBtnQuick[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(mIdx * MENU10_BTN_KEY_STEP + viewerDir*2 + SYS_KEY_ICON_BASE + 68 + 1));
        }else
        {
            pBtnQuick[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(mIdx * MENU10_BTN_KEY_STEP + viewerDir*2 + SYS_KEY_ICON_BASE + 68));
        }
    }

    m_iViewDir = viewerDir;
}
void CQuickBase10::quickPressed()
{
    //通过配置文件，关闭快捷运动按钮
    if(g_mainCfg->value("isQuickEnable",true).toInt() == false)
        return;

    for(int mIdx = 0 ; mIdx < QUICK_BTN_MAX ; mIdx++)
    {
        if(sender() == pBtnQuick[mIdx])
        {
            pBtnQuick[mIdx]->setStyleSheet( g_skinBase->GetStyleMapStr(mIdx * MENU10_BTN_KEY_STEP + m_iViewDir * 2 + SYS_KEY_ICON_BASE + 68 + 1));

            emit ViewChange(VIEW_MOTION);
            SendCmdKey(m_codeQuickDown[mIdx]);
            m_iQuickIdx = mIdx;
            timerLongPress->start();
            break;
        }
    }
}
void CQuickBase10::quickReleased()
{
    for(int mIdx = 0 ; mIdx < QUICK_BTN_MAX ; mIdx++)
    {
        if(sender() == pBtnQuick[mIdx])
        {
            m_iQuickIdx = QUICK_KEY_INVALID;
            pBtnQuick[mIdx]->setStyleSheet( g_skinBase->GetStyleMapStr(mIdx * MENU10_BTN_KEY_STEP + m_iViewDir * 2 +  SYS_KEY_ICON_BASE + 68));
            timerLongPress->stop();
            break;
        }
    }
}
void CQuickBase10::OnKeyLongPress()
{

    //emit SmartChange( m_codeQuickLong[m_iQuickIdx]);     //发送一键命令给下位机
    SendCmdKey(m_codeQuickLong[m_iQuickIdx]);
}
