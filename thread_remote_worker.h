#ifndef CTHREADREMOTE_H
#define CTHREADREMOTE_H

#include <QObject>
//#include <QSqlQuery>
//#include <QSqlDatabase>
//#include <QSqlDriver>
//#include <QSqlError>

//init sql database
//send data to sql server
//report result

class CThreadRemoteWorker : public QObject
{
    Q_OBJECT
public:
    explicit CThreadRemoteWorker(QObject *parent = 0);

private:
    //QSqlDatabase mMainDb;
    //QSqlQuery *mQuery;

    QString mServerAddr;
    int mServerPort;
    QString mSvrDb;
    QString mSvrUser;
    QString mSvrPwd;
    QString mClientId;

    bool mKeyValid;
    unsigned short mKey;


public slots:
    //void keySendTest(unsigned short);
    //void ValSendTest(unsigned short*);
    //bool SqlDbInit();

signals:
    void WorkerRes(int , const QString &);
};

#endif // CTHREADREMOTE_H
