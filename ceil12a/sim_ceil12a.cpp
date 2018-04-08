#include "sim_rail12a.h"

#ifdef USE_CEIL_12_A

CSimCeil12a::CSimCeil12a(QWidget *parent) :
    CSimBase12(parent)
{

    setObjectName("CSimCeil12a");

    m_iSmartMax = RAIL8_SMART_MAX;
    m_iMotionMax= RAIL8_MOTION_MAX;

    m_iDisplayText = g_sysDb->value("CSimCeil12a/DisplayText",false).toInt();

    SimulateDataInit();

}


void CSimCeil12a::SimulateDataInit()
{

    //1 stand 1.8 position
    m_iPosSmart[SmartPos00][MOTOR_FID] = 150;
    m_iPosSmart[SmartPos00][MOTOR_SID] = 180;
    m_iPosSmart[SmartPos00][MOTOR_ANG] = 90;
    m_iPosSmart[SmartPos00][MOTOR_DTH] = 150;
    m_iPosSmart[SmartPos00][MOTOR_BEH] = 40;
    m_iPosSmart[SmartPos00][MOTOR_DTP] = 200;

    //2 stand 1.1 position
    m_iPosSmart[SmartPos01][MOTOR_FID] = 150;
    m_iPosSmart[SmartPos01][MOTOR_SID] = 110;
    m_iPosSmart[SmartPos01][MOTOR_ANG] = 90;
    m_iPosSmart[SmartPos01][MOTOR_DTH] = 150;
    m_iPosSmart[SmartPos01][MOTOR_BEH] = 40;
    m_iPosSmart[SmartPos01][MOTOR_DTP] = 110;

    //3 slash
    m_iPosSmart[SmartPos02][MOTOR_FID] = 170;
    m_iPosSmart[SmartPos02][MOTOR_SID] = 130;
    m_iPosSmart[SmartPos02][MOTOR_ANG] = 65;
    m_iPosSmart[SmartPos02][MOTOR_DTH] = 65;
    m_iPosSmart[SmartPos02][MOTOR_BEH] = 40;
    m_iPosSmart[SmartPos02][MOTOR_DTP] = 180;

    //4 slash
    m_iPosSmart[SmartPos03][MOTOR_FID] = 70;
    m_iPosSmart[SmartPos03][MOTOR_SID] = 120;
    m_iPosSmart[SmartPos03][MOTOR_ANG] = 115;
    m_iPosSmart[SmartPos03][MOTOR_DTH] = 160;
    m_iPosSmart[SmartPos03][MOTOR_BEH] = 40;
    m_iPosSmart[SmartPos03][MOTOR_DTP] = 240;

    //5 table
    m_iPosSmart[SmartPos04][MOTOR_FID] = 160;
    m_iPosSmart[SmartPos04][MOTOR_SID] = 220;
    m_iPosSmart[SmartPos04][MOTOR_ANG] = 0;
    m_iPosSmart[SmartPos04][MOTOR_DTH] = 160;
    m_iPosSmart[SmartPos04][MOTOR_BEH] = 70;
    m_iPosSmart[SmartPos04][MOTOR_DTP] = 220;

    //6 slash
    m_iPosSmart[SmartPos05][MOTOR_FID] = 150;
    m_iPosSmart[SmartPos05][MOTOR_SID] = 220;
    m_iPosSmart[SmartPos05][MOTOR_ANG] = 25;
    m_iPosSmart[SmartPos05][MOTOR_DTH] = 140;
    m_iPosSmart[SmartPos05][MOTOR_BEH] = 70;
    m_iPosSmart[SmartPos05][MOTOR_DTP] = 180;

    // 7 slash
    m_iPosSmart[SmartPos06][MOTOR_FID] = 150;
    m_iPosSmart[SmartPos06][MOTOR_SID] = 180;
    m_iPosSmart[SmartPos06][MOTOR_ANG] = -20;
    m_iPosSmart[SmartPos06][MOTOR_DTH] = 90;
    m_iPosSmart[SmartPos06][MOTOR_BEH] = 70;
    m_iPosSmart[SmartPos06][MOTOR_DTP] = 240;

    m_iMotor[MOTOR_FID][MOTOR_POS_MIN] = 50;
    m_iMotor[MOTOR_FID][MOTOR_POS_MAX] = 180;
    m_iMotor[MOTOR_FID][MOTOR_POS_DAT] = 120;

    m_iMotor[MOTOR_SID][MOTOR_POS_MIN] = 50;
    m_iMotor[MOTOR_SID][MOTOR_POS_MAX] = 180;
    m_iMotor[MOTOR_SID][MOTOR_POS_DAT] = 120;

    m_iMotor[MOTOR_ANG][MOTOR_POS_MIN] = -30;
    m_iMotor[MOTOR_ANG][MOTOR_POS_MAX] = 120;
    m_iMotor[MOTOR_ANG][MOTOR_POS_DAT] = 0;

    m_iMotor[MOTOR_DTH][MOTOR_POS_MIN] = 50;
    m_iMotor[MOTOR_DTH][MOTOR_POS_MAX] = 180;
    m_iMotor[MOTOR_DTH][MOTOR_POS_DAT] = 120;

    m_iMotor[MOTOR_BEH][MOTOR_POS_MIN] = 40;
    m_iMotor[MOTOR_BEH][MOTOR_POS_MAX] = 70;
    m_iMotor[MOTOR_BEH][MOTOR_POS_DAT] = 60;

    m_iMotor[MOTOR_DTP][MOTOR_POS_MIN] = 180;
    m_iMotor[MOTOR_DTP][MOTOR_POS_MAX] = 240;
    m_iMotor[MOTOR_DTP][MOTOR_POS_DAT] = 200;


    for(int mIdx = 0 ; mIdx < RAIL8_MOTION_MAX; mIdx++)
    {
        m_iMotor[mIdx][MOTOR_POS_STEP] = 1;
        m_iMotor[mIdx][MOTOR_POS_DIR]  = 0;
        m_iMotor[mIdx][MOTOR_POS_FLG] = 0;
    }

    for(int mIdx = 0 ; mIdx < RAIL8_MOTION_MAX; mIdx++)
    {
        g_sysDb->CurrentData[mIdx] = m_iPosSmart[SmartPos04][mIdx];
    }
}


void CSimCeil12a::OnSimulateKey(int mKey)
{
    int mSmartIndex = -1;

    switch(mKey)
    {
    case 0x0050:
        break;
    case 0x0051:
        mSmartIndex = 0;
        break;
    case 0x0052:
        mSmartIndex = 1;
        break;
    case 0x0053:
        mSmartIndex = 2;
        break;
    case 0x0054:
        mSmartIndex = 3;
        break;
    case 0x0055:
        mSmartIndex = 4;
        break;
    case 0x0056:
        mSmartIndex = 5;
        break;
    case 0x0057:
        mSmartIndex = 6;
        break;
    default:
        break;
    }

    if(mSmartIndex >= 0 && mSmartIndex < RAIL8_SMART_MAX )
    {
        for(int mIdx = 0 ; mIdx < RAIL8_MOTION_MAX; mIdx++)
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

        g_sysDb->StateData[2] = mSmartIndex + 1;

        timerSimFresh->start();

        return;
    }

    switch( mKey)
    {
    case 0x0020:
        m_iMotor[MOTOR_FID][MOTOR_POS_DIR] = 1;
        m_iMotor[MOTOR_FID][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_FID][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x0021:
        m_iMotor[MOTOR_FID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0022:
        m_iMotor[MOTOR_FID][MOTOR_POS_DIR] = -1;
        m_iMotor[MOTOR_FID][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_FID][MOTOR_POS_TAR] = 50;
        timerSimFresh->start();
        break;
    case 0x0023:
        m_iMotor[MOTOR_FID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0024:
        m_iMotor[MOTOR_SID][MOTOR_POS_DIR] = 1;
        m_iMotor[MOTOR_SID][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_SID][MOTOR_POS_TAR] = 310;
        timerSimFresh->start();
        break;
    case 0x0025:
        m_iMotor[MOTOR_SID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0026:
        m_iMotor[MOTOR_SID][MOTOR_POS_DIR] = -1;
        m_iMotor[MOTOR_SID][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_SID][MOTOR_POS_TAR] = 110;
        timerSimFresh->start();
        break;
    case 0x0027:
        m_iMotor[MOTOR_SID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0028:
        m_iMotor[MOTOR_ANG][MOTOR_POS_DIR] = 1;
        m_iMotor[MOTOR_ANG][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_ANG][MOTOR_POS_TAR] = 120;
        timerSimFresh->start();
        break;
    case 0x0029:
        m_iMotor[MOTOR_ANG][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002a:
        m_iMotor[MOTOR_ANG][MOTOR_POS_DIR] = -1;
        m_iMotor[MOTOR_ANG][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_ANG][MOTOR_POS_TAR] = -30;
        timerSimFresh->start();
        break;
    case 0x002b:
        m_iMotor[MOTOR_ANG][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002c:
        m_iMotor[MOTOR_DTH][MOTOR_POS_DIR] = 1;
        m_iMotor[MOTOR_DTH][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_DTH][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x002d:
        m_iMotor[MOTOR_DTH][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002e:
        m_iMotor[MOTOR_DTH][MOTOR_POS_DIR] = -1;
        m_iMotor[MOTOR_DTH][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_DTH][MOTOR_POS_TAR] = 50;
        timerSimFresh->start();
        break;
    case 0x002f:
        m_iMotor[MOTOR_DTH][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0030:
        m_iMotor[MOTOR_BEH][MOTOR_POS_DIR] = 1;
        m_iMotor[MOTOR_BEH][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_BEH][MOTOR_POS_TAR] = 70;
        timerSimFresh->start();
        break;
    case 0x0031:
        m_iMotor[MOTOR_BEH][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0032:
        m_iMotor[MOTOR_BEH][MOTOR_POS_DIR] = -1;
        m_iMotor[MOTOR_BEH][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_BEH][MOTOR_POS_TAR] = 40;
        timerSimFresh->start();
        break;
    case 0x0033:
        m_iMotor[MOTOR_BEH][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0034:
        m_iMotor[MOTOR_DTP][MOTOR_POS_DIR] = 1;
        m_iMotor[MOTOR_DTP][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_DTP][MOTOR_POS_TAR] = 264;
        timerSimFresh->start();
        break;
    case 0x0035:
        m_iMotor[MOTOR_DTP][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0036:
        m_iMotor[MOTOR_DTP][MOTOR_POS_DIR] = -1;
        m_iMotor[MOTOR_DTP][MOTOR_POS_FLG] = 1;
        m_iMotor[MOTOR_DTP][MOTOR_POS_TAR] = 170;
        timerSimFresh->start();
        break;
    case 0x0037:
        m_iMotor[MOTOR_DTP][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    default:
        break;
    }

}

#endif
