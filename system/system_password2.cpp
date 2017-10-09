#include "system_password2.h"
#include "resource_manager.h"

#include <QCryptographicHash>
#include <QSettings>
#include "qmath.h"

#define PWD_COMFIRM                 (1)      /*密码有效*/
#define PWD_INVALID                   (0)       /*密码无效*/
#define PWD_DATE_EARLY             (-1)     /*密码未开始使用*/
#define PWD_DATE_LATE               (-2)     /*密码已过期*/
#define PWD_FILTER_BLOCK         (-3)     /*密码已使用过*/
#define PWD_CONSOLE                 (-4)     /*进入控制台*/

CSystemPassword2::CSystemPassword2( QWidget* parent ):
    CSystemBase(parent)
{     

    memset(mStrMachineCode,0,MACHINE_CODE_LEN + 1);
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
    edpsw->installEventFilter(this);

    lbdyn = new QLabel(this);
    lbdyn->setGeometry(QRect(10, 220, 110, 45));
    lbdyn->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    lbdyn->setText(QApplication::translate("CSystemPassword", "Password:"));

    lbinfo = new QLabel(this);
    lbinfo->setGeometry(QRect(70, 280, 285, 32));
    lbinfo->setAlignment(Qt::AlignCenter);
    lbinfo->setStyleSheet("color : red");

    lbDateTime = new QLabel(this);
    lbDateTime->setGeometry(QRect(30, 70, 170, 64));
    lbDateTime->setFrameShape(QFrame::Box);
    lbDateTime->setLineWidth(2);

    lbVer = new QLabel(this);
    lbVer->setGeometry(QRect(30, 136, 170, 60));
    lbVer->setFrameShape(QFrame::Box);
    lbVer->setLineWidth(2);
    lbVer->setStyleSheet("color:yellow");

    btLock = new CButtonStable(this);
    btLock->setGeometry(QRect(500, 420, 80, 80));

    btGeneral = new CButtonStable(this);
    btGeneral->setGeometry(QRect(20, 420, 80, 80));

    btPswCheck = new CButtonStable(this);
    btPswCheck->setGeometry(QRect(425, 525, 120, 60));
    btPswCheck->setText(QApplication::translate("CSystemPassword", "OK"));
    btPswCheck->setAutoFillBackground(true);

    tmRefresh = new QTimer();

    btLock->setStyleSheet(g_skinBase->GetStyleMapStr("BASE_STR_PASSWORD"));
    btGeneral->setStyleSheet(g_skinBase->GetStyleMapStr("BASE_STR_GENERAL"));

    connect(tmRefresh,  SIGNAL(timeout()),this,SLOT(OnTimerFresh()));

    connect(btLock,     SIGNAL(pressed()),this,SLOT(OnPasswordCheck()));
    connect(btPswCheck,       SIGNAL(pressed()),this,SLOT(OnPasswordCheck()));
    connect(btnExit,    SIGNAL(pressed()),this,SLOT(OnPasswordPress()));
    connect(btGeneral,  SIGNAL(pressed()),this,SLOT(OnPasswordPress()));

    translateFontSize( this );

    setVisible(false);

    g_systemDb->m_bCanSaveDate = false;
    g_systemDb->m_bCanUpdate = false;

    //no password check.
    if(QFile::exists(QCoreApplication::applicationDirPath() + "/skip_password"))
    {
        m_bSkipPsdForm = true;
        g_systemDb->m_bCanSaveDate = true;
        g_systemDb->m_bCanUpdate = true;
    }

    GenerateMachCode();
}

void CSystemPassword2::GenerateMachCode()
{
    //generator mech code
    QDateTime mDt(QDate::currentDate(),QTime::currentTime());
    qint64 mTemp = mDt.toMSecsSinceEpoch();

    int mIdx = 0;
    while(mIdx < MACHINE_CODE_LEN)
    {
        mStrMachineCode[mIdx] = mTemp % 10;
        mTemp /= 10;

        if( mIdx == 0 && mStrMachineCode[mIdx] == 0 )
        {
            continue;
        }
        mStrMachineCode[mIdx++] += 0x30;
    }

    //check file exist
    QFile fileMechCode(QCoreApplication::applicationDirPath() +"/MachCode");

    //first time start up
    if(!fileMechCode.exists())
    {
        fileMechCode.open(QFile::WriteOnly);
        fileMechCode.write(mStrMachineCode,MACHINE_CODE_LEN);
        fileMechCode.flush();
        fileMechCode.close();

        QFile fileSkipPwd("/sdcard/home/fa/skip_password");
        fileSkipPwd.open(QFile::WriteOnly);
        fileSkipPwd.write(mStrMachineCode,MACHINE_CODE_LEN);
        fileSkipPwd.flush();
        fileSkipPwd.close();

        m_bSkipPsdForm = true;
        g_systemDb->m_bCanSaveDate = true;
        g_systemDb->m_bCanUpdate = true;
        return;
    }

    char mBufCode[9];

    //file exist,check code lenght and chars
    fileMechCode.open(QFile::ReadWrite);
    int mCodeLenTemp =  fileMechCode.read(mBufCode,MACHINE_CODE_LEN);

    //check machine code length
    if(mCodeLenTemp < MACHINE_CODE_LEN)
    {
        fileMechCode.reset();   //reset to file start.
        fileMechCode.write(mStrMachineCode,MACHINE_CODE_LEN);
        fileMechCode.flush();
        fileMechCode.close();
        return;
    }

    //check machine code numbers
    for(int mIdx = 0 ; mIdx  < MACHINE_CODE_LEN ; mIdx++)
    {
        if(mBufCode[mIdx] < '0' || mBufCode[mIdx] > '9')
        {
            fileMechCode.reset();
            fileMechCode.write(mStrMachineCode,MACHINE_CODE_LEN);
            fileMechCode.flush();
            fileMechCode.close();
            return;
        }
    }

    //use code of file
    memcpy(mStrMachineCode,mBufCode,MACHINE_CODE_LEN);
}

void CSystemPassword2::OnTimerFresh()
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
void CSystemPassword2::showEvent(QShowEvent *event)
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

    QString mStrVer = QApplication::translate("CSystemPassword", "Machine:") + mStrMachineCode;
    mStrVer.append('\n');
    mStrVer.append(QApplication::translate("CSystemPassword", "PSW VER:") + "0002");
    lbVer->setText(mStrVer);

    grabKeyboard();

    CSystemBase::showEvent(event);
}

void CSystemPassword2::hideEvent(QHideEvent *event)
{
    tmRefresh->stop();

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    releaseKeyboard();

    CSystemBase::hideEvent(event);
}

bool CSystemPassword2::eventFilter(QObject * watched, QEvent * event)
{
    if(event->type() ==  QEvent::MouseButtonPress)
    {
        if(watched == edpsw )
        {
            m_strKeyBuff = "";
            edpsw->setText(m_strKeyBuff);
        }
    }

    return QWidget::eventFilter(watched,event);
}
void CSystemPassword2::mousePressEvent(QMouseEvent */*event*/)
{
    qDebug()<<"CTitleBase::mousePressEvent";
}
void CSystemPassword2::keyPressEvent( QKeyEvent * event )
{
    int mKey = event->key();
    switch(mKey)
    {
    case  Qt::Key_Backspace:
        m_strKeyBuff.chop( 1);      //remove the last char of the string
        break;
    case Qt::Key_Escape:
        this->hide();
        emit ViewChange(VIEW_MAIN);
        return;
    case Qt::Key_Close:
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        OnPasswordCheck();
        break;
    default:
        if(m_strKeyBuff.length() < PASSWORD_MAX_LENGTH &&( (mKey >= Qt::Key_0 &&  mKey <= Qt::Key_9) || ( mKey >= Qt::Key_A  &&  mKey <= Qt::Key_Z)))
            m_strKeyBuff.append(event->text());

        break;
    }

    lbinfo->hide();
    edpsw->setText(m_strKeyBuff);

}
int CSystemPassword2::ConsoleCheck()
{
    //seperate information and check info
    QString strPwdFull;
    QByteArray pwdConsole;
    strPwdFull = edpsw->text();

    if(strPwdFull.length() != PASSWORD_MAX_LENGTH)
        return false;

    //get year month day
    int mYear,mMonth,mDay;
    mDay = QDate::currentDate().day();
    mMonth = QDate::currentDate().month();
    mYear =  QDate::currentDate().year() % 100;

    //get mach code
    char  mMachChar;
    pwdConsole.append(qFloor(mYear / 10) + 0x61);
    pwdConsole.append(qFloor(mYear % 10) + 0x61);
    pwdConsole.append(qFloor(mMonth / 10) + 0x61);
    pwdConsole.append(qFloor(mMonth % 10) + 0x61);
    pwdConsole.append(qFloor(mDay / 10) + 0x61);
    pwdConsole.append(qFloor(mDay % 10) + 0x61);

    mMachChar = g_dbsys.dbsystem.machine2[4];
    pwdConsole.append(qFloor(mMachChar - 0x30) + 0x41);
    mMachChar = g_dbsys.dbsystem.machine2[5];
    pwdConsole.append(qFloor(mMachChar - 0x30) + 0x41);
    mMachChar = g_dbsys.dbsystem.machine2[6];
    pwdConsole.append(qFloor(mMachChar - 0x30) + 0x41);
    mMachChar = g_dbsys.dbsystem.machine2[7];
    pwdConsole.append(qFloor(mMachChar - 0x30) + 0x41);

    //qDebug()<<"pwdConsole ="<<pwdConsole;
    //qDebug()<<"strPwdFull ="<<strPwdFull;

    if(pwdConsole == strPwdFull)
        return PWD_CONSOLE;

    return false;
}
void CSystemPassword2::OnPasswordCheck()
{

    if(PWD_CONSOLE == ConsoleCheck())
    {
        this->hide();
        emit ViewChange(VIEW_CONSOLE);
        return;
    }

    if(m_bSkipPsdForm)          //判断是否已经成功输入过密码
    {
        this->hide();           //判断成功
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        return;
    }

    int mPwdValue = calcPassword();

    if(PWD_COMFIRM == mPwdValue)
    {
        m_bSkipPsdForm = true;
        this->hide();           //判断成功
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
    }

    if(PWD_INVALID == mPwdValue)
    {
        lbinfo->setText(QApplication::translate("CSystemPassword", "Please input valid PWD!"));
        lbinfo->show();
        return;
    }

    if(PWD_DATE_EARLY == mPwdValue)
    {
        lbinfo->setText(QApplication::translate("CSystemPassword", "Password not enabled!"));
        lbinfo->show();
        return;
    }

    if(PWD_DATE_LATE == mPwdValue)
    {
        lbinfo->setText(QApplication::translate("CSystemPassword", "The password is out of date!"));
        lbinfo->show();
        return;
    }

    if(PWD_FILTER_BLOCK == mPwdValue)
    {
        lbinfo->setText(QApplication::translate("CSystemPassword", "Password has been used!"));
        lbinfo->show();
        return;
    }

    return;

}
void CSystemPassword2::OnPasswordPress()
{ 
    if(sender() == btnExit)
    {
        this->hide();
        emit ViewChange(VIEW_MAIN);
        return;
    }

    if(sender() == btGeneral)
    {
        //确实是否允许显示通用界面
        if(g_systemDb->getSystemCfg("PWD/GENERAL_SHOW"    ,true).toInt() == false)
            return;

        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemGeneral);
        return;
    }
} 

int CSystemPassword2::calcPassword()
{
    //get date number of today
    unsigned int mDateCur;
    QDate juianTest = QDate::currentDate();
    mDateCur =  juianTest.toJulianDay() % 1000;

    //seperate information and check info
    QString strPwdFull,strPwdDate,strPwdInstall,strPwdDateChange,strPwdRand,strPwdCheck;
    strPwdFull = edpsw->text();
    strPwdRand = strPwdFull.left(1);
    strPwdDate = strPwdFull.mid(1,3);
    strPwdCheck = strPwdFull.mid(4,2);
    strPwdInstall = strPwdFull.mid(6,1);
    strPwdDateChange = strPwdFull.right(1);

    //check the password length
    if(strPwdFull.length() < 8 )
        return false;

    //build information for check
    QByteArray arrCheckFull;
    arrCheckFull.append(strPwdDate).append(strPwdInstall).append(strPwdDateChange).append(strPwdRand).append(g_dbsys.dbsystem.machine2);

    //get check information
    QByteArray arrCheckRes;
    arrCheckRes = QCryptographicHash::hash(arrCheckFull,QCryptographicHash::Md5);

    //start position of used check byte
    int checkStartPos;
    checkStartPos =( unsigned char )arrCheckRes.at(0) % 15;

    //use 2 byte only
    quint32 decValue = ( unsigned char )arrCheckRes.at(checkStartPos);

    decValue %= 100;

    //check check
    if(strPwdCheck.toUInt() != decValue)
        return PWD_INVALID;

    if(strPwdDateChange.toUInt() >= 5)
        g_systemDb->m_bCanSaveDate = true;

    //if change date is enabled,disable time check
    if(!g_systemDb->m_bCanSaveDate)
    {
        //check time 1
        if(mDateCur < strPwdDate.toUInt())
            return PWD_DATE_EARLY;

        //check time 2
        if(mDateCur > strPwdDate.toUInt())
            return PWD_DATE_LATE;
    }else
    {
        if(PwdFiltered(strPwdFull))
            return PWD_FILTER_BLOCK;
    }

    //save password julian date
    g_systemDb->mDateJulian = strPwdDate.toUInt();

    if(strPwdInstall.toUInt() < 5)
        g_systemDb->m_bCanUpdate = true;

    return PWD_COMFIRM;
}

int CSystemPassword2::PwdFiltered(QString pwd)
{
    //    if (!g_dbsys.operationx.cState)     //only filter with period function
    //        return false;

    QSettings *filter = new QSettings("/sdcard/home/fa/pwdfilter.ini",QSettings::IniFormat);

    if(filter->allKeys().size() > 1000)      //if the filter size large than 1000,block all key with time change enable
        return true;

    if(filter->value("block/" + pwd ,0).toUInt() == 1)       //if the time change enable key has been recorded,block it.
        return true;
    else
        filter->setValue("block/" + pwd,1);                              //save the key to disk

    return false;
}
