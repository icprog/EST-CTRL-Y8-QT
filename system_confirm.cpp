#include "system_confirm.h"

#include "stdio.h"
#include "sys_database.h"
#include "resource_manager.h"

#include <QSettings>

CSystemConfirm::CSystemConfirm( QWidget* parent):
    CSystemBase(parent)
{
    setObjectName("CSystemConfirm");

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemConfirm", "New Password Confirm"));

    label0 = new QLabel(this);
    label0->setGeometry(QRect(0, 60, 600, 40));
    label0->setAlignment(Qt::AlignCenter);
    label0->setStyleSheet("color : blue");

    label1 = new QLabel(this);
    label1->setGeometry(QRect(30, 110, 150, 24));
    label1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    label2 = new QLabel(this);
    label2->setGeometry(QRect(180, 110, 130, 32));
    label2->setStyleSheet("background-color : white");

    label3 = new QLabel(this);
    label3->setGeometry(QRect(30, 160, 150, 24));
    label3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    label4 = new QLabel(this);
    label4->setGeometry(QRect(180, 160, 45, 32));
    label4->setStyleSheet("background-color : white");

    label5 = new QLabel(this);
    label5->setGeometry(QRect(243, 160, 45, 32));
    label5->setStyleSheet("background-color : white");

    label6 = new QLabel(this);
    label6->setGeometry(QRect(305, 160, 45, 32));
    label6->setStyleSheet("background-color : white");

    label7 = new QLabel(this);
    label7->setGeometry(QRect(30, 210, 150, 24));
    label7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    label8 = new QLabel(this);
    label8->setGeometry(QRect(228, 160, 16, 28));
    label8->setAlignment(Qt::AlignCenter);

    label9 = new QLabel(this);
    label9->setGeometry(QRect(286, 160, 16, 28));
    label9->setAlignment(Qt::AlignCenter);

    label10 = new QLabel(this);
    label10->setGeometry(QRect(355, 160, 155, 22));
    label10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    label11 = new QLabel(this);
    label11->setGeometry(QRect(180, 210, 80, 32));
    label11->setStyleSheet("background-color : white");

    label12 = new QLabel(this);
    label12->setGeometry(QRect(30, 260, 150, 24));
    label12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    label13 = new QLabel(this);
    label13->setGeometry(QRect(180, 260, 80, 32));
    label13->setStyleSheet("background-color : white");

    label14 = new QLabel(this);
    label14->setGeometry(QRect(30, 310, 150, 24));
    label14->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    label20 = new QLabel(this);
    label20->setGeometry(QRect(30, 370, 151, 40));

    label21 = new QLabel(this);
    label21->setGeometry(QRect(30, 410, 181, 40));

    label22 = new QLabel(this);
    label22->setGeometry(QRect(30, 450, 171, 40));

    label23 = new QLabel(this);
    label23->setGeometry(QRect(220, 420, 200, 32));
    label23->setStyleSheet("background-color : white");

    label24 = new QLabel(this);
    label24->setGeometry(QRect(220, 460, 200, 32));
    label24->setStyleSheet("background-color : white");

    stinfo = new QLabel(this);
    stinfo->setGeometry(QRect(200, 370, 400, 35));
    stinfo->setStyleSheet("color : red");

    btOk = new CButtonStable(this);
    btOk->setGeometry(QRect(425, 525, 100, 60));
    btOk->setStyleSheet("QPushButton{background-color:cyan}");

    btContinueUse = new CButtonStable(this);
    btContinueUse->setGeometry(QRect(75, 525, 100, 60));
    btContinueUse->setStyleSheet("QPushButton{background-color:darkRed}");

    btnExit->setGeometry(QRect(200, 525, 120, 60));

    label0->setText(QApplication::translate("CSystemConfirm", "EST (SHANGHAI) MEDICAL EQUIPMENT CO.,LTD" ));
    label1->setText(QApplication::translate("CSystemConfirm", "Machine Code:" ));
    label3->setText(QApplication::translate("CSystemConfirm", "Manufacture Date:" ));
    label7->setText(QApplication::translate("CSystemConfirm", "Current Period:" ));
    label8->setText("-");
    label9->setText("-");
    label10->setText(QApplication::translate("CSystemConfirm", "(YY-MM-DD)" ));
    label12->setText(QApplication::translate("CSystemConfirm", "Periods:" ));
    label14->setText(QApplication::translate("CSystemConfirm", "Password:" ));
    label20->setText(QApplication::translate("CSystemConfirm", "Contact information:" ));
    label21->setText(QApplication::translate("CSystemConfirm", "Manufacturer Tel:" ));
    label22->setText(QApplication::translate("CSystemConfirm", "Sale Tel:" ));
    btOk->setText(QApplication::translate("CSystemConfirm", "OK" ));
    btContinueUse->setText(QApplication::translate("CSystemConfirm", "Emergency" ));

    mLine1 = new QFrame(this);
    mLine1->setGeometry(QRect(50, 360, 500, 10));
    mLine1->setFrameShape(QFrame::HLine);
    mLine1->setFrameShadow(QFrame::Sunken);

    edPassword = new QLabel(this);
    edPassword->setLineWidth(2);
    edPassword->setFrameShape(QFrame::Panel);
    edPassword->setGeometry(QRect(180, 310, 140, 32));
    edPassword->setStyleSheet("background-color : white ;color : green");
    edPassword->installEventFilter(this);

    connect(btOk,SIGNAL(pressed()),this,SLOT(click()) );
    connect(btContinueUse,SIGNAL(pressed()),this,SLOT(OnEmergencyUse()) );

    translateFontSize( this );

    setVisible(false);
}


void CSystemConfirm::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    QString mStr;
    mStr.sprintf("%s", g_dbsys.dbsystem.machine2);
    label2->setText(mStr);

    mStr.setNum(g_dbsys.dateOut.year);
    label4->setText(mStr);

    mStr.setNum(g_dbsys.dateOut.month);
    label5->setText(mStr);

    mStr.setNum(g_dbsys.dateOut.day);
    label6->setText(mStr);

    mStr.setNum(g_dbsys.operationx.cNowNum);
    label11->setText(mStr);

    mStr.setNum(g_dbsys.operationx.cPeriods);
    label13->setText(mStr);

    QSettings * configClientInfo = new QSettings(QCoreApplication::applicationDirPath() + "/clientinfo.ini",QSettings::IniFormat);

    QString telManufacture  = configClientInfo->value("/client/telManufacture").toString();
    QString telSeller       = configClientInfo->value("/client/telSeller").toString();

    label23->setText(telManufacture);
    label24->setText(telSeller);

    btnExit->setText(QApplication::translate("CSystemConfirm", "Times:") +   mStr.setNum(g_dbsys.utility.mTryTimes));

    edPassword->setText("0");
    stinfo->setText("");

    if (g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad=new CSystemImepad(this);

}

void CSystemConfirm::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}

bool CSystemConfirm::eventFilter(QObject *watched, QEvent *event)
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

            g_systemPad->move(350,110);
            g_systemPad->show();
        }
    }

    return QWidget::eventFilter(watched,event);
}
void CSystemConfirm::keyPressEvent( QKeyEvent * event )
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

void CSystemConfirm::OnEmergencyUse()
{

    if(g_dbsys.utility.mTryTimes > 0)
    {
        g_dbsys.utility.mTryTimes--;

        g_dbsys.operation.bTimeout = false;
        //g_systemDb->SaveSystemCfg("operation/bTimeout",g_dbsys.operation.bTimeout);       //do not save to disk,change ram only
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

void CSystemConfirm::click()
{

    unsigned int wValue;
    int i;
    if(sender() == btOk)
    {
        wValue = edPassword->text().toInt();
        i = PeriodPassx(wValue) ;

        if ( i > g_dbsys.operationx.cPeriods)
        {
            stinfo->setText(QApplication::translate("CSystemConfirm", "Invalid Password!" ));
        }else
        {
            g_dbsys.operation.bTimeout = false;
            g_dbsys.operationx.cNowNum=i;
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

int CSystemConfirm::transtoword(char* p)
{
    int w=0;
    while (*p){
        if (*p<='9' && *p>='0'){
            w=w*10+(*p-'0');
        }
        p++;
    }
    return w;
}

unsigned int CSystemConfirm::PeriodPassx(unsigned int password)
{
    unsigned int Periods[50]={78439121,23680729,57294760,56722311,29862580,
                              69810549,15876621,42198890,23874001,41298300,
                              44619805,18710659,76701648,36890468,89164801,
                              77809168,35591975,76917559,97116554,66154075,
                              93847512,54823165,69121265,67813556,57379834,
                              15769880,97613468,97633310,16687146,80362582,
                              98977755,24566713,47623763,13267125,46583256,
                              32876550,63165237,65223543,83736523,49876871,
                              32476598,73645287,48645876,16332538,96542587,
                              27645467,23765905,64556253,87638765,41854342};
    int k0=23;
    int k1=19;
    int k2=17;
    int k3=13;
    int k4=11;
    int k5=7;
    int k6=3;
    int k7=1;
    int i = g_dbsys.operationx.cNowNum;

    unsigned int dwOutNo = transtoword( g_dbsys.dbsystem.machine2);

    char cOutNo[9];
    sprintf(cOutNo,"%u",dwOutNo);

    for (unsigned int mIdx = 0 ; mIdx < 8 - strlen(cOutNo); mIdx++)
    {
        dwOutNo = dwOutNo*10;
    }

    unsigned int dwDate = g_dbsys.dateOut.year*10000 + g_dbsys.dateOut.month * 100 + g_dbsys.dateOut.day;
    char cOutDate[9];
    sprintf(cOutDate,"%u",dwDate);
    for (unsigned int mIdx = 0 ; mIdx < 8-strlen(cOutDate) ; mIdx++)
    {
        dwDate = dwDate*10;
    }

    unsigned int dwCode = g_dbsys.operationx.wIdentifyCode;
    char cIdentifyCode[9];
    sprintf(cIdentifyCode,"%u",dwCode);
    for(unsigned int mIdx = 0 ; mIdx < 8-strlen(cIdentifyCode) ; mIdx++)
    {
        dwCode = dwCode*10;
    }

    while (i <= g_dbsys.operationx.cPeriods)
    {
        unsigned int dwValue=(dwOutNo ^ dwDate ^Periods[i-1] ^ dwCode);
        unsigned int dwValuex=(12345678 ^ dwDate ^Periods[i-1]);
        char cValue[12],cValuex[12];

        sprintf(cValue,"%u",dwValue);
        if(strlen(cValue)<8)
            for(unsigned int m=0;m<8-strlen(cValue);m++){
                dwValue=dwValue*10;
            }
        sprintf(cValuex,"%u",dwValuex);
        if(strlen(cValuex)<8)
            for(unsigned int n=0;n<8-strlen(cValuex);n++){
                dwValuex=dwValuex*10;
            }
        sprintf(cValue,"%u",dwValue);
        sprintf(cValuex,"%u",dwValuex);
        unsigned int    x= ((cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*k7
                            +(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*k6
                            +(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*k5
                            +(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*k4
                            +(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*k3
                            +(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*k2
                            +(cValue[6]-'0')*(cValue[6]-'0')*k1
                            +(cValue[7]-'0')*k0)%9+1;

        unsigned int   x1=((cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*k6
                           +(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*k5
                           +(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*k4
                           +(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*k3
                           +(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*k2
                           +(cValue[5]-'0')*(cValue[5]-'0')*k1
                           +(cValue[6]-'0')*k0
                           +(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*k7)%10;

        unsigned int   x2=((cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*k5
                           +(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*k4
                           +(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*k3
                           +(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*k2
                           +(cValue[4]-'0')*(cValue[4]-'0')*k1
                           +(cValue[5]-'0')*k0
                           +(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*k7
                           +(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*k6)%10;

        unsigned int   x3=((cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*k4
                           +(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*k3
                           +(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*k2
                           +(cValue[3]-'0')*(cValue[3]-'0')*k1
                           +(cValue[4]-'0')*k0
                           +(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*k7
                           +(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*k6
                           +(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*k5)%10;

        unsigned int   x4=((cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*k3
                           +(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*k2
                           +(cValue[2]-'0')*(cValue[2]-'0')*k1
                           +(cValue[3]-'0')*k0
                           +(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*k7
                           +(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*k6
                           +(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*k5
                           +(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*k4)%10;

        unsigned int   x5=((cValue[0]-'0')*(cValue[0]-'0')*(cValue[0]-'0')*k2
                           +(cValue[1]-'0')*(cValue[1]-'0')*k1
                           +(cValue[2]-'0')*k0
                           +(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*k7
                           +(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*k6
                           +(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*k5
                           +(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*k4
                           +(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*k3)%10;

        unsigned int   x6=((cValue[0]-'0')*(cValue[0]-'0')*k1
                           +(cValue[1]-'0')*k0
                           +(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*k7
                           +(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*k6
                           +(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*k5
                           +(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*k4
                           +(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*k3
                           +(cValue[7]-'0')*(cValue[7]-'0')*(cValue[7]-'0')*k2)%10;

        unsigned int   x7=((cValue[0]-'0')*k0
                           +(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*(cValue[1]-'0')*k7
                           +(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*(cValue[2]-'0')*k6
                           +(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*(cValue[3]-'0')*k5
                           +(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*(cValue[4]-'0')*k4
                           +(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*(cValue[5]-'0')*k3
                           +(cValue[6]-'0')*(cValue[6]-'0')*(cValue[6]-'0')*k2
                           +(cValue[7]-'0')*(cValue[7]-'0')*k1)%10;

        //no identify
        unsigned int    y=((cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*k7
                           +(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*k6
                           +(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*k5
                           +(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*k4
                           +(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*k3
                           +(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*k2
                           +(cValuex[6]-'0')*(cValuex[6]-'0')*k1
                           +(cValuex[7]-'0')*k0)%9+1;

        unsigned int   y1=((cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*k6
                           +(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*k5
                           +(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*k4
                           +(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*k3
                           +(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*k2
                           +(cValuex[5]-'0')*(cValuex[5]-'0')*k1
                           +(cValuex[6]-'0')*k0
                           +(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*k7)%10;

        unsigned int   y2=((cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*k5
                           +(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*k4
                           +(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*k3
                           +(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*k2
                           +(cValuex[4]-'0')*(cValuex[4]-'0')*k1
                           +(cValuex[5]-'0')*k0
                           +(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*k7
                           +(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*k6)%10;

        unsigned int   y3=((cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*k4
                           +(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*k3
                           +(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*k2
                           +(cValuex[3]-'0')*(cValuex[3]-'0')*k1
                           +(cValuex[4]-'0')*k0
                           +(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*k7
                           +(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*k6
                           +(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*k5)%10;

        unsigned int   y4=((cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*k3
                           +(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*k2
                           +(cValuex[2]-'0')*(cValuex[2]-'0')*k1
                           +(cValuex[3]-'0')*k0
                           +(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*k7
                           +(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*k6
                           +(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*k5
                           +(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*k4)%10;

        unsigned int   y5=((cValuex[0]-'0')*(cValuex[0]-'0')*(cValuex[0]-'0')*k2
                           +(cValuex[1]-'0')*(cValuex[1]-'0')*k1
                           +(cValuex[2]-'0')*k0
                           +(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*k7
                           +(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*k6
                           +(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*k5
                           +(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*k4
                           +(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*k3)%10;

        unsigned int   y6=((cValuex[0]-'0')*(cValuex[0]-'0')*k1
                           +(cValuex[1]-'0')*k0
                           +(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*k7
                           +(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*k6
                           +(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*k5
                           +(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*k4
                           +(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*k3
                           +(cValuex[7]-'0')*(cValuex[7]-'0')*(cValuex[7]-'0')*k2)%10;

        unsigned int   y7=((cValuex[0]-'0')*k0
                           +(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*(cValuex[1]-'0')*k7
                           +(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*(cValuex[2]-'0')*k6
                           +(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*(cValuex[3]-'0')*k5
                           +(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*(cValuex[4]-'0')*k4
                           +(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*(cValuex[5]-'0')*k3
                           +(cValuex[6]-'0')*(cValuex[6]-'0')*(cValuex[6]-'0')*k2
                           +(cValuex[7]-'0')*(cValuex[7]-'0')*k1)%10;


        unsigned int  jmdwValue,jmdwValuex;
        jmdwValue   = x*10000000+x1*1000000+x2*100000+x3*10000+x4*1000+x5*100+x6*10+x7;
        jmdwValuex  = y*10000000+y1*1000000+y2*100000+y3*10000+y4*1000+y5*100+y6*10+y7;

        if ((jmdwValue == password) || (jmdwValuex == password))
            break;

        i++;
    }

    return i;
}




