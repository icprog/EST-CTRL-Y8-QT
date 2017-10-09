#include "./system/system_defines.h"

#include "fast_mgr.h"

#include "./base08/fast_base8.h"
#include "./base10/fast_base10.h"
#include "./base12/fast_base12.h"
#include "./ceil10b/fast_ceil10b.h"

CFastMgr::CFastMgr()
{
    mFastBase = 0;
}

CFastBase * CFastMgr::fastInit(int mpf)
{
    switch(mpf)
    {
    case PF_CEIL_10_A:
        mFastBase    = new CFastBase10();
        break;
    case PF_CEIL_10_B:
        mFastBase    = new CFastCeil10b();
        break;
    case PF_UARM_10_A:
        mFastBase    = new CFastBase10();
        break;
    case PF_RAIL_12_A:
        mFastBase    = new CFastBase12();
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        mFastBase    = new CFastBase8();
        break;
    default:
        mFastBase    = new CFastBase10();
        break;
    }

    return mFastBase;
}
