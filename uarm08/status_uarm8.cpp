#include "status_uarm8.h"
#include "resource_manager.h"

CStatusUarm8::CStatusUarm8(QWidget *parent) :
    CStatusBase8(parent)
{

    setObjectName("CStatusUarm8");

    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT
    m_iViewDir = VIEW_DIR_NORMAL;
    OnViewDirChange(m_iViewDir);

    lbIcon[UARM8_MOTOR_HEI]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_HEI"));
    lbIcon[UARM8_MOTOR_SID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_FID"));
    lbIcon[UARM8_MOTOR_ANG]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_ANG"));
    lbIcon[UARM8_MOTOR_DTA]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_DTA"));

    //将需要的内容设为可见
    lbIcon[UARM8_MOTOR_HEI]->setVisible(true);
    lbIcon[UARM8_MOTOR_SID]->setVisible(true);
    lbIcon[UARM8_MOTOR_ANG]->setVisible(true);
    lbIcon[UARM8_MOTOR_DTA]->setVisible(true);

    lcd[UARM8_MOTOR_HEI]->setVisible(true);
    lcd[UARM8_MOTOR_SID]->setVisible(true);
    lcd[UARM8_MOTOR_ANG]->setVisible(true);
    lcd[UARM8_MOTOR_DTA]->setVisible(true);

    //设置LCDNubers的线宽
    lcd[UARM8_MOTOR_HEI]->setLineWidth(2);
    lcd[UARM8_MOTOR_SID]->setLineWidth(2);
    lcd[UARM8_MOTOR_ANG]->setLineWidth(2);
    lcd[UARM8_MOTOR_DTA]->setLineWidth(2);

    //根据按钮颜色，设置数码显示的颜色
    lcd[UARM8_MOTOR_HEI]->setStyleSheet("color : rgb(48,155,70)");
    lcd[UARM8_MOTOR_SID]->setStyleSheet("color : rgb(27,66,130)");
    lcd[UARM8_MOTOR_ANG]->setStyleSheet("color : rgb(252,176,64)");
    lcd[UARM8_MOTOR_DTA]->setStyleSheet("color : rgb(0,173,238)");

}


void CStatusUarm8::OnStatusFresh()
{
    CStatusBase::OnStatusFresh();

    lcd[UARM8_MOTOR_HEI]->display(g_systemDb->g_dbMachine.CurrentData[UARM8_MOTOR_HEI]);
    lcd[UARM8_MOTOR_SID]->display(g_systemDb->g_dbMachine.CurrentData[UARM8_MOTOR_SID]);
    lcd[UARM8_MOTOR_ANG]->display(g_systemDb->g_dbMachine.CurrentData[UARM8_MOTOR_ANG]);
    lcd[UARM8_MOTOR_DTA]->display(qAbs(g_systemDb->g_dbMachine.CurrentData[UARM8_MOTOR_DTA]));      //不显示负数
}
void CStatusUarm8::OnViewDirChange(int mDir)
{

    m_iViewDir      = mDir;

    if(m_iViewDir == VIEW_DIR_NORMAL)
    {
        resize(SYS_WID(165),SYS_HEI(315));

        lbIcon[UARM8_MOTOR_HEI]->setGeometry(SYS_WID(0), SYS_HEI(12) ,SYS_WID(50), SYS_HEI(50));
        lbIcon[UARM8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(92) ,SYS_WID(50), SYS_HEI(50));
        lbIcon[UARM8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(172),SYS_WID(50), SYS_HEI(50));
        lbIcon[UARM8_MOTOR_DTA]->setGeometry(SYS_WID(0), SYS_HEI(252),SYS_WID(50), SYS_HEI(50));

        lcd[UARM8_MOTOR_HEI]->setGeometry(SYS_WID(0), SYS_HEI(12) , SYS_WID(145), SYS_HEI(50));
        lcd[UARM8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(92) , SYS_WID(145), SYS_HEI(50));
        lcd[UARM8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(172), SYS_WID(145), SYS_HEI(50));
        lcd[UARM8_MOTOR_DTA]->setGeometry(SYS_WID(0), SYS_HEI(252), SYS_WID(145), SYS_HEI(50));
        return;
    }

    if(m_iViewDir == VIEW_DIR_LEFT)
    {
        resize(SYS_WID(300),SYS_HEI(135));

        lbIcon[UARM8_MOTOR_HEI]->setGeometry(SYS_WID(0), SYS_HEI(0)  ,SYS_WID(50), SYS_HEI(50));
        lcd[UARM8_MOTOR_HEI]->setGeometry(SYS_WID(0), SYS_HEI(0)  , SYS_WID(145), SYS_HEI(50));

        lbIcon[UARM8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(60) ,SYS_WID(50), SYS_HEI(50));
        lcd[UARM8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(60) , SYS_WID(145), SYS_HEI(50));

        lbIcon[UARM8_MOTOR_ANG]->setGeometry(SYS_WID(150), SYS_HEI(0),SYS_WID(50), SYS_HEI(50));
        lcd[UARM8_MOTOR_ANG]->setGeometry(SYS_WID(150), SYS_HEI(0), SYS_WID(145), SYS_HEI(50));

        lbIcon[UARM8_MOTOR_DTA]->setGeometry(SYS_WID(150), SYS_HEI(60),SYS_WID(50), SYS_HEI(50));
        lcd[UARM8_MOTOR_DTA]->setGeometry(SYS_WID(150), SYS_HEI(60), SYS_WID(145), SYS_HEI(50));
        return;
    }

    if(m_iViewDir == VIEW_DIR_RIGHT)
    {
        resize(SYS_WID(300),SYS_HEI(110));

        lbIcon[UARM8_MOTOR_HEI]->setGeometry(SYS_WID(0), SYS_HEI(0)  ,SYS_WID(50), SYS_HEI(50));
        lcd[UARM8_MOTOR_HEI]->setGeometry(SYS_WID(0), SYS_HEI(0)  , SYS_WID(145), SYS_HEI(50));

        lbIcon[UARM8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(60) ,SYS_WID(50), SYS_HEI(50));
        lcd[UARM8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(60) , SYS_WID(145), SYS_HEI(50));

        lbIcon[UARM8_MOTOR_ANG]->setGeometry(SYS_WID(150), SYS_HEI(0),SYS_WID(50), SYS_HEI(50));
        lcd[UARM8_MOTOR_ANG]->setGeometry(SYS_WID(150), SYS_HEI(0), SYS_WID(145), SYS_HEI(50));

        lbIcon[UARM8_MOTOR_DTA]->setGeometry(SYS_WID(150), SYS_HEI(60),SYS_WID(50), SYS_HEI(50));
        lcd[UARM8_MOTOR_DTA]->setGeometry(SYS_WID(150), SYS_HEI(60), SYS_WID(145), SYS_HEI(50));
        return;
    }
}
