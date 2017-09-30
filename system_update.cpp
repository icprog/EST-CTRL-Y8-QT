#include "system_update.h"
#include "sys_database.h"
#include "resource_manager.h"

#define PROG_SEG_1 ( 6200 )
#define PROG_SEG_2 ( 1000 )
#define PROG_SEG_3 ( 1000 )

CSystemUpdate::CSystemUpdate( QWidget* parent):
    CSystemBase(parent)
{

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemUpdate", "System Program Upgrade"));

    TextLabel2 = new QLabel(this);
    TextLabel2->setGeometry(QRect(20, 290, 131, 32));
    TextLabel2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    TextLabel3 = new QLabel(this);
    TextLabel3->setGeometry(QRect(20, 390, 191, 32));
    TextLabel3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    TextLabel4 = new QLabel(this);
    TextLabel4->setGeometry(QRect(20, 55, 320, 32));
    TextLabel4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    edCmd = new QLabel(this);
    edCmd->setGeometry(QRect(240, 90, 120, 40));
    edCmd->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    edCmd->setStyleSheet("background-color : white ; color : darkRed");
    edCmd->setFrameShape(QFrame::Panel);
    edCmd->setLineWidth(2);

    TextLabel1 = new QLabel(this);
    TextLabel1->setGeometry(QRect(20, 190, 141, 32));
    TextLabel1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    TextLabel0 = new QLabel(this);
    TextLabel0->setGeometry(QRect(20, 90, 181, 35));

    ProgressCtrl = new QProgressBar(this);
    ProgressCtrl->setGeometry(QRect(190, 285, 230, 37));
    ProgressCtrl->setProperty("progress", QVariant(2));
    ProgressCtrl->setProperty("centerIndicator", QVariant(true));

    btUpdateControl = new CButtonStable(this);
    btUpdateControl->setGeometry(QRect(480, 280, 100, 50));
    btUpdateControl->setFocusPolicy(Qt::StrongFocus);

    btRestart = new CButtonStable(this);
    btRestart->setGeometry(QRect(480, 450, 100, 50));
    btRestart->setFocusPolicy(Qt::StrongFocus);

    btUpdateConsole = new CButtonStable(this);
    btUpdateConsole->setGeometry(QRect(480, 180, 100, 50));
    btUpdateConsole->setFocusPolicy(Qt::StrongFocus);

    btCalibration = new CButtonStable(this);
    btCalibration->setGeometry(QRect(480, 370, 100, 50));
    btCalibration->setFocusPolicy(Qt::StrongFocus);

    pixUSB = new QLabel(this);
    pixUSB->setGeometry(QRect(410, 460, 36, 36));
    pixUSB->setStyleSheet(g_skinBase->GetStyleMapStr("BASE_STR_USB"));

    frameLine0 = new QFrame(this);
    frameLine0->setGeometry(QRect(20, 150, 560, 10));
    frameLine0->setFrameShape(QFrame::HLine);
    frameLine0->setFrameShadow(QFrame::Sunken);

    frameLine1 = new QFrame(this);
    frameLine1->setGeometry(QRect(20, 250, 560, 10));
    frameLine1->setFrameShape(QFrame::HLine);
    frameLine1->setFrameShadow(QFrame::Sunken);

    frameLine2 = new QFrame(this);
    frameLine2->setGeometry(QRect(20, 350, 560, 10));
    frameLine2->setFrameShape(QFrame::HLine);
    frameLine2->setFrameShadow(QFrame::Sunken);

    strMessage = new QLabel(this);
    strMessage->setGeometry(QRect(0, 450, 471, 40));
    strMessage->setAlignment(Qt::AlignCenter);
    strMessage->setStyleSheet("color : red");

    ProgressConsole = new QProgressBar(this);
    ProgressConsole->setGeometry(QRect(190, 185, 230, 37));
    ProgressConsole->setProperty("progress", QVariant(2));
    ProgressConsole->setProperty("centerIndicator", QVariant(true));

    TextLabel2->setText(QApplication::translate("CSystemUpdate", "Control System:" ));
    TextLabel3->setText(QApplication::translate("CSystemUpdate", "Touch screen calibration:" ));
    TextLabel1->setText(QApplication::translate("CSystemUpdate", "Console program:" ));
    TextLabel0->setText(QApplication::translate("CSystemUpdate", "Version Select Code:" ));
    btUpdateControl->setText(QApplication::translate("CSystemUpdate", "Update" ));
    btRestart->setText(QApplication::translate("CSystemUpdate", "Restart" ));
    btUpdateConsole->setText(QApplication::translate("CSystemUpdate", "Update" ));
    btCalibration->setText(QApplication::translate("CSystemUpdate", "Calibration" ));
    strMessage->setText(QApplication::translate("CSystemUpdate", "messages." ));

    edCmd->installEventFilter(this);

    connect(btUpdateConsole, SIGNAL(pressed()),this,SLOT(OnButtonConsole()));
    connect(btUpdateControl, SIGNAL(pressed()),this,SLOT(OnButtonControl()));
    connect(btCalibration, SIGNAL(pressed()),this,SLOT(OnButtonUpdate()));
    connect(btRestart, SIGNAL(pressed()),this,SLOT(OnButtonUpdate()));
    connect(btnExit, SIGNAL(pressed()),this,SLOT(OnButtonUpdate()));

    strMessage->setText("");
    btRestart->hide();
    edCmd->setText("");
    pixUSB->raise();

    m_DelayCounter = 0;
    timerUpdate = new QTimer();
    connect(timerUpdate,SIGNAL(timeout()),this,SLOT(OnTimerProgram()));

    timerCounter = new QTimer(this);
    timerCounter->setInterval(1000);
    connect(timerCounter,SIGNAL(timeout()),this,SLOT(OnCounterUpdate()));

    translateFontSize( this );
    setVisible(false);
}


void CSystemUpdate::showEvent(QShowEvent *)
{

    TextLabel4->setText(QApplication::translate("CSystemUpdate", "Current Control Board Version:" ) + "   " + g_dbsys.firmVersion);

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad = new CSystemImepad(this);
    Q_ASSERT(g_systemPad != 0);

    bSending = false;

    ProgressCtrl->reset();

    strMessage->setText("");
    btRestart->hide();

    edCmd->setText("");

    timerUpdate->start(30);        //30ms经过计算测试，如果时间太短，则可能会更新失败
    //时间太长，则更新速度慢

    grabKeyboard();
}

void CSystemUpdate::hideEvent(QHideEvent *)
{
    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    timerUpdate->stop();
    timerCounter->stop();

    if(mfileNewCode.isOpen())
        mfileNewCode.close();

    RsMgr->VisibleWidgetDel(this);

    releaseKeyboard();
}

void CSystemUpdate::OnCounterUpdate()
{
    nSeconds += 2;

    if(nSeconds > 98)
        nSeconds = 99;

    ProgressConsole->setValue(nSeconds);
}


void CSystemUpdate::OnButtonConsole()
{
    if(!g_systemDb->m_bCanUpdate)
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "Upgrade feature is not enabled!"));
        return;
    }

    if(g_systemPad)
        g_systemPad->hide();

    if (check_sda())
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "U Disk Not Exist!"));
        return ;
    }else
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "U Disk Fond."));
        strMessage->repaint();
        QApplication::processEvents();
    }

    //get system information and figure out the platform,set different for different update path
    QProcess proVersion;

    proVersion.start("cat /proc/version");
    proVersion.waitForFinished();

    QByteArray byteRead;
    byteRead = proVersion.readAll();
    QString mStrFilePath;

    if(byteRead.indexOf("FriendlyARM",0) != -1)
    {
        mStrFilePath = "/udisk/estmedcarefirmware/hmx";
        qDebug() << "FriendlyARM 6410";
    }else  if(byteRead.indexOf("EmbedSky",0) != -1)
    {
        mStrFilePath = "/udisk/estmedcarefirmv200/psx";
        qDebug() << "EmbedSky 3358";
    } else
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "Ubuntu system!"));
        qDebug() << "Ubuntu x86";
        return;
    }

    if(edCmd->text().isEmpty())
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "Code Invalid!"));
        return;
    }

    mStrFilePath += edCmd->text();

    if (! QFile::exists(mStrFilePath))
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "No File in U Disk!"));
        return ;
    }else
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "File in U Disk.."));
        strMessage->repaint();
        QApplication::processEvents();
    }

    nSeconds = 0;
    ProgressConsole->setMaximum(100);
    timerCounter->start();

    QProcess * mPro = new QProcess(this);
    connect(mPro,SIGNAL(error(QProcess::ProcessError)), this,SLOT(OnUpdateError( QProcess::ProcessError )));
    connect(mPro,SIGNAL(finished(int, QProcess::ExitStatus)), this,SLOT(OnUpdateFinished(int , QProcess::ExitStatus)));

    strMessage->setText(QApplication::translate("CSystemUpdate", "Update,please wait..."));
    strMessage->repaint();
    QApplication::processEvents();

    btUpdateConsole->setEnabled(false);
    btUpdateControl->setEnabled(false);
    btCalibration->setEnabled(false);

    mPro->start(mStrFilePath);

}
void CSystemUpdate::OnUpdateError ( QProcess::ProcessError  error)
{
    switch (error) {
    case QProcess::FailedToStart:
        strMessage->setText(QApplication::translate("CSystemUpdate", "Console Update Error!") + "::FailedToStart");
        break;
    case QProcess::Crashed:
        strMessage->setText(QApplication::translate("CSystemUpdate", "Console Update Error!") + "::Crashed");
        break;
    case QProcess::Timedout:
        strMessage->setText(QApplication::translate("CSystemUpdate", "Console Update Error!") + "::Timedout");
        break;
    case QProcess::WriteError:
        strMessage->setText(QApplication::translate("CSystemUpdate", "Console Update Error!") + "::WriteError");
        break;
    case QProcess::ReadError:
        strMessage->setText(QApplication::translate("CSystemUpdate", "Console Update Error!") + "::ReadError");
        break;
    case QProcess::UnknownError:
        strMessage->setText(QApplication::translate("CSystemUpdate", "Console Update Error!") + "::UnknownError");
        break;
    default:
        strMessage->setText(QApplication::translate("CSystemUpdate", "Console Update Error!"));
        break;
    }

    timerCounter->stop();
}
void CSystemUpdate::OnUpdateFinished ( int exitCode, QProcess::ExitStatus )
{

    btUpdateConsole->setEnabled(true);
    btUpdateControl->setEnabled(true);
    btCalibration->setEnabled(true);

    timerCounter->stop();

    if (exitCode >= 0)
    {
        ProgressConsole->setValue(100);
        btRestart->show();
        btRestart->setFocus();
        strMessage->setText(QApplication::translate("CSystemUpdate", "Please Restart Panel"));
    }else
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "No File in U Disk!"));
        return;
    }

}
void CSystemUpdate::OnButtonControl()
{
    if(!g_systemDb->m_bCanUpdate)
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "Upgrade feature is not enabled!"));
        return;
    }

    if(g_systemPad)
        g_systemPad->hide();

    if ( bSending )
    {
        SendCancel();
        ProgressCtrl->reset();
        return ;
    }

    strMessage->setText("");
    if (check_sda())
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "U Disk Not Exist!"));
        return ;
    }

    QString mStrFilePath;
    mStrFilePath.sprintf("/udisk/estmedcarefirmware/%s/mainest/main-%04d%04d%04d.bin",edCmd->text().toLocal8Bit().data(),PROG_SEG_1,PROG_SEG_2,PROG_SEG_3);
    if (! QFile::exists( mStrFilePath ))
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "No File in U Disk!"));
        return ;
    }

    bSending    = true;
    bComm       = true;
    nCounters   = g_nCounter;
    nSeconds    = 0;

    if(mfileNewCode.isOpen())
    {
        mfileNewCode.close();
    }

    mfileNewCode.setFileName(mStrFilePath);
    mfileNewCode.open( QIODevice::ReadOnly );

    mfileLenght = (mfileNewCode.size()+1)/2;
    ProgressCtrl->setMaximum( (mfileLenght+127)/128);

    g_systemDb->packno = 0;
    g_systemDb->g_nPrgPack = 0;

    if( !g_systemDb->g_bNoApp)
        g_taskComCtrl->CreateTask(CMD_FUNC_REBOOT,0,0);

}
void CSystemUpdate::OnTimerProgram()
{
    if (check_sda())
        pixUSB->hide();
    else
        pixUSB->show();

    if ( ! bSending )
        return;

    if (g_systemDb->g_nPrgPack != g_systemDb->packno)
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "Wait for controler ack!"));

        if(++m_DelayCounter < 20)
            return;
        else
            m_DelayCounter = 0;
    }else
    {
        strMessage->setText(QApplication::translate("CSystemUpdate", "Upgrading!Keep power on!"));
    }

    ProgressCtrl->setValue(g_systemDb->packno & 0x7FFF);

    if (mfileLenght == 0)
    {
        SendCancel();
        strMessage->setText(QApplication::translate("CSystemUpdate", "Update Main Successfully"));
        g_systemDb->g_bNoApp = false;

        return;
    }

    if (mfileLenght > 128)
    {
        g_systemDb->packLen = 128;
    }else
    {
        g_systemDb->packLen = mfileLenght;
        g_systemDb->packno |= 0x8000;
    }

    if (g_systemDb->g_nPrgPack == g_systemDb->packno)
    {
        mfileLenght -= g_systemDb->packLen;

        mfileNewCode.read((char*)g_systemDb->g_wPrgBuf,g_systemDb->packLen * 2);
        ++g_systemDb->packno;
    }

    if(bComm)
    {
        g_taskComCtrl->CreateTask(COMM_TX_MAINPRG,0, g_systemDb->packLen) ;
    }else
    {
        g_taskCan->Create_TaskCan(CAN_TX_MAINPRG,0,g_systemDb->packno,g_systemDb->packLen);
    }
}

void CSystemUpdate::OnButtonUpdate()
{
    if(sender() == btCalibration)
    {
        RsMgr->g_filmBase->SetLCD(false);

        RsMgr->g_filmBase->SetLCD(false);
        MySystem("rm /etc/pointercal");
        MySystem("reboot");
    }

    if(sender() == btnExit)
    {
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        this->hide();
    }

    if(sender() == btRestart)
    {
        RsMgr->g_filmBase->SetLCD(false);
        MySystem("reboot");
    }
}
bool CSystemUpdate::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==edCmd)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            edCmd->setText("");
            strMessage->setText("");

            g_systemPad->move(180,150);
            g_systemPad->show();

            m_strKeyBuff = "";
        }
    }

    return QWidget::eventFilter(watched,event);
}

void CSystemUpdate::SendCancel()
{

    bSending = false;
    g_systemDb->packno = 0;
    g_systemDb->g_nPrgPack = 0;
    mfileNewCode.close();

    timerUpdate->stop();
}

void CSystemUpdate::keyPressEvent( QKeyEvent * event )
{

    int mKey = event->key();
    switch (mKey) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        break;

    case Qt::Key_Backspace:
        m_strKeyBuff.chop( 1);
        break;
    case Qt::Key_Close:
        break;
    case Qt::Key_Escape:
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        break;
    case Qt::Key_Tab:
        break;
    default:
        if(m_strKeyBuff.length() < VERSION_MAX_LENGTH &&( (mKey >= Qt::Key_0 &&  mKey <= Qt::Key_9) || ( mKey >= Qt::Key_A  &&  mKey <= Qt::Key_Z)))
            m_strKeyBuff.append(event->key());
        break;
    }

    edCmd->setText(m_strKeyBuff);
}

int CSystemUpdate::check_sda()
{
    QFile fileTest;
    fileTest.setFileName("/dev/sda");

    if (fileTest.exists())
        return 0;
    else
        return 1;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
