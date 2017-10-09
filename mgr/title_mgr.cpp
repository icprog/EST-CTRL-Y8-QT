#include "title_mgr.h"

#include "./base08/title_base8.h"
#include "./base10/title_base10.h"
#include "./base12/title_base12.h"

CTitleMgr::CTitleMgr()
{
    mTitleBase = 0;
}


CTitleBase * CTitleMgr::titleInit(int mpf)
{
    switch(mpf)
    {
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
        mTitleBase    = new CTitleBase10();
        break;
    case PF_RAIL_12_A:
        mTitleBase    = new CTitleBase12();
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        mTitleBase    = new CTitleBase8();
        break;
    default:
        mTitleBase    = new CTitleBase10();
        break;
    }
    return mTitleBase;
}
