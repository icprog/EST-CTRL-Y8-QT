#include "curtain_rail08b.h"
#include "resource_manager.h"

CCurtainRail08b::CCurtainRail08b(QWidget *parent) :
    CCurtainBase8(parent)
{
    setObjectName("CCurtainRail08b");

    resize(SYS_HEI(70),SYS_WID(70));

    OnViewDirChange(g_systemDb->g_startAngle);

    pbCurtainSwitch->setText("");
    pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_CURTAIN_OFF"));

    m_iDisplayText = false;

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(20,0,100)");
    }
}


void CCurtainRail08b::OnViewDirChange(int sAngle)
{
    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:

        pbCurtainSwitch->setGeometry(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56));
        break;
    case VIEW_DIR_LEFT:

        pbCurtainSwitch->setGeometry(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56));
        break;
    case VIEW_DIR_RIGHT:

     pbCurtainSwitch->setGeometry(SYS_HEI(0), SYS_WID(7), SYS_HEI(70), SYS_WID(56));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }

}
