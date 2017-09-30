#include "key_rail12.h"
#include "resource_manager.h"

#define RAIL8_SOFT_KEY_MAX          ( 10 )

CKeyRail12::CKeyRail12(QWidget *parent) :
    CKeyBase12(parent)
{
    setObjectName("CKeyRail12");

    m_iSoftKeyMax = RAIL8_SOFT_KEY_MAX;

    KeyBtnInit();

    keyCodeInit();

    OnViewDirChange(g_systemDb->g_startAngle);

    KeyBtnSlotInit();

}

void CKeyRail12::keyCodeInit()
{
    //按键图标
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
    m_iIconList[16] = SYS_RUN_UP_3;
    m_iIconList[17] = SYS_RUN_UP_0;
    m_iIconList[18] = SYS_RUN_DOWN_3;
    m_iIconList[19] = SYS_RUN_DOWN_0;

    //下面代码消除按钮按下后留下的黑色边框
    pBtnGroup[0]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[1]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[2]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[3]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[4]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[5]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[6]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[7]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[8]->setFocusPolicy(Qt::NoFocus);
    pBtnGroup[9]->setFocusPolicy(Qt::NoFocus);

    //按键键码
    keyBtnDown[0] = g_systemDb->getSystemCfg("KEYMAP/0",0x0020).toInt();
    keyBtnDown[1] = g_systemDb->getSystemCfg("KEYMAP/1",0x0022).toInt();
    keyBtnDown[2] = g_systemDb->getSystemCfg("KEYMAP/2",0x0026).toInt();
    keyBtnDown[3] = g_systemDb->getSystemCfg("KEYMAP/3",0x0024).toInt();
    keyBtnDown[4] = g_systemDb->getSystemCfg("KEYMAP/4",0x002a).toInt();
    keyBtnDown[5] = g_systemDb->getSystemCfg("KEYMAP/5",0x0028).toInt();
    keyBtnDown[6] = g_systemDb->getSystemCfg("KEYMAP/6",0x002c).toInt();
    keyBtnDown[7] = g_systemDb->getSystemCfg("KEYMAP/7",0x002e).toInt();
    keyBtnDown[8] = g_systemDb->getSystemCfg("KEYMAP/8",0x0030).toInt();
    keyBtnDown[9] = g_systemDb->getSystemCfg("KEYMAP/9",0x0032).toInt();

    //左右手机
    if(g_systemDb->getSystemCfg("utility/mDetectorStandDir",0).toInt() == DETECTOR_STAND_RIGHT)
    {
        std::swap(keyBtnDown[2],keyBtnDown[3]);
        std::swap(keyBtnDown[4],keyBtnDown[5]);
    }

    //按键抬起键码
    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        keyBtnUp[mIdx] = keyBtnDown[mIdx] + 1;
    }
}

void CKeyRail12::OnViewDirChange(int viewPoint)
{
    /*
    //按键位置,初始界面
    pBtnGroup[0]->setGeometry(SYS_WID(26), SYS_HEI( 247),SYS_WID(108),SYS_HEI(108));
    pBtnGroup[1]->setGeometry(SYS_WID(134),SYS_HEI( 249),SYS_WID( 108),SYS_HEI( 108));
    pBtnGroup[2]->setGeometry(SYS_WID(28), SYS_HEI( 354),SYS_WID( 108),SYS_HEI(  92));
    pBtnGroup[3]->setGeometry(SYS_WID(133),SYS_HEI( 355),SYS_WID( 108),SYS_HEI( 92));
    pBtnGroup[4]->setGeometry(SYS_WID(363),SYS_HEI( 290),SYS_WID( 90),SYS_HEI( 143));
    pBtnGroup[5]->setGeometry(SYS_WID(272),SYS_HEI( 290),SYS_WID( 90),SYS_HEI( 143));
    pBtnGroup[6]->setGeometry(SYS_WID(495),SYS_HEI( 265),SYS_WID( 108),SYS_HEI( 92));
    pBtnGroup[7]->setGeometry(SYS_WID(513),SYS_HEI( 354),SYS_WID( 108),SYS_HEI( 92));
    pBtnGroup[8]->setGeometry(SYS_WID(589),SYS_HEI( 263),SYS_WID( 108),SYS_HEI( 108));
    pBtnGroup[9]->setGeometry(SYS_WID(602),SYS_HEI( 350),SYS_WID( 108),SYS_HEI( 108));
    */
    switch(viewPoint)
    {

    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(720),SYS_WID(720));
        pBtnGroup[0]->setGeometry(SYS_HEI(26), SYS_WID( 244),SYS_HEI(108),SYS_WID(108));
        pBtnGroup[1]->setGeometry(SYS_HEI(134),SYS_WID( 249),SYS_HEI( 108),SYS_WID( 108));
        pBtnGroup[2]->setGeometry(SYS_HEI(28), SYS_WID( 354),SYS_HEI( 108),SYS_WID(  92));
        pBtnGroup[3]->setGeometry(SYS_HEI(133),SYS_WID( 355),SYS_HEI( 108),SYS_WID( 92));
        pBtnGroup[4]->setGeometry(SYS_HEI(363),SYS_WID( 290),SYS_HEI( 90),SYS_WID( 143));
        pBtnGroup[5]->setGeometry(SYS_HEI(272),SYS_WID( 290),SYS_HEI( 90),SYS_WID( 143));
        pBtnGroup[6]->setGeometry(SYS_HEI(495),SYS_WID( 265),SYS_HEI( 108),SYS_WID( 92));
        pBtnGroup[7]->setGeometry(SYS_HEI(513),SYS_WID( 354),SYS_HEI( 108),SYS_WID( 92));
        pBtnGroup[8]->setGeometry(SYS_HEI(589),SYS_WID( 263),SYS_HEI( 108),SYS_WID( 108));
        pBtnGroup[9]->setGeometry(SYS_HEI(602),SYS_WID( 350),SYS_HEI( 108),SYS_WID( 108));
        frameAngleTube->setGeometry(SYS_HEI(262),SYS_WID( 263),SYS_HEI( 208),SYS_WID( 194));
        break;
    case VIEW_DIR_LEFT: //向左90度
        resize(SYS_WID(720),SYS_HEI(720));
        pBtnGroup[0]->setGeometry(SYS_WID(252),SYS_HEI( 101),SYS_WID(108),SYS_HEI(108));
        pBtnGroup[1]->setGeometry(SYS_WID(361),SYS_HEI( 105),SYS_WID( 108),SYS_HEI(  108));
        pBtnGroup[2]->setGeometry(SYS_WID(254),SYS_HEI( 203),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[3]->setGeometry(SYS_WID(361),SYS_HEI( 203),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[4]->setGeometry(SYS_WID(363),SYS_HEI( 300),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[5]->setGeometry(SYS_WID(273),SYS_HEI( 300),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[6]->setGeometry(SYS_WID(251),SYS_HEI( 446),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[7]->setGeometry(SYS_WID(361),SYS_HEI( 446),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[8]->setGeometry(SYS_WID(254),SYS_HEI( 525),SYS_WID( 108),SYS_HEI( 108));
        pBtnGroup[9]->setGeometry(SYS_WID(359),SYS_HEI( 524),SYS_WID( 108),SYS_HEI( 108));
        frameAngleTube->setGeometry(SYS_WID(257),SYS_HEI( 272),SYS_WID( 208),SYS_HEI( 194));
        break;
    case VIEW_DIR_RIGHT://向左90度
        resize(SYS_WID(720),SYS_HEI(720));
        pBtnGroup[0]->setGeometry(SYS_WID(252),SYS_HEI( 101),SYS_WID(108),SYS_HEI(108));
        pBtnGroup[1]->setGeometry(SYS_WID(361),SYS_HEI( 105),SYS_WID( 108),SYS_HEI(  108));
        pBtnGroup[2]->setGeometry(SYS_WID(254),SYS_HEI( 203),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[3]->setGeometry(SYS_WID(361),SYS_HEI( 203),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[4]->setGeometry(SYS_WID(363),SYS_HEI( 300),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[5]->setGeometry(SYS_WID(273),SYS_HEI( 300),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[6]->setGeometry(SYS_WID(251),SYS_HEI( 446),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[7]->setGeometry(SYS_WID(361),SYS_HEI( 446),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[8]->setGeometry(SYS_WID(254),SYS_HEI( 525),SYS_WID( 108),SYS_HEI( 108));
        pBtnGroup[9]->setGeometry(SYS_WID(359),SYS_HEI( 524),SYS_WID( 108),SYS_HEI( 108));
        frameAngleTube->setGeometry(SYS_WID(257),SYS_HEI( 272),SYS_WID( 208),SYS_HEI( 194));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;
    }
}
