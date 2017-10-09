#include "smart_mgr.h"

#include "./ceil10a/smart_ceil10a.h"
#include "./ceil10b/smart_ceil10b.h"
#include "./ceil08/smart_ceil8.h"
#include "./uarm10/smart_uarm10.h"
#include "./uarm08/smart_uarm8.h"
#include "./rail12/smart_rail12.h"
#include "./rail08/smart_rail8.h"

CSmartMgr::CSmartMgr()
{
}

CSmartBase * CSmartMgr::smartInit(int mpf)
{
    switch(mpf)
    {
    case PF_CEIL_10_A:
        mSmartBase    = new CSmartCeil10a();
        break;
    case PF_CEIL_10_B:
        mSmartBase    = new CSmartCeil10b();
        break;
    case PF_CEIL_08_A:
        mSmartBase    = new CSmartCeil8();
        break;
    case PF_UARM_10_A:
        mSmartBase    = new CSmartUarm10();
        break;
    case PF_UARM_08_A:
        mSmartBase    = new CSmartUarm8();
        break;
    case PF_RAIL_12_A:
        mSmartBase    = new CSmartRail12();
        break;
    case PF_RAIL_08_A:
        mSmartBase    = new CSmartRail8();
        break;
    default:
        mSmartBase    = new CSmartCeil10a();
        break;
    }

    return mSmartBase;
}
