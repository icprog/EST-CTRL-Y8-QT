#include "fast_ceil10b.h"

#include "resource_manager.h"

CFastCeil10b::CFastCeil10b(QWidget *parent) :
    CFastBase10(parent)
{
}
//快捷触发按钮按下
void CFastCeil10b::OnFastPressed()
{
    g_systemDb->SetAutoRun(false);          //停止自运行

    emit ViewChange(VIEW_MOTION);           //切换到动画界面
    emit PopupShow(SYS_POPUP_SMART);        //弹出快捷选择对话框

    emit SmartChange(SMART_POS_07);   //发出状态位置变化消息，让系统处于自由状态

}

//快捷状态改变
void CFastCeil10b::OnStatusChange(int pos,QPushButton * pWid)
{

    btMotionSmart->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE + pos));

    if((pos == 7) || (pWid == 0))
    {
        lbFastPosition->setText(QApplication::translate("CFastBase", "Free Move."));
    }else
    {
        lbFastPosition->setText(pWid->text());
    }
}
