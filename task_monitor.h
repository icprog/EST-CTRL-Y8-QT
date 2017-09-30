#ifndef     TASK_MONITOR_H
#define     TASK_MONITOR_H

#include <QObject>
#include <QTime>


class CTaskMonitor : public QObject
{
    Q_OBJECT

public:
    CTaskMonitor();

public:
    void Init_TaskMonitor();                            //初始化任务监控
    void On_TaskMonitor();                              //任务监控调度

    void InitDog();                                     //初始化看门狗
    void Dogging();                                     //任务调度看门狗

private:
    void TimeoutMonitor();                             //运行时间限制检测
    void InstallMonitor();                             //判断是否开始使用，默认300小时,之后停止使用
    void DateLostMonitor();                         //check if the year is too early,less than 2015

private:
    QTime           timerTick;

    unsigned char   timerSecond;
    unsigned int   timerMinute;
    unsigned short  timerHour;

    unsigned long   m_lCounter;

    int m_iOneTimeVersionGet;
};

#endif  //TASK_MONITOR_H
