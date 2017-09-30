#include "system_install.h"
#include "sys_database.h"
#include "resource_manager.h"

#define INSTALL_PERIOD_MAX ( 12 )
#define INSTALL_PERIOD_MONTH_MAX ( 12 )
#define INSTALL_STATE_ON ( 1 )
#define INSTALL_STATE_OFF ( 0 )

CSystemInstall::CSystemInstall( QWidget* parent):
    CSystemBase(parent)
{

    setObjectName("CSystemInstall");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemInstall", "System Install Configuration"));

    for(int mIdx = 0 ; mIdx < INSTALL_EDIT_MAX ; mIdx++)
    {
        pLineE[mIdx] = new QLabel(this);
        pLineE[mIdx]->installEventFilter(this);
        pLineE[mIdx]->setStyleSheet("background-color : white ; color : black");
        pLineE[mIdx]->setFrameShape(QFrame::Panel);
    }

    pLineE[0]->setGeometry(QRect(180, 120, 80, 38));
    pLineE[1]->setGeometry(QRect(180, 160, 80, 38));
    pLineE[2]->setGeometry(QRect(180, 202, 130, 38));
    pLineE[3]->setGeometry(QRect(180, 242, 50, 38));
    pLineE[4]->setGeometry(QRect(243, 242, 50, 38));
    pLineE[5]->setGeometry(QRect(305, 242, 50, 38));
    pLineE[6]->setGeometry(QRect(180, 282, 50, 38));
    pLineE[7]->setGeometry(QRect(243, 282, 50, 38));
    pLineE[8] ->setGeometry(QRect(305, 282, 50, 38));
    pLineE[9]->setGeometry(QRect(180, 322, 45, 38));
    pLineE[10]->setGeometry(QRect(243, 322, 45, 38));
    pLineE[11]->setGeometry(QRect(180, 362, 101, 38));
    pLineE[12]->setGeometry(QRect(180, 402, 101, 38));

    btStateOn = new CButtonStable(this);
    btStateOn->setGeometry(QRect(175, 70, 70, 40));
    btStateOn->setText(QApplication::translate("CSystemInstall", "On"));

    btStateOff = new CButtonStable(this);
    btStateOff->setGeometry(QRect(270, 70, 70, 40));
    btStateOff->setText(QApplication::translate("CSystemInstall", "Off"));

    btSave = new CButtonStable(this);
    btSave->setGeometry(QRect(425, 525, 100, 60));
    btSave->setText(QApplication::translate("CSystemInstall", "SAVE"));

    sterror = new QLabel(this);
    sterror->setGeometry(QRect(0, 465, 600, 35));
    sterror->setStyleSheet("color : red");
    sterror->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    for(int mIdx = 0 ; mIdx < INSTALL_LABEL_MAX; mIdx++)
    {
        pLabelAry[mIdx] = new QLabel(this);
    }

    pLabelAry[0]->setGeometry(QRect(15, 367, 150, 24));
    pLabelAry[0]->setText(QApplication::translate("CSystemInstall", "Identify Code:"));

    pLabelAry[1]->setGeometry(QRect(15, 407, 150, 24));
    pLabelAry[1]->setText(QApplication::translate("CSystemInstall", "Code Confirm:"));

    pLabelAry[2]->setGeometry(QRect(15, 207, 150, 24));
    pLabelAry[2]->setText(QApplication::translate("CSystemInstall", "Machine Code:"));

    pLabelAry[3]->setGeometry(QRect(15, 80, 150, 31));
    pLabelAry[3]->setText(QApplication::translate("CSystemInstall", "Install Choice:"));

    pLabelAry[4]->setGeometry(QRect(15, 287, 150, 24));
    pLabelAry[4]->setText(QApplication::translate("CSystemInstall", "Start Stop Data:"));

    pLabelAry[5]->setGeometry(QRect(15, 125, 150, 24));
    pLabelAry[5]->setText(QApplication::translate("CSystemInstall", "Periods:"));

    pLabelAry[6]->setGeometry(QRect(15, 327, 150, 24));
    pLabelAry[6]->setText(QApplication::translate("CSystemInstall", "Stop Time:"));

    pLabelAry[7]->setGeometry(QRect(15, 167, 150, 24));
    pLabelAry[7]->setText(QApplication::translate("CSystemInstall", "Period Length:"));

    pLabelAry[8]->setGeometry(QRect(15, 247, 150, 24));
    pLabelAry[8]->setText(QApplication::translate("CSystemInstall", "Manufacture Date:"));

    pLabelAry[9]->setGeometry(QRect(231, 327, 18, 28));
    pLabelAry[9]->setText(QApplication::translate("CSystemInstall", ":"));
    pLabelAry[9]->lower();

    pLabelAry[10]->setGeometry(QRect(232, 287, 18, 28));
    pLabelAry[10]->setText(QApplication::translate("CSystemInstall", "-"));
    pLabelAry[10]->lower();

    pLabelAry[11]->setGeometry(QRect(295, 247, 18, 28));
    pLabelAry[11]->setText(QApplication::translate("CSystemInstall", "-"));
    pLabelAry[11]->lower();

    pLabelAry[12]->setGeometry(QRect(320, 210, 300, 24));
    pLabelAry[12]->setText(QApplication::translate("CSystemInstall", "(Manufacture number)"));

    pLabelAry[13]->setGeometry(QRect(365, 252, 165, 24));
    pLabelAry[13]->setText(QApplication::translate("CSystemInstall", "(YY-MM-DD)"));

    pLabelAry[14]->setGeometry(QRect(285, 412, 211, 24));
    pLabelAry[14]->setText(QApplication::translate("CSystemInstall", "(Input Range:1~9999)"));

    pLabelAry[15]->setGeometry(QRect(365, 292, 165, 24));
    pLabelAry[15]->setText(QApplication::translate("CSystemInstall", "(YY-MM-DD)"));

    pLabelAry[16]->setGeometry(QRect(295, 287, 18, 28));
    pLabelAry[16]->setText(QApplication::translate("CSystemInstall", "-"));
    pLabelAry[16]->lower();

    pLabelAry[17]->setGeometry(QRect(232, 247, 18, 28));
    pLabelAry[17]->setText(QApplication::translate("CSystemInstall", "-"));
    pLabelAry[17]->lower();

    pLabelAry[18]->setGeometry(QRect(285, 372, 241, 24));
    pLabelAry[18]->setText(QApplication::translate("CSystemInstall", "(Input Range:1~9999)"));

    pLabelAry[19]->setGeometry(QRect(270, 128, 201, 24));
    pLabelAry[19]->setText(QApplication::translate("CSystemInstall", "(Range:1~12)"));

    pLabelAry[20]->setGeometry(QRect(270, 170, 201, 24));
    pLabelAry[20]->setText(QApplication::translate("CSystemInstall", "(Month:1~12)"));

    connect(btSave,SIGNAL(pressed()),this,SLOT(OnInstallSave()));
    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnInstallExit()));
    connect(btStateOn,SIGNAL(pressed()),this,SLOT(OnStateChange()));
    connect(btStateOff,SIGNAL(pressed()),this,SLOT(OnStateChange()));

    translateFontSize( this );

    setVisible(false);
}

void CSystemInstall::OnStateChange()
{
    if(sender() == btStateOn)
    {
        g_dbsys.operationx.cState = INSTALL_STATE_ON;
        btStateOn->setStyleSheet("background-color:cyan; border : 1px solid green");
        btStateOff->setStyleSheet("background-color:darkGray; border : 1px solid green");
    }
    if(sender() == btStateOff)
    {
        g_dbsys.operationx.cState = INSTALL_STATE_OFF;
        btStateOn->setStyleSheet("background-color:darkGray; border : 1px solid green");
        btStateOff->setStyleSheet("background-color:cyan; border : 1px solid green");
    }
    //only the save button can save data to disk.
    //    g_dbsys.utility.mTryTimes = 12;
    //    g_systemDb->SaveSystemCfg("utility/mTryTimes",g_dbsys.utility.mTryTimes);
    //    g_systemDb->SaveSystemCfg("operationx/cState",g_dbsys.operationx.cState);
}

void CSystemInstall::showEvent(QShowEvent *event)
{
    QString mStr;

    if(g_dbsys.operationx.cState == INSTALL_STATE_ON)
    {
        btStateOn->setStyleSheet("background-color:cyan; border : 1px solid green");
        btStateOff->setStyleSheet("background-color:darkGray; border : 1px solid green");
    }else
    {
        btStateOn->setStyleSheet("background-color:darkGray; border : 1px solid green");
        btStateOff->setStyleSheet("background-color:cyan; border : 1px solid green");
    }

    mStr.setNum(g_dbsys.operationx.cPeriods);
    pLineE[0]->setText(mStr);

    mStr.setNum(g_dbsys.operationx.cPeriodLength);
    pLineE[1]->setText(mStr);

    mStr.sprintf("%s", g_dbsys.dbsystem.machine2);
    pLineE[2]->setText(mStr);

    mStr.setNum(g_dbsys.dateOut.year);
    pLineE[3]->setText(mStr);
    mStr.setNum(g_dbsys.dateOut.month);
    pLineE[4]->setText(mStr);
    mStr.setNum(g_dbsys.dateOut.day);
    pLineE[5]->setText(mStr);

    mStr.setNum(g_dbsys.dateStart.year);
    pLineE[6]->setText(mStr);
    mStr.setNum(g_dbsys.dateStart.month);
    pLineE[7]->setText(mStr);
    mStr.setNum(g_dbsys.dateStart.day);
    pLineE[8]->setText(mStr);

    mStr.setNum(g_dbsys.operationx.tHour);
    pLineE[9]->setText(mStr);
    mStr.setNum(g_dbsys.operationx.tMinute);
    pLineE[10]->setText(mStr);

    pLineE[11]->setText("1");
    pLineE[12]->setText("1");

    //g_dbsys.operation.bTimeout = false;

    sterror->setText("");

    if (g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad=new CSystemImepad(this);

    CSystemBase::showEvent(event);
}

void CSystemInstall::hideEvent(QHideEvent *event)
{
    CSystemBase::hideEvent(event);
}

void CSystemInstall::OnInstallExit()
{

    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);

        return;
    }
}

void CSystemInstall::OnInstallSave()
{ 
    unsigned short wValue;
    QDate mDate;
    QTime mTime;

    if(sender() == btSave )
    {
        g_dbsys.operationx.cPeriods = pLineE[0]->text().toInt();
        g_dbsys.operationx.cPeriodLength = pLineE[1]->text().toInt();

        g_dbsys.dateOut.year = pLineE[3]->text().toInt();
        g_dbsys.dateOut.month = pLineE[4]->text().toInt();
        g_dbsys.dateOut.day = pLineE[5]->text().toInt();

        g_dbsys.dateStart.year = pLineE[6]->text().toInt();
        g_dbsys.dateStart.month = pLineE[7]->text().toInt();
        g_dbsys.dateStart.day = pLineE[8]->text().toInt();

        g_dbsys.operationx.tHour = pLineE[9]->text().toInt();
        g_dbsys.operationx.tMinute = pLineE[10]->text().toInt();

        g_dbsys.operationx.wIdentifyCode = pLineE[11]->text().toInt();
        wValue = pLineE[12]->text().toInt();
        strcpy(g_dbsys.dbsystem.machine2,pLineE[2]->text().toLatin1().data());

        if(g_dbsys.operationx.cState == INSTALL_STATE_OFF)
        {

            g_systemDb->SaveSystemCfg("operationx/cPeriods", g_dbsys.operationx.cPeriods);
            g_systemDb->SaveSystemCfg("operationx/cPeriodLength", g_dbsys.operationx.cPeriodLength);
            g_systemDb->SaveSystemCfg("operationx/tHour", g_dbsys.operationx.tHour);
            g_systemDb->SaveSystemCfg("operationx/tMinute", g_dbsys.operationx.tMinute);
            g_systemDb->SaveSystemCfg("operationx/wIdentifyCode", g_dbsys.operationx.wIdentifyCode);

            g_systemDb->SaveSystemCfg("dateOut/year", g_dbsys.dateOut.year);
            g_systemDb->SaveSystemCfg("dateOut/month", g_dbsys.dateOut.month);
            g_systemDb->SaveSystemCfg("dateOut/day", g_dbsys.dateOut.day);

            g_systemDb->SaveSystemCfg("dateStart/year", g_dbsys.dateStart.year);
            g_systemDb->SaveSystemCfg("dateStart/month", g_dbsys.dateStart.month);
            g_systemDb->SaveSystemCfg("dateStart/day", g_dbsys.dateStart.day);

            sterror->setText(QApplication::translate("CSystemInstall", "Intasll State closed." ));
            return;
        }

        if((g_dbsys.operationx.cPeriods < 1) || (g_dbsys.operationx.cPeriods > INSTALL_PERIOD_MAX))
        {
            pLineE[0]->setFocus();
            sterror->setText(QApplication::translate("CSystemInstall", "Periods out of range!" ));
            return;
        }

        if((g_dbsys.operationx.cPeriodLength < 1) || (g_dbsys.operationx.cPeriodLength > INSTALL_PERIOD_MONTH_MAX))
        {
            pLineE[1]->setFocus();
            sterror->setText(QApplication::translate("CSystemInstall", "Period length error!" ));
            return;
        }

        if (strlen( g_dbsys.dbsystem.machine2) < 6 || g_dbsys.dbsystem.machine2[0]==' ' || strlen( g_dbsys.dbsystem.machine2) > 8)
        {
            pLineE[2]->setFocus();
            sterror->setText(QApplication::translate("CSystemInstall", "Char is Not Enough" ));
            return;
        }

        mDate.setDate(g_dbsys.dateOut.year,g_dbsys.dateOut.month,g_dbsys.dateOut.day);
        if(!mDate.isValid())
        {
            sterror->setText(QApplication::translate("CSystemInstall", "Enter dates illegal" ));
            return;
        }

        mDate.setDate(g_dbsys.dateStart.year,g_dbsys.dateStart.month,g_dbsys.dateStart.day);
        if(!mDate.isValid())
        {
            sterror->setText(QApplication::translate("CSystemInstall", "Enter dates illegal" ));
            return;
        }

        mTime.setHMS(g_dbsys.operationx.tHour,g_dbsys.operationx.tMinute,0);
        if(!mTime.isValid())
        {
            sterror->setText(QApplication::translate("CSystemInstall", "Enter time illegal" ));
            return;
        }

        if (g_dbsys.operationx.wIdentifyCode != wValue)
        {
            pLineE[11]->setFocus();
            sterror->setText(QApplication::translate("CSystemInstall", "Inconsistency identifier" ));
            return;
        }

        if(g_dbsys.operationx.wIdentifyCode < 1)
        {
            pLineE[12]->setFocus();
            sterror->setText(QApplication::translate("CSystemInstall", "ID out of range" ));
            return;
        }

        g_dbsys.operationx.cNowNum = 1;

        g_systemDb->SaveSystemCfg("operationx/cPeriods", g_dbsys.operationx.cPeriods);
        g_systemDb->SaveSystemCfg("operationx/cPeriodLength", g_dbsys.operationx.cPeriodLength);
        g_systemDb->SaveSystemCfg("operationx/tHour", g_dbsys.operationx.tHour);
        g_systemDb->SaveSystemCfg("operationx/tMinute", g_dbsys.operationx.tMinute);
        g_systemDb->SaveSystemCfg("operationx/wIdentifyCode", g_dbsys.operationx.wIdentifyCode);
        g_systemDb->SaveSystemCfg("operationx/cNowNum", g_dbsys.operationx.cNowNum);

        g_systemDb->SaveSystemCfg("dateOut/year", g_dbsys.dateOut.year);
        g_systemDb->SaveSystemCfg("dateOut/month", g_dbsys.dateOut.month);
        g_systemDb->SaveSystemCfg("dateOut/day", g_dbsys.dateOut.day);

        g_systemDb->SaveSystemCfg("dateStart/year", g_dbsys.dateStart.year);
        g_systemDb->SaveSystemCfg("dateStart/month", g_dbsys.dateStart.month);
        g_systemDb->SaveSystemCfg("dateStart/day", g_dbsys.dateStart.day);

        g_systemDb->SaveSystemCfg("dbsystem/machine2", g_dbsys.dbsystem.machine2);

        //20160912 only valid passwd can save data to disk.
        g_dbsys.utility.mTryTimes = 12;
        g_systemDb->SaveSystemCfg("utility/mTryTimes",g_dbsys.utility.mTryTimes);
        g_systemDb->SaveSystemCfg("operationx/cState",g_dbsys.operationx.cState);

        sterror->setText(QApplication::translate("CSystemInstall", "Save Successfully" ));
    }
}
bool CSystemInstall::eventFilter(QObject *watched, QEvent *event)
{ for(int mIdx = 0 ; mIdx < 13 ; mIdx++)
    {
        if(watched == pLineE[mIdx])
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                m_iFocusCurrent = mIdx;
                m_strKeyBuff = "";
                sterror->setText("");
                pLineE[m_iFocusCurrent]->setText("");
                g_systemPad->move(360,140);
                g_systemPad->show();
            }
            break;
        }
    }

    return QWidget::eventFilter(watched,event);
}
void CSystemInstall::keyPressEvent( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Backspace)
    {
        int iStrLen = m_strKeyBuff.length();
        if(iStrLen > 0)
        {
            m_strKeyBuff.remove( iStrLen - 1,1);
            pLineE[m_iFocusCurrent]->setText(m_strKeyBuff);
        }
    }else if(event->key() == Qt::Key_Close)
    {
    }else
    {
        if(m_strKeyBuff.length() < 8 )
            m_strKeyBuff.append(event->key());

        pLineE[m_iFocusCurrent]->setText(m_strKeyBuff);
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
