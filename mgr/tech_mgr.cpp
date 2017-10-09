#include "tech_mgr.h"

#include "./base08/tech_base8.h"
#include "./base10/tech_base10.h"
#include "./base12/tech_base12.h"

CTechMgr::CTechMgr()
{
    mTechBase = 0;
}


CTechBase * CTechMgr::techInit(int mpf)
{

    switch(mpf)
    {
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
        mTechBase    = new CTechBase10();
        break;
    case PF_RAIL_12_A:
        mTechBase    = new CTechBase12();
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        mTechBase    = new CTechBase8();
        break;
    default:
        mTechBase    = new CTechBase10();
        break;
    }

    return mTechBase;
}
