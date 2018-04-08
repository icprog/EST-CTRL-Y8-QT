#include "quick_rail12a.h"
#ifdef USE_CEIL_12_A

CQuickCeil12a::CQuickCeil12a(QWidget *parent) :
    CQuickBase12(parent)
{
    setObjectName("CQuickCeil12a");

    pCodeQuickDown.append(0x0058);
    pCodeQuickDown.append(0x0058);
    pCodeQuickDown.append(0x0057);

    pCodeQuickLong.append(SmartPos01);
    pCodeQuickLong.append(SmartPos05);
    pCodeQuickLong.append(SmartPos07);

    QList <QRect> pRect;

    //normal
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirNORM/Btn00",QRect(SYS_HEI(110),SYS_WID(50),   SYS_HEI(111),SYS_WID(73))).toRect());
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirNORM/Btn01",QRect(SYS_HEI(109),SYS_WID(128),  SYS_HEI(111),SYS_WID(73))).toRect());
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirNORM/Btn02",QRect(SYS_HEI(109),SYS_WID(204),  SYS_HEI(111),SYS_WID(73))).toRect());
    pRectQuickBtn.append(pRect);

    //left
    pRect.clear();
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirLEFT/Btn00",QRect(SYS_WID(2),  SYS_HEI(130),  SYS_WID(111),SYS_HEI(73))).toRect());
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirLEFT/Btn01",QRect(SYS_WID(110),SYS_HEI(131),  SYS_WID(111),SYS_HEI(73))).toRect());
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirLEFT/Btn02",QRect(SYS_WID(219),SYS_HEI(130),  SYS_WID(111),SYS_HEI(73))).toRect());
    pRectQuickBtn.append(pRect);

    //right
    pRect.clear();
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirRIGHT/Btn00",QRect(SYS_WID(2),  SYS_HEI(130),  SYS_WID(111),SYS_HEI(73))).toRect());
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirRIGHT/Btn01",QRect(SYS_WID(110),SYS_HEI(131),  SYS_WID(111),SYS_HEI(73))).toRect());
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirRIGHT/Btn02",QRect(SYS_WID(219),SYS_HEI(130),  SYS_WID(111),SYS_HEI(73))).toRect());
    pRectQuickBtn.append(pRect);

    //reverse
    pRect.clear();
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirREVERSE/Btn00",QRect(SYS_HEI(110),SYS_WID(50),   SYS_HEI(111),SYS_WID(73))).toRect());
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirREVERSE/Btn01",QRect(SYS_HEI(109),SYS_WID(128),  SYS_HEI(111),SYS_WID(73))).toRect());
    pRect.append(g_sysDb->value("CQuickCeil12a/VDirREVERSE/Btn02",QRect(SYS_HEI(109),SYS_WID(204),  SYS_HEI(111),SYS_WID(73))).toRect());
    pRectQuickBtn.append(pRect);

    pRectQuickWid.append(g_sysDb->value("CQuickCeil12a/Geometry/NORMAL",QRect(0,0,SYS_HEI(330),SYS_WID(330))).toRect());
    pRectQuickWid.append(g_sysDb->value("CQuickCeil12a/Geometry/LEFT",QRect(0,0,SYS_WID(330),SYS_HEI(330))).toRect());
    pRectQuickWid.append(g_sysDb->value("CQuickCeil12a/Geometry/RIGHT",QRect(0,0,SYS_WID(330),SYS_HEI(330))).toRect());
    pRectQuickWid.append(g_sysDb->value("CQuickCeil12a/Geometry/REVERSE",QRect(0,0,SYS_HEI(330),SYS_WID(330))).toRect());

    quickBtnInit(3);

    OnViewDirChange(g_sysDb->g_startAngle);

}

void CQuickCeil12a::quickBtnInit(uchar keyCount)
{
    CQuickBase12::quickBtnInit(keyCount);


}
void CQuickCeil12a::quickPressed()
{

    //通过配置文件，关闭快捷运动按钮
    if(g_sysDb->value("isQuickEnable",true).toInt() == false)
        return;

    if(sender() == pQuickBtnList[QUICK_BTN_00])
    {
        SendCmdKey(pCodeQuickDown[QUICK_BTN_00]);

        m_iQuickIdx = QUICK_BTN_00;
        timerLongPress->start();

        pQuickBtnList[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_00"));
        pQuickBtnList[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_03"));
        pQuickBtnList[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_05"));

    }

    if(sender() == pQuickBtnList[QUICK_BTN_01])
    {
        SendCmdKey(pCodeQuickDown[QUICK_BTN_01]);

        m_iQuickIdx = QUICK_BTN_01;
        timerLongPress->start();

        pQuickBtnList[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_01"));
        pQuickBtnList[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_02"));
        pQuickBtnList[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_05"));

    }

    if(sender() == pQuickBtnList[QUICK_BTN_02])
    {
        SendCmdKey(pCodeQuickDown[QUICK_BTN_02]);

        pQuickBtnList[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_01"));
        pQuickBtnList[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_03"));
        pQuickBtnList[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_04"));
    }

}

//快捷状态改变
void CQuickCeil12a::OnStatusChange(int pos )
{

    switch(pos)
    {
    case SmartPos00:
        pQuickBtnList[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_01"));
        pQuickBtnList[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_03"));
        pQuickBtnList[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_05"));
        break;
    case SmartPos01:
    case SmartPos02:
        pQuickBtnList[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_00"));
        pQuickBtnList[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_03"));
        pQuickBtnList[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_05"));
        break;
    case SmartPos03:
    case SmartPos04:
        pQuickBtnList[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_00"));
        pQuickBtnList[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_03"));
        pQuickBtnList[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_04"));
        break;
    case SmartPos05:
        pQuickBtnList[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_01"));
        pQuickBtnList[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_02"));
        pQuickBtnList[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_05"));
        break;
    case SmartPos06:
        pQuickBtnList[QUICK_BTN_00]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_01"));
        pQuickBtnList[QUICK_BTN_01]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_02"));
        pQuickBtnList[QUICK_BTN_02]->setStyleSheet(g_skinBase->GetStyleMapStr("QUICK_STR_SMART_04"));
        break;
    }
}

#endif
