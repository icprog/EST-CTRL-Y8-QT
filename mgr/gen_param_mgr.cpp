#include "qmath.h"
#include "gen_param_mgr.h"
#include "resource_manager.h"


#define FRAME_BASE_KV           ( 0 )
#define FRAME_BASE_MA           ( 7 )
#define FRAME_BASE_MS           ( 10 )
#define FRAME_BASE_MAS          ( 15 )

CGenParamMgr::CGenParamMgr(int mPf,QWidget *parent) :
    QWidget(parent)
{

    setObjectName("CGenParamMgr");

    btPre = new CButtonStable(this);
    btNext = new CButtonStable(this);

    connect(btNext, SIGNAL(pressed()),this,SLOT(OnPageChange()));
    connect(btPre,  SIGNAL(pressed()),this,SLOT(OnPageChange()));

    btNext->setFlat(true);
    btNext->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INDEX_NEXT"));

    btPre->setFlat(true);
    btPre->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INDEX_PRE"));

    switch(mPf)
    {
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
    case PF_RAIL_12_A:
        resize(SYS_HEI(305),SYS_WID(550));
        btPre->setGeometry(SYS_HEI(40), SYS_WID(470), SYS_HEI(100), SYS_WID(75));
        btNext->setGeometry(SYS_HEI(170), SYS_WID(470), SYS_HEI(100), SYS_WID(75));
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        resize(SYS_WID(305),SYS_HEI(550));
        btPre->setGeometry(SYS_WID(40), SYS_HEI(470), SYS_WID(100), SYS_HEI(75));
        btNext->setGeometry(SYS_WID(170), SYS_HEI(470), SYS_WID(100), SYS_HEI(75));
        break;
    default:
        break;
    }

    for(int mIdx = 0 ; mIdx < GEN_KV_PAGE ; mIdx++)
    {
        m_iFrames[mIdx + FRAME_BASE_KV] = new CGenParam(mPf,TYPE_KV,mIdx,this);
        m_iFrames[mIdx + FRAME_BASE_KV]->move(0,0);
        m_iFrames[mIdx + FRAME_BASE_KV]->hide();
        connect(m_iFrames[mIdx + FRAME_BASE_KV],SIGNAL(ParamChange(int,int)),this,SLOT(OnParamChange(int,int)));
        connect(m_iFrames[mIdx + FRAME_BASE_KV],SIGNAL(ParamChange(int,int)),g_GenMain,SLOT(OnParamChange(int,int)));
        connect(m_iFrames[mIdx + FRAME_BASE_KV],SIGNAL(ParamChange(int,int)),g_genClient,SLOT(OnParamChange(int,int)));
    }

    for(int mIdx = 0 ; mIdx < GEN_MA_PAGE ; mIdx++)
    {
        m_iFrames[mIdx + FRAME_BASE_MA] = new CGenParam(mPf,TYPE_MA,mIdx,this);
        m_iFrames[mIdx + FRAME_BASE_MA]->move(0,0);
        m_iFrames[mIdx + FRAME_BASE_MA]->hide();
        connect(m_iFrames[mIdx + FRAME_BASE_MA],SIGNAL(ParamChange(int,int)),this,SLOT(OnParamChange(int,int)));
        connect(m_iFrames[mIdx + FRAME_BASE_MA],SIGNAL(ParamChange(int,int)),g_GenMain,SLOT(OnParamChange(int,int)));
        connect(m_iFrames[mIdx + FRAME_BASE_MA],SIGNAL(ParamChange(int,int)),g_genClient,SLOT(OnParamChange(int,int)));
    }

    for(int mIdx = 0 ; mIdx < GEN_MAS_PAGE ; mIdx++)
    {
        m_iFrames[mIdx + FRAME_BASE_MAS] = new CGenParam(mPf,TYPE_MAS,mIdx,this);
        m_iFrames[mIdx + FRAME_BASE_MAS]->move(0,0);
        m_iFrames[mIdx + FRAME_BASE_MAS]->hide();
        connect(m_iFrames[mIdx + FRAME_BASE_MAS],SIGNAL(ParamChange(int,int)),this,SLOT(OnParamChange(int,int)));
        connect(m_iFrames[mIdx + FRAME_BASE_MAS],SIGNAL(ParamChange(int,int)),g_GenMain,SLOT(OnParamChange(int,int)));
        connect(m_iFrames[mIdx + FRAME_BASE_MAS],SIGNAL(ParamChange(int,int)),g_genClient,SLOT(OnParamChange(int,int)));
    }

    for(int mIdx = 0 ; mIdx < GEN_MS_PAGE ; mIdx++)
    {
        m_iFrames[mIdx + FRAME_BASE_MS] = new CGenParam(mPf,TYPE_MS,mIdx,this);
        m_iFrames[mIdx + FRAME_BASE_MS]->move(0,0);
        m_iFrames[mIdx + FRAME_BASE_MS]->hide();
        connect(m_iFrames[mIdx + FRAME_BASE_MS],SIGNAL(ParamChange(int,int)),this,SLOT(OnParamChange(int,int)));
        connect(m_iFrames[mIdx + FRAME_BASE_MS],SIGNAL(ParamChange(int,int)),g_GenMain,SLOT(OnParamChange(int,int)));
        connect(m_iFrames[mIdx + FRAME_BASE_MS],SIGNAL(ParamChange(int,int)),g_genClient,SLOT(OnParamChange(int,int)));
    }

    m_iPageKv       = 0;
    m_iPageMa       = 0;
    m_iPageMas      = 0;
    m_iPageMs       = 0;
    m_iPageDisplay  = 0;
    m_iPageNew      = 0;
    m_iPageKvLast   = 0;
    m_iPageMaLast   = 0;
    m_iPageMsLast   = 0;
    m_iPageMasLast  = 0;

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(128,127,216,235));
    setPalette(pal);

    setVisible(false);
}


void CGenParamMgr::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
}
void CGenParamMgr::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}

void CGenParamMgr::OnParamShow(int type)
{
    switch(type)
    {
    case SYS_POPUP_KV:
        ShowType(TYPE_KV);
        emit PopupShow(SYS_POPUP_PARAM);
        break;
    case SYS_POPUP_MAS:
        ShowType(TYPE_MAS);
        emit PopupShow(SYS_POPUP_PARAM);
        break;
    case SYS_POPUP_MA:
        ShowType(TYPE_MA);
        emit PopupShow(SYS_POPUP_PARAM);
        break;
    case SYS_POPUP_MS:
        ShowType(TYPE_MS);
        emit PopupShow(SYS_POPUP_PARAM);
        break;
    default:
        return;
    }
}

void CGenParamMgr::ShowType(int type)
{
    switch(type)
    {
    case TYPE_KV:
        m_iTypeCur  = TYPE_KV;
        m_iPageNew  = m_iPageKv + FRAME_BASE_KV;
        break;
    case TYPE_MA:
        m_iTypeCur = TYPE_MA;
        m_iPageNew  = m_iPageMa + FRAME_BASE_MA;
        break;
    case TYPE_MAS:
        m_iTypeCur = TYPE_MAS;
        m_iPageNew  = m_iPageMas + FRAME_BASE_MAS;
        break;
    case TYPE_MS:
        m_iTypeCur = TYPE_MS;
        m_iPageNew  = m_iPageMs + FRAME_BASE_MS;
        break;
    default:
        return;
    }

    if(m_iPageNew != m_iPageDisplay)
        m_iFrames[m_iPageDisplay]->setVisible(false);

    m_iFrames[m_iPageNew]->setVisible(true);
    m_iPageDisplay = m_iPageNew;
}

void CGenParamMgr::OnPageChange()
{
    if(sender() == btNext)
    {
        switch(m_iTypeCur)
        {
        case TYPE_KV:
            if(m_iPageKv < (GEN_KV_PAGE - 1))
                m_iPageKv++ ;
            break;
        case TYPE_MA:
            if(m_iPageMa < ( GEN_MA_PAGE - 1))
                m_iPageMa++ ;
            break;
        case TYPE_MAS:
            if(m_iPageMas < ( GEN_MAS_PAGE - 1))
                m_iPageMas++;
            break;
        case TYPE_MS:
            if(m_iPageMs < ( GEN_MS_PAGE - 1))
                m_iPageMs++;
            break;
        default:
            return;
        }
    }

    if(sender() == btPre)
    {

        switch(m_iTypeCur)
        {
        case TYPE_KV:
            if(m_iPageKv != 0)
                m_iPageKv--;
            break;
        case TYPE_MA:
            if(m_iPageMa != 0)
                m_iPageMa-- ;
            break;
        case TYPE_MAS:
            if(m_iPageMas != 0)
                m_iPageMas--;
            break;
        case TYPE_MS:
            if(m_iPageMs != 0)
                m_iPageMs--;
            break;
        default:
            return;
        }
    }

    ShowType(m_iTypeCur);
}

void CGenParamMgr::OnBodyIndexChange(int bodyIdx)
{
    if(bodyIdx < 0 ||  bodyIdx >= GEN_PAR_MAX )
        return;

    int mVal,mPage,mIdx;

    mVal    = g_systemDb->m_sBodyBuf[bodyIdx].mKv ;
    mPage   = qFloor(mVal / PARAM_MAX);
    mIdx    = mVal % PARAM_MAX ;
    m_iFrames[ m_iPageKvLast + FRAME_BASE_KV ]->KeyClear(0);
    m_iPageKv = mPage;
    m_iFrames[ m_iPageKv + FRAME_BASE_KV ]->KeySet(mIdx);
    m_iPageKvLast = m_iPageKv;

    mVal    = g_systemDb->m_sBodyBuf[bodyIdx].mMa ;
    mPage   = qFloor(mVal / PARAM_MAX);
    mIdx    = mVal % PARAM_MAX ;
    m_iFrames[ m_iPageMaLast + FRAME_BASE_MA ]->KeyClear(0);
    m_iPageMa = mPage;
    m_iFrames[ m_iPageMa + FRAME_BASE_MA ]->KeySet(mIdx);
    m_iPageMaLast = m_iPageMa;

    mVal    = g_systemDb->m_sBodyBuf[bodyIdx].mMs ;
    mPage   = qFloor(mVal/ PARAM_MAX);
    mIdx    = mVal % PARAM_MAX ;
    m_iFrames[ m_iPageMsLast + FRAME_BASE_MS ]->KeyClear(0);
    m_iPageMs = mPage;
    m_iFrames[ m_iPageMs + FRAME_BASE_MS ]->KeySet(mIdx);
    m_iPageMsLast = m_iPageMs;

    mVal    = g_systemDb->m_sBodyBuf[bodyIdx].mMas ;
    mPage   = qFloor(mVal / PARAM_MAX);
    mIdx    = mVal % PARAM_MAX ;
    m_iFrames[ m_iPageMasLast + FRAME_BASE_MAS ]->KeyClear(0);
    m_iPageMas = mPage;
    m_iFrames[ m_iPageMas + FRAME_BASE_MAS ]->KeySet(mIdx);
    m_iPageMasLast = m_iPageMas;
}

void CGenParamMgr::OnParamChange(int type,int )
{
    emit PopupHide(this);

    this->hide();

    if(type < 0 || type >= PARAM_TYPE_MAX)
        return;

}
