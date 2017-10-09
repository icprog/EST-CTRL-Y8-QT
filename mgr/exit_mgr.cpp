#include "./system/system_defines.h"

#include "exit_mgr.h"

#include "./base08/exit_base8.h"
#include "./base10/exit_base10.h"
#include "./base12/exit_base12.h"
#include "./ndt10/exit_base_ndt10.h"

CExitMgr::CExitMgr()
{
    setObjectName("CExitMgr");

    mPowerBase = 0;
}


CExitBase * CExitMgr::exitInit(int mpf)
{
    switch(mpf)
    {
    case PF_NDT_8_A:
    case PF_RF_8_A:
    case PF_NDT_10_A:
        mPowerBase    = new CExitBaseNdt();
        break;
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
        mPowerBase    = new CExitBase10();
        break;
    case PF_RAIL_12_A:
        mPowerBase    = new CExitBase12();
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        mPowerBase    = new CExitBase8();
        break;
    default:
        mPowerBase    = new CExitBase10();
        break;
    }

    return mPowerBase;
}
