#ifndef SYSTEM_NETWORK_H
#define SYSTEM_NETWORK_H

#include "system_base.h"
#include <QHostInfo>
#include <QProcess>
#include <QHostAddress>
#include <QNetworkInterface>


#define NET_EDIT_MAX    (4)
#define NET_EDIT_IP     (0)
#define NET_EDIT_MASK   (1)
#define NET_EDIT_GATE   (2)
#define NET_EDIT_DNS    (3)

class CSystemNetWork : public CSystemBase
{
    Q_OBJECT
public:
    explicit CSystemNetWork(QWidget *parent = 0);
    

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:
    void getNetWorkCfg();           //读取IP地址等配置

    void FlushNetWorkCfg();         //刷新当前网络配置，将参数信息告诉系统


    void IPAdressPatch(QString &);  //IP 地址补足15位，用于显示
    int IPAdressFormat(QString &);  //将IP地址中多余的0去掉，用于参数设置或保存

    QString m_strIp;
    QString m_strMask;
    QString m_strGate;
    QString m_strDNS;
    QString m_strMAC;

    QProcess * ping;

    QNetworkAddressEntry entryWlan0;
    QNetworkAddressEntry entryEth0;

    void DisplayNetInfoWlan0();
    void DisplayNetInfoEth0();
private:

    QLabel * strNetMode;
    CButtonStable *btNetEth0;           //dhcp mode
    CButtonStable *btNetWlan0;          //static mode
    CButtonStable *btNetRemote0;        //static mode

    QLabel * strWorkMode;
    CButtonStable *btNetModeClient;     //work as client,control via net work
    CButtonStable *btNetModeServer;     //work as server,control via com232

    QLabel * strIpAddr;
    QLabel * strNetMask;
    QLabel * strGate;
    QLabel * strDns;

    QLabel * editNet[NET_EDIT_MAX];

    QLabel * strMsgNotify;              // notify message
    CButtonStable *btTestGate;          //test gate
    CButtonStable *btTestInternet;      //test internet

    CButtonStable *btNetSave;           //test internet

    QTimer * timerInternetTest;         //internet test timer
    QTimer * timerGateTest;             //internet test timer
    int m_iTestState;
    int m_iTestWait;
    int m_iTestCount;

signals:
    
private slots:
    void OnBtnNetSave();

    void OnNetWorkPressed();
    void OnNetWorkExit();

    void OnTimerInternetTest();             //internet test
    void OnTimerGateTest();             //internet test

    void OnBtnInternetTest();               //internet test
    void OnBtnGateTest();                   //internet test
    void lookedUp(const QHostInfo &host);   //internet test return

    void OnModeLan();
    void OnModeWifi();
    void OnModeRemote();
public slots:
    bool eventFilter(QObject *, QEvent *);
};

#endif // SYSTEM_NETWORK_H
