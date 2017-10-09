#include "thread_remote_worker.h"
#include <QFile>
#include <QDebug>
#include <QSettings>

#include "resource_manager.h"

CThreadRemoteWorker::CThreadRemoteWorker(QObject *parent) : QObject(parent)
{
    qDebug()<<"CThreadRemoteWorker init thread:"<<QThread::currentThread();

    //mQuery = NULL;
}
/*
bool CThreadRemoteWorker::SqlDbInit()
{
    qDebug()<<"CThreadRemoteWorker run thread:"<<QThread::currentThread();

    if(!QFile::exists(QCoreApplication::applicationDirPath() + "/clientinfo.ini"))
        return false;

    QSettings * configClientInfo = new QSettings(QCoreApplication::applicationDirPath() + "/clientinfo.ini",QSettings::IniFormat);

    mMainDb = QSqlDatabase::addDatabase("QMYSQL");

    mServerAddr = QString::fromUtf8(configClientInfo->value("/server/address").toByteArray());
    mServerPort  = configClientInfo->value("/server/port").toInt();
    mSvrDb          = QString::fromUtf8(configClientInfo->value("/server/dbname").toByteArray());
    mSvrUser       = QString::fromUtf8(configClientInfo->value("/server/dbuser").toByteArray());
    mSvrPwd        = QString::fromUtf8(configClientInfo->value("/server/dbpwd").toByteArray());
    mClientId        = QString::fromUtf8(configClientInfo->value("/client/id").toByteArray());

    mMainDb.setHostName(mServerAddr);

    if(mServerPort != 0)
        mMainDb.setPort(mServerPort);

    //db_cloud_001
    mMainDb.setDatabaseName(mSvrDb);

    //db_cloud_user_de
    mMainDb.setUserName(mSvrUser);

    //Db_Cloud_Dev
    mMainDb.setPassword(mSvrPwd);

    bool ok = mMainDb.open();


    if(ok)
    {
        mQuery = new QSqlQuery(mMainDb);

        emit  WorkerRes(0 , "data base connect successfully!");
        return true;
    }else
    {
        qDebug()<<"data base connect fail";
        qDebug() << mMainDb.lastError();
        return false;
    }
}
*/
/*
void CThreadRemoteWorker::ValSendTest(unsigned short *pVal)
{

    qDebug()<<"CThreadRemoteWorker ValSendTest thread:"<<QThread::currentThread();

    if(pVal == NULL)
        return;

    if(mQuery == NULL)
        return ;

    mQuery->prepare("INSERT INTO dev_par_value (dpar_device_id, dpar_ch0,dpar_ch1,dpar_ch2,dpar_ch3,dpar_ch4,dpar_ch5,dpar_ch6,dpar_ch7) "
                  "VALUES (?,?,?,?,?,?,?,?,?)");

    mQuery->bindValue(0, mClientId);
    for(int mIdx = 1 ; mIdx < 9 ; mIdx++)
    {
        mQuery->bindValue(mIdx, pVal[mIdx - 1]);
    }

    if(! mQuery->exec())
        qDebug() <<  mQuery->lastError();

}
*/
/*
void CThreadRemoteWorker::keySendTest(unsigned short knew)
{

    qDebug()<<"CThreadRemoteWorker keySendTest thread:"<<QThread::currentThread();

    if(mQuery == NULL)
        return ;

    //query.prepare("INSERT INTO dev_par (dpar_device_id, dpar_ch0,dpar_ch1,dpar_ch2,dpar_ch3,dpar_ch4,dpar_ch5,dpar_ch6,dpar_ch7) "
    //             "VALUES (:dpar_device_id,:dpar_ch0,:dpar_ch1,:dpar_ch2,:dpar_ch3,:dpar_ch4,:dpar_ch5,:dpar_ch6,:dpar_ch7)");
    mQuery->prepare("INSERT INTO dev_par_key (dkey_device_id, dkey_key) "
                    "VALUES (:dkey_device_id,:dkey_key)");

    mQuery->bindValue(":dkey_device_id", mClientId);
    mQuery->bindValue(":dkey_key", knew);

    if(! mQuery->exec())
        qDebug() <<  mQuery->lastError();

}
*/

