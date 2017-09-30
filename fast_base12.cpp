#include "fast_base12.h"
#include "resource_manager.h"

CFastBase12::CFastBase12(QWidget *parent) :
    CFastBase(parent)
{
    setObjectName("CFastBase12");

    lbFastPosition->setGeometry(QRect(0, 0, 0, 0));

    OnViewDirChange(g_systemDb->g_startAngle);

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,0,208)");
    }

}

void CFastBase12::OnFastPressed()
{

    g_systemDb->SetAutoRun(false);          //停止自运行

    if(!g_systemDb->getPopSmartShowState())
    {
        emit ViewChange(VIEW_MOTION);           //切换到动画界面
        emit PopupShow(SYS_POPUP_SMART);        //弹出快捷选择对话框

        emit SmartChange(SMART_POS_00);   //发出状态位置变化消息，让系统处于自由状态

        g_systemDb->setPopSmartShowState(true);
    }else
    {

        emit PopupShow(SYS_POPUP_SMART_HIDE);

        g_systemDb->setPopSmartShowState(false);
    }

    btMotionSmart->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_STR_SMART_10));
}
//快捷状态改变
void CFastBase12::OnStatusChange(int pos,QPushButton * /*pWid*/)
{

    btMotionSmart->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_STR_SMART_10 + pos));

}
void CFastBase12::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(125),SYS_WID(124));
        btMotionSmart->setGeometry(SYS_HEI(0), SYS_WID(0), SYS_HEI(125), SYS_WID(124));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(125),SYS_HEI(124));
        btMotionSmart->setGeometry(SYS_WID(0), SYS_HEI(0), SYS_WID(125), SYS_HEI(124));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(125),SYS_HEI(124));
        btMotionSmart->setGeometry(SYS_WID(0), SYS_HEI(0), SYS_WID(125), SYS_HEI(124));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }
}
