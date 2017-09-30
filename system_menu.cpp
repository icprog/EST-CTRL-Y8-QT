
#include "system_menu.h"
#include "resource_manager.h"

#define SYS_MENU_POSITION    ( 0 )   /*位置校正菜单*/
#define SYS_MENU_SPEED    ( 1 )   /*位置校正菜单*/
#define SYS_MENU_FAST       ( 2 )
#define SYS_MENU_SETTING     (3)
#define SYS_MENU_UPDATE      (4)
#define SYS_MENU_DEBUG  (5)
#define SYS_MENU_INSTALL (6)
#define SYS_MENU_SELFRUN (7)
#define SYS_MENU_KEY        (8)
#define SYS_MENU_PLATFORM   (9)
#define SYS_MENU_ADVANCE    (10)
#define SYS_MENU_NETWORK    (11)

CSystemMenu::CSystemMenu( QWidget* parent ):
    CSystemBase(parent)
{     

    setObjectName("CSystemMenu");

    m_iFocusCurrent = 0;        //button focus index

    resize(600,600);

    textTitle->setText(QApplication::translate("CSystemMenu", "System Configuration Menu"));

    TextLabel1 = new QLabel(this);
    TextLabel1->setGeometry(QRect(20, 55, 150, 28));
    TextLabel1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    TextLabel1->setStyleSheet("color : red");

    TextLabel3 = new QLabel(this);
    TextLabel3->setGeometry(QRect(20, 110, 571, 28));
    TextLabel3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    TextLabel3->setStyleSheet("color : red");

    TextLabel2 = new QLabel(this);
    TextLabel2->setGeometry(QRect(20, 80, 571, 28));
    TextLabel2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    TextLabel2->setStyleSheet("color : red");

    TextLabel1->setText(QApplication::translate("CSystemMenu", "Attention:"));
    TextLabel3->setText(QApplication::translate("CSystemMenu", "carefully! Improper operation may cause serious damage to the system."));
    TextLabel2->setText(QApplication::translate("CSystemMenu", "All software Protection are closed in debugging mode, please operate"));

    for(int mIdx = 0 ; mIdx < BTN_MENU_MAX ; mIdx++)
    {
        pBtnGroup[mIdx] = new CButtonStable(this);
        //pBtnGroup[mIdx]->setFocusPolicy(Qt::TabFocus);    //let CSystemMenu handle tabfocus
        pBtnGroup[mIdx]->setFocusPolicy(Qt::NoFocus);    //let CSystemMenu handle tabfocus
        pBtnGroup[mIdx]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 2px solid black"));
    }
    pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 3px solid green"));

    pBtnGroup[SYS_MENU_POSITION]->setGeometry(QRect(12,  155, 135, 90));
    pBtnGroup[SYS_MENU_SPEED]   ->setGeometry(QRect(159, 155, 135, 90));
    pBtnGroup[SYS_MENU_FAST]    ->setGeometry(QRect(306, 155, 135, 90));
    pBtnGroup[SYS_MENU_SETTING] ->setGeometry(QRect(453, 155, 135, 90));
    pBtnGroup[SYS_MENU_UPDATE]  ->setGeometry(QRect(12,  270, 135, 90));
    pBtnGroup[SYS_MENU_DEBUG]   ->setGeometry(QRect(159, 270, 135, 90));
    pBtnGroup[SYS_MENU_INSTALL] ->setGeometry(QRect(306, 270, 135, 90));
    pBtnGroup[SYS_MENU_SELFRUN] ->setGeometry(QRect(453, 270, 135, 90));
    pBtnGroup[SYS_MENU_KEY]     ->setGeometry(QRect(12,  385, 135, 90));
    pBtnGroup[SYS_MENU_PLATFORM]->setGeometry(QRect(159, 385, 135, 90));
    pBtnGroup[SYS_MENU_ADVANCE] ->setGeometry(QRect(306, 385, 135, 90));
    pBtnGroup[SYS_MENU_NETWORK] ->setGeometry(QRect(453, 385, 135, 90));

    pBtnGroup[SYS_MENU_POSITION]->setText(QApplication::translate("CSystemMenu", "Position\nCalibration"));
    pBtnGroup[SYS_MENU_SPEED]   ->setText(QApplication::translate("CSystemMenu", "Motor Speed\nSettings"));
    pBtnGroup[SYS_MENU_FAST]    ->setText(QApplication::translate("CSystemMenu", "Fast Pos.\nSettings"));
    pBtnGroup[SYS_MENU_SETTING] ->setText(QApplication::translate("CSystemMenu", "System\nSettings"));
    pBtnGroup[SYS_MENU_UPDATE]  ->setText(QApplication::translate("CSystemMenu", "Application\nUpgrade"));
    pBtnGroup[SYS_MENU_DEBUG]   ->setText(QApplication::translate("CSystemMenu", "Motor\nDebugging"));
    pBtnGroup[SYS_MENU_INSTALL] ->setText(QApplication::translate("CSystemMenu", "Installment"));
    pBtnGroup[SYS_MENU_SELFRUN] ->setText(QApplication::translate("CSystemMenu", "Self\nRunning"));
    pBtnGroup[SYS_MENU_KEY]     ->setText(QApplication::translate("CSystemMenu", "KeyBoard\nSettings"));
    pBtnGroup[SYS_MENU_PLATFORM]->setText(QApplication::translate("CSystemMenu", "Platform\nChange"));
    pBtnGroup[SYS_MENU_ADVANCE] ->setText(QApplication::translate("CSystemMenu", "Advanced\nsettings"));
    pBtnGroup[SYS_MENU_NETWORK] ->setText(QApplication::translate("CSystemMenu", "NetWork\nsettings"));
    //pBtnGroup[SYS_MENU_NETWORK]->setVisible(false);

    for(int mIdx = 0 ; mIdx < BTN_MENU_MAX ;mIdx++ )
    {
        connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnButtonPressed()));
    }

    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnButtonPressed()));

    translateFontSize( this );

    setVisible(false);
}

void CSystemMenu::keyPressEvent( QKeyEvent * event )
{
    switch(event->key())
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if(m_iFocusCurrent < BTN_MENU_MAX && m_iFocusCurrent >= 0 )
        {
            this->hide();
            g_mainSetting->setSceneWidget(pWidGroup[m_iFocusCurrent]);
        }
        break;
    case Qt::Key_Tab:
        pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 2px solid black"));

        if(++m_iFocusCurrent >= BTN_MENU_MAX)
            m_iFocusCurrent = 0;

        pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 3px solid green"));

        break;
    case Qt::Key_Escape:
        this->hide();
        emit ViewChange(VIEW_MAIN);
        return;
    default:
        event->accept();
        break;
    }
}


void CSystemMenu::hideEvent(QHideEvent *event)
{   	

    releaseKeyboard();

    CSystemBase::hideEvent(event);
} 

void CSystemMenu::showEvent(QShowEvent *event)
{
    //发送指令消息，进入设定模式
    unsigned short buf[10];
    buf[0]=0;
    buf[1]=SYS_CMD_SETTING;
    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);

    //停止所有动作
    g_taskComCtrl->CreateTask(CMD_FUNC_MOTO,0,0);

    //将控件与控制指针关联
    pWidGroup[SYS_MENU_POSITION]= RsMgr->g_motorMenu;
    pWidGroup[SYS_MENU_SPEED]   = RsMgr->g_systemSpeed;
    pWidGroup[SYS_MENU_FAST]    = RsMgr->g_systemSmart;
    pWidGroup[SYS_MENU_SETTING] = RsMgr->g_systemConfig;
    pWidGroup[SYS_MENU_UPDATE]  = RsMgr->g_systemUpdate;
    pWidGroup[SYS_MENU_DEBUG]   = g_debugPage1;
    pWidGroup[SYS_MENU_INSTALL] = RsMgr->g_systemInstall;
    pWidGroup[SYS_MENU_SELFRUN] = RsMgr->g_systemSelfRun;
    pWidGroup[SYS_MENU_KEY]     = RsMgr->g_filmBase;
    pWidGroup[SYS_MENU_PLATFORM]= RsMgr->g_systemPlatform;
    pWidGroup[SYS_MENU_ADVANCE] = RsMgr->g_systemAdvance;
    pWidGroup[SYS_MENU_NETWORK] = RsMgr->g_systemNetWork;

    //根据配置文件，关闭或打开对应功能，默认全部开启   
#ifdef QT_ARCH_ARM
    pBtnGroup[SYS_MENU_POSITION]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_POSITION"  ,true).toInt() != false);
    pBtnGroup[SYS_MENU_SPEED]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_SPEED"        ,true).toInt() != false);
    pBtnGroup[SYS_MENU_FAST]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_FAST"          ,true).toInt() != false);
    pBtnGroup[SYS_MENU_SETTING]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_SETTING"    ,true).toInt() != false);
    pBtnGroup[SYS_MENU_UPDATE]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_UPDATE"      ,true).toInt() != false);
    pBtnGroup[SYS_MENU_DEBUG]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_DEBUG"        ,true).toInt() != false);
    pBtnGroup[SYS_MENU_INSTALL]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_INSTALL"    ,true).toInt() != false);
    pBtnGroup[SYS_MENU_SELFRUN]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_SELFRUN"    ,true).toInt() != false);
    pBtnGroup[SYS_MENU_KEY]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_KEY"            ,true).toInt() != false);
    pBtnGroup[SYS_MENU_PLATFORM]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_PLATFORM"  ,true).toInt() != false);
    pBtnGroup[SYS_MENU_ADVANCE]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_ADVANCE"    ,true).toInt() != false);
    pBtnGroup[SYS_MENU_NETWORK]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_NETWORK"    ,true).toInt() != false);
#else
    pBtnGroup[SYS_MENU_POSITION]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_POSITION"  ,false).toInt() != false);
    pBtnGroup[SYS_MENU_SPEED]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_SPEED"        ,false).toInt() != false);
    pBtnGroup[SYS_MENU_FAST]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_FAST"          ,false).toInt() != false);
    pBtnGroup[SYS_MENU_SETTING]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_SETTING"    ,true).toInt() != false);
    pBtnGroup[SYS_MENU_UPDATE]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_UPDATE"      ,false).toInt() != false);
    pBtnGroup[SYS_MENU_DEBUG]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_DEBUG"        ,true).toInt() != false);
    pBtnGroup[SYS_MENU_INSTALL]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_INSTALL"    ,false).toInt() != false);
    pBtnGroup[SYS_MENU_SELFRUN]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_SELFRUN"    ,false).toInt() != false);
    pBtnGroup[SYS_MENU_KEY]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_KEY"            ,false).toInt() != false);
    pBtnGroup[SYS_MENU_PLATFORM]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_PLATFORM"  ,false).toInt() != false);
    pBtnGroup[SYS_MENU_ADVANCE]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_ADVANCE"    ,false).toInt() != false);
    pBtnGroup[SYS_MENU_NETWORK]->setEnabled(g_systemDb->getSystemCfg("MENU/SYS_MENU_NETWORK"    ,true).toInt() != false);
#endif

    //获取按键输入
    grabKeyboard();

    CSystemBase::showEvent(event);
}

void CSystemMenu::OnButtonPressed()
{
    if(sender() == btnExit)
    {
        this->hide();
        emit ViewChange(VIEW_MAIN);
        return;
    }

    for(int mIdx = 0 ; mIdx < BTN_MENU_MAX ;mIdx++ )
    {
        if(pBtnGroup[mIdx] == sender())
        {
            pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 2px solid black"));
            m_iFocusCurrent = mIdx;
            pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 3px solid green"));
            break;
        }
    }

    if(m_iFocusCurrent < BTN_MENU_MAX && m_iFocusCurrent >= 0 )
    {
        this->hide();
        g_mainSetting->setSceneWidget(pWidGroup[m_iFocusCurrent]);
    }
}

