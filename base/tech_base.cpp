#include "tech_base.h"
#include "resource_manager.h"

CTechBase::CTechBase(QWidget *parent) :
    QWidget(parent)
{
    //初始化字体
    QFont font;
    font.setPixelSize(SYS_FONT(22));

    //初始化技术切换按钮
    for(int mIdx = SYS_TECH_MIN ; mIdx < SYS_TECH_MAX ; mIdx++ )
    {
        pBtnGroup[mIdx]   = new CButtonStable(this);
        connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnTechPressed()));
        pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_TECH_UP"));
        pBtnGroup[mIdx]->setFlat(true);
        pBtnGroup[mIdx]->setFont(font);
    }

    //初始化文字信息
    pBtnGroup[SYS_TECH_AEC]->setText("AEC");
    pBtnGroup[SYS_TECH_MAS]->setText("mAs");
    pBtnGroup[SYS_TECH_MAMS]->setText("mA/ms");
    pBtnGroup[SYS_TECH_AEC]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_TECH_DOWN"));
    m_iCurTech = SYS_TECH_AEC;

    setVisible(false);
}

//按钮按下
void CTechBase::OnTechPressed()
{
    g_systemDb->SetAutoRun(false);

    for(int mIdx = 0 ;mIdx < SYS_TECH_MAX ; mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
        {
            pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_TECH_DOWN"));
            pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_TECH_UP"));

            m_iCurTech = mIdx;
            emit GenTechChange(m_iCurTech);
            break;
        }
    }
}

void CTechBase::OnBodyIndexChange(int bodyIdx)
{
    if(bodyIdx < 0 ||  bodyIdx >= GEN_PAR_MAX )
        return;

    pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_TECH_UP"));
    m_iCurTech = g_systemDb->m_sBodyBuf[bodyIdx].mTech;
    pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_TECH_DOWN"));
}

void CTechBase::OnGenTechChange(int mTech)
{
    if(mTech < 0 ||  mTech >= SYS_TECH_MAX )
        return;

    pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_TECH_DOWN"));
    m_iCurTech = mTech;
    pBtnGroup[m_iCurTech]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_TECH_UP"));

}
void CTechBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
}
void CTechBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
void CTechBase::mousePressEvent(QMouseEvent */*event*/)
{
    qDebug()<<"CTechBase::mousePressEvent";
}
void CTechBase::OnViewDirChange(int)
{

}
