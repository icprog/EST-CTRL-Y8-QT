#include "net_server_base12.h"
#include "resource_manager.h"

CNetServer12::CNetServer12(QWidget *parent) :
    CNetServerBase(parent)
{
    setObjectName("CNetServer12");

    resize(SYS_WID(90),SYS_HEI(90));

    pbRemote = new CButtonStable(this);
    pbRemote->setGeometry(SYS_WID(0), SYS_HEI(6), SYS_WID(90), SYS_HEI(72));
    pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_DEFAULT"));

    connect(pbRemote,               SIGNAL(pressed()),this,SLOT(OnNetClientCtrl()));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
        //setStyleSheet("background-color:black");
    }else
    {
        //设置背景色
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(208,0,100));
        setPalette(pal);
    }

    setVisible(false);
}
void CNetServer12::OnNetClientCtrl()
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
void CNetServer12::OnCtrlChange(int /*idxCur*/,int func)
{

//    if(idxCur < 0)
//    {
//        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_DEFAULT"));
//        return;
//    }

    switch(func)
    {
    case CLIENT_FUNC_READ:
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_VIEW"));
        break;
    case CLIENT_FUNC_RUN:
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_CONTROL"));
        break;
    case CLIENT_FUNC_SET:
        pbRemote->setStyleSheet("");
        break;
    }

}
void CNetServer12::OnClientNumberChange(int mCount)
{


    if(mCount <= 0)
    {
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_DEFAULT"));

    }else
    {
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_NET_REMOTE_VIEW"));

        this->show();
    }
}
void CNetServer12::OnViewDirChange(int)
{
    //切换显示角度

}
