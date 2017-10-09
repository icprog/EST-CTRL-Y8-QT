#include "info_mgr.h"

#include "./base08/info_base8.h"
#include "./base10/info_base10.h"
#include "./base12/info_base12.h"
#include "./rf08/info_base_rf8a.h"
#include "./ndt08/info_base_ndt8.h"

CInfoMgr::CInfoMgr()
{
    mInfoBase = 0;
}

CInfoBase * CInfoMgr::infoInit(int mpf)
{
    switch(mpf)
    {
    case PF_NDT_8_A:
        mInfoBase    = new CInfoBaseNdt8();
        mInfoBase->m_iLimitMask = 0x0003;
        break;
    case PF_RF_8_A:
        mInfoBase    = new CInfoBaseRf8a();
        mInfoBase->m_iLimitMask = 0x00ff;
        break;
    case PF_CEIL_10_A:
        mInfoBase    = new CInfoBase10();   //初始化为10寸液晶屏的信息显示对象
        mInfoBase->m_iLimitMask = 0x0fff;   //根据系统电机数量，设置物理限位屏蔽位
        break;
    case PF_CEIL_10_B:
        mInfoBase    = new CInfoBase10();
        mInfoBase->m_iLimitMask = 0x0fff;
        break;
    case PF_CEIL_08_A:
        mInfoBase    = new CInfoBase8();    //初始化为8寸液晶屏的信息显示对象
        mInfoBase->m_iLimitMask = 0x03ff;   //初始化为8寸液晶屏的信息显示对象
        break;
    case PF_UARM_10_A:
        mInfoBase    = new CInfoBase10();
        mInfoBase->m_iLimitMask = 0x00ff;
        break;
    case PF_UARM_08_A:
        mInfoBase    = new CInfoBase8();
        mInfoBase->m_iLimitMask = 0x00ff;
        break;
    case PF_RAIL_12_A:
        mInfoBase    = new CInfoBase12();
        mInfoBase->m_iLimitMask = 0x00ff;
        break;
    case PF_RAIL_08_A:
        mInfoBase    = new CInfoBase8();
        mInfoBase->m_iLimitMask = 0x00ff;
        break;
    default:
        mInfoBase    = new CInfoBase10();
        break;
    }

    return mInfoBase;
}
