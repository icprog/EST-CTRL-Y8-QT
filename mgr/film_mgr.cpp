#include "film_mgr.h"

#include "./ceil10a/film_ceil10a.h"
#include "./ceil10b/film_ceil10b.h"
#include "./uarm10/film_uarm10.h"
#include "./rail12/film_rail12.h"
#include "./ceil08/film_ceil8.h"
#include "./uarm08/film_uarm8.h"
#include "./rail08/film_rail8.h"
#include "./ndt10/film_ndt10.h"

CFilmMgr::CFilmMgr()
{
    mKeyBase = 0;
}

CFilmBase * CFilmMgr::filmInit(int mpf)
{

    //判断平台，初始化不同的Key
    switch(mpf)
    {
    case PF_CEIL_10_A:
        mKeyBase    = new CFilmCeil10a();
        break;
    case PF_CEIL_10_B:
        mKeyBase    = new CFilmCeil10b();
        break;
    case PF_CEIL_08_A:
        mKeyBase    = new CFilmCeil8();
        break;
    case PF_UARM_10_A:
        mKeyBase    = new CFilmUarm10();
        break;
    case PF_UARM_08_A:
        mKeyBase    = new CFilmUarm8();
        break;
    case PF_RAIL_12_A:
        mKeyBase    = new CFilmRail12();
        break;
    case PF_RAIL_08_A:
        mKeyBase    = new CFilmRail8();
        break;
    case PF_NDT_8_A:
    case PF_RF_8_A:
    case PF_NDT_10_A:
        mKeyBase    = new CFilmNdt01();
        break;
    default:
        mKeyBase    = new CFilmCeil10a();
        break;
    }

    return mKeyBase;
}
