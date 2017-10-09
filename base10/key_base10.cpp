#include "key_base10.h"
#include "resource_manager.h"

CKeyBase10::CKeyBase10(QWidget *parent) :
    CKeyBase(parent)
{

    m_iViewDir = VIEW_DIR_NORMAL;    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT//VIEW_DIR_R180

    KeyBtnInit();

    KeyBtnSlotInit();

}

void CKeyBase10::KeyBtnInit()
{

    pBtnGroup[MENU10_BTN_LEFT1] = new CButtonStable(this);
    pBtnGroup[MENU10_BTN_LEFT1]->setGeometry(SYS_WID(0), 0, SYS_WID(94), SYS_HEI(114));

    pBtnGroup[MENU10_BTN_LEFT2] = new CButtonStable(this);
    pBtnGroup[MENU10_BTN_LEFT2]->setGeometry(SYS_WID(94), 0, SYS_WID(94), SYS_HEI(114));

    pBtnGroup[MENU10_BTN_LEFT3] = new CButtonStable(this);
    pBtnGroup[MENU10_BTN_LEFT3]->setGeometry(SYS_WID(188), 0, SYS_WID(94), SYS_HEI(114));

    pBtnGroup[MENU10_BTN_LEFT4] = new CButtonStable(this);
    pBtnGroup[MENU10_BTN_LEFT4]->setGeometry(SYS_WID(282), 0, SYS_WID(94), SYS_HEI(114));

    pBtnGroup[MENU10_BTN_RIGHT1] = new CButtonStable(this);
    pBtnGroup[MENU10_BTN_RIGHT1]->setGeometry(0, SYS_HEI(486), SYS_WID(94), SYS_HEI(114));

    pBtnGroup[MENU10_BTN_RIGHT2] = new CButtonStable(this);
    pBtnGroup[MENU10_BTN_RIGHT2]->setGeometry(SYS_WID(94), SYS_HEI(486), SYS_WID(94), SYS_HEI(114));

    pBtnGroup[MENU10_BTN_RIGHT3] = new CButtonStable(this);
    pBtnGroup[MENU10_BTN_RIGHT3]->setGeometry(SYS_WID(188), SYS_HEI(486), SYS_WID(94), SYS_HEI(114));

    pBtnGroup[MENU10_BTN_RIGHT4] = new CButtonStable(this);
    pBtnGroup[MENU10_BTN_RIGHT4]->setGeometry(SYS_WID(282), SYS_HEI(486), SYS_WID(94), SYS_HEI(114));

}

void CKeyBase10::KeyBtnSlotInit()
{

    if(!g_dbsys.utility.mScreenKeyEnable)
        return;

    for(int mIdx = MENU10_BTN_LEFT1 ; mIdx <= MENU10_BTN_RIGHT4 ; mIdx++)
    {
        connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(motionKeyPressed()));
        connect(pBtnGroup[mIdx],SIGNAL(released()),this,SLOT(motionKeyReleased()));
        pBtnGroup[mIdx]->setFocusPolicy(Qt::NoFocus);
    }
}

void CKeyBase10::OnViewDirChange(int viewerDir)
{

    for(int mIdx = 0 ;mIdx < m_iSoftKeyMax ; mIdx++)
    {
        if(pBtnGroup[mIdx]->isDown())
        {
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(mIdx * MENU10_BTN_KEY_STEP + viewerDir*2 +MENU10_BTN_BASE + 1));
        }else
        {
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(mIdx * MENU10_BTN_KEY_STEP + viewerDir*2 + MENU10_BTN_BASE));
        }
    }

    m_iViewDir = viewerDir;
}
void CKeyBase10::motionKeyPressed()
{
    //关闭自运行
    g_systemDb->SetAutoRun(false);

    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
        {

            pBtnGroup[mIdx]->setStyleSheet( g_skinBase->GetStyleMapStr(mIdx * MENU10_BTN_KEY_STEP + m_iViewDir * 2 + MENU10_BTN_BASE + 1));

            emit ViewChange(VIEW_MOTION);
            SendCmdKey(keyBtnDown[mIdx]);
            break;
        }
    }
}
void CKeyBase10::motionKeyReleased()
{

    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
        {
            pBtnGroup[mIdx]->setStyleSheet( g_skinBase->GetStyleMapStr(mIdx * MENU10_BTN_KEY_STEP + m_iViewDir * 2 + MENU10_BTN_BASE));

            SendCmdKey(keyBtnUp[mIdx]);
            break;
        }
    }
}

