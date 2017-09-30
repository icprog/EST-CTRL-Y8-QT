#include "net_server_ndt8.h"

#include "resource_manager.h"

#include <QMessageBox>

CNetServerNdt8::CNetServerNdt8(QWidget *parent) :
    CNetServerBase8(parent)
{
    setObjectName("CNetServerNdt8");
    resize(SYS_WID(90),SYS_HEI(50));

    m_bSkipRunCheck = true;
}

void CNetServerNdt8::OnCtrlChange(int idxCur,int func)
{
    QString mStr,mInfo;

    if(idxCur < 0)
    {

        mStr = QApplication::translate("CNetServerBase", "Remote:" );
        mStr += "\n";
        pbRemote->setText(mStr);
        return;
    }

    mStr = QApplication::translate("CNetServerBase", "Remote:" );
    mStr += "\n";
    mInfo.setNum(idxCur);
    mStr += mInfo;
    pbRemote->setText(mStr);

    mStr = QApplication::translate("CNetServerBase", "Func:" );
    mStr += "\n";

    switch(func)
    {
    case CLIENT_FUNC_READ:
        mStr += QApplication::translate("CNetServerBase", "view" );
        break;
    case CLIENT_FUNC_RUN:
        mStr += QApplication::translate("CNetServerBase", "run" );
        break;
    case CLIENT_FUNC_SET:
        mStr += QApplication::translate("CNetServerBase", "conf" );
        break;
    }

}
void CNetServerNdt8::OnClientNumberChange(int mCount)
{

    if(mCount <= 0)
    {
        QString mStr;

        mStr = QApplication::translate("CNetServerBase", "Remote:" );
        mStr += "\n";
        mStr += QApplication::translate("CNetServerBase", "Func:" );
        pbRemote->setText(mStr);

    }else
    {
        this->show();
        QString mStr;
        mStr = QApplication::translate("CNetServerBase", "Remote:" );
        mStr += "\n";
        mStr += QApplication::translate("CNetServerBase", "Func:" );
        mStr += QApplication::translate("CNetServerBase", "run" );

        pbRemote->setText(mStr);
    }
}

void CNetServerNdt8::ProcessNetMessage(unsigned short * pCmdBuf)
{
    unsigned short m_buf[2];
    switch(pCmdBuf[CMD_FUNC_ADDR])
    {
    case CMD_FUNC_SMART:
        emit SmartChange(pCmdBuf[FUNC_WKEY_ADDR]);
        break;
    case CMD_FUNC_WKEY:
        m_buf[0] = 0;
        m_buf[1] = pCmdBuf[FUNC_WKEY_ADDR];
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,m_buf,2);

        break;
    case NET_CMD_KEY_PRESS:
        emit RemoteKeyPressed(pCmdBuf[FUNC_WKEY_ADDR]);
        RsMgr->g_filmBase->SetKeySound();
        break;
    case NET_CMD_KEY_RELEASE:
        emit RemoteKeyReleased(pCmdBuf[FUNC_WKEY_ADDR]);
        break;
    case NET_CMD_KEY_PAGE:
        emit RemotePageChange(pCmdBuf[FUNC_WKEY_ADDR]);
        RsMgr->g_filmBase->SetKeySound();
        break;
    case CMD_FUNC_COMMD:
        break;
    case CMD_FUNC_PARAM:
        break;
    case CMD_FUNC_MOTO:
        break;
    case CMD_FUNC_REBOOT:
        MySystem("reboot");
        break;
    case MSG_CTRL_HEARTBEAT:
        m_iHeartAckCounter++;
        m_iHeartAckChecker = m_iHeartAckCounter;
        break;
    default:
        break;
    }
}
