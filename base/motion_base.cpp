#include "motion_base.h"
#include "resource_manager.h"

CMotionBase::CMotionBase(QWidget *parent) :
    QWidget(parent)
{

    timerMotionFresh = new QTimer();
    connect(timerMotionFresh,SIGNAL(timeout()),this,SLOT(OnMotionFresh()));

    m_fLiftScalePre = 1;
    m_fLiftScaleCur = 0;

    setVisible(false);
}

void CMotionBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
    timerMotionFresh->start(TIME_MOTION_FRESH);
}

void CMotionBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
    timerMotionFresh->stop();
}
void CMotionBase::myMotionInit()
{
    sceneDet        = new QGraphicsScene(this);
    sceneTube      = new QGraphicsScene(this);

    viewTube = new QGraphicsView(this);
    viewTube->setFocusPolicy(Qt::NoFocus);
    viewTube->setFrameShape(QFrame::NoFrame);
    viewTube->setFrameShadow(QFrame::Plain);
    viewTube->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewTube->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //FullViewportUpdate//MinimalViewportUpdate//SmartViewportUpdate//BoundingRectViewportUpdate//NoViewportUpdate
    viewTube->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    viewTube->setStyleSheet("background:transparent");
    viewTube->show();

    viewDet = new QGraphicsView(this);
    viewDet->setFocusPolicy(Qt::NoFocus);
    viewDet->setFrameShape(QFrame::NoFrame);
    viewDet->setFrameShadow(QFrame::Plain);
    viewDet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewDet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewDet->setStyleSheet("background:transparent");
    viewDet->show();

}

void CMotionBase::OnMotionFresh()
{

}
void CMotionBase::mousePressEvent(QMouseEvent */*event*/)
{
    qDebug()<<"CNetBase::mousePressEvent";
}
void CMotionBase::OnViewDirChange(int )
{
}
