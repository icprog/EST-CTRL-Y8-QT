#ifndef SYS_DEF_H
#define SYS_DEF_H

//pi 定义
#define PI 3.1415926

//密码版本定义
#define PWD_VERSION_1       1
#define PWD_VERSION_2       2
#define PWD_VERSION_DEF   PWD_VERSION_2

//平台定义，悬吊，U臂，拍片床系统
//////////////////////////////////////////////////////////
//#define USE_CEIL_10_A 1
//#define USE_CEIL_08_A 1
//#define USE_UARM_10_A 1
//#define USE_UARM_08_A 1
//#define USE_RAIL_12_A 1
#define USE_RAIL_08_A   1
#define USE_RAIL_08_B   1
//#define USE_CEIL_10_B 1
//#define USE_NDT_10_A  1
//#define USE_NDT_8_A   1
//#define USE_RF_8_A    1

#define PLATFORM_MAX    ( 10 )       /*平台数量*/
#define PF_CEIL_10_A    ( 0 )       /*平台,悬吊，10寸屏，升降床，西门子胸片架*/
#define PF_CEIL_08_A    ( 1 )       /*平台,悬吊，8寸屏，移动床，杰瑞胸片架*/
#define PF_UARM_10_A    ( 2 )       /*平台,U臂，10寸屏，移动床*/
#define PF_UARM_08_A    ( 3 )       /*平台,U臂，8寸屏，移动床*/
#define PF_RAIL_12_A    ( 4 )      /*平台,拍片床，10寸屏，升降床，自主胸片架*/
#define PF_RAIL_08_A    ( 5 )      /*平台,拍片床，8寸屏，升降床，自主胸片架*/
#define PF_RAIL_08_B    ( 6 )      /*平台,拍片床，8寸屏，升降床，自主胸片架*/
#define PF_CEIL_10_B    ( 7 )      /*平台,悬吊，10寸屏，移动床，杰瑞胸片架*/
#define PF_NDT_10_A     ( 8 )     /*平台,悬吊，10寸屏，Nondestructive testing*/
#define PF_NDT_8_A      ( 9 )     /*平台,定制，8寸屏，Nondestructive testing*/
#define PF_RF_8_A       ( 10 )     /*平台,胃肠床，8寸屏，Nondestructive testing*/

//语言定义，目前只支持英语，中文
//////////////////////////////////////////////////////////
#define LANGUAGE_MAX            ( 4 )
#define _ENGLISH                ( 0 )
#define _CHINESE                ( 1 )
#define _RUSSIAN                ( 2 )
#define _KOREA                  ( 3 )
#define _SPANISH                ( 4 )
#define _TURKISH                ( 5 )

//屏幕分辨率设置
#define SYS_SCREEN_WID          ( 800 )
#define SYS_SCREEN_HEI          ( 600 )
//#define SYS_SCREEN_WID          ( 1024 )
//#define SYS_SCREEN_HEI          ( 768 )

#define SYS_WID(a)      (qRound((float)(a * g_sysWidth)  / SYS_SCREEN_WID))
#define SYS_HEI(b)      (qRound((float)(b * g_sysHeight) / SYS_SCREEN_HEI))
#define SYS_FONT(c)     (qRound((float)(c * g_sysHeight) / SYS_SCREEN_HEI))
#define SYS_WIDf(a)     ((a * g_sysWidth)  / SYS_SCREEN_WID)
#define SYS_HEIf(b)     ((b * g_sysHeight) / SYS_SCREEN_HEI)

//旋转视角定义
//////////////////////////////////////////////////////////
#define VIEW_DIR_MAX          ( 4 )     /*最大视角个数*/
#define VIEW_DIR_NORMAL       ( 0 )     /*正常显示*/
#define VIEW_DIR_LEFT         ( 1 )     /*左转显示*/
#define VIEW_DIR_RIGHT        ( 2 )     /*右转显示*/
#define VIEW_DIR_R180         ( 3 )     /*旋转180度显示*/

//系统布局定义
///////////////////////////////////////////////////////////
#define POPUP_CFG_MAX       ( 3 )
#define SYS_POPUP_PARAM_CFG ( 0 )
#define SYS_POPUP_AEC_CFG   ( 1 )
#define SYS_POPUP_FOCUS_CFG ( 2 )

#define SYS_POPUP_FOCUS     ( 0 )
#define SYS_POPUP_AEC       ( 1 )
#define SYS_POPUP_SMART     ( 2 )
#define SYS_POPUP_REQUEST   ( 3 )
#define SYS_POPUP_GEN       ( 4 )
#define SYS_POPUP_MOTION    ( 5 )
#define SYS_POPUP_INFO      ( 6 )
#define SYS_POPUP_PARAM     ( 7 )
#define SYS_POPUP_MENU      ( 8 )
#define SYS_POPUP_STATUS    ( 9 )
#define SYS_POPUP_TITLE     ( 10 )
#define SYS_POPUP_TECH      ( 11 )
#define SYS_POPUP_FAST      ( 12 )
#define SYS_POPUP_POWER     ( 13 )
#define SYS_POPUP_SIM       ( 14 )
#define SYS_POPUP_NET       ( 15 )
#define SYS_POPUP_KEY       ( 16 )
#define SYS_POPUP_QUICK     ( 17 )
#define SYS_POPUP_CURTAIN   ( 18 )
#define SYS_POPUP_NOTIFY    ( 19 )
#define SYS_POPUP_SIM_HIDE  ( 20 )
#define SYS_POPUP_SMART_HIDE ( 21 )
#define SYS_POPUP_MAX       ( 22 )
#define SYS_POPUP_KV        ( 21 )
#define SYS_POPUP_MAS       ( 22 )
#define SYS_POPUP_MA        ( 23 )
#define SYS_POPUP_MS        ( 24 )

#endif // SYS_DEF_H
