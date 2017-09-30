#include "button_stable.h"
#include "resource_manager.h"

CButtonStable::CButtonStable(QWidget *parent)
    :QPushButton(parent)
{
    setAutoFillBackground(true);
    setStyleSheet("background-color : lightGray ; border : 1px solid black");
}

void CButtonStable::mousePressEvent ( QMouseEvent * event)
{
    //如果MouseButtonPress消息，调用声音函数
    //发射按下消息
    if(event->type() == QEvent::MouseButtonPress)
    {
        emit pressed();
        RsMgr->g_filmBase->SetKeySound();
        event->accept();
    }else
    {
        QPushButton::mousePressEvent(event);
    }
}

void CButtonStable::mouseReleaseEvent ( QMouseEvent * event)
{
    //如果消息MouseButtonRelease，发射released消息
    if(event->type() == QEvent::MouseButtonRelease)
    {
        emit released();
        event->accept();
    }else
    {
        QPushButton::mouseReleaseEvent(event);
    }
}

void CButtonStable::mouseMoveEvent ( QMouseEvent * event)
{
    //不做任何事情
    event->accept();
}

void CButtonStable::mouseDoubleClickEvent ( QMouseEvent * event)
{
    //不做任何事情,
    event->accept();
}
