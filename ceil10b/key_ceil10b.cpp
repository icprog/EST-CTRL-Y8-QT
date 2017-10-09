#include "key_ceil10b.h"
#include "resource_manager.h"

CKeyCeil10b::CKeyCeil10b(QWidget *parent) :
    CKeyBase10(parent)
{
    setObjectName("CKeyCeil10b");

    resize(SYS_WID(380),SYS_HEI(600));

    m_iSoftKeyMax = CEIL10_B_KEY_SCREEN;

    keyCodeInit();

    OnViewDirChange(m_iViewDir);
}

void CKeyCeil10b::keyCodeInit()
{

    keyBtnDown[0]   = g_systemDb->getSystemCfg("KEYMAP/0",0x0026).toInt();
    keyBtnDown[1]   = g_systemDb->getSystemCfg("KEYMAP/1",0x0024).toInt();
    keyBtnDown[2]   = g_systemDb->getSystemCfg("KEYMAP/2",0x002E).toInt();
    keyBtnDown[3]   = g_systemDb->getSystemCfg("KEYMAP/3",0x002C).toInt();
    keyBtnDown[4]   = g_systemDb->getSystemCfg("KEYMAP/4",0x002A).toInt();
    keyBtnDown[5]   = g_systemDb->getSystemCfg("KEYMAP/5",0x0028).toInt();
    keyBtnDown[6]   = g_systemDb->getSystemCfg("KEYMAP/6",0x0022).toInt();
    keyBtnDown[7]   = g_systemDb->getSystemCfg("KEYMAP/7",0x0020).toInt();

   if(g_systemDb->getSystemCfg("utility/mDetectorStandDir",0).toInt() == DETECTOR_STAND_RIGHT)
    {
        std::swap(keyBtnDown[0],keyBtnDown[1]);
        std::swap(keyBtnDown[4],keyBtnDown[5]);
    }

    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        keyBtnUp[mIdx] = keyBtnDown[mIdx] + 1;
    }
}

