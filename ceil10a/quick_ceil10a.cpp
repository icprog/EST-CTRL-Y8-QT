#include "quick_ceil10a.h"

#include "resource_manager.h"

CQuickCeil10a::CQuickCeil10a(QWidget *parent) :
    CQuickBase10(parent)
{
    setObjectName("CQuickCeil10a");

    m_codeQuickDown[QUICK_BTN_00] = 0x0058;
    m_codeQuickDown[QUICK_BTN_01] = 0x0058;
    m_codeQuickDown[QUICK_BTN_02] = 0x0058;

    m_codeQuickLong[QUICK_BTN_00] = 0x0050;
    m_codeQuickLong[QUICK_BTN_01] = 0x0055;
    m_codeQuickLong[QUICK_BTN_02] = 0x0054;

}

