#include "main_mgr.h"

#include "./ceil10a/main_ceil10a.h"
#include "./ceil10b/main_ceil10b.h"
#include "./ceil08/main_ceil8.h"
#include "./uarm10/main_uarm10.h"
#include "./uarm08/main_uarm8.h"
#include "./rail12/main_rail12.h"
#include "./rail08/main_rail8.h"

//add ndt to this control class
#include "./ndt10/main_base_ndt10.h"
#include "./ndt08/main_base_ndt8.h"
#include "./rf08/main_base_rf8a.h"

CMainMgr::CMainMgr()
{
    mMainBase = 0;
}

CMainBase * CMainMgr::mainInit(int mpf)
{
    switch(mpf)
    {
    case PF_CEIL_10_A:
        mMainBase    = new CMainCeil10a();  //10寸，悬吊，升降床
        break;
    case PF_CEIL_10_B:
        mMainBase    = new CMainCeil10b();  //10寸，悬吊，移动床
        break;
    case PF_CEIL_08_A:
        mMainBase    = new CMainCeil8();    //8寸，悬吊，移动床
        break;
    case PF_UARM_10_A:
        mMainBase    = new CMainUarm10();   //10寸，U臂，移动床
        break;
    case PF_UARM_08_A:
        mMainBase    = new CMainUarm8();    //8寸，U臂，移动床
        break;
    case PF_RAIL_12_A:
        mMainBase    = new CMainRail12();   //10寸，拍片床，升降床
        break;
    case PF_RAIL_08_A:
        mMainBase    = new CMainRail8();    //10寸，拍片床，升降床
        break;
    case PF_NDT_8_A:
        mMainBase    = new CMainBaseNdt8();    //8寸，胃肠床，工业探伤版本2
        break;
    case PF_RF_8_A:
        mMainBase    = new CMainBaseRf8a();    //8寸，胃肠床，工业探伤版本2
        break;
    case PF_NDT_10_A:
        mMainBase    = new CMainBaseNdt10();    //10寸，工业探伤版本1
        break;
    default:
        mMainBase    = new CMainCeil10a();
        break;
    }
    return mMainBase;
}
