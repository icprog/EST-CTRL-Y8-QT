#include "thread_remote_controller.h"
#include "resource_manager.h"

CThreadRemoteController::CThreadRemoteController(QObject *parent) : QObject(parent)
{

}

CThreadRemoteController::~CThreadRemoteController()
{
    workerThread.quit();
    workerThread.wait();
}

void CThreadRemoteController::threadStart()
{
    worker = new CThreadRemoteWorker;
    worker->moveToThread(&workerThread);

    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker,SIGNAL(WorkerRes(int , const QString &)), this, SLOT(FuncWorkerRes(int , const QString &)));
    connect(RsMgr->g_smartBase,    SIGNAL(ComKeyCommand(unsigned short)),worker,SLOT(keySendTest(unsigned short)));
    connect(g_taskComCtrl,    SIGNAL(ChxValData(unsigned short *)),worker,SLOT(ValSendTest(unsigned short *)));
    //connect(this, SIGNAL(SqlInit()), worker, SLOT(SqlDbInit()));

    workerThread.start();

    emit SqlInit();
}
void CThreadRemoteController::FuncWorkerRes(int , const QString &res)
{

    qDebug()<<res;

}
