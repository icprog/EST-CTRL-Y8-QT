#include "motion_ceil10b.h"

#include "resource_manager.h"

//POSITION
#define STAND_ARM_LEFT      (SYS_WID( 29 ))
#define STAND_ARM_TOP       (SYS_HEI( 300 ))
#define STAND_ARM_WIDTH     (SYS_WID( 72 ))
#define STAND_ARM_HEIGHT    (SYS_HEI( 72 ))
#define STAND_ARM_PIX_MIN   (SYS_HEI( 188 ))
#define STAND_ARM_PIX_MAX   (SYS_HEI( 328 ))
#define STAND_ARM_DATA_MIN  ( 50 )
#define STAND_ARM_DATA_MAX  ( 180 )

//STAND_DET ANGLE
#define STAND_DET_LEFT      (SYS_WID( 35 ))
#define STAND_DET_TOP       (SYS_HEI( -14 ))
#define STAND_DET_WIDHT     (SYS_WID( 72 ))
#define STAND_DET_HEIGHT    (SYS_HEI( 72 ))
#define STAND_DET_MIN       ( 0 )
#define STAND_DET_MAX       ( 120 )

//CEIL
#define CEIL_LEFT           (SYS_WID( 211 ))
#define CEIL_TOP            (SYS_HEI( 10 ))
#define CEIL_WIDTH          (SYS_WID( 122 ))
#define CEIL_HEIGHT         (SYS_HEI( 400 ))
#define CEIL_PIX_MIN        (SYS_WID( 21 ))
#define CEIL_PIX_MAX        (SYS_WID( 300 ))
#define CEIL_DATA_MIN       (SYS_WID( 0 ))
#define CEIL_DATA_MAX       (SYS_WID( 180 ))

//LIFT
#define LIFT_LEFT           (SYS_WID( 35 ))
#define LIFT_TOP            (SYS_HEI( 87 ))
#define LIFT_WIDTH          (SYS_WID( 20 ))
#define LIFT_HEIGHT         (SYS_HEI( 166 ))
#define LIFT_SCALE_MIN      (SYS_HEIf( 0.63f ))
#define LIFT_SCALE_MAX      (SYS_HEIf( 1.48f ))
#define LIFT_DATA_MIN       (SYS_HEI( 50 ))
#define LIFT_DATA_MAX       (SYS_HEI( 180 ))

//TUBE  ANGLE
#define TUBE_LEFT           (SYS_WID( 4 ))
#define TUBE_TOP            (SYS_HEI( 232 ))
#define TUBE_WIDTH          (SYS_WID( 80 ))
#define TUBE_HEIGHT         (SYS_HEI( 80 ))
#define TUBE_DATA_MIN       ( -90 )
#define TUBE_DATA_MAX       ( 120 )


CMotionCeil10b::CMotionCeil10b(QWidget *parent) :
    CMotionBase10(parent)
{

    setObjectName("CMotionCeil10b");

    resize(SYS_WID(420),SYS_HEI(420));

    pixBackGround = new QFrame(this);
    pixCeil       = new QLabel(this);
    pixStandArm   = new QFrame(this);

    pixDet        = new QLabel();
    pixTube       = new QFrame();
    pixLift       = new QFrame();

    pixBackGround->setGeometry(0,0,SYS_WID(420),SYS_HEI(420));
    pixBackGround->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10b_MOTION_BACK"));

    rectCeil.setRect(CEIL_LEFT,CEIL_TOP,CEIL_WIDTH,CEIL_HEIGHT);
    pixCeil->setGeometry(rectCeil);
    pixCeil->setStyleSheet(g_skinBase->GetStyleMapStr("BASE10_MOTION_CEIL"));

    rectStandArm.setRect(STAND_ARM_LEFT,STAND_ARM_TOP,STAND_ARM_WIDTH,STAND_ARM_HEIGHT);
    pixStandArm->setGeometry(rectStandArm);
    pixStandArm->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10b_MOTION_STAND_ARM"));
    pixStandArm->raise();

    rectDet.setRect(0,0,STAND_DET_WIDHT,STAND_DET_HEIGHT);
    pixDet->setGeometry(0,0,STAND_DET_WIDHT,STAND_DET_HEIGHT);
    pixDet->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10b_MOTION_STAND_DET"));

    rectLift.setRect(LIFT_LEFT,LIFT_TOP,LIFT_WIDTH,LIFT_HEIGHT);
    pixLift->setGeometry(0,0,LIFT_WIDTH,LIFT_HEIGHT);
    pixLift->setStyleSheet(g_skinBase->GetStyleMapStr("BASE10_MOTION_LIFT"));
    m_iLiftHeight = rectLift.height();

    rectTube.setRect(TUBE_LEFT,TUBE_TOP,TUBE_WIDTH,TUBE_HEIGHT);
    pixTube->setGeometry(0,0,TUBE_WIDTH,TUBE_HEIGHT);
    pixTube->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10b_MOTION_TUBE"));

    myMotionInit();

    for(int mIdx = 0 ; mIdx < CEIL10b_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = 0;
        m_iMotionDataCur[mIdx] = 1;
        m_iMotionFresh[mIdx] = false;
    }

    m_fLiftScale = 1.0f;
    m_iTableDown = 0;

}


void CMotionCeil10b::myMotionInit()
{
    CMotionBase::myMotionInit();

    sceneDet->addWidget(pixDet);
    viewDet->setParent(pixStandArm);
    viewDet->setScene(sceneDet);

    sceneTube->addWidget(pixTube);
    viewTube->setParent(pixCeil);
    viewTube->setScene(sceneTube);

    pSceneLift          = new QGraphicsScene(this);
    pSceneLift->addWidget(pixLift);
    viewLift           = new QGraphicsView(pSceneLift,pixCeil);

    viewDet->setGeometry(rectDet);
    viewDet->rotate(-90);

    viewTube->setGeometry(rectTube);

    viewLift->setGeometry(rectLift);
    viewLift->setFocusPolicy(Qt::NoFocus);
    viewLift->setFrameShape(QFrame::NoFrame);
    viewLift->setFrameShadow(QFrame::Plain);
    viewLift->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewLift->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewLift->setStyleSheet("background:transparent");

    viewDet->raise();
    viewLift->raise();
    viewTube->raise();

    pixCeil->raise();
}

void CMotionCeil10b::OnMotionFresh()
{
    int  tempPositionY,tempPositionX;
    float fRatio;

    if(!g_systemDb->g_bCommunicate)
        return;

    for(int mIdx = 0 ;mIdx < CEIL10b_MOTION_MAX ;mIdx++)
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

    if(m_iMotionFresh[CEIL10b_MOTOR_FID])
        m_iMotionFresh[CEIL10b_MOTOR_ANG] = true;

    //1//////////////////////////////////////立柱探测器升降
    if(m_iMotionFresh[CEIL10b_MOTOR_DTH])
    {
        tempPositionY = rectStandArm.top();
        tempPositionX = rectStandArm.left();

        if(m_iMotionDataCur[CEIL10b_MOTOR_DTH] < STAND_ARM_DATA_MIN)
            m_iMotionDataCur[CEIL10b_MOTOR_DTH] = STAND_ARM_DATA_MIN;

        if(m_iMotionDataCur[CEIL10b_MOTOR_DTH] > STAND_ARM_DATA_MAX)
            m_iMotionDataCur[CEIL10b_MOTOR_DTH] = STAND_ARM_DATA_MAX;

        fRatio =(float) (STAND_ARM_PIX_MIN - STAND_ARM_PIX_MAX )/(STAND_ARM_DATA_MAX - STAND_ARM_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[CEIL10b_MOTOR_DTH] - STAND_ARM_DATA_MAX) * fRatio +STAND_ARM_PIX_MIN;

        rectStandArm.moveTo(tempPositionX,tempPositionY);
        pixStandArm->setGeometry(rectStandArm);
    }

    //2//////////////////////////////////////立柱探测器转动
    if(m_iMotionFresh[CEIL10b_MOTOR_DTA])
    {
        if(m_iMotionDataCur[CEIL10b_MOTOR_DTA] < STAND_DET_MIN)
            m_iMotionDataCur[CEIL10b_MOTOR_DTA] = STAND_DET_MIN;

        if(m_iMotionDataCur[CEIL10b_MOTOR_DTA] > STAND_DET_MAX)
            m_iMotionDataCur[CEIL10b_MOTOR_DTA] = STAND_DET_MAX;

        viewDet->rotate(m_iMotionDataCur[CEIL10b_MOTOR_DTA] - m_iMotionDataPre[CEIL10b_MOTOR_DTA]);
        viewDet->setGeometry(rectDet);
    }

    //3//////////////////////////////////////滑车平移
    if(m_iMotionFresh[CEIL10b_MOTOR_SID])
    {
        tempPositionX = rectCeil.left();
        tempPositionY = rectCeil.top();


        if(m_iMotionDataCur[CEIL10b_MOTOR_SID]< CEIL_DATA_MIN)
            m_iMotionDataCur[CEIL10b_MOTOR_SID] = CEIL_DATA_MIN;
        if(m_iMotionDataCur[CEIL10b_MOTOR_SID]> CEIL_DATA_MAX)
            m_iMotionDataCur[CEIL10b_MOTOR_SID] = CEIL_DATA_MAX;

        fRatio =(float) (CEIL_PIX_MAX - CEIL_PIX_MIN)/(CEIL_DATA_MAX - CEIL_DATA_MIN);
        tempPositionX = (m_iMotionDataCur[CEIL10b_MOTOR_SID] - CEIL_DATA_MIN) * fRatio +CEIL_PIX_MIN;

        rectCeil.moveTo(tempPositionX,tempPositionY);
        pixCeil->setGeometry(rectCeil);
    }

    //4//////////////////////////////////////球管升降
    if(m_iMotionFresh[CEIL10b_MOTOR_FID])
    {

        if(m_iMotionDataCur[CEIL10b_MOTOR_FID] < LIFT_DATA_MIN)
            m_iMotionDataCur[CEIL10b_MOTOR_FID] = LIFT_DATA_MIN;

        if(m_iMotionDataCur[CEIL10b_MOTOR_FID] > LIFT_DATA_MAX)
            m_iMotionDataCur[CEIL10b_MOTOR_FID] = LIFT_DATA_MAX;

        fRatio =(float) (LIFT_SCALE_MAX - LIFT_SCALE_MIN )/(LIFT_DATA_MIN - LIFT_DATA_MAX );
        m_fLiftScale = (m_iMotionDataCur[CEIL10b_MOTOR_FID] - LIFT_DATA_MAX) * fRatio +LIFT_SCALE_MIN;

        int m_iTempPosition;
        m_iTempPosition = TUBE_TOP - m_iLiftHeight *  (1.0f- m_fLiftScale);

        rectTube.moveTop(m_iTempPosition );
        m_iTempPosition = LIFT_TOP - m_iLiftHeight *  (1.0f- m_fLiftScale) / 2;

        rectLift.setHeight(m_iLiftHeight * m_fLiftScale);

        m_fLiftScaleCur = m_fLiftScale;
        viewLift->setGeometry(rectLift);
        viewLift->scale(1,m_fLiftScaleCur/m_fLiftScalePre);

        m_fLiftScalePre = m_fLiftScaleCur;
    }

    //5//////////////////////////////////////球管转动
    if(m_iMotionFresh[CEIL10b_MOTOR_ANG])
    {
        if( m_iMotionDataCur[CEIL10b_MOTOR_ANG] < TUBE_DATA_MIN)
            m_iMotionDataCur[CEIL10b_MOTOR_ANG] = TUBE_DATA_MIN;

        if( m_iMotionDataCur[CEIL10b_MOTOR_ANG] > TUBE_DATA_MAX)
            m_iMotionDataCur[CEIL10b_MOTOR_ANG] = TUBE_DATA_MAX;

        viewTube->rotate( m_iMotionDataCur[CEIL10b_MOTOR_ANG] - m_iMotionDataPre[CEIL10b_MOTOR_ANG]);
        viewTube->setGeometry(rectTube);
    }

    for(int mIdx = 0 ;mIdx < CEIL10b_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = m_iMotionDataCur[mIdx];
    }

}
