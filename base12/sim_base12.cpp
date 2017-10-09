#include "sim_base12.h"
#include "resource_manager.h"

CSimBase12::CSimBase12(QWidget *parent) :
    CSimBase(parent)
{    

    btnSim->setParent(this);
    btnSim->setText("");

    OnViewDirChange(g_systemDb->g_startAngle);

}
void CSimBase12::OnSimPressed()
{

    if(sender() == btnSim)
    {
        if( g_systemDb->g_bMotionSimulate)
        {
            g_systemDb->g_bMotionSimulate = false;
            btnSim->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_OFF"));
            //btnSim->setText(QApplication::translate("CSimBase", "Demo\nOFF"));
            emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_MODE_DEMO);
        }else
        {
            g_systemDb->g_bCommunicate = true;
            g_systemDb->g_bMotionSimulate = true;

            g_systemDb->g_dbMachine.StateData[0] = 0;
            g_systemDb->g_dbMachine.StateData[1] = 0;
            g_systemDb->g_dbMachine.StateData[4] = 0xffff;

            for(int mIdx = 0 ;mIdx < m_iMotionMax ;mIdx++)
            {
                m_iMotor[mIdx][MOTOR_POS_DAT] = g_systemDb->g_dbMachine.CurrentData[mIdx];
            }

            btnSim->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_ON"));
            //btnSim->setText(QApplication::translate("CSimBase", "Demo\nON"));
            emit InfoMsgCtrl(INFO_CTRL_ADD,MSG_MODE_DEMO);
        }
    }
}
void CSimBase12::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(90),SYS_WID(90));
        btnSim->setGeometry(SYS_HEI(0), SYS_WID(6), SYS_HEI(90), SYS_WID(72));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(90),SYS_HEI(90));
        btnSim->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(90),SYS_HEI(90));
        btnSim->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }
}
