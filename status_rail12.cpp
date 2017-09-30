#include "status_rail12.h"
#include "resource_manager.h"

CStatusRail12::CStatusRail12(QWidget *parent) :
    CStatusBase12(parent)
{

    setObjectName("CStatusRail12");

    lbIcon[RAIL8_MOTOR_FID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_FID"));
    lbIcon[RAIL8_MOTOR_SID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_SID"));
    lbIcon[RAIL8_MOTOR_ANG]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_ANG"));
    lbIcon[RAIL8_MOTOR_DTH]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_DTH"));
    lbIcon[RAIL8_MOTOR_BEH]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_BEH"));

    //根据配置，设置需要显示的控件
    lbIcon[RAIL8_MOTOR_FID]->setVisible(true);
    lbIcon[RAIL8_MOTOR_SID]->setVisible(true);
    lbIcon[RAIL8_MOTOR_ANG]->setVisible(true);
    lbIcon[RAIL8_MOTOR_DTH]->setVisible(true);
    lbIcon[RAIL8_MOTOR_BEH]->setVisible(true);

    lcd[RAIL8_MOTOR_FID]->setVisible(true);
    lcd[RAIL8_MOTOR_SID]->setVisible(true);
    lcd[RAIL8_MOTOR_ANG]->setVisible(true);
    lcd[RAIL8_MOTOR_DTH]->setVisible(true);
    lcd[RAIL8_MOTOR_BEH]->setVisible(true);

    //设置LCD显示颜色，根据按键颜色
    lcd[RAIL8_MOTOR_FID]->setStyleSheet("color : rgb(233,234,236)");
    lcd[RAIL8_MOTOR_SID]->setStyleSheet("color : rgb(49,108,166)");
    lcd[RAIL8_MOTOR_ANG]->setStyleSheet("color : rgb(233,234,236)");
    lcd[RAIL8_MOTOR_DTH]->setStyleSheet("color : rgb(49,108,166)");
    lcd[RAIL8_MOTOR_BEH]->setStyleSheet("color : rgb(233,234,236)");

    lcd[RAIL8_MOTOR_FID]->raise();
    lcd[RAIL8_MOTOR_SID]->raise();
    lcd[RAIL8_MOTOR_ANG]->raise();
    lcd[RAIL8_MOTOR_DTH]->raise();
    lcd[RAIL8_MOTOR_BEH]->raise();

    OnViewDirChange(g_systemDb->g_startAngle);

}

void CStatusRail12::OnStatusFresh()
{
    CStatusBase::OnStatusFresh();

    //刷新显示数据
    int mFid = g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_FID] - g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_BEH];
    lcd[RAIL8_MOTOR_FID]->display(mFid);
    lcd[RAIL8_MOTOR_SID]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_SID]);
    lcd[RAIL8_MOTOR_ANG]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_ANG]);
    lcd[RAIL8_MOTOR_DTH]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_DTH]);
    lcd[RAIL8_MOTOR_BEH]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_BEH]);

}
//显示角度切换时，变幻控件位置
void CStatusRail12::OnViewDirChange(int sAngle)
{

    if(sAngle == VIEW_DIR_NORMAL)
    {
        resize(SYS_HEI(696),SYS_WID(520));
        lbIcon[RAIL8_MOTOR_FID]->setGeometry(SYS_HEI(1), SYS_WID(188)  ,SYS_HEI(213), SYS_WID(68));
        lbIcon[RAIL8_MOTOR_SID]->setGeometry(SYS_HEI(1), SYS_WID(267) ,SYS_HEI(213), SYS_WID(68));
        lbIcon[RAIL8_MOTOR_ANG]->setGeometry(SYS_HEI(238), SYS_WID(237),SYS_HEI(213), SYS_WID(68));
        lbIcon[RAIL8_MOTOR_DTH]->setGeometry(SYS_HEI(473), SYS_WID(187),SYS_HEI(213), SYS_WID(68));
        lbIcon[RAIL8_MOTOR_BEH]->setGeometry(SYS_HEI(475), SYS_WID(270),SYS_HEI(213), SYS_WID(68));

        lcd[RAIL8_MOTOR_FID]->setGeometry(SYS_HEI(36), SYS_WID(198)  , SYS_HEI(145), SYS_WID(50));
        lcd[RAIL8_MOTOR_SID]->setGeometry(SYS_HEI(36), SYS_WID(277) , SYS_HEI(145), SYS_WID(50));
        lcd[RAIL8_MOTOR_ANG]->setGeometry(SYS_HEI(271), SYS_WID(247), SYS_HEI(145), SYS_WID(50));
        lcd[RAIL8_MOTOR_DTH]->setGeometry(SYS_HEI(496), SYS_WID(198), SYS_HEI(145), SYS_WID(50));
        lcd[RAIL8_MOTOR_BEH]->setGeometry(SYS_HEI(496), SYS_WID(277), SYS_HEI(145), SYS_WID(50));

        return;
    }

    if(sAngle == VIEW_DIR_LEFT)
    {
        resize(SYS_WID(696),SYS_HEI(520));
        lbIcon[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(245), SYS_HEI(34) ,SYS_WID(213), SYS_HEI(68));
        lbIcon[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(246), SYS_HEI(118) ,SYS_WID(213), SYS_HEI(68));
        lbIcon[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(244), SYS_HEI(228),SYS_WID(213), SYS_HEI(68));
        lbIcon[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(243), SYS_HEI(340),SYS_WID(213), SYS_HEI(68));
        lbIcon[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(244), SYS_HEI(426),SYS_WID(213), SYS_HEI(68));

        lcd[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(283), SYS_HEI(44) , SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(283), SYS_HEI(128), SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(283), SYS_HEI(238), SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(283), SYS_HEI(350), SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(283), SYS_HEI(436), SYS_WID(145), SYS_HEI(50));

        return;
    }

    if(sAngle == VIEW_DIR_RIGHT)
    {
        resize(SYS_WID(696),SYS_HEI(520));
        lbIcon[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(245), SYS_HEI(34) ,SYS_WID(213), SYS_HEI(68));
        lbIcon[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(246), SYS_HEI(118) ,SYS_WID(213), SYS_HEI(68));
        lbIcon[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(244), SYS_HEI(228),SYS_WID(213), SYS_HEI(68));
        lbIcon[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(243), SYS_HEI(340),SYS_WID(213), SYS_HEI(68));
        lbIcon[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(244), SYS_HEI(426),SYS_WID(213), SYS_HEI(68));

        lcd[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(283), SYS_HEI(44) , SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(283), SYS_HEI(128), SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(283), SYS_HEI(238), SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(283), SYS_HEI(350), SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(283), SYS_HEI(436), SYS_WID(145), SYS_HEI(50));

        return;
    }
}
