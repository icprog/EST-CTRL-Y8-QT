#include "net_mgr.h"

#include "./base08/net_server_base8.h"
#include "./base10/net_server_base10.h"
#include "./base12/net_server_base12.h"
#include "./base08/net_client_base8.h"
#include "./base10/net_client_base10.h"
#include "./base12/net_client_base12.h"
#include "./ndt10/net_server_ndt10.h"
#include "./ndt10/net_client_ndt10.h"
#include "./ndt08/net_server_ndt8.h"
#include "./ndt08/net_client_ndt8.h"
#include "resource_manager.h"

CNetMgr::CNetMgr()
{
}

void CNetMgr::netWorkInit(int mpf)
{

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        switch(mpf)
        {
        case PF_CEIL_10_A:
        case PF_CEIL_10_B:
        case PF_UARM_10_A:
            g_netBase    = new CNetClient10();
            break;
        case PF_RAIL_12_A:
            g_netBase    = new CNetClient12();
            break;
        case PF_CEIL_08_A:
        case PF_UARM_08_A:
        case PF_RAIL_08_A:
            g_netBase    = new CNetClient8();
            break;
        case PF_NDT_8_A:
        case PF_RF_8_A:
            g_netBase    = new CNetClientNdt8();
            break;
        case PF_NDT_10_A:
            g_netBase    = new CNetClientNdt10();
            break;
        default:
            g_netBase    = new CNetClient10();
            break;
        }
    }else
    {
        switch(mpf)
        {
        case PF_CEIL_10_A:
        case PF_CEIL_10_B:
        case PF_UARM_10_A:
            g_netBase    = new CNetServer10();
            break;
        case PF_RAIL_12_A:
            g_netBase    = new CNetServer12();
            break;
        case PF_CEIL_08_A:
        case PF_UARM_08_A:
        case PF_RAIL_08_A:
            g_netBase    = new CNetServerBase8();
            break;
        case PF_NDT_8_A:
        case PF_RF_8_A:
            g_netBase    = new CNetServerNdt8();
            break;
        case PF_NDT_10_A:
            g_netBase    = new CNetServerNdt10();
            break;
        default:
            g_netBase    = new CNetServer10();
            break;
        }
    }
}
