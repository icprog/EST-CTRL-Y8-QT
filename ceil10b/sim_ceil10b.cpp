#include "sim_ceil10b.h"
#include "resource_manager.h"
#include "qmath.h"


CSimCeil10b::CSimCeil10b(QWidget *parent) :
    CSimBase10(parent)
{
    setObjectName("CSimCeil10b");

    resize(SYS_HEI(90),SYS_WID(90));

    m_iSmartMax = CEIL10b_SMART_MAX;
    m_iMotionMax= CEIL10b_MOTION_MAX;

    btnSim->setGeometry(SYS_HEI(0),SYS_WID(0),SYS_HEI(65),SYS_WID(65));

    sceneSim->addWidget(btnSim);

    viewSim->setScene(sceneSim);
    viewSim->setGeometry(SYS_HEI(0),SYS_WID(0),SYS_HEI(70),SYS_WID(70));
    viewSim->rotate(90);

    setGeometry(SYS_HEI(625),SYS_WID(13), SYS_HEI(70),SYS_WID( 70));

    SimulateDataInit();
}
void CSimCeil10b::OnViewDirChange(int m_iViewDir)
{
    int m_rotAngle = 0;
    switch(m_iViewDir)
    {
    case VIEW_DIR_NORMAL:
        m_rotAngle = 90;
        break;
    case VIEW_DIR_LEFT:
        m_rotAngle = 0;
        break;
    case VIEW_DIR_RIGHT:
        m_rotAngle = 180;
        break;
    case VIEW_DIR_R180:
        m_rotAngle = 0;
        break;
    default:
        return;
    }
    viewSim->resetTransform();
    viewSim->rotate(m_rotAngle);

}

void CSimCeil10b::SimulateDataInit()
{

    //stand 1.8m
    m_iPosSmart[SMART_POS_00][CEIL10b_MOTOR_FID] = 120;
    m_iPosSmart[SMART_POS_00][CEIL10b_MOTOR_SID] = 180;
    m_iPosSmart[SMART_POS_00][CEIL10b_MOTOR_ANG] = 90;
    m_iPosSmart[SMART_POS_00][CEIL10b_MOTOR_DTH] = 120;
    m_iPosSmart[SMART_POS_00][CEIL10b_MOTOR_DTA] = 90;
    m_iPosSmart[SMART_POS_00][CEIL10b_MOTOR_CEP] = 0;

    // stand 1.1m
    m_iPosSmart[SMART_POS_01][CEIL10b_MOTOR_FID] = 120;
    m_iPosSmart[SMART_POS_01][CEIL10b_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_01][CEIL10b_MOTOR_ANG] = 90;
    m_iPosSmart[SMART_POS_01][CEIL10b_MOTOR_DTH] = 120;
    m_iPosSmart[SMART_POS_01][CEIL10b_MOTOR_DTA] = 90;
    m_iPosSmart[SMART_POS_01][CEIL10b_MOTOR_CEP] = 0;

    //stand slash
    m_iPosSmart[SMART_POS_02][CEIL10b_MOTOR_FID] = 160;
    m_iPosSmart[SMART_POS_02][CEIL10b_MOTOR_SID] = 100;
    m_iPosSmart[SMART_POS_02][CEIL10b_MOTOR_ANG] = 55;
    m_iPosSmart[SMART_POS_02][CEIL10b_MOTOR_DTH] = 90;
    m_iPosSmart[SMART_POS_02][CEIL10b_MOTOR_DTA] = 90;
    m_iPosSmart[SMART_POS_02][CEIL10b_MOTOR_CEP] = 0;

    //stand slash
    m_iPosSmart[SMART_POS_03][CEIL10b_MOTOR_FID] = 80;
    m_iPosSmart[SMART_POS_03][CEIL10b_MOTOR_SID] = 100;
    m_iPosSmart[SMART_POS_03][CEIL10b_MOTOR_ANG] = 120;
    m_iPosSmart[SMART_POS_03][CEIL10b_MOTOR_DTH] = 150;
    m_iPosSmart[SMART_POS_03][CEIL10b_MOTOR_DTA] = 90;
    m_iPosSmart[SMART_POS_03][CEIL10b_MOTOR_CEP] = 0;

    //stand position
    m_iPosSmart[SMART_POS_04][CEIL10b_MOTOR_FID] = 140;
    m_iPosSmart[SMART_POS_04][CEIL10b_MOTOR_SID] = 0;
    m_iPosSmart[SMART_POS_04][CEIL10b_MOTOR_ANG] = 0;
    m_iPosSmart[SMART_POS_04][CEIL10b_MOTOR_DTH] = 50;
    m_iPosSmart[SMART_POS_04][CEIL10b_MOTOR_DTA] = 0;
    m_iPosSmart[SMART_POS_04][CEIL10b_MOTOR_CEP] = 0;

    //table position
    m_iPosSmart[SMART_POS_05][CEIL10b_MOTOR_FID] = 180;
    m_iPosSmart[SMART_POS_05][CEIL10b_MOTOR_SID] = 100;
    m_iPosSmart[SMART_POS_05][CEIL10b_MOTOR_ANG] = 45;
    m_iPosSmart[SMART_POS_05][CEIL10b_MOTOR_DTH] = 110;
    m_iPosSmart[SMART_POS_05][CEIL10b_MOTOR_DTA] = 90;
    m_iPosSmart[SMART_POS_05][CEIL10b_MOTOR_CEP] = 0;

    //table slash
    m_iPosSmart[SMART_POS_06][CEIL10b_MOTOR_FID] = 160;
    m_iPosSmart[SMART_POS_06][CEIL10b_MOTOR_SID] = 90;
    m_iPosSmart[SMART_POS_06][CEIL10b_MOTOR_ANG] = -30;
    m_iPosSmart[SMART_POS_06][CEIL10b_MOTOR_DTH] = 110;
    m_iPosSmart[SMART_POS_06][CEIL10b_MOTOR_DTA] = 90;
    m_iPosSmart[SMART_POS_06][CEIL10b_MOTOR_CEP] = 0;

    //table slash
    m_iPosSmart[SMART_POS_07][CEIL10b_MOTOR_FID] = 170;
    m_iPosSmart[SMART_POS_07][CEIL10b_MOTOR_SID] = 150;
    m_iPosSmart[SMART_POS_07][CEIL10b_MOTOR_ANG] = 30;
    m_iPosSmart[SMART_POS_07][CEIL10b_MOTOR_DTH] = 110;
    m_iPosSmart[SMART_POS_07][CEIL10b_MOTOR_DTA] = 90;
    m_iPosSmart[SMART_POS_07][CEIL10b_MOTOR_CEP] = 0;

    m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_MIN] = 50;
    m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_MAX] = 180;
    m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_DAT] = 140;

    m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_MIN] = 50;
    m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_MAX] = 180;
    m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_DAT] = 120;

    m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_MIN] = -30;
    m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_MAX] = 120;
    m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_DAT] = 0;

    m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_MIN] = 50;
    m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_MAX] = 180;
    m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_DAT] = 110;

    m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_MIN] = 0;
    m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_MAX] = 120;
    m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_DAT] = 90;

    m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_MIN] = 50;
    m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_MAX] = 180;
    m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_DAT] = 100;

    for(int mIdx = 0 ; mIdx < CEIL10b_MOTION_MAX; mIdx++)
    {

        m_iMotor[mIdx][MOTOR_POS_STEP] = 1;
        m_iMotor[mIdx][MOTOR_POS_DIR]  = 0;
        m_iMotor[mIdx][MOTOR_POS_FLG] = 0;
    }

    for(int mIdx = 0 ; mIdx < CEIL10b_MOTION_MAX; mIdx++)
    {
        g_systemDb->g_dbMachine.CurrentData[mIdx] = m_iPosSmart[SMART_POS_05][mIdx];
    }

}


void CSimCeil10b::OnSimulateKey(int mKey)
{
    int mSmartIndex = mKey - 0x0050;

    if(mSmartIndex >= 0 && mSmartIndex < 8)
    {
        for(int mIdx = 0 ; mIdx < CEIL10b_MOTION_MAX ; mIdx++)
        {
            if(m_iMotor[mIdx][MOTOR_POS_DAT] > m_iPosSmart[mSmartIndex][mIdx])
            {
                m_iMotor[mIdx][MOTOR_POS_DIR] = -1;
                m_iMotor[mIdx][MOTOR_POS_FLG] = 1;
                m_iMotor[mIdx][MOTOR_POS_TAR] =  m_iPosSmart[mSmartIndex][mIdx];
            }else if(m_iMotor[mIdx][MOTOR_POS_DAT] < m_iPosSmart[mSmartIndex][mIdx])
            {
                m_iMotor[mIdx][MOTOR_POS_DIR] = 1;
                m_iMotor[mIdx][MOTOR_POS_FLG] = 1;
                m_iMotor[mIdx][MOTOR_POS_TAR] =  m_iPosSmart[mSmartIndex][mIdx];
            }else
            {
                m_iMotor[mIdx][MOTOR_POS_FLG] = 0 ;
            }
        }

        g_systemDb->g_dbMachine.StateData[2] = mSmartIndex + 1;

        g_systemDb->g_dbMachine.CurrentData[16] = 0;
        g_systemDb->g_dbMachine.CurrentData[17] = 0;
        g_systemDb->g_dbMachine.CurrentData[18] = 0;

        timerSimFresh->start();

        return;
    }

    switch( mKey)
    {
    case 0x0020:
        m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x0021:
        m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0022:
        m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_TAR] = 50;
        timerSimFresh->start();
        break;
    case 0x0023:
        m_iMotor[CEIL10b_MOTOR_FID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0024:
        m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x0025:
        m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0026:
        m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_TAR] = 0;
        timerSimFresh->start();
        break;
    case 0x0027:
        m_iMotor[CEIL10b_MOTOR_SID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0028:
        m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_TAR] = 120;
        timerSimFresh->start();
        break;
    case 0x0029:
        m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002a:
        m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_TAR] = -30;
        timerSimFresh->start();
        break;
    case 0x002b:
        m_iMotor[CEIL10b_MOTOR_ANG][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002c:
        m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x002d:
        m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002e:
        m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_TAR] = 50;
        timerSimFresh->start();
        break;
    case 0x002f:
        m_iMotor[CEIL10b_MOTOR_DTH][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0030:
        m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_TAR] = 120;
        timerSimFresh->start();
        break;
    case 0x0031:
        m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0032:
        m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_TAR] = 0;
        timerSimFresh->start();
        break;
    case 0x0033:
        m_iMotor[CEIL10b_MOTOR_DTA][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0034:
        m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x0035:
        m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0036:
        m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_TAR] = 50;
        timerSimFresh->start();
        break;
    case 0x0037:
        m_iMotor[CEIL10b_MOTOR_CEP][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0038:
        break;
    case 0x0039:
        break;
    case 0x003a:
        break;
    case 0x003b:
        break;
    case 0x003c:
        break;
    case 0x003d:
        break;
    case 0x003e:
        break;
    case 0x003f:
        break;
    case 0x0058:
        timerSimFresh->stop();
        g_systemDb->g_dbMachine.StateData[2] = 0;
        break;
    default:
        break;
    }

}


