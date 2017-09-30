#include "quick_mgr.h"

#include "quick_ceil10a.h"
#include "quick_ceil10b.h"
#include "quick_uarm10.h"
#include "quick_rail12.h"
#include "quick_ceil8.h"
#include "quick_uarm8.h"
#include "quick_rail8.h"

#include "resource_manager.h"

CQuickMgr::CQuickMgr()
{

}


CQuickBase * CQuickMgr::quickInit(int mpf)
{
    switch(mpf)
    {
    case PF_CEIL_10_A:
         mQuickBase    = new CQuickCeil10a();
         break;
    case PF_CEIL_10_B:
        mQuickBase    = new CQuickCeil10b();
        break;
    case PF_UARM_10_A:
        mQuickBase    = new CQuickUarm10();
        break;
    case PF_RAIL_12_A:
        mQuickBase    = new CQuickRail12();
        break;
    case PF_CEIL_08_A:
        mQuickBase    = new CQuickCeil8();
        break;
    case PF_UARM_08_A:
        mQuickBase    = new CQuickUarm8();
        break;
    case PF_RAIL_08_A:
        mQuickBase    = new CQuickRail8();
        break;
    default:
        mQuickBase    = new CQuickCeil10a();
        break;
    }

    return mQuickBase;
}
