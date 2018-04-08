#include "thread_remote_controller.h"

#include "resource_manager.h"
extern CResourceManager *  RsMgr;

#include "./sys/sys_database.h"
extern CSysDataBase * g_sysDb;

extern CMainBase        * g_mainBase ;

#include "./base/film_base.h"
extern CFilmBase   * g_filmBase;

CThreadRemoteController::CThreadRemoteController()
{

    //旧线程
}


void CThreadRemoteController::run()
{

    //新线程
    setTerminationEnabled(true);

    //延时5秒，用于等待其他模块启动
    sleep(5);

    QProcess *scanPro;      //用于扫描外部输入，分析输入结果
    //创建用于扫描WEB输入的进程
    scanPro = new QProcess();

    int mResCode;               //执行外部程序返回消息
    QStringList strParamList;   //执行外部程序参数列表
    QByteArray  byRead;         //扫描返回的结果
    QString byCmdFinder;       //用于查找WEB发送过来的命令
    int mCmdStartPos;           //命令段开始的位置

    while(1)
    {
        QKeyEvent * keyEvent;     //待发送的命令，写在循环内部，防止内存泄漏
        keyEvent = NULL;        //清空消息内容
        //检测WEB消息
        strParamList.clear();           //清空参数队列
        strParamList.append("1");       //读取共享内存
        strParamList.append("1");       //通道1

        if(scanPro->atEnd())            //如果程序没有在执行，进行扫描作业。
        {
            scanPro->start("/sdcard/home/fa/NetAdapter",strParamList);    //启动共享内存读取程序
            scanPro->waitForStarted(-1);
            scanPro->waitForFinished(-1);                  //等待最长200ms
            scanPro->waitForReadyRead(-1);                  //等待允许数据读取
            byRead = scanPro->readAllStandardOutput();      //读取WEB发送的内容
        }

        if(byRead.length() > 0)                         //判断是否有数据
        {
            mCmdStartPos = byRead.indexOf("ARGV0=");    //命令标志位
            byCmdFinder = byRead.mid(mCmdStartPos+6,12);    //提取命令
            //fprintf(stderr, "LEN=%d:STR=%s",byCmdFinder.length(),byCmdFinder.toStdString().data());

            //根据命令，发送按键消息给主应用程序
            if(0 == byCmdFinder.compare("key_smart_01"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F1,Qt::NoModifier);   //Qt::ControlModifier  组合
            }
            if(0 == byCmdFinder.compare("key_smart_02"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F2,Qt::NoModifier);   //Qt::ControlModifier  组合
            }
            if(0 == byCmdFinder.compare("key_smart_03"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F3,Qt::NoModifier);   //Qt::ControlModifier  组合
            }
            if(0 == byCmdFinder.compare("key_smart_04"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F4,Qt::NoModifier);   //Qt::ControlModifier  组合
            }
            if(0 == byCmdFinder.compare("key_smart_05"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F5,Qt::NoModifier);   //Qt::ControlModifier  组合
            }
            if(0 == byCmdFinder.compare("key_smart_06"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F6,Qt::NoModifier);   //Qt::ControlModifier  组合
            }
            if(0 == byCmdFinder.compare("key_smart_07"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F7,Qt::NoModifier);   //Qt::ControlModifier  组合
            }
            if(0 == byCmdFinder.compare("key_smart_08"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F8,Qt::NoModifier);   //Qt::ControlModifier  组合
            }
            if(0 == byCmdFinder.compare("key_smart_09"))
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_F9,Qt::NoModifier);   //Qt::ControlModifier  组合
            }

            if(keyEvent)       //事件不为空才发送
            {
                g_filmBase->SetKeySound();
                qApp->postEvent(g_mainBase,keyEvent);
            }

            byRead.clear();
        }

        //发送数据更新到WEB
        strParamList.clear();           //清空参数队列
        strParamList.append("0");       //写共享内存
        strParamList.append("0");       //通道0
        strParamList.append(QString::number(g_sysDb->CurrentData[tRAIL_FID]));  //发给WEB的显示数据
        strParamList.append(QString::number(g_sysDb->CurrentData[tRAIL_SID]));
        strParamList.append(QString::number(g_sysDb->CurrentData[tRAIL_ANG]));
        strParamList.append(QString::number(g_sysDb->CurrentData[tRAIL_DTH]));
        strParamList.append(QString::number(g_sysDb->CurrentData[tRAIL_BEH]));
        strParamList.append(QString::number(g_sysDb->CurrentData[tRAIL_DTP]));
        mResCode = QProcess::execute("/sdcard/home/fa/NetAdapter",strParamList);

        if(mResCode == -2)      //判断应用是否没有启动
        {
            fprintf(stderr, "the process cannot be started");
            break;
        }

        if(mResCode == -1)      //判断应用是否崩溃
        {
            fprintf(stderr, "the process crashes");
            break;
        }

        msleep(100);    //延时100ms
    }
}

