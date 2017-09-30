#include "key_ceil8.h"
#include "resource_manager.h"
#define CEIL8_SOFT_KEY_MAX      ( 10 )
CKeyCeil8::CKeyCeil8(QWidget *parent) :
    CKeyBase8(parent)
{
    setObjectName("CKeyCeil8");

    m_iSoftKeyMax = CEIL8_SOFT_KEY_MAX;

    resize(SYS_WID(150),SYS_HEI(375));

    KeyBtnInit();

    keyCodeInit();

    KeyBtnSlotInit();

}

void CKeyCeil8::keyCodeInit()
{
    //图标关联
    m_iIconList[0] = SYS_RUN_UP_1;
    m_iIconList[1] = SYS_RUN_UP_0;
    m_iIconList[2] = SYS_RUN_DOWN_1;
    m_iIconList[3] = SYS_RUN_DOWN_0;
    m_iIconList[4] = SYS_RUN_LEFT_1;
    m_iIconList[5] = SYS_RUN_LEFT_0;
    m_iIconList[6] = SYS_RUN_RIGHT_1;
    m_iIconList[7] = SYS_RUN_RIGHT_0;
    m_iIconList[8] = SYS_TURN_LEFT_1;
    m_iIconList[9] = SYS_TURN_LEFT_0;
    m_iIconList[10] = SYS_TURN_RIGHT_1;
    m_iIconList[11] = SYS_TURN_RIGHT_0;
    m_iIconList[12] = SYS_RUN_UP_2;
    m_iIconList[13] = SYS_RUN_UP_0;
    m_iIconList[14] = SYS_RUN_DOWN_2;
    m_iIconList[15] = SYS_RUN_DOWN_0;
    m_iIconList[16] = SYS_TURN_LEFT_2;
    m_iIconList[17] = SYS_TURN_LEFT_0;
    m_iIconList[18] = SYS_TURN_RIGHT_2;
    m_iIconList[19] = SYS_TURN_RIGHT_0;

    //按钮位置定义
    pBtnGroup[0]->setGeometry(SYS_WID(0),SYS_HEI( 0),SYS_WID(75),SYS_HEI(75));
    pBtnGroup[1]->setGeometry(SYS_WID(75),SYS_HEI( 0),SYS_WID( 75),SYS_HEI(  75));
    pBtnGroup[2]->setGeometry(SYS_WID(0),SYS_HEI( 75),SYS_WID( 75),SYS_HEI( 75));
    pBtnGroup[3]->setGeometry(SYS_WID(75),SYS_HEI( 75),SYS_WID( 75),SYS_HEI( 75));
    pBtnGroup[4]->setGeometry(SYS_WID(0),SYS_HEI( 150),SYS_WID( 75),SYS_HEI( 75));
    pBtnGroup[5]->setGeometry(SYS_WID(75),SYS_HEI( 150),SYS_WID( 75),SYS_HEI( 75));
    pBtnGroup[6]->setGeometry(SYS_WID(0),SYS_HEI( 225),SYS_WID( 75),SYS_HEI( 75));
    pBtnGroup[7]->setGeometry(SYS_WID(75),SYS_HEI( 225),SYS_WID( 75),SYS_HEI( 75));
    pBtnGroup[8]->setGeometry(SYS_WID(0),SYS_HEI( 300),SYS_WID( 75),SYS_HEI( 75));
    pBtnGroup[9]->setGeometry(SYS_WID(75),SYS_HEI( 300),SYS_WID( 75),SYS_HEI( 75));

    //按键键码定义
    keyBtnDown[0]   = g_systemDb->getSystemCfg("KEYMAP/0",0x0020).toInt();
    keyBtnDown[1]   = g_systemDb->getSystemCfg("KEYMAP/1",0x0022).toInt();
    keyBtnDown[2]   = g_systemDb->getSystemCfg("KEYMAP/2",0x0026).toInt();
    keyBtnDown[3]   = g_systemDb->getSystemCfg("KEYMAP/3",0x0024).toInt();
    keyBtnDown[4]   = g_systemDb->getSystemCfg("KEYMAP/4",0x002a).toInt();
    keyBtnDown[5]   = g_systemDb->getSystemCfg("KEYMAP/5",0x0028).toInt();
    keyBtnDown[6]   = g_systemDb->getSystemCfg("KEYMAP/6",0x002c).toInt();
    keyBtnDown[7]   = g_systemDb->getSystemCfg("KEYMAP/7",0x002e).toInt();
    keyBtnDown[8]   = g_systemDb->getSystemCfg("KEYMAP/8",0x0032).toInt();
    keyBtnDown[9]   = g_systemDb->getSystemCfg("KEYMAP/9",0x0030).toInt();

    //左右手机配置
    if(g_systemDb->getSystemCfg("utility/mDetectorStandDir",0).toInt() == DETECTOR_STAND_RIGHT)
    {
        std::swap(keyBtnDown[2],keyBtnDown[3]);
        std::swap(keyBtnDown[4],keyBtnDown[5]);
        std::swap(keyBtnDown[8],keyBtnDown[9]);
    }

    //抬起键码
    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        keyBtnUp[mIdx]      = keyBtnDown[mIdx] + 1;
    }

}

