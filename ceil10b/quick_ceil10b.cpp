#include "quick_ceil10b.h"

CQuickCeil10b::CQuickCeil10b(QWidget *parent) :
    CQuickBase10(parent)
{
    setObjectName("CQuickCeil10b");

    m_codeQuickDown[QUICK_BTN_00] = 0x0058;
    m_codeQuickDown[QUICK_BTN_01] = 0x0058;
    m_codeQuickDown[QUICK_BTN_02] = 0x0058;

    m_codeQuickLong[QUICK_BTN_00] = 0x0050;
    m_codeQuickLong[QUICK_BTN_01] = 0x0051;
    m_codeQuickLong[QUICK_BTN_02] = 0x0054;

}
