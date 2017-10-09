#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include "skin_mgr.h"
#include "resource_manager.h"

#include "./ceil10a/skin_ceil10a.h"
#include "./ceil10b/skin_ceil10b.h"
#include "./rail12/skin_rail12.h"
#include "./uarm10/skin_uarm10.h"
#include "./ceil08/skin_ceil8.h"
#include "./rail08/skin_rail8.h"
#include "./uarm08/skin_uarm8.h"
#include "./ndt08/skin_ndt8.h"
#include "./ndt10/skin_ndt10.h"

CSkinManager::CSkinManager()
{
    m_skinBase = NULL;
}
CSkinBase * CSkinManager::skinInit(unsigned short mPf,unsigned short mSkin)
{
    //屏蔽超过限值的皮肤设定
    if(mSkin >= SYSTEM_SKIN_MAX )
        mSkin = 0;

    //根据不同参数初始化对象
    switch(mPf)
    {
    case PF_NDT_8_A:
        m_skinBase = new CSkinNdt8();
        break;
    case PF_RF_8_A:
        m_skinBase = new CSkinCeil10a();
        break;
    case PF_NDT_10_A:
        m_skinBase = new CSkinNdt10();
        break;
    case PF_CEIL_10_A:
        m_skinBase = new CSkinCeil10a();
        break;
    case PF_CEIL_10_B:
        m_skinBase = new CSkinCeil10b();
        break;
    case PF_CEIL_08_A:
        m_skinBase = new CSkinCeil8();
        break;
    case PF_UARM_10_A:
        m_skinBase = new CSkinUarm10();
        break;
    case PF_UARM_08_A:
        m_skinBase = new CSkinUarm8();
        break;
    case PF_RAIL_12_A:
        m_skinBase = new CSkinRail12();
        break;
    case PF_RAIL_08_A:
        m_skinBase = new CSkinRail8();
        break;
    default:
        m_skinBase = new CSkinCeil10a();
        break;
    }

    //判断是否切换资源路径
    if( !QFile::exists("/sdcard/home/fa/outresource"))
        return m_skinBase;

    //从配置文件读取需要切换到的资源路径
    if(g_mainCfg)
        m_skinBase->ConfigResource(g_mainCfg->value("outresource","/sdcard/home/fa/").toByteArray().data());

    return m_skinBase;
}
