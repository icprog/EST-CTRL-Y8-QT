#include "main_uarm10.h"
#include "resource_manager.h"

CMainUarm10::CMainUarm10(QWidget *parent) :
    CMainBase10(parent)
{
    setObjectName("CMainUarm10");   //对象名

    resize(g_sysWidth,g_sysHeight); //大小

    this->setStyleSheet("background-color: black ");
}
