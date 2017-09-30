#include "curtain_base.h"
#include "resource_manager.h"

CCurtainBase::CCurtainBase(QWidget *parent) :
    QWidget(parent)
{

    pbCurtainSwitch = new QPushButton(this);

    connect(pbCurtainSwitch,SIGNAL(pressed()),this,SLOT(OnCurtainSwitch()));
    pbCurtainSwitch->setText(QApplication::translate("CCurtainBase", "Curtain\nOFF"));
    pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_OFF"));
    pbCurtainSwitch->show();

    QFont font;
    font.setPixelSize(SYS_FONT(18));
    pbCurtainSwitch->setFont(font);

    tmCurtainStateFresh = new QTimer(this);
    tmCurtainStateFresh->setInterval(SYS_LIGHT_CURTAIN_FRESH);
    connect(tmCurtainStateFresh,SIGNAL(timeout()),this,SLOT(OnCurtainStateFresh()));

    setVisible(false);
}

void CCurtainBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    //read one time after start up
    tmCurtainStateFresh->start();

}
void CCurtainBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
void CCurtainBase::mousePressEvent(QMouseEvent */*event*/)
{
}
void CCurtainBase::OnCurtainSwitch()
{   

    unsigned short  buf[16];
    buf[0] =0;

    if(g_systemDb->g_iArrLightCurtain[1] == 0)
    {

        buf[1] =LC_CMD_ON;
        g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

        pbCurtainSwitch->setText(QApplication::translate("CCurtainBase", "Curtain\nON"));
        pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_ON"));
    }else
    {

        buf[1] =LC_CMD_OFF;
        g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

        pbCurtainSwitch->setText(QApplication::translate("CCurtainBase", "Curtain\nOFF"));
        pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_OFF"));
    }

}

void CCurtainBase::OnCurtainStateFresh()
{
    if(g_systemDb->g_iArrLightCurtain[1] == 0)
    {
        pbCurtainSwitch->setText(QApplication::translate("CCurtainBase", "Curtain\nOFF"));
        pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_OFF"));
    }else
    {
        pbCurtainSwitch->setText(QApplication::translate("CCurtainBase", "Curtain\nON"));
        pbCurtainSwitch->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_ON"));
    }

    unsigned short  buf[16];
    buf[0] =0;
    buf[1] =LC_CMD_FRESH;
    g_taskComCtrl->CreateTask(CMD_FUNC_LIGHT_CURTAIN,buf,10);

}
void CCurtainBase::OnViewDirChange(int )
{
}
