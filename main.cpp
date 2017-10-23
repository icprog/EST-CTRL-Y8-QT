#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>
#include <QFontDatabase>
#include <QDesktopServices>

#include "./ndt08/thread_joystick.h"
#include "./base/thread_touchscreen.h"
#include "resource_manager.h"

void AutoRunCfg();                          //自动运行检测配置
void ScreenCheck();                         //屏幕分辨率检测
void ApplyLanguage(unsigned char nLang);    //翻译文件加载

//消息处理机制
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
void myMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg);
#else
void myMessageOutput(QtMsgType type, const char *msg);
#endif

int g_sysWidth;         //屏幕宽度
int g_sysHeight;        //屏幕高度
int g_sysFrameRotate;   //主界面旋转角度

//翻译文件加载对象
QTranslator * g_mTranslator = 0;

//1.设置错误处理函数
//2.设定软件字体
//3.数据配置文件加载
//4.语言应用
//5.初始化界面
//6.主窗口显示
int main( int argc, char *argv[] )//主程序
{

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))       //错误处理机制
    qInstallMessageHandler(myMessageHandler);
#else
    qInstallMsgHandler(myMessageOutput);
#endif

    QApplication a( argc, argv );                   //主应用对象

#ifdef QT_ARCH_ARM                                  //字体
    QFont fn("WenQuanYi Micro Hei",18);             //ARM版本使用文泉译
    qApp->setFont( fn );
#else
    QFont fn("Song Ti",18);                         //其他版本使用宋体
    qApp->setFont( fn );
#endif                            

    g_systemDb = new CSystemDataBase();                     //读取系统配置信息

    if(!QFile::exists(SYS_MAIN_CFG_FILE))
        g_systemDb->SaveSystem(SYS_MAIN_CFG_FILE);

    g_mainCfg = new QSettings(SYS_MAIN_CFG_FILE,QSettings::IniFormat);

    g_systemDb->Init_DataBase();

    ScreenCheck();

    ////for test  only
    ////PF_CEIL_10_A;PF_UARM_10_A;PF_RAIL_12_A;PF_CEIL_10_B;PF_NDT_10_A
    ////PF_CEIL_08_A;PF_UARM_08_A;PF_RAIL_08_A;PF_RF_8_A;PF_NDT_8_A
    g_dbsys.utility.mPlatform = PF_NDT_8_A;
    g_dbsys.utility.mNetTcpMode = TARGET_TCP_CLIENT;
    g_dbsys.utility.mNetShow = 1;

    ApplyLanguage(g_dbsys.dbsystem.language);               //语言

    CSkinManager skinMgr;                                   //图片资源
    g_skinBase = skinMgr.skinInit(g_dbsys.utility.mPlatform,g_dbsys.utility.mSkinIdx);

    CFaceMgr * faceMgr = new CFaceMgr();                    //初始化界面
    g_faceBase = faceMgr->faceInit(g_dbsys.utility.mPlatform);

    RsMgr       = new CResourceManager();                   //创建资源管理

#ifdef QT_ARCH_ARM
    //NDT 8 inch and RF system need screen rotate 180
    if(g_dbsys.utility.mPlatform == PF_RF_8_A ||g_dbsys.utility.mPlatform == PF_NDT_8_A)
        g_sysFrameRotate = 180;
#endif

    //如果12寸屏，旋转180度
    if(g_dbsys.utility.mPlatform == PF_RAIL_12_A)
    {
#if defined QT_ARCH_ARM
        g_sysFrameRotate = 180;     //ARM需要180度
#elif defined Q_OS_ANDROID
        g_sysFrameRotate = 270;     //安卓需要270度
#else
        g_sysFrameRotate = 0;     //安卓需要270度
#endif
    }

    CMainFrame frmMainframe;                                //创建并显示MainframeForm
    frmMainframe.show();

    if(!g_dbsys.utility.mCursorShow)                        //是否显示光标，一般ARM不显示，
    {
        if(!QFile::exists("/dev/event2"))                   //如果认为鼠标接入，则显示光标
        {
            qApp->setOverrideCursor(Qt::BlankCursor);       //隐藏光标
        }

        QCursor::setPos(0,0);                               //设定光标到一个特定位置
    }

#ifdef QT_ARCH_ARM                                          //基于tslib触控屏扫描线程，ARM板的触控
   // CThreadTouchScreen tCtp;
   // tCtp.start();
#endif

#ifndef Q_OS_ANDROID
    //基于udev的USB摇杆扫描线程

    //CThreadJoystick * tJoyStick;
    //tJoyStick = new CThreadJoystick();
    //tJoyStick->setVisible(false);

#endif

    AutoRunCfg();                          //自动运行检测配置

    return a.exec();
}

//本程序设计，必须g_sysWidth > g_sysHeight,否则显示异常
//分辨率需要接近4:3
void ScreenCheck()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();

    QRect screenRect = desktopWidget->availableGeometry();

    g_sysWidth  = screenRect.width();
    g_sysHeight = screenRect.height();

    if(g_sysHeight > g_sysWidth )
    {
        int mBuf = g_sysHeight;

        g_sysHeight = g_sysWidth;
        g_sysWidth = mBuf;
        g_sysFrameRotate = -90;
    }else {
        g_sysFrameRotate = 0;
    }


    if(g_mainCfg->contains("ScreenWidth"))            //如果存在配置文件，从配置文件中读取分辨率
    {
        g_sysWidth  = g_mainCfg->value("ScreenWidth",800).toInt();
    }else
    {                       //如果不存在配置文件，保存分辨率到配置文件
        g_mainCfg->setValue("ScreenWidth",g_sysWidth);
    }

    if(g_mainCfg->contains("ScreenHeight"))            //如果存在配置文件，从配置文件中读取分辨率
    {
        g_sysHeight = g_mainCfg->value("ScreenHeight",600).toInt();
    }else
    {                       //如果不存在配置文件，保存分辨率到配置文件
        g_mainCfg->setValue("ScreenHeight",g_sysHeight);
    }
}

//qt 资源文件提取->翻译文件
void SaveTranslateFile()
{

    if(!QFile::exists("/sdcard/home/fa/w6410.qm"))
    {
        QFile inputFile(":/QRes/w6410.qm");

        inputFile.open(QIODevice::ReadOnly);        // 只读打开
        inputFile.copy("/sdcard/home/fa/w6410.qm");
        inputFile.close();          // 关闭文本流
    }
}

//////////////////切换系统语言
///nLang允许:255 for delete translator, _ENGLISH default English,_CHINESE for Chinese
//print system font database
void ApplyLanguage(unsigned char nLang)
{  

    SaveTranslateFile();

    if (nLang == 255)
        return;

    g_mTranslator = new QTranslator();
    bool mRes = false;

    if (nLang ==_ENGLISH)
        mRes = g_mTranslator->load("/sdcard/home/fa/w6410_en.qm",QCoreApplication::applicationDirPath());

    if (nLang ==_CHINESE)
        mRes = g_mTranslator->load("/sdcard/home/fa/w6410.qm",QCoreApplication::applicationDirPath());

    if (nLang == _RUSSIAN)
        mRes =  g_mTranslator->load("/sdcard/home/fa/w6410_ru.qm",QCoreApplication::applicationDirPath());

    if (nLang == _KOREA)
        mRes =  g_mTranslator->load("/sdcard/home/fa/w6410_kr.qm",QCoreApplication::applicationDirPath());

    if(!mRes)
        fprintf(stderr,".................ApplyLanguage failure!!");

    qApp->installTranslator(g_mTranslator);

}
//自动运行检测配置
//检测特定文件的存在，并执行该文件
void AutoRunCfg()
{
    //如果关闭了该功能，退出，不继续执行
    if(!g_mainCfg->value("AutoRunEnable",true).toInt())
        return;

    QString mStr = "/udisk/";
    mStr.append(g_dbsys.dbsystem.machine2);
    mStr.append("/autorun.txt");

    if(!QFile::exists(mStr))
        return;

    QString mStrBuf = "mv ";
    mStrBuf.append(mStr.toLatin1().data());
    mStrBuf.append(" ");
    mStrBuf.append(mStr.toLatin1().data());
    mStrBuf.append(".bak");

    //执行自动运行
    system(mStr.toLatin1().data());

    //将该文件增加后缀，防止再次运行
    system(mStrBuf.toLatin1().data());
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
void myMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg)
{
    switch (type) {
    case QtInfoMsg:
        fprintf(stderr, "QtInfoMsg=%s\nFILE=%s||FUNC=%s||LINE=%d", msg.toLocal8Bit().data(),context.function,context.file,context.line);
    case QtDebugMsg:
        fprintf(stderr, "QtDebugMsg=%s\nFILE=%s||FUNC=%s||LINE=%d", msg.toLocal8Bit().data(),context.function,context.file,context.line);
        break;
    case QtWarningMsg:
        fprintf(stderr, "QtWarningMsg=%s\nFILE=%s||FUNC=%s||LINE=%d",  msg.toLocal8Bit().data(),context.function,context.file,context.line);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "QtCriticalMsg=%s\nFILE=%s||FUNC=%s||LINE=%d",  msg.toLocal8Bit().data(),context.function,context.file,context.line);
        abort();
        break;
    case QtFatalMsg:
        fprintf(stderr, "QtFatalMsg=%s\nFILE=%s||FUNC=%s||LINE=%d",  msg.toLocal8Bit().data(),context.function,context.file,context.line);
        abort();
    }
}
#else
void myMessageOutput(QtMsgType type, const char *msg)
{
    switch (type)
    {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg);
        abort();
    }
}
#endif

