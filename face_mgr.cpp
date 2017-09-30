#include "face_mgr.h"

#include "face_base8.h"
#include "face_base10.h"
#include "face_base12.h"
#include "system_defines.h"

CFaceMgr::CFaceMgr()
{
    mFaceBase = 0;
}

CFaceBase * CFaceMgr::faceInit(int mpf)
{

    switch(mpf)
    {
    case PF_NDT_8_A:
    case PF_RF_8_A:
        mFaceBase    = new CFaceBase8();
        break;
    case PF_NDT_10_A:
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
        mFaceBase    = new CFaceBase10();
        break;
    case PF_RAIL_12_A:
        mFaceBase    = new CFaceBase12();
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        mFaceBase    = new CFaceBase8();
        break;
    default:
        mFaceBase    = new CFaceBase10();
        break;
    }

    return mFaceBase;
}
