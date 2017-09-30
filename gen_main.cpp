#include "gen_main.h"
#include "resource_manager.h"

CGenMain::CGenMain(int mPf,QWidget *parent) :
    QWidget(parent)
{

    setObjectName("CGenMain");

    frame = new QFrame(this);

    QFont font;
    font.setPixelSize(SYS_FONT(26));

    for(int mIdx = 0 ; mIdx < GEN_BTN_MAX ; mIdx++)
    {
        pBtnGroup[mIdx] = new CButtonStable(this);
        pBtnGroup[mIdx]->setFont(font);
        pBtnGroup[mIdx]->setFocusPolicy(Qt::NoFocus);
        pBtnGroup[mIdx]->raise();
        pBtnGroup[mIdx]->setFlat(true);
        connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnParameterPressed()));
    }

    pBtnGroup[GEN_BTN_AEC]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_AEC_50));
    pBtnGroup[GEN_BTN_FOCUS]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_FSMALL_01"));
    pBtnGroup[GEN_BTN_KV]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_GEN_KV"));
    pBtnGroup[GEN_BTN_MAS]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_GEN_MAS"));
    pBtnGroup[GEN_BTN_MA]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_GEN_MA"));
    pBtnGroup[GEN_BTN_MS]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_GEN_MS"));

    m_iTechButtonShow[SYS_TECH_AEC][GEN_BTN_KV]       = 1;
    m_iTechButtonShow[SYS_TECH_AEC][GEN_BTN_FOCUS]    = SYS_FOCUS_LARGE;
    m_iTechButtonShow[SYS_TECH_AEC][GEN_BTN_AEC]      = 1;
    m_iTechButtonShow[SYS_TECH_AEC][GEN_BTN_MAS]      = 0;
    m_iTechButtonShow[SYS_TECH_AEC][GEN_BTN_MA]       = 0;
    m_iTechButtonShow[SYS_TECH_AEC][GEN_BTN_MS]       = 0;

    m_iTechButtonShow[SYS_TECH_MAS][GEN_BTN_KV]       = 1;
    m_iTechButtonShow[SYS_TECH_MAS][GEN_BTN_FOCUS]    = SYS_FOCUS_LARGE;
    m_iTechButtonShow[SYS_TECH_MAS][GEN_BTN_AEC]      = 0;
    m_iTechButtonShow[SYS_TECH_MAS][GEN_BTN_MAS]      = 1;
    m_iTechButtonShow[SYS_TECH_MAS][GEN_BTN_MA]       = 0;
    m_iTechButtonShow[SYS_TECH_MAS][GEN_BTN_MS]       = 0;

    m_iTechButtonShow[SYS_TECH_MAMS][GEN_BTN_KV]      = 1;
    m_iTechButtonShow[SYS_TECH_MAMS][GEN_BTN_FOCUS]   = SYS_FOCUS_LARGE;
    m_iTechButtonShow[SYS_TECH_MAMS][GEN_BTN_AEC]     = 0;
    m_iTechButtonShow[SYS_TECH_MAMS][GEN_BTN_MAS]     = 0;
    m_iTechButtonShow[SYS_TECH_MAMS][GEN_BTN_MA]      = 1;
    m_iTechButtonShow[SYS_TECH_MAMS][GEN_BTN_MS]      = 1;

    for(int mIdx = 0 ; mIdx < GEN_BODY_MAX ;mIdx++)
    {
        pBtnBody[mIdx] = new CButtonStable(this);
        pBtnBody[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_GEN_RAD_01"));
        pBtnBody[mIdx]->setFlat(true);
        pBtnBody[mIdx]->setFocusPolicy(Qt::NoFocus);
        pBtnBody[mIdx]->setAutoDefault(false);
        pBtnBody[mIdx]->raise();
        connect(pBtnBody[mIdx],SIGNAL(pressed()),this,SLOT(OnBodyPressed()));
    }

    switch(mPf)
    {
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
    case PF_RAIL_12_A:

        resize( SYS_HEI(420), SYS_WID(420));

        pBtnGroup[GEN_BTN_KV]->setGeometry(SYS_HEI(300),    SYS_WID(20),SYS_HEI(100),SYS_WID(80));
        pBtnGroup[GEN_BTN_AEC]->setGeometry(SYS_HEI(300),   SYS_WID(220),SYS_HEI(100),SYS_WID(80));
        pBtnGroup[GEN_BTN_MAS]->setGeometry(SYS_HEI(300),   SYS_WID(220),SYS_HEI(100),SYS_WID(80));
        pBtnGroup[GEN_BTN_FOCUS]->setGeometry(SYS_HEI(300), SYS_WID(120),SYS_HEI(100),SYS_WID(80));
        pBtnGroup[GEN_BTN_MS]->setGeometry(SYS_HEI(300),    SYS_WID(320),SYS_HEI(100),SYS_WID(80));
        pBtnGroup[GEN_BTN_MA]->setGeometry(SYS_HEI(300),    SYS_WID(220),SYS_HEI(100),SYS_WID(80));

        pBtnBody[0]->setGeometry(SYS_HEI(165),  SYS_WID(10),SYS_HEI(65),SYS_WID(65));
        pBtnBody[1]->setGeometry(SYS_HEI(58),   SYS_WID(70),SYS_HEI(65),SYS_WID(65));
        pBtnBody[2]->setGeometry(SYS_HEI(125),  SYS_WID(79),SYS_HEI(65),SYS_WID(65));
        pBtnBody[3]->setGeometry(SYS_HEI(200),  SYS_WID(120),SYS_HEI(65),SYS_WID(65));
        pBtnBody[4]->setGeometry(SYS_HEI(125),  SYS_WID(147),SYS_HEI(65),SYS_WID(65));
        pBtnBody[5]->setGeometry(SYS_HEI(20),   SYS_WID(180),SYS_HEI(65),SYS_WID(65));
        pBtnBody[6]->setGeometry(SYS_HEI(160),  SYS_WID(220),SYS_HEI(65),SYS_WID(65));
        pBtnBody[7]->setGeometry(SYS_HEI(90),   SYS_WID(260),SYS_HEI(65),SYS_WID(65));
        pBtnBody[8]->setGeometry(SYS_HEI(160),  SYS_WID(310),SYS_HEI(65),SYS_WID(65));
        pBtnBody[9]->setGeometry(SYS_HEI(90),   SYS_WID(350),SYS_HEI(65),SYS_WID(65));

        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:

        resize( SYS_WID(420), SYS_HEI(420));

        pBtnGroup[GEN_BTN_KV]->setGeometry(SYS_WID(300),    SYS_HEI(20),SYS_WID(100),SYS_HEI(80));
        pBtnGroup[GEN_BTN_AEC]->setGeometry(SYS_WID(300),   SYS_HEI(220),SYS_WID(100),SYS_HEI(80));
        pBtnGroup[GEN_BTN_MAS]->setGeometry(SYS_WID(300),   SYS_HEI(220),SYS_WID(100),SYS_HEI(80));
        pBtnGroup[GEN_BTN_FOCUS]->setGeometry(SYS_WID(300), SYS_HEI(120),SYS_WID(100),SYS_HEI(80));
        pBtnGroup[GEN_BTN_MS]->setGeometry(SYS_WID(300),    SYS_HEI(320),SYS_WID(100),SYS_HEI(80));
        pBtnGroup[GEN_BTN_MA]->setGeometry(SYS_WID(300),    SYS_HEI(220),SYS_WID(100),SYS_HEI(80));

        pBtnBody[0]->setGeometry(SYS_WID(165),  SYS_HEI(10),SYS_WID(65),SYS_HEI(65));
        pBtnBody[1]->setGeometry(SYS_WID(58),   SYS_HEI(70),SYS_WID(65),SYS_HEI(65));
        pBtnBody[2]->setGeometry(SYS_WID(125),  SYS_HEI(79),SYS_WID(65),SYS_HEI(65));
        pBtnBody[3]->setGeometry(SYS_WID(200),  SYS_HEI(120),SYS_WID(65),SYS_HEI(65));
        pBtnBody[4]->setGeometry(SYS_WID(125),  SYS_HEI(147),SYS_WID(65),SYS_HEI(65));
        pBtnBody[5]->setGeometry(SYS_WID(20),   SYS_HEI(180),SYS_WID(65),SYS_HEI(65));
        pBtnBody[6]->setGeometry(SYS_WID(160),  SYS_HEI(220),SYS_WID(65),SYS_HEI(65));
        pBtnBody[7]->setGeometry(SYS_WID(90),   SYS_HEI(260),SYS_WID(65),SYS_HEI(65));
        pBtnBody[8]->setGeometry(SYS_WID(160),  SYS_HEI(310),SYS_WID(65),SYS_HEI(65));
        pBtnBody[9]->setGeometry(SYS_WID(90),   SYS_HEI(350),SYS_WID(65),SYS_HEI(65));

        break;
    default:
        break;
    }

    frame->resize(this->size());
    frame->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_GEN_BASE"));

    m_bCanDataSave = false;
    m_iBodyIdx = 2;
    m_iIconIdx = ICON_IDX_0;

    BodyParSet(m_iBodyIdx);

    timerRefresh = new QTimer(this);
    connect(timerRefresh,SIGNAL(timeout()),this,SLOT(OnFresh()));
    timerRefresh->setInterval(TIME_GEN_FRESH);

    setVisible(false);
}

void CGenMain::setGenForSave(bool bSave)
{
    m_bCanDataSave = bSave;
}
void CGenMain::OnGenTechChange(int iTech)
{
    for(int mIdx = 0 ;mIdx < GEN_BTN_MAX ;mIdx++)
    {
        pBtnGroup[mIdx]->setVisible(m_iTechButtonShow[iTech][mIdx]);
    }

    g_systemDb->m_sBodyBuf[m_iBodyIdx].mTech = iTech;

}
void CGenMain::OnFresh()
{

    if(m_iIconIdx == ICON_IDX_0)
    {
        pBtnBody[m_iBodyIdx]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_GEN_RAD_02"));
        m_iIconIdx = ICON_IDX_1;
        return;
    }

    if(m_iIconIdx == ICON_IDX_1)
    {
        pBtnBody[m_iBodyIdx]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_GEN_RAD_01"));
        m_iIconIdx = ICON_IDX_0;
        return;
    }
}

int CGenMain::GetGenKv()
{
    return g_systemDb->m_sBodyBuf[m_iBodyIdx].mKv;
}
void CGenMain::SetGenKv(int valKv)
{
    if(!pBtnGroup[GEN_BTN_KV])
        return;

    pBtnGroup[GEN_BTN_KV]->setText(CGenParam::mKvList[valKv]);
}
void CGenMain::BodyParSet(unsigned char idx)
{
    SetGenKv(g_systemDb->m_sBodyBuf[idx].mKv);
    SetGenMas(g_systemDb->m_sBodyBuf[idx].mMas);
    SetGenAec(g_systemDb->m_sBodyBuf[idx].mAec);
    SetGenFocus(g_systemDb->m_sBodyBuf[idx].mFocus);
    SetGenMa(g_systemDb->m_sBodyBuf[idx].mMa);
    SetGenMs(g_systemDb->m_sBodyBuf[idx].mMs);

    OnGenTechChange(g_systemDb->m_sBodyBuf[idx].mTech);
}
void CGenMain::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    emit BodyIndexChange(m_iBodyIdx);

    timerRefresh->start();
}
void CGenMain::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);

    timerRefresh->stop();
}
void CGenMain::OnBodyPressed()
{
    int mSenderIdx = -1;

    for(int mIdx = 0 ;mIdx < GEN_BODY_MAX;mIdx++)
    {
        if(sender() == pBtnBody[mIdx])
        {
            mSenderIdx = mIdx;
            break;
        }
    }
    if(mSenderIdx == -1)
        return;

    m_iBodyIdx = mSenderIdx;
    BodyParSet(m_iBodyIdx);

    emit BodyIndexChange(m_iBodyIdx);
}

void CGenMain::OnParameterPressed()
{

    if(sender() == pBtnGroup[GEN_BTN_FOCUS])
    {
        emit PopupShow(SYS_POPUP_FOCUS);
        return;
    }

    if(sender() == pBtnGroup[GEN_BTN_AEC])
    {
        emit PopupShow(SYS_POPUP_AEC);
        return;
    }

    if(sender() == pBtnGroup[GEN_BTN_KV])
    {
        emit ParamShow(SYS_POPUP_KV);
        return;
    }

    if(sender() == pBtnGroup[GEN_BTN_MAS])
    {
        emit ParamShow(SYS_POPUP_MAS);
        return;
    }

    if(sender() == pBtnGroup[GEN_BTN_MA])
    {
        emit ParamShow(SYS_POPUP_MA);
        return;
    }

    if(sender() == pBtnGroup[GEN_BTN_MS])
    {
        emit ParamShow(SYS_POPUP_MS);
        return;
    }
}

void CGenMain::OnGenAecChange(int aec)
{
    g_systemDb->m_sBodyBuf[m_iBodyIdx].mAec = aec;
    SetGenAec(aec);
}
void CGenMain::OnGenFocusChange(int focus)
{
    g_systemDb->m_sBodyBuf[m_iBodyIdx].mFocus = focus;
    SetGenFocus(focus);
}

void CGenMain::SetGenMas(int mMasNew)
{
    pBtnGroup[GEN_BTN_MAS]->setText(CGenParam::mMasList[mMasNew]);
}

void CGenMain::SetGenMa(int mMaNew)
{
    pBtnGroup[GEN_BTN_MA]->setText(CGenParam::mMaList[mMaNew]);
}

void CGenMain::SetGenMs(int mMsNew)
{
    pBtnGroup[GEN_BTN_MS]->setText(CGenParam::mMsList[mMsNew]);
}

void CGenMain::SetGenAec(int mAecNew)
{
    pBtnGroup[GEN_BTN_AEC]->setStyleSheet(g_skinBase->GetStyleMapStr(mAecNew * 2 + SYS_AEC_BASE));
}
void CGenMain::SetGenFocus(int mFocusNew)
{

    if(mFocusNew == SYS_FOCUS_SMALL)
        pBtnGroup[GEN_BTN_FOCUS]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_FSMALL_02"));

    if(mFocusNew == SYS_FOCUS_LARGE)
        pBtnGroup[GEN_BTN_FOCUS]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_FLARGE_02"));

}
void CGenMain::OnParamChange(int type,int val)
{
    switch(type)
    {
    case TYPE_KV:
        g_systemDb->m_sBodyBuf[m_iBodyIdx].mKv = val;
        SetGenKv(val);
        break;
    case TYPE_MA:
        g_systemDb->m_sBodyBuf[m_iBodyIdx].mMa = val;
        SetGenMa(val);
        break;
    case TYPE_MAS:
        g_systemDb->m_sBodyBuf[m_iBodyIdx].mMas = val;
        SetGenMas(val);
        break;
    case TYPE_MS:
        g_systemDb->m_sBodyBuf[m_iBodyIdx].mMs = val;
        SetGenMs(val);
        break;
    }

    emit BodyIndexChange(m_iBodyIdx);
}
void CGenMain::OnViewDirChange(int )
{
}
