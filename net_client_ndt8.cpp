#include "net_client_ndt8.h"
#include "resource_manager.h"

CNetClientNdt8::CNetClientNdt8(QWidget *parent) :
    CNetClient8(parent)
{
    setObjectName("CNetClientNdt8");

}
void CNetClientNdt8::OnClientReadyRead()
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
        m_iClientIdx = mTcpBufRead[1];
        mStrIdx.setNum(m_iClientIdx);
        mStrInfo = QApplication::translate("CNetClientBase","Index:");
        mStrInfo += mStrIdx;
        mStrInfo += "\n";
        m_iFunctionCurrent = mTcpBufRead[2];

        mStrIdx = "Mode:Run";

        mStrInfo += QApplication::translate("CNetClientBase",mStrIdx.toUtf8() );
        pbCtrlRequest->setText(mStrInfo);
        pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));

        mStrInfo = QApplication::translate("CNetClientBase","Connect to server successfully!");
        mStrInfo += "\n";
        mStrInfo += QApplication::translate("CNetClientBase","Client Index:");
        mStrInfo += mStrIdx.setNum(m_iClientIdx);
        mStrInfo += "\n";
        mStrInfo += QApplication::translate("CNetClientBase","Click the 'Mode' button to change working mode!");

        //QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_REQUEST:
        m_iClientIdx = mTcpBufRead[1];
        mStrIdx.setNum(m_iClientIdx);
        mStrInfo = QApplication::translate("CNetClientBase","Index:");
        mStrInfo += mStrIdx;
        mStrInfo += "\n";
        m_iFunctionCurrent = mTcpBufRead[2];
        if(m_iFunctionCurrent == CLIENT_FUNC_READ)
        {
            mStrInfo += QApplication::translate("CNetClientBase","Mode:View");
        }else if(m_iFunctionCurrent == CLIENT_FUNC_RUN)
        {
            mStrInfo +=  QApplication::translate("CNetClientBase","Mode:Run");
        }else if(m_iFunctionCurrent == CLIENT_FUNC_SET)
        {
            mStrInfo += QApplication::translate("CNetClientBase","Mode:Set");;
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

        //QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;

    case MSG_CTRL_LIMIT:
        mStrInfo = "The server disable any remote!\n";
        mStrInfo += "Please tye remote control after open the remote control function!\n";
        mStrInfo += "Click the remote button on the machine can open remote control function!";
        // QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_COLLISION:
        mStrInfo = QApplication::translate("CNetClientBase","The server is connecting!");
        mStrInfo += "\n";
        mStrInfo += QApplication::translate("CNetClientBase","Please wait for the end of current connecting!");;
        mStrInfo += "\n";
        // QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;
    case MSG_CTRL_REJECT:
        mStrInfo = QApplication::translate("CNetClientBase","Your request was rejected!");
        mStrInfo += "\n";
        mStrInfo += QApplication::translate("CNetClientBase","OR the connection request timeout, please try again!");
        mStrInfo += "\n";
        // QMessageBox::information(0,QApplication::translate("CNetClientBase","System Information!"),mStrInfo,QMessageBox::Yes);
        break;
    default:
        break;
    }

}
