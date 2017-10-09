#include "motion_mgr.h"

#include "./ceil08/motion_ceil8.h"
#include "./uarm08/motion_uarm8.h"
#include "./rail08/motion_rail8.h"
#include "./rail12/motion_rail12.h"
#include "./uarm10/motion_uarm10.h"
#include "./ceil10a/motion_ceil10a.h"
#include "./ceil10b/motion_ceil10b.h"

CMotionMgr::CMotionMgr()
{
    mMotionBase = 0;
}

CMotionBase * CMotionMgr::motionInit(int mpf)
{

    switch(mpf)
    {
    case PF_CEIL_10_A:
        mMotionBase    = new CMotionCeil10a();
        break;
    case PF_CEIL_10_B:
        mMotionBase    = new CMotionCeil10b();
        break;
    case PF_CEIL_08_A:
        mMotionBase    = new CMotionCeil8();
        break;
    case PF_UARM_10_A:
        mMotionBase    = new CMotionUarm10();
        break;
    case PF_UARM_08_A:
        mMotionBase    = new CMotionUarm8();
        break;
    case PF_RAIL_12_A:
        mMotionBase    = new CMotionRail12();
        break;
    case PF_RAIL_08_A:
        mMotionBase    = new CMotionRail8();
        break;
    default:
        mMotionBase    = new CMotionCeil10a();
        break;
    }

    return mMotionBase;
}
