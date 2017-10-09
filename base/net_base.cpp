#include "net_base.h"
#include <QDebug>

CNetBase::CNetBase(QWidget *parent) :
    QWidget(parent)
{

}
void CNetBase::OnViewDirChange(int)
{
    //切换显示角度

}
void CNetBase::OnClientAck( int)
{
    //客戶端反馈消息
}
unsigned short * CNetBase::getBufWrite()
{
    return NULL;
}

void CNetBase::PublishMessage()
{
    //发送消息
}
void CNetBase::BroadcastMsg()
{
    //广播消息，服务端使用
}
unsigned short * CNetBase::getUdpBufferWrite()
{
    return NULL;
}

bool CNetBase::isConnected()
{
    return false;
}
int CNetBase::GetPendingRequest()
{
    return 0;
}
void CNetBase::mousePressEvent(QMouseEvent */*event*/)
{
    qDebug()<<"CNetBase::mousePressEvent";
}
