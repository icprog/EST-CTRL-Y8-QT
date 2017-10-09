#include "status_mgr.h"

#include "./ceil08/status_ceil8.h"
#include "./uarm10/status_uarm10.h"
#include "./uarm08/status_uarm8.h"
#include "./rail12/status_rail12.h"
#include "./rail08/status_rail8.h"
#include "./ceil10a/status_ceil10a.h"
#include "./ceil10b/status_ceil10b.h"

CStatusMgr::CStatusMgr()
{
    mStatusBase = 0;
}

CStatusBase * CStatusMgr::statusInit(int mpf)
{
    //根据平台选择，创建Status
    switch(mpf)
    {
    case PF_CEIL_10_A:
        mStatusBase    = new CStatusCeil10a();
        break;
    case PF_CEIL_10_B:
        mStatusBase    = new CStatusCeil10b();
        break;
    case PF_CEIL_08_A:
        mStatusBase    = new CStatusCeil8();
        break;
    case PF_UARM_10_A:
        mStatusBase    = new CStatusUarm10();
        break;
    case PF_UARM_08_A:
        mStatusBase    = new CStatusUarm8();
        break;
    case PF_RAIL_12_A:
        mStatusBase    = new CStatusRail12();
        break;
    case PF_RAIL_08_A:
        mStatusBase    = new CStatusRail8();
        break;
    default:
        mStatusBase    = new CStatusCeil10a();
        break;
    }

    return mStatusBase;
}
