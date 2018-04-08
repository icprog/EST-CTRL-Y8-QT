#include "title_mgr.h"

#include "./sys/system_defines.h"


#include "./ceil08a/title_ceil08a.h"
#include "./ceil10a/title_ceil10a.h"
#include "./ceil10b/title_ceil10b.h"
#include "./uarm08a/title_uarm08a.h"
#include "./uarm08b/title_uarm08b.h"
#include "./rail08a/title_rail08a.h"
#include "./rail08b/title_rail08b.h"
#include "./rail12a/title_rail12a.h"


CTitleMgr::CTitleMgr()
{
    mTitleBase = 0;
}

CTitleBase * CTitleMgr::titleInit(int mpf)
{
    switch(mpf)
    {
#ifdef USE_CEIL_10_A
    case PF_CEIL_10_A:
        mTitleBase    = new CTitleCeil10a();
        break;
#endif
#ifdef USE_CEIL_10_B
    case PF_CEIL_10_B:
        mTitleBase    = new CTitleCeil10b();
        break;
#endif
#ifdef USE_UARM_08_B
    case PF_UARM_08_B:
        mTitleBase    = new CTitleUarm08b();
        break;
#endif
#ifdef USE_RAIL_12_A
    case PF_RAIL_12_A:
        mTitleBase    = new CTitleRail12();
        break;
#endif
#ifdef USE_CEIL_08_A
    case PF_CEIL_08_A:
        mTitleBase    = new CTitleCeil08a();
        break;
#endif
#ifdef USE_UARM_08_A
    case PF_UARM_08_A:
        mTitleBase    = new CTitleUarm08a();
        break;
#endif
#ifdef USE_RAIL_08_A
    case PF_RAIL_08_A:
        mTitleBase    = new CTitleRail08a();
        break;
#endif
#ifdef USE_RAIL_08_B
    case PF_RAIL_08_B:
        mTitleBase    = new CTitleRail08b();
        break;
#endif
    default:
        mTitleBase    = new CTitleBase();
        break;
    }
    return mTitleBase;
}
