#include "sim_ndt8.h"
#include "resource_manager.h"


CSimNdt8::CSimNdt8(QWidget *parent) :
    CSimBase8(parent)
{

    setObjectName("CSimNdt8");

    resize(SYS_WID(90),SYS_HEI(50));

    setGeometry(SYS_WID(400),SYS_HEI(0),SYS_WID(90),SYS_HEI(50));

    m_iSmartMax = 0;
    m_iMotionMax= 0;

    btnSim->setParent(this);
    btnSim->setGeometry(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(50));

    SimulateDataInit();
}


void CSimNdt8::SimulateDataInit()
{
    for(int mIdx = 0 ; mIdx < SYS_CURRENT_DATA_SIZE ; mIdx++)
    {
        g_systemDb->g_dbMachine.CurrentData[mIdx] = 0;
    }
}

void CSimNdt8::OnSimulateKey(int )
{

}

void CSimNdt8::OnSimFresh()
{

}

