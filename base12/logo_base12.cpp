#include "title_base12.h"
#include "resource_manager.h"

CTitleBase12::CTitleBase12(QWidget *parent) :
    CTitleBase(parent)
{

    QFont font;
    font.setPixelSize(SYS_FONT(16));
    pLabelList[TITLE_IDX_TIME]->setFont(font);

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,20,0)");
    }

}

void CTitleBase12::OnViewDirChange(int )
{

}
