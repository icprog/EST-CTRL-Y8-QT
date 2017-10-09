#ifndef SYSTEM_DEFINES_H
#define SYSTEM_DEFINES_H


#include "./uarm08/system_defines_uarm8.h"
#include "./uarm10/system_defines_uarm10.h"
#include "./rail08/system_defines_rail8.h"
#include "./rail12/system_defines_rail12.h"
#include "./ceil08/system_defines_ceil8.h"
#include "./ceil10a/system_defines_ceil10a.h"
#include "./ceil10b/system_defines_ceil10b.h"
#include "./rf08/system_defines_rf8a.h"
#include "./ndt08/system_defines_ndt8a.h"

#define  FILM_LED_STAND                0x801
#define  FILM_LED_TABLE                 0x802
#define  FILM_LED_TUBE                  0x803
#define  FILM_LED_ALL_FLASH         0x901
#define  FILM_LED_ALL_ON              0x902
#define  FILM_LED_ALL_OFF              0x903


#define NDT_STAT_STS        11

#define NDT_FID_STOP_MASK       0x0001
#define NDT_SID_STOP_MASK      0x0002
#define NDT_ANG_STOP_MASK      0x0004
#define NDT_CEP_STOP_MASK      0x0008
#define NDT_UID_STOP_MASK      0x0010
#define NDT_DTA_STOP_MASK      0x0020
#define NDT_ROL_STOP_MASK     0x0040
#define NDT_SRL_STOP_MASK      0x0080
#define NDT_RMV_STOP_MASK     0x0100
#define NDT_LMV_STOP_MASK      0x0200
#define NDT_HEI_STOP_MASK       0x0400
#define NDT_STAND_STOP_MASK  (NDT_UID_STOP_MASK |  NDT_DTA_STOP_MASK | NDT_HEI_STOP_MASK)
#define NDT_TUBE_STOP_MASK      (NDT_FID_STOP_MASK | NDT_SID_STOP_MASK | NDT_ANG_STOP_MASK | NDT_CEP_STOP_MASK)
#define NDT_MOTOR_STOP       9001
#define NDT_MOTOR_IGNORE  9000

#define PI 3.1415926

#define PWD_VERSION_1       1
#define PWD_VERSION_2       2
#define PWD_VERSION_DEF   PWD_VERSION_2

//ndt key index
#define NDT_KEY_IDX_FID     0
#define NDT_KEY_IDX_SID     1
#define NDT_KEY_IDX_ANG   2
#define NDT_KEY_IDX_CEP    3
#define NDT_KEY_IDX_UID    4
#define NDT_KEY_IDX_DTA    5
#define NDT_KEY_IDX_ROL    6
#define NDT_KEY_IDX_SRL     7
#define NDT_KEY_IDX_RMV    8
#define NDT_KEY_IDX_LMV    9
#define NDT_KEY_IDX_HEI     10
#define NDT_KEY_IDX_OUT    11
#define NDT_KEY_IDX_IN       12
#define NDT_KEY_IDX_MIN      NDT_KEY_IDX_FID
#define NDT_KEY_IDX_MAX      NDT_KEY_IDX_OUT
#define NDT_KEY_BUF_SIZE    12                /*for send message only*/



#define MACHINE_CODE_LEN    8

#define AUTO_RUN_MODE_FAST      (0)     /*自动运行-快捷位*/
#define AUTO_RUN_MODE_SOFT      (1)     /*自动运行-软件限位*/
#define AUTO_RUN_MODE_SWITCH    (2)     /*自动运行-硬件限位*/
#define AUTO_RUN_MODE_HARD      (3)     /*自动运行-机械限位*/

#define OS_LINUX_ARM             (0)
#define OS_LINUX_ANDROID    (1)

#define TITLE8_LABEL_MAX     ( 6 )
#define EMG_STOP_V1         (0X0099)    /*非工作区域按下后的急停键码*/

//信息提示定义
//////////////////////////////////////////////////////////
#define MSG_UNKNWON             ( 2 )
#define MSG_EMERGESTOP          ( 3 )
#define MSG_SAFEDISTANCE        ( 4 )
#define MSG_LIMITIBIT           ( 5 )
#define MSG_TIMEOVER            ( 6 )
#define MSG_COM_LOST            ( 7 )
#define MSG_NET_START_FAIL      ( 8 )
#define MSG_MODE_DEMO           ( 9 )
#define MSG_FIRMWARE_LOST       ( 10 )
#define MSG_SELF_RUN            ( 11 )
#define MSG_TEMPERATURE         ( 12 )
#define MSG_DATE                ( 13 )
#define MSG_TIME                ( 14 )
#define MSG_NORMAL              ( 15 )
#define MSG_FAST_NOT_SET        ( 16 )
#define MSG_TEST_FINISHED       ( 17 )
#define MSG_FAST_SET_ERR        ( 18 )
#define MSG_FAST_EXE_ERR        ( 19 )
#define MSG_NET_SIGNAL_WARN     ( 20 )
#define MSG_NET_REMOTE_LOST     ( 21 )
#define MSG_NET_RESTART         ( 22 )
#define MSG_FAST_SLASH_ERR      ( 23 )
#define MSG_INIT_FILM_PRESS     ( 24 )
#define MSG_RUN_POSITION_ERR    ( 25 )
#define MSG_MOTOR_CALI_ERR      ( 26 )
#define MSG_CAN_LOST_1          ( 27 )
#define MSG_CAN_LOST_2          ( 28 )
#define MSG_TIME_NEED_SET     ( 29 )

//杂项
//////////////////////////////////////////////////////////
#define SAFE_DISTANCE_MASK      0x0001  /*小于安全距离标志位*/
#define CAN1_LOST_MASK          0x0002  /*CAN通信失败标志位*/
#define CAN2_LOST_MASK          0x0004  /*CAN通信失败标志位*/

#define SYS_START_FINISH        ( 100 )
#define VISIBLE_WIDGET_MAX      ( 100 )

#define NET_LAN     (0)
#define NET_WIFI    (1)
#define NET_CMD_KEY_PRESS        (0x5A5A)
#define NET_CMD_KEY_RELEASE    (0xA5A5)
#define NET_CMD_KEY_PAGE        (0x5A00)

#define FUNC_SIMULATE_OFF      ( 0 )
#define FUNC_SIMULATE_ON       ( 1 )

#define SYS_SMART_MAX           ( 9 )
#define SYS_MOTION_MAX          ( 10 )  /*系统支持的最大电机数量*/

#define SYS_KEY_MAX             ( 24 )
#define SOFT_KEY_MAX            ( 16 )

#define SYS_SCREEN_WID          ( 800 )
#define SYS_SCREEN_HEI          ( 600 )
//#define SYS_SCREEN_WID          ( 1024 )
//#define SYS_SCREEN_HEI          ( 768 )

#define SYS_WID(a)      (qRound((float)(a * g_sysWidth)  / SYS_SCREEN_WID))
#define SYS_HEI(b)      (qRound((float)(b * g_sysHeight) / SYS_SCREEN_HEI))
#define SYS_FONT(c)     (qRound((float)(c * g_sysHeight) / SYS_SCREEN_HEI))
#define SYS_WIDf(a)     ((a * g_sysWidth)  / SYS_SCREEN_WID)
#define SYS_HEIf(b)     ((b * g_sysHeight) / SYS_SCREEN_HEI)

//薄膜按键功能定义
#define FILM_FUNC_NORMAL    (0)/*正常*/
#define FILM_FUNC_STOP_SCAN (1)/*停止扫描*/
#define FILM_FUNC_STOP_RUN  (2)/*停止执行*/

//按键长按时间定义，单位ms
//////////////////////////////////////////////////////////
#define TIME_DATA_FRESH         ( 200 )     /*MainSetting*/
#define TIME_SCREEN_FRESH       ( 200 )     /*电机调试、位置设置、密码界面、速度设定*/
#define TIME_INFO_FRESH         ( 1500 )
#define TIME_LONG_PRESS         ( 1000 )
#define TIME_MOTION_FRESH       ( 100 )
#define TIME_SIM_FRESH          ( 100 )
#define TIME_GEN_FRESH          ( 300 )

//网络相关定义
//////////////////////////////////////////////////////////
#define TARGET_TCP_SERVER       ( 0 )
#define TARGET_TCP_CLIENT       ( 1 )
#define TARGET_UDP_SERVER       ( 2 )
#define TARGET_UDP_CLIENT       ( 4 )

#define CLIENT_ACK_REJECT       ( 1 )
#define CLIENT_ACK_TIMEOUT      ( 2 )
#define CLIENT_ACK_ACCEPT       ( 3 )


#define COMM_PROTOCOL_00        (0)     /*旧的，只有2个一键位置的通信协议*/
#define COMM_PROTOCOL_01        (1)     /*新的，支持8个一键位置的通信协议*/

//信息提示图标定义
//////////////////////////////////////////////////////////
#define INFO_PIC_MAX            ( 5 )   /*系统支持的信息提示等级，优先显示高优先级的提示信息，数字0代表最高优先级*/
#define INFO_PIC_CRITICAL       ( 0 )
#define INFO_PIC_ERROR          ( 1 )
#define INFO_PIC_WARNING        ( 2 )
#define INFO_PIC_QUESTION       ( 3 )
#define INFO_PIC_INFO           ( 4 )

//信息提示
//////////////////////////////////////////////////////////
#define INFO_SCROLL_MAX         ( 10 )   /*同一等级错误，支持5个交替显示*/
#define INFO_CTRL_ADD           ( 0 )
#define INFO_CTRL_DEL           ( 1 )
#define INFO_CTRL_CLR           ( 2 )
#define INFO_CTRL_FRE           ( 3 )

//按键的状态
//////////////////////////////////////////////////////////
#define KEY_STATUS_DOWN         ( 1 )
#define KEY_STATUS_UP           ( 0 )

//语言定义，目前只支持英语，中文
//////////////////////////////////////////////////////////
#define LANGUAGE_MAX            ( 4 )
#define _ENGLISH                ( 0 )
#define _CHINESE                ( 1 )
#define _RUSSIAN                ( 2 )
#define _KOREA                  ( 3 )
#define _SPANISH                ( 4 )
#define _TURKISH                ( 5 )

//平台定义，悬吊，U臂，拍片床系统
//////////////////////////////////////////////////////////


#define PLATFORM_MAX    ( 10 )       /*平台数量*/
#define PF_CEIL_10_A    ( 0 )       /*平台,悬吊，10寸屏，升降床，西门子胸片架*/
#define PF_CEIL_08_A    ( 1 )       /*平台,悬吊，8寸屏，移动床，杰瑞胸片架*/
#define PF_UARM_10_A    ( 2 )       /*平台,U臂，10寸屏，移动床*/
#define PF_UARM_08_A    ( 3 )       /*平台,U臂，8寸屏，移动床*/
#define PF_RAIL_12_A    ( 4 )      /*平台,拍片床，10寸屏，升降床，自主胸片架*/
#define PF_RAIL_08_A    ( 5 )      /*平台,拍片床，8寸屏，升降床，自主胸片架*/
#define PF_CEIL_10_B    ( 6 )      /*平台,悬吊，10寸屏，移动床，杰瑞胸片架*/
#define PF_NDT_10_A     ( 7 )     /*平台,悬吊，10寸屏，Nondestructive testing*/
#define PF_NDT_8_A      ( 8 )     /*平台,定制，8寸屏，Nondestructive testing*/
#define PF_RF_8_A       ( 9 )     /*平台,胃肠床，8寸屏，Nondestructive testing*/

//////////////////////////////////////////////////////////
#define DETECTOR_STAND_LEFT     ( 0 )
#define DETECTOR_STAND_RIGHT    ( 1 )

//////////////////////////////////////////////////////////
#define VIEW_GEN_CFG            ( 0 )
#define VIEW_PASSWORD         ( 1 )
#define VIEW_GEN                     ( 2 )
#define VIEW_MOTION              ( 3 )
#define VIEW_MAIN                   ( 4 )
#define VIEW_CONFIRM            ( 5 )
#define VIEW_INSTALL               ( 6 )
#define VIEW_CONSOLE            ( 7 )
//////////////////////////////////////////////////////////
#define VIEW_DIR_MAX          ( 4 )     /*最大视角个数*/
#define VIEW_DIR_NORMAL       ( 0 )     /*正常显示*/
#define VIEW_DIR_LEFT         ( 1 )     /*左转显示*/
#define VIEW_DIR_RIGHT        ( 2 )     /*右转显示*/
#define VIEW_DIR_R180         ( 3 )     /*旋转180度显示*/

//////////////////////////////////////////////////////////
#define SYS_TECH_MIN        ( 0 )
#define SYS_TECH_MAX        ( 3 )
#define SYS_TECH_MAMS       ( 0 )
#define SYS_TECH_MAS        ( 1 )
#define SYS_TECH_AEC        ( 2 )

//////////////////////////////////////////////////////////
#define PARAM_TYPE_MAX      ( 4 )
#define TYPE_MS             ( 0 )
#define TYPE_KV             ( 1 )
#define TYPE_MA             ( 2 )
#define TYPE_MAS            ( 3 )

#define SYS_FOCUS_SMALL     ( 1 )
#define SYS_FOCUS_LARGE     ( 2 )

#define GEN_MS_PAGE         ( 5 )
#define GEN_MAS_PAGE        ( 4 )
#define GEN_MA_PAGE         ( 3 )
#define GEN_KV_PAGE         ( 7 )

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
#define SYS_POPUP_SIM_HIDE  ( 16 )
#define SYS_POPUP_KEY       ( 17 )
#define SYS_POPUP_SMART_HIDE ( 18 )
#define SYS_POPUP_QUICK     ( 19 )
#define SYS_POPUP_CURTAIN   ( 20 )
#define SYS_POPUP_NOTIFY    ( 21 )
#define SYS_POPUP_MAX       ( 22 )
#define SYS_POPUP_KV        ( 21 )
#define SYS_POPUP_MAS       ( 22 )
#define SYS_POPUP_MA        ( 23 )
#define SYS_POPUP_MS        ( 24 )


///////////////////////////////////////////////////////////
#define TCP_SERVER_PORT      12801
#define UDP_CLIENT_PORT      45454
#define UDP_GEN_CLIENT_PORT  45450
#define PKG_DEFAULT_SIZE     32
#define MAX_CLIENT_NUM       8

#define CLIENT_FUNC_NULL     0
#define CLIENT_FUNC_READ     1
#define CLIENT_FUNC_RUN      2
#define CLIENT_FUNC_SET      3
#define CLIENT_FUNC_MAX      4

#define TCP_STATE_EMPTY      0
#define TCP_STATE_USING      1

#define NET_RE_CONNECT_TIME  500
#define CONNECT_WAIT_TIME    200

#define FUNC_WKEY_ADDR       1
#define CMD_FUNC_ADDR        0

#define CMD_FUNC_WKEY        0x1001
#define CMD_FUNC_POSI        0x1002
#define CMD_FUNC_SPEED       0x1003
#define CMD_FUNC_COMMD       0x1004
#define CMD_FUNC_PARAM       0x1005
#define CMD_FUNC_MOTO        0x1006
#define CMD_FUNC_DEBUG       0x1007
#define CMD_FUNC_STATE       0x1008
#define CMD_FUNC_VER       0x1009
#define CMD_FUNC_LIGHT_CURTAIN       0x1010
#define CMD_FUNC_SMART       0x1011
#define CMD_FUNC_REBOOT      0x10AA

#define CMD_NDT_RUN         0x3011
#define CMD_NDT_STATE       0x3012
#define CMD_KEEP_ALIVE_HEADER   0x3013
#define CMD_KEEP_ALIVE_DATA     0x00cc

#define MSG_CLIENT_IDX       0x2000
#define MSG_CTRL_REQUEST     0x2020
#define MSG_CTRL_BUSY        0x2030
#define MSG_CTRL_LIMIT       0x2040
#define MSG_CTRL_COLLISION   0x2050
#define MSG_CTRL_REJECT      0x2060
#define MSG_CTRL_HEARTBEAT   0x2070

///////////////////////////////////////////////////////////
#define SMART_POS_00            ( 0 )
#define SMART_POS_01            ( 1 )
#define SMART_POS_02            ( 2 )
#define SMART_POS_03            ( 3 )
#define SMART_POS_04            ( 4 )
#define SMART_POS_05            ( 5 )
#define SMART_POS_06            ( 6 )
#define SMART_POS_07            ( 7 )
#define SMART_POS_08            ( 8 )

///////////////////////////////////////////////////////////
#define MENU10_KEY_MAX              ( 8 )
#define MENU10_BTN_LEFT1            ( 0 )
#define MENU10_BTN_LEFT2            ( 1 )
#define MENU10_BTN_LEFT3            ( 2 )
#define MENU10_BTN_LEFT4            ( 3 )
#define MENU10_BTN_RIGHT1           ( 4 )
#define MENU10_BTN_RIGHT2           ( 5 )
#define MENU10_BTN_RIGHT3           ( 6 )
#define MENU10_BTN_RIGHT4           ( 7 )
#define MENU10_BTN_VIEW_MAX         ( 4 )
#define MENU10_BTN_VIEW_0           ( 0 )
#define MENU10_BTN_VIEW_1           ( 1 )
#define MENU10_BTN_VIEW_2           ( 2 )
#define MENU10_BTN_VIEW_3           ( 3 )

///////////////////////////////////////////////////////////
//运动模拟使用
#define MOTOR_POS_MIN       ( 0 )
#define MOTOR_POS_MAX       ( 1 )
#define MOTOR_POS_STEP      ( 2 )
#define MOTOR_POS_DIR       ( 3 )
#define MOTOR_POS_FLG       ( 4 )
#define MOTOR_POS_DAT       ( 5 )
#define MOTOR_POS_TAR       ( 6 )

#define SIM_FRAME_RATE      ( 5 )
#define SIM_MOTION_PERIOD   ( 8 )

extern long G_PasswordPeriods[];
#define PASSWORD_MAX_LENGTH       (10)

////////////////////////////////////////////////////////////////
#define SYSTEM_SKIN_MAX            ( 3 )
#define SYSTEM_MOTOR_MAX            ( 10 )

////////////////////////////////////////////////////////////////
//system image strings defines
#define TABLE_STR_MAX           ( 300 )
#define SYS_STR_BASE            ( 0 )

//////////
#define SYS_STR_CRITICAL    ( SYS_STR_BASE + 0 )
#define SYS_STR_ERROR       ( SYS_STR_BASE + 1 )
#define SYS_STR_WARNING     ( SYS_STR_BASE + 2 )
#define SYS_STR_QUESTION    ( SYS_STR_BASE + 3 )
#define SYS_STR_INFO        ( SYS_STR_BASE + 4 )
//////////13

#define SYS_BTN_BASE        ( SYS_STR_BASE + 15 )


#define SYS_GEN_BASE        ( SYS_BTN_BASE + 5 )
//////////20

#define SYS_INDEX_BASE      ( SYS_GEN_BASE + 5 )
//////////30

#define SYS_FOCUS_BASE          ( SYS_INDEX_BASE + 10 )
#define SYS_FSMALL_01           ( SYS_FOCUS_BASE + 0)
#define SYS_FSMALL_02           ( SYS_FOCUS_BASE + 1)
#define SYS_FLARGE_01           ( SYS_FOCUS_BASE + 2)
#define SYS_FLARGE_02           ( SYS_FOCUS_BASE + 3)
#define SYS_SCREEN_LEFT_01      ( SYS_FOCUS_BASE + 4)
#define SYS_SCREEN_LEFT_02      ( SYS_FOCUS_BASE + 5)
#define SYS_SCREEN_RIGHT_01     ( SYS_FOCUS_BASE + 6)
#define SYS_SCREEN_RIGHT_02     ( SYS_FOCUS_BASE + 7)
//////////40

#define SYS_AEC_BASE            ( SYS_FOCUS_BASE + 10 )
#define SYS_AEC_00              ( SYS_AEC_BASE + 0 )
#define SYS_AEC_01              ( SYS_AEC_BASE + 1 )
#define SYS_AEC_10              ( SYS_AEC_BASE + 2 )
#define SYS_AEC_11              ( SYS_AEC_BASE + 3 )
#define SYS_AEC_20              ( SYS_AEC_BASE + 4 )
#define SYS_AEC_21              ( SYS_AEC_BASE + 5 )
#define SYS_AEC_30              ( SYS_AEC_BASE + 6 )
#define SYS_AEC_31              ( SYS_AEC_BASE + 7 )
#define SYS_AEC_40              ( SYS_AEC_BASE + 8 )
#define SYS_AEC_41              ( SYS_AEC_BASE + 9 )
#define SYS_AEC_50              ( SYS_AEC_BASE + 10 )
#define SYS_AEC_51              ( SYS_AEC_BASE + 11 )
#define SYS_AEC_60              ( SYS_AEC_BASE + 12 )
#define SYS_AEC_61              ( SYS_AEC_BASE + 13 )

//////////60
#define SYS_SMART_BASE        ( SYS_AEC_BASE + 15 )
#define SYS_STR_SMART_00      ( SYS_SMART_BASE + 0 )
#define SYS_STR_SMART_01      ( SYS_SMART_BASE + 1 )
#define SYS_STR_SMART_02      ( SYS_SMART_BASE + 2 )
#define SYS_STR_SMART_03      ( SYS_SMART_BASE + 3 )
#define SYS_STR_SMART_04      ( SYS_SMART_BASE + 4 )
#define SYS_STR_SMART_05      ( SYS_SMART_BASE + 5 )
#define SYS_STR_SMART_06      ( SYS_SMART_BASE + 6 )
#define SYS_STR_SMART_07      ( SYS_SMART_BASE + 7 )
#define SYS_STR_SMART_08      ( SYS_SMART_BASE + 8 )
#define SYS_SMART_BASE1       ( SYS_SMART_BASE + 9 )
#define SYS_STR_SMART_10      ( SYS_SMART_BASE + 9 )
#define SYS_STR_SMART_11      ( SYS_SMART_BASE + 10 )
#define SYS_STR_SMART_12      ( SYS_SMART_BASE + 11 )
#define SYS_STR_SMART_13      ( SYS_SMART_BASE + 12 )
#define SYS_STR_SMART_14      ( SYS_SMART_BASE + 13 )
#define SYS_STR_SMART_15      ( SYS_SMART_BASE + 14 )
#define SYS_STR_SMART_16      ( SYS_SMART_BASE + 15 )
#define SYS_STR_SMART_17      ( SYS_SMART_BASE + 16 )
#define SYS_STR_SMART_18      ( SYS_SMART_BASE + 17 )
#define SYS_SMART_BASE2       ( SYS_SMART_BASE + 18 )
#define SYS_STR_SMART_20      ( SYS_SMART_BASE + 18 )
#define SYS_STR_SMART_21      ( SYS_SMART_BASE + 19 )
#define SYS_STR_SMART_22      ( SYS_SMART_BASE + 20 )
#define SYS_STR_SMART_23      ( SYS_SMART_BASE + 21 )
#define SYS_STR_SMART_24      ( SYS_SMART_BASE + 22 )
#define SYS_STR_SMART_25      ( SYS_SMART_BASE + 23 )
#define SYS_STR_SMART_26      ( SYS_SMART_BASE + 24 )
#define SYS_STR_SMART_27      ( SYS_SMART_BASE + 25 )
#define SYS_STR_SMART_28      ( SYS_SMART_BASE + 26 )

//////////80
#define SYS_MEASURE_BASE        ( SYS_SMART_BASE + 30 )
#define SYS_MEASURE_FID         ( SYS_MEASURE_BASE + 0 )
#define SYS_MEASURE_SID         ( SYS_MEASURE_BASE + 1 )
#define SYS_MEASURE_ANG         ( SYS_MEASURE_BASE + 2 )
#define SYS_MEASURE_DTH         ( SYS_MEASURE_BASE + 3)
#define SYS_MEASURE_DTA         ( SYS_MEASURE_BASE + 4 )
#define SYS_MEASURE_BEH         ( SYS_MEASURE_BASE + 5 )
#define SYS_MEASURE_HEI         ( SYS_MEASURE_BASE + 6 )
#define SYS_MEASURE_DTP         ( SYS_MEASURE_BASE + 7 )
#define SYS_MEASURE_CEP         ( SYS_MEASURE_BASE + 8 )
#define SYS_MOTOR_MAX           ( 9 )
#define SYS_TECH_UP             ( SYS_MEASURE_BASE + 9 )
#define SYS_TECH_DOWN           ( SYS_MEASURE_BASE + 10 )
#define SYS_SIM_ON              ( SYS_MEASURE_BASE + 11 )
#define SYS_SIM_OFF             ( SYS_MEASURE_BASE + 12 )
#define SYS_LEFT_GEN_UP         ( SYS_MEASURE_BASE + 13 )
#define SYS_LEFT_GEN_DOWN       ( SYS_MEASURE_BASE + 14 )
#define SYS_LEFT_CFG_UP         ( SYS_MEASURE_BASE + 15 )
#define SYS_LEFT_CFG_DOWN       ( SYS_MEASURE_BASE + 16 )
#define SYS_RIGHT_GEN_UP        ( SYS_MEASURE_BASE + 17 )
#define SYS_RIGHT_GEN_DOWN      ( SYS_MEASURE_BASE + 18 )
#define SYS_RIGHT_CFG_UP        ( SYS_MEASURE_BASE + 19 )
#define SYS_RIGHT_CFG_DOWN      ( SYS_MEASURE_BASE + 20 )
#define SYS_CLIENT8_BACK        ( SYS_MEASURE_BASE + 21 )

#define SYS_KEY_ICON_BASE       ( SYS_MEASURE_BASE + 22 )
#define SYS_TURN_LEFT_0         (SYS_KEY_ICON_BASE + 0)
#define SYS_TURN_LEFT_1         (SYS_KEY_ICON_BASE + 1)
#define SYS_TURN_LEFT_2         (SYS_KEY_ICON_BASE + 2)
#define SYS_TURN_RIGHT_0        (SYS_KEY_ICON_BASE + 3)
#define SYS_TURN_RIGHT_1        (SYS_KEY_ICON_BASE + 4)
#define SYS_TURN_RIGHT_2        (SYS_KEY_ICON_BASE + 5)
#define SYS_RUN_LEFT_0          (SYS_KEY_ICON_BASE + 6)
#define SYS_RUN_LEFT_1          (SYS_KEY_ICON_BASE + 7)
#define SYS_RUN_LEFT_2          (SYS_KEY_ICON_BASE + 8)
#define SYS_RUN_RIGHT_0         (SYS_KEY_ICON_BASE + 9)
#define SYS_RUN_RIGHT_1         (SYS_KEY_ICON_BASE + 10)
#define SYS_RUN_RIGHT_2         (SYS_KEY_ICON_BASE + 11)
#define SYS_RUN_UP_0            (SYS_KEY_ICON_BASE + 12)
#define SYS_RUN_UP_1            (SYS_KEY_ICON_BASE + 13)
#define SYS_RUN_UP_2            (SYS_KEY_ICON_BASE + 14)
#define SYS_RUN_UP_3            (SYS_KEY_ICON_BASE + 15)
#define SYS_RUN_DOWN_0          (SYS_KEY_ICON_BASE + 16)
#define SYS_RUN_DOWN_1          (SYS_KEY_ICON_BASE + 17)
#define SYS_RUN_DOWN_2          (SYS_KEY_ICON_BASE + 18)
#define SYS_RUN_DOWN_3          (SYS_KEY_ICON_BASE + 19)

//normal //press - down
#define MENU10_BTN_BASE                 ( SYS_KEY_ICON_BASE + 20 )
#define MENU10_BTN_KEY_STEP             ( 6 )
#define MENU10_BTN_ICON_MAX             ( 11 )

//////////100
#endif // SYSTEM_DEFINES_H
