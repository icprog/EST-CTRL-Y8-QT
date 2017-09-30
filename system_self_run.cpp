#include "system_self_run.h"

#include "sys_database.h"
#include "resource_manager.h"

#define FOCUS_IDX_NULL          (0)
#define FOCUS_IDX_INTERVAL      (1)
#define FOCUS_IDX_HOURS         (2)

CSystemSelfRun::CSystemSelfRun( QWidget* parent ):
    CSystemBase(parent)
{     

    setObjectName("CSystemSelfRun");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemSelfRun", "System Self-Runing Test"));

    edMinuteTotal = new QLabel(this);
    edMinuteTotal->installEventFilter(this);
    edMinuteTotal->setGeometry(QRect(120, 300, 120, 45));
    edMinuteTotal->setStyleSheet("background-color : white ; color : green");
    edMinuteTotal->setFrameShape(QFrame::Panel);
    edMinuteTotal->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    edMinuteTotal->setLineWidth(2);

    edMinutePassed = new QLabel(this);
    edMinutePassed->setGeometry(QRect(350, 100, 80, 35));
    edMinutePassed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    lbMinute = new QLabel(this);
    lbMinute->setGeometry(QRect(450, 100, 75, 35));
    lbMinute->setText(QApplication::translate("CSystemSelfRun", "(Minute)"));

    edRunInterval = new QLabel(this);
    edRunInterval->setGeometry(QRect(120, 200, 120, 45));
    edRunInterval->installEventFilter(this);
    edRunInterval->setStyleSheet("background-color : white ; color : green");
    edRunInterval->setFrameShape(QFrame::Panel);
    edRunInterval->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    edRunInterval->setLineWidth(2);

    btOk = new CButtonStable(this);
    btOk->setGeometry(QRect(425, 525, 100, 60));
    btOk->setText(QApplication::translate("CSystemSelfRun", "Start"));

    btFastPosTest = new CButtonStable(this);
    btFastPosTest->setGeometry(QRect(90, 365, 180, 60));
    btFastPosTest->setText(QApplication::translate("CSystemSelfRun", "Fast Position"));
    btFastPosTest->setStyleSheet("background-color : cyan ; border : 2px solid green");

    btSoftLimitTest = new CButtonStable(this);
    btSoftLimitTest->setGeometry(QRect(330, 365, 180, 60));
    btSoftLimitTest->setText(QApplication::translate("CSystemSelfRun", "Soft Limit"));
    btSoftLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");

    btSwitchLimitTest = new CButtonStable(this);
    btSwitchLimitTest->setGeometry(QRect(90, 435, 180, 60));
    btSwitchLimitTest->setText(QApplication::translate("CSystemSelfRun", "Switch Limit"));
    btSwitchLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");

    btHardLimitTest = new CButtonStable(this);
    btHardLimitTest->setGeometry(QRect(330, 435, 180, 60));
    btHardLimitTest->setText(QApplication::translate("CSystemSelfRun", "Hard Limit"));
    btHardLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");

    lbinfo1 = new QLabel(this);
    lbinfo1->setGeometry(QRect(120, 310, 321, 44));
    lbinfo1->setText(QApplication::translate("CSystemSelfRun", "Interval Out Of Range!"));
    lbinfo1->setStyleSheet("color : red");

    lbinfo3 = new QLabel(this);
    lbinfo3->setGeometry(QRect(50, 150, 301, 38));
    lbinfo3->setText(QApplication::translate("CSystemSelfRun", "Self-Runing time interval:"));

    lbinfo4 = new QLabel(this);
    lbinfo4->setGeometry(QRect(260, 200, 261, 44));
    lbinfo4->setText(QApplication::translate("CSystemSelfRun", "(Range:3~60)(Second)"));

    lbinfo5 = new QLabel(this);
    lbinfo5->setGeometry(QRect(0, 55, 600, 35));
    lbinfo5->setText(QApplication::translate("CSystemSelfRun", "Attention: please set the fast position\nparameter before Self-Running test."));
    lbinfo5->setStyleSheet("color : red");
    lbinfo5->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    lbinfo2 = new QLabel(this);
    lbinfo2->setGeometry(QRect(120, 460, 321, 44));
    lbinfo2->setText(QApplication::translate("CSystemSelfRun", "Time Out Of Range"));
    lbinfo2->setStyleSheet("color : red");

    lbinfo6 = new QLabel(this);
    lbinfo6->setGeometry(QRect(260, 300, 261, 44));
    lbinfo6->setText(QApplication::translate("CSystemSelfRun", "(Range:120-2880)(Minute)"));

    lbinfo7 = new QLabel(this);
    lbinfo7->setGeometry(QRect(50, 260, 301, 38));
    lbinfo7->setText(QApplication::translate("CSystemSelfRun", "Self-Runing totle time:"));

    lbinfo8 = new QLabel(this);
    lbinfo8->setGeometry(QRect(50, 100, 251, 35));
    lbinfo8->setText(QApplication::translate("CSystemSelfRun", "Self-Running passed:"));

    for(int mIdx = 0 ; mIdx < 4 ; mIdx++)
    {
        pLine[mIdx] = new QFrame(this);
        pLine[mIdx]->setFrameShape(QFrame::HLine);
        pLine[mIdx]->setFrameShadow(QFrame::Sunken);
    }

    pLine[0]->setGeometry(QRect(50, 90, 500, 10));
    pLine[1]->setGeometry(QRect(50, 140, 500, 10));
    pLine[2]->setGeometry(QRect(50, 255, 500, 10));
    pLine[3]->setGeometry(QRect(50, 355, 500, 10));

    connect(btOk,SIGNAL(pressed()),this,SLOT(OnSelfRunPressed()) );
    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnSelfRunPressed()) );
    connect(btFastPosTest,SIGNAL(pressed()),this,SLOT(OnRunModePressed()) );
    connect(btSoftLimitTest,SIGNAL(pressed()),this,SLOT(OnRunModePressed()) );
    connect(btSwitchLimitTest,SIGNAL(pressed()),this,SLOT(OnRunModePressed()) );
    connect(btHardLimitTest,SIGNAL(pressed()),this,SLOT(OnRunModePressed()) );

    m_iAutoRunSel = AUTO_RUN_MODE_FAST;
    g_systemDb->g_iAutoRunMode = AUTO_RUN_MODE_FAST;

    m_strKeyBuff = "";
    m_iFocusCurrent = FOCUS_IDX_NULL;

    translateFontSize( this );
    setVisible(false);
}


void CSystemSelfRun::showEvent(QShowEvent *event)
{

    QString mStr;
    mStr.setNum( g_systemDb->m_SelfRunInterval);
    edRunInterval->setText(mStr);

    mStr.setNum(g_dbsys.dbsystem.mSelfRunTotal);
    edMinuteTotal->setText(mStr);

    mStr.setNum(g_dbsys.dbsystem.mSelfRunTime);
    edMinutePassed->setText(mStr);

    if(g_dbsys.dbsystem.mSelfRunTime >= g_dbsys.dbsystem.mSelfRunTotal)
        edMinutePassed->setStyleSheet("background-color : yellow ; color : green; border : 1px solid black");
    else
        edMinutePassed->setStyleSheet("background-color : yellow ; color : red; border : 1px solid black");

    lbinfo1->hide();
    lbinfo2->hide();

    if (g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad=new CSystemImepad(this);

    grabKeyboard();

    CSystemBase::showEvent(event);
}

void CSystemSelfRun::hideEvent(QHideEvent *event)
{

    if (g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    releaseKeyboard();

    CSystemBase::hideEvent(event);
}
void CSystemSelfRun::OnRunModePressed()
{
    if(sender() == btFastPosTest)
    {
        m_iAutoRunSel = AUTO_RUN_MODE_FAST;
        g_systemDb->g_iAutoRunMode = AUTO_RUN_MODE_FAST;
    return;
        btFastPosTest->setStyleSheet("background-color : cyan ; border : 2px solid green");
        btSoftLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btSwitchLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btHardLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");

        return;
    }

    if(sender() == btSoftLimitTest)
    {
        //跳过目前不支持的按钮 20150901 jsy
    return;
        m_iAutoRunSel = AUTO_RUN_MODE_SOFT;
        g_systemDb->g_iAutoRunMode = AUTO_RUN_MODE_SOFT;

        btFastPosTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btSoftLimitTest->setStyleSheet("background-color : cyan ; border : 2px solid green");
        btSwitchLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btHardLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");

        return;
    }

    if(sender() == btSwitchLimitTest)
    {
        //跳过目前不支持的按钮 20150901 jsy
        return;
        m_iAutoRunSel = AUTO_RUN_MODE_SWITCH;

        btFastPosTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btSoftLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btSwitchLimitTest->setStyleSheet("background-color : cyan ; border : 2px solid green");
        btHardLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");

        return;
    }

    if(sender() == btHardLimitTest)
    {
        //跳过目前不支持的按钮 20150901 jsy
        return;
        m_iAutoRunSel = AUTO_RUN_MODE_HARD;

        btFastPosTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btSoftLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btSwitchLimitTest->setStyleSheet("background-color : gray ; border : 2px solid green");
        btHardLimitTest->setStyleSheet("background-color : cyan ; border : 2px solid green");

        return;
    }

}
void CSystemSelfRun::OnSelfRunPressed()
{ 
    unsigned short wValue;

    if(sender() == btOk)
    {
        wValue = edRunInterval->text().toInt();

        if((wValue < 3) || (wValue > 60))
        {
            lbinfo1->show();
            m_strKeyBuff = "";
            return;
        }

        g_systemDb->m_SelfRunInterval = wValue;

        wValue = edMinuteTotal->text().toInt();
        if((wValue < 120) || (wValue > 2880))
        {
            lbinfo2->show();
            m_strKeyBuff = "";
            return;
        }
        g_dbsys.dbsystem.mSelfRunTotal = wValue;

        g_systemDb->SetAutoRun(true);
        this->hide();

        emit ViewChange(VIEW_MAIN);

        g_systemDb->g_bAutoRunOpen = true;

        g_systemDb->SaveSystemCfg("dbsystem/mSelfRunTotal",g_dbsys.dbsystem.mSelfRunTotal);

        return;

    }

    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
    }
} 

bool CSystemSelfRun::eventFilter(QObject *watched, QEvent *event)
{

    if(watched==edRunInterval)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            lbinfo1->hide();

            m_iFocusCurrent = FOCUS_IDX_INTERVAL;
            m_strKeyBuff = "";
            g_systemPad->move(310,100);
            g_systemPad->show();
        }
    }

    if(watched == edMinuteTotal)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            lbinfo2->hide();
            m_iFocusCurrent = FOCUS_IDX_HOURS;
            m_strKeyBuff="";
            g_systemPad->move(310,180);
            g_systemPad->show();
        }
    }

    return QWidget::eventFilter(watched,event);
}

void CSystemSelfRun::keyPressEvent( QKeyEvent * event )
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
        m_iFocusCurrent = FOCUS_IDX_NULL;
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

    if(m_iFocusCurrent == FOCUS_IDX_HOURS)
    {
        edMinuteTotal->setText(m_strKeyBuff);
    }else if( m_iFocusCurrent == FOCUS_IDX_INTERVAL)
    {
        edRunInterval->setText(m_strKeyBuff);
    }
}
