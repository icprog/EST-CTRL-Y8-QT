#include "motion_ceil10a.h"

#include "resource_manager.h"

//POSITION
#define STAND_ARM_LEFT      (SYS_HEI( 29 ))
#define STAND_ARM_TOP       (SYS_WID( 300 ))
#define STAND_ARM_WIDTH     (SYS_HEI( 72 ))
#define STAND_ARM_HEIGHT    (SYS_WID( 72 ))
#define STAND_ARM_PIX_MIN   (SYS_WID( 188 ))
#define STAND_ARM_PIX_MAX   (SYS_WID( 328 ))
#define STAND_ARM_DATA_MIN  ( 50 )
#define STAND_ARM_DATA_MAX  ( 180 )

//STAND_DET ANGLE
#define STAND_DET_LEFT      (SYS_HEI( 35 ))
#define STAND_DET_TOP       (SYS_WID( -14 ))
#define STAND_DET_WIDHT     (SYS_HEI( 72 ))
#define STAND_DET_HEIGHT    (SYS_WID( 72 ))
#define STAND_DET_MIN       ( 0 )
#define STAND_DET_MAX       ( 120 )

//TABLE
#define TABLE_LEFT          (SYS_HEI( 135 ))
#define TABLE_TOP           (SYS_WID( 335 ))
#define TABLE_WIDTH         (SYS_HEI( 227 ))
#define TABLE_HEIGHT        (SYS_WID( 26 ))
#define TABLE_PIX_MIN       ( 335 )/*(SYS_WID( 335 ))*/
#define TABLE_PIX_MAX       ( 376 )/*(SYS_WID( 376 ))*/
#define TABLE_DATA_MIN      ( 25 )/*(SYS_WID( 25 ))*/
#define TABLE_DATA_MAX      ( 70 )/*(SYS_WID( 70 ))*/

//TABLE_DET
#define TABLE_DET_LEFT      (SYS_HEI( 80 ))
#define TABLE_DET_TOP       (SYS_WID( 6 ))
#define TABLE_DET_WIDTH     (SYS_HEI( 58 ))
#define TABLE_DET_HEIGHT    (SYS_WID( 9 ))
#define TABLE_DET_PIX_MIN   (SYS_HEI( 48 ))
#define TABLE_DET_PIX_MAX   (SYS_HEI( 122 ))
#define TABLE_DET_DATA_MIN  (SYS_HEI( 94 ))
#define TABLE_DET_DATA_MAX  (SYS_HEI( 144 ))

//CEIL
#define CEIL_LEFT           (SYS_HEI( 211 ))
#define CEIL_TOP            (SYS_WID( 10 ))
#define CEIL_WIDTH          (SYS_HEI( 122 ))
#define CEIL_HEIGHT         (SYS_WID( 400 ))
#define CEIL_PIX_MIN        (SYS_HEI( 21 ))
#define CEIL_PIX_MAX        (SYS_HEI( 300 ))
#define CEIL_DATA_MIN       (SYS_HEI( 0 ))
#define CEIL_DATA_MAX       (SYS_HEI( 180 ))

//LIFT
#define LIFT_LEFT           (SYS_HEI( 35 ))
#define LIFT_TOP            (SYS_WID( 87 ))
#define LIFT_WIDTH          (SYS_HEI( 20 ))
#define LIFT_HEIGHT         (SYS_WID( 166 ))
#define LIFT_SCALE_MIN      (( 0.63f )) /*(SYS_HEIf( 0.63f ))*/
#define LIFT_SCALE_MAX      (( 1.48f ))/*(SYS_HEIf( 1.48f ))*/
#define LIFT_DATA_MIN       ( 50 )/*(SYS_WID( 50 ))*/
#define LIFT_DATA_MAX       ( 180 )/*(SYS_WID( 180 ))*/

//TUBE  ANGLE
#define TUBE_LEFT           (SYS_HEI( 4 ))
#define TUBE_TOP            (SYS_WID( 232 ))
#define TUBE_WIDTH          (SYS_HEI( 80 ))
#define TUBE_HEIGHT         (SYS_WID( 80 ))
#define TUBE_DATA_MIN       ( -90 )
#define TUBE_DATA_MAX       ( 120 )

//ACCORDION
#define ACCORDION_LEFT      (SYS_HEI( 204 ))
#define ACCORDION_TOP       (TABLE_TOP + SYS_WID( 25 ))
#define ACCORDION_WIDTH     (SYS_WID( 83 ))
#define ACCORDION_HEIGHT    (SYS_WID( 38 ))

//POSITION REFERENCE
#define ACCORDION_REF       ( 23 )
#define TABLE_DET_REF       ( 6 )


CMotionCeil10a::CMotionCeil10a(QWidget *parent) :
    CMotionBase10(parent)
{

    setObjectName("CMotionCeil10a");

    resize(SYS_HEI(420),SYS_WID(420));

    pixBackGround = new QFrame(this);
    pixTable      = new QFrame(this);
    pixCeil       = new QLabel(this);
    pixStandArm   = new QFrame(this);
    pixTableDet   = new QFrame(pixTable);

    pixAccordion  = new QFrame();
    pixDet        = new QLabel();
    pixTube       = new QFrame();
    pixLift       = new QFrame();

    pixBackGround->setGeometry(0,0,SYS_HEI(420),SYS_WID(420));
    pixBackGround->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10a_MOTION_BACK"));

    rectTable.setRect(TABLE_LEFT,TABLE_TOP,TABLE_WIDTH,TABLE_HEIGHT);
    pixTable->setGeometry(rectTable);
    pixTable->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10a_MOTION_TABLE"));
    pixTable->raise();

    rectTableDet.setRect(TABLE_DET_LEFT,TABLE_DET_TOP,TABLE_DET_WIDTH,TABLE_DET_HEIGHT);
    pixTableDet->setGeometry(rectTableDet);
    pixTableDet->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10a_MOTION_TABLE_DET"));
    pixTableDet->raise();

    rectCeil.setRect(CEIL_LEFT,CEIL_TOP,CEIL_WIDTH,CEIL_HEIGHT);
    pixCeil->setGeometry(rectCeil);
    pixCeil->setStyleSheet(g_skinBase->GetStyleMapStr("BASE10_MOTION_CEIL"));

    rectStandArm.setRect(STAND_ARM_LEFT,STAND_ARM_TOP,STAND_ARM_WIDTH,STAND_ARM_HEIGHT);
    pixStandArm->setGeometry(rectStandArm);
    pixStandArm->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10a_MOTION_STAND_ARM"));
    pixStandArm->raise();

    rectAccordion.setRect(ACCORDION_LEFT,ACCORDION_TOP,ACCORDION_WIDTH,ACCORDION_HEIGHT);
    pixAccordion->setGeometry(0,0,ACCORDION_WIDTH,ACCORDION_HEIGHT);
    pixAccordion->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10a_MOTION_ACCORDION"));

    rectDet.setRect(0,0,STAND_DET_WIDHT,STAND_DET_HEIGHT);
    pixDet->setGeometry(0,0,STAND_DET_WIDHT,STAND_DET_HEIGHT);
    pixDet->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10a_MOTION_STAND_DET"));

    rectLift.setRect(LIFT_LEFT,LIFT_TOP,LIFT_WIDTH,LIFT_HEIGHT);
    pixLift->setGeometry(0,0,LIFT_WIDTH,LIFT_HEIGHT);
    pixLift->setStyleSheet(g_skinBase->GetStyleMapStr("BASE10_MOTION_LIFT"));
    m_iLiftHeight = rectLift.height();

    rectTube.setRect(TUBE_LEFT,TUBE_TOP,TUBE_WIDTH,TUBE_HEIGHT);
    pixTube->setGeometry(0,0,TUBE_WIDTH,TUBE_HEIGHT);
    pixTube->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL10a_MOTION_TUBE"));

    myMotionInit();

    for(int mIdx = 0 ; mIdx < CEIL10a_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = 0;
        m_iMotionDataCur[mIdx] = 1;
        m_iMotionFresh[mIdx] = false;
    }

    m_fLiftScale = 1.0f;
    m_iTableDown = 0;

}


void CMotionCeil10a::myMotionInit()
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

    pSceneAccordion     = new QGraphicsScene(this);
    pSceneAccordion->addWidget(pixAccordion);
    viewAccordion      = new QGraphicsView(pSceneAccordion,this);

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

    viewAccordion->setGeometry(rectAccordion);
    viewAccordion->setFocusPolicy(Qt::NoFocus);
    viewAccordion->setFrameShape(QFrame::NoFrame);
    viewAccordion->setFrameShadow(QFrame::Plain);
    viewAccordion->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewAccordion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewAccordion->setStyleSheet("background:transparent");

    viewAccordion->raise();
    viewDet->raise();
    viewLift->raise();
    viewTube->raise();

    pixCeil->raise();
}

void CMotionCeil10a::OnMotionFresh()
{
    int  tempPositionY,tempPositionX;
    float fRatio;

    if(!g_systemDb->g_bCommunicate)
        return;

    for(int mIdx = 0 ;mIdx < CEIL10a_MOTION_MAX ;mIdx++)
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

    if(m_iMotionFresh[CEIL10a_MOTOR_FID])
        m_iMotionFresh[CEIL10a_MOTOR_ANG] = true;

    if(m_iMotionFresh[CEIL10a_MOTOR_BEH])
        m_iMotionFresh[CEIL10a_MOTOR_DTP] = true;

    //1//////////////////////////////////////立柱探测器升降
    if(m_iMotionFresh[CEIL10a_MOTOR_DTH])
    {
        tempPositionY = rectStandArm.top();
        tempPositionX = rectStandArm.left();

        if(m_iMotionDataCur[CEIL10a_MOTOR_DTH] < STAND_ARM_DATA_MIN)
            m_iMotionDataCur[CEIL10a_MOTOR_DTH] = STAND_ARM_DATA_MIN;

        if(m_iMotionDataCur[CEIL10a_MOTOR_DTH] > STAND_ARM_DATA_MAX)
            m_iMotionDataCur[CEIL10a_MOTOR_DTH] = STAND_ARM_DATA_MAX;

        fRatio =(float) (STAND_ARM_PIX_MIN - STAND_ARM_PIX_MAX )/(STAND_ARM_DATA_MAX - STAND_ARM_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[CEIL10a_MOTOR_DTH] - STAND_ARM_DATA_MAX) * fRatio +STAND_ARM_PIX_MIN;

        rectStandArm.moveTo(tempPositionX,tempPositionY);
        pixStandArm->setGeometry(rectStandArm);
    }

    //2//////////////////////////////////////立柱探测器转动
    if(m_iMotionFresh[CEIL10a_MOTOR_DTA])
    {
        if(m_iMotionDataCur[CEIL10a_MOTOR_DTA] < STAND_DET_MIN)
            m_iMotionDataCur[CEIL10a_MOTOR_DTA] = STAND_DET_MIN;

        if(m_iMotionDataCur[CEIL10a_MOTOR_DTA] > STAND_DET_MAX)
            m_iMotionDataCur[CEIL10a_MOTOR_DTA] = STAND_DET_MAX;

        viewDet->rotate(m_iMotionDataCur[CEIL10a_MOTOR_DTA] - m_iMotionDataPre[CEIL10a_MOTOR_DTA]);
        viewDet->setGeometry(rectDet);
    }

    //3//////////////////////////////////////滑车平移
    if(m_iMotionFresh[CEIL10a_MOTOR_SID])
    {
        tempPositionX = rectCeil.left();
        tempPositionY = rectCeil.top();


        if(m_iMotionDataCur[CEIL10a_MOTOR_SID]< CEIL_DATA_MIN)
            m_iMotionDataCur[CEIL10a_MOTOR_SID] = CEIL_DATA_MIN;
        if(m_iMotionDataCur[CEIL10a_MOTOR_SID]> CEIL_DATA_MAX)
            m_iMotionDataCur[CEIL10a_MOTOR_SID] = CEIL_DATA_MAX;

        fRatio =(float) (CEIL_PIX_MAX - CEIL_PIX_MIN)/(CEIL_DATA_MAX - CEIL_DATA_MIN);
        tempPositionX = (m_iMotionDataCur[CEIL10a_MOTOR_SID] - CEIL_DATA_MIN) * fRatio +CEIL_PIX_MIN;

        rectCeil.moveTo(tempPositionX,tempPositionY);
        pixCeil->setGeometry(rectCeil);
    }

    //4//////////////////////////////////////球管升降
    if(m_iMotionFresh[CEIL10a_MOTOR_FID])
    {

        int tempCur = m_iMotionDataCur[CEIL10a_MOTOR_FID];

        if(tempCur < LIFT_DATA_MIN)
            tempCur = LIFT_DATA_MIN;

        if(tempCur > LIFT_DATA_MAX)
            tempCur = LIFT_DATA_MAX;

        fRatio =(float) (LIFT_SCALE_MAX - LIFT_SCALE_MIN )/(LIFT_DATA_MIN - LIFT_DATA_MAX );
        m_fLiftScale = (tempCur - LIFT_DATA_MAX) * fRatio +LIFT_SCALE_MIN;

        int m_iTempPosition;
        m_iTempPosition = TUBE_TOP - m_iLiftHeight *  (1.0f- m_fLiftScale);
        rectTube.moveTop(m_iTempPosition );

        rectLift.setHeight(m_iLiftHeight * m_fLiftScale);

        m_fLiftScaleCur = m_fLiftScale;
        viewLift->setGeometry(rectLift);
        viewLift->scale(1,m_fLiftScaleCur/m_fLiftScalePre);

        m_fLiftScalePre = m_fLiftScaleCur;
    }

    //5//////////////////////////////////////球管转动
    if(m_iMotionFresh[CEIL10a_MOTOR_ANG])
    {
        if( m_iMotionDataCur[CEIL10a_MOTOR_ANG] < TUBE_DATA_MIN)
            m_iMotionDataCur[CEIL10a_MOTOR_ANG] = TUBE_DATA_MIN;

        if( m_iMotionDataCur[CEIL10a_MOTOR_ANG] > TUBE_DATA_MAX)
            m_iMotionDataCur[CEIL10a_MOTOR_ANG] = TUBE_DATA_MAX;

        viewTube->rotate( m_iMotionDataCur[CEIL10a_MOTOR_ANG] - m_iMotionDataPre[CEIL10a_MOTOR_ANG]);
        viewTube->setGeometry(rectTube);
    }

    //6//////////////////////////////////////床面升降
    if(m_iMotionFresh[CEIL10a_MOTOR_BEH])
    {
        tempPositionX = rectTable.left();
        tempPositionY = rectTable.top();

        if(m_iMotionDataCur[CEIL10a_MOTOR_BEH] < TABLE_DATA_MIN)
            m_iMotionDataCur[CEIL10a_MOTOR_BEH] = TABLE_DATA_MIN;

        if(m_iMotionDataCur[CEIL10a_MOTOR_BEH] > TABLE_DATA_MAX)
            m_iMotionDataCur[CEIL10a_MOTOR_BEH] = TABLE_DATA_MAX;

        fRatio =(float) ( TABLE_PIX_MIN - TABLE_PIX_MAX)/(TABLE_DATA_MAX - TABLE_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[CEIL10a_MOTOR_BEH] - TABLE_DATA_MAX) * fRatio +TABLE_PIX_MIN;
        m_iTableDown = SYS_WID((TABLE_PIX_MIN - tempPositionY));

        rectTable.moveTo(tempPositionX,SYS_WID(tempPositionY));

        rectAccordion.moveTop(SYS_WID(tempPositionY) + SYS_WID(ACCORDION_REF));
        pixTable->setGeometry(rectTable);

        //7//////////////////////////////////////床下皮老虎伸缩

        fRatio =(float) (ACCORDION_HEIGHT+  m_iTableDown)/ACCORDION_HEIGHT;
        viewAccordion->resetTransform();
        viewAccordion->scale(1,fRatio);
        rectAccordion.setHeight(ACCORDION_HEIGHT + m_iTableDown );
        viewAccordion->setGeometry(rectAccordion);

    }

    //7//////////////////////////////////////床下探测器左右
    if(m_iMotionFresh[CEIL10a_MOTOR_DTP])
    {
        tempPositionX = rectTableDet.left();
        tempPositionY = rectTableDet.top();

        if(m_iMotionDataCur[CEIL10a_MOTOR_DTP] < TABLE_DET_DATA_MIN)
            m_iMotionDataCur[CEIL10a_MOTOR_DTP] = TABLE_DET_DATA_MIN;

        if(m_iMotionDataCur[CEIL10a_MOTOR_DTP] > TABLE_DET_DATA_MAX)
            m_iMotionDataCur[CEIL10a_MOTOR_DTP] = TABLE_DET_DATA_MAX;

        fRatio =(float) (TABLE_DET_PIX_MAX - TABLE_DET_PIX_MIN)/(TABLE_DET_DATA_MAX - TABLE_DET_DATA_MIN);
        tempPositionX = (m_iMotionDataCur[CEIL10a_MOTOR_DTP] - TABLE_DET_DATA_MIN) * fRatio +TABLE_DET_PIX_MIN;

        rectTableDet.moveTo(tempPositionX,tempPositionY);
        pixTableDet->setGeometry(rectTableDet);
    }

    for(int mIdx = 0 ;mIdx < CEIL10a_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = m_iMotionDataCur[mIdx];
    }

}
