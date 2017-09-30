#include "motion_uarm10.h"
#include "resource_manager.h"

#define UARM10_ARM_DISP_MIN              ( -40 )
#define UARM10_ARM_DISP_MAX              ( 65 )
#define UARM10_ARM_DATA_MIN              ( 180 )
#define UARM10_ARM_DATA_MAX              ( 50 )
#define UARM10_ARM_ANG_MIN               ( 0 )
#define UARM10_ARM_ANG_MAX               ( 120 )

#define UARM10_TUBE_DISP_MIN             ( 160 )
#define UARM10_TUBE_DISP_MAX             ( 310 )
#define UARM10_TUBE_DATA_MIN             ( 100 )
#define UARM10_TUBE_DATA_MAX             ( 180 )

#define UARM10_DET_LEFT                  ( -28 )
#define UARM10_DET_TOP                   ( 130 )
#define UARM10_DET_ANG_MIN               ( -45 )
#define UARM10_DET_ANG_MAX               ( 45 )

CMotionUarm10::CMotionUarm10(QWidget *parent) :
    CMotionBase10(parent)
{

    setObjectName("CMotionUarm10");

    resize(SYS_WID(420),SYS_HEI(420));

    pixBackGround    = new QFrame(this);
    pixBackGround->setStyleSheet(g_skinBase->GetStyleMapStr("UARM10_MOVIE_STAND"));
    pixBackGround->setGeometry(0,0,SYS_WID(420),SYS_HEI(420));

    pixUarm     = new QLabel();
    pixUarm->setStyleSheet(g_skinBase->GetStyleMapStr("UARM10_MOVIE_UARM"));
    rectUarm.setRect(0,0,SYS_WID(420),SYS_HEI(420));
    pixUarm->setGeometry(rectUarm);

    pixTube     = new QFrame(pixUarm);
    pixTube->setStyleSheet(g_skinBase->GetStyleMapStr("UARM10_MOVIE_TUBE"));
    rectTube.setRect(SYS_WID(265),SYS_HEI(150),SYS_WID(112),SYS_HEI(112));
    pixTube->setGeometry(rectTube);

    pixDet      = new QFrame();
    pixDet->setStyleSheet(g_skinBase->GetStyleMapStr("UARM10_MOVIE_DET"));
    rectDet.setRect(SYS_WID(10),SYS_HEI(150),SYS_WID(121),SYS_HEI(121));
    pixDet->setGeometry(rectDet);

    myMotionInit();

    for(int mIdx = 0 ; mIdx < UARM10_MOTION_MAX ;mIdx++)
    {
        m_iMotionDataPre[mIdx] = 0xffff;
        m_iMotionDataCur[mIdx] = 1;
        m_iMotionFresh[mIdx] = false;
    }

}

void CMotionUarm10::myMotionInit()
{
    CMotionBase::myMotionInit();

    sceneUarm       = new QGraphicsScene(this);
    viewUarm        = new QGraphicsView(this);

    sceneDet->setParent(pixUarm);
    viewDet->setParent(pixUarm);

    pixBackGround->raise();
    viewUarm->raise();
    viewDet->raise();
    pixTube->raise();

    sceneDet->addWidget(pixDet);
    viewDet->setScene(sceneDet);
    viewDet->setGeometry(rectDet);

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
    viewUarm->show();

}
void CMotionUarm10::OnMotionFresh()
{
    int  tempPositionY,tempPositionX;
    float fRatio;

    for(int mIdx = 0 ;mIdx < UARM10_MOTION_MAX ;mIdx++)
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
    if(m_iMotionFresh[UARM10_MOTOR_HEI])
    {
        tempPositionY = rectUarm.top();
        tempPositionX = rectUarm.left();

        if(m_iMotionDataCur[UARM10_MOTOR_HEI] > UARM10_ARM_DATA_MIN)
            m_iMotionDataCur[UARM10_MOTOR_HEI] = UARM10_ARM_DATA_MIN;

        if(m_iMotionDataCur[UARM10_MOTOR_HEI] < UARM10_ARM_DATA_MAX)
            m_iMotionDataCur[UARM10_MOTOR_HEI] = UARM10_ARM_DATA_MAX;

        fRatio =(float) (UARM10_ARM_DISP_MAX - UARM10_ARM_DISP_MIN )/(UARM10_ARM_DATA_MAX - UARM10_ARM_DATA_MIN);
        tempPositionY = (m_iMotionDataCur[UARM10_MOTOR_HEI] - UARM10_ARM_DATA_MIN) * fRatio + UARM10_ARM_DISP_MIN;

        rectUarm.moveTo(tempPositionX,tempPositionY);
        viewUarm->setGeometry(rectUarm);
    }

    //1//////////////////////////////////////球管运动
    if(m_iMotionFresh[UARM10_MOTOR_SID])
    {
        tempPositionY = rectTube.top();
        tempPositionX = rectTube.left();

        if(m_iMotionDataCur[UARM10_MOTOR_SID] < UARM10_TUBE_DATA_MIN)
            m_iMotionDataCur[UARM10_MOTOR_SID] = UARM10_TUBE_DATA_MIN;

        if(m_iMotionDataCur[UARM10_MOTOR_SID] > UARM10_TUBE_DATA_MAX)
            m_iMotionDataCur[UARM10_MOTOR_SID] = UARM10_TUBE_DATA_MAX;

        fRatio =(float) (UARM10_TUBE_DISP_MAX - UARM10_TUBE_DISP_MIN )/(UARM10_TUBE_DATA_MAX - UARM10_TUBE_DATA_MIN);
        tempPositionX = (m_iMotionDataCur[UARM10_MOTOR_SID] - UARM10_TUBE_DATA_MIN) * fRatio + UARM10_TUBE_DISP_MIN;

        rectTube.moveTo(tempPositionX,tempPositionY);
        pixTube->setGeometry(rectTube);

    }

    //2//////////////////////////////////////U臂角度转动
    if(m_iMotionFresh[UARM10_MOTOR_ANG])
    {
        if(m_iMotionDataCur[UARM10_MOTOR_ANG] < UARM10_ARM_ANG_MIN)
            m_iMotionDataCur[UARM10_MOTOR_ANG] = UARM10_ARM_ANG_MIN;

        if(m_iMotionDataCur[UARM10_MOTOR_ANG] > UARM10_ARM_ANG_MAX)
            m_iMotionDataCur[UARM10_MOTOR_ANG] = UARM10_ARM_ANG_MAX;

        viewUarm->resetTransform();
        viewUarm->rotate(m_iMotionDataCur[UARM10_MOTOR_ANG] - 90.0f);
    }

    //3//////////////////////////////////////探测器转动
    if(m_iMotionFresh[UARM10_MOTOR_DTA])
    {
        if(m_iMotionDataCur[UARM10_MOTOR_DTA] < UARM10_DET_ANG_MIN)
            m_iMotionDataCur[UARM10_MOTOR_DTA] = UARM10_DET_ANG_MIN;

        if(m_iMotionDataCur[UARM10_MOTOR_DTA] > UARM10_DET_ANG_MAX)
            m_iMotionDataCur[UARM10_MOTOR_DTA] = UARM10_DET_ANG_MAX;

        viewDet->resetTransform();
        viewDet->rotate(m_iMotionDataCur[UARM10_MOTOR_DTA]);
    }

}

