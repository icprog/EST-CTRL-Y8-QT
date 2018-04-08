#ifndef CTHREADREMOTECONTROLLER_H
#define CTHREADREMOTECONTROLLER_H

#include <QObject>
#include <QThread>
#include <QProcess>

//检测WEB通过共享内存发送过来的指令，以按键的方式，发送给主程序
//通过共享内存，发送状态信息给WEB
class CThreadRemoteController  : public QThread
{

public:
    CThreadRemoteController();

protected:
    virtual void run();

};

#endif // CTHREADREMOTECONTROLLER_H
