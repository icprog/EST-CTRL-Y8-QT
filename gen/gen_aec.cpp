#include "gen_aec.h"
#include "resource_manager.h"

CGenAec::CGenAec(int mPf,QWidget *parent) :
    QWidget(parent)
{

    setObjectName("CGenAec");

    m_iCurAec = 5;

    for(int mIdx = 0 ; mIdx < GEN_AEC_MAX; mIdx++)
    {
        pBtnGroup[mIdx] = new CButtonStable(this);

        connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnBtnPress()));

        pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(mIdx * 2 + SYS_AEC_BASE));
        pBtnGroup[mIdx]->setFlat(true);
    }

    switch(mPf)
    {
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
    case PF_RAIL_12_A:

        resize(SYS_HEI(300),   SYS_WID(280));
        pBtnGroup[0]->setGeometry(SYS_HEI(0),   SYS_WID(10), SYS_HEI(100), SYS_WID(80));
        pBtnGroup[1]->setGeometry(SYS_HEI(0),   SYS_WID(100),SYS_HEI(100), SYS_WID(80));
        pBtnGroup[2]->setGeometry(SYS_HEI(100), SYS_WID(10), SYS_HEI(100), SYS_WID(80));
        pBtnGroup[3]->setGeometry(SYS_HEI(100), SYS_WID(100),SYS_HEI(100), SYS_WID(80));
        pBtnGroup[4]->setGeometry(SYS_HEI(100), SYS_WID(190),SYS_HEI(100), SYS_WID(80));
        pBtnGroup[5]->setGeometry(SYS_HEI(200), SYS_WID(10), SYS_HEI(100), SYS_WID(80));
        pBtnGroup[6]->setGeometry(SYS_HEI(200), SYS_WID(100),SYS_HEI(100), SYS_WID(80));

        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:

        resize(SYS_WID(300),   SYS_HEI(280));
        pBtnGroup[0]->setGeometry(SYS_WID(0),   SYS_HEI(10), SYS_WID(100), SYS_HEI(80));
        pBtnGroup[1]->setGeometry(SYS_WID(0),   SYS_HEI(100),SYS_WID(100), SYS_HEI(80));
        pBtnGroup[2]->setGeometry(SYS_WID(100), SYS_HEI(10), SYS_WID(100), SYS_HEI(80));
        pBtnGroup[3]->setGeometry(SYS_WID(100), SYS_HEI(100),SYS_WID(100), SYS_HEI(80));
        pBtnGroup[4]->setGeometry(SYS_WID(100), SYS_HEI(190),SYS_WID(100), SYS_HEI(80));
        pBtnGroup[5]->setGeometry(SYS_WID(200), SYS_HEI(10), SYS_WID(100), SYS_HEI(80));
        pBtnGroup[6]->setGeometry(SYS_WID(200), SYS_HEI(100),SYS_WID(100), SYS_HEI(80));

        break;
    default:
        break;
    }

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(128,127,216,235));
    setPalette(pal);

    setVisible(false);
}


void CGenAec::OnBtnPress()
{
    int mBtnIdx;
    for(mBtnIdx = 0 ; mBtnIdx < 7;  mBtnIdx++)
    {
        if(sender() == pBtnGroup[mBtnIdx] )
        {
            emit PopupHide(this);

            this->hide();
            emit GenAecChange(mBtnIdx);

            pBtnGroup[m_iCurAec]->setStyleSheet(g_skinBase->GetStyleMapStr(m_iCurAec * 2 + SYS_AEC_BASE));
            m_iCurAec =  mBtnIdx;
            pBtnGroup[m_iCurAec]->setStyleSheet(g_skinBase->GetStyleMapStr(m_iCurAec * 2 + SYS_AEC_BASE + 1));

            break;
        }
    }
}

void CGenAec::OnBodyIndexChange(int bodyIdx)
{
    if(bodyIdx < 0 ||  bodyIdx >= GEN_PAR_MAX )
        return;

    pBtnGroup[m_iCurAec]->setStyleSheet(g_skinBase->GetStyleMapStr(m_iCurAec * 2 + SYS_AEC_BASE));
    m_iCurAec =  g_systemDb->m_sBodyBuf[bodyIdx].mAec;
    pBtnGroup[m_iCurAec]->setStyleSheet(g_skinBase->GetStyleMapStr(m_iCurAec * 2 + SYS_AEC_BASE + 1));

}


void CGenAec::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
}
void CGenAec::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);

}
