#include "menu_base12.h"
#include "resource_manager.h"

CMenuBase12::CMenuBase12(QWidget *parent) :
    CMenuBase(parent)
{
    QFont font;
    font.setPixelSize(SYS_FONT(22));

    pbSystem    = new CButtonStable(this);
    pbGenerator = new CButtonStable(this);
    pbMotion    = new CButtonStable(this);

    OnViewDirChange(g_systemDb->g_startAngle);

    pbSystem->setFont(font);
    pbGenerator->setFont(font);
    pbMotion->setFont(font);

    pbGenerator->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_GEN_UP"));
    pbSystem->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_SYSTEM_UP") );
    pbMotion->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_ICON_MOTION_DOWN") );

    connect(pbGenerator,SIGNAL(pressed()),this,SLOT(OnMenuPressed()));
    connect(pbSystem,   SIGNAL(pressed()),this,SLOT(OnMenuPressed()));
    connect(pbMotion,   SIGNAL(pressed()),this,SLOT(OnMenuPressed()));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(100,235,245)");
    }

}

void CMenuBase12::OnViewChange(int view)
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
void CMenuBase12::OnMenuPressed()
{
    g_systemDb->SetAutoRun(false);
    EmergencyStop();

    if(g_dbsys.utility.mConfigShow)
    {
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

void CMenuBase12::OnViewDirChange(int viewPoint)
{

    switch(viewPoint)
    {
    case VIEW_DIR_R180:
        break;
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(330),SYS_WID(330));
        pbSystem->setGeometry(   SYS_HEI(108), SYS_WID(49),SYS_HEI(111),SYS_WID(73));
        pbGenerator->setGeometry(SYS_HEI(107),SYS_WID(125),SYS_HEI(111),SYS_WID(73));
        pbMotion->setGeometry(   SYS_HEI(110),SYS_WID(202),SYS_HEI(108),SYS_WID(73));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(330),SYS_HEI(330));
        pbSystem->setGeometry(   SYS_WID(2),  SYS_HEI(130),SYS_WID(111),SYS_HEI(73));
        pbGenerator->setGeometry(SYS_WID(111),SYS_HEI(130),SYS_WID(111),SYS_HEI(73));
        pbMotion->setGeometry(   SYS_WID(222),SYS_HEI(131),SYS_WID(108),SYS_HEI(73));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(330),SYS_HEI(330));
        pbSystem->setGeometry(   SYS_WID(2),  SYS_HEI(130),SYS_WID(111),SYS_HEI(73));
        pbGenerator->setGeometry(SYS_WID(111),SYS_HEI(130),SYS_WID(111),SYS_HEI(73));
        pbMotion->setGeometry(   SYS_WID(222),SYS_HEI(131),SYS_WID(108),SYS_HEI(73));
        break;
    default:
        break;
    }
}

void CMenuBase12::OnBodyIndexChange(int )
{

}
