#include "./ndt10/motor_ndt10.h"
#include "resource_manager.h"

#include <QSettings>


#define NDT_MOTOR_SOFT_MAX_LENGTH   4

CMotorNdt::CMotorNdt( QWidget* parent):
    CSystemBase(parent)
{

    setObjectName("CMotorNdt");

    resize(600,600);

    m_iFocusCurrent = 0;

    textTitle->setText(QApplication::translate("CMotorNdt", "NDT Soft Limit Setting"));

    lbMin[0] = new QLabel(this);
    lbMin[0]->setGeometry(110,70,80,50);
    lbMin[0]->setText(QApplication::translate("CMotorNdt", "Min Data"));

    lbMax[0] = new QLabel(this);
    lbMax[0]->setGeometry(210,70,80,50);
    lbMax[0]->setText(QApplication::translate("CMotorNdt", "Max Data"));

    lbMin[1] = new QLabel(this);
    lbMin[1]->setGeometry(410,70,80,50);
    lbMin[1]->setText(QApplication::translate("CMotorNdt", "Min Data"));

    lbMax[1] = new QLabel(this);
    lbMax[1]->setGeometry(510,70,80,50);
    lbMax[1]->setText(QApplication::translate("CMotorNdt", "Max Data"));

    //Middle line
    pFrameLine = new QFrame(this);
    pFrameLine->setGeometry(295,55,5,445);
    pFrameLine->setStyleSheet("background-color : rgb(255,232,166) ; border : 1px solid rgb(192,167,118)");

    //save button
    btSave = new CButtonStable(this);
    btSave->setGeometry(425,525,100,60);
    btSave->setText(QApplication::translate("CMotorNdt", "Save"));
    connect(btSave,SIGNAL(pressed()),this,SLOT(OnBtnNdtPressed()));

    lbSave = new QLabel(this);
    lbSave->setGeometry(QRect(0,460,600,40));
    lbSave->setStyleSheet("color:green");
    lbSave->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbSave->setText(QApplication::translate("CMotorNdt", "Data Save Successfully!"));

    //FID//SID
    int mWidAdd;
    for(int mIdx = 0 ; mIdx < (NDT_SOFT_LIMIT_NUMBER -1) ; mIdx++)
    {
        if(mIdx >= 5)
            mWidAdd = 300;
        else
            mWidAdd = 0;

        pLabel[mIdx] = new QLabel(this);
        pLabel[mIdx]->setGeometry(20 + mWidAdd,110 + mIdx%5 * 60,80,50);

        pEditNdt[2*mIdx] = new QLabel(this);
        pEditNdt[2*mIdx]->setGeometry(100 + mWidAdd,110 + mIdx%5 * 60,80,50);
        pEditNdt[2*mIdx]->installEventFilter(this);
        pEditNdt[2*mIdx]->setStyleSheet("background-color : white ; color : darkBlue");
        pEditNdt[2*mIdx]->setFrameShape(QFrame::Panel);
        pEditNdt[2*mIdx]->setLineWidth(2);

        pEditNdt[2*mIdx+1] = new QLabel(this);
        pEditNdt[2*mIdx+1]->setGeometry(200 + mWidAdd,110 + mIdx%5 * 60,80,50);
        pEditNdt[2*mIdx+1]->installEventFilter(this);
        pEditNdt[2*mIdx+1]->setStyleSheet("background-color : white ; color : darkBlue");
        pEditNdt[2*mIdx+1]->setFrameShape(QFrame::Panel);
        pEditNdt[2*mIdx+1]->setLineWidth(2);
    }

    int lastIndex = NDT_SOFT_LIMIT_NUMBER -1;
    pLabel[lastIndex] = new QLabel(this);
    pLabel[lastIndex]->setGeometry(20 + mWidAdd,110 + 5 * 60,80,50);

    pEditNdt[2*lastIndex] = new QLabel(this);
    pEditNdt[2*lastIndex]->setGeometry(100 + mWidAdd,110 + 5 * 60,80,50);
    pEditNdt[2*lastIndex]->installEventFilter(this);
    pEditNdt[2*lastIndex]->setStyleSheet("background-color : white ; color : darkBlue");
    pEditNdt[2*lastIndex]->setFrameShape(QFrame::Panel);
    pEditNdt[2*lastIndex]->setLineWidth(2);

    pEditNdt[2*lastIndex+1] = new QLabel(this);
    pEditNdt[2*lastIndex+1]->setGeometry(200 + mWidAdd,110 + 5 * 60,80,50);
    pEditNdt[2*lastIndex+1]->installEventFilter(this);
    pEditNdt[2*lastIndex+1]->setStyleSheet("background-color : white ; color : darkBlue");
    pEditNdt[2*lastIndex+1]->setFrameShape(QFrame::Panel);
    pEditNdt[2*lastIndex+1]->setLineWidth(2);

    pLabel[0]->setText(QApplication::translate("CMotorNdt", "FID"));
    pLabel[1]->setText(QApplication::translate("CMotorNdt", "SID"));
    pLabel[2]->setText(QApplication::translate("CMotorNdt", "ANG"));
    pLabel[3]->setText(QApplication::translate("CMotorNdt", "CEP"));
    pLabel[4]->setText(QApplication::translate("CMotorNdt", "UID"));
    pLabel[5]->setText(QApplication::translate("CMotorNdt", "DTA"));
    pLabel[6]->setText(QApplication::translate("CMotorNdt", "ROL"));
    pLabel[7]->setText(QApplication::translate("CMotorNdt", "SRL"));
    pLabel[8]->setText(QApplication::translate("CMotorNdt", "RMV"));
    pLabel[9]->setText(QApplication::translate("CMotorNdt", "LMV"));
    pLabel[10]->setText(QApplication::translate("CMotorNdt", "HEI"));

    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnBtnNdtPressed()));

    translateFontSize( this );

    if(!loadSoftLimit(QCoreApplication::applicationDirPath() + "/ndtConfig.ini"))
        saveSoftLimit(QCoreApplication::applicationDirPath() +"/ndtConfig.ini");

    updateSoftLimit(false);      //update values to display

    setVisible(false);

}
CMotorNdt::~CMotorNdt()
{

}
int CMotorNdt::getLimitMin(int motorId)
{
    if(motorId < NDT_SOFT_LIMIT_NUMBER)
        return m_iMotorSoftMin[motorId];
    else
        return 0;
}
int CMotorNdt::getLimitMax(int motorId)
{
    if(motorId < NDT_SOFT_LIMIT_NUMBER)
        return m_iMotorSoftMax[motorId];
    else
        return 0;
}
bool CMotorNdt::saveSoftLimit(QString cfgFile)
{
    QSettings * configNdt = new QSettings(cfgFile,QSettings::IniFormat);

    if(!configNdt)
        return false;

    configNdt->setValue("SoftLimit/fidMin",m_iMotorSoftMin[0] );
    configNdt->setValue("SoftLimit/fidMax",m_iMotorSoftMax[0] );
    configNdt->setValue("SoftLimit/sidMin",m_iMotorSoftMin[1] );
    configNdt->setValue("SoftLimit/sidMax",m_iMotorSoftMax[1] );
    configNdt->setValue("SoftLimit/angMin",m_iMotorSoftMin[2] );
    configNdt->setValue("SoftLimit/angMax",m_iMotorSoftMax[2]);
    configNdt->setValue("SoftLimit/cepMin",m_iMotorSoftMin[3] );
    configNdt->setValue("SoftLimit/cepMax",m_iMotorSoftMax[3]);
    configNdt->setValue("SoftLimit/uidMin",m_iMotorSoftMin[4] );
    configNdt->setValue("SoftLimit/uidMax",m_iMotorSoftMax[4]);
    configNdt->setValue("SoftLimit/dtaMin",m_iMotorSoftMin[5]);
    configNdt->setValue("SoftLimit/dtaMax",m_iMotorSoftMax[5]);
    configNdt->setValue("SoftLimit/rolMin",m_iMotorSoftMin[6]);
    configNdt->setValue("SoftLimit/rolMax",m_iMotorSoftMax[6]);
    configNdt->setValue("SoftLimit/srlMin",m_iMotorSoftMin[7]);
    configNdt->setValue("SoftLimit/srlMax",m_iMotorSoftMax[7]);
    configNdt->setValue("SoftLimit/rmvMin",m_iMotorSoftMin[8] );
    configNdt->setValue("SoftLimit/rmvMax",m_iMotorSoftMax[8] );
    configNdt->setValue("SoftLimit/lmvMin",m_iMotorSoftMin[9] );
    configNdt->setValue("SoftLimit/lmvMax",m_iMotorSoftMax[9] );
    configNdt->setValue("SoftLimit/heiMin",m_iMotorSoftMin[10]);
    configNdt->setValue("SoftLimit/heiMax", m_iMotorSoftMax[10]);

    return true;
}

bool CMotorNdt::loadSoftLimit(QString cfgFile)
{
    if(!QFile::exists(cfgFile))
    {
        //set default value for saving
        m_iMotorSoftMin[0] = 800;           //fid
        m_iMotorSoftMax[0]=1500;
        m_iMotorSoftMin[1]=800;             //sid
        m_iMotorSoftMax[1]=1500;
        m_iMotorSoftMin[2]=0;                   //ang
        m_iMotorSoftMax[2]=90;
        m_iMotorSoftMin[3]=800;             //cep
        m_iMotorSoftMax[3]=1600;
        m_iMotorSoftMin[4]=400;               //uid
        m_iMotorSoftMax[4]=1200;
        m_iMotorSoftMin[5]=0;                   //dta
        m_iMotorSoftMax[5]=0;
        m_iMotorSoftMin[6]=-720;                  //rol
        m_iMotorSoftMax[6]=720;
        m_iMotorSoftMin[7]=-720;                 //srl
        m_iMotorSoftMax[7]=720;
        m_iMotorSoftMin[8]=2500;                   //rmv
        m_iMotorSoftMax[8]=3500;
        m_iMotorSoftMin[9]=2500;            //lmv
        m_iMotorSoftMax[9]=3500;
        m_iMotorSoftMin[10]=500;                  //hei
        m_iMotorSoftMax[10]=1400;

        return false;
    }

    QSettings * configNdt = new QSettings(cfgFile,QSettings::IniFormat);

    if(!configNdt)
        return false;

    m_iMotorSoftMin[0] = configNdt->value("SoftLimit/fidMin","1").toInt();
    m_iMotorSoftMax[0] = configNdt->value("SoftLimit/fidMax","2000").toInt();
    m_iMotorSoftMin[1] = configNdt->value("SoftLimit/sidMin","2").toInt();
    m_iMotorSoftMax[1] = configNdt->value("SoftLimit/sidMax","2100").toInt();
    m_iMotorSoftMin[2] = configNdt->value("SoftLimit/angMin","0").toInt();
    m_iMotorSoftMax[2] = configNdt->value("SoftLimit/angMax","90").toInt();
    m_iMotorSoftMin[3] = configNdt->value("SoftLimit/cepMin","3").toInt();
    m_iMotorSoftMax[3] = configNdt->value("SoftLimit/cepMax","2200").toInt();
    m_iMotorSoftMin[4] = configNdt->value("SoftLimit/uidMin","4").toInt();
    m_iMotorSoftMax[4] = configNdt->value("SoftLimit/uidMax","1200").toInt();
    m_iMotorSoftMin[5] = configNdt->value("SoftLimit/dtaMin","0").toInt();
    m_iMotorSoftMax[5] = configNdt->value("SoftLimit/dtaMax","90").toInt();
    m_iMotorSoftMin[6] = configNdt->value("SoftLimit/rolMin","180").toInt();
    m_iMotorSoftMax[6] = configNdt->value("SoftLimit/rolMax","181").toInt();
    m_iMotorSoftMin[7] = configNdt->value("SoftLimit/srlMin","182").toInt();
    m_iMotorSoftMax[7] = configNdt->value("SoftLimit/srlMax","183").toInt();
    m_iMotorSoftMin[8] = configNdt->value("SoftLimit/rmvMin","5").toInt();
    m_iMotorSoftMax[8] = configNdt->value("SoftLimit/rmvMax","2300").toInt();
    m_iMotorSoftMin[9] = configNdt->value("SoftLimit/lmvMin","6").toInt();
    m_iMotorSoftMax[9] = configNdt->value("SoftLimit/lmvMax","2400").toInt();
    m_iMotorSoftMin[10] = configNdt->value("SoftLimit/heiMin","7").toInt();
    m_iMotorSoftMax[10] = configNdt->value("SoftLimit/heiMax","2500").toInt();

    return true;
}
bool CMotorNdt::updateSoftLimit(bool beStorage)
{
    for(int mIdx = 0 ; mIdx < NDT_SOFT_LIMIT_NUMBER ; mIdx++)
    {

        if(beStorage)       //save data from label
        {
            if(pEditNdt[2*mIdx])
                m_iMotorSoftMin[mIdx] = pEditNdt[2*mIdx]->text().toInt();

            if(pEditNdt[2*mIdx+1])
                m_iMotorSoftMax[mIdx] = pEditNdt[2*mIdx+1]->text().toInt();
        }else               //update data from memory
        {
            if(pEditNdt[2*mIdx])
                pEditNdt[2*mIdx]->setNum(m_iMotorSoftMin[mIdx]);

            if(pEditNdt[2*mIdx+1])
                pEditNdt[2*mIdx+1]->setNum(m_iMotorSoftMax[mIdx]);
        }
    }

    return true;
}
void CMotorNdt::OnBtnNdtPressed()
{

    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_motorMenu);
        return;
    }

    if(sender() == btSave)
    {
        updateSoftLimit(true);

        saveSoftLimit(QCoreApplication::applicationDirPath() +"/ndtConfig.ini");

        lbSave->show();
    }

}
void CMotorNdt::hideEvent(QHideEvent *event)
{
    CSystemBase::hideEvent(event);
}

void CMotorNdt::showEvent(QShowEvent *event)
{

    if(g_systemPad)
    {
        delete g_systemPad;
        g_systemPad = 0;
    }

    g_systemPad = new CSystemImepad(this);

    g_systemDb->g_bDataSaved = false;
    lbSave->hide();

    CSystemBase::showEvent(event);
}

void CMotorNdt::mousePressEvent ( QMouseEvent * /*event*/ )
{

}

bool CMotorNdt::eventFilter(QObject *watched, QEvent *event)
{

    for(int mIdx = 0 ;mIdx < NDT_SOFT_LIMIT_NUMBER * 2 ; mIdx++)
    {
        if(pEditNdt[mIdx] == watched)
        {
            if(event->type()==QEvent::MouseButtonPress)
            {
                //move the number input pad
                if(mIdx < 10)
                    g_systemPad->move(380 ,82);
                else
                    g_systemPad->move(80 ,82);

                //clear the old indicate
                pEditNdt[m_iFocusCurrent]->setStyleSheet("background-color : white ; color : darkBlue");

                //indicate the input box
                pEditNdt[mIdx]->setStyleSheet("background-color : white ; color : green");

                //show the number input pad
                g_systemPad->show();
                m_iFocusCurrent = mIdx;
                m_strKeyBuff = "";

                lbSave->hide();
            }
        }
    }

    return QWidget::eventFilter(watched,event);
}

void CMotorNdt::keyPressEvent ( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Backspace)                                                              //判断是否是退格键
    {
        int iStrLen = m_strKeyBuff.length();

        if(iStrLen > 0)
        {
            m_strKeyBuff.remove( iStrLen - 1,1);
            pEditNdt[m_iFocusCurrent]->setText(m_strKeyBuff);
        }else
            pEditNdt[m_iFocusCurrent]->setText("");

    }else if(event->key() == Qt::Key_Close)
    {
    }else
    {
        if(m_strKeyBuff.length() <NDT_MOTOR_SOFT_MAX_LENGTH)
            m_strKeyBuff.append(event->key());

        pEditNdt[m_iFocusCurrent]->setText(m_strKeyBuff);
    }

}
