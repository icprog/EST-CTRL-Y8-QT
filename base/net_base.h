#ifndef NET_BASE_H
#define NET_BASE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

class CNetBase : public QWidget
{
    Q_OBJECT
public:
    explicit CNetBase(QWidget *parent = 0);

    virtual void BroadcastMsg();            //广播消息，向遥控端
    virtual void PublishMessage();
    virtual unsigned short * getBufWrite();
    virtual unsigned short * getUdpBufferWrite();
    virtual bool isConnected();
    virtual int GetPendingRequest();

protected:
    void mousePressEvent(QMouseEvent *event);

    QFrame          * mFrame;
    QGraphicsScene  * mScene;
    QGraphicsView   * mView;

signals:
    void PopupShow(int);
    void InfoMsgCtrl(int , int,void * param = 0);
    void SmartChange(int);
    void RemoteKeyPressed(int);                //客户端按钮按下消息
    void RemoteKeyReleased(int);                //客户端按钮抬起消息
    void RemotePageChange(int);

public slots:
    virtual void OnViewDirChange(int);
    virtual void OnClientAck( int);
};

#endif // NET_BASE_H
