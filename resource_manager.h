#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <QObject>
#include <QApplication>
#include <QSettings>

#include "face_base.h"      /*软件初始化显示界面*/
#include "face_mgr.h"
#include "smart_base.h"     /*弹出式快捷按钮*/
#include "smart_mgr.h"
#include "status_base.h"    /*位置信息显示*/
#include "status_mgr.h"
#include "film_base.h"      /*薄膜按键扫描*/
#include "film_mgr.h"
#include "key_base.h"       /*屏幕按键处理*/
#include "key_mgr.h"
#include "fast_base.h"      /*快捷界面触发控件*/
#include "fast_mgr.h"
#include "info_base.h"      /*信息显示控制*/
#include "info_mgr.h"
#include "tech_base.h"      /*发生器技术选择控制*/
#include "tech_mgr.h"
#include "menu_base.h"      /*主界面菜单控制*/
#include "menu_mgr.h"
#include "title_base.h"     /*8寸屏标题，10寸屏顶部背景*/
#include "title_mgr.h"
#include "exit_base.h"      /*系统退出按钮控制，主要用于安卓系统*/
#include "exit_mgr.h"
#include "sim_base.h"       /*系统运动模拟控制*/
#include "sim_mgr.h"
#include "motion_base.h"    /*系统运动动画控制*/
#include "motion_mgr.h"
#include "net_server_base.h"
#include "net_mgr.h"        /*系统网络通信模块*/
#include "net_client_base.h"
#include "motor_base.h"
#include "motor_mgr.h"      /*电机位置校正模块*/
#include "motor_menu.h"
#include "gen_main.h"
#include "gen_config.h"
#include "gen_aec.h"
#include "gen_focus.h"      /*发生器参数控制模块*/
#include "gen_param.h"
#include "gen_param_mgr.h"
#include "gen_client.h"
#include "quick_base.h"     /*固定式快捷按钮*/
#include "quick_mgr.h"
#include "remote_client.h"  /*远程查看与控制*/
#include "remote_server.h"

#include "system_advance.h"     /*高级设定页面*/
#include "system_imepad.h"      /*虚拟按键页面*/
#include "system_password.h"    /*系统设定密码页面*/
#include "system_password2.h"    /*系统设定密码页面,new*/
#include "system_menu.h"        /*系统主菜单页面*/
#include "system_speed.h"       /*电机速度设定页面*/
#include "system_smart.h"       /*系统快捷位置设定*/
#include "system_config.h"      /*系统配置页面*/
#include "system_update.h"      /*系统升级页面*/
#include "debug_page1.h"
#include "debug_page2.h"        /*系统调试界面*/
#include "system_install.h"     /*分期付款设置页面*/
#include "system_install2.h"     /*分期付款设置页面,new*/
#include "system_confirm.h"     /*密码到期确认界面*/
#include "system_confirm2.h"     /*密码到期确认界面,new*/
#include "system_self_run.h"    /*系统自运行页面*/
#include "system_platform.h"    /*系统平台切换页面*/
#include "system_network.h"     /*网络相关设定*/
#include "system_light_curtain.h"/*光幕控制界面*/
#include "system_console1.h"
#include "curtain_mgr.h"        /*光幕开关*/

#include "sys_database.h"
#include "task_can.h"
#include "task_com_ctrl.h"
#include "task_com_key.h"
#include "task_monitor.h"

#include "main_base.h"      /**/
#include "main_mgr.h"
#include "main_frame.h"
#include "main_setting.h"

#include "system_general.h"
#include "system_client_request.h"
#include "skin_manager.h"

#include "thread_remote_controller.h"

#define INIT_STAGE_0        ( 0 )
#define INIT_STAGE_1        ( 1 )

#define INIT_STATE_NORMAL   (0)
#define INIT_STATE_INFO     (1)
#define INIT_STATE_WARNING  (2)
#define INIT_STATE_ERROR    (3)
#define INIT_STATE_FATAL    (4)
#define INIT_STATE_CLEAR    (5)

#define INIT_ERROR_FILM_KEY     (1)
#define INIT_WARNING_DATA_BASE  (2)


#define SYS_MAIN_CFG_FILE   "/sdcard/home/fa/medcare.ini"

class CResourceManager : public QObject
{
    Q_OBJECT
public:
    explicit CResourceManager(QObject *parent = 0);

public:
    void InitView(unsigned short mpf,int stage);
    void InitSlot(int stage);

    unsigned int getInitStage();
    void setInitStage(unsigned int );

public:
    int g_PwdVersion;   //密码版本,1代表老版本，2代表新版本，默认为2
    //公共使用区
    ///////////////////////////////////////////////
    CGenParamMgr    * g_genParamMgr;
    CGenAec         * g_genAec;
    CGenFocus       * g_genFocus;
    CMotorMenu      * g_motorMenu;
    CGenConfig      * g_genConfig;
    CKeyBase        * g_keyBase;
    CSimBase        * g_simBase;
    CSmartBase      * g_smartBase;
    CMotionBase     * g_motionBase;
    CMenuBase       * g_menuBase;
    CTitleBase      * g_titleBase;
    CInfoBase       * g_infoBase;
    CStatusBase     * g_statusBase;
    CTechBase       * g_techBase;
    CFastBase       * g_fastBase;
    CFilmBase       * g_filmBase;
    CMainBase       * g_mainBase;
    CExitBase       * g_exitBase;
    CQuickBase      * g_quickBase;
    CCurtainBase    * g_curtainBase;

    CRemoteClient   * g_remoteClient;
    CRemoteServer   * g_remoteServer;

    CMenuMgr        * g_menuMgr;
    CSimMgr         * g_simMgr;
    CTechMgr        * g_techMgr;
    CKeyMgr         * g_keyMgr;
    CTitleMgr       * g_titleMgr;
    CMainMgr        * g_mainMgr;
    CExitMgr        * g_exitMgr;    
    CInfoMgr        * g_infoMgr;
    CFastMgr        * g_fastMgr;
    CFilmMgr        * g_filmMgr;
    CSmartMgr       * g_smartMgr;
    CMotionMgr      * g_motionMgr;
    CStatusMgr      * g_statusMgr;
    CNetMgr         * g_netMgr;
    CQuickMgr       * g_quickMgr;
    CCurtainMgr     * g_curtainMgr;

    CSystemGeneral      * g_systemGeneral;
    CSystemClient       * g_systemClient;
    CSystemPlatform     * g_systemPlatform;
    CSystemMenu         * g_systemMenu;
    QWidget             * g_systemPsw;
    CSystemSpeed        * g_systemSpeed;
    CSystemSmart        * g_systemSmart;
    CSystemConfig       * g_systemConfig;
    CSystemUpdate       * g_systemUpdate;
    QWidget             * g_systemInstall;
    QWidget             * g_systemConfirm;
    CSystemSelfRun      * g_systemSelfRun;
    CSystemAdvance      * g_systemAdvance;
    CSystemNetWork      * g_systemNetWork;
    CSystemLightCurtain * g_systemLightCurtain;
    QWidget             * g_systemConsole;

    CThreadRemoteController * thRmtCtrl;

    void VisibleWidgetAdd(QWidget *);
    void VisibleWidgetDel(QWidget *);
    void InfoRecord(QString );

private:
    QWidget * pWidgetArrayVisible[VISIBLE_WIDGET_MAX];
    int pWidgetArrayIdx;

    QFile mfileRecord;
    bool bSaveToDisk;
    unsigned int m_iInitPercent;     //初始化百分比

    int getPwdVersion(QString );
signals:
    
public slots:
    
};

extern CResourceManager *  RsMgr;
extern DB_SYS           g_dbsys;                        //系统数据
extern CMainFrame       * g_mainFrame;
extern CMainSetting     * g_mainSetting;
extern QSettings        * g_mainCfg;
extern CSystemDataBase  * g_systemDb;
extern CTaskComKey      * g_taskComKey;
extern CTaskComCtrl     * g_taskComCtrl;
extern CTaskMonitor     * g_taskMonitor;
extern CTaskCan         * g_taskCan;
extern CNetBase         * g_netBase;
extern CSystemImepad    * g_systemPad;
extern CGenMain         * g_GenMain;
extern CGenClient       * g_genClient;
extern CMotorMgr        * g_motorMgr;
extern CFaceBase        * g_faceBase;
extern CDebugPage1      * g_debugPage1;
extern CDebugPage2      * g_debugPage2;
extern CSkinBase        * g_skinBase;
extern  unsigned long g_nCounter;

extern  int g_sysOsType;
extern  int g_sysWidth;
extern  int g_sysHeight;
extern  int g_sysFrameRotate;
void translateFontSize( QWidget *ui );
int MySystem(const char * command);

#endif // RESOURCE_MANAGER_H
