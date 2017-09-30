#include "menu_mgr.h"

#include "menu_ceil10a.h"
#include "menu_ceil10b.h"
#include "menu_ceil8.h"
#include "menu_uarm10.h"
#include "menu_uarm8.h"
#include "menu_rail12.h"
#include "menu_rail8.h"

CMenuMgr::CMenuMgr()
{
    mMenuBase = 0;
}


CMenuBase * CMenuMgr::menuInit(int mpf)
{
    switch(mpf)
    {
    case PF_CEIL_10_A:
        mMenuBase    = new CMenuCeil10a();
        break;
    case PF_CEIL_10_B:
        mMenuBase    = new CMenuCeil10b();
        break;
    case PF_CEIL_08_A:
        mMenuBase    = new CMenuCeil8();
        break;
    case PF_UARM_10_A:
        mMenuBase    = new CMenuUarm10();
        break;
    case PF_UARM_08_A:
        mMenuBase    = new CMenuUarm8();
        break;
    case PF_RAIL_12_A:
        mMenuBase    = new CMenuRail12();
        break;
    case PF_RAIL_08_A:
        mMenuBase    = new CMenuRail8();
        break;
    default:
        mMenuBase    = new CMenuCeil10a();
        break;
    }
    return mMenuBase;
}
