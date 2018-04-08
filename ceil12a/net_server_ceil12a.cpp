#include "net_server_rail12a.h"

#ifdef USE_CEIL_12_A


CNetServerCeil12a::CNetServerCeil12a(QWidget *parent) :
    CNetServer12(parent)
{
    setObjectName("CNetServerCeil12a");

    m_iDisplayText = g_sysDb->value("CNetServerCeil12a/DisplayText",false).toInt();

    pRectNetWid.append(g_sysDb->value("CNetServerCeil12a/VDIR_NORMAL"  ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(90), SYS_WID(90))).toRect());
    pRectNetWid.append(g_sysDb->value("CNetServerCeil12a/VDIR_LEFT"    ,QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(90))).toRect());
    pRectNetWid.append(g_sysDb->value("CNetServerCeil12a/VDIR_RIGHT"   ,QRect(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(90))).toRect());
    pRectNetWid.append(g_sysDb->value("CNetServerCeil12a/VDIR_REVERSE" ,QRect(SYS_HEI(0), SYS_WID(0), SYS_HEI(90), SYS_WID(90))).toRect());

    pRectNetBtn.append(g_sysDb->value("CNetServerCeil12a/VDIR_NORMAL/ICON"  ,QRect(SYS_HEI(0), SYS_WID(6), SYS_HEI(90), SYS_WID(72))).toRect());
    pRectNetBtn.append(g_sysDb->value("CNetServerCeil12a/VDIR_LEFT/ICON"    ,QRect(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72))).toRect());
    pRectNetBtn.append(g_sysDb->value("CNetServerCeil12a/VDIR_RIGHT/ICON"   ,QRect(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72))).toRect());
    pRectNetBtn.append(g_sysDb->value("CNetServerCeil12a/VDIR_REVERSE/ICON" ,QRect(SYS_HEI(0), SYS_WID(6), SYS_HEI(90), SYS_WID(72))).toRect());

    OnViewDirChange(g_sysDb->g_startAngle);
}
void CNetServerCeil12a::OnNetClientCtrl()
{

    if(sender() ==  pbRemote)
    {
        if(m_iCurrentControl >= 0)
        {
            mTcpBufWrite[0] = MSG_CTRL_REQUEST;
            mTcpBufWrite[1] = m_iCurrentControl;
            mTcpBufWrite[2] = CLIENT_FUNC_READ;

            clientFunctionArray[m_iCurrentControl] = CLIENT_FUNC_READ;
            SendMessage(m_iCurrentControl);

            m_iCurrentControl = -1;
            OnCtrlChange(-1,CLIENT_FUNC_READ);
        }
        return;
    }
}
void CNetServerCeil12a::OnCtrlChange(int /*idxCur*/,int func)
{

//    if(idxCur < 0)
//    {
//        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("NET_CLIENT_REMOTE_DEFAULT"));
//        return;
//    }

    switch(func)
    {
    case CLIENT_FUNC_READ:
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("NET_REMOTE_VIEW"));
        break;
    case CLIENT_FUNC_RUN:
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("NET_REMOTE_CONTROL"));
        break;
    case CLIENT_FUNC_SET:
        pbRemote->setStyleSheet("");
        break;
    }

}
/*
void CNetServerCeil12a::OnClientNumberChange(int mCount)
{


    if(mCount <= 0)
    {
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("NET_CLIENT_REMOTE_DEFAULT"));

    }else
    {
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("NET_REMOTE_VIEW"));

        this->show();
    }
}
*/


#endif
