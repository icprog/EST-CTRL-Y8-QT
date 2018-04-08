#include "tech_rail08b.h"
#include "resource_manager.h"

CTechRail08b::CTechRail08b(QWidget *parent) :
    CTechBase8(parent)
{
    setObjectName("CTechRail08b");

    OnViewDirChange(g_systemDb->g_startAngle);

    pBtnGroup[SYS_TECH_AEC]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_OFF"));
    pBtnGroup[SYS_TECH_MAS]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_OFF"));
    pBtnGroup[SYS_TECH_MAMS]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_OFF"));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,20,0)");
    }
}

//按钮按下
void CTechRail08b::OnTechPressed()
{
    g_systemDb->SetAutoRun(false);

    for(int mIdx = 0 ;mIdx < SYS_TECH_MAX ; mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
        {
            pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_OFF"));
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_ON"));

            m_iCurTech = mIdx;
            emit GenTechChange(m_iCurTech);
            break;
        }
    }
}

void CTechRail08b::OnBodyIndexChange(int bodyIdx)
{
    if(bodyIdx < 0 ||  bodyIdx >= GEN_PAR_MAX )
        return;

    pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_OFF"));
    m_iCurTech = g_systemDb->m_sBodyBuf[bodyIdx].mTech;
    pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_ON"));
}

void CTechRail08b::OnGenTechChange(int mTech)
{
    if(mTech < 0 ||  mTech >= SYS_TECH_MAX )
        return;

    pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_ON"));
    m_iCurTech = mTech;
    pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_SYSTEM_TECH_OFF"));

}
void CTechRail08b::OnViewDirChange(int viewPoint)
{
    switch(viewPoint)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(267),SYS_WID(267));
        pBtnGroup[SYS_TECH_AEC]->setGeometry(SYS_HEI(0),SYS_WID(98),   SYS_HEI(89),SYS_WID(69));
        pBtnGroup[SYS_TECH_MAS]->setGeometry(SYS_HEI(89),SYS_WID(98),  SYS_HEI(89),SYS_WID(69));
        pBtnGroup[SYS_TECH_MAMS]->setGeometry(SYS_HEI(178),SYS_WID(98),  SYS_HEI(89),SYS_WID(69));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(330),SYS_HEI(330));
        pBtnGroup[SYS_TECH_AEC]->setGeometry(SYS_WID(2),  SYS_HEI(130),  SYS_WID(111),SYS_HEI(73));
        pBtnGroup[SYS_TECH_MAS]->setGeometry(SYS_WID(110),SYS_HEI(131),  SYS_WID(111),SYS_HEI(73));
        pBtnGroup[SYS_TECH_MAMS]->setGeometry(SYS_WID(219),SYS_HEI(130),  SYS_WID(111),SYS_HEI(73));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(330),SYS_HEI(330));
        pBtnGroup[SYS_TECH_AEC]->setGeometry(SYS_WID(2),  SYS_HEI(130),  SYS_WID(111),SYS_HEI(73));
        pBtnGroup[SYS_TECH_MAS]->setGeometry(SYS_WID(110),SYS_HEI(131),  SYS_WID(111),SYS_HEI(73));
        pBtnGroup[SYS_TECH_MAMS]->setGeometry(SYS_WID(219),SYS_HEI(130),  SYS_WID(111),SYS_HEI(73));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;
    }
}
