#include "motion_rail8.h"
#include "resource_manager.h"

#define FID_DATA_MIN    (50)
#define FID_DATA_MAX    (180)
#define FID_PIX_MIN     SYS_HEI(0)
#define FID_PIX_MAX     SYS_HEI(100)

#define ANG_DATA_MIN    (-30)
#define ANG_DATA_MAX    (120)

#define DET_LEFT        (SYS_WID(32))
#define DTH_DATA_MIN    (50)
#define DTH_DATA_MAX    (180)
#define DTH_PIX_MIN     SYS_HEI(120)
#define DTH_PIX_MAX     SYS_HEI(220)

#define SID_DATA_MIN    (110)
#define SID_DATA_MAX    (310)
#define SID_PIX_MIN     SYS_HEI(110)
#define SID_PIX_MAX     SYS_HEI(320)

//TABLE
#define TABLE_LEFT          (SYS_WID( 147 ))
#define TABLE_TOP           (SYS_HEI( 300 ))
#define TABLE_WIDTH         (SYS_WID( 227 ))
#define TABLE_HEIGHT        (SYS_HEI( 26 ))
#define TABLE_PIX_MIN       ( 295 )    /*(SYS_HEI( 295 ))*/
#define TABLE_PIX_MAX       ( 330 )    /*(SYS_HEI( 330 ))*/
#define TABLE_DATA_MIN      ( 35 )     /*(SYS_HEI( 35 ))*/
#define TABLE_DATA_MAX      ( 70 )     /*(SYS_HEI( 70 ))*/

//TABLE_DET
#define TABLE_DET_LEFT      (SYS_WID( 80 ))
#define TABLE_DET_TOP       (SYS_HEI( 6 ))
#define TABLE_DET_WIDTH     (SYS_WID( 58 ))
#define TABLE_DET_HEIGHT    (SYS_HEI( 9 ))
#define TABLE_DET_PIX_MIN   (SYS_WID( 58 ))
#define TABLE_DET_PIX_MAX   (SYS_WID( 156 ))
#define TABLE_DET_DATA_MIN  (SYS_WID( 170 ))
#define TABLE_DET_DATA_MAX  (SYS_WID( 264 ))

//ACCORDION
#define ACCORDION_LEFT      (SYS_WID( 228 ))
#define ACCORDION_TOP       (TABLE_TOP + SYS_HEI( 26 ))
#define ACCORDION_WIDTH     (SYS_WID( 116 ))
#define ACCORDION_HEIGHT    (SYS_HEI( 48 ))

//POSITION REFERENCE
#define ACCORDION_REF       ( 24 )
#define TABLE_DET_REF       ( 6 )


CMotionRail8::CMotionRail8(QWidget *parent) :
    CMotionBase8(parent)
{

    setObjectName("CMotionRail8");

    resize(SYS_WID(450),SYS_HEI(450));

    for(int mIdx = 0 ; mIdx < RAIL8_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = 0;
        m_iMotionDataCur[mIdx] = 0;
        m_iMotionFresh[mIdx] = false;
    }

    m_iTableDown = 0;

    myMotionInit();
}


void CMotionRail8::myMotionInit()
{

    CMotionBase::myMotionInit();

    pixBackGround = new QFrame(this);
    pixBackGround->setStyleSheet(g_skinBase->GetStyleMapStr("RAIL8_MOVIE_BACK"));
    pixBackGround->setGeometry(0,0,SYS_WID(450),SYS_HEI(450));

    pixStand = new QLabel(this);
    pixStand->setStyleSheet(g_skinBase->GetStyleMapStr("RAIL8_MOVIE_STAND"));
    rectStand.setRect(SYS_WID(150),SYS_HEI(110),SYS_WID(120),SYS_HEI(256));
    pixStand->setGeometry(rectStand);
    //connect(pixStand,SIGNAL())

    pixTube = new QFrame();
    pixTube->setStyleSheet(g_skinBase->GetStyleMapStr("RAIL8_MOVIE_TUBE"));
    rectTube.setRect(0,SYS_HEI(50),SYS_WID(120),SYS_HEI(120));
    pixTube->setGeometry(0,0,SYS_WID(120),SYS_HEI(120));

    pixTable = new QLabel(this);
    pixTable->setStyleSheet(g_skinBase->GetStyleMapStr("RAIL8_MOVIE_TABLE"));
    rectTable.setRect(TABLE_LEFT,TABLE_TOP,SYS_WID(276),SYS_HEI(30));
    pixTable->setGeometry(rectTable);

    pixBucky = new QFrame(pixTable);
    pixBucky->setStyleSheet(g_skinBase->GetStyleMapStr("RAIL8_MOVIE_BUCKY"));
    rectTableDet.setRect(SYS_WID(70),SYS_HEI(6),SYS_WID(63),SYS_HEI(10));
    pixBucky->setGeometry(rectTableDet);

    pixAccordion = new QFrame();
    pixAccordion->setStyleSheet(g_skinBase->GetStyleMapStr("RAIL8_MOVIE_ACCORD"));
    pixAccordion->setGeometry(0,0,ACCORDION_WIDTH,ACCORDION_HEIGHT);
    rectAccordion.setRect(ACCORDION_LEFT,ACCORDION_TOP,ACCORDION_WIDTH,ACCORDION_HEIGHT);

    pixDet = new QFrame(this);
    pixDet->setStyleSheet(g_skinBase->GetStyleMapStr("RAIL8_MOVIE_DET"));
    rectDet.setRect(DET_LEFT,SYS_HEI(200),SYS_WID(22),SYS_HEI(96));
    pixDet->setGeometry(rectDet);

    pSceneAccordion     = new QGraphicsScene(this);
    pSceneAccordion->addWidget(pixAccordion);
    viewAccordion      = new QGraphicsView(pSceneAccordion,this);

    viewAccordion->setGeometry(rectAccordion);
    viewAccordion->setFocusPolicy(Qt::NoFocus);
    viewAccordion->setFrameShape(QFrame::NoFrame);
    viewAccordion->setFrameShadow(QFrame::Plain);
    viewAccordion->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewAccordion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewAccordion->setStyleSheet("background:transparent");

    sceneTube->setParent(pixStand);
    sceneTube->addWidget(pixTube);
    viewTube->setParent(pixStand);
    viewTube->setScene(sceneTube);
    viewTube->setGeometry(rectTube);
    viewTube->rotate(0);
    viewTube->raise();

    pixBackGround->raise();
    pixStand->raise();
    pixTube->raise();
    viewAccordion->raise();
    pixTable->raise();
    pixBucky->raise();
    pixDet->raise();

}
void CMotionRail8::OnMotionFresh()
{
    int  tempPositionY,tempPositionX;
    float fRatio;

    for(int mIdx = 0 ;mIdx < RAIL8_MOTION_MAX ;mIdx++)
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

    if(m_iMotionFresh[RAIL8_MOTOR_FID])
        m_iMotionFresh[RAIL8_MOTOR_ANG] = true;


    //1//////////////////////////////////////立柱球管升降
    if(m_iMotionFresh[RAIL8_MOTOR_FID])
    {
        tempPositionY = rectTube.top();
        tempPositionX = rectTube.left();

        if(m_iMotionDataCur[RAIL8_MOTOR_FID] < FID_DATA_MIN)
            m_iMotionDataCur[RAIL8_MOTOR_FID] = FID_DATA_MIN;

        if(m_iMotionDataCur[RAIL8_MOTOR_FID] > FID_DATA_MAX)
            m_iMotionDataCur[RAIL8_MOTOR_FID] = FID_DATA_MAX;

        fRatio =(float) (FID_PIX_MIN - FID_PIX_MAX )/(FID_DATA_MAX - FID_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[RAIL8_MOTOR_FID] - FID_DATA_MAX) * fRatio + FID_PIX_MIN;

        rectTube.moveTo(tempPositionX,tempPositionY);
        viewTube->setGeometry(rectTube);
    }
    //2//////////////////////////////////////立柱探测器升降
    if(m_iMotionFresh[RAIL8_MOTOR_DTH])//
    {
        tempPositionY = rectDet.top();
        tempPositionX = rectDet.left();

        if(m_iMotionDataCur[RAIL8_MOTOR_DTH] < DTH_DATA_MIN)
            m_iMotionDataCur[RAIL8_MOTOR_DTH] = DTH_DATA_MIN;

        if(m_iMotionDataCur[RAIL8_MOTOR_DTH] > DTH_DATA_MAX)
            m_iMotionDataCur[RAIL8_MOTOR_DTH] = DTH_DATA_MAX;

        fRatio =(float) (DTH_PIX_MIN - DTH_PIX_MAX )/(DTH_DATA_MAX - DTH_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[RAIL8_MOTOR_DTH] - DTH_DATA_MAX) * fRatio + DTH_PIX_MIN;

        rectDet.moveTo(tempPositionX,tempPositionY);
        pixDet->setGeometry(rectDet);
    }

    //3//////////////////////////////////////球管转动
    if(m_iMotionFresh[RAIL8_MOTOR_ANG])
    {

        if( m_iMotionDataCur[RAIL8_MOTOR_ANG] < ANG_DATA_MIN)
            m_iMotionDataCur[RAIL8_MOTOR_ANG] = ANG_DATA_MIN;

        if( m_iMotionDataCur[RAIL8_MOTOR_ANG] > ANG_DATA_MAX)
            m_iMotionDataCur[RAIL8_MOTOR_ANG] = ANG_DATA_MAX;

        viewTube->rotate( m_iMotionDataCur[RAIL8_MOTOR_ANG] -  m_iMotionDataPre[RAIL8_MOTOR_ANG]);
    }

    //4//////////////////////////////////////立柱移动控制
    if(m_iMotionFresh[RAIL8_MOTOR_SID])
    {
        tempPositionX = rectStand.left();
        tempPositionY = rectStand.top();

        if(m_iMotionDataCur[RAIL8_MOTOR_SID]< SID_DATA_MIN)
            m_iMotionDataCur[RAIL8_MOTOR_SID] = SID_DATA_MIN;
        if(m_iMotionDataCur[RAIL8_MOTOR_SID]> SID_DATA_MAX)
            m_iMotionDataCur[RAIL8_MOTOR_SID] = SID_DATA_MAX;

        fRatio =(float) (SID_PIX_MAX - SID_PIX_MIN)/(SID_DATA_MAX - SID_DATA_MIN);
        tempPositionX = (m_iMotionDataCur[RAIL8_MOTOR_SID] - SID_DATA_MIN) * fRatio +SID_PIX_MIN;

        rectStand.moveTo(tempPositionX,tempPositionY);
        pixStand->setGeometry(rectStand);
    }

    //5//////////////////////////////////////床面升降
    if(m_iMotionFresh[RAIL8_MOTOR_BEH])
    {
        tempPositionX = rectTable.left();
        tempPositionY = rectTable.top();

        if(m_iMotionDataCur[RAIL8_MOTOR_BEH] < TABLE_DATA_MIN)
            m_iMotionDataCur[RAIL8_MOTOR_BEH] = TABLE_DATA_MIN;

        if(m_iMotionDataCur[RAIL8_MOTOR_BEH] > TABLE_DATA_MAX)
            m_iMotionDataCur[RAIL8_MOTOR_BEH] = TABLE_DATA_MAX;

        fRatio =(float) ( TABLE_PIX_MIN - TABLE_PIX_MAX)/(TABLE_DATA_MAX - TABLE_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[RAIL8_MOTOR_BEH] - TABLE_DATA_MAX) * fRatio +TABLE_PIX_MIN;
        m_iTableDown = SYS_HEI((TABLE_PIX_MIN - tempPositionY));

        rectTable.moveTo(tempPositionX,SYS_HEI(tempPositionY));

        rectAccordion.moveTop(SYS_HEI(tempPositionY) + SYS_HEI(ACCORDION_REF));
        pixTable->setGeometry(rectTable);

        //7//////////////////////////////////////床下皮老虎伸缩

        fRatio =(float) (ACCORDION_HEIGHT+  m_iTableDown)/ACCORDION_HEIGHT;
        viewAccordion->resetTransform();
        viewAccordion->scale(1,fRatio);
        rectAccordion.setHeight(ACCORDION_HEIGHT + m_iTableDown );
        viewAccordion->setGeometry(rectAccordion);

    }

    //6//////////////////////////////////////床下探测器左右
    if(m_iMotionFresh[RAIL8_MOTOR_DTP])//
    {
        tempPositionX = rectTableDet.left();
        tempPositionY = rectTableDet.top();

        if(m_iMotionDataCur[RAIL8_MOTOR_DTP] < TABLE_DET_DATA_MIN)
            m_iMotionDataCur[RAIL8_MOTOR_DTP] = TABLE_DET_DATA_MIN;

        if(m_iMotionDataCur[RAIL8_MOTOR_DTP] > TABLE_DET_DATA_MAX)
            m_iMotionDataCur[RAIL8_MOTOR_DTP] = TABLE_DET_DATA_MAX;

        fRatio =(float) (TABLE_DET_PIX_MAX - TABLE_DET_PIX_MIN)/(TABLE_DET_DATA_MAX - TABLE_DET_DATA_MIN);
        tempPositionX = (m_iMotionDataCur[RAIL8_MOTOR_DTP] - TABLE_DET_DATA_MIN) * fRatio +TABLE_DET_PIX_MIN;

        rectTableDet.moveTo(tempPositionX,tempPositionY);
        pixBucky->setGeometry(rectTableDet);
    }


    for(int mIdx = 0 ;mIdx < RAIL8_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = m_iMotionDataCur[mIdx];
    }

}
