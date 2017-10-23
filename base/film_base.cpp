#include <fcntl.h>
#include <sys/ioctl.h>

#include <QSettings>

#include "film_base.h"
#include "resource_manager.h"


CFilmBase::CFilmBase(QWidget *parent) :
    CSystemBase(parent)
{

    resize(600,600);

    m_iFilmState    = FILM_FUNC_NORMAL;    //允许按键扫描
    m_fileKeyBoard  = -1;
    m_fileDevice    = -1;
    keylast         = 0;
    nKey            = 0;
    m_iFocusCurrent = 0;

    m_bIsVisable = false;       //System Key Configuration

    if(!QFile::exists("/sdcard/home/fa/soundkey.wav"))
    {
        QFile inputFile(":/QRes/soundkey.wav");

        inputFile.open(QIODevice::ReadOnly);        // 只读打开
        inputFile.copy("/sdcard/home/fa/soundkey.wav");
        inputFile.close();          // 关闭文本流
    }

    soundKey = new QSound("/sdcard/home/fa/soundkey.wav");
    soundKey->setLoops(2);

    //    soundKey2.setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/soundkey2.wav"));
    //    //循环播放
    //    soundKey2.setLoopCount(1);
    //    //设置音量，0-1
    //    soundKey2.setVolume(0.9f);

    InitFilmBoard();        //初始化按键

    textTitle->setText(QApplication::translate("CFilmBase", "System Key Configuration"));

    line_1 = new QFrame(this);
    line_1->setGeometry(QRect(20, 240, 560, 10));
    line_1->setFrameShape(QFrame::HLine);
    line_1->setFrameShadow(QFrame::Sunken);

    label_test = new QLabel(this);
    label_test->setGeometry(QRect(20, 50, 120, 40));
    label_test->setText(QApplication::translate("CFilmBase", "Key Test:"));
    label_test->lower();

    label_config = new QLabel(this);
    label_config->setGeometry(QRect(20, 200, 200, 40));
    label_config->setText(QApplication::translate("CFilmBase", "Configuration:"));
    label_config->lower();

    label_cur_code = new QLabel(this);
    label_cur_code->setGeometry(QRect(40, 80, 200, 41));
    label_cur_code->setText(QApplication::translate("CFilmBase", "Physical Key Code:"));
    label_cur_code->lower();

    lbCurrentCode = new QLabel(this);
    lbCurrentCode->setGeometry(QRect(250, 80, 50, 40));
    lbCurrentCode->setText(QString());

    label_fun_down = new QLabel(this);
    label_fun_down->setGeometry(QRect(40, 120, 200, 41));
    label_fun_down->setText(QApplication::translate("CFilmBase", "Key Function Down:"));
    label_fun_down->setStyleSheet("color : red");
    label_fun_down->lower();

    lbFunctionDown = new QLabel(this);
    lbFunctionDown->setGeometry(QRect(250, 120, 50, 40));
    lbFunctionDown->setText(QString());
    lbFunctionDown->setStyleSheet("color : red");

    label_fun_up = new QLabel(this);
    label_fun_up->setGeometry(QRect(40, 160, 200, 41));
    label_fun_up->setText(QApplication::translate("CFilmBase", "Key Function Up:"));
    label_fun_up->setStyleSheet("color : blue");
    label_fun_up->lower();

    lbFunctionUp = new QLabel(this);
    lbFunctionUp->setGeometry(QRect(250, 160, 50, 40));
    lbFunctionUp->setText(QString());
    lbFunctionUp->setStyleSheet("color : blue");

    m_btnKeyFunc[FILM_KEY_0031] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_0031]->setGeometry(QRect(70, 260, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_0031],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_0031]->setText("0x0031");

    m_btnKeyFunc[FILM_KEY_0032] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_0032]->setGeometry(QRect(190, 260, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_0032],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_0032]->setText("0x0032");

    m_btnKeyFunc[FILM_KEY_0033] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_0033]->setGeometry(QRect(310, 260, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_0033],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_0033]->setText("0x0033");

    m_btnKeyFunc[FILM_KEY_1012] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_1012]->setGeometry(QRect(430, 260, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_1012],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_1012]->setText("0x1012");

    m_btnKeyFunc[FILM_KEY_1030] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_1030]->setGeometry(QRect(70, 340, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_1030],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_1030]->setText("0x1030");

    m_btnKeyFunc[FILM_KEY_1031] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_1031]->setGeometry(QRect(190, 340, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_1031],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_1031]->setText("0x1031");

    m_btnKeyFunc[FILM_KEY_1032] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_1032]->setGeometry(QRect(310, 340, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_1032],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_1032]->setText("0x1032");

    m_btnKeyFunc[FILM_KEY_1036] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_1036]->setGeometry(QRect(430, 340, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_1036],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_1036]->setText("0x1036");

    m_btnKeyFunc[FILM_KEY_2030] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_2030]->setGeometry(QRect(70, 420, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_2030],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_2030]->setText("0x2030");

    m_btnKeyFunc[FILM_KEY_2031] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_2031]->setGeometry(QRect(190, 420, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_2031],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_2031]->setText("0x2031");

    m_btnKeyFunc[FILM_KEY_2032] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_2032]->setGeometry(QRect(310, 420, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_2032],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_2032]->setText("0x2032");

    m_btnKeyFunc[FILM_KEY_2033] = new CButtonStable(this);
    m_btnKeyFunc[FILM_KEY_2033]->setGeometry(QRect(430, 420, 100, 60));
    connect(m_btnKeyFunc[FILM_KEY_2033],SIGNAL(pressed()),this,SLOT(OnKeyFilterDown()));
    m_btnKeyFunc[FILM_KEY_2033]->setText("0x2033");

    timerFilmLong = new QTimer(this);
    timerFilmLong->setSingleShot(true);
    timerFilmLong->setInterval(TIME_LONG_PRESS);

    timerSoundPlay = new QTimer(this);
    timerSoundPlay->setSingleShot(true);
    timerSoundPlay->setInterval(10);                //10ms后播放声音

    connect(timerSoundPlay,SIGNAL(timeout()),this,SLOT(PlayKeySound()));
    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnFilmExit()));

    setVisible(false);
    translateFontSize(this);

    setStyleSheet("background-color : lightGray");

    KeyFilterInit();                //增加按键屏蔽功能

    memset(m_bufLed,0,8);
    m_ledCounter = 0;
}

void CFilmBase::KeyFilterAdd(int mKey)
{
    if(m_keyFilterCount >= FILM_KEY_MAX)
        return;

    for(int mIdx = 0 ; mIdx < m_keyFilterCount ; mIdx++)
    {
        if(m_keyFilter[mIdx] == mKey)
            return;
    }

    m_keyFilter[m_keyFilterCount] = mKey;
    m_keyFilterCount += 1;

}
void CFilmBase::KeyFilterDel(int mKey)
{
    if(m_keyFilterCount == 0)
        return;

    int mKeyDelIdx = FILM_KEY_MAX;

    for(int mIdx = 0 ; mIdx < m_keyFilterCount ; mIdx++)
    {
        if(m_keyFilter[mIdx] == mKey)
        {
            mKeyDelIdx = mIdx;
            break;
        }
    }

    if(mKeyDelIdx >= FILM_KEY_MAX)
        return;

    for(int mIdx = mKeyDelIdx ; mIdx < FILM_KEY_MAX - 1; mIdx++)
    {
        m_keyFilter[mIdx] = m_keyFilter[mIdx + 1];
    }

    m_keyFilter[FILM_KEY_MAX - 1] = 0;

    m_keyFilterCount -= 1;

}
void CFilmBase::KeyFilterInit()
{
    m_keyFilterCount = 0;                               //初始化相关内存
    m_bLastKeyFiltered = false;             //默认，没有按键被过滤掉

    for(int mIdx = 0 ; mIdx < FILM_KEY_MAX ; mIdx++)
        m_keyFilter[mIdx] = 0;

    mBufKeyConst[FILM_KEY_0031] = 0x0031;
    mBufKeyConst[FILM_KEY_0032] = 0x0032;
    mBufKeyConst[FILM_KEY_0033] = 0x0033;
    mBufKeyConst[FILM_KEY_1012] = 0x1012;
    mBufKeyConst[FILM_KEY_1030] = 0x1030;
    mBufKeyConst[FILM_KEY_1031] = 0x1031;
    mBufKeyConst[FILM_KEY_1032] = 0x1032;
    mBufKeyConst[FILM_KEY_1036] = 0x1036;
    mBufKeyConst[FILM_KEY_2030] = 0x2030;
    mBufKeyConst[FILM_KEY_2031] = 0x2031;
    mBufKeyConst[FILM_KEY_2032] = 0x2032;
    mBufKeyConst[FILM_KEY_2033] = 0x2033;

    QString mKeyTag;
    QSettings * iniKeyFilter = new QSettings(QCoreApplication::applicationDirPath() + "/key_filter.ini",QSettings::IniFormat);
    int mValRes;

    for(int mIdx = 0 ; mIdx < FILM_KEY_MAX ; mIdx++)
    {
        mKeyTag.sprintf("data/key_%04x",mBufKeyConst[mIdx]);

        mValRes = iniKeyFilter->value(mKeyTag,false).toInt();

        if(mValRes == true)
        {
            KeyFilterAdd(mBufKeyConst[mIdx]);
        }
    }
}
void CFilmBase::SendCmdKey(int mKey)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = mKey;

    qDebug() << "CFilmBase::SendCmdKey" << mKey;

    //判断是否初始化完成之前有按键按下
    if(RsMgr->getInitStage() < SYS_START_FINISH)
    {

        qDebug() << "SYS_START_FINISH" << "INIT_STATE_ERROR";

        g_systemDb->setInitState(INIT_STATE_ERROR,INIT_ERROR_FILM_KEY,mKey);
        return;
    }

    //如果串口对象无效，不发送相应的按键
    if(g_taskComCtrl)
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);

}
void CFilmBase::InitFilmBoard()
{

    m_fileKeyBoard = ::open("/dev/wrtc", O_RDWR);

    //for w6410 CPU
    m_fileDevice = ::open("/dev/wrtc", O_RDWR);

    if(!m_fileDevice)
    {
        m_fileDevice = ::open("/dev/cled", O_RDWR);
    }

    if(!m_fileDevice)
    {
        g_systemDb->setInitState(INIT_STATE_ERROR,INIT_ERROR_FILM_KEY,0x21);
        return;
    }

    //for test
    ioctl(m_fileDevice, 8 , false);  //open lcd
    //   ioctl(m_fileDevice, 8 , true);  //open lcd
    ioctl(m_fileDevice, 10, 0);
    ioctl(m_fileDevice, 7 ,0x0007);

}
//薄膜按键LED灯控制
void CFilmBase::filmLed(int )
{
    //if filmLed control too fast ,the sound control will delay.
    //every 5 times control led 1 time.

    int valuecontrol = 0;

    if(m_ledCounter++ < 5)
        return;
    m_ledCounter = 0;

    if(g_systemDb->g_dbMachine.CurrentData[16] == 1)
    {
        valuecontrol |= 0x0001;
        m_bufLed[1] |= 0x0010;
    }else if(g_systemDb->g_dbMachine.CurrentData[16] == 2)
    {
        valuecontrol |= 0x020000;
        m_bufLed[1] ^= 0x0010;
    }else
    {
        m_bufLed[1] &= 0xffef;
    }

    if(g_systemDb->g_dbMachine.CurrentData[17] == 1)
    {
        valuecontrol |= 0x0002;
        m_bufLed[0] |= 0x0001;
    }else if(g_systemDb->g_dbMachine.CurrentData[17] == 2)
    {
        valuecontrol |=0x040000;
        m_bufLed[0] ^= 0x0001;
    }else
    {
        m_bufLed[0] &= 0xfffe;
    }

    if(g_systemDb->g_dbMachine.CurrentData[18] == 1)
    {
        valuecontrol |= 0x0004;
        m_bufLed[1] |= 0x4000;
    }else if(g_systemDb->g_dbMachine.CurrentData[18]== 2)
    {
        valuecontrol |= 0x080000;
        m_bufLed[1] ^= 0x4000;
    }else
    {
        m_bufLed[1] &= 0xbfff;
    }

    if( m_fileDevice != -1 )
        ioctl(m_fileDevice,7,valuecontrol);

    if(g_taskComKey)
        g_taskComKey->CreateTask(COMM_TX_LED,m_bufLed,5);

}

//液晶背光控制
void CFilmBase::SetLCD(bool bState)
{

    if(m_fileDevice != -1)
        ioctl(m_fileDevice, 8, bState);

}

//通过驱动播放按键声音
void CFilmBase::SetKeySound()
{
    unsigned short mBuf[8];
    memset(mBuf,0,8);

    if(m_fileDevice != -1)
    {

        if(!g_dbsys.utility.keySound)
            return;

        //ioctl(m_fileDevice, 6, 0); // for w6410 cpu
        ioctl(m_fileDevice, 6, 1);  //for freescal cpu

    }else if(g_taskComKey->devValid())
    {
        g_taskComKey->CreateTask(COMM_TX_KEY,mBuf,5);
    }else
    {
        soundKey->play();
    }

    return;
    /*
    if(!timerSoundPlay)
        return;

    //for Qt5.5.1 only,for touch panel
    //soundKey2.play();

    timerSoundPlay->start();
    */
}

void CFilmBase::PlayKeySound()
{
    unsigned short mBuf[8];
    memset(mBuf,0,8);

    if(m_fileDevice != -1)
    {

        if(!g_dbsys.utility.keySound)
            return;

        //ioctl(m_fileDevice, 6, 0); // for w6410 cpu
        ioctl(m_fileDevice, 6, 1);  //for freescal cpu

    }else if(g_taskComKey->devValid())
    {
        g_taskComKey->CreateTask(COMM_TX_KEY,mBuf,5);
    }else
    {
        soundKey->play();
    }
}

void CFilmBase::keyPressEvent( QKeyEvent * event )
{
    int mKey = event->key();
    switch (mKey) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if(m_btnKeyFiltered[m_iFocusCurrent] )
            m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        else
            m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : cyan ; border : 2px solid black");

        OnKeyFilterSave(m_iFocusCurrent);
        break;

    case Qt::Key_Backspace:
        break;
    case Qt::Key_Close:
        break;
    case Qt::Key_Escape:
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        break;
    case Qt::Key_Tab:

        if(m_btnKeyFiltered[m_iFocusCurrent] )
            m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : lightGray ; border : 2px solid black");
        else
            m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : cyan ; border : 2px solid black");

        if(++m_iFocusCurrent >= FILM_KEY_MAX)
            m_iFocusCurrent = 0;

        if(m_btnKeyFiltered[m_iFocusCurrent] )
            m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : lightGray ; border : 3px solid green");
        else
            m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : cyan ; border : 3px solid green");

        break;
    default:
        break;
    }
}
void CFilmBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    QString mKeyTag;
    QSettings * iniKeyFilter = new QSettings(QCoreApplication::applicationDirPath() + "/key_filter.ini",QSettings::IniFormat);
    int mValRes;

    for(int mIdx = 0 ; mIdx < FILM_KEY_MAX ; mIdx++)
    {
        mKeyTag.sprintf("data/key_%04x",mBufKeyConst[mIdx]);
        mValRes = iniKeyFilter->value(mKeyTag,0).toInt();
        m_btnKeyFunc[mIdx]->setFocusPolicy(Qt::NoFocus);

        if(mValRes == 1)
        {
            if(mIdx == 0)
                m_btnKeyFunc[mIdx]->setStyleSheet("background-color : lightGray ; border : 3px solid green");
            else
                m_btnKeyFunc[mIdx]->setStyleSheet("background-color : lightGray ; border : 2px solid black");

            m_btnKeyFiltered[mIdx] = true;
        }else
        {
            m_btnKeyFunc[mIdx]->setStyleSheet("background-color : cyan ; border : 2px solid black");
            m_btnKeyFiltered[mIdx] = false;
        }
    }

    m_bIsVisable = true;

    grabKeyboard();

}
void CFilmBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
    m_bIsVisable = false;

    releaseKeyboard();
}
void CFilmBase::mousePressEvent(QMouseEvent */*event*/)
{
    qDebug()<<"CFilmBase::mousePressEvent";
}
//退出时，切换到主界面
void CFilmBase::OnFilmExit()
{
    if(sender() == btnExit)
    {
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
    }
}
void CFilmBase::OnKeyFilterSave(int mKeyIdx)
{
    if(mKeyIdx >= FILM_KEY_MAX  || mKeyIdx < 0)
        return;

    for(int mIdx = 0 ; mIdx < FILM_KEY_MAX ; mIdx++)
    {
        if(sender() == m_btnKeyFunc[mIdx])
            mKeyIdx = mIdx;
    }

    QString mKeyTag;
    QSettings * iniKeyFilter = new QSettings(QCoreApplication::applicationDirPath() + "/key_filter.ini",QSettings::IniFormat);
    int mValRes;

    mKeyTag.sprintf("data/key_%04x",mBufKeyConst[mKeyIdx]);
    mValRes = iniKeyFilter->value(mKeyTag,0).toInt();

    if(mValRes == 1)
    {
        m_btnKeyFiltered[mKeyIdx] = false;
        iniKeyFilter->setValue(mKeyTag,0);
        //m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : cyan ; border : 3px solid green");
        KeyFilterDel(mBufKeyConst[mKeyIdx]);

    }else
    {
        m_btnKeyFiltered[mKeyIdx] = true;
        iniKeyFilter->setValue(mKeyTag,1);
        //m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : lightGray ; border : 3px solid green");
        KeyFilterAdd(mBufKeyConst[mKeyIdx]);
    }

    if(m_btnKeyFiltered[mKeyIdx] )
        m_btnKeyFunc[mKeyIdx]->setStyleSheet("background-color : lightGray ; border : 3px solid green");
    else
        m_btnKeyFunc[mKeyIdx]->setStyleSheet("background-color : cyan ; border : 3px solid green");
}
void CFilmBase::OnKeyFilterDown()
{
    if(m_btnKeyFiltered[m_iFocusCurrent] )
        m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : lightGray ; border : 2px solid black");
    else
        m_btnKeyFunc[m_iFocusCurrent]->setStyleSheet("background-color : cyan ; border : 2px solid black");

    for(int mIdx = 0 ; mIdx < FILM_KEY_MAX ; mIdx++)
    {
        if(sender() == m_btnKeyFunc[mIdx])
            m_iFocusCurrent = mIdx;
    }

    if(m_iFocusCurrent >= FILM_KEY_MAX )
        return;

    OnKeyFilterSave(m_iFocusCurrent);
}
void CFilmBase::filmCtrl(int func)
{
    m_iFilmState = func;
}
//薄膜按键扫描
void CFilmBase::filmTask()
{
    if(m_iFilmState == FILM_FUNC_STOP_SCAN)
        return;

    unsigned short mKeyNew;

    mKeyNew = filmScan();

    if(m_bIsVisable)
        filmKeyDisplay(mKeyNew);       //扫面按键仅显示
    else
        filmKeyExecute(mKeyNew);       //扫面按键执行

}
unsigned short CFilmBase::filmScan()
{
    unsigned short mKeyPhisic = 0xff;

    if(m_fileKeyBoard != -1)
        mKeyPhisic = ioctl(m_fileKeyBoard, 9, 0);   //读取物理按键

    return mKeyPhisic;
}
void CFilmBase::filmImport(unsigned short keyIn)
{
    if(m_bIsVisable)
        filmKeyDisplay(keyIn);       //扫面按键仅显示
    else
        filmKeyExecute(keyIn);       //扫面按键执行
}


void CFilmBase::filmKeyExecute(unsigned short mKeyPhisic)
{

    if(m_iFilmState == FILM_FUNC_STOP_RUN)
        return;

    if(g_dbsys.operation.bTimeout)              //如果系统认为过期，不进行后续操作
        return;

    if(g_dbsys.operation.bStopRunMach)              //如果系统认为过期，不进行后续操作
        return;

    if(mKeyPhisic != 0xff)                      //若果有效按键，停止自运行
        g_systemDb->SetAutoRun(false);

    for(int mIdx = 0 ; mIdx < m_keyFilterCount ; mIdx++)
    {
        if(m_keyFilter[mIdx] == mKeyPhisic)     //屏蔽掉需要屏蔽的按键
        {
            m_bLastKeyFiltered = true;          //标记、按键被过滤掉
            return;
        }
    }

    //如果上个按键被过滤掉//按键抬起，不作处理
    if(mKeyPhisic == 0xf0 && m_bLastKeyFiltered)
    {
        m_bLastKeyFiltered = false;             //清除标记
        return;
    }

    if(mKeyPhisic == 0xf0)                      //抬起键码，将最后有效键码加1
    {
        nKey = keylast + 1;
        SendCmdKey(nKey);               //发送抬起键码
        emit FilmKeyUp(keylast);        //for ndt only
    }else
    {
        for(int i = 0; i < m_keyMax ; i++)
        {
            if(mKeyPhisic == (*g_keyPtr)[i][0])
            {
                keylast = (*g_keyPtr)[i][1];

                if(nKey == keylast)
                    return;

                nKey = (*g_keyPtr)[i][1];
                SendCmdKey(nKey);     //发送按下键码
                emit FilmKeyDown(nKey);
                break;
            }
        }
    }
}
//扫描键码并显示
void CFilmBase::filmKeyDisplay(unsigned short mKeyPhisic)
{

    if(mKeyPhisic == 0xff)
        return;

    mStrBuf.setNum(mKeyPhisic,16);
    lbCurrentCode->setText(mStrBuf);

    if(mKeyPhisic == 0xf0)
    {
        nKey = keylast + 1;

        mStrBuf.setNum(nKey,16);
        lbFunctionUp->setText(mStrBuf);
    }else
    {
        for(int i = 0; i < m_keyMax ; i++)
        {
            if(mKeyPhisic == (*g_keyPtr)[i][0])
            {
                keylast = (*g_keyPtr)[i][1];

                if(nKey == keylast)
                    return;

                nKey = (*g_keyPtr)[i][1];

                mStrBuf.setNum(nKey,16);
                lbFunctionDown->setText(mStrBuf);
                break;
            }
        }
    }
}







