#include "key_uarm10.h"
#include "resource_manager.h"

CKeyUarm10::CKeyUarm10(QWidget *parent) :
    CKeyBase10(parent)
{
    setObjectName("CKeyUarm10");

    m_iSoftKeyMax = CEIL10_A_KEY_SCREEN;

    OnViewDirChange(m_iViewDir);
}

void CKeyUarm10::keyCodeInit()
{

}

