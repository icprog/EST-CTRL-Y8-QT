#include "menu_base10.h"
#include "resource_manager.h"

CMenuBase10::CMenuBase10(QWidget *parent) :
    CMenuBase(parent)
{
    resize(SYS_WID(226),SYS_HEI(600));

    myButtonInit();

    myButtonViewInit();
    myButtonSlotInit();

}

void CMenuBase10::myButtonInit()
{

    pbRight5 = new CButtonStable(this);
    pbRight5->setGeometry(SYS_WID(0), SYS_HEI(510), SYS_WID(94), SYS_HEI(90));
    pbRight5->setFocusPolicy(Qt::NoFocus);
    pbRight5->setCheckable(true);

    pbRight6 = new CButtonStable(this);
    pbRight6->setGeometry(SYS_WID(94), SYS_HEI(510), SYS_WID(132), SYS_HEI(90));
    pbRight6->setFocusPolicy(Qt::NoFocus);
    pbRight6->setCheckable(true);

    pbLeft5 = new CButtonStable(this);
    pbLeft5->setGeometry(SYS_WID(0), SYS_HEI(0), SYS_WID(94), SYS_HEI(90));
    pbLeft5->setFocusPolicy(Qt::NoFocus);
    pbLeft5->setCheckable(true);

    pbLeft6 = new CButtonStable(this);
    pbLeft6->setGeometry(SYS_WID(94), SYS_HEI(0), SYS_WID(132), SYS_HEI(90));
    pbLeft6->setFocusPolicy(Qt::NoFocus);
    pbLeft6->setCheckable(true);
}
void CMenuBase10::OnViewChange(int view)
{
    switch(view)
    {
    case VIEW_GEN:
        pBtnView[MENU10_BTN_VIEW_2]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_LEFT_GEN_DOWN"));
        pBtnView[MENU10_BTN_VIEW_3]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_RIGHT_GEN_UP"));
        break;
    case VIEW_MAIN:
        break;
    case VIEW_MOTION:
        pBtnView[MENU10_BTN_VIEW_2]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_LEFT_GEN_UP"));
        pBtnView[MENU10_BTN_VIEW_3]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_RIGHT_GEN_DOWN"));
        break;
    default:
        break;
    }
}
void CMenuBase10::OnViewerSwitch()
{
    //关闭自运行
    g_systemDb->SetAutoRun(false);

    if(sender() == pbLeft5)
    {
        //判断是否允许发生器页面显示
        if(!g_dbsys.utility.mGeneratorShow)
            return;

        //切换到发生器配置页面
        emit ViewChange(VIEW_GEN_CFG);

    }

    if(sender() == pbLeft6)
    {

        if(!g_dbsys.utility.mGeneratorShow)
            return;

        pBtnView[MENU10_BTN_VIEW_2]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_LEFT_GEN_DOWN"));
        pBtnView[MENU10_BTN_VIEW_3]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_RIGHT_GEN_UP"));
        emit ViewChange(VIEW_GEN);
    }

    if( sender() == pbRight5)
    {

        this->hide();
        emit ViewChange(VIEW_PASSWORD);
    }

    if( sender()  == pbRight6)
    {

        pBtnView[MENU10_BTN_VIEW_2]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_LEFT_GEN_UP"));
        pBtnView[MENU10_BTN_VIEW_3]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_RIGHT_GEN_DOWN"));
        emit ViewChange(VIEW_MOTION);
    }

}
void CMenuBase10::OnGenTechChange(int mTech)
{
    if(mTech == SYS_TECH_AEC || mTech == SYS_TECH_MAS  || mTech == SYS_TECH_MAMS )
    {
        pBtnView[MENU10_BTN_VIEW_2]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_LEFT_GEN_DOWN"));
        pBtnView[MENU10_BTN_VIEW_3]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_RIGHT_GEN_UP"));
    }

}

void CMenuBase10::OnViewDirChange(int viewerDir)
{
    int dirAngle[4];
    dirAngle[0] = 90;    dirAngle[1] = 0;    dirAngle[2] = 180;    dirAngle[3] = 90;

    for(int mIdx = MENU10_BTN_VIEW_0 ; mIdx <= MENU10_BTN_VIEW_3 ; mIdx++)
    {
        keyView[mIdx]->resetTransform();
        keyView[mIdx]->rotate(dirAngle[viewerDir]);
    }
}
void CMenuBase10::myButtonViewInit()
{

    pBtnView[MENU10_BTN_VIEW_0]     = pbLeft5;
    pBtnView[MENU10_BTN_VIEW_1]     = pbRight5 ;
    pBtnView[MENU10_BTN_VIEW_2]     = pbLeft6;
    pBtnView[MENU10_BTN_VIEW_3]     = pbRight6;

    pBtnView[MENU10_BTN_VIEW_0]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_LEFT_CFG_UP"));
    pBtnView[MENU10_BTN_VIEW_1]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_RIGHT_CFG_UP"));
    pBtnView[MENU10_BTN_VIEW_2]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_LEFT_GEN_UP"));
    pBtnView[MENU10_BTN_VIEW_3]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_RIGHT_GEN_DOWN"));

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    for(int mIdx = MENU10_BTN_VIEW_0 ; mIdx <= MENU10_BTN_VIEW_3 ; mIdx++)
    {
        keyLabel[mIdx]    = new QLabel() ;
        keyLabel[mIdx]->setGeometry(0,0,90,90);
        keyLabel[mIdx]->setFont(font);
        keyLabel[mIdx]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        keyLabel[mIdx]->setStyleSheet("background:transparent;color:white");
        keyScene[mIdx]      = new QGraphicsScene(pBtnView[mIdx]);
        keyScene[mIdx]->addWidget(keyLabel[mIdx] );
        keyLabel[mIdx] ->show();
        keyView[mIdx]       = new QGraphicsView(pBtnView[mIdx]);
        keyView[mIdx]->setFocusPolicy(Qt::NoFocus);
        keyView[mIdx]->setFrameShape(QFrame::NoFrame);
        keyView[mIdx]->setFrameShadow(QFrame::Plain);
        keyView[mIdx]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        keyView[mIdx]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        keyView[mIdx]->setScene(keyScene[mIdx]);
        keyView[mIdx]->setStyleSheet("background:transparent");

        keyView[mIdx]->setFocusPolicy(Qt::NoFocus);
    }

    keyView[MENU10_BTN_VIEW_0]->setGeometry(SYS_WID(5),SYS_HEI(0),SYS_WID(90),SYS_HEI(90));
    keyView[MENU10_BTN_VIEW_1]->setGeometry(SYS_WID(5),SYS_HEI(0),SYS_WID(90),SYS_HEI(90));
    keyView[MENU10_BTN_VIEW_2]->setGeometry(SYS_WID(20),SYS_HEI(0),SYS_WID(90),SYS_HEI(90));
    keyView[MENU10_BTN_VIEW_3]->setGeometry(SYS_WID(20),SYS_HEI(0),SYS_WID(90),SYS_HEI(90));
    keyLabel[MENU10_BTN_VIEW_0]->setText(QApplication::translate("CMenuBase", "CONFIG"));
    keyLabel[MENU10_BTN_VIEW_1]->setText(QApplication::translate("CMenuBase", "CONFIG"));
    keyLabel[MENU10_BTN_VIEW_2]->setText(QApplication::translate("CMenuBase", "GEN"));
    keyLabel[MENU10_BTN_VIEW_3]->setText(QApplication::translate("CMenuBase", "SYS"));

    keyLabel[MENU10_BTN_VIEW_0]->setFont(font);
    keyLabel[MENU10_BTN_VIEW_1]->setFont(font);
    keyLabel[MENU10_BTN_VIEW_2]->setFont(font);
    keyLabel[MENU10_BTN_VIEW_3]->setFont(font);

    OnViewDirChange(m_iViewDir);
}
void CMenuBase10::myButtonSlotInit()
{
    connect(pbLeft5,SIGNAL(pressed()),this,SLOT(OnViewerSwitch()));
    connect(pbLeft6,SIGNAL(pressed()),this,SLOT(OnViewerSwitch()));
    connect(pbRight5,SIGNAL(pressed()),this,SLOT(OnViewerSwitch()));
    connect(pbRight6,SIGNAL(pressed()),this,SLOT(OnViewerSwitch()));

}
