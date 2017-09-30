#include "status_base8.h"

CStatusBase8::CStatusBase8(QWidget *parent) :
    CStatusBase(parent)
{

    //设置背景色
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(208,235,245));
    setPalette(pal);
}
