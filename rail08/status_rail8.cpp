#include "status_rail8.h"
#include "resource_manager.h"

CStatusRail8::CStatusRail8(QWidget *parent) :
    CStatusBase8(parent)
{

    setObjectName("CStatusRail8");

    //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT
    m_iViewDir = VIEW_DIR_NORMAL;
    OnViewDirChange(m_iViewDir);

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
    //lbIcon[RAIL8_MOTOR_DTP]->setVisible(true);

    lcd[RAIL8_MOTOR_FID]->setLineWidth(2);
    lcd[RAIL8_MOTOR_SID]->setLineWidth(2);
    lcd[RAIL8_MOTOR_ANG]->setLineWidth(2);
    lcd[RAIL8_MOTOR_DTH]->setLineWidth(2);
    lcd[RAIL8_MOTOR_BEH]->setLineWidth(2);
    //lcd[RAIL8_MOTOR_DTP]->setLineWidth(2);

    lcd[RAIL8_MOTOR_FID]->setVisible(true);
    lcd[RAIL8_MOTOR_SID]->setVisible(true);
    lcd[RAIL8_MOTOR_ANG]->setVisible(true);
    lcd[RAIL8_MOTOR_DTH]->setVisible(true);
    lcd[RAIL8_MOTOR_BEH]->setVisible(true);
    //lcd[RAIL8_MOTOR_DTP]->setVisible(true);

    //设置LCD显示颜色，根据按键颜色
    lcd[RAIL8_MOTOR_FID]->setStyleSheet("color : rgb(48,155,70)");
    lcd[RAIL8_MOTOR_SID]->setStyleSheet("color : rgb(27,66,130)");
    lcd[RAIL8_MOTOR_ANG]->setStyleSheet("color : rgb(0,173,238)");
    lcd[RAIL8_MOTOR_DTH]->setStyleSheet("color : rgb(159,31,99)");
    lcd[RAIL8_MOTOR_BEH]->setStyleSheet("color : rgb(252,176,64)");
    //lcd[RAIL8_MOTOR_DTP]->setStyleSheet("color : rgb(252,176,64)");

}


void CStatusRail8::OnStatusFresh()
{
    CStatusBase::OnStatusFresh();

    //刷新显示数据
    int mFid = g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_FID] - g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_BEH];
    lcd[RAIL8_MOTOR_FID]->display(mFid);
    lcd[RAIL8_MOTOR_SID]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_SID]);
    lcd[RAIL8_MOTOR_ANG]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_ANG]);
    lcd[RAIL8_MOTOR_DTH]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_DTH]);
    lcd[RAIL8_MOTOR_BEH]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_BEH]);
    //lcd[RAIL8_MOTOR_DTP]->display(g_systemDb->g_dbMachine.CurrentData[RAIL8_MOTOR_DTP]);

}
//显示角度切换时，变幻控件位置
void CStatusRail8::OnViewDirChange(int mDir)
{
    /*
    lbIcon[RAIL8_MOTOR_FID]->setVisible(true);
    lbIcon[RAIL8_MOTOR_SID]->setVisible(true);
    lbIcon[RAIL8_MOTOR_ANG]->setVisible(true);
    lbIcon[RAIL8_MOTOR_DTH]->setVisible(true);
    lbIcon[RAIL8_MOTOR_BEH]->setVisible(true);
    //lbIcon[RAIL8_MOTOR_DTP]->setVisible(true);
    */
    m_iViewDir      = mDir;

    if(m_iViewDir == VIEW_DIR_NORMAL)
    {
        setGeometry(0,0,SYS_WID(150),SYS_HEI(350));

        lbIcon[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(0) ,SYS_WID(50), SYS_HEI(50));
        lbIcon[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(75) ,SYS_WID(50), SYS_HEI(50));
        lbIcon[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(150),SYS_WID(50), SYS_HEI(50));
        lbIcon[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(0), SYS_HEI(225),SYS_WID(50), SYS_HEI(50));
        lbIcon[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(0), SYS_HEI(300),SYS_WID(50), SYS_HEI(50));
        //lbIcon[RAIL8_MOTOR_DTP]->setGeometry(SYS_WID(0), SYS_HEI(300),SYS_WID(50), SYS_HEI(50));

        lcd[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(0) , SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(75) , SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(150), SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(0), SYS_HEI(225), SYS_WID(145), SYS_HEI(50));
        lcd[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(0), SYS_HEI(300), SYS_WID(145), SYS_HEI(50));
        //lcd[RAIL8_MOTOR_DTP]->setGeometry(SYS_WID(0), SYS_HEI(300), SYS_WID(145), SYS_HEI(50));

        if(g_dbsys.utility.mShutdownShow)
        {
            setGeometry(0,0,SYS_WID(150),SYS_HEI(350));

            lbIcon[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(0) ,SYS_WID(50), SYS_HEI(50));
            lbIcon[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(70) ,SYS_WID(50), SYS_HEI(50));
            lbIcon[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(138),SYS_WID(50), SYS_HEI(50));
            lbIcon[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(0), SYS_HEI(207),SYS_WID(50), SYS_HEI(50));
            lbIcon[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(0), SYS_HEI(276),SYS_WID(50), SYS_HEI(50));
            //lbIcon[RAIL8_MOTOR_DTP]->setGeometry(SYS_WID(0), SYS_HEI(276),SYS_WID(50), SYS_HEI(50));

            lcd[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(0) , SYS_WID(145), SYS_HEI(50));
            lcd[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(70) , SYS_WID(145), SYS_HEI(50));
            lcd[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(138), SYS_WID(145), SYS_HEI(50));
            lcd[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(0), SYS_HEI(207), SYS_WID(145), SYS_HEI(50));
            lcd[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(0), SYS_HEI(276), SYS_WID(145), SYS_HEI(50));
            //lcd[RAIL8_MOTOR_DTP]->setGeometry(SYS_WID(0), SYS_HEI(276), SYS_WID(145), SYS_HEI(50));
        }

        return;
    }

    if(m_iViewDir == VIEW_DIR_LEFT)
    {
        setGeometry(0,0,SYS_WID(300),SYS_HEI(300));

        lbIcon[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(152), SYS_HEI(0)  ,SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(152), SYS_HEI(0)  , SYS_WID(145), SYS_HEI(50));

        lbIcon[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(152), SYS_HEI(60) ,SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(152), SYS_HEI(60) , SYS_WID(145), SYS_HEI(50));

        lbIcon[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(2), SYS_HEI(120),SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(2), SYS_HEI(120), SYS_WID(145), SYS_HEI(50));

        lbIcon[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(2), SYS_HEI(0),SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(2), SYS_HEI(0), SYS_WID(145), SYS_HEI(50));

        lbIcon[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(2), SYS_HEI(60),SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(2), SYS_HEI(60), SYS_WID(145), SYS_HEI(50));

        //lbIcon[RAIL8_MOTOR_DTP]->setGeometry(SYS_WID(2), SYS_HEI(60),SYS_WID(50), SYS_HEI(50));
        //lcd[RAIL8_MOTOR_DTP]->setGeometry(SYS_WID(2), SYS_HEI(60), SYS_WID(145), SYS_HEI(50));
        return;
    }

    if(m_iViewDir == VIEW_DIR_RIGHT)
    {
        setGeometry(0,0,SYS_WID(300),SYS_HEI(300));

        lbIcon[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(60)  ,SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_FID]->setGeometry(SYS_WID(0), SYS_HEI(60)  , SYS_WID(145), SYS_HEI(50));

        lbIcon[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(120) ,SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_SID]->setGeometry(SYS_WID(0), SYS_HEI(120) , SYS_WID(145), SYS_HEI(50));

        lbIcon[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(180),SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_ANG]->setGeometry(SYS_WID(0), SYS_HEI(180), SYS_WID(145), SYS_HEI(50));

        lbIcon[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(150), SYS_HEI(60),SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_DTH]->setGeometry(SYS_WID(150), SYS_HEI(60), SYS_WID(145), SYS_HEI(50));

        lbIcon[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(150), SYS_HEI(120),SYS_WID(50), SYS_HEI(50));
        lcd[RAIL8_MOTOR_BEH]->setGeometry(SYS_WID(150), SYS_HEI(120), SYS_WID(145), SYS_HEI(50));

        //lbIcon[RAIL8_MOTOR_DTP]->setGeometry(SYS_WID(150), SYS_HEI(120),SYS_WID(50), SYS_HEI(50));
        //lcd[RAIL8_MOTOR_DTP]->setGeometry(SYS_WID(150), SYS_HEI(120), SYS_WID(145), SYS_HEI(50));
        return;
    }
}
