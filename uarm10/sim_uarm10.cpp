#include "sim_uarm10.h"
#include "resource_manager.h"

CSimUarm10::CSimUarm10(QWidget *parent) :
    CSimBase10(parent)
{

    setObjectName("CSimUarm10");

    resize(SYS_WID(90),SYS_HEI(90));

    m_iSmartMax = UARM10_SMART_MAX;
    m_iMotionMax= UARM10_MOTION_MAX;

    btnSim->setGeometry(SYS_WID(0),SYS_HEI(0),SYS_WID(65),SYS_HEI(65));

    sceneSim->addWidget(btnSim);

    viewSim->setScene(sceneSim);
    viewSim->setGeometry(SYS_WID(0),SYS_HEI(0),SYS_WID(70),SYS_HEI(70));
    viewSim->rotate(90);

    setGeometry(SYS_WID(625),SYS_HEI(13), SYS_WID(70),SYS_HEI( 70));

    SimulateDataInit();
}

void CSimUarm10::OnViewDirChange(int m_iViewDir)
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
void CSimUarm10::SimulateDataInit()
{

    //1 stand 1.8 position
    m_iPosSmart[SMART_POS_00][UARM10_MOTOR_HEI] = 150;
    m_iPosSmart[SMART_POS_00][UARM10_MOTOR_SID] = 180;
    m_iPosSmart[SMART_POS_00][UARM10_MOTOR_ANG] = 90;
    m_iPosSmart[SMART_POS_00][UARM10_MOTOR_DTA] = 0;

    //2 stand 1.1 position
    m_iPosSmart[SMART_POS_01][UARM10_MOTOR_HEI] = 150;
    m_iPosSmart[SMART_POS_01][UARM10_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_01][UARM10_MOTOR_ANG] = 90;
    m_iPosSmart[SMART_POS_01][UARM10_MOTOR_DTA] = 0;

    //3 slash
    m_iPosSmart[SMART_POS_02][UARM10_MOTOR_HEI] = 170;
    m_iPosSmart[SMART_POS_02][UARM10_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_02][UARM10_MOTOR_ANG] = 55;
    m_iPosSmart[SMART_POS_02][UARM10_MOTOR_DTA] = 35;

    //4 slash
    m_iPosSmart[SMART_POS_03][UARM10_MOTOR_HEI] = 100;
    m_iPosSmart[SMART_POS_03][UARM10_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_03][UARM10_MOTOR_ANG] = 120;
    m_iPosSmart[SMART_POS_03][UARM10_MOTOR_DTA] = -30;

    //5 table
    m_iPosSmart[SMART_POS_04][UARM10_MOTOR_HEI] = 160;
    m_iPosSmart[SMART_POS_04][UARM10_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_04][UARM10_MOTOR_ANG] = 0;
    m_iPosSmart[SMART_POS_04][UARM10_MOTOR_DTA] = 0;

    //6 slash
    m_iPosSmart[SMART_POS_05][UARM10_MOTOR_HEI] = 160;
    m_iPosSmart[SMART_POS_05][UARM10_MOTOR_SID] = 110;
    m_iPosSmart[SMART_POS_05][UARM10_MOTOR_ANG] = 30;
    m_iPosSmart[SMART_POS_05][UARM10_MOTOR_DTA] = -30;

    // 7 slash
    m_iPosSmart[SMART_POS_06][UARM10_MOTOR_HEI] = 180;
    m_iPosSmart[SMART_POS_06][UARM10_MOTOR_SID] = 150;
    m_iPosSmart[SMART_POS_06][UARM10_MOTOR_ANG] = 90;
    m_iPosSmart[SMART_POS_06][UARM10_MOTOR_DTA] = 0;

    m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_MIN] = 50;
    m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_MAX] = 180;
    m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_DAT] = 120;

    m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_MIN] = 50;
    m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_MAX] = 180;
    m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_DAT] = 120;

    m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_MIN] = -30;
    m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_MAX] = 120;
    m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_DAT] = 0;

    m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_MIN] = -45;
    m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_MAX] = 45;
    m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_DAT] = 0;


    for(int mIdx = 0 ; mIdx < UARM10_MOTION_MAX; mIdx++)
    {
        m_iMotor[mIdx][MOTOR_POS_STEP] = 1;

        m_iMotor[mIdx][MOTOR_POS_DIR]  = 0;
        m_iMotor[mIdx][MOTOR_POS_FLG] = 0;
    }

    for(int mIdx = 0 ; mIdx < UARM10_MOTION_MAX; mIdx++)
    {
        g_systemDb->g_dbMachine.CurrentData[mIdx] = m_iPosSmart[SMART_POS_04][mIdx];
    }
}

void CSimUarm10::OnSimulateKey(int mKey)
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
    default:
        break;
    }


    if(mSmartIndex >= 0 && mSmartIndex < UARM10_SMART_MAX )
    {
        for(int mIdx = 0 ; mIdx < UARM10_MOTION_MAX; mIdx++)
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
        m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_DIR] = 1;
        m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_FLG] = 1;
        m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x0021:
        m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0022:
        m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_DIR] = -1;
        m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_FLG] = 1;
        m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_TAR] = 50;
        timerSimFresh->start();
        break;
    case 0x0023:
        m_iMotor[UARM10_MOTOR_HEI][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0024:
        m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_DIR] = 1;
        m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_FLG] = 1;
        m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_TAR] = 180;
        timerSimFresh->start();
        break;
    case 0x0025:
        m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0026:
        m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_DIR] = -1;
        m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_FLG] = 1;
        m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_TAR] = 110;
        timerSimFresh->start();
        break;
    case 0x0027:
        m_iMotor[UARM10_MOTOR_SID][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x0028:
        m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_DIR] = 1;
        m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_FLG] = 1;
        m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_TAR] = 120;
        timerSimFresh->start();
        break;
    case 0x0029:
        m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002a:
        m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_DIR] = -1;
        m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_FLG] = 1;
        m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_TAR] = 0;
        timerSimFresh->start();
        break;
    case 0x002b:
        m_iMotor[UARM10_MOTOR_ANG][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002c:
        m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_DIR] = 1;
        m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_FLG] = 1;
        m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_TAR] = 30;
        timerSimFresh->start();
        break;
    case 0x002d:
        m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    case 0x002e:
        m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_DIR] = -1;
        m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_FLG] = 1;
        m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_TAR] = -30;
        timerSimFresh->start();
        break;
    case 0x002f:
        m_iMotor[UARM10_MOTOR_DTA][MOTOR_POS_FLG] = 0;
        timerSimFresh->stop();
        break;
    default:
        break;
    }

}

