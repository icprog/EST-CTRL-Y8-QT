#include "title_base.h"

#include "resource_manager.h"

CTitleBase::CTitleBase(QWidget *parent) :
    QWidget(parent)
{

    timerTitleFresh = new QTimer(this);
    connect(timerTitleFresh,SIGNAL(timeout()),this,SLOT(OnTitleFresh()));
    timerTitleFresh->setInterval(TIME_INFO_FRESH);

}

void CTitleBase::showEvent(QShowEvent *)
{
    timerTitleFresh->start();
    RsMgr->VisibleWidgetAdd(this);
}
void CTitleBase::hideEvent(QHideEvent *)
{
    timerTitleFresh->stop();
    RsMgr->VisibleWidgetDel(this);
}
void CTitleBase::OnTitleFresh()
{
}
void CTitleBase::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"CTitleBase::mousePressEvent";

    if(event->type() == QEvent::MouseButtonPress)
    {
        unsigned short keyBuf[2];
        keyBuf[0] =0;
        keyBuf[1] = EMG_STOP_V1;
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
    }
}
void CTitleBase::OnViewDirChange(int)
{

}
