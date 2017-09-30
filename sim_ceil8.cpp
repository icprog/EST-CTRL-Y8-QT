#include "sim_ceil8.h"
#include "resource_manager.h"
#include "qmath.h"

CSimCeil8::CSimCeil8(QWidget *parent) :
    CSimBase8(parent)
{
    setObjectName("CSimCeil8");

    resize(SYS_WID(90),SYS_HEI(50));

    setGeometry(SYS_WID(400),SYS_HEI(0),SYS_WID(90),SYS_HEI(50));

    m_iSmartMax = CEIL8_SMART_MAX;
    m_iMotionMax= CEIL8_MOTION_MAX;

    btnSim->setParent(this);
    btnSim->setGeometry(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(50));

    SimulateDataInit();
}


void CSimCeil8::SimulateDataInit()
{

    // 1 stand 1.8m
    m_iPosSmart[SMART_POS_00][CEIL8_MOTOR_FID] = 140;
    m_iPosSmart[SMART_POS_00][CEIL8_MOTOR_SID] = 180;
    m_iPosSmart[SMART_POS_00][CEIL8_MOTOR_ANG] = 90;
    m_iPosSmart[SMART_POS_00][CEIL8_MOTOR_DTH] = 140;
    m_iPosSmart[SMART_POS_00][CEIL8_MOTOR_DTA] = 90;

    // 2 stand 1.1m
    m_iPosSmart[SMART_POS_01][CEIL8_MOTOR_FID] = 140;
    m_iPosSmart[SMART_POS_01][CEIL8_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_01][CEIL8_MOTOR_ANG] = 90;
    m_iPosSmart[SMART_POS_01][CEIL8_MOTOR_DTH] = 140;
    m_iPosSmart[SMART_POS_01][CEIL8_MOTOR_DTA] = 90;

    // 3 stand slash
    m_iPosSmart[SMART_POS_02][CEIL8_MOTOR_FID] = 170;
    m_iPosSmart[SMART_POS_02][CEIL8_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_02][CEIL8_MOTOR_ANG] = 55;
    m_iPosSmart[SMART_POS_02][CEIL8_MOTOR_DTH] = 95;
    m_iPosSmart[SMART_POS_02][CEIL8_MOTOR_DTA] = 90;

    // 4 stand slash
    m_iPosSmart[SMART_POS_03][CEIL8_MOTOR_FID] = 90;
    m_iPosSmart[SMART_POS_03][CEIL8_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_03][CEIL8_MOTOR_ANG] = 120;
    m_iPosSmart[SMART_POS_03][CEIL8_MOTOR_DTH] = 150;
    m_iPosSmart[SMART_POS_03][CEIL8_MOTOR_DTA] = 90;

    // 5 table
    m_iPosSmart[SMART_POS_04][CEIL8_MOTOR_FID] = 160;
    m_iPosSmart[SMART_POS_04][CEIL8_MOTOR_SID] = 0;
    m_iPosSmart[SMART_POS_04][CEIL8_MOTOR_ANG] = 0;
    m_iPosSmart[SMART_POS_04][CEIL8_MOTOR_DTH] = 50;
    m_iPosSmart[SMART_POS_04][CEIL8_MOTOR_DTA] = 0;

    // 6 table slash
    m_iPosSmart[SMART_POS_05][CEIL8_MOTOR_FID] = 160;
    m_iPosSmart[SMART_POS_05][CEIL8_MOTOR_SID] = 60;
    m_iPosSmart[SMART_POS_05][CEIL8_MOTOR_ANG] = 30;
    m_iPosSmart[SMART_POS_05][CEIL8_MOTOR_DTH] = 50;
    m_iPosSmart[SMART_POS_05][CEIL8_MOTOR_DTA] = 0;

    // 7 slash
    m_iPosSmart[SMART_POS_06][CEIL8_MOTOR_FID] = 160;
    m_iPosSmart[SMART_POS_06][CEIL8_MOTOR_SID] = 130;
    m_iPosSmart[SMART_POS_06][CEIL8_MOTOR_ANG] = 0;
    m_iPosSmart[SMART_POS_06][CEIL8_MOTOR_DTH] = 100;
    m_iPosSmart[SMART_POS_06][CEIL8_MOTOR_DTA] = 90;

    m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_MIN] = 50;
    m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_MAX] = 180;
    m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_DAT] = 120;

    m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_MIN] = 0;
    m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_MAX] = 180;
    m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_DAT] = 120;

    m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_MIN] = -30;
    m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_MAX] = 120;
    m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_DAT] = 0;

    m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_MIN] = 50;
    m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_MAX] = 180;
    m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_DAT] = 120;

    m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_MIN] = -30;
    m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_MAX] = 90;
    m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_DAT] = 0;

    for(int mIdx = 0 ; mIdx < CEIL8_MOTION_MAX; mIdx++)
    {
        m_iMotor[mIdx][MOTOR_POS_STEP] = 1;

        m_iMotor[mIdx][MOTOR_POS_DIR]  = 0;
        m_iMotor[mIdx][MOTOR_POS_FLG] = 0;

    }

    for(int mIdx = 0 ; mIdx < CEIL8_MOTION_MAX; mIdx++)
    {
        g_systemDb->g_dbMachine.CurrentData[mIdx] = m_iPosSmart[SMART_POS_01][mIdx];
    }

}

void CSimCeil8::OnSimulateKey(int mKey)
{
    int mSmartIndex = -1;

    switch(mKey)
    {
    case 0x0050:
        break;
    case 0x0051:
        mSmartIndex = 0;
        break;
    case 0x0053:
        mSmartIndex = 1;
        break;
    case 0x0057:
        mSmartIndex = 2;
        break;
    case 0x0059:
        mSmartIndex = 3;
        break;
    case 0x005b:
        mSmartIndex = 4;
        break;
    case 0x005d:
        mSmartIndex = 5;
        break;
    default:
        break;
    }

    if(mSmartIndex >= 0 && mSmartIndex < CEIL8_SMART_MAX )
    {
        for(int mIdx = 0 ; mIdx < CEIL8_MOTION_MAX; mIdx++)
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

        timerSimFresh->start();

        return;
    }

    switch( mKey)
    {
    case 0x0020:
        m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x0021:
        m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0022:
        m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_TAR] = 50;
        timerSimFresh->start();
        break;
    case 0x0023:
        m_iMotor[CEIL8_MOTOR_FID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0024:
        m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x0025:
        m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0026:
        m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_TAR] = 0;
        timerSimFresh->start();
        break;
    case 0x0027:
        m_iMotor[CEIL8_MOTOR_SID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0028:
        m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_TAR] = 120;
        timerSimFresh->start();
        break;
    case 0x0029:
        m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002a:
        m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_TAR] = -30;
        timerSimFresh->start();
        break;
    case 0x002b:
        m_iMotor[CEIL8_MOTOR_ANG][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002c:
        m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x002d:
        m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002e:
        m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_TAR] = 50;
        timerSimFresh->start();
        break;
    case 0x002f:
        m_iMotor[CEIL8_MOTOR_DTH][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0030:
        m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_DIR] = 1;
        m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_TAR] = 120;
        timerSimFresh->start();
        break;
    case 0x0031:
        m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0032:
        m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_DIR] = -1;
        m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_FLG] = 1;
        m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_TAR] = 0;
        timerSimFresh->start();
        break;
    case 0x0033:
        m_iMotor[CEIL8_MOTOR_DTA][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    default:
        break;
    }

}


