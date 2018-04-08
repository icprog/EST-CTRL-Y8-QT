#include "net_server_base8.h"
#include "resource_manager.h"

CNetServerBase8::CNetServerBase8(QWidget *parent) :
    CNetServerBase(parent)
{
    setObjectName("CNetServerBase8");

    resize(SYS_WID(100),SYS_HEI(50));

    QFont font;
    font.setPixelSize(SYS_FONT(16));

    pbRemote = new CButtonStable(this);
    pbRemote->setGeometry(SYS_WID(0), SYS_HEI(0), SYS_WID(90), SYS_HEI(50));
    pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));
    pbRemote->setFont(font);

    QString mStr;
    mStr = QApplication::translate("CNetServerBase", "Remote:" );
    mStr += "\n";
    mStr += QApplication::translate("CNetServerBase", "Func:" );
    pbRemote->setText(mStr);

    connect(pbRemote,               SIGNAL(pressed()),this,SLOT(OnNetClientCtrl()));

    setVisible(false);
}
void CNetServerBase8::OnNetClientCtrl()
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
void CNetServerBase8::OnCtrlChange(int idxCur,int func)
{
    QString mStr,mInfo;

    if(idxCur < 0)
    {

        mStr = QApplication::translate("CNetServerBase", "Remote:" );
        mStr += "\n";
        mStr += QApplication::translate("CNetServerBase", "Func:" );
        mStr += QApplication::translate("CNetServerBase", "view" );

        pbRemote->setText(mStr);
        return;
    }

    pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));

    mStr = QApplication::translate("CNetServerBase", "Remote:" );
    mInfo.setNum(idxCur);
    mStr += mInfo;
    mStr += "\n";

    mStr +=  QApplication::translate("CNetServerBase", "Func:" );

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

    pbRemote->setText(mStr);


}
void CNetServerBase8::OnClientNumberChange(int mCount)
{

     qDebug() << "OnClientNumberChange mIdx ";

    if(mCount <= 0)
    {
        QString mStr;
        mStr = QApplication::translate("CNetServerBase", "Remote:" );
        mStr += "\n";
        mStr += QApplication::translate("CNetServerBase", "Func:" );

        pbRemote->setText(mStr);
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));

    }else
    {
        QString mStr;
        mStr = QApplication::translate("CNetServerBase", "Remote:" );
        mStr += "\n";
        mStr += QApplication::translate("CNetServerBase", "Func:" );
        mStr += QApplication::translate("CNetServerBase", "view" );

        pbRemote->setText(mStr);
        pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));

        this->show();
    }
}
