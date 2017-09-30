#include "motion_uarm8.h"

#include "resource_manager.h"

#define UARM8_ARM_DISP_MIN              ( -40 )
#define UARM8_ARM_DISP_MAX              ( 65 )
#define UARM8_ARM_DATA_MIN              ( 180 )
#define UARM8_ARM_DATA_MAX              ( 50 )
#define UARM8_ARM_ANG_MIN               ( -30 )
#define UARM8_ARM_ANG_MAX               ( 120 )

#define UARM8_TUBE_LEFT         (SYS_WID( 310 ))
#define UARM8_TUBE_TOP          (SYS_HEI( 162 ))
#define UARM8_TUBE_DISP_MIN     (SYS_WID( 160 ))
#define UARM8_TUBE_DISP_MAX     (SYS_WID( 310 ))
#define UARM8_TUBE_DATA_MIN             ( 100 )
#define UARM8_TUBE_DATA_MAX             ( 180 )

#define UARM8_DET_LEFT          (SYS_WID( 10 ))
#define UARM8_DET_TOP           (SYS_HEI( 150 ))
#define UARM8_DET_ANG_MIN       ( -45 )
#define UARM8_DET_ANG_MAX       ( 45 )

CMotionUarm8::CMotionUarm8(QWidget *parent) :
    CMotionBase8(parent)
{

    setObjectName("CMotionUarm8");

    resize(SYS_WID(450),SYS_HEI(450));

    pixBackGround   = new QFrame(this);
    pixBackGround->setStyleSheet(g_skinBase->GetStyleMapStr("UARM8_MOVIE_STAND"));
    pixBackGround->setGeometry(0,0,SYS_WID(450),SYS_HEI(450));

    pixUarm         = new QLabel();
    pixUarm->setStyleSheet(g_skinBase->GetStyleMapStr("UARM8_MOVIE_UARM"));
    rectUarm.setRect(0,0,SYS_WID(450),SYS_HEI(450));
    pixUarm->setGeometry(rectUarm);

    pixTube         = new QFrame(pixUarm);
    pixTube->setStyleSheet(g_skinBase->GetStyleMapStr("UARM8_MOVIE_TUBE"));
    rectTube.setRect(UARM8_TUBE_LEFT,UARM8_TUBE_TOP,SYS_WID(120),SYS_HEI(120));
    pixTube->setGeometry(rectTube);

    pixDet          = new QFrame();
    pixDet->setStyleSheet(g_skinBase->GetStyleMapStr("UARM8_MOVIE_DET"));
    rectDet.setRect(UARM8_DET_LEFT,UARM8_DET_TOP,SYS_WID(130),SYS_HEI(130));
    pixDet->setGeometry(rectDet);

    myMotionInit();

    for(int mIdx = 0 ; mIdx < UARM8_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = 0;
        m_iMotionDataCur[mIdx] = 1;
        m_iMotionFresh[mIdx] = false;
    }

}

void CMotionUarm8::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
    timerMotionFresh->start(6*TIME_MOTION_FRESH);   //将U臂的刷新速度由原来的10f/s 降为5f/s
}

void CMotionUarm8::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
    timerMotionFresh->stop();
}
void CMotionUarm8::myMotionInit()
{
    CMotionBase::myMotionInit();

    sceneDet->setParent(pixUarm);
    sceneDet->addWidget(pixDet);
    viewDet->setParent(pixUarm);
    viewDet->setScene(sceneDet);
    viewDet->setGeometry(rectDet);

    sceneUarm       = new QGraphicsScene(this);
    viewUarm        = new QGraphicsView(this);

    sceneUarm->addWidget(pixUarm);
    viewUarm->setScene(sceneUarm);
    viewUarm->setGeometry(rectUarm);
    viewUarm->setFocusPolicy(Qt::NoFocus);
    viewUarm->setFrameShape(QFrame::NoFrame);
    viewUarm->setFrameShadow(QFrame::Plain);
    viewUarm->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewUarm->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //FullViewportUpdate//MinimalViewportUpdate//SmartViewportUpdate//BoundingRectViewportUpdate//NoViewportUpdate
    viewUarm->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    viewUarm->setStyleSheet("background:transparent");

    viewUarm->raise();
    viewDet->raise();
    pixDet->raise();
    pixTube->raise();
}
void CMotionUarm8::OnMotionFresh()
{
    int  tempPositionY,tempPositionX;
    float fRatio;

    for(int mIdx = 0 ;mIdx < UARM8_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataCur[mIdx] = g_systemDb->g_dbMachine.CurrentData[mIdx];
        if(m_iMotionDataCur[mIdx] != m_iMotionDataPre[mIdx])
        {
            m_iMotionFresh[mIdx] = true;
        }else
        {
            m_iMotionFresh[mIdx] = false;
        }
        m_iMotionDataPre[mIdx] = m_iMotionDataCur[mIdx];
    }

    //0//////////////////////////////////////U臂升降移动
    if(m_iMotionFresh[UARM8_MOTOR_HEI])
    {
        tempPositionY = rectUarm.top();
        tempPositionX = rectUarm.left();

        if(m_iMotionDataCur[UARM8_MOTOR_HEI] > UARM8_ARM_DATA_MIN)
            m_iMotionDataCur[UARM8_MOTOR_HEI] = UARM8_ARM_DATA_MIN;

        if(m_iMotionDataCur[UARM8_MOTOR_HEI] < UARM8_ARM_DATA_MAX)
            m_iMotionDataCur[UARM8_MOTOR_HEI] = UARM8_ARM_DATA_MAX;

        fRatio =(float) (UARM8_ARM_DISP_MAX - UARM8_ARM_DISP_MIN )/(UARM8_ARM_DATA_MAX - UARM8_ARM_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[UARM8_MOTOR_HEI] - UARM8_ARM_DATA_MIN) * fRatio + UARM8_ARM_DISP_MIN;

        rectUarm.moveTo(tempPositionX,tempPositionY);
        viewUarm->setGeometry(rectUarm);
    }

    //1//////////////////////////////////////球管运动
    if(m_iMotionFresh[UARM8_MOTOR_SID])
    {
        tempPositionY = rectTube.top();
        tempPositionX = rectTube.left();

        if(m_iMotionDataCur[UARM8_MOTOR_SID] < UARM8_TUBE_DATA_MIN)
            m_iMotionDataCur[UARM8_MOTOR_SID] = UARM8_TUBE_DATA_MIN;

        if(m_iMotionDataCur[UARM8_MOTOR_SID] > UARM8_TUBE_DATA_MAX)
            m_iMotionDataCur[UARM8_MOTOR_SID] = UARM8_TUBE_DATA_MAX;

        fRatio =(float) (UARM8_TUBE_DISP_MAX - UARM8_TUBE_DISP_MIN )/(UARM8_TUBE_DATA_MAX - UARM8_TUBE_DATA_MIN);
        tempPositionX = (m_iMotionDataCur[UARM8_MOTOR_SID] - UARM8_TUBE_DATA_MIN) * fRatio + UARM8_TUBE_DISP_MIN;

        rectTube.moveTo(tempPositionX,tempPositionY);
        pixTube->setGeometry(rectTube);

    }

    //2//////////////////////////////////////U臂角度转动
    if(m_iMotionFresh[UARM8_MOTOR_ANG])
    {
        if(m_iMotionDataCur[UARM8_MOTOR_ANG] < UARM8_ARM_ANG_MIN)
            m_iMotionDataCur[UARM8_MOTOR_ANG] = UARM8_ARM_ANG_MIN;

        if(m_iMotionDataCur[UARM8_MOTOR_ANG] > UARM8_ARM_ANG_MAX)
            m_iMotionDataCur[UARM8_MOTOR_ANG] = UARM8_ARM_ANG_MAX;

        viewUarm->resetTransform();
        viewUarm->rotate(m_iMotionDataCur[UARM8_MOTOR_ANG] - 90.0f);
    }

    //3//////////////////////////////////////探测器转动
    if(m_iMotionFresh[UARM8_MOTOR_DTA])
    {
        if(m_iMotionDataCur[UARM8_MOTOR_DTA] < UARM8_DET_ANG_MIN)
            m_iMotionDataCur[UARM8_MOTOR_DTA] = UARM8_DET_ANG_MIN;

        if(m_iMotionDataCur[UARM8_MOTOR_DTA] > UARM8_DET_ANG_MAX)
            m_iMotionDataCur[UARM8_MOTOR_DTA] = UARM8_DET_ANG_MAX;

        viewDet->resetTransform();
        viewDet->rotate(m_iMotionDataCur[UARM8_MOTOR_DTA]);
    }
}
