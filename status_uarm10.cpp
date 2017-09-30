#include "status_uarm10.h"
#include "resource_manager.h"

CStatusUarm10::CStatusUarm10(QWidget *parent) :
    CStatusBase10(parent)
{

    setObjectName("CStatusUarm10");

    resize(SYS_WID(300),SYS_HEI(83));

    lbIcon[UARM10_MOTOR_HEI]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_HEI"));
    lbIcon[UARM10_MOTOR_SID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_FID"));
    lbIcon[UARM10_MOTOR_ANG]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_ANG"));
    lbIcon[UARM10_MOTOR_DTA]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_DTA"));

    //设置控件可见
    lbIcon[UARM10_MOTOR_HEI]->setVisible(true);
    lbIcon[UARM10_MOTOR_SID]->setVisible(true);
    lbIcon[UARM10_MOTOR_ANG]->setVisible(true);
    lbIcon[UARM10_MOTOR_DTA]->setVisible(true);

    //设置控件位置
    lbIcon[UARM10_MOTOR_HEI]->setGeometry(SYS_WID(0),  SYS_HEI(0), SYS_WID(40), SYS_HEI(40));
    lbIcon[UARM10_MOTOR_SID]->setGeometry(SYS_WID(150),SYS_HEI(0), SYS_WID(40), SYS_HEI(40));
    lbIcon[UARM10_MOTOR_ANG]->setGeometry(SYS_WID(0),  SYS_HEI(43), SYS_WID(40), SYS_HEI(40));
    lbIcon[UARM10_MOTOR_DTA]->setGeometry(SYS_WID(150),SYS_HEI(43), SYS_WID(40), SYS_HEI(40));

    //设置控件可见
    lcd[UARM10_MOTOR_HEI]->setVisible(true);
    lcd[UARM10_MOTOR_SID]->setVisible(true);
    lcd[UARM10_MOTOR_ANG]->setVisible(true);
    lcd[UARM10_MOTOR_DTA]->setVisible(true);

    //设置控件位置
    lcd[UARM10_MOTOR_HEI]->setGeometry(SYS_WID(12) , SYS_HEI(-5), SYS_WID(70), SYS_HEI(50));
    lcd[UARM10_MOTOR_SID]->setGeometry(SYS_WID(162), SYS_HEI(-5), SYS_WID(70), SYS_HEI(50));
    lcd[UARM10_MOTOR_ANG]->setGeometry(SYS_WID(12) , SYS_HEI(38), SYS_WID(70), SYS_HEI(50));
    lcd[UARM10_MOTOR_DTA]->setGeometry(SYS_WID(162), SYS_HEI(38), SYS_WID(70), SYS_HEI(50));

    setStyleSheet("background-color : lightGray");
}

void CStatusUarm10::OnStatusFresh()
{
    //刷新显示数据
    lcd[UARM10_MOTOR_HEI]->display(g_systemDb->g_dbMachine.CurrentData[UARM10_MOTOR_HEI]);
    lcd[UARM10_MOTOR_SID]->display(g_systemDb->g_dbMachine.CurrentData[UARM10_MOTOR_SID]);
    lcd[UARM10_MOTOR_ANG]->display(g_systemDb->g_dbMachine.CurrentData[UARM10_MOTOR_ANG]);
    lcd[UARM10_MOTOR_DTA]->display(g_systemDb->g_dbMachine.CurrentData[UARM10_MOTOR_DTA]);

    CStatusBase::OnStatusFresh();
}
