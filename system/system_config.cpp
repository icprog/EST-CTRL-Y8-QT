#include <sys/time.h>

#include "resource_manager.h"
#include "sys_database.h"
#include "system_config.h"

CSystemConfig::CSystemConfig( QWidget* parent):
    CSystemBase(parent)
{
    setObjectName("CSystemConfig");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemConfig", "System Configuration"));

    btSaveDate = new CButtonStable(this);
    btSaveDate->setGeometry(QRect(480, 90, 100, 60));
    btSaveDate->setText(QApplication::translate("CSystemConfig", "SAVE" ));

    btLang[_ENGLISH] = new CButtonStable(this);
    btLang[_ENGLISH]->setGeometry(QRect(160, 285, 100, 60));

    btLang[_CHINESE] = new CButtonStable(this);
    btLang[_CHINESE]->setGeometry(QRect(265, 285, 100, 60));

    btLang[_RUSSIAN] = new CButtonStable(this);
    btLang[_RUSSIAN]->setGeometry(QRect(370, 285, 100, 60));

    btLang[_KOREA] = new CButtonStable(this);
    btLang[_KOREA]->setGeometry(QRect(480, 285, 100, 60));

    btMaintenanceSet = new CButtonStable(this);
    btMaintenanceSet->setGeometry(QRect(480, 190, 100, 60));

    btStandOnLeft = new CButtonStable(this);
    btStandOnLeft->setGeometry(QRect(430, 355, 150, 55));

    btStandOnRight = new CButtonStable(this);
    btStandOnRight->setGeometry(QRect(250, 355, 150, 55));

    btRestart = new CButtonStable(this);
    btRestart->setGeometry(QRect(60, 530, 105, 55));

    stCtrl_2 = new QLabel(this);
    stCtrl_2->setGeometry(QRect(20, 60, 171, 50));

    stCtrl_3 = new QLabel(this);
    stCtrl_3->setGeometry(QRect(20, 170, 281, 50));

    stCtrl_4 = new QLabel(this);
    stCtrl_4->setGeometry(QRect(20, 220, 220, 50));

    stCtrl_5 = new QLabel(this);
    stCtrl_5->setGeometry(QRect(20, 280, 101, 50));

    stCtrl_6 = new QLabel(this);
    stCtrl_6->setGeometry(QRect(20, 350, 131, 50));

    lbInfoDateTime = new QLabel(this);
    lbInfoDateTime->setGeometry(QRect(200, 60, 271, 50));
    lbInfoDateTime->setStyleSheet("color : red");

    edHours = new QLabel(this);
    edHours->setGeometry(QRect(310, 180, 105, 40));
    edHours->setStyleSheet("background-color : white ; color : darkGreen");
    edHours->setFrameShape(QFrame::Panel);
    edHours->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    edHours->setLineWidth(2);

    edHoursRun = new QLabel(this);
    edHoursRun->setGeometry(QRect(310, 225, 105, 40));
    edHoursRun->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    edHoursRun->setStyleSheet("background-color : yellow ; color : red; border : 1px solid black");

    dateEdit = new QLabel(this);
    dateEdit->setGeometry(QRect(25, 100, 140, 40));
    dateEdit->setStyleSheet("background-color : white ; color : darkGreen");
    dateEdit->setFrameShape(QFrame::Panel);
    dateEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    dateEdit->setLineWidth(2);

    timeEdit = new QLabel(this);
    timeEdit->setGeometry(QRect(200, 100, 101, 40));
    timeEdit->setStyleSheet("background-color : white ; color : darkGreen");
    timeEdit->setFrameShape(QFrame::Panel);
    timeEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    timeEdit->setLineWidth(2);

    line_1 = new QFrame(this);
    line_1->setGeometry(QRect(50, 160, 500, 10));
    line_1->setFrameShape(QFrame::HLine);
    line_1->setFrameShadow(QFrame::Sunken);

    line_2 = new QFrame(this);
    line_2->setGeometry(QRect(50, 270, 500, 10));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);

    line_3 = new QFrame(this);
    line_3->setGeometry(QRect(50, 345, 500, 10));
    line_3->setFrameShape(QFrame::HLine);
    line_3->setFrameShadow(QFrame::Sunken);

    line_4 = new QFrame(this);
    line_4->setGeometry(QRect(50, 415, 500, 10));
    line_4->setFrameShape(QFrame::HLine);
    line_4->setFrameShadow(QFrame::Sunken);

    btRestart->hide();

    stCtrl_2->setText(QApplication::translate("CSystemConfig", "System time set:" ));
    stCtrl_3->setText(QApplication::translate("CSystemConfig", "Time for next maintenance(Hours):" ));
    stCtrl_4->setText(QApplication::translate("CSystemConfig", "Elapsed/Total time(Hours):" ));
    stCtrl_5->setText(QApplication::translate("CSystemConfig", "Language:" ));
    stCtrl_6->setText(QApplication::translate("CSystemConfig", "Install Mode:" ));

    btLang[_ENGLISH]->setText(QApplication::translate("CSystemConfig", "English" ));
    btLang[_CHINESE]->setText(QApplication::translate("CSystemConfig", "Chinese" ));
    btLang[_RUSSIAN]->setText(QApplication::translate("CSystemConfig", "Russian" ));
    btLang[_KOREA]->setText(QApplication::translate("CSystemConfig", "Korea" ));
    btMaintenanceSet->setText(QApplication::translate("CSystemConfig", "SET" ));
    btStandOnLeft->setText(QApplication::translate("CSystemConfig", "Stand On Left" ));
    btStandOnRight->setText(QApplication::translate("CSystemConfig", "Stand On Right" ));
    btRestart->setText(QApplication::translate("CSystemConfig", "Restart" ));

    flag_NeedReboot = false;

    m_iFocusCurrent = -1;

    edHours->installEventFilter(this);
    dateEdit->installEventFilter(this);
    timeEdit->installEventFilter(this);

    connect(btLang[_ENGLISH],   SIGNAL(pressed()),this,SLOT(OnLanguageChange()));
    connect(btLang[_CHINESE],   SIGNAL(pressed()),this,SLOT(OnLanguageChange()) );
    connect(btLang[_RUSSIAN],   SIGNAL(pressed()),this,SLOT(OnLanguageChange()) );
    connect(btLang[_KOREA],     SIGNAL(pressed()),this,SLOT(OnLanguageChange()) );

    connect(btMaintenanceSet,   SIGNAL(pressed()),this,SLOT(OnButtonPressed()) );
    connect(btStandOnRight,     SIGNAL(pressed()),this,SLOT(OnButtonPressed()) );
    connect(btStandOnLeft,      SIGNAL(pressed()),this,SLOT(OnButtonPressed()) );
    connect(btSaveDate,             SIGNAL(pressed()),this,SLOT(OnBtnSaveDate()) );
    connect(btnExit,            SIGNAL(pressed()),this,SLOT(OnButtonPressed()) );
    connect(btRestart,          SIGNAL(pressed()),this,SLOT(OnButtonPressed()) );

    translateFontSize( this );

    setVisible(false);
}


void CSystemConfig::showEvent(QShowEvent *event)
{
    QString mStr,strDate,strTime;

    QTime ts=QTime::currentTime();
    QDate dt=QDate::currentDate();

    strDate.sprintf("%d/%02d/%02d ",dt.year(),dt.month(),dt.day());
    strTime.sprintf("%02d:%02d",ts.hour(),ts.minute());

    dateEdit->setText(strDate);
    timeEdit->setText(strTime);

    mStr.setNum(g_dbsys.dbsystem.mMaintenanceTime);
    edHours->setText(mStr);

    //display section time and total .
    mStr.sprintf("%u/%u",g_dbsys.dbsystem.mOperationTime,g_dbsys.dbsystem.mTotalTime);
    edHoursRun->setText(mStr);

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad = new CSystemImepad(this);

    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        btStandOnRight->setStyleSheet("background-color:cyan ; border : 1px solid black");
        btStandOnLeft->setStyleSheet("background-color:darkGray ; border : 1px solid black");
    }else
    {
        btStandOnRight->setStyleSheet("background-color:darkGray ; border : 1px solid black");
        btStandOnLeft->setStyleSheet("background-color:cyan ; border : 1px solid black");
    }

    for(int mIdx = 0 ; mIdx < LANGUAGE_MAX; mIdx++)
    {
        btLang[mIdx]->setStyleSheet("background-color:darkGray ; border : 1px solid black");
    }
    btLang[g_dbsys.dbsystem.language]->setStyleSheet("background-color:cyan ; border : 1px solid black");

    grabKeyboard();

    CSystemBase::showEvent(event);

}

void CSystemConfig::hideEvent(QHideEvent *event)
{
    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    releaseKeyboard();

    CSystemBase::hideEvent(event);
}
void CSystemConfig::OnBtnSaveDate()
{

    if(!g_systemDb->m_bCanSaveDate)
    {
        lbInfoDateTime->setText(QApplication::translate("CSystemConfig", "Modified date function is not enabled!"));
        return;
    }

    if(g_systemPad)
        g_systemPad->hide();

    QDateTime mDt;
    QDate mDate;
    QTime mTime;

    QString mStr = dateEdit->text();
    QString mTemp;

    int mYear,mMonth,mDay,mHour,mMinute;

    mTemp = mStr.left(4);
    mStr.remove(0,5);
    mYear = mTemp.toInt();

    mTemp = mStr.left(2);
    mStr.remove(0,3);
    mMonth = mTemp.toInt();

    mDay = mStr.toInt();

    mStr = timeEdit->text();
    mTemp = mStr.left(2);
    mStr.remove(0,3);
    mHour = mTemp.toInt();

    mMinute = mStr.toInt();

    mDate.setDate(mYear,mMonth,mDay);
    mTime.setHMS(mHour,mMinute,0);

    if(!mDate.isValid())
    {
        lbInfoDateTime->setText(QApplication::translate("CSystemConfig", "Enter dates illegal" ));
        return;
    }

    if(!mTime.isValid())
    {
        lbInfoDateTime->setText(QApplication::translate("CSystemConfig", "Enter time illegal" ));
        return;
    }

    //check password date and user input date,if  g_systemDb->mDateJulian == 0, skip check for super user.
    if(g_systemDb->mDateJulian != mDate.toJulianDay() % 1000  && g_systemDb->mDateJulian != 0 )
    {
        lbInfoDateTime->setText(QApplication::translate("CSystemConfig", "Please enter the date of the day" ));
        return;
    }

    mDt.setDate(mDate);
    mDt.setTime(mTime);

    struct timeval myTv;
    myTv.tv_sec  = mDt.toUTC().toTime_t();
    myTv.tv_usec = 0;

    if ( myTv.tv_sec != -1 )
    {
        int mRes = ::settimeofday( &myTv, 0 );
        if(mRes != 0)
        {
            lbInfoDateTime->setText(QApplication::translate("CSystemConfig", "Set time failure." ));
            return;
        }

        mRes = MySystem("hwclock -w");
        if(mRes != 0)
        {
            lbInfoDateTime->setText(QApplication::translate("CSystemConfig", "Refresh time failure." ));
            return;
        }

        lbInfoDateTime->setText(QApplication::translate("CSystemConfig", "Time refresh successfully." ));
    }

}
void CSystemConfig::OnButtonPressed()
{

    lbInfoDateTime->setText("");

    if(flag_NeedReboot == true)
    {
        if(sender() == btRestart )
        {
            RsMgr->g_filmBase->SetLCD(false);

            MySystem("reboot");
        }

        return;
    }

    if(sender() == btnExit )
    {

        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        return;
    }

    if(sender() == btStandOnRight )
    {
        btStandOnRight->setStyleSheet("background-color:cyan; border : 1px solid black");
        btStandOnLeft->setStyleSheet("background-color:darkGray; border : 1px solid black");
        g_dbsys.utility.mDetectorStandDir = DETECTOR_STAND_RIGHT;
        g_systemDb->SaveSystemCfg("utility/mDetectorStandDir",g_dbsys.utility.mDetectorStandDir);
        return;
    }

    if(sender() == btStandOnLeft )
    {
        btStandOnRight->setStyleSheet("background-color:darkGray; border : 1px solid black");
        btStandOnLeft->setStyleSheet("background-color:cyan; border : 1px solid black");
        g_dbsys.utility.mDetectorStandDir = DETECTOR_STAND_LEFT;
        g_systemDb->SaveSystemCfg("utility/mDetectorStandDir",g_dbsys.utility.mDetectorStandDir);
        return;
    }

    if(sender() == btMaintenanceSet )
    {

        if(g_systemPad)
            g_systemPad->hide();

        g_dbsys.dbsystem.mMaintenanceTime = edHours->text().toInt();
        g_systemDb->SaveSystemCfg("dbsystem/mMaintenanceTime",g_dbsys.dbsystem.mMaintenanceTime);

        edHoursRun->setText("0");
        g_dbsys.dbsystem.mOperationTime=0;
        g_systemDb->SaveSystemCfg("dbsystem/mOperationTime",g_dbsys.dbsystem.mOperationTime);
    }

}
void CSystemConfig::OnLanguageChange()
{

    if(g_systemPad)
        g_systemPad->hide();

    for(int mIdx = 0 ; mIdx < LANGUAGE_MAX; mIdx++)
    {
        if(sender() == btLang[mIdx])
        {
            g_dbsys.dbsystem.language = mIdx;
        }
    }

    g_systemDb->SaveSystemCfg("dbsystem/language",g_dbsys.dbsystem.language);

    flag_NeedReboot = true;
    btRestart->show();
    btRestart->setStyleSheet( "QPushButton{background-color:cyan}");

    for(int mIdx = 0 ; mIdx < LANGUAGE_MAX; mIdx++)
    {
        btLang[mIdx]->setStyleSheet("background-color:darkGray ; border : 1px solid black");
    }
    btLang[g_dbsys.dbsystem.language]->setStyleSheet("background-color:cyan ; border : 1px solid black");
}

bool CSystemConfig::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==timeEdit)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            g_systemPad->move(70,180);
            g_systemPad->show();
            m_iFocusCurrent = CFG_FOCUS_TIME;
            m_strKeyBuff = "";
            lbInfoDateTime->setText("");
            m_StrMaxLength = LENGTH_MAX_TIME;
        }
    }

    if(watched==dateEdit)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            g_systemPad->move(20,180);
            g_systemPad->show();
            m_iFocusCurrent = CFG_FOCUS_DATE;
            m_strKeyBuff = "";
            lbInfoDateTime->setText("");
            m_StrMaxLength = LENGTH_MAX_DATE;
        }
    }

    if(watched==edHours)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            g_systemPad->show();
            g_systemPad->move(80,180);
            m_iFocusCurrent = CFG_FOCUS_MANT;
            m_strKeyBuff = "";

            m_StrMaxLength = LENGTH_MAX_MAINTANCE;
        }
    }

    return QWidget::eventFilter(watched,event);
}

void CSystemConfig::keyPressEvent ( QKeyEvent * event )
{
    bool bBackSpace = false;

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
        if(m_strKeyBuff.length() < PASSWORD_MAX_LENGTH &&( (mKey >= Qt::Key_0 &&  mKey <= Qt::Key_9) || ( mKey >= Qt::Key_A  &&  mKey <= Qt::Key_Z)))
            m_strKeyBuff.append(event->key());

        break;
    }


    if(m_iFocusCurrent == CFG_FOCUS_MANT)
    {
        edHours->setText(m_strKeyBuff);
        return;
    }
    if(m_iFocusCurrent == CFG_FOCUS_TIME)
    {
        if(!bBackSpace)
        {
            if(m_strKeyBuff.length() == 2)
                m_strKeyBuff += ":";
        }
        timeEdit->setText(m_strKeyBuff);
        return;
    }
    if(m_iFocusCurrent == CFG_FOCUS_DATE)
    {
        if(!bBackSpace)
        {
            if(m_strKeyBuff.length() == 4)
                m_strKeyBuff += "/";

            if(m_strKeyBuff.length() == 7)
                m_strKeyBuff += "/";
        }
        dateEdit->setText(m_strKeyBuff);
        return;
    }
}

