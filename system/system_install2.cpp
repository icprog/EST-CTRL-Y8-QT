#include "system_install2.h"
#include "sys_database.h"
#include "resource_manager.h"
#include <QCryptographicHash>

#define INSTALL_PERIOD_MAX ( 12 )
#define INSTALL_PERIOD_MONTH_MAX ( 12 )
#define INSTALL2_EDIT_MAX ( 14 )
#define INSTALL2_LABEL_MAX (15)
#define INSTALL_STATE_ON ( 1 )
#define INSTALL_STATE_OFF ( 0 )

#define INSTALL_EDIT_PERIOD   0
#define INSTALL_EDIT_LENGTH  1
#define INSTALL_EDIT_MACH_CODE       2
#define INSTALL_EDIT_YEAR       3
#define INSTALL_EDIT_MON       4
#define INSTALL_EDIT_DAY         5
#define INSTALL_EDIT_HOUR      6
#define INSTALL_EDIT_MINITE    7
#define INSTALL_EDIT_IDENTITY    8
#define INSTALL_EDIT_CODE_0    9
#define INSTALL_EDIT_CODE_1    10
#define INSTALL_EDIT_CODE_2    11
#define INSTALL_EDIT_CODE_3    12
#define INSTALL_EDIT_CODE_4    13

#define INSTALL_NUM_PER_EDIT  5   /*5 number in one edit box*/

CSystemInstall2::CSystemInstall2( QWidget* parent):
    CSystemBase(parent)
{

    setObjectName("CSystemInstall");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemInstall", "System Install Configuration"));

    //default pointer to code 0
    m_iFocusCurrent = INSTALL_EDIT_CODE_0;

    for(int mIdx = 0 ; mIdx < INSTALL2_LABEL_MAX; mIdx++)
    {
        QLabel * lbTemp = new QLabel(this);
        lbTemp->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        lbTemp->lower();
        arrLabel.push_back(lbTemp);
    }

    int mCtr = 0;
    arrLabel.at(mCtr)->setGeometry(QRect(15, 70, 150, 40));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "Install Choice:"));

    btStateOn = new CButtonStable(this);
    btStateOn->setGeometry(QRect(180, 70, 70, 40));
    btStateOn->setText(QApplication::translate("CSystemInstall", "On"));

    btStateOff = new CButtonStable(this);
    btStateOff->setGeometry(QRect(270, 70, 70, 40));
    btStateOff->setText(QApplication::translate("CSystemInstall", "Off"));

    for(int mIdx = 0 ; mIdx < INSTALL2_EDIT_MAX ; mIdx++)
    {
        QLabel * lbTemp = new QLabel(this);
        lbTemp->setStyleSheet("background-color : gray ; color : black");
        lbTemp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        lbTemp->setFrameShape(QFrame::Panel);
        arrEdit.push_back(lbTemp);
    }

    arrEdit.at(INSTALL_EDIT_CODE_0)->installEventFilter(this);
    arrEdit.at(INSTALL_EDIT_CODE_0)->setStyleSheet("background-color : white ; color : black;border:2px solid green");
    arrEdit.at(INSTALL_EDIT_CODE_1)->installEventFilter(this);
    arrEdit.at(INSTALL_EDIT_CODE_1)->setStyleSheet("background-color : white ; color : black");
    arrEdit.at(INSTALL_EDIT_CODE_2)->installEventFilter(this);
    arrEdit.at(INSTALL_EDIT_CODE_2)->setStyleSheet("background-color : white ; color : black");
    arrEdit.at(INSTALL_EDIT_CODE_3)->installEventFilter(this);
    arrEdit.at(INSTALL_EDIT_CODE_3)->setStyleSheet("background-color : white ; color : black");
    arrEdit.at(INSTALL_EDIT_CODE_4)->installEventFilter(this);
    arrEdit.at(INSTALL_EDIT_CODE_4)->setStyleSheet("background-color : white ; color : black");

    arrLabel.at(mCtr)->setGeometry(QRect(15, 120, 150, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "Periods:"));
    arrEdit.at(INSTALL_EDIT_PERIOD)->setGeometry(QRect(180, 120, 80, 38));

    arrLabel.at(mCtr)->setGeometry(QRect(15, 160, 150, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "Period Length:"));
    arrEdit.at(INSTALL_EDIT_LENGTH)->setGeometry(QRect(180, 160, 80, 38));

    arrLabel.at(mCtr)->setGeometry(QRect(15, 200, 150, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "Machine Code:"));
    arrEdit.at(INSTALL_EDIT_MACH_CODE)->setGeometry(QRect(180, 200, 96, 38));

    arrLabel.at(mCtr)->setGeometry(QRect(15, 240, 150, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "Identify Code:"));
    arrEdit.at(INSTALL_EDIT_IDENTITY)->setGeometry(QRect(180, 240, 96, 38));

    arrLabel.at(mCtr)->setGeometry(QRect(15, 280, 150, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "Stop Time:"));
    arrEdit.at(INSTALL_EDIT_HOUR)->setGeometry(QRect(180, 280, 50, 38));
    arrLabel.at(mCtr)->setGeometry(QRect(234, 280, 18, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", ":"));
    arrEdit.at(INSTALL_EDIT_MINITE)->setGeometry(QRect(243, 280, 50, 38));

    arrLabel.at(mCtr)->setGeometry(QRect(15, 320, 150, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "Start Stop Data:"));
    arrEdit.at(INSTALL_EDIT_YEAR)->setGeometry(QRect(180, 320, 50, 38));
    arrLabel.at(mCtr)->setGeometry(QRect(234, 320, 18, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "-"));
    arrEdit.at(INSTALL_EDIT_MON)->setGeometry(QRect(243, 320, 50, 38));
    arrLabel.at(mCtr)->setGeometry(QRect(297, 320, 18, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "-"));
    arrEdit.at(INSTALL_EDIT_DAY)->setGeometry(QRect(305, 320, 50, 38));

    arrLabel.at(mCtr)->setGeometry(QRect(15, 360, 150, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "Code Confirm:"));
    arrEdit.at(INSTALL_EDIT_CODE_0)->setGeometry(QRect(180, 360, 60, 38));
    arrLabel.at(mCtr)->setGeometry(QRect(240, 360, 18, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "-"));
    arrEdit.at(INSTALL_EDIT_CODE_1)->setGeometry(QRect(245, 360, 60, 38));
    arrLabel.at(mCtr)->setGeometry(QRect(305, 360, 18, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "-"));
    arrEdit.at(INSTALL_EDIT_CODE_2)->setGeometry(QRect(310, 360, 60, 38));
    arrLabel.at(mCtr)->setGeometry(QRect(370, 360, 18, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "-"));
    arrEdit.at(INSTALL_EDIT_CODE_3)->setGeometry(QRect(375, 360, 60, 38));
    arrLabel.at(mCtr)->setGeometry(QRect(435, 360, 18, 38));
    arrLabel.at(mCtr++)->setText(QApplication::translate("CSystemInstall", "-"));
    arrEdit.at(INSTALL_EDIT_CODE_4)->setGeometry(QRect(440, 360, 60, 38));

    btSave = new CButtonStable(this);
    btSave->setGeometry(QRect(425, 525, 100, 60));
    btSave->setText(QApplication::translate("CSystemInstall", "SAVE"));

    sterror = new QLabel(this);
    sterror->setGeometry(QRect(0, 465, 600, 35));
    sterror->setStyleSheet("color : blue");
    sterror->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    connect(btSave,SIGNAL(pressed()),this,SLOT(OnInstallSave()));
    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnInstallExit()));

    translateFontSize( this );

    setVisible(false);
}

void CSystemInstall2::FreshInformation()
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
    arrEdit.at(INSTALL_EDIT_PERIOD)->setText(mStr);

    mStr.setNum(g_dbsys.operationx.cPeriodLength);
    arrEdit.at(INSTALL_EDIT_LENGTH)->setText(mStr);

    QFile fileMechCode(QCoreApplication::applicationDirPath() +"/MachCode");
    char mBufCode[MACHINE_CODE_LEN + 1];
    memset(mBufCode,0,MACHINE_CODE_LEN + 1);

    //display the machine code in the file
    if(fileMechCode.exists())
    {
        fileMechCode.open(QFile::ReadOnly);
        fileMechCode.read(mBufCode,MACHINE_CODE_LEN);
        fileMechCode.close();
        arrEdit.at(INSTALL_EDIT_MACH_CODE)->setText(mBufCode);
    } else
    {
        mStr.sprintf("%s", g_dbsys.dbsystem.machine2);
        arrEdit.at(INSTALL_EDIT_MACH_CODE)->setText(mStr);
    }

    mStr.setNum(g_dbsys.dateStart.year);
    arrEdit.at(INSTALL_EDIT_YEAR)->setText(mStr);
    mStr.setNum(g_dbsys.dateStart.month);
    arrEdit.at(INSTALL_EDIT_MON)->setText(mStr);
    mStr.setNum(g_dbsys.dateStart.day);
    arrEdit.at(INSTALL_EDIT_DAY)->setText(mStr);

    mStr.setNum(g_dbsys.operationx.tHour);
    arrEdit.at(INSTALL_EDIT_HOUR)->setText(mStr);
    mStr.setNum(g_dbsys.operationx.tMinute);
    arrEdit.at(INSTALL_EDIT_MINITE)->setText(mStr);

    arrEdit.at(INSTALL_EDIT_IDENTITY)->setText("1");

}
void CSystemInstall2::showEvent(QShowEvent *event)
{

    grabKeyboard();

    FreshInformation();

    sterror->setText(QApplication::translate("CSystemInstall", "Please input the correct identity code!" ) + '#' );

    if (g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad=new CSystemImepad(this,false);  //can not close
    g_systemPad->move(368,65);
    g_systemPad->show();

    arrEdit.at(INSTALL_EDIT_CODE_0)->setFocus();


    QString *mStr;

    mStr = new QString(g_systemDb->getSystemCfg("operationx/key1","00000").toString());
    arrEdit.at(INSTALL_EDIT_CODE_0)->setText(*mStr);
    arrPwd.append(mStr);

    mStr = new QString(g_systemDb->getSystemCfg("operationx/key2","00000").toString());
    arrEdit.at(INSTALL_EDIT_CODE_1)->setText(*mStr);
    arrPwd.append(mStr);

    mStr = new QString(g_systemDb->getSystemCfg("operationx/key3","00000").toString());
    arrEdit.at(INSTALL_EDIT_CODE_2)->setText(*mStr);
    arrPwd.append(mStr);

    mStr = new QString(g_systemDb->getSystemCfg("operationx/key4","00000").toString());
    arrEdit.at(INSTALL_EDIT_CODE_3)->setText(*mStr);
    arrPwd.append(mStr);

    mStr = new QString(g_systemDb->getSystemCfg("operationx/key5","00000").toString());
    arrEdit.at(INSTALL_EDIT_CODE_4)->setText(*mStr);
    arrPwd.append(mStr);

    CSystemBase::showEvent(event);
}

void CSystemInstall2::hideEvent(QHideEvent *event)
{
    releaseKeyboard();

    CSystemBase::hideEvent(event);
}

void CSystemInstall2::OnInstallExit()
{

    if( g_dbsys.operationx.keyNeed)
    {
        sterror->setText(QApplication::translate("CSystemInstall", "Please input the correct identity code!" ) + '@' );
        return;
    }

    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);

        return;
    }
}

void CSystemInstall2::OnInstallSave()
{ 

    sterror->setStyleSheet("color : red");

    //get information from input box
    QString *mInputEdit[5];
    
    mInputEdit[0] =  new QString(arrEdit.at(INSTALL_EDIT_CODE_0)->text());
    mInputEdit[1] =  new QString(arrEdit.at(INSTALL_EDIT_CODE_1)->text());
    mInputEdit[2] =  new QString(arrEdit.at(INSTALL_EDIT_CODE_2)->text());
    mInputEdit[3] =  new QString(arrEdit.at(INSTALL_EDIT_CODE_3)->text());
    mInputEdit[4] =  new QString(arrEdit.at(INSTALL_EDIT_CODE_4)->text());

    //filter the old password
    int mCompareCtr = 0;
    for(int mIdx = 0 ; mIdx < 5 ; mIdx++)
        if( mInputEdit[mIdx]->compare( arrPwd.at(mIdx)) == 0 )
            mCompareCtr++;

    //if the password is used,return error.
    if(mCompareCtr >= 5)
    {
        sterror->setText(QApplication::translate("CSystemInstall", "Please input the correct identity code!" ) + '0' );
        return;
    }

    //check length of all data
    int totalLen = 0;
    for(int mIdx = 0 ; mIdx < 5 ; mIdx++)
        totalLen += mInputEdit[mIdx]->length() ;
    if(totalLen < 25)
    {
        sterror->setText(QApplication::translate("CSystemInstall", "Please input the correct identity code!" ) + '1' );
        return;
    }

    //seperate information and md5
    QString mStrMach,mStrRand,mStrOpen,mStrNum,mStrLen,mStrYear,mStrMon,mStrDay,mStrMd5;

    mStrMach = arrEdit.at(INSTALL_EDIT_MACH_CODE)->text();
    mStrRand = mInputEdit[0]->left(4);
    mStrOpen = mInputEdit[1]->left(2);
    mStrNum = mInputEdit[2]->mid(2,2);
    mStrLen = mInputEdit[2]->left(2);
    mStrYear = mInputEdit[1]->right(3);
    mStrMon = mInputEdit[0]->right(1) + mInputEdit[3]->right(1);
    mStrDay = mInputEdit[2]->right(1) + mInputEdit[4]->right(1);
    mStrMd5 = mInputEdit[3]->left(4) + mInputEdit[4]->left(4);

    //qDebug()<<"::mach="<<mStrMach<<"::rand="<<mStrRand<<"open="<<mStrOpen<<"::num="<<mStrNum<<"::len="<<mStrLen<<"::year="<< mStrYear<<"::mon="<< mStrMon<<"::day="<<mStrDay<<"::md5="<<mStrMd5;
    //to string for md5 check
    QByteArray arrOrgInfo;
    arrOrgInfo.append(mStrRand).append(mStrMach).append(mStrYear).append(mStrMon).append(mStrDay).append(mStrOpen).append(mStrLen).append(mStrNum);
    //qDebug()<<arrOrgInfo;

    //get md5 data
    QByteArray arrMd5Data;
    arrMd5Data = QCryptographicHash::hash(arrOrgInfo,QCryptographicHash::Md5);
    //qDebug()<<arrMd5Data.toHex();

    //use 4 byte only
    QByteArray mMd5Hex;
    for (int mIdx = 0 ; mIdx < 4 ; mIdx++)
    {
        mMd5Hex.append(arrMd5Data.at(mIdx * 4));
    }
    //qDebug()<<mMd5Hex.toHex() ;
    char chHeader = mMd5Hex.at(0);
    chHeader &= 0x0f;
    mMd5Hex.replace(0,1,&chHeader,1);
    //qDebug()<<mMd5Hex.toHex() ;

    quint32 decValue = 0;
    for (int mIdx = 0 ; mIdx < mMd5Hex.size(); mIdx++)
    {
        char mcar = mMd5Hex.at(mIdx);
        decValue <<= 8;
        decValue += (unsigned char)mcar;
    }

    decValue %= 100000000;
    //qDebug()<<decValue;

    //check here
    if(mStrMd5.toULong() != decValue)
    {
        sterror->setText(QApplication::translate("CSystemInstall", "Please input the correct identity code!" )+ '2' );
        return;
    }

    //Decode information
    g_dbsys.operationx.cState = mStrOpen.toUInt() /50;
    g_dbsys.operationx.cPeriods = mStrNum.toUInt() / 8 + 1;
    g_dbsys.operationx.cPeriodLength = 12 - mStrLen.toUInt()  / 8;
    g_dbsys.dateStart.year = mStrYear.toUInt()  / 7;
    g_dbsys.dateStart.month =  mStrMon.toUInt()  / 8 + 1;
    g_dbsys.dateStart.day =  mStrDay.toUInt()  / 3 + 1;

    qDebug()<<"open="<<g_dbsys.operationx.cState<<"::num="<<g_dbsys.operationx.cPeriods<<"::len="<<g_dbsys.operationx.cPeriodLength<<"::year="<< g_dbsys.dateStart.year<<"::mon="<< g_dbsys.dateStart.month<<"::day="<<g_dbsys.dateStart.day;
    //check information valid
    if((g_dbsys.operationx.cState != 0) && (g_dbsys.operationx.cState != 1))
    {
        sterror->setText(QApplication::translate("CSystemInstall", "State Error!" ));
        return;
    }

    if((g_dbsys.operationx.cPeriods < 1) || (g_dbsys.operationx.cPeriods > INSTALL_PERIOD_MAX))
    {
        sterror->setText(QApplication::translate("CSystemInstall", "Periods out of range!" ));
        return;
    }

    if((g_dbsys.operationx.cPeriodLength < 1) || (g_dbsys.operationx.cPeriodLength > INSTALL_PERIOD_MONTH_MAX))
    {
        sterror->setText(QApplication::translate("CSystemInstall", "Period length error!" ));
        return;
    }

    QDate mDate;
    mDate.setDate(g_dbsys.dateStart.year,g_dbsys.dateStart.month,g_dbsys.dateStart.day);
    if(!mDate.isValid())
    {
        sterror->setText(QApplication::translate("CSystemInstall", "Enter dates illegal" ));
        return;
    }

    QTime mTime;
    mTime.setHMS(g_dbsys.operationx.tHour,g_dbsys.operationx.tMinute,0);
    if(!mTime.isValid())
    {
        sterror->setText(QApplication::translate("CSystemInstall", "Enter time illegal" ));
        return;
    }

    //storage information to disk,save
    g_dbsys.operationx.cNowNum = 1;
    g_dbsys.dateStart.year = g_dbsys.dateStart.year ;
    g_dbsys.dateStart.month = g_dbsys.dateStart.month;
    g_dbsys.dateStart.day = g_dbsys.dateStart.day;

    g_systemDb->SaveSystemCfg("operationx/cPeriods", g_dbsys.operationx.cPeriods);
    g_systemDb->SaveSystemCfg("operationx/cPeriodLength", g_dbsys.operationx.cPeriodLength);
    g_systemDb->SaveSystemCfg("operationx/tHour", g_dbsys.operationx.tHour);
    g_systemDb->SaveSystemCfg("operationx/tMinute", g_dbsys.operationx.tMinute);
    g_systemDb->SaveSystemCfg("operationx/wIdentifyCode", g_dbsys.operationx.wIdentifyCode);
    g_systemDb->SaveSystemCfg("operationx/cNowNum", g_dbsys.operationx.cNowNum);

    g_systemDb->SaveSystemCfg("dateStart/year", g_dbsys.dateStart.year);
    g_systemDb->SaveSystemCfg("dateStart/month", g_dbsys.dateStart.month);
    g_systemDb->SaveSystemCfg("dateStart/day", g_dbsys.dateStart.day);

    g_systemDb->SaveSystemCfg("dateStart/year", g_dbsys.dateStart.year);
    g_systemDb->SaveSystemCfg("dateStart/month", g_dbsys.dateStart.month);
    g_systemDb->SaveSystemCfg("dateStart/day", g_dbsys.dateStart.day);

    //20160912 only valid passwd can save data to disk.
    g_dbsys.utility.mTryTimes = 12;
    g_systemDb->SaveSystemCfg("utility/mTryTimes",g_dbsys.utility.mTryTimes);
    g_systemDb->SaveSystemCfg("operationx/cState",g_dbsys.operationx.cState);

    sterror->setStyleSheet("color : green");
    sterror->setText(QApplication::translate("CSystemInstall", "Save Successfully" ));

    //fresh information
    FreshInformation();

    //remove the password skip file.
    QFile::remove(QCoreApplication::applicationDirPath() +"/skip_password");

    g_systemDb->SaveSystemCfg("operationx/keyInstalled",1);
    g_systemDb->SaveSystemCfg("operationx/key1", *mInputEdit[0] );
    g_systemDb->SaveSystemCfg("operationx/key2", *mInputEdit[1] );
    g_systemDb->SaveSystemCfg("operationx/key3", *mInputEdit[2] );
    g_systemDb->SaveSystemCfg("operationx/key4", *mInputEdit[3] );
    g_systemDb->SaveSystemCfg("operationx/key5", *mInputEdit[4] );

    //kill the function for setting of time,function of update
    g_systemDb->m_bCanSaveDate = false;
    g_systemDb->m_bCanUpdate = false;

    //enable exit to this page
    g_dbsys.operationx.keyNeed = false;
}
bool CSystemInstall2::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        for(int mIdx = INSTALL_EDIT_CODE_0 ; mIdx <= INSTALL_EDIT_CODE_4 ; mIdx++)
        {
            if(watched ==arrEdit.at(mIdx))
            {
                arrEdit.at(m_iFocusCurrent)->setStyleSheet("background-color : white ; color : black");
                m_iFocusCurrent = mIdx;
                m_strKeyBuff = "";
                sterror->setText("");
                arrEdit.at(m_iFocusCurrent)->setText("");
                arrEdit.at(m_iFocusCurrent)->setStyleSheet("background-color : white ; color : black;border:2px solid green");
                arrEdit.at(m_iFocusCurrent)->setFocus();
                break;
            }
        }
    }

    return QWidget::eventFilter(watched,event);
}
void CSystemInstall2::keyPressEvent( QKeyEvent * event )
{

    int mKey = event->key();
    switch (mKey) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        break;

    case Qt::Key_Backspace:
        m_strKeyBuff.chop( 1);
        arrEdit.at(m_iFocusCurrent)->setText(m_strKeyBuff);

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
        if(m_strKeyBuff.length() < INSTALL_NUM_PER_EDIT)
        {
            m_strKeyBuff.append(event->key());
            arrEdit.at(m_iFocusCurrent)->setText(m_strKeyBuff);
        }else
        {
            if(m_iFocusCurrent < INSTALL_EDIT_CODE_4)
            {
                arrEdit.at(m_iFocusCurrent++)->setStyleSheet("background-color : white ; color : black");
                arrEdit.at(m_iFocusCurrent)->setStyleSheet("background-color : white ; color : black;border:2px solid green");
                m_strKeyBuff = "";
                m_strKeyBuff.append(event->key());
                arrEdit.at(m_iFocusCurrent)->setText(m_strKeyBuff);
            }
        }
        break;
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
