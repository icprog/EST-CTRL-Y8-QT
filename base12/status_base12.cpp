#include "status_base12.h"
#include "resource_manager.h"

CStatusBase12::CStatusBase12(QWidget *parent) :
    CStatusBase(parent)
{

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        //设置背景色
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(208,235,100));
        setPalette(pal);
    }

    resize(SYS_WID(720),SYS_HEI(520));
}
