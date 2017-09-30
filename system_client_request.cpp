#include "system_client_request.h"

#include "resource_manager.h"

CSystemClient::CSystemClient(QWidget *parent) :
    QWidget(parent)
{

    setObjectName("CSystemClient");

    resize(360, 220);

    lbClientIdx = new QLabel(this);
    lbClientIdx->setGeometry(QRect(190, 0, 70, 70));
    lbClientIdx->setStyleSheet(QString::fromUtf8("color: rgb(0, 85, 0);"));

    label = new QLabel(this);
    label->setGeometry(QRect(10, 70, 300, 40));
    label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
    label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    pbAccept = new QPushButton(this);
    pbAccept->setGeometry(QRect(200, 130, 110, 70));

    label_2 = new QLabel(this);
    label_2->setGeometry(QRect(10, 10, 160, 40));
    label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
    label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    pbReject = new QPushButton(this);
    pbReject->setObjectName(QString::fromUtf8("pbReject"));
    pbReject->setGeometry(QRect(50, 130, 110, 70));

    label->setText(QApplication::translate("CSystemClient", "Request control of this system"));
    pbAccept->setText(QApplication::translate("CSystemClient", "Accept"));
    label_2->setText(QApplication::translate("CSystemClient", "Client Index:"));
    pbReject->setText(QApplication::translate("CSystemClient", "Reject"));

    translateFontSize(this);

    timerClick = new QTimer(this);
    timerClick->setInterval(FUNC_WAIT_INTVERAL);

    connect(timerClick, SIGNAL(timeout()),this,SLOT(OnTimeOut()));
    connect(pbReject,   SIGNAL(pressed()),this,SLOT(OnButtonPressed()));
    connect(pbAccept,   SIGNAL(pressed()),this,SLOT(OnButtonPressed()));

    pbReject->setStyleSheet( g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));
    pbAccept->setStyleSheet( g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(128,127,216,235));
    setPalette(pal);

    m_bAutoAccept = false;

    //    QFile fileAccept;
    //    fileAccept.setFileName(QCoreApplication::applicationDirPath() + "/auto_accept");

    //    if(fileAccept.exists())
    //        m_bAutoAccept = true;

    if(QFile::exists(QCoreApplication::applicationDirPath() + "/auto_accept"))
        m_bAutoAccept = true;

    setVisible(false);
}

void CSystemClient::hideEvent(QHideEvent *)
{
    timerClick->stop();
    RsMgr->VisibleWidgetDel(this);
}
void CSystemClient::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    if(!g_netBase)
        return;

    timerClick->start();
    m_iSecondPassed = 0;
    lbClientIdx->setNum(g_netBase->GetPendingRequest());
    lbClientIdx->setStyleSheet("{color: red;}");
    pbAccept->setFocus();

    QString mStr,mText;
    mStr.sprintf("(%d)",FUNC_WAIT_TIME + 1);

    if(m_bAutoAccept)
    {
        mText = QApplication::translate("CSystemClient", "Accept" );
        mText.append(mStr);
        pbAccept->setText(mText);
    }else
    {
        mText = QApplication::translate("CSystemClient", "Reject" );
        mText.append(mStr);
        pbReject->setText(mText);
    }

}
void CSystemClient::OnButtonPressed()
{
    if(sender() ==  pbReject )
    {
        emit PopupHide(this);

        this->hide();
        emit ClientAck(CLIENT_ACK_REJECT);
        return;
    }

    if(sender() ==  pbAccept )
    {

        emit PopupHide(this);

        this->hide();
        emit ClientAck(CLIENT_ACK_ACCEPT);
        return;
    }
}
void CSystemClient::OnTimeOut()
{

    QString mStr,mText;
    mStr.sprintf("(%d)",FUNC_WAIT_TIME - m_iSecondPassed);

    if(m_bAutoAccept)
    {
        mText = QApplication::translate("CSystemClient", "Accept" );
        mText.append(mStr);
        pbAccept->setText(mText);
    }else
    {
        mText = QApplication::translate("CSystemClient", "Reject" );
        mText.append(mStr);
        pbReject->setText(mText);
    }

    if(m_iSecondPassed >= FUNC_WAIT_TIME)
    {

        timerClick->stop();

        emit PopupHide(this);
        this->hide();

        if(m_bAutoAccept)
            emit ClientAck(CLIENT_ACK_ACCEPT);
        else
            emit ClientAck(CLIENT_ACK_TIMEOUT);

        m_iSecondPassed = 0;

        return;
    }

    m_iSecondPassed++;
}
