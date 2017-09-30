#include "fast_base.h"
#include "resource_manager.h"

CFastBase::CFastBase(QWidget *parent) :
    QWidget(parent)
{
    //初始化字体
    QFont font;
    font.setPixelSize(SYS_FONT(22));

    //快捷信息显示标签
    lbFastPosition = new QLabel(this);
    lbFastPosition->setFont(font);
    lbFastPosition->setAlignment(Qt::AlignCenter);

    lbFastPosition->setText(QApplication::translate("CFastBase", "Free Move."));

    //快捷动作触发按钮
    btMotionSmart = new CButtonStable(this);
    btMotionSmart->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_SMART_00"));
    btMotionSmart->setFlat(true);

    connect(btMotionSmart,SIGNAL(pressed()),this,SLOT(OnFastPressed()));

    setVisible(false);
}

//快捷触发按钮按下
void CFastBase::OnFastPressed()
{
    qDebug()<< "OnFastPressed";

    g_systemDb->SetAutoRun(false);          //停止自运行

    emit ViewChange(VIEW_MOTION);           //切换到动画界面
    emit PopupShow(SYS_POPUP_SMART);        //弹出快捷选择对话框

    emit SmartChange(SMART_POS_00);   //发出状态位置变化消息，让系统处于自由状态

}

//快捷状态改变
void CFastBase::OnStatusChange(int pos,QPushButton * pWid)
{

    btMotionSmart->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE + pos));

    if((pos == 0) || (pWid == 0))
    {
        lbFastPosition->setText(QApplication::translate("CFastBase", "Free Move."));
    }else
    {
        lbFastPosition->setText(pWid->text());
    }
}

void CFastBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

}
void CFastBase::hideEvent(QHideEvent *)
{

    RsMgr->VisibleWidgetDel(this);
}
void CFastBase::OnViewDirChange(int)
{


}
