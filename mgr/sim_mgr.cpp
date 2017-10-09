#include "sim_mgr.h"

#include "./ceil10a/sim_ceil10a.h"
#include "./ceil10b/sim_ceil10b.h"
#include "./ceil08/sim_ceil8.h"
#include "./uarm10/sim_uarm10.h"
#include "./uarm08/sim_uarm8.h"
#include "./rail12/sim_rail12.h"
#include "./rail08/sim_rail8.h"
#include "./ndt08/sim_ndt8.h"

CSimMgr::CSimMgr()
{
    mSimBase = 0;
}

CSimBase * CSimMgr::simInit(int mpf)
{

    switch(mpf)
    {
    case PF_CEIL_10_A:
        mSimBase    = new CSimCeil10a();
        break;
    case PF_CEIL_10_B:
        mSimBase    = new CSimCeil10b();
        break;
    case PF_CEIL_08_A:
        mSimBase    = new CSimCeil8();
        break;
    case PF_UARM_10_A:
        mSimBase    = new CSimUarm10();
        break;
    case PF_UARM_08_A:
        mSimBase    = new CSimUarm8();
        break;
    case PF_RAIL_12_A:
        mSimBase    = new CSimRail12();
        break;
    case PF_RAIL_08_A:
        mSimBase    = new CSimRail8();
        break;
     case PF_NDT_8_A:
        mSimBase    = new CSimNdt8();
        break;
    default:
        mSimBase    = new CSimCeil10a();
        break;
    }

    return mSimBase;
}
