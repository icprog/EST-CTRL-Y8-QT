#include "system_confirm2.h"

#include "stdio.h"
#include "sys_database.h"
#include "resource_manager.h"

#include <QSettings>
#include <QCryptographicHash>



CSystemConfirm2::CSystemConfirm2( QWidget* parent):
    CSystemBase(parent)
{
    setObjectName("CSystemConfirm");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemConfirm", "New Password Confirm"));

    QLabel * pLabel;

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(0, 60, 600, 40));
    pLabel->setAlignment(Qt::AlignCenter);
    pLabel->setStyleSheet("color : blue");
    pLabel->setText(QApplication::translate("CSystemConfirm", "EST (SHANGHAI) MEDICAL EQUIPMENT CO.,LTD" ));
    arrLabel.append(pLabel);        //0

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 100, 150, 24));
    pLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    pLabel->setText(QApplication::translate("CSystemConfirm", "SN:" ));
    arrLabel.append(pLabel);        //1

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(72, 100, 290, 32));
    pLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    pLabel->setStyleSheet("background-color : white;border:1px solid green");
    arrLabel.append(pLabel);        //2

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 140, 150, 24));
    pLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    pLabel->setText(QApplication::translate("CSystemConfirm", "Confirm Date:" ));
    arrLabel.append(pLabel);        //3

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(180, 140, 40, 32));
    pLabel->setStyleSheet("background-color : gray;border:1px solid black");
    pLabel->setAlignment(Qt::AlignCenter);
    arrLabel.append(pLabel);        //4

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(223, 140, 16, 28));
    pLabel->setAlignment(Qt::AlignCenter);
    pLabel->setText("-");
    pLabel->lower();
    arrLabel.append(pLabel);        //5

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(240, 140, 40, 32));
    pLabel->setStyleSheet("background-color : gray;border:1px solid black");
    pLabel->setAlignment(Qt::AlignCenter);
    arrLabel.append(pLabel);        //6

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(282, 140, 16, 28));
    pLabel->setAlignment(Qt::AlignCenter);
    pLabel->setText("-");
    pLabel->lower();
    arrLabel.append(pLabel);        //7

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(300, 140, 40, 32));
    pLabel->setStyleSheet("background-color : gray;border:1px solid black");
    pLabel->setAlignment(Qt::AlignCenter);
    arrLabel.append(pLabel);        //8

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 180, 150, 24));
    pLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    pLabel->setText(QApplication::translate("CSystemConfirm", "Machine Code:" ));
    arrLabel.append(pLabel);        //9

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(180, 180, 100, 32));
    pLabel->setStyleSheet("background-color : gray;border:1px solid black");
    pLabel->setAlignment(Qt::AlignCenter);
    arrLabel.append(pLabel);        //10

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 220, 150, 24));
    pLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    pLabel->setText(QApplication::translate("CSystemConfirm", "Current Period:" ));
    arrLabel.append(pLabel);        //11

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(180, 220, 60, 32));
    pLabel->setStyleSheet("background-color : gray;border:1px solid black");
    pLabel->setAlignment(Qt::AlignCenter);
    arrLabel.append(pLabel);        //12

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 260, 150, 24));
    pLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    pLabel->setText(QApplication::translate("CSystemConfirm", "Periods:" ));
    arrLabel.append(pLabel);        //13

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(180, 260, 60, 32));
    pLabel->setStyleSheet("background-color : gray;border:1px solid black");
    pLabel->setAlignment(Qt::AlignCenter);
    arrLabel.append(pLabel);        //14

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 300, 150, 24));
    pLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    pLabel->setText(QApplication::translate("CSystemConfirm", "Password:" ));
    arrLabel.append(pLabel);        //15

    edPassword = new QLabel(this);
    edPassword->setLineWidth(2);
    edPassword->setFrameShape(QFrame::Panel);
    edPassword->setGeometry(QRect(180, 300, 120, 32));
    edPassword->setStyleSheet("background-color : white ;color : green");
    edPassword->installEventFilter(this);
    edPassword->setAlignment(Qt::AlignCenter);

    stinfo = new QLabel(this);
    stinfo->setGeometry(QRect(200, 340, 400, 35));
    stinfo->setStyleSheet("color : red");

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 370, 151, 40));
    pLabel->setText(QApplication::translate("CSystemConfirm", "Contact information:" ));
    arrLabel.append(pLabel);        //16

    mLine1 = new QFrame(this);
    mLine1->setGeometry(QRect(50, 405, 500, 10));
    mLine1->setFrameShape(QFrame::HLine);
    mLine1->setFrameShadow(QFrame::Sunken);
    mLine1->raise();

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 410, 181, 40));
    pLabel->setText(QApplication::translate("CSystemConfirm", "Manufacturer Tel:" ));
    arrLabel.append(pLabel);        //17

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(220, 420, 200, 32));
    pLabel->setStyleSheet("background-color : gray;border:1px solid black");
    arrLabel.append(pLabel);        //18

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(30, 450, 171, 40));
    pLabel->setText(QApplication::translate("CSystemConfirm", "Sale Tel:" ));
    arrLabel.append(pLabel);        //19

    pLabel = new QLabel(this);
    pLabel->setGeometry(QRect(220, 460, 200, 32));
    pLabel->setStyleSheet("background-color : gray;border:1px solid black");
    arrLabel.append(pLabel);        //20

    btOk = new CButtonStable(this);
    btOk->setGeometry(QRect(425, 525, 100, 60));
    btOk->setStyleSheet("QPushButton{background-color:cyan}");
    btOk->setText(QApplication::translate("CSystemConfirm", "OK" ));

    btContinueUse = new CButtonStable(this);
    btContinueUse->setGeometry(QRect(75, 525, 100, 60));
    btContinueUse->setStyleSheet("QPushButton{background-color:darkRed}");
    btContinueUse->setText(QApplication::translate("CSystemConfirm", "Emergency" ));

    btnExit->setGeometry(QRect(200, 525, 120, 60));

    connect(btOk,SIGNAL(pressed()),this,SLOT(click()) );
    connect(btContinueUse,SIGNAL(pressed()),this,SLOT(OnEmergencyUse()) );

    translateFontSize( this );

    setVisible(false);
}


void CSystemConfirm2::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    QString mStr;

    QFile fileMechCode(QCoreApplication::applicationDirPath() +"/MachCode");
    char mBufCode[MACHINE_CODE_LEN + 1];
    memset(mBufCode,0,MACHINE_CODE_LEN + 1);

    //display the machine code in the file
    if(fileMechCode.exists())
    {
        fileMechCode.open(QFile::ReadOnly);
        fileMechCode.read(mBufCode,MACHINE_CODE_LEN);
        fileMechCode.close();
        arrLabel.at(10)->setText(mBufCode);

        mStr = g_systemDb->getSystemCfg("operationx/key1","00000").toString() + "-";
        mStr += g_systemDb->getSystemCfg("operationx/key2","00000").toString()+ "-";
        mStr +=  g_systemDb->getSystemCfg("operationx/key3","00000").toString()+ "-";
        mStr += g_systemDb->getSystemCfg("operationx/key4","00000").toString()+ "-";
        mStr += g_systemDb->getSystemCfg("operationx/key5","00000").toString();
        arrLabel.at(2)->setText(mStr);

    } else
    {
        mStr.sprintf("%s", g_dbsys.dbsystem.machine2);
        arrLabel.at(10)->setText(mStr);
    }

    mStr.setNum(g_dbsys.dateStart.year);
    arrLabel.at(4)->setText(mStr);

    mStr.setNum(g_dbsys.dateStart.month);
    arrLabel.at(6)->setText(mStr);

    mStr.setNum(g_dbsys.dateStart.day);
    arrLabel.at(8)->setText(mStr);

    mStr.setNum(g_dbsys.operationx.cNowNum);
    arrLabel.at(12)->setText(mStr);

    mStr.setNum(g_dbsys.operationx.cPeriods);
    arrLabel.at(14)->setText(mStr);

    QSettings * configClientInfo = new QSettings(QCoreApplication::applicationDirPath() +"/clientinfo.ini",QSettings::IniFormat);

    QString telManufacture  = configClientInfo->value("/client/telManufacture").toString();
    QString telSeller       = configClientInfo->value("/client/telSeller").toString();

    arrLabel.at(18)->setText(telManufacture);
    arrLabel.at(20)->setText(telSeller);

    btnExit->setText(QApplication::translate("CSystemConfirm", "Times:") +   mStr.setNum(g_dbsys.utility.mTryTimes));

    edPassword->setText("0");
    stinfo->setText("");

    if (g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad=new CSystemImepad(this,false);

    g_systemPad->move(370,110);
    g_systemPad->show();

    grabKeyboard();
}

void CSystemConfirm2::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);

    releaseKeyboard();
}

bool CSystemConfirm2::eventFilter(QObject *watched, QEvent *event)
{
    QString mStr;
    if(watched==edPassword)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            mStr = edPassword->text();
            stinfo->setText("");
            edPassword->setText("");
            m_strKeyBuff = "";
        }
    }

    return QWidget::eventFilter(watched,event);
}
void CSystemConfirm2::keyPressEvent( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Backspace)
    {
        int iStrLen = m_strKeyBuff.length();
        if(iStrLen > 0)
        {
            m_strKeyBuff.remove( iStrLen - 1,1);
            edPassword->setText(m_strKeyBuff);
        }
    }else if(event->key() == Qt::Key_Close)
    {
    }else
    {
        if(m_strKeyBuff.length() < 8 )
            m_strKeyBuff.append(event->key());

        edPassword->setText(m_strKeyBuff);
    }
}

void CSystemConfirm2::OnEmergencyUse()
{

    if(g_dbsys.utility.mTryTimes > 0)
    {
        g_dbsys.utility.mTryTimes--;

        g_dbsys.operation.bTimeout = false;
        //g_systemDb->SaveSystemCfg("operation/bTimeout",g_dbsys.operation.bTimeout);   //do not save to disk,change ram only
        g_systemDb->SaveSystemCfg("utility/mTryTimes",g_dbsys.utility.mTryTimes);

        QString mStr;
        mStr.setNum(g_dbsys.utility.mTryTimes);
        btContinueUse->setText(mStr);

        this->hide();
        emit ViewChange(VIEW_MAIN);
    }else
    {
        stinfo->setText(QApplication::translate("CSystemConfirm", "Invalid Password!" ));
        btContinueUse->setVisible(false);
    }
}

void CSystemConfirm2::click()
{

    if(sender() == btOk)
    {
        int pwdCtr;

        pwdCtr = PeriodPassx(edPassword->text().toInt()) ;

        if ( pwdCtr > g_dbsys.operationx.cPeriods)
        {
            stinfo->setText(QApplication::translate("CSystemConfirm", "Invalid Password!" ));
        }else
        {
            g_dbsys.operation.bTimeout      = false;
            g_dbsys.operationx.cNowNum  = pwdCtr;
            g_dbsys.operationx.cNowNum++;
            if (g_dbsys.operationx.cNowNum > g_dbsys.operationx.cPeriods)
            {
                g_dbsys.operationx.cState           = 0;
                g_dbsys.operationx.wIdentifyCode    = 0;
            }

            g_systemDb->SaveSystemCfg("operationx/cNowNum",g_dbsys.operationx.cNowNum);
            g_systemDb->SaveSystemCfg("operationx/cState",g_dbsys.operationx.cState);
            g_systemDb->SaveSystemCfg("operationx/wIdentifyCode",g_dbsys.operationx.wIdentifyCode);

            this->hide();
            emit ViewChange(VIEW_MAIN);
        }
    }
}

unsigned int CSystemConfirm2::PeriodPassx(unsigned int password)
{
    int pwdCtr = g_dbsys.operationx.cNowNum;
    /*
    QString strSN;
    strSN += g_systemDb->getSystemCfg("operationx/key1","00000").toString() + "-";
    strSN += g_systemDb->getSystemCfg("operationx/key2","00000").toString() + "-";
    strSN +=  g_systemDb->getSystemCfg("operationx/key3","00000").toString() + "-";
    strSN += g_systemDb->getSystemCfg("operationx/key4","00000").toString() + "-";
    strSN += g_systemDb->getSystemCfg("operationx/key5","00000").toString();

    qDebug() << strSN;
*/
    QByteArray arrMd5Data;
    QString mStr;
    while(pwdCtr <= g_dbsys.operationx.cPeriods )
    {
        QByteArray arrOrgInfo,mMd5Hex;
        arrOrgInfo.append(arrLabel.at(2)->text()).append(arrLabel.at(10)->text()).append(mStr.sprintf("%02u",pwdCtr));

        arrMd5Data = QCryptographicHash::hash(arrOrgInfo,QCryptographicHash::Md5);

        for (int mIdx = 0 ; mIdx < 4 ; mIdx++)
        {
            mMd5Hex.append(arrMd5Data.at(mIdx * 4));
        }

        char chHeader = mMd5Hex.at(0);
        chHeader &= 0x0f;
        mMd5Hex.replace(0,1,&chHeader,1);

        quint32 decValue = 0;
        for (int mIdx = 0 ; mIdx < mMd5Hex.size(); mIdx++)
        {
            char mcar = mMd5Hex.at(mIdx);
            decValue <<= 8;
            decValue += (unsigned char)mcar;
        }

        decValue %= 100000000;

        if(decValue == password)
            break;

        pwdCtr++;
    }

    return pwdCtr;
}




