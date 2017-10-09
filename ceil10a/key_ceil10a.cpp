#include "key_ceil10a.h"
#include "resource_manager.h"

CKeyCeil10a::CKeyCeil10a(QWidget *parent) :
    CKeyBase10(parent)
{

    setObjectName("CKeyCeil10a");

    resize(SYS_WID(380),SYS_HEI(600));

    m_iSoftKeyMax = CEIL10_A_KEY_SCREEN;

    keyCodeInit();

    OnViewDirChange(m_iViewDir);
}

void CKeyCeil10a::keyCodeInit()
{
    //为按键赋值键码，支持配置文件重新定义键码。
    keyBtnDown[0]   = g_systemDb->getSystemCfg("KEYMAP/0",0x0026).toInt();
    keyBtnDown[1]   = g_systemDb->getSystemCfg("KEYMAP/1",0x0024).toInt();
    keyBtnDown[2]   = g_systemDb->getSystemCfg("KEYMAP/2",0x0036).toInt();
    keyBtnDown[3]   = g_systemDb->getSystemCfg("KEYMAP/3",0x0034).toInt();
    keyBtnDown[4]   = g_systemDb->getSystemCfg("KEYMAP/4",0x002A).toInt();
    keyBtnDown[5]   = g_systemDb->getSystemCfg("KEYMAP/5",0x0028).toInt();
    keyBtnDown[6]   = g_systemDb->getSystemCfg("KEYMAP/6",0x0022).toInt();
    keyBtnDown[7]   = g_systemDb->getSystemCfg("KEYMAP/7",0x0020).toInt();

    //判断左右手配置
    if(g_systemDb->getSystemCfg("utility/mDetectorStandDir",0).toInt() == DETECTOR_STAND_RIGHT)
    {
        std::swap(keyBtnDown[0],keyBtnDown[1]);
        std::swap(keyBtnDown[4],keyBtnDown[5]);
    }

    //赋值按键抬起键码
    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        keyBtnUp[mIdx] = keyBtnDown[mIdx] + 1;
    }
}
