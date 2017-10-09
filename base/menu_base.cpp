#include "menu_base.h"
#include "resource_manager.h"

CMenuBase::CMenuBase(QWidget *parent) :
    QWidget(parent)
{

    m_iViewMode     = VIEW_MOTION;          //VIEW_GEN//VIEW_MOTION
    m_iViewDir      = VIEW_DIR_NORMAL;    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT//VIEW_DIR_R180

    setVisible(false);
}

void CMenuBase::OnViewChange(int)
{

}
void CMenuBase::OnViewDirChange(int)
{

}

void CMenuBase::OnGenTechChange(int)
{

}
void CMenuBase::showEvent(QShowEvent *)
{

    RsMgr->VisibleWidgetAdd(this);

}
void CMenuBase::hideEvent(QHideEvent *)
{

    RsMgr->VisibleWidgetDel(this);
}

void CMenuBase::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"CMenuBase::mousePressEvent";
    if(event->type() == QEvent::MouseButtonPress)
    {
        EmergencyStop();
    }
}

void CMenuBase::EmergencyStop()
{

    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = EMG_STOP_V1;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);

}
