#include "exit_base.h"
#include "resource_manager.h"

CExitBase::CExitBase(QWidget *parent) :
    QWidget(parent)
{

    pbSystemExit = new QPushButton(this);

    connect(pbSystemExit,SIGNAL(pressed()),this,SLOT(OnSystemExit()));
    pbSystemExit->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_ICON_EXIT"));
    pbSystemExit->show();

    setVisible(false);

}

void CExitBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
}
void CExitBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
void CExitBase::mousePressEvent(QMouseEvent */*event*/)
{
}
void CExitBase::OnSystemExit()
{   

    MySystem("exit");
}
void CExitBase::OnViewDirChange(int )
{
}
