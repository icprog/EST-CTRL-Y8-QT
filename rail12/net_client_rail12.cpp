#include "net_client_base12.h"
#include "resource_manager.h"

CNetClient12::CNetClient12(QWidget *parent) :
    CNetClientBase(parent)
{
    setObjectName("CNetClient12");

    pbCtrlRequest = new CButtonStable(this);
    pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_DEFAULT"));

    connect(pbCtrlRequest,  SIGNAL(pressed()),this,SLOT(OnClientCtrlPressed()));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,0,100)");
    }

    OnViewDirChange(g_systemDb->g_startAngle);
}
void CNetClient12::OnClientReadyRead()
{
    QString mStrIdx,mStrInfo;

    if(tcpClient.state() != QAbstractSocket::ConnectedState)
        return;

    int mDatLen = tcpClient.read((char *)mTcpBufRead,PKG_DEFAULT_SIZE);

    if(mDatLen <PKG_DEFAULT_SIZE )
        return;

    switch(mTcpBufRead[CMD_FUNC_ADDR])
    {
    case CMD_FUNC_DEBUG:
        for(int i=0;i<20;i++)
        {
            g_systemDb->g_dbMachine.CurrentData[i]=mTcpBufRead[1 + i];
        }
        break;
    case CMD_FUNC_STATE:
        for(int i=0;i<8;i++)
        {
            g_systemDb->g_dbMachine.StateData[i]= mTcpBufRead[1 + i];
        }
        break;
    case MSG_CLIENT_IDX:
        emit PopupShow( SYS_POPUP_SIM_HIDE );
        m_iClientIdx = mTcpBufRead[1];
        mStrIdx.setNum(m_iClientIdx);
        mStrInfo += mStrIdx;
        m_iFunctionCurrent = mTcpBufRead[2];

        pbCtrlRequest->setText(mStrInfo);
        pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_VIEW"));

        mStrInfo = QApplication::translate("CNetClientBase","Connect to server successfully!");
        mStrInfo += "\n";
        mStrInfo += QApplication::translate("CNetClientBase","Client Index:");
        mStrInfo += mStrIdx.setNum(m_iClientIdx);
        mStrInfo += "\n";
        mStrInfo += QApplication::translate("CNetClientBase","Click the 'PAD' button to change working mode!");
        QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_REQUEST:
        m_iClientIdx = mTcpBufRead[1];
        mStrIdx.setNum(m_iClientIdx);
        mStrInfo += mStrIdx;
        m_iFunctionCurrent = mTcpBufRead[2];
        if(m_iFunctionCurrent == CLIENT_FUNC_READ)
        {
            pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_VIEW"));
        }else if(m_iFunctionCurrent == CLIENT_FUNC_RUN)
        {
            pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_CONTROL"));
        }else if(m_iFunctionCurrent == CLIENT_FUNC_SET)
        {
        }
        pbCtrlRequest->setText(mStrInfo);

        break;
    case MSG_CTRL_BUSY:
        mStrIdx.setNum(mTcpBufRead[3]);
        mStrInfo = "Server is controled by another controler！\n";
        mStrInfo += "Controler Index:";
        mStrInfo += mStrIdx;
        mStrInfo += "\n";
        mStrInfo += "Click 'Remote' button on the system can release current Controler!";

        QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;

    case MSG_CTRL_LIMIT:
        mStrInfo = "The server disable any remote!\n";
        mStrInfo += "Please tye remote control after open the remote control function!\n";
        mStrInfo += "Click the remote button on the machine can open remote control function!";
        QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_COLLISION:
        mStrInfo = QApplication::translate("CNetClientBase","The server is connecting!");
        mStrInfo += "\n";
        mStrInfo += QApplication::translate("CNetClientBase","Please wait for the end of current connecting!");;
        mStrInfo += "\n";
        QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_REJECT:
        mStrInfo = QApplication::translate("CNetClientBase","Your request was rejected!");
        mStrInfo += "\n";
        mStrInfo += QApplication::translate("CNetClientBase","OR the connection request timeout, please try again!");
        mStrInfo += "\n";
        QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;
    default:
        break;
    }

}

void CNetClient12::OnClientDisconnected()
{
    connectStatus = false;
    timerReconnect->start();

    pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_DEFAULT"));
}

void CNetClient12::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(90),SYS_WID(90));
        pbCtrlRequest->setGeometry(SYS_HEI(0), SYS_WID(6), SYS_HEI(90), SYS_WID(72));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(90),SYS_HEI(90));
        pbCtrlRequest->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(90),SYS_HEI(90));
        pbCtrlRequest->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }

}
void CNetClient12::OnReConnect()
{

    if(!connectStatus)
    {
        tcpClient.abort();
        tcpClient.connectToHost(m_IpAddr,TCP_SERVER_PORT);

        if(m_iTryTimes == 0)
            pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_TRY1"));

        if(m_iTryTimes == 1)
            pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_TRY2"));

        if(m_iTryTimes == 2)
            pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_DEFAULT"));

        if(++m_iTryTimes > 2)
            m_iTryTimes = 0;

        pbCtrlRequest->setText("");
    }else
    {
        timerReconnect->stop();
    }
}
