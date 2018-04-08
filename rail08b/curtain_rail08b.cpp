#include "curtain_base12.h"
#include "resource_manager.h"

CCurtainBase12::CCurtainBase12(QWidget *parent) :
    CCurtainBase(parent)
{
    setObjectName("CCurtainBase12");

    OnViewDirChange(g_systemDb->g_startAngle);

    pbCurtainSwitch->setText("");
    pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_CURTAIN_OFF"));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(20,0,100)");
    }
}

void CCurtainBase12::OnCurtainSwitch()
{

    unsigned short  buf[16];
    buf[0] =0;

    if(g_systemDb->g_iArrLightCurtain[1] == 0)
    {

        buf[1] =LC_CMD_ON;
        g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

        pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_CURTAIN_ON"));
    }else
    {

        buf[1] =LC_CMD_OFF;
        g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

        pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_CURTAIN_OFF"));
    }

}

void CCurtainBase12::OnCurtainStateFresh()
{
    if(g_systemDb->g_iArrLightCurtain[1] == 0)
    {
        pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_CURTAIN_OFF"));
    }else
    {
        pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_CURTAIN_ON"));
    }

    unsigned short  buf[16];
    buf[0] =0;
    buf[1] =LC_CMD_FRESH;
    g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

}
void CCurtainBase12::OnViewDirChange(int sAngle)
{
    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(90),SYS_WID(90));
        pbCurtainSwitch->setGeometry(SYS_HEI(0), SYS_WID(6), SYS_HEI(90), SYS_WID(72));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(90),SYS_HEI(90));
        pbCurtainSwitch->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(90),SYS_HEI(90));
        pbCurtainSwitch->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }

}
