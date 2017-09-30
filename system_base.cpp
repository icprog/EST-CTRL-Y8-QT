#include "system_base.h"
#include "resource_manager.h"

CSystemBase::CSystemBase(QWidget *parent) :
    QWidget(parent)
{

    textTitle = new QLabel(this);
    textTitle->setObjectName(QString::fromUtf8("textTitle"));
    textTitle->setGeometry(QRect(0, 0, 600, 50));
    textTitle->setAlignment(Qt::AlignCenter);

    lineTitleLeft = new QWidget(this);
    lineTitleLeft->setObjectName(QString::fromUtf8("lineTitle"));
    lineTitleLeft->setGeometry(QRect(50, 50, 500, 5));
    //lineTitleLeft->setStyleSheet("background-color : black");
    lineTitleLeft->setStyleSheet("background-color : rgb(255,232,166) ; border : 1px solid rgb(192,167,118)");

    lineBaseLeft = new QWidget(this);
    lineBaseLeft->setObjectName(QString::fromUtf8("lineBase"));
    lineBaseLeft->setGeometry(QRect(50, 500, 500, 5));
    //lineBaseLeft->setStyleSheet("background-color : black");
    lineBaseLeft->setStyleSheet("background-color : rgb(255,232,166) ; border : 1px solid rgb(192,167,118)");

    btnExit = new CButtonStable(this);
    btnExit->setObjectName(QString::fromUtf8("btnExit"));
    btnExit->setGeometry(QRect(250, 525, 100, 60));
    btnExit->setFocusPolicy(Qt::NoFocus);
    btnExit->setAutoDefault(false);
    btnExit->setStyleSheet("background-color : lightGray ; border : 2px solid black");
    btnExit->setText(QApplication::translate("CSystemBase", "EXIT"));

    setStyleSheet("background-color : lightGray");
}

void CSystemBase::showEvent(QShowEvent *)
{

    RsMgr->VisibleWidgetAdd(this);
}


void CSystemBase::hideEvent(QHideEvent *)
{

    RsMgr->VisibleWidgetDel(this);
}
