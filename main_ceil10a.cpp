#include "main_ceil10a.h"
#include "resource_manager.h"

CMainCeil10a::CMainCeil10a(QWidget *parent) :
    CMainBase10(parent)
{
    setObjectName("CMainCeil10a");

    resize(g_sysWidth,g_sysHeight);

    this->setStyleSheet("background-color: black ");
}

