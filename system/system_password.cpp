#include "system_password.h"
#include "resource_manager.h"

CSystemPassword::CSystemPassword( QWidget* parent ):
    CSystemBase(parent)
{     

    setObjectName("CSystemPassword");

    resize(600,600);

    m_bSkipPsdForm = false;  //set false to enable password
    textTitle->setText(QApplication::translate("CSystemPassword", "Password Input"));

    edpsw = new QLabel(this);
    edpsw->setGeometry(QRect(140, 220, 172, 45));
    edpsw->setAlignment(Qt::AlignCenter);
    edpsw->setStyleSheet("color : blue ; background-color : white");
    edpsw->setFrameShape(QFrame::Panel);
    edpsw->setLineWidth(2);

    lbdyn = new QLabel(this);
    lbdyn->setGeometry(QRect(10, 220, 110, 45));
    lbdyn->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    lbdyn->setText(QApplication::translate("CSystemPassword", "Password:"));

    lbinfo = new QLabel(this);
    lbinfo->setGeometry(QRect(70, 280, 285, 32));
    lbinfo->setAlignment(Qt::AlignCenter);
    lbinfo->setStyleSheet("color : red");

    lbDateTime = new QLabel(this);
    lbDateTime->setGeometry(QRect(30, 70, 150, 64));
    lbDateTime->setFrameShape(QFrame::Box);
    lbDateTime->setLineWidth(2);

    btLock = new CButtonStable(this);
    btLock->setGeometry(QRect(500, 420, 80, 80));

    btGeneral = new CButtonStable(this);
    btGeneral->setGeometry(QRect(20, 420, 80, 80));

    btOk = new CButtonStable(this);
    btOk->setGeometry(QRect(425, 525, 120, 60));
    btOk->setText(QApplication::translate("CSystemPassword", "OK"));

    tmRefresh = new QTimer();

    btLock->setStyleSheet(g_skinBase->GetStyleMapStr("BASE_STR_PASSWORD"));
    btGeneral->setStyleSheet(g_skinBase->GetStyleMapStr("BASE_STR_GENERAL"));

    connect(tmRefresh,  SIGNAL(timeout()),this,SLOT(OnTimerFresh()));

    connect(btLock,     SIGNAL(pressed()),this,SLOT(OnPasswordCheck()));
    connect(btOk,       SIGNAL(pressed()),this,SLOT(OnPasswordCheck()));
    connect(btnExit,    SIGNAL(pressed()),this,SLOT(OnPasswordPress()));
    connect(btGeneral,  SIGNAL(pressed()),this,SLOT(OnPasswordPress()));

    translateFontSize( this );

    setVisible(false);

    //no password check.
    if(QFile::exists(QCoreApplication::applicationDirPath() + "/skip_password"))
        m_bSkipPsdForm = true;
}

void CSystemPassword::OnTimerFresh()
{
    QString strDate,strTime;

    QTime ts = QTime::currentTime();
    QDate dt = QDate::currentDate();

    strDate.sprintf("%02d.%02d.%02d",dt.year(),dt.month(),dt.day());
    strTime.sprintf("%02d:%02d:%02d",ts.hour(),ts.minute(),ts.second());

    strDate.append("\n");
    strDate.append(strTime);

    lbDateTime->setText(strDate);
}
void CSystemPassword::showEvent(QShowEvent *event)
{
    if (g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad = new CSystemImepad(this,0);

    g_systemPad->move(350,100);                                                //键盘显示位置
    g_systemPad->show();

    edpsw->setText("");
    m_strKeyBuff = "";

    lbinfo->hide();

    tmRefresh->start(TIME_SCREEN_FRESH);

    CSystemBase::showEvent(event);
}

void CSystemPassword::hideEvent(QHideEvent *event)
{
    tmRefresh->stop();

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    CSystemBase::hideEvent(event);
}

void CSystemPassword::keyPressEvent( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Backspace)                                                              //判断是否是退格键
    {
        int iStrLen = m_strKeyBuff.length();
        if(iStrLen > 0)
        {
            m_strKeyBuff.remove( iStrLen - 1,1);
        }
    }else if(event->key() == Qt::Key_Close)
    {
        return;
    }else
    {
        if(m_strKeyBuff.length() < PASSWORD_MAX_LENGTH)
            m_strKeyBuff.append(event->key());
    }

    lbinfo->hide();
    edpsw->setText(m_strKeyBuff);
}

void CSystemPassword::OnPasswordCheck()
{
    if(m_bSkipPsdForm)          //判断是否已经成功输入过密码
    {
        this->hide();           //判断成功
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        return;
    }

    QDate qd;                   //判断密码是否有效
    unsigned short dy;

    qd = QDate::currentDate();
    dy = qd.month() + qd.year() + qd.day();

    if(G_PasswordPeriods[ dy%50 ] == edpsw->text().toLong())
    {
        m_bSkipPsdForm = true;
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        return;
    }

    if(sender() == btOk)
    {
        lbinfo->setText(QApplication::translate("CSystemPassword", "The Password is Wrong!"));
        lbinfo->show();
        return;
    }

    if(sender() == btLock)
    {
        lbinfo->setText(QApplication::translate("CSystemPassword", "Please input valid PWD!"));
        lbinfo->show();
        return;
    }

}
void CSystemPassword::OnPasswordPress()
{ 
    if(sender() == btnExit)
    {
        this->hide();
        emit ViewChange(VIEW_MAIN);
        return;
    }

    if(sender() == btGeneral)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemGeneral);
        return;
    }
} 
