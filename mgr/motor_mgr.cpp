#include "motor_mgr.h"
#include "resource_manager.h"

CMotorMgr::CMotorMgr()
{
    for(int mIdx = 0 ; mIdx < SYSTEM_MOTOR_MAX ; mIdx++)
    {
        g_motorConfig[mIdx] = 0;
    }
}
int CMotorMgr::getLimitMin(int motorId)
{

    return g_motorNdt->getLimitMin(motorId);

}
int CMotorMgr::getLimitMax(int motorId)
{
    return g_motorNdt->getLimitMax(motorId);
}

void CMotorMgr::motorInit(int mpf)
{
    int mCounter;

    m_iPlatform = mpf;

    switch(m_iPlatform)
    {
    case PF_NDT_8_A:

        for(mCounter = NDT8a_MOTOR_FID ; mCounter <= NDT8a_MOTOR_Y2 ; mCounter++)
            g_motorConfig[mCounter] = new CMotorBase(PF_NDT_8_A,mCounter);
        break;

    case PF_RF_8_A:
        for(mCounter = RF8A_MOTOR_FID ; mCounter <= RF8A_MOTOR_SGV ; mCounter++)
            g_motorConfig[mCounter] = new CMotorBase(PF_RF_8_A,mCounter);

        break;
    case PF_NDT_10_A:
        g_motorNdt = new CMotorNdt();

    case PF_CEIL_10_A:
        for(mCounter = CEIL10a_MOTOR_FID ; mCounter <= CEIL10a_MOTOR_DTP ; mCounter++)
            g_motorConfig[mCounter] = new CMotorBase(PF_CEIL_10_A,mCounter);

        break;
    case PF_CEIL_10_B:
        for(mCounter = CEIL10b_MOTOR_FID ; mCounter <= CEIL10b_MOTOR_CEP ; mCounter++)
            g_motorConfig[mCounter] = new CMotorBase(PF_CEIL_10_B,mCounter);

        break;
    case PF_CEIL_08_A:
        for(mCounter = CEIL8_MOTOR_FID ; mCounter <= CEIL8_MOTOR_DTA ; mCounter++)
            g_motorConfig[mCounter]  = new CMotorBase(PF_CEIL_08_A,mCounter);

        break;
    case PF_UARM_10_A:
        for(mCounter = UARM10_MOTOR_HEI ; mCounter <= UARM10_MOTOR_DTA ; mCounter++)
            g_motorConfig[mCounter] = new CMotorBase(PF_UARM_10_A,mCounter);

        break;
    case PF_UARM_08_A:
        for(mCounter = UARM8_MOTOR_HEI ; mCounter <= UARM8_MOTOR_DTA ; mCounter++)
            g_motorConfig[mCounter]  = new CMotorBase(PF_UARM_08_A,mCounter);

        break;
    case PF_RAIL_12_A:
        for(mCounter = RAIL10_MOTOR_FID ; mCounter <= RAIL10_MOTOR_DTP ; mCounter++)
            g_motorConfig[mCounter] = new CMotorBase(PF_RAIL_12_A,mCounter);

        break;
    case PF_RAIL_08_A:
        for(mCounter = RAIL8_MOTOR_FID ; mCounter <= RAIL8_MOTOR_DTP ; mCounter++)
            g_motorConfig[mCounter]  = new CMotorBase(PF_RAIL_08_A,mCounter);

        break;
    default:
        return;
    }

    int mPre,mNext;
    CMotorBase * pMotorPre;
    CMotorBase * pMotorNext;

    for(int mIdx = 0 ; mIdx < SYSTEM_MOTOR_MAX ; mIdx++)
    {
        mPre    = mIdx - 1;
        if(mPre < 0)
            pMotorPre = 0;
        else
            pMotorPre = g_motorConfig[mPre];

        mNext   = mIdx + 1;
        if(mNext >= SYSTEM_MOTOR_MAX)
            pMotorNext = 0;
        else
            pMotorNext = g_motorConfig[mNext];

        if(g_motorConfig[mIdx])
            g_motorConfig[mIdx]->SetWidgetIndex(pMotorNext,pMotorPre);
    }

    //工业探伤项目不执行后续内容
    if(m_iPlatform == PF_NDT_10_A)
        return;

    if(m_iPlatform == PF_NDT_8_A)
        return;

    if(m_iPlatform == PF_RF_8_A)
        return;

    //获取位置校正数据
    if(!g_systemDb->g_bPosDataValid)
    {
        if(g_taskComCtrl)
            g_taskComCtrl->CreateTask(CMD_FUNC_PARAM,0,0);
    }
}

int CMotorMgr::motorCheck()
{
    int mCounter,mRes;

    switch(m_iPlatform)
    {
    case PF_NDT_8_A:
    case PF_RF_8_A:
    case PF_NDT_10_A:
    case PF_CEIL_10_A:
        for(mCounter = CEIL10a_MOTOR_FID ; mCounter <= CEIL10a_MOTOR_DTP ; mCounter++)
        {
            mRes = g_motorConfig[mCounter]->DataValidCheck();
            if(mRes != 0)
                return mRes;
        }
        break;
    case PF_CEIL_10_B:
        for(mCounter = CEIL10b_MOTOR_FID ; mCounter <= CEIL10b_MOTOR_CEP ; mCounter++)
        {
            mRes = g_motorConfig[mCounter]->DataValidCheck();
            if(mRes != 0)
                return mRes;
        }

        break;
    case PF_CEIL_08_A:
        for(mCounter = CEIL8_MOTOR_FID ; mCounter <= CEIL8_MOTOR_DTA ; mCounter++)
        {
            mRes = g_motorConfig[mCounter]->DataValidCheck();
            if(mRes != 0)
                return mRes;
        }

        break;
    case PF_UARM_10_A:
        for(mCounter = UARM10_MOTOR_HEI ; mCounter <= UARM10_MOTOR_DTA ; mCounter++)
        {
            mRes = g_motorConfig[mCounter]->DataValidCheck();
            if(mRes != 0)
                return mRes;
        }

        break;
    case PF_UARM_08_A:
        for(mCounter = UARM8_MOTOR_HEI ; mCounter <= UARM8_MOTOR_DTA ; mCounter++)
        {
            mRes = g_motorConfig[mCounter]->DataValidCheck();
            if(mRes != 0)
                return mRes;
        }

        break;
    case PF_RAIL_12_A:
        for(mCounter = RAIL10_MOTOR_FID ; mCounter <= RAIL10_MOTOR_DTP ; mCounter++)
        {
            mRes = g_motorConfig[mCounter]->DataValidCheck();
            if(mRes != 0)
                return mRes;
        }

        break;
    case PF_RAIL_08_A:
        for(mCounter = RAIL8_MOTOR_FID ; mCounter <= RAIL8_MOTOR_DTP ; mCounter++)
        {
            mRes = g_motorConfig[mCounter]->DataValidCheck();
            if(mRes != 0)
                return mRes;
        }
        break;
    default:
        return -1;
    }

    return -1;
}
