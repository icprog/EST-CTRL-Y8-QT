#include "menu_base8.h"
#include "resource_manager.h"

CMenuBase8::CMenuBase8(QWidget *parent) :
    CMenuBase(parent)
{

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(208,235,245));
    setPalette(pal);

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    pbSystem    = new CButtonStable(this);
    pbGenerator = new CButtonStable(this);
    pbMotion    = new CButtonStable(this);

    pbSystem->setGeometry(   SYS_WID(0),  SYS_HEI(100),SYS_WID(100),SYS_HEI(100));
    pbGenerator->setGeometry(SYS_WID(100),SYS_HEI(100),SYS_WID(100),SYS_HEI(100));
    pbMotion->setGeometry(   SYS_WID(200),SYS_HEI(100),SYS_WID(100),SYS_HEI(100));

    pbSystem->setText(QApplication::translate("CMenuBase", "CONFIG"));
    pbGenerator->setText(QApplication::translate("CMenuBase", "GEN"));
    pbMotion->setText(QApplication::translate("CMenuBase", "SYS"));

    pbSystem->setFont(font);
    pbGenerator->setFont(font);
    pbMotion->setFont(font);

    pbGenerator->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_GEN_UP"));
    pbSystem->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_SYSTEM_UP") );
    pbMotion->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_MOTION_DOWN") );

    connect(pbGenerator,SIGNAL(pressed()),this,SLOT(OnMenuPressed()));
    connect(pbSystem,   SIGNAL(pressed()),this,SLOT(OnMenuPressed()));
    connect(pbMotion,   SIGNAL(pressed()),this,SLOT(OnMenuPressed()));

}


void CMenuBase8::OnViewChange(int view)
{
    switch(view)
    {
    case VIEW_GEN:
        pbGenerator->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_GEN_DOWN") );
        pbMotion->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_MOTION_UP") );

        RsMgr->g_quickBase->hide();
        break;
    case VIEW_MAIN:
        break;
    case VIEW_MOTION:
        pbGenerator->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_GEN_UP") );
        pbMotion->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_MOTION_DOWN"));

        RsMgr->g_quickBase->show();
        break;
    default:
        break;
    }
}
void CMenuBase8::OnMenuPressed()
{
    g_systemDb->SetAutoRun(false);
    EmergencyStop();

    if(sender() == pbSystem)
    {
        if(m_iViewMode == VIEW_MOTION)
        {
            emit ViewChange(VIEW_PASSWORD);
        }else
        {
            emit ViewChange(VIEW_GEN_CFG);
        }
    }

    if(sender() == pbMotion)
    {
        //RsMgr->g_techBase->hide();
       // RsMgr->g_fastBase->show();
        //RsMgr->g_quickBase->show();
        emit ViewChange(VIEW_MOTION);
        m_iViewMode = VIEW_MOTION;
    }

    if(g_dbsys.utility.mGeneratorShow)
    {
        if(sender() == pbGenerator)
        {
            //RsMgr->g_techBase->show();
            //RsMgr->g_quickBase->hide();
            //RsMgr->g_fastBase->hide();
            emit ViewChange(VIEW_GEN);
            m_iViewMode = VIEW_GEN;
        }
    }

    emit MenuKeyDown(m_iViewMode);
}

void CMenuBase8::OnBodyIndexChange(int )
{

}
