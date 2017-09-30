#include "system_defines.h"

#include "curtain_mgr.h"

#include "curtain_base8.h"
#include "curtain_base10.h"
#include "curtain_base12.h"

CCurtainMgr::CCurtainMgr()
{
    mCurtainBase = 0;
}

CCurtainBase * CCurtainMgr::curtainInit(int mpf)
{
    switch(mpf)
    {
    case PF_NDT_8_A:
    case PF_RF_8_A:
    case PF_NDT_10_A:
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
        mCurtainBase    = new CCurtainBase10();
        break;
    case PF_RAIL_12_A:
        mCurtainBase    = new CCurtainBase12();
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        mCurtainBase    = new CCurtainBase8();
        break;
    default:
        mCurtainBase    = new CCurtainBase10();
        break;
    }

    return mCurtainBase;
}
