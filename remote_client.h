#ifndef REMOTE_CLIENT_H
#define REMOTE_CLIENT_H
//#include <QSqlQuery>
//#include <QSqlDatabase>

#include "./base/remote_base.h"

#define UPDATE_STATE_CONNECT 0
#define UPDATE_STATE_ID      1
#define UPDATE_STATE_AGENY   2
#define UPDATE_STATE_ADDR    3
#define UPDATE_STATE_CONTACT 4
#define UPDATE_STATE_PHONE   5
#define UPDATE_STATE_MANAGER 6
#define UPDATE_STATE_ALIVE   7

#define TCP_SLAVE_CMD_SIZE  512


class CRemoteClient : public CRemoteBase
{
    Q_OBJECT
public:
    explicit CRemoteClient(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    unsigned short mBufSendToServer[TCP_SLAVE_CMD_SIZE];

    QTcpSocket *tcpClient;
    int m_iUpdateState;

    QString mStrServerAddr;
    QString mStrClientId;
    QString mStrClientAgency;
    QString mStrClientAddr;
    QString mStrClientContacts;
    QString mStrClientPhone;
    QString mStrClientManager;

    QTimer *m_timerConnect;         //用于通知服务器
    QTimer *m_timerBufferCheck;     //用于读取服务器消息

    void InitNetworkClient();

    int PutStrToBuf(QString &,unsigned short *);

    //QSqlDatabase mMainDb;
    //void DbInit();
private:
    QLabel * pLbServerAddr;         /*服务器地址*/
    QLabel * pLbClientId;           /*客户端ID*/
    QLabel * pLbOrganization;       /*客户单位*/
    QLabel * pLbAddress;            /*客户地址*/
    QLabel * pLbContacts;           /*客户联系人*/
    QLabel * pLbPhone;              /*客户联系电话*/
    QLabel * pLbManager;            /*客户经理*/
    QLabel * pLbState;              /*当前状态*/

    QLabel * strServerAddr;         /*服务器地址*/
    QLabel * strClientId;           /*客户端ID*/
    QLabel * strOrganization;       /*客户单位*/
    QLabel * strAddress;            /*客户地址*/
    QLabel * strContacts;           /*客户联系人*/
    QLabel * strPhone;              /*客户联系电话*/
    QLabel * strManager;            /*客户经理*/
    QLabel * strState;              /*当前状态*/

    QLabel * pLbMessage;            /*提示信息*/

    CButtonStable   * btnCheckNetWork;      /*检查网络设置*/
    CButtonStable   * btnUpdate;            /*更新客户端信息*/

private slots:
    void OnUpdateInfo();                /*按钮更新信息*/
    void DisplayInfo();                 /*显示信息*/

    void OnUpdateToServer();

private slots:
    void OnConnected();
    void OnClientDisconnected();
    void OnClientReadyRead();
};

#endif // REMOTE_CLIENT_H
