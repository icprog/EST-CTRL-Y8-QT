#include "status_ceil8.h"
#include "resource_manager.h"

CStatusCeil8::CStatusCeil8(QWidget *parent) :
    CStatusBase8(parent)
{

    setObjectName("CStatusCeil8");

    lbIcon[CEIL8_MOTOR_FID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_FID") );
    lbIcon[CEIL8_MOTOR_SID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_SID"));
    lbIcon[CEIL8_MOTOR_ANG]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_ANG") );
    lbIcon[CEIL8_MOTOR_DTA]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_DTA") );
    lbIcon[CEIL8_MOTOR_DTH]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_DTH"));

    lbIcon[CEIL8_MOTOR_FID]->setVisible(true);
    lbIcon[CEIL8_MOTOR_SID]->setVisible(true);
    lbIcon[CEIL8_MOTOR_ANG]->setVisible(true);
    lbIcon[CEIL8_MOTOR_DTH]->setVisible(true);
    lbIcon[CEIL8_MOTOR_DTA]->setVisible(true);

    lcd[CEIL8_MOTOR_FID]->setLineWidth(2);
    lcd[CEIL8_MOTOR_SID]->setLineWidth(2);
    lcd[CEIL8_MOTOR_ANG]->setLineWidth(2);
    lcd[CEIL8_MOTOR_DTH]->setLineWidth(2);
    lcd[CEIL8_MOTOR_DTA]->setLineWidth(2);

    lcd[CEIL8_MOTOR_FID]->setVisible(true);
    lcd[CEIL8_MOTOR_SID]->setVisible(true);
    lcd[CEIL8_MOTOR_ANG]->setVisible(true);
    lcd[CEIL8_MOTOR_DTH]->setVisible(true);
    lcd[CEIL8_MOTOR_DTA]->setVisible(true);

    lcd[CEIL8_MOTOR_FID]->setStyleSheet("color : rgb(48,155,70)");
    lcd[CEIL8_MOTOR_SID]->setStyleSheet("color : rgb(27,66,130)");
    lcd[CEIL8_MOTOR_ANG]->setStyleSheet("color : rgb(252,176,64)");
    lcd[CEIL8_MOTOR_DTH]->setStyleSheet("color : rgb(159,31,99)");
    lcd[CEIL8_MOTOR_DTA]->setStyleSheet("color : rgb(0,173,238)");

    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT
    m_iViewDir = VIEW_DIR_NORMAL;
    OnViewDirChange(m_iViewDir);

}

void CStatusCeil8::OnViewDirChange(int mDir)
{
    /*
    lbFidIcon->setVisible(true);
    lbSidIcon->setVisible(true);
    lbAngIcon->setVisible(true);
    lbDthIcon->setVisible(true);
    lbDtaIcon->setVisible(true);
    */
    m_iViewDir      = mDir;

    if(m_iViewDir == VIEW_DIR_NORMAL)
    {
        setGeometry(0,0,SYS_WID(150),SYS_HEI(350));

        lbIcon[CEIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(0) ,SYS_WID(50), SYS_HEI(50));
        lbIcon[CEIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(75) ,SYS_WID(50), SYS_HEI(50));
        lbIcon[CEIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(150),SYS_WID(50), SYS_HEI(50));
        lbIcon[CEIL8_MOTOR_DTH]->setGeometry(SYS_WID(0), SYS_HEI(225),SYS_WID(50), SYS_HEI(50));
        lbIcon[CEIL8_MOTOR_DTA]->setGeometry(SYS_WID(0), SYS_HEI(300),SYS_WID(50), SYS_HEI(50));

        lcd[CEIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(0) , SYS_WID(145), SYS_HEI(50));
        lcd[CEIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(75) , SYS_WID(145), SYS_HEI(50));
        lcd[CEIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(150), SYS_WID(145), SYS_HEI(50));
        lcd[CEIL8_MOTOR_DTH]->setGeometry(SYS_WID(0), SYS_HEI(225), SYS_WID(145), SYS_HEI(50));
        lcd[CEIL8_MOTOR_DTA]->setGeometry(SYS_WID(0), SYS_HEI(300), SYS_WID(145), SYS_HEI(50));

        if(g_dbsys.utility.mShutdownShow)
        {

            lbIcon[CEIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(0) ,SYS_WID(50), SYS_HEI(50));
            lbIcon[CEIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(70) ,SYS_WID(50), SYS_HEI(50));
            lbIcon[CEIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(138),SYS_WID(50), SYS_HEI(50));
            lbIcon[CEIL8_MOTOR_DTH]->setGeometry(SYS_WID(0), SYS_HEI(207),SYS_WID(50), SYS_HEI(50));
            lbIcon[CEIL8_MOTOR_DTA]->setGeometry(SYS_WID(0), SYS_HEI(276),SYS_WID(50), SYS_HEI(50));

            lcd[CEIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(0) , SYS_WID(145), SYS_HEI(50));
            lcd[CEIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(70) , SYS_WID(145), SYS_HEI(50));
            lcd[CEIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(138), SYS_WID(145), SYS_HEI(50));
            lcd[CEIL8_MOTOR_DTH]->setGeometry(SYS_WID(0), SYS_HEI(207), SYS_WID(145), SYS_HEI(50));
            lcd[CEIL8_MOTOR_DTA]->setGeometry(SYS_WID(0), SYS_HEI(276), SYS_WID(145), SYS_HEI(50));
        }

        return;
    }

    if(m_iViewDir == VIEW_DIR_LEFT)
    {
        setGeometry(0,0,SYS_WID(300),SYS_HEI(300));

        lbIcon[CEIL8_MOTOR_FID]->setGeometry(SYS_WID(152), SYS_HEI(0)  ,SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_FID]->setGeometry(SYS_WID(152), SYS_HEI(0)  , SYS_WID(145), SYS_HEI(50));

        lbIcon[CEIL8_MOTOR_SID]->setGeometry(SYS_WID(152), SYS_HEI(60) ,SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_SID]->setGeometry(SYS_WID(152), SYS_HEI(60) , SYS_WID(145), SYS_HEI(50));

        lbIcon[CEIL8_MOTOR_ANG]->setGeometry(SYS_WID(2), SYS_HEI(120),SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_ANG]->setGeometry(SYS_WID(2), SYS_HEI(120), SYS_WID(145), SYS_HEI(50));

        lbIcon[CEIL8_MOTOR_DTH]->setGeometry(SYS_WID(2), SYS_HEI(0),SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_DTH]->setGeometry(SYS_WID(2), SYS_HEI(0), SYS_WID(145), SYS_HEI(50));

        lbIcon[CEIL8_MOTOR_DTA]->setGeometry(SYS_WID(2), SYS_HEI(60),SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_DTA]->setGeometry(SYS_WID(2), SYS_HEI(60), SYS_WID(145), SYS_HEI(50));
        return;
    }

    if(m_iViewDir == VIEW_DIR_RIGHT)
    {
        setGeometry(0,0,SYS_WID(300),SYS_HEI(300));

        lbIcon[CEIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(60)  ,SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(60)  , SYS_WID(145), SYS_HEI(50));

        lbIcon[CEIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(120) ,SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(120) , SYS_WID(145), SYS_HEI(50));

        lbIcon[CEIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(180),SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(180), SYS_WID(145), SYS_HEI(50));

        lbIcon[CEIL8_MOTOR_DTH]->setGeometry(SYS_WID(150), SYS_HEI(60),SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_DTH]->setGeometry(SYS_WID(150), SYS_HEI(60), SYS_WID(145), SYS_HEI(50));

        lbIcon[CEIL8_MOTOR_DTA]->setGeometry(SYS_WID(150), SYS_HEI(120),SYS_WID(50), SYS_HEI(50));
        lcd[CEIL8_MOTOR_DTA]->setGeometry(SYS_WID(150), SYS_HEI(120), SYS_WID(145), SYS_HEI(50));
        return;
    }
}
void CStatusCeil8::OnStatusFresh()
{
    CStatusBase::OnStatusFresh();

    int mFid = g_systemDb->g_dbMachine.CurrentData[CEIL8_MOTOR_FID] - g_systemDb->g_dbMachine.CurrentData[CEIL8_MOTOR_DTH];
    lcd[CEIL8_MOTOR_FID]->display(mFid);
    lcd[CEIL8_MOTOR_SID]->display(g_systemDb->g_dbMachine.CurrentData[CEIL8_MOTOR_SID]);
    lcd[CEIL8_MOTOR_ANG]->display(g_systemDb->g_dbMachine.CurrentData[CEIL8_MOTOR_ANG]);
    lcd[CEIL8_MOTOR_DTH]->display(g_systemDb->g_dbMachine.CurrentData[CEIL8_MOTOR_DTH]);
    lcd[CEIL8_MOTOR_DTA]->display(g_systemDb->g_dbMachine.CurrentData[CEIL8_MOTOR_DTA]);
}
