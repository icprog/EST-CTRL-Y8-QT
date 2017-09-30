#include "key_base.h"
#include "resource_manager.h"

CKeyBase::CKeyBase(QWidget *parent) :
    QWidget(parent)
{

    m_iSoftKeyMax = 0;

    setVisible(false);
}

void CKeyBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
}
void CKeyBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
void CKeyBase::mousePressEvent(QMouseEvent */*event*/)
{
    qDebug()<<"CKeyBase::mousePressEvent";
}
void CKeyBase::OnViewDirChange(int)
{

}
void CKeyBase::KeyBtnInit()
{

}
void CKeyBase::keyCodeInit()
{

}
void CKeyBase::KeyBtnSlotInit()
{

}

void CKeyBase::motionKeyPressed()
{

}
void CKeyBase::motionKeyReleased()
{

}
void CKeyBase::SendCmdKey(int mKey)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = mKey;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}
