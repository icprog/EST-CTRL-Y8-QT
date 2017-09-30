#include "motor_menu.h"

#include "resource_manager.h"

CMotorMenu::CMotorMenu(unsigned short mPlatform,QWidget *parent) :
    CSystemBase(parent)
{
    setObjectName("CMotorMenu");

    resize(600,600);

    m_iFocusCurrent = 0;        //button focus index
    m_iBtnCount = 0;
    label_2 = new QLabel(this);
    label_2->setGeometry(QRect(20, 60, 600, 75));
    label_2->setStyleSheet("color : red");
    label_2->setText(QApplication::translate("CMotorMenu", "Attention:Please make sure all the motors\n(limits and directions) are working normally first."));

    m_iPlatform = mPlatform;

    for(int mIdx = 0 ; mIdx < 2 ; mIdx++)
    {
        for(int mCtr = 0 ; mCtr < 4 ; mCtr++)
        {
            pBtnGroup[mIdx * 4 + mCtr ] = new CButtonStable(this);
            pBtnGroup[mIdx * 4 + mCtr ]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 2px solid black"));
            pBtnGroup[mIdx * 4 + mCtr ]->setGeometry(QRect(12 + mCtr * 148,150 + mIdx * 165,135,135));
            pBtnGroup[mIdx * 4 + mCtr ]->setFocusPolicy(Qt::NoFocus);
            connect(pBtnGroup[mIdx * 4 + mCtr ],SIGNAL(pressed()),this,SLOT(OnButtonClick()) );
        }
    }
    pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 3px solid green"));
    pBtnGroup[MENU_MOTION_IDX8] = btnExit;
    connect(pBtnGroup[MENU_MOTION_IDX8],SIGNAL(pressed()),this,SLOT(OnButtonClick()) );

    textTitle->setText(QApplication::translate("CMotorMenu", "Position Calibration Menu"));

    InitMenuMotion(mPlatform);

    translateFontSize(this);

    setVisible(false);
}
void CMotorMenu::InitMenuMotion(unsigned short mPf)
{
    switch(mPf)
    {
    case PF_NDT_8_A:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Panel\n" "X1" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Panel\n" "Y1" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Tube\n" "X2" ));
        pBtnGroup[MENU_MOTION_IDX4]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Y2" ));
        pBtnGroup[MENU_MOTION_IDX5]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX6]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX7]->setVisible(false);
        m_iBtnCount = 5;
        break;
    case PF_RF_8_A:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Table\n" "Position" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Position" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Table\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX4]->setText(QApplication::translate("CMotorMenu", "Foot\n" "Pedal" ));
        pBtnGroup[MENU_MOTION_IDX5]->setText(QApplication::translate("CMotorMenu", "Compressor" ));
        pBtnGroup[MENU_MOTION_IDX6]->setText(QApplication::translate("CMotorMenu", "Collimator\n" "Horizontal" ));
        pBtnGroup[MENU_MOTION_IDX7]->setText(QApplication::translate("CMotorMenu", "Collimator\n" "Vertical" ));
        m_iBtnCount = 8;
        break;
    case PF_NDT_10_A:
        pBtnSoftLimitSet = new CButtonStable(this);
        pBtnSoftLimitSet->setGeometry(50,525,150,60);
        pBtnSoftLimitSet->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));"));
        pBtnSoftLimitSet->show();
        connect(pBtnSoftLimitSet,SIGNAL(pressed()),this,SLOT(OnSoftLimitSet()) );
        pBtnSoftLimitSet->setText(QApplication::translate("CMotorMenu", "NDT Position Cali." ));
    case PF_CEIL_10_A:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Ceilling\n" "X Direction" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX4]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX5]->setText(QApplication::translate("CMotorMenu", "Ceilling\n" "Y Direction" ));
        pBtnGroup[MENU_MOTION_IDX6]->setText(QApplication::translate("CMotorMenu", "Table\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX7]->setText(QApplication::translate("CMotorMenu", "Table\n" "Bucky" ));
        m_iBtnCount = 8;
        break;
    case PF_CEIL_10_B:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Ceilling\n" "X Direction" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX4]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX5]->setText(QApplication::translate("CMotorMenu", "Ceilling\n" "Y Direction" ));
        pBtnGroup[MENU_MOTION_IDX6]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX7]->setVisible(false);
        m_iBtnCount = 6;
        break;
    case PF_CEIL_08_A:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Ceilling\n" "X Direction" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX4]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Angle"));
        pBtnGroup[MENU_MOTION_IDX5]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX6]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX7]->setVisible(false);
        m_iBtnCount = 5;
        break;
    case PF_UARM_10_A:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Uarm\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Position" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Uarm\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX4]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX5]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX6]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX7]->setVisible(false);
        m_iBtnCount = 4;
        break;
    case PF_UARM_08_A:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Uarm\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Position" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Uarm\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX4]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX5]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX6]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX7]->setVisible(false);
        m_iBtnCount = 4;
        break;
    case PF_RAIL_12_A:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Distance" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX4]->setText(QApplication::translate("CMotorMenu", "Table\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX5]->setText(QApplication::translate("CMotorMenu", "Table\n" "Bucky" ));
        pBtnGroup[MENU_MOTION_IDX6]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX7]->setVisible(false);
        m_iBtnCount = 6;
        break;
    case PF_RAIL_08_A:
        pBtnGroup[MENU_MOTION_IDX0]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX1]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Distance" ));
        pBtnGroup[MENU_MOTION_IDX2]->setText(QApplication::translate("CMotorMenu", "Tube\n" "Angle" ));
        pBtnGroup[MENU_MOTION_IDX3]->setText(QApplication::translate("CMotorMenu", "Detector\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX4]->setText(QApplication::translate("CMotorMenu", "Table\n" "Height" ));
        pBtnGroup[MENU_MOTION_IDX5]->setText(QApplication::translate("CMotorMenu", "Table\n" "Bucky" ));
        pBtnGroup[MENU_MOTION_IDX6]->setVisible(false);
        pBtnGroup[MENU_MOTION_IDX7]->setVisible(false);
        m_iBtnCount = 6;
        break;
    default:
        break;
    }
}
void CMotorMenu::showEvent(QShowEvent *event)
{

    //通知下位己发送电机参数
    g_taskComCtrl->CreateTask(CMD_FUNC_PARAM,0,0);

    switch(m_iPlatform)
    {
    case PF_NDT_8_A:
        m_iWidArray[MENU_MOTION_IDX0] = g_motorMgr->g_motorConfig[NDT8a_MOTOR_FID];
        m_iWidArray[MENU_MOTION_IDX1] = g_motorMgr->g_motorConfig[NDT8a_MOTOR_X1];
        m_iWidArray[MENU_MOTION_IDX2] = g_motorMgr->g_motorConfig[NDT8a_MOTOR_Y1];
        m_iWidArray[MENU_MOTION_IDX3] = g_motorMgr->g_motorConfig[NDT8a_MOTOR_X2];
        m_iWidArray[MENU_MOTION_IDX4] = g_motorMgr->g_motorConfig[NDT8a_MOTOR_Y2];
        m_iWidArray[MENU_MOTION_IDX8] = RsMgr->g_systemMenu;
        break;
    case PF_RF_8_A:
    case PF_NDT_10_A:
    case PF_CEIL_10_A:
        m_iWidArray[MENU_MOTION_IDX0] = g_motorMgr->g_motorConfig[CEIL10a_MOTOR_FID];
        m_iWidArray[MENU_MOTION_IDX1] = g_motorMgr->g_motorConfig[CEIL10a_MOTOR_SID];
        m_iWidArray[MENU_MOTION_IDX2] = g_motorMgr->g_motorConfig[CEIL10a_MOTOR_ANG];
        m_iWidArray[MENU_MOTION_IDX3] = g_motorMgr->g_motorConfig[CEIL10a_MOTOR_DTH];
        m_iWidArray[MENU_MOTION_IDX4] = g_motorMgr->g_motorConfig[CEIL10a_MOTOR_DTA];
        m_iWidArray[MENU_MOTION_IDX5] = g_motorMgr->g_motorConfig[CEIL10a_MOTOR_CEP];
        m_iWidArray[MENU_MOTION_IDX6] = g_motorMgr->g_motorConfig[CEIL10a_MOTOR_BEH];
        m_iWidArray[MENU_MOTION_IDX7] = g_motorMgr->g_motorConfig[CEIL10a_MOTOR_DTP];
        m_iWidArray[MENU_MOTION_IDX8] = RsMgr->g_systemMenu;
        break;
    case PF_CEIL_10_B:
        m_iWidArray[MENU_MOTION_IDX0] = g_motorMgr->g_motorConfig[CEIL10b_MOTOR_FID];
        m_iWidArray[MENU_MOTION_IDX1] = g_motorMgr->g_motorConfig[CEIL10b_MOTOR_SID];
        m_iWidArray[MENU_MOTION_IDX2] = g_motorMgr->g_motorConfig[CEIL10b_MOTOR_ANG];
        m_iWidArray[MENU_MOTION_IDX3] = g_motorMgr->g_motorConfig[CEIL10b_MOTOR_DTH];
        m_iWidArray[MENU_MOTION_IDX4] = g_motorMgr->g_motorConfig[CEIL10b_MOTOR_DTA];
        m_iWidArray[MENU_MOTION_IDX5] = g_motorMgr->g_motorConfig[CEIL10b_MOTOR_CEP];
        m_iWidArray[MENU_MOTION_IDX8] = RsMgr->g_systemMenu;
        break;
    case PF_CEIL_08_A:
        m_iWidArray[MENU_MOTION_IDX0] = g_motorMgr->g_motorConfig[CEIL8_MOTOR_FID];
        m_iWidArray[MENU_MOTION_IDX1] = g_motorMgr->g_motorConfig[CEIL8_MOTOR_SID];
        m_iWidArray[MENU_MOTION_IDX2] = g_motorMgr->g_motorConfig[CEIL8_MOTOR_ANG];
        m_iWidArray[MENU_MOTION_IDX3] = g_motorMgr->g_motorConfig[CEIL8_MOTOR_DTH];
        m_iWidArray[MENU_MOTION_IDX4] = g_motorMgr->g_motorConfig[CEIL8_MOTOR_DTA];
        m_iWidArray[MENU_MOTION_IDX8] = RsMgr->g_systemMenu;
        break;
    case PF_UARM_10_A:
        m_iWidArray[MENU_MOTION_IDX0] = g_motorMgr->g_motorConfig[UARM10_MOTOR_HEI];
        m_iWidArray[MENU_MOTION_IDX1] = g_motorMgr->g_motorConfig[UARM10_MOTOR_SID];
        m_iWidArray[MENU_MOTION_IDX2] = g_motorMgr->g_motorConfig[UARM10_MOTOR_ANG];
        m_iWidArray[MENU_MOTION_IDX3] = g_motorMgr->g_motorConfig[UARM10_MOTOR_DTA];
        m_iWidArray[MENU_MOTION_IDX8] = RsMgr->g_systemMenu;
        break;
    case PF_UARM_08_A:
        m_iWidArray[MENU_MOTION_IDX0] = g_motorMgr->g_motorConfig[UARM8_MOTOR_HEI];
        m_iWidArray[MENU_MOTION_IDX1] = g_motorMgr->g_motorConfig[UARM8_MOTOR_SID];
        m_iWidArray[MENU_MOTION_IDX2] = g_motorMgr->g_motorConfig[UARM8_MOTOR_ANG];
        m_iWidArray[MENU_MOTION_IDX3] = g_motorMgr->g_motorConfig[UARM8_MOTOR_DTA];
        m_iWidArray[MENU_MOTION_IDX8] = RsMgr->g_systemMenu;
        break;
    case PF_RAIL_12_A:
        m_iWidArray[MENU_MOTION_IDX0] = g_motorMgr->g_motorConfig[RAIL10_MOTOR_FID];
        m_iWidArray[MENU_MOTION_IDX1] = g_motorMgr->g_motorConfig[RAIL10_MOTOR_SID];
        m_iWidArray[MENU_MOTION_IDX2] = g_motorMgr->g_motorConfig[RAIL10_MOTOR_ANG];
        m_iWidArray[MENU_MOTION_IDX3] = g_motorMgr->g_motorConfig[RAIL10_MOTOR_DTH];
        m_iWidArray[MENU_MOTION_IDX4] = g_motorMgr->g_motorConfig[RAIL10_MOTOR_BEH];
        m_iWidArray[MENU_MOTION_IDX5] = g_motorMgr->g_motorConfig[RAIL10_MOTOR_DTP];
        m_iWidArray[MENU_MOTION_IDX8] = RsMgr->g_systemMenu;
        break;
    case PF_RAIL_08_A:
        m_iWidArray[MENU_MOTION_IDX0] = g_motorMgr->g_motorConfig[RAIL8_MOTOR_FID];
        m_iWidArray[MENU_MOTION_IDX1] = g_motorMgr->g_motorConfig[RAIL8_MOTOR_SID];
        m_iWidArray[MENU_MOTION_IDX2] = g_motorMgr->g_motorConfig[RAIL8_MOTOR_ANG];
        m_iWidArray[MENU_MOTION_IDX3] = g_motorMgr->g_motorConfig[RAIL8_MOTOR_DTH];
        m_iWidArray[MENU_MOTION_IDX4] = g_motorMgr->g_motorConfig[RAIL8_MOTOR_BEH];
        m_iWidArray[MENU_MOTION_IDX5] = g_motorMgr->g_motorConfig[RAIL8_MOTOR_DTP];
        m_iWidArray[MENU_MOTION_IDX8] = RsMgr->g_systemMenu;
        break;
    default:

        break;
    }

    grabKeyboard();

    CSystemBase::showEvent(event);
}
void CMotorMenu::hideEvent(QHideEvent *event)
{
    releaseKeyboard();

    CSystemBase::hideEvent(event);
}

void CMotorMenu::keyPressEvent( QKeyEvent * event )
{
    event->accept();

    switch(event->key())
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if(m_iFocusCurrent < m_iBtnCount && m_iFocusCurrent >= 0 )
        {
            this->hide();
            g_mainSetting->setSceneWidget(m_iWidArray[m_iFocusCurrent]);
        }
        break;
    case Qt::Key_Tab:
        pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 2px solid black"));

        if(++m_iFocusCurrent >= m_iBtnCount)
            m_iFocusCurrent = 0;

        pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 3px solid green"));

        break;
    case Qt::Key_Escape:
        this->hide();
        g_mainSetting->setSceneWidget(m_iWidArray[MENU_MOTION_IDX8]);
        return;
    default:
        break;
    }
}

void CMotorMenu::OnButtonClick()
{

    for(int mIdx = 0 ; mIdx < MENU_MOTION_WID_MAX ; mIdx++)
    {
        if(sender() == pBtnGroup[mIdx])
        {
            pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 2px solid black"));
            m_iFocusCurrent = mIdx;
            pBtnGroup[m_iFocusCurrent]->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(174, 207, 241, 255), stop:1 rgba(255, 255, 255, 255));border : 3px solid green"));
            break;
        }
    }

    if(m_iFocusCurrent <= MENU_MOTION_WID_MAX && m_iFocusCurrent >= 0 )
    {
        this->hide();
        g_mainSetting->setSceneWidget(m_iWidArray[m_iFocusCurrent]);
    }
}

void CMotorMenu::OnSoftLimitSet()
{
    this->hide();
    g_mainSetting->setSceneWidget(g_motorMgr->g_motorNdt);
}
