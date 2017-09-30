#include "quick_base.h"
#include "resource_manager.h"


CQuickBase::CQuickBase(QWidget *parent) :
    QWidget(parent)
{
    m_iViewDir  = VIEW_DIR_NORMAL;
    m_iQuickIdx = QUICK_KEY_INVALID;

    for(int mIdx = 0 ; mIdx < QUICK_BTN_MAX ; mIdx++)
    {
        pBtnQuick[mIdx] = new CButtonStable(this);

        if(g_dbsys.utility.mScreenKeyEnable)
        {
            connect(pBtnQuick[mIdx],SIGNAL(pressed()),this,SLOT(quickPressed()));
            connect(pBtnQuick[mIdx],SIGNAL(released()),this,SLOT(quickReleased()));
        }
        pBtnQuick[mIdx]->setFocusPolicy(Qt::NoFocus);
    }

    timerLongPress = new QTimer();
    timerLongPress->setInterval(TIME_LONG_PRESS);
    timerLongPress->setSingleShot(true);
    connect(timerLongPress,SIGNAL(timeout()),this,SLOT(OnKeyLongPress()));

    setVisible(false);
}
void CQuickBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
}
void CQuickBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
void CQuickBase::mousePressEvent(QMouseEvent */*event*/)
{
     qDebug()<<"CSimBase::mousePressEvent";
}
void CQuickBase::quickBtnInit()
{

}
void CQuickBase::quickBtnSlotInit()
{

}
void CQuickBase::quickBtnViewInit()
{

}

void CQuickBase::quickPressed()
{

}
void CQuickBase::quickReleased()
{

}
void CQuickBase::OnViewDirChange(int)
{

}
//快捷状态改变
void CQuickBase::OnStatusChange(int,QPushButton *)
{

}
void CQuickBase::SendCmdKey(int mKey)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = mKey;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}
void CQuickBase::OnKeyLongPress()
{

    if(m_iQuickIdx < 0 || m_iQuickIdx >= QUICK_BTN_MAX)     //判断m_iQuickIdx位置，不能超出位置
        return;

    emit SmartChange( m_codeQuickLong[m_iQuickIdx]);     //发送一键命令给下位机

}
