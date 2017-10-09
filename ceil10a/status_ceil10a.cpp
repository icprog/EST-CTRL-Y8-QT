#include "status_ceil10a.h"
#include "resource_manager.h"

CStatusCeil10a::CStatusCeil10a(QWidget *parent) :
    CStatusBase10(parent)
{
    setObjectName("CStatusCeil10a");

    resize(SYS_HEI(300),SYS_WID(83));

    lbIcon[CEIL10a_MOTOR_FID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_FID"));
    lbIcon[CEIL10a_MOTOR_SID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_SID") );
    lbIcon[CEIL10a_MOTOR_ANG]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_ANG") );
    lbIcon[CEIL10a_MOTOR_DTH]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_DTH") );
    lbIcon[CEIL10a_MOTOR_DTA]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_DTA") );
    lbIcon[CEIL10a_MOTOR_BEH]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_BEH"));

    lbIcon[CEIL10a_MOTOR_FID]->setVisible(true);
    lbIcon[CEIL10a_MOTOR_SID]->setVisible(true);
    lbIcon[CEIL10a_MOTOR_ANG]->setVisible(true);
    lbIcon[CEIL10a_MOTOR_DTH]->setVisible(true);
    lbIcon[CEIL10a_MOTOR_DTA]->setVisible(true);
    lbIcon[CEIL10a_MOTOR_BEH]->setVisible(true);

    lbIcon[CEIL10a_MOTOR_FID]->setGeometry(SYS_HEI(0)  , SYS_WID(0), SYS_HEI(40), SYS_WID(40));
    lbIcon[CEIL10a_MOTOR_SID]->setGeometry(SYS_HEI(100), SYS_WID(0), SYS_HEI(40), SYS_WID(40));
    lbIcon[CEIL10a_MOTOR_ANG]->setGeometry(SYS_HEI(200), SYS_WID(0), SYS_HEI(40), SYS_WID(40));
    lbIcon[CEIL10a_MOTOR_DTH]->setGeometry(SYS_HEI(0)  , SYS_WID(43), SYS_HEI(40), SYS_WID(40));
    lbIcon[CEIL10a_MOTOR_DTA]->setGeometry(SYS_HEI(100), SYS_WID(43), SYS_HEI(40), SYS_WID(40));
    lbIcon[CEIL10a_MOTOR_BEH]->setGeometry(SYS_HEI(200), SYS_WID(43), SYS_HEI(40), SYS_WID(40));

    lcd[CEIL10a_MOTOR_FID]->setVisible(true);
    lcd[CEIL10a_MOTOR_SID]->setVisible(true);
    lcd[CEIL10a_MOTOR_ANG]->setVisible(true);
    lcd[CEIL10a_MOTOR_DTH]->setVisible(true);
    lcd[CEIL10a_MOTOR_DTA]->setVisible(true);
    lcd[CEIL10a_MOTOR_BEH]->setVisible(true);

    lcd[CEIL10a_MOTOR_FID]->setGeometry(SYS_HEI(12)    , SYS_WID(-5), SYS_HEI(70), SYS_WID(50));
    lcd[CEIL10a_MOTOR_SID]->setGeometry(SYS_HEI(112)   , SYS_WID(-5), SYS_HEI(70), SYS_WID(50));
    lcd[CEIL10a_MOTOR_ANG]->setGeometry(SYS_HEI(212)   , SYS_WID(-5), SYS_HEI(70), SYS_WID(50));
    lcd[CEIL10a_MOTOR_DTH]->setGeometry(SYS_HEI(12)    , SYS_WID(38), SYS_HEI(70), SYS_WID(50));
    lcd[CEIL10a_MOTOR_DTA]->setGeometry(SYS_HEI(112)   , SYS_WID(38), SYS_HEI(70), SYS_WID(50));
    lcd[CEIL10a_MOTOR_BEH]->setGeometry(SYS_HEI(212)   , SYS_WID(38), SYS_HEI(70), SYS_WID(50));

    setStyleSheet("background-color : lightGray");

}

void CStatusCeil10a::OnStatusFresh()
{

    lcd[CEIL10a_MOTOR_FID]->display(g_systemDb->g_dbMachine.CurrentData[CEIL10a_MOTOR_FID] - g_systemDb->g_dbMachine.CurrentData[CEIL10a_MOTOR_BEH]);
    lcd[CEIL10a_MOTOR_SID]->display(g_systemDb->g_dbMachine.CurrentData[CEIL10a_MOTOR_SID]);
    lcd[CEIL10a_MOTOR_ANG]->display(g_systemDb->g_dbMachine.CurrentData[CEIL10a_MOTOR_ANG]);
    lcd[CEIL10a_MOTOR_DTH]->display(g_systemDb->g_dbMachine.CurrentData[CEIL10a_MOTOR_DTH]);
    lcd[CEIL10a_MOTOR_DTA]->display(g_systemDb->g_dbMachine.CurrentData[CEIL10a_MOTOR_DTA]);
    lcd[CEIL10a_MOTOR_BEH]->display(g_systemDb->g_dbMachine.CurrentData[CEIL10a_MOTOR_BEH]);//CEIL10a_MOTOR_BEH

    CStatusBase::OnStatusFresh();
}
