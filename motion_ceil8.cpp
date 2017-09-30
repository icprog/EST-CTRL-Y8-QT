#include "motion_ceil8.h"
#include "resource_manager.h"

//POSITION
#define STAND_ARM_LEFT          (SYS_WID( 0 ))
#define STAND_ARM_TOP           (SYS_HEI( 30 ))
#define STAND_ARM_PIX_MIN       (SYS_HEI( 120 ))
#define STAND_ARM_PIX_MAX       (SYS_HEI( 310 ))
#define STAND_ARM_DATA_MIN      ( 50 )
#define STAND_ARM_DATA_MAX      ( 180 )

//TUBE  ANGLE
#define TUBE_LEFT               (SYS_WID( 0 ))
#define TUBE_TOP                (SYS_HEI( 292 ))
#define TUBE_DATA_MIN           ( -90 )
#define TUBE_DATA_MAX           ( 120 )

//CEILLING
#define CEIL_LEFT               (SYS_WID( 10 ))
#define CEIL_TOP                (SYS_HEI( 0 ))
#define CEIL_PIX_MIN            (SYS_WID( 10 ))
#define CEIL_PIX_MAX            (SYS_WID( 300 ))
#define CEIL_DATA_MIN           ( 0 )
#define CEIL_DATA_MAX           ( 180 )

//det angle
#define CEIL8_DET_ANG_MIN       ( 0 )
#define CEIL8_DET_ANG_MAX       ( 120 )

//LIFT
#define LIFT_LEFT               (SYS_WID( 28 ))
#define LIFT_TOP                (SYS_HEI( 87 ))
#define LIFT_SCALE_MIN          (SYS_HEIf( 0.23f ))
#define LIFT_SCALE_MAX          (SYS_HEIf( 1.09f ))
#define LIFT_DATA_MIN           ( 50 )
#define LIFT_DATA_MAX           ( 180 )


CMotionCeil8::CMotionCeil8(QWidget *parent) :
    CMotionBase8(parent)
{

    setObjectName("CMotionCeil8");

    resize(SYS_WID(450),SYS_HEI(450));

    pixBackGround   = new QFrame(this);
    pixStandArm     = new QLabel(this);
    pixCeil         = new QLabel(this);
    pixTube         = new QFrame();
    pixLift         = new QFrame();
    pixDet          = new QFrame();

    pixBackGround->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_MOVIE_BACK"));
    pixBackGround->setGeometry(0,0,SYS_WID(450),SYS_HEI(450));
    pixBackGround->show();

    rectTube.setRect(0,TUBE_TOP,SYS_WID(98),SYS_HEI(98));
    pixTube->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_MOVIE_TUBE"));
    pixTube->setGeometry(0,0,SYS_WID(98),SYS_HEI(98));

    pixLift->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_MOVIE_LIFT"));
    rectLift.setRect(SYS_WID(34),SYS_HEI(118),SYS_WID(24),SYS_HEI(220));
    pixLift->setGeometry(0,0,SYS_WID(24),SYS_HEI(220));
    m_iLiftHeight = rectLift.height();

    pixDet->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_MOVIE_DET"));
    rectDet.setRect(0,0,SYS_WID(120),SYS_HEI(120));
    pixDet->setGeometry(rectDet);

    rectStandArm.setRect(0,SYS_HEI(270),SYS_WID(120),SYS_HEI(120));
    pixStandArm->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_MOVIE_STAND_ARM"));
    pixStandArm->setGeometry(rectStandArm);

    rectCeil.setRect(SYS_WID(275),SYS_HEI(11),SYS_WID(141),SYS_HEI(400));
    pixCeil->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_MOVIE_CEIL"));
    pixCeil->setGeometry(rectCeil);

    myMotionInit();

    for(int mIdx = 0 ; mIdx < CEIL8_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = 0;
        m_iMotionDataCur[mIdx] = 1;
        m_iMotionFresh[mIdx] = false;
    }

}

void CMotionCeil8::myMotionInit()
{
    CMotionBase::myMotionInit();

    sceneTube->setParent(pixCeil);
    sceneTube->addWidget(pixTube);
    viewTube->setParent(pixCeil);
    viewTube->setScene(sceneTube);
    viewTube->setGeometry(rectTube);

    sceneDet->setParent(pixStandArm);
    sceneDet->addWidget(pixDet);
    viewDet->setParent(pixStandArm);
    viewDet->setScene(sceneDet);
    viewDet->setGeometry(rectDet);
    viewDet->rotate(-90);

    sceneLift       = new QGraphicsScene(pixCeil);
    viewLift        = new QGraphicsView(pixCeil);
    sceneLift->addWidget(pixLift);
    viewLift->setScene(sceneLift);

    viewLift->setGeometry(rectLift);
    viewLift->setFocusPolicy(Qt::NoFocus);
    viewLift->setFrameShape(QFrame::NoFrame);
    viewLift->setFrameShadow(QFrame::Plain);
    viewLift->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewLift->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewLift->setStyleSheet("background:transparent");
    viewLift->show();

    pixBackGround->raise();
    pixStandArm->raise();
    pixCeil->raise();
    viewTube->raise();
    viewDet->raise();

}
void CMotionCeil8::OnMotionFresh()
{
    int  tempPositionY,tempPositionX;
    float fRatio;

    for(int mIdx = 0 ;mIdx < CEIL8_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataCur[mIdx] = g_systemDb->g_dbMachine.CurrentData[mIdx];
        if(m_iMotionDataCur[mIdx] != m_iMotionDataPre[mIdx])
        {
            m_iMotionFresh[mIdx] = true;
        }else
        {
            m_iMotionFresh[mIdx] = false;
        }
    }

    if(m_iMotionFresh[CEIL8_MOTOR_FID])
        m_iMotionFresh[CEIL8_MOTOR_ANG] = true;


    //1//////////////////////////////////////立柱探测器升降
    if(m_iMotionFresh[CEIL8_MOTOR_DTH])
    {
        tempPositionY = rectStandArm.top();
        tempPositionX = rectStandArm.left();

        if(m_iMotionDataCur[CEIL8_MOTOR_DTH] < STAND_ARM_DATA_MIN)
            m_iMotionDataCur[CEIL8_MOTOR_DTH] = STAND_ARM_DATA_MIN;

        if(m_iMotionDataCur[CEIL8_MOTOR_DTH] > STAND_ARM_DATA_MAX)
            m_iMotionDataCur[CEIL8_MOTOR_DTH] = STAND_ARM_DATA_MAX;

        fRatio =(float) (STAND_ARM_PIX_MIN - STAND_ARM_PIX_MAX )/(STAND_ARM_DATA_MAX - STAND_ARM_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[CEIL8_MOTOR_DTH] - STAND_ARM_DATA_MAX) * fRatio +STAND_ARM_PIX_MIN;

        rectStandArm.moveTo(tempPositionX,tempPositionY);
        pixStandArm->setGeometry(rectStandArm);
    }

    //2//////////////////////////////////////探测器转动
    if(m_iMotionFresh[CEIL8_MOTOR_DTA])
    {
        if(m_iMotionDataCur[CEIL8_MOTOR_DTA] < CEIL8_DET_ANG_MIN)
            m_iMotionDataCur[CEIL8_MOTOR_DTA] = CEIL8_DET_ANG_MIN;

        if(m_iMotionDataCur[CEIL8_MOTOR_DTA] > CEIL8_DET_ANG_MAX)
            m_iMotionDataCur[CEIL8_MOTOR_DTA] = CEIL8_DET_ANG_MAX;

        viewDet->rotate(m_iMotionDataCur[CEIL8_MOTOR_DTA] - m_iMotionDataPre[CEIL8_MOTOR_DTA]);
    }

    //3//////////////////////////////////////球管升降控制
    if(m_iMotionFresh[CEIL8_MOTOR_FID])
    {

        if(m_iMotionDataCur[CEIL8_MOTOR_FID] < LIFT_DATA_MIN)
            m_iMotionDataCur[CEIL8_MOTOR_FID] = LIFT_DATA_MIN;

        if(m_iMotionDataCur[CEIL8_MOTOR_FID] > LIFT_DATA_MAX)
            m_iMotionDataCur[CEIL8_MOTOR_FID] = LIFT_DATA_MAX;

        fRatio =(float) (LIFT_SCALE_MAX - LIFT_SCALE_MIN )/(LIFT_DATA_MIN - LIFT_DATA_MAX );
        m_fLiftScale = (m_iMotionDataCur[CEIL8_MOTOR_FID] - LIFT_DATA_MAX) * fRatio +LIFT_SCALE_MIN;

        int m_iTempPosition;
        m_iTempPosition = TUBE_TOP - m_iLiftHeight *  (1.0f- m_fLiftScale);
        rectTube.moveTop(m_iTempPosition );

        m_iTempPosition = LIFT_TOP - m_iLiftHeight *  (1.0f- m_fLiftScale) / 2;

        rectLift.setHeight(m_iLiftHeight * m_fLiftScale);

        m_fLiftScaleCur = m_fLiftScale;
        viewLift->setGeometry(rectLift);
        viewLift->scale(1,m_fLiftScaleCur/m_fLiftScalePre);
        m_fLiftScalePre = m_fLiftScale;
    }
    //4//////////////////////////////////////球管转动
    if(m_iMotionFresh[CEIL8_MOTOR_ANG])
    {
        if( m_iMotionDataCur[CEIL8_MOTOR_ANG] < TUBE_DATA_MIN)
            m_iMotionDataCur[CEIL8_MOTOR_ANG] = TUBE_DATA_MIN;

        if( m_iMotionDataCur[CEIL8_MOTOR_ANG] > TUBE_DATA_MAX)
            m_iMotionDataCur[CEIL8_MOTOR_ANG] = TUBE_DATA_MAX;

        viewTube->rotate( m_iMotionDataCur[CEIL8_MOTOR_ANG] -  m_iMotionDataPre[CEIL8_MOTOR_ANG]);
        viewTube->setGeometry(rectTube);
    }

    //5//////////////////////////////////////滑车移动控制
    if(m_iMotionFresh[CEIL8_MOTOR_SID])
    {
        tempPositionX = rectCeil.left();
        tempPositionY = rectCeil.top();

        if(m_iMotionDataCur[CEIL8_MOTOR_SID]< CEIL_DATA_MIN)
            m_iMotionDataCur[CEIL8_MOTOR_SID] = CEIL_DATA_MIN;
        if(m_iMotionDataCur[CEIL8_MOTOR_SID]> CEIL_DATA_MAX)
            m_iMotionDataCur[CEIL8_MOTOR_SID] = CEIL_DATA_MAX;

        fRatio =(float) (CEIL_PIX_MAX - CEIL_PIX_MIN)/(CEIL_DATA_MAX - CEIL_DATA_MIN);
        tempPositionX = (m_iMotionDataCur[CEIL8_MOTOR_SID] - CEIL_DATA_MIN) * fRatio +CEIL_PIX_MIN;

        rectCeil.moveTo(tempPositionX,tempPositionY);
        pixCeil->setGeometry(rectCeil);
    }

    for(int mIdx = 0 ;mIdx < CEIL8_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = m_iMotionDataCur[mIdx];
    }

}
