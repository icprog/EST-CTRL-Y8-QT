#ifndef GEN_CLIENT_H
#define GEN_CLIENT_H

#include <QWidget>
#include <QUdpSocket>
#include "system_defines.h"

// PACKET Frame
#define UDP_PACKET_SIZE			(14)	// UDP Packet Size : 14 byte
#define UDP_PACKET_HEADER1		0xF0	// UDP Header #1 : Fixed
#define UDP_PACKET_HEADER2		0x0A	// UDP Header #2 : Fixed
#define UDP_PACKET_TAIL			0x0F	// UDP Tail : Fixed
#define UDP_PACKET_FROM_SERVER	0x02	// 0x02 : from Server to Client
#define UDP_PACKET_FROM_CLIENT	0x01	// 0x01 : from Clinet to Server


class CGenClient : public QWidget
{
    Q_OBJECT
public:
    explicit CGenClient(QWidget *parent = 0);
    
private:
    QUdpSocket * m_GenUdpClient;
    unsigned char mUdpBufRead[UDP_PACKET_SIZE];

public:

    bool ServiceDataCheck(unsigned char* pData, int nSize);     //check data valid.

    void GenMsgNotify(int cmd,int val);             //

    bool SendCommand(int nCmd, char nD1, char nD2, char nD3, char nD4, char nD5, char nD6, char nD7, char nD8);

signals:
    void ParamChange(int type,int idx);     //发生器参数变化
    void GenTechChange(int tech);           //发生器技术切换信号
    void GenFocusChange(int focus);

    void ViewChange(int );                  //视图切换消息

public slots:
    void OnParamChange(int,int);            //传信号给发生器
    void OnGenFocusChange(int);
    void OnGenTechChange(int);
    void OnGenAecChange(int );

    void processPendingDatagrams();         //读取发生器过来的信号
};

#endif // GEN_CLIENT_H
