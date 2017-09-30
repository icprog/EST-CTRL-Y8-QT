#ifndef CTHREADREMOTECONTROLLER_H
#define CTHREADREMOTECONTROLLER_H

#include <QObject>
#include <QThread>
#include "thread_remote_worker.h"


//start,stop,monitor the remote working thread
class CThreadRemoteController : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit CThreadRemoteController(QObject *parent = 0);
    ~CThreadRemoteController();

    void threadStart();

private:
        CThreadRemoteWorker *worker;

signals:
    void SqlInit();

public slots:
    void FuncWorkerRes(int , const QString &);  //result of worker thread

};

#endif // CTHREADREMOTECONTROLLER_H
