
#include "gen_config.h"
#include "resource_manager.h"

CGenConfig::CGenConfig(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("CGenConfig");

    resize(600,600);

    myPopupPosInit();

    m_lbTitle = new QLabel(this);
    m_lbTitle->setGeometry(QRect(0, 0, 450, 50));
    m_lbTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_lbTitle->setText(QApplication::translate("CGenConfig", "Exposure Parameter Configuration"));

    btSave = new CButtonStable(this);
    btSave->setGeometry(QRect(490, 390, 100, 70));
    btSave->setText(QApplication::translate("CGenConfig", "SAVE"));

    btExit = new CButtonStable(this);
    btExit->setGeometry(QRect(490, 480, 100, 70));
    btExit->setText(QApplication::translate("CGenConfig", "EXIT"));

    connect(btSave,SIGNAL(pressed()),this,SLOT(OnButtonClick()) );
    connect(btExit,SIGNAL(pressed()),this,SLOT(OnButtonClick()) );

    for(int mIdx = 0 ;mIdx < CFG_MAX_TECH ;mIdx++)
    {
        pBtnGroup[mIdx] = new CButtonStable(this);
        pBtnGroup[mIdx]->setGeometry(QRect(490, 80 + mIdx * 90, 100, 70));
        connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnGenTechChange()));
        pBtnGroup[mIdx]->setStyleSheet("background-color : lightGray");
    }

    pBtnGroup[0]->setText(QApplication::translate("CGenConfig", "AEC"));
    pBtnGroup[1]->setText(QApplication::translate("CGenConfig", "mAs"));
    pBtnGroup[2]->setText(QApplication::translate("CGenConfig", "mA/ms"));

    m_iLastTech = 0;
    pBtnGroup[m_iLastTech]->setStyleSheet("background-color : cyan");

    btExit->setStyleSheet( "QPushButton:focus{background-color:cyan}");
    setStyleSheet("background-color : lightGray");

    translateFontSize(this);

    setVisible(false);
}


void CGenConfig::OnGenTechChange()
{

    for(int mIdx = 0 ;mIdx < SYS_TECH_MAX;mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
        {

            pBtnGroup[mIdx]->setStyleSheet("background-color : cyan");

            if(m_iLastTech != mIdx)
                emit GenTechChange(mIdx);

            m_iLastTech = mIdx;
        }else
        {
            pBtnGroup[mIdx]->setStyleSheet("background-color : lightGray");
        }
    }
}

void CGenConfig::OnButtonClick()
{

    if(sender() == btExit )
    {
        viewPopup->hide();
        this->hide();
        emit ViewChange(VIEW_MAIN);
        return;
    }

    if(sender()== btSave)
    {
        g_systemDb->GenParamSave();

        return;
    }
}

void CGenConfig::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
    g_GenMain->setGenForSave(true);

    memcpy(g_systemDb->m_sBodyBuf,g_systemDb->m_sBody,sizeof(BodyPar)  * GEN_PAR_MAX);

    if(viewGen)
    {
        viewGen->resetMatrix();
        viewGen->setGeometry( QRect(0,60,480,480));
        viewGen->show();
    }

    if(viewPopup)
        viewPopup->resetMatrix();

    btExit->setFocus();
}
void CGenConfig::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
    g_GenMain->setGenForSave(false);
}

void CGenConfig::myPopupPosInit()
{

    PopInfoPos[SYS_POPUP_PARAM_CFG] = QRect(20,60,305,550);
    PopInfoPos[SYS_POPUP_FOCUS_CFG] = QRect(125,200,200,100);
    PopInfoPos[SYS_POPUP_AEC_CFG]   = QRect(25,210,300,280);

}

void CGenConfig::OnPopupHide(QWidget *)
{
    if(!isVisible())
        return;

    if(viewPopup)
        viewPopup->hide();
}
void CGenConfig::OnPopupShow(int popIdx)
{
    if(!isVisible())
        return;

    if(!viewPopup)
        return;

    switch(popIdx)
    {
    case SYS_POPUP_PARAM:
        viewPopup->setScene(pSceneArray[SYS_POPUP_PARAM_CFG]);
        viewPopup->setGeometry(PopInfoPos[SYS_POPUP_PARAM_CFG]);
        RsMgr->g_genParamMgr->show();
        break;
    case SYS_POPUP_AEC:
        viewPopup->setScene(pSceneArray[SYS_POPUP_AEC_CFG]);
        viewPopup->setGeometry(PopInfoPos[SYS_POPUP_AEC_CFG]);
        RsMgr->g_genAec->show();
        break;
    case SYS_POPUP_FOCUS:
        viewPopup->setScene(pSceneArray[SYS_POPUP_FOCUS_CFG]);
        viewPopup->setGeometry(PopInfoPos[SYS_POPUP_FOCUS_CFG]);
        RsMgr->g_genFocus->show();
        break;
    default:
        break;
    }

    viewPopup->raise();
    viewPopup->show();
}

