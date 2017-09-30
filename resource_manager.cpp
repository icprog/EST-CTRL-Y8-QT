#include "resource_manager.h"

#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QIODevice>

DB_SYS               g_dbsys;                        //系统数据

CMainFrame          * g_mainFrame   = 0;
CMainSetting        * g_mainSetting = 0;
CResourceManager    * RsMgr         = 0;
CTaskCan            * g_taskCan     = 0;
CNetBase            * g_netBase     = 0;
CSystemImepad       * g_systemPad   = 0;
CTaskMonitor        * g_taskMonitor = 0;
CSystemDataBase     * g_systemDb    = 0;
CTaskComCtrl        * g_taskComCtrl = 0;
CTaskComKey         * g_taskComKey  = 0;
CGenMain            * g_GenMain     = 0;
CGenClient          * g_genClient   = 0;
CMotorMgr           * g_motorMgr    = 0;
CDebugPage1         * g_debugPage1  = 0;
CDebugPage2         * g_debugPage2  = 0;
CFaceBase           * g_faceBase    = 0;
QSettings           * g_mainCfg     = 0;
CSkinBase        * g_skinBase       = 0;
unsigned long g_nCounter    = 0;

CResourceManager::CResourceManager(QObject *parent) :
    QObject(parent)
{
    ///////////////////////////////////////////////
    g_PwdVersion = PWD_VERSION_DEF;
    m_iInitPercent  = 0;                    //初始化百分比,0

    g_genParamMgr   = 0;
    g_genAec        = 0;
    g_genFocus      = 0;
    g_systemMenu    = 0;
    g_motorMenu     = 0;
    g_systemPsw     = 0;
    g_systemSpeed   = 0;
    g_systemSmart   = 0;
    g_systemConfig  = 0;
    g_systemUpdate  = 0;
    g_systemInstall = 0;
    g_systemConfirm = 0;
    g_systemSelfRun = 0;
    g_systemAdvance = 0;
    g_genConfig     = 0;
    g_systemGeneral = 0;
    g_systemClient  = 0;
    g_systemPlatform= 0;
    g_systemNetWork = 0;
    g_systemLightCurtain = 0;

    g_keyBase       = 0;
    g_simBase       = 0;
    g_smartBase     = 0;
    g_motionBase    = 0;
    g_menuBase      = 0;
    g_titleBase     = 0;
    g_infoBase      = 0;
    g_statusBase    = 0;
    g_techBase      = 0;
    g_fastBase      = 0;
    g_filmBase      = 0;
    g_mainBase      = 0;
    g_exitBase      = 0;
    g_quickBase     = 0;
    g_curtainBase   = 0;

    g_remoteClient  = 0;
    g_remoteServer  = 0;

    g_menuMgr   = 0;
    g_simMgr    = 0;
    g_techMgr   = 0;
    g_keyMgr    = 0;
    g_titleMgr  = 0;
    g_mainMgr   = 0;
    g_exitMgr   = 0;
    g_infoMgr   = 0;
    g_fastMgr   = 0;
    g_filmMgr   = 0;
    g_smartMgr  = 0;
    g_motionMgr = 0;
    g_statusMgr = 0;
    g_netMgr    = 0;
    g_quickMgr  = 0;
    g_curtainMgr = 0;

    thRmtCtrl = 0;

    pWidgetArrayIdx     = 0;

    bSaveToDisk = false;

    if( bSaveToDisk )
    {
        mfileRecord.setFileName(QCoreApplication::applicationDirPath() +"/log.txt");
        if(mfileRecord.exists())
            mfileRecord.remove();

        mfileRecord.open(QIODevice::WriteOnly);
    }

    getPwdVersion(QCoreApplication::applicationDirPath() +"/pwdversion");
}

int CResourceManager::getPwdVersion(QString strFile)
{
    QSettings config(strFile, QSettings::IniFormat);

    g_PwdVersion = config.value("system/version",PWD_VERSION_DEF).toUInt();

    return g_PwdVersion;
}

unsigned int CResourceManager::getInitStage()
{
    return m_iInitPercent;
}

void CResourceManager::setInitStage(unsigned int stage)
{
    //更新初始化百分比
    m_iInitPercent  = stage;

    //更新界面显示
    g_faceBase->setProgressBar(stage);
}

void CResourceManager::InitView(unsigned short mpf,int stage)
{

    if(stage == INIT_STAGE_0)
    {

        setInitStage(2);
        g_genFocus    = new CGenFocus(mpf);

        setInitStage(4);
        g_genAec      = new CGenAec(mpf);

        setInitStage(6);
        g_systemClient  = new CSystemClient();

        setInitStage(8);
        if(g_PwdVersion == PWD_VERSION_1)
            g_systemConfirm = new CSystemConfirm();
        else
            g_systemConfirm = new CSystemConfirm2();

        setInitStage(10);
        g_GenMain      = new CGenMain(mpf);
        g_genClient    = new CGenClient();

        setInitStage(12);
        g_genParamMgr   = new CGenParamMgr(mpf);

        setInitStage(14);
        g_systemGeneral = new CSystemGeneral();

        setInitStage(16);
        if(g_PwdVersion == PWD_VERSION_1)
            g_systemPsw    = new CSystemPassword();
        else
            g_systemPsw    = new CSystemPassword2();

        setInitStage(18);
        g_mainSetting       = new CMainSetting();

        setInitStage(20);
        g_genConfig  = new CGenConfig();

        setInitStage(22);
        g_fastMgr           = new CFastMgr();
        g_fastBase = g_fastMgr->fastInit(mpf);

        setInitStage(24);
        g_filmMgr            = new CFilmMgr();
        g_filmBase  = g_filmMgr->filmInit(mpf);

        setInitStage(26);
        g_smartMgr          = new CSmartMgr();
        g_smartBase  = g_smartMgr->smartInit(mpf);

        setInitStage(28);
        g_motionMgr         = new CMotionMgr();
        g_motionBase   = g_motionMgr->motionInit(mpf);

        setInitStage(30);
        g_statusMgr         = new CStatusMgr();
        g_statusBase   = g_statusMgr->statusInit(mpf);

        setInitStage(32);
        g_menuMgr           = new CMenuMgr();
        g_menuBase     = g_menuMgr->menuInit(mpf);

        setInitStage(34);
        g_simMgr            = new CSimMgr();
        g_simBase      = g_simMgr->simInit(mpf);

        setInitStage(36);
        g_keyMgr           = new CKeyMgr();
        g_keyBase     = g_keyMgr->keyInit(mpf);

        setInitStage(38);
        g_techMgr           = new CTechMgr();
        g_techBase     = g_techMgr->techInit(mpf);
        g_taskComKey        = new CTaskComKey();

        setInitStage(40);
        g_titleMgr          = new CTitleMgr();
        g_titleBase    = g_titleMgr->titleInit(mpf);

        setInitStage(42);
        g_exitMgr          = new CExitMgr();
        g_exitBase    = g_exitMgr->exitInit(mpf);

        setInitStage(44);
        g_quickMgr          = new CQuickMgr();
        g_quickBase = g_quickMgr->quickInit(mpf);

        setInitStage(46);
        g_infoMgr           = new CInfoMgr();
        g_infoBase     = g_infoMgr->infoInit(mpf);

        setInitStage(48);
        g_taskCan           = new CTaskCan();
        Q_ASSERT(g_taskCan != 0);
        g_taskCan->Init_TaskCan();

        setInitStage(50);
        g_taskComCtrl          = new CTaskComCtrl();
        Q_ASSERT(g_taskComCtrl != 0);

        setInitStage(52);
        g_taskMonitor       = new CTaskMonitor();
        g_taskMonitor->Init_TaskMonitor();

        setInitStage(54);
        g_netMgr            = new CNetMgr();
        g_netMgr->netWorkInit(mpf);

        setInitStage(56);
        g_curtainMgr          = new CCurtainMgr();
        g_curtainBase     = g_curtainMgr->curtainInit(mpf);

        setInitStage(64);
        g_mainMgr           = new CMainMgr();
        g_mainBase          = g_mainMgr->mainInit(mpf);

        setInitStage(66);
        thRmtCtrl           = new CThreadRemoteController();

    }

    if(stage == INIT_STAGE_1 )
    {

        g_systemMenu    = new CSystemMenu();

        g_motorMenu     = new CMotorMenu(mpf);

        g_motorMgr      = new CMotorMgr();
        g_motorMgr->motorInit(mpf);

        g_systemSpeed   = new CSystemSpeed(mpf);

        g_systemSmart   = new CSystemSmart(mpf);

        g_systemConfig  = new CSystemConfig();

        g_systemUpdate  = new CSystemUpdate();

        g_systemNetWork = new CSystemNetWork();

        g_debugPage1  = new CDebugPage1(mpf);
        g_debugPage2  = new CDebugPage2(mpf);

        //use new version of password
        if(g_PwdVersion == PWD_VERSION_1)
            g_systemInstall     = new CSystemInstall();
        else
            g_systemInstall     = new CSystemInstall2();

        g_systemSelfRun     = new CSystemSelfRun();

        g_systemPlatform    = new CSystemPlatform();

        g_systemAdvance     = new CSystemAdvance();

        g_remoteClient      = new CRemoteClient();

        g_remoteServer      = new CRemoteServer();

        g_systemLightCurtain = new CSystemLightCurtain();

        g_systemConsole = new CSystemConsole1();

    }
}

void CResourceManager::InitSlot( int stage )
{

    if(stage == INIT_STAGE_0 )
    {
        connect(g_genFocus,       SIGNAL(GenFocusChange(int)),    g_GenMain,SLOT(OnGenFocusChange(int)));
        connect(g_genFocus,       SIGNAL(GenFocusChange(int)),    g_genClient,SLOT(OnGenFocusChange(int)));
        connect(g_genFocus,       SIGNAL(PopupHide(QWidget*)),    g_mainBase,SLOT(OnPopupHide(QWidget*)));
        connect(g_genFocus,       SIGNAL(PopupHide(QWidget*)),    g_genConfig,SLOT(OnPopupHide(QWidget*)));

        connect(g_genAec,         SIGNAL(GenAecChange(int)),      g_GenMain,SLOT(OnGenAecChange(int)));
        connect(g_genAec,         SIGNAL(GenAecChange(int)),      g_genClient,SLOT(OnGenAecChange(int)));
        connect(g_genAec,         SIGNAL(PopupHide(QWidget*)),    g_mainBase,SLOT(OnPopupHide(QWidget*)));
        connect(g_genAec,         SIGNAL(PopupHide(QWidget*)),    g_genConfig,SLOT(OnPopupHide(QWidget*)));

        connect(g_genConfig,     SIGNAL(GenTechChange(int)),     g_GenMain,SLOT(OnGenTechChange(int)));
        connect(g_genConfig,     SIGNAL(ViewChange(int)),        g_mainBase,SLOT(OnViewChange(int)));

        connect(g_GenMain,         SIGNAL(PopupShow(int)),         g_genConfig,SLOT(OnPopupShow(int)));
        connect(g_GenMain,         SIGNAL(PopupShow(int)),         g_mainBase,SLOT(OnPopupShow(int)));
        connect(g_GenMain,         SIGNAL(ParamShow(int)),         g_genParamMgr,SLOT(OnParamShow(int)));
        connect(g_GenMain,         SIGNAL(BodyIndexChange(int)),   g_genParamMgr,SLOT(OnBodyIndexChange(int)));
        connect(g_GenMain,         SIGNAL(BodyIndexChange(int)),   g_genFocus,SLOT(OnBodyIndexChange(int)));
        connect(g_GenMain,         SIGNAL(BodyIndexChange(int)),   g_genAec,SLOT(OnBodyIndexChange(int)));

        connect(g_taskComCtrl,         SIGNAL(ComKeyCommand(unsigned short)),g_simBase,SLOT(OnComKeyCommand(unsigned short)));

        connect(g_systemClient,     SIGNAL(PopupHide(QWidget*)),g_mainBase,SLOT(OnPopupHide(QWidget*)));
        if(g_netBase)
            connect(g_systemClient,     SIGNAL(ClientAck(int)),     g_netBase,SLOT(OnClientAck(int)));


        connect(g_systemPsw,   SIGNAL(ViewChange(int)),    g_mainBase,SLOT(OnViewChange(int)));
        connect(g_systemPsw,   SIGNAL(ViewChange(int)),    g_mainFrame,SLOT(OnViewChange(int)));

        connect(g_systemGeneral,    SIGNAL(ViewChange(int)),    g_mainBase,SLOT(OnViewChange(int)));

        if(g_netBase)
        {
            connect(g_netBase,    SIGNAL(PopupShow(int)),     g_mainBase,SLOT(OnPopupShow(int)));
            connect(g_netBase,    SIGNAL(SmartChange(int)),   g_smartBase,SLOT(OnSmartChange(int)));
            connect(g_netBase,    SIGNAL(InfoMsgCtrl(int,int,void*)), g_infoBase,SLOT(OnInfoMsgCtrl(int ,int ,void*)));
            connect(g_netBase, SIGNAL(RemoteKeyPressed(int)),   g_mainBase,SLOT(OnFilmKeyDown(int)));
            connect(g_netBase, SIGNAL(RemoteKeyReleased(int)),   g_mainBase,SLOT(OnFilmKeyUp(int)));
            connect(g_netBase, SIGNAL(RemotePageChange(int)),   g_mainBase,SLOT(OnPageChange(int)));
        }

        connect(g_mainBase,         SIGNAL(ViewChange(int)),    g_menuBase ,SLOT(OnViewChange(int)));
        connect(g_mainBase,         SIGNAL(ViewChange(int)),    g_mainSetting,SLOT(OnViewChange(int)));
        connect(g_mainBase,         SIGNAL(ViewChange(int)),    g_mainFrame,SLOT(OnViewChange(int)));

        connect(g_genParamMgr,      SIGNAL(PopupShow(int)),     g_genConfig,SLOT(OnPopupShow(int)));
        connect(g_genParamMgr,      SIGNAL(PopupShow(int)),     g_mainBase,SLOT(OnPopupShow(int)));
        connect(g_genParamMgr,      SIGNAL(PopupHide(QWidget*)),g_mainBase,SLOT(OnPopupHide(QWidget*)));
        connect(g_genParamMgr,      SIGNAL(PopupHide(QWidget*)),g_genConfig,SLOT(OnPopupHide(QWidget*)));

        connect(g_menuBase, SIGNAL(ViewChange(int)),    g_mainBase,SLOT(OnViewChange(int)));
        connect(g_menuBase, SIGNAL(MenuKeyDown(int)),   g_smartBase,SLOT(OnKeyPressed(int)));

        connect(g_simBase,    SIGNAL(InfoMsgCtrl(int,int,void*)), g_infoBase,SLOT(OnInfoMsgCtrl(int ,int ,void*)));

        connect(g_infoBase,    SIGNAL(RunStatusChange(int)),   g_smartBase,SLOT(OnStatusChange(int)));
        connect(g_infoBase,    SIGNAL(ViewChange(int)),   g_mainBase,SLOT(OnViewChange(int)));

        connect(g_fastBase, SIGNAL(ViewChange(int)),    g_mainBase, SLOT(OnViewChange(int)));
        connect(g_fastBase, SIGNAL(ViewChange(int)),    g_menuBase, SLOT(OnViewChange(int)));
        connect(g_fastBase, SIGNAL(PopupShow(int)),     g_mainBase, SLOT(OnPopupShow(int)));
        connect(g_fastBase, SIGNAL(SmartChange(int)),   g_smartBase,SLOT(OnSmartChange(int)));

        connect(g_filmBase, SIGNAL(SmartChange(int)),   g_smartBase,SLOT(OnSmartChange(int)));
        connect(g_filmBase, SIGNAL(FilmKeyDown(int)),   g_smartBase,SLOT(OnKeyPressed(int)));
        connect(g_filmBase, SIGNAL(FilmKeyDown(int)),   g_mainBase,SLOT(OnFilmKeyDown(int)));
        connect(g_filmBase, SIGNAL(FilmKeyUp(int)),   g_mainBase,SLOT(OnFilmKeyUp(int)));

        connect(g_quickBase,SIGNAL(SmartChange(int)),   g_smartBase,SLOT(OnSmartChange(int)));
        connect(g_quickBase,SIGNAL(QuickKeyDown(int)),  g_smartBase,SLOT(OnKeyPressed(int)));

        connect(g_keyBase,  SIGNAL(ViewChange(int)),    g_menuBase,SLOT(OnViewChange(int)));
        connect(g_keyBase,  SIGNAL(ViewChange(int)),    g_mainBase,SLOT(OnViewChange(int)));
        connect(g_keyBase,  SIGNAL(softWareKeyDown(int)),  g_smartBase,SLOT(OnKeyPressed(int)));

        connect(g_techBase,    SIGNAL(GenTechChange(int)),     g_mainBase,SLOT(OnGenTechChange(int)));
        connect(g_techBase,    SIGNAL(GenTechChange(int)),     g_GenMain,SLOT(OnGenTechChange(int)));
        connect(g_techBase,    SIGNAL(GenTechChange(int)),     g_menuBase,SLOT(OnGenTechChange(int)));
        connect(g_techBase,    SIGNAL(GenTechChange(int)),     g_genClient,SLOT(OnGenTechChange(int)));

        connect(g_genClient,    SIGNAL(GenTechChange(int)),     g_techBase,SLOT(OnGenTechChange(int)));
        connect(g_genClient,    SIGNAL(GenTechChange(int)),     g_GenMain,SLOT(OnGenTechChange(int)));
        connect(g_genClient,    SIGNAL(GenFocusChange(int)),    g_GenMain,SLOT(OnGenFocusChange(int)));
        connect(g_genClient,    SIGNAL(ParamChange(int,int)),   g_GenMain,SLOT(OnParamChange(int,int)));
        connect(g_genClient,    SIGNAL(ViewChange(int)),    g_mainBase, SLOT(OnViewChange(int)));

        connect(g_systemConfirm,    SIGNAL(ViewChange(int)),    g_mainBase,     SLOT(OnViewChange(int)));

        connect(g_smartBase,    SIGNAL(PopupHide(QWidget*)),g_mainBase,SLOT(OnPopupHide(QWidget*)));
        connect(g_smartBase,    SIGNAL(ComKeyCommand(unsigned short)),g_simBase,SLOT(OnComKeyCommand(unsigned short)));
        connect(g_smartBase,    SIGNAL(RunStatusChange(int,QPushButton*)),g_fastBase,SLOT(OnStatusChange(int,QPushButton*)));
        connect(g_smartBase,    SIGNAL(RunStatusChange(int,QPushButton*)),g_quickBase,SLOT(OnStatusChange(int,QPushButton*)));
        connect(g_smartBase,    SIGNAL(InfoMsgCtrl(int,int,void*)), g_infoBase,SLOT(OnInfoMsgCtrl(int ,int ,void*)));

        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_keyBase,SLOT(OnViewDirChange(int)));
        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_quickBase,SLOT(OnViewDirChange(int)));
        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_mainBase,SLOT(OnViewDirChange(int)));
        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_menuBase,SLOT(OnViewDirChange(int)));
        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_simBase,SLOT(OnViewDirChange(int)));
        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_smartBase,SLOT(OnViewDirChange(int)));
        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_curtainBase,SLOT(OnViewDirChange(int)));
        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_techBase,SLOT(OnViewDirChange(int)));
        connect(g_statusBase,  SIGNAL(ViewDirChange(int)), g_netBase,SLOT(OnViewDirChange(int)));
    }

    if(stage == INIT_STAGE_1 )
    {
        connect(g_systemMenu,         SIGNAL(ViewChange(int)),    g_mainBase,SLOT(OnViewChange(int)));
        connect(g_systemSelfRun,    SIGNAL(ViewChange(int)),    g_mainBase,SLOT(OnViewChange(int)));
        connect(g_mainBase,SIGNAL(SmartPressed(int)),g_smartBase,SLOT(OnSmartPressed(int)));
    }
}
//setPointSize
//setPixelSize
void translateFontSize( QWidget *ui )
{
    QObjectList l;
    QObject *w;
    if (!ui)
        return;

    QFont font = QFont(ui->font());
    switch(font.pointSize())
    {
    case 10:
    case 11:
    case 12:
        font.setPixelSize(12);
        break;
    case 13:
    case 14:
        font.setPixelSize(14);
        break;
    case 15:
    case 16:
        font.setPixelSize(16);
        break;
    case 17:
    case 18:
        font.setPixelSize(18);
        break;
    case 19:
    case 20:
        font.setPixelSize(20);
        break;
    case 21:
    case 22:
        font.setPixelSize(22);
        break;
    case 23:
    case 24:
        font.setPixelSize(24);
        break;
    case 25:
    case 26:
        font.setPixelSize(26);
        break;
    case 27:
    case 28:
        font.setPixelSize(28);
        break;
    case 29:
    case 30:
        font.setPixelSize(30);
        break;
    case 31:
    case 32:
        font.setPixelSize(32);
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        font.setPixelSize(36);
        break;
    default:
        font.setPixelSize(24);
        break;
    }
    //    font.setPixelSize(46);
    ui->setFont(font);
    l = ui->children();

    foreach (w, l)
    {
        QWidget *ww = dynamic_cast<QWidget *>(w);
        if (ww)
        {
            translateFontSize( ww );
        }
    }
}

void CResourceManager::VisibleWidgetAdd(QWidget *pWidgetNew)
{
    for(int mIdx = 0 ;mIdx < pWidgetArrayIdx ;mIdx++)
    {
        if(pWidgetArrayVisible[mIdx] == pWidgetNew)
            return;
    }

    if(pWidgetArrayIdx >= VISIBLE_WIDGET_MAX)
        return;

    pWidgetArrayVisible[pWidgetArrayIdx] = pWidgetNew;

    QString mStr;
    mStr = pWidgetNew->objectName();

    if(mStr.isEmpty())
    {
        fprintf(stderr, "pWidgetNew->objectName()");
    }
    mStr.append("\t\tshow\t");

    InfoRecord(mStr);

    pWidgetArrayIdx++;
}
void CResourceManager::VisibleWidgetDel(QWidget *pWidget)
{
    int mWidgetPos = -1;
    for(int mIdx = 0 ;mIdx < pWidgetArrayIdx ;mIdx++)
    {
        if(pWidgetArrayVisible[mIdx] == pWidget)
        {
            mWidgetPos = mIdx;
            break;
        }
    }

    if(mWidgetPos < 0)
        return;

    QString mStr;
    mStr = pWidget->objectName();
    mStr.append("\t\thide\t");

    InfoRecord(mStr);

    for(int mIdx = mWidgetPos ;mIdx < pWidgetArrayIdx ;mIdx++)
    {
        pWidgetArrayVisible[mIdx] = pWidgetArrayVisible[mIdx + 1];
    }

    pWidgetArrayIdx--;

}
void CResourceManager::InfoRecord(QString pInfo)
{

    if(!bSaveToDisk)
        return;

    if(!mfileRecord.isOpen())
        return;

    QString strDate;

    QTime ts = QTime::currentTime();
    QDate dt = QDate::currentDate();

    strDate.sprintf("%02d.%02d.%02d-%02d:%02d:%02d\t",dt.year(),dt.month(),dt.day(),ts.hour(),ts.minute(),ts.second());

    QTextStream fStream(&mfileRecord);
    fStream << strDate << pInfo << endl;
    fStream.flush();
}

int MySystem(const char * command)
{

#ifdef QT_ARCH_ARM
    if(strcmp(command,"exit") == 0 || strcmp(command,"reboot") == 0 )
    {
        return system("reboot");
    }
    return system(command);
#else
    if(strcmp(command,"exit") == 0 || strcmp(command,"reboot") == 0 )
    {
        QApplication::exit(0);
        return 0;
    }
    return 0;
#endif

}
