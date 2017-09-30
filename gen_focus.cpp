#include "gen_focus.h"
#include "resource_manager.h"

CGenFocus::CGenFocus(int mPf,QWidget *parent) :
    QWidget(parent)
{

    setObjectName("CGenFocus");

    btFocusSmall = new CButtonStable(this);
    btFocusLarge = new CButtonStable(this);

    switch(mPf)
    {
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
    case PF_RAIL_12_A:
        resize(SYS_HEI(200),SYS_WID(100));
        btFocusSmall->setGeometry(SYS_HEI(0), SYS_WID(10), SYS_HEI(100), SYS_WID(80));
        btFocusLarge->setGeometry(SYS_HEI(100), SYS_WID(10), SYS_HEI(100), SYS_WID(80));
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        resize(SYS_WID(200),SYS_HEI(100));
        btFocusSmall->setGeometry(SYS_WID(0), SYS_HEI(10), SYS_WID(100), SYS_HEI(80));
        btFocusLarge->setGeometry(SYS_WID(100), SYS_HEI(10), SYS_WID(100), SYS_HEI(80));
        break;
    default:
        break;
    }

    btFocusSmall->setFlat(true);
    btFocusLarge->setFlat(true);

    connect(btFocusSmall,SIGNAL(pressed()),this,SLOT(OnFocusPressed()));
    connect(btFocusLarge,SIGNAL(pressed()),this,SLOT(OnFocusPressed()));

    m_iFocusIdx = SYS_FOCUS_SMALL;

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(128,127,216,235));
    setPalette(pal);

    setVisible(false);
}

void CGenFocus::showEvent(QShowEvent *)
{
    if(m_iFocusIdx == SYS_FOCUS_SMALL)
    {
        btFocusSmall->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_FSMALL_02"));
        btFocusLarge->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_FLARGE_01"));

    }else if(m_iFocusIdx == SYS_FOCUS_LARGE)
    {
        btFocusSmall->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_FSMALL_01"));
        btFocusLarge->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_FLARGE_02"));
    }

    RsMgr->VisibleWidgetAdd(this);
}
void CGenFocus::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}

void CGenFocus::OnBodyIndexChange(int bodyIdx)
{
    if(bodyIdx < 0 ||  bodyIdx >= GEN_PAR_MAX )
        return;

    m_iFocusIdx = g_systemDb->m_sBodyBuf[bodyIdx].mFocus;
}
void CGenFocus::OnFocusPressed()
{
    if(btFocusSmall == sender())
    {
        m_iFocusIdx = SYS_FOCUS_SMALL;
    }

    if(btFocusLarge == sender())
    {
        m_iFocusIdx = SYS_FOCUS_LARGE;
    }

    emit PopupHide(this);

    this->hide();
    emit GenFocusChange(m_iFocusIdx);

}
