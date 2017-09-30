#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTransform>
#include <QMessageBox>
#include <QVector3D>
#include <QSettings>

#include "main_base_ndt10.h"
#include "sys_database.h"
#include "resource_manager.h"

#define NDT_XRAY_OPEN   0
#define NDT_XRAY_CLOSE  1

#define NDT_PAGE_STAND              0
#define NDT_PAGE_TABLE               1
#define NDT_PAGE_TUBE                 2
#define NDT_PAGE_SCAN_LONG     3      /*long table scan page*/
#define NDT_PAGE_SCAN_ROUND  4      /*large round table scan page*/
#define NDT_PAGE_SCAN_SMALL    5      /*small round table scan page*/
#define NDT_PAGE_SCAN_ARM       6      /* ARM scan page*/

#define NDT_FRESH_INTERVAL      400
#define NDT_BTN_TITLE                   0
#define  NDT_AUTO_POS_INTERVAL   1500

#define NDT_AUTO_MODE_DEFAULT            -1
#define NDT_AUTO_MODE_TABLE                  0
#define NDT_AUTO_MODE_ROUND_FLAT      1
#define NDT_AUTO_MODE_SMALL                 2
#define NDT_AUTO_MODE_ROUND_ANG      3
#define NDT_AUTO_MODE_ARM                    4

#define NDT_AUTO_STAT00         0
#define NDT_AUTO_STAT01         1
#define NDT_AUTO_STAT02         2
#define NDT_AUTO_STAT03         3
#define NDT_AUTO_STAT04         4
#define  NDT_AUTO_STAT05        5
#define NDT_AUTO_STAT06         6
#define NDT_AUTO_STAT07         7
#define NDT_AUTO_STAT08         8
#define NDT_AUTO_STAT09         9
#define NDT_AUTO_STAT10         10
#define NDT_AUTO_STAT11         11


#define NDT_PANEL_BORDER_CENTOR   0
#define NDT_PANEL_BORDER_FRONT     1
#define NDT_PANEL_BORDER_BACK        2

#define NDT_EXP_DELAY_LONG        20
#define NDT_EXP_DELAY_ROUND     15
#define NDT_EXP_DELAY_SMALL       15
#define NDT_EXP_DELAY_EN              0

#define NDT_KEY_BASE_STAND         0x10
#define NDT_KEY_BASE_TABLE           0x30
#define NDT_KEY_BASE_TUBE            0x50
#define NDT_KEY_BASE_LONG           0x70
#define NDT_KEY_BASE_ROUND         0x90
#define NDT_KEY_BASE_SMALL           0xA0
#define NDT_KEY_BASE_ARM              0xC0

#define SMALL_TABLE_CENTER_X               SYS_WID(575)
#define SMALL_TABLE_CENTER_Y               SYS_HEI(300)
#define SMALL_PANEL_RECT_WIDTH         SYS_WID(70)
#define SMALL_TABLE_CENTER_RL               SYS_HEI(220)

#define ROUND_TABLE_CENTER_X               SYS_WID(575)
#define ROUND_TABLE_CENTER_Y               SYS_HEI(300)
#define ROUND_PANEL_RECT_WIDTH              SYS_HEI(70)
#define ROUND_TABLE_CENTER_RL               SYS_HEI(280)
#define ROUND_TABLE_CENTER_RS               SYS_HEI(80)

CMainBaseNdt10::CMainBaseNdt10(QWidget *parent) :
    CMainBase(parent)
{

    AutoPositionIndex = NDT_AUTO_MODE_DEFAULT;

    statLongTableAuto    = NDT_AUTO_STAT00;
    statRoundTableAuto  = NDT_AUTO_STAT00;               ///测试模式
    statSmallTableAuto    = NDT_AUTO_STAT00;
    statArmTableAuto      = NDT_AUTO_STAT00;

    bManualPosition = false;

    mExpDelayCtr = NDT_EXP_DELAY_EN;            //默认允许曝光
    mLongExpDir = 1;
    mArmExpDir = 1;
    mRoundPanelIndex = 2;                   //序号0，1为圆形背景图标
    mRoundExpDir = 1;

    mWatchDogCtr = 0;

    mSmallPanelIndex = 2;
    mSmallExpDir = 1;

    bLongExpStill       = false;

    gStrWarnings = "";
    mBrColor = Qt::green;

#ifdef QT_ARCH_ARM
    mMoveReadyMask = false;                      //在机架设备上，开启位置到位检测
#else
    mMoveReadyMask = true;                       //在遥控设备上，屏蔽位置到位检测。
#endif

    //开机清除所有模式进入标识
    isLongTablePos = false;
    isRoundTablePos = false;
    isSmallTablePos = false;
    isArmTablePos = false;

    m_pageIdxBuf = m_pageIdx = NDT_PAGE_STAND;

    keyEventBtn = NULL;

    //resize frame size
    resize(g_sysWidth,g_sysHeight);

    this->setAutoFillBackground(true);

    QPalette palette;
#ifdef QT_ARCH_ARM
    palette.setBrush(QPalette::Background, QBrush(QPixmap(QString("/sdcard/home/fa") + "/8090/png00/background.png")));
#else
    palette.setBrush(QPalette::Background, QBrush(QColor(68,68,68)));
#endif
    this->setPalette(palette);

    mech = new CSystemMech();
    BuildLcdDisplay();

    BuildMenuScanBtn();        //长台，大圆台，小圆台扫描

    ParamLoad();                    //加载参数

    BuidMenuBottonBtn();        //底部按钮
    BuidTubeCtrlBtn();          //球管控制页面
    BuidStandCtrlBtn();         //立柱控制页面
    BuidTableCtrlBtn();         //平台控制页面
    BuidSmartLongCtrlBtn();          //长台扫描页面动作支持
    BuidSmartRoundCtrlBtn();   //大圆台扫描页面动作支持
    BuidSmartSmallCtrlBtn();
    BuidSmartArmCtrlBtn();

    BuildLongVisiable();

    BuildRoundVisiable(arrRenderRoundR30,30);
    BuildRoundVisiable(arrRenderRoundR20,20);
    BuildRoundVisiable(arrRenderRoundR18,18);
    BuildRoundVisiable(arrRenderRoundR15,15);
    arrRenderRoundR30.at(2)->setBeShow(true);
    arrRenderRoundR20.at(2)->setBeShow(true);
    arrRenderRoundR18.at(2)->setBeShow(true);
    arrRenderRoundR15.at(2)->setBeShow(true);

    arrRenderRound = &arrRenderRoundR30;
    mRoundTableRotateStep = 30;

    BuildSmallVisiable(arrRenderSmallR60,60);
    BuildSmallVisiable(arrRenderSmallR45,45);
    BuildSmallVisiable(arrRenderSmallR40,40);
    BuildSmallVisiable(arrRenderSmallR36,36);

    arrRenderSmallR60.at(2)->setBeShow(true);
    arrRenderSmallR45.at(2)->setBeShow(true);
    arrRenderSmallR40.at(2)->setBeShow(true);
    arrRenderSmallR36.at(2)->setBeShow(true);

    arrRenderSmall = &arrRenderSmallR60;
    mSmallAngleRotate = 60;

    BuildArmVisiable();

    tmNdtFresh = new QTimer(this);
    tmNdtFresh->setInterval(NDT_FRESH_INTERVAL);
    connect(tmNdtFresh,SIGNAL(timeout()),this,SLOT(OnNdtDataFresh()));

    //disable tips for medical system
    if(lbCompletionTips)
        lbCompletionTips->setVisible(false);

    tmAutoPosition = new QTimer(this);
    tmAutoPosition->setInterval(NDT_AUTO_POS_INTERVAL);
    connect(tmAutoPosition,SIGNAL(timeout()),this,SLOT(OnAutoPositionTimer()));

    tmArmTubeFollow = new QTimer(this);
    tmArmTubeFollow->setInterval(400);
    connect(tmArmTubeFollow,SIGNAL(timeout()),this,SLOT(OnTimerTubeFollow()));

    myPopupPosInit();           //初始化弹出框位置

    myViewInit();               //初始化视图
    mySceneInit();              //初始化场景

}

void CMainBaseNdt10::LongVisableCtrl()
{
    if(!isLongTablePos)
    {
        if(mLongColorIndex == 1)
        {
            mLongColorIndex = 0;
            pBtnLongCentor.at(0)->setStyleSheet(*listPanelColor.at(mLongColorIndex));
        }else
        {
            mLongColorIndex = 1;
            pBtnLongCentor.at(0)->setStyleSheet(*listPanelColor.at(mLongColorIndex));
        }
    }
}
void CMainBaseNdt10::ArmVisableCtrl()
{
    if(!isArmTablePos)
    {
        if(mArmColorIndex == 1)
        {
            mArmColorIndex = 0;
            pBtnArmCentor.first()->setStyleSheet(*listPanelColor.at(mArmColorIndex));
        }else
        {
            mArmColorIndex = 1;
            pBtnArmCentor.first()->setStyleSheet(*listPanelColor.at(mArmColorIndex));
        }
    }
}

void CMainBaseNdt10::RoundVisableCtrl()
{
    if(!isRoundTablePos)
    {
        if( arrRenderRound->at(mRoundPanelIndex)->getPenColor() == Qt::darkRed)
        {
            arrRenderRound->at(mRoundPanelIndex)->setPenColor(Qt::red);
            arrRenderRound->at(mRoundPanelIndex)->setFillColor(Qt::red);
            arrRenderRound->at(mRoundPanelIndex)->setBeShow(true);
        }else
        {
            arrRenderRound->at(mRoundPanelIndex)->setPenColor(Qt::darkRed);
            arrRenderRound->at(mRoundPanelIndex)->setFillColor(Qt::darkRed);
            arrRenderRound->at(mRoundPanelIndex)->setBeShow(true);
        }

        update();
    }
}

void CMainBaseNdt10::SmallVisableCtrl()
{
    if(!isSmallTablePos)
    {
        arrRenderSmall->at(2)->setBeShow(true);
        if(arrRenderSmall->at(2)->getFillColor() == Qt::darkRed )
            arrRenderSmall->at(2)->setFillColor(Qt::red);
        else
            arrRenderSmall->at(2)->setFillColor(Qt::darkRed);

        update();
    }
}
void CMainBaseNdt10::BuildLongVisiable()
{


    listPanelColor.append(new QString("background-color:red;"));

    listPanelColor.append(new QString("background-color:darkRed;"));

    listPanelColor.append(new QString("background-color:yellow;"));

    listPanelColor.append(new QString("background-color:green;"));

    listPanelColor.append(new QString("background-color:lightGray;"));

    pLongBackBorder = new QFrame(this);
    pLongBackBorder->setAutoFillBackground(false);
    pLongBackBorder->setGeometry(SYS_WID(468),SYS_HEI(98),SYS_WID(164),SYS_HEI(404));
    pLongBackBorder->setStyleSheet("background-color : lightGray ; border : 2px solid black;");
    pLongBackBorder->setVisible(false);

    CButtonStable * pBtnTemp;

    //中间
    for(int mIdx = 420 ; mIdx >= 100 ; mIdx -= 80)
    {
        pBtnTemp = new CButtonStable(this);
        pBtnTemp->setGeometry(SYS_WID(510),SYS_HEI(mIdx),SYS_WID(80),SYS_HEI(80));
        pBtnTemp->setVisible(false);
        pBtnLongCentor.append(pBtnTemp);
    }

}
void CMainBaseNdt10::BuildArmVisiable()
{

    pArmBackBorder = new QFrame(this);
    pArmBackBorder->setAutoFillBackground(false);
    pArmBackBorder->setGeometry(SYS_WID(468),SYS_HEI(98),SYS_WID(164),SYS_HEI(404));
    pArmBackBorder->setStyleSheet("background-color : lightGray ; border : 2px solid black;");
    pArmBackBorder->setVisible(false);

    CButtonStable * pBtnTemp;

    //中间
    for(int mIdx = 380 ; mIdx >= 140 ; mIdx -= 80)
    {
        pBtnTemp = new CButtonStable(this);
        pBtnTemp->setGeometry(SYS_WID(510),SYS_HEI(mIdx),SYS_WID(80),SYS_HEI(80));
        pBtnTemp->setVisible(false);
        pBtnArmCentor.append(pBtnTemp);
    }

}
void CMainBaseNdt10::BuildRoundVisiable(QList<CButtonRender*> & arrList ,int startAngle)
{

    arrList.clear();

    CButtonRender * renderTemp;

    QPainterPath  mPathBig;
    mPathBig.addEllipse(ROUND_TABLE_CENTER_X - ROUND_TABLE_CENTER_RL / 2,ROUND_TABLE_CENTER_Y - ROUND_TABLE_CENTER_RL / 2,ROUND_TABLE_CENTER_RL,ROUND_TABLE_CENTER_RL);
    renderTemp =  new CButtonRender(mPathBig,this);
    renderTemp->setBrush(QBrush(Qt::lightGray,Qt::SolidPattern));
    renderTemp->setPenColor(Qt::black);
    renderTemp->setPenWidth(2);

    arrList.append(renderTemp);

    QPainterPath  mPathSmall;
    mPathSmall.addEllipse(ROUND_TABLE_CENTER_X - ROUND_TABLE_CENTER_RS / 2,ROUND_TABLE_CENTER_Y - ROUND_TABLE_CENTER_RS / 2,ROUND_TABLE_CENTER_RS,ROUND_TABLE_CENTER_RS);
    renderTemp =  new CButtonRender(mPathSmall,this);
    renderTemp->setBrush(QBrush(Qt::black,Qt::Dense6Pattern));
    renderTemp->setPenColor(Qt::black);
    renderTemp->setPenWidth(2);

    arrList.append(renderTemp);

    //创建并显示一个没有旋转过的矩形
    for( int mIdx = 0 ; mIdx < 360 / startAngle; mIdx++)
    {

        qreal mAng = mIdx * startAngle + 90;

        //生成中心点在0，0的矩形
        QPainterPath  mPathRect;
        mPathRect.moveTo(-ROUND_PANEL_RECT_WIDTH/2,ROUND_PANEL_RECT_WIDTH/2);
        mPathRect.lineTo(ROUND_PANEL_RECT_WIDTH/2,ROUND_PANEL_RECT_WIDTH/2);
        mPathRect.lineTo(ROUND_PANEL_RECT_WIDTH/2,-ROUND_PANEL_RECT_WIDTH/2);
        mPathRect.lineTo(-ROUND_PANEL_RECT_WIDTH/2,-ROUND_PANEL_RECT_WIDTH/2);
        mPathRect.closeSubpath();

        //旋转矩形
        QTransform Tmatrax;
        Tmatrax.setMatrix(1,0,0,0,1,0,0,0,1.0);
        Tmatrax.rotate(mAng);

        QPolygonF pRectTransform = mPathRect.toFillPolygon(Tmatrax);
        QPainterPath  mPathRectTrans;
        mPathRectTrans.addPolygon(pRectTransform);
        mPathRectTrans.closeSubpath();

        //计算中心点
        qreal cenX,cenY;
        Tmatrax.map(SYS_HEI(-100),0,&cenX,&cenY);
        cenX += ROUND_TABLE_CENTER_X;
        cenY += ROUND_TABLE_CENTER_Y;

        //移动矩形到位
        mPathRectTrans.translate(cenX,cenY);

        //添加矩形到数据队列
        renderTemp =  new CButtonRender(mPathRectTrans,this);
        renderTemp->setBeShow(false);
        renderTemp->setPenColor(Qt::black);
        renderTemp->setPenWidth(2);
        arrList.append(renderTemp);
    }

}


void CMainBaseNdt10::BuildSmallVisiable(QList<CButtonRender*> & arrList ,int startAngle)
{

    arrList.clear();

    CButtonRender * renderTemp;

    QPainterPath  mPathBig;
    mPathBig.addEllipse(SMALL_TABLE_CENTER_X - SMALL_TABLE_CENTER_RL / 2,SMALL_TABLE_CENTER_Y - SMALL_TABLE_CENTER_RL / 2,SMALL_TABLE_CENTER_RL,SMALL_TABLE_CENTER_RL);
    renderTemp =  new CButtonRender(mPathBig,this);
    renderTemp->setBrush(QBrush(Qt::lightGray,Qt::SolidPattern));
    renderTemp->setPenColor(Qt::black);
    renderTemp->setPenWidth(2);

    arrList.append(renderTemp);

    QPainterPath  mPathPanel;
    mPathPanel.addRect(SYS_WID(500),SYS_HEI(140),SYS_WID(140),SYS_HEI(15));
    renderTemp =  new CButtonRender(mPathPanel,this);
    renderTemp->setBrush(QBrush(Qt::blue,Qt::Dense5Pattern));
    renderTemp->setPenColor(Qt::yellow);
    renderTemp->setPenWidth(2);

    arrList.append(renderTemp);

    //创建并显示一个没有旋转过的矩形
    for( int mIdx = 0 ; mIdx < 360 / startAngle ; mIdx++)
    {

        qreal mAng = 90 - startAngle/2 - mIdx * startAngle;

        //生成中心点在0，0的矩形
        QPainterPath  mPathRect;
        mPathRect.moveTo(SMALL_TABLE_CENTER_X ,SMALL_TABLE_CENTER_Y );
        mPathRect.arcTo(SMALL_TABLE_CENTER_X - SMALL_TABLE_CENTER_RL / 2,SMALL_TABLE_CENTER_Y - SMALL_TABLE_CENTER_RL / 2,SMALL_TABLE_CENTER_RL,SMALL_TABLE_CENTER_RL,mAng,startAngle);
        mPathRect.closeSubpath();

        //添加矩形到数据队列
        renderTemp =  new CButtonRender(mPathRect,this);
        renderTemp->setBeShow(false);
        renderTemp->setPenColor(Qt::black);
        renderTemp->setPenWidth(2);
        arrList.append(renderTemp);
    }

}

void CMainBaseNdt10::BuildLcdDisplay()
{
    pLcdDisplay[0] = new CLcdNumber(this);
    pLcdDisplay[0]->move(SYS_WID(93),SYS_HEI(246));
    pLcdDisplay[0]->setVisible(false);
    pLcdDisplay[0]->raise();

    pLcdDisplay[1] = new CLcdNumber(this);
    pLcdDisplay[1]->move(SYS_WID(173),SYS_HEI(246));
    pLcdDisplay[1]->raise();

    pLcdDisplay[2] = new CLcdNumber(this);
    pLcdDisplay[2]->move(SYS_WID(253),SYS_HEI(246));
    pLcdDisplay[2]->raise();

    pLcdDisplay[3] = new CLcdNumber(this);
    pLcdDisplay[3]->move(SYS_WID(333),SYS_HEI(246));
    pLcdDisplay[3]->raise();
}
void CMainBaseNdt10::mySceneInit()
{
    /*
    pSceneArray[SYS_POPUP_REQUEST] = new QGraphicsScene(this);
    pSceneArray[SYS_POPUP_REQUEST]->addWidget(RsMgr->g_systemClient);
*/

}
void CMainBaseNdt10::myViewInit()
{

    //弹出信息
    //    viewPopup   = new QGraphicsView(this);
    //    viewPopup->setObjectName(QString::fromUtf8("viewPopup"));
    //    viewPopup->setGeometry(PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_R180]);
    //    viewPopup->setFocusPolicy(Qt::NoFocus);
    //    viewPopup->setFrameShape(QFrame::NoFrame);
    //    viewPopup->setFrameShadow(QFrame::Plain);
    //    viewPopup->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    viewPopup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    viewPopup->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
    //    viewPopup->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //    viewPopup->setStyleSheet("background:transparent");
    //    viewPopup->rotate(m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_RIGHT]);
    //    viewPopup->raise();
    //    viewPopup->hide();

}
void CMainBaseNdt10::myPopupPosInit()
{

    //视角切换角度初始化
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_NORMAL]= 0;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_LEFT]  = -90;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_RIGHT] = 90;
    m_iViewSwitch[VIEW_DIR_NORMAL][VIEW_DIR_R180]  = 0;

    //部分控件位置初始化

    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_R180]     = QRect(SYS_WID(290),SYS_HEI(120),SYS_WID(220),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_NORMAL]   = QRect(SYS_WID(290),SYS_HEI(120),SYS_WID(220),SYS_HEI(360));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_LEFT]     = QRect(SYS_WID(190),SYS_HEI(158),SYS_WID(360),SYS_HEI(220));
    PopInfoPos[SYS_POPUP_REQUEST][VIEW_DIR_RIGHT]    = QRect(SYS_WID(190),SYS_HEI(158),SYS_WID(360),SYS_HEI(220));

}
void CMainBaseNdt10::ParamLoad()
{
    //QSettings * pNdtCfg = new QSettings(QString("/sdcard/home/fa") + "/ndtConfig.ini",QSettings::IniFormat);
    QSettings * pNdtCfg = new QSettings(QCoreApplication::applicationDirPath() + "/ndtConfig.ini",QSettings::IniFormat);

    mLongTableRunStep = pNdtCfg->value("Config/mLongTableRunStep",400).toInt();
    mArmTableRunStep = pNdtCfg->value("Config/mArmTableRunStep",300).toInt();
    mPanelYStepMin = pNdtCfg->value("Config/mPanelYStepMin",360).toInt();
    mPanelYStepMax = pNdtCfg->value("Config/mPanelYStepMax",660).toInt();
    mTubeYStepMin = pNdtCfg->value("Config/mTubeYStepMin",330).toInt();
    mTubeYStepMax = pNdtCfg->value("Config/mTubeYStepMax",630).toInt();
    mPanelZStepMin = pNdtCfg->value("Config/mPanelZStepMin",800).toInt();
    mTubeFollowPatch = pNdtCfg->value("Config/mTubeFollowPatch",0).toInt();


    statLongTableStepCounter = 0;
    mLongTableRunStepNumber = 4;
    mArmTableRunStepNumber = 3;
}
void CMainBaseNdt10::BuidMenuBottonBtn()
{

    btnStandPage = new CButtonStable(this);
    btnStandPage->setGeometry(SYS_WID(0),SYS_HEI(55) ,SYS_WID(62),SYS_HEI(130));
    btnStandPage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/lzkz2.png);}");
    connect(btnStandPage,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnMenuBottom.push_back(btnStandPage);

    btnMenuNc1 = new CButtonStable(this);
    btnMenuNc1->setGeometry(SYS_WID(0),SYS_HEI(55) ,SYS_WID(62),SYS_HEI(130));
    btnMenuNc1->setVisible(false);
    btnMenuNc1->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/kb.png);}");
    connect(btnMenuNc1,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnScanBottom.push_back(btnMenuNc1);

    btnTablePage = new CButtonStable(this);
    btnTablePage->setGeometry(SYS_WID(0),SYS_HEI(235),SYS_WID(62),SYS_HEI(130));
    btnTablePage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ptkz1.png);}");
    connect(btnTablePage,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnMenuBottom.push_back(btnTablePage);

    btnMenuBack = new CButtonStable(this);
    btnMenuBack->setGeometry(SYS_WID(0),SYS_HEI(235),SYS_WID(62),SYS_HEI(130));
    btnMenuBack->setVisible(false);
    btnMenuBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zcd1.png);}");
    connect(btnMenuBack,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnScanBottom.push_back(btnMenuBack);

    btnTubePage = new CButtonStable(this);
    btnTubePage->setGeometry(SYS_WID(0),SYS_HEI(420),SYS_WID(62),SYS_HEI(130));
    btnTubePage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgkz1.png);}");
    connect(btnTubePage,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnMenuBottom.push_back(btnTubePage);

    btnMenuNc2 = new CButtonStable(this);
    btnMenuNc2->setGeometry(SYS_WID(0),SYS_HEI(420),SYS_WID(62),SYS_HEI(130));
    btnMenuNc2->setVisible(false);
    btnMenuNc2->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/kb.png);}");
    connect(btnMenuNc2,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnScanBottom.push_back(btnMenuNc2);

}
void CMainBaseNdt10::HideAllButton()
{
    //扫描模式下的底部按钮
    for(int mIdx = 0 ; mIdx < arrBtnScanBottom.size() ; mIdx++)
        arrBtnScanBottom.at(mIdx)->setVisible(false);

    //扫描模式按钮
    for(int mIdx = 1 ; mIdx < arrBtnMenuScan.size() ; mIdx++)
        arrBtnMenuScan.at(mIdx)->setVisible(false);

    //显示默认底部菜单
    for(int mIdx = 0 ; mIdx < arrBtnMenuBottom.size() ; mIdx++)
        arrBtnMenuBottom.at(mIdx)->setVisible(false);

    //长台扫描按钮
    for(int mIdx = 0 ; mIdx < arrBtnSmartLong.size() ; mIdx++)
        arrBtnSmartLong.at(mIdx)->setVisible(false);

    //大圆台扫描按钮
    for(int mIdx = 0 ; mIdx < arrBtnSmartRound.size() ; mIdx++)
        arrBtnSmartRound.at(mIdx)->setVisible(false);

    //小圆台扫描按钮
    for(int mIdx = 0 ; mIdx < arrBtnSmartSmall.size() ; mIdx++)
        arrBtnSmartSmall.at(mIdx)->setVisible(false);

    //横臂扫描按钮
    for(int mIdx = 0 ; mIdx < arrBtnSmartArm.size() ; mIdx++)
        arrBtnSmartArm.at(mIdx)->setVisible(false);

    //立柱控制页面按钮
    for(int mIdx = 0 ; mIdx < arrBtnStand.size() ; mIdx++)
        arrBtnStand.at(mIdx)->setVisible(false);

    //平台控制页面按钮
    for(int mIdx = 0 ; mIdx < arrBtnTable.size() ; mIdx++)
        arrBtnTable.at(mIdx)->setVisible(false);

    //球管控制页面按钮
    for(int mIdx = 0 ; mIdx < arrBtnTube.size() ; mIdx++)
        arrBtnTube.at(mIdx)->setVisible(false);

    for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
        pBtnLongCentor.at(mIdx)->setVisible(false);

    for(int mIdx = 0 ; mIdx < pBtnArmCentor.size() ; mIdx++)
        pBtnArmCentor.at(mIdx)->setVisible(false);

    SetInfoText("");

    pLongBackBorder->setVisible(false);

}
//根据序号显示页面
void CMainBaseNdt10::ShowPage(int nPage)
{

    HideAllButton();

    if(nPage == NDT_PAGE_STAND)
    {

        btnStandPage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/lzkz2.png);}");
        btnTablePage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ptkz1.png);}");
        btnTubePage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgkz1.png);}");
        pLcdDisplay[0]->setVisible(false);
        setPageIdx(NDT_PAGE_STAND);

        for(int mIdx = 1 ; mIdx < arrBtnMenuScan.size() ; mIdx++)
            arrBtnMenuScan.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnMenuBottom.size() ; mIdx++)
            arrBtnMenuBottom.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnStand.size() ; mIdx++)
            arrBtnStand.at(mIdx)->setVisible(true);

        return;
    }

    if(nPage == NDT_PAGE_TABLE)
    {

        btnStandPage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/lzkz1.png);}");
        btnTablePage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ptkz2.png);}");
        btnTubePage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgkz1.png);}");
        pLcdDisplay[0]->setVisible(true);
        setPageIdx(NDT_PAGE_TABLE);

        for(int mIdx = 1 ; mIdx < arrBtnMenuScan.size() ; mIdx++)
            arrBtnMenuScan.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnMenuBottom.size() ; mIdx++)
            arrBtnMenuBottom.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnTable.size() ; mIdx++)
            arrBtnTable.at(mIdx)->setVisible(true);

        return;
    }

    if(nPage == NDT_PAGE_TUBE)
    {

        btnStandPage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/lzkz1.png);}");
        btnTablePage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ptkz1.png);}");
        btnTubePage->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgkz2.png);}");
        pLcdDisplay[0]->setVisible(true);
        setPageIdx(NDT_PAGE_TUBE);

        for(int mIdx = 1 ; mIdx < arrBtnMenuScan.size() ; mIdx++)
            arrBtnMenuScan.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnMenuBottom.size() ; mIdx++)
            arrBtnMenuBottom.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnTube.size() ; mIdx++)
            arrBtnTube.at(mIdx)->setVisible(true);

        return;
    }

    if(nPage == NDT_PAGE_SCAN_LONG)
    {

        pLongBackBorder->setVisible(true);

        for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
            pBtnLongCentor.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnScanBottom.size() ; mIdx++)
            arrBtnScanBottom.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnSmartLong.size() ; mIdx++)
            arrBtnSmartLong.at(mIdx)->setVisible(true);

        setPageIdx(NDT_PAGE_SCAN_LONG);
    }

    if(nPage == NDT_PAGE_SCAN_ARM)
    {

        pLongBackBorder->setVisible(true);

        for(int mIdx = 0 ; mIdx < pBtnArmCentor.size() ; mIdx++)
            pBtnArmCentor.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnScanBottom.size() ; mIdx++)
            arrBtnScanBottom.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnSmartArm.size() ; mIdx++)
            arrBtnSmartArm.at(mIdx)->setVisible(true);

        setPageIdx(NDT_PAGE_SCAN_ARM);
    }


    if(nPage == NDT_PAGE_SCAN_ROUND)
    {

        for(int mIdx = 0 ; mIdx < arrBtnScanBottom.size() ; mIdx++)
            arrBtnScanBottom.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnSmartRound.size() ; mIdx++)
            arrBtnSmartRound.at(mIdx)->setVisible(true);

        setPageIdx(NDT_PAGE_SCAN_ROUND);
    }

    if(nPage == NDT_PAGE_SCAN_SMALL)
    {
        for(int mIdx = 0 ; mIdx < arrBtnScanBottom.size() ; mIdx++)
            arrBtnScanBottom.at(mIdx)->setVisible(true);

        for(int mIdx = 0 ; mIdx < arrBtnSmartSmall.size() ; mIdx++)
            arrBtnSmartSmall.at(mIdx)->setVisible(true);

        setPageIdx(NDT_PAGE_SCAN_SMALL);
    }

}
void CMainBaseNdt10::OnMenuCtrlPressed()
{

    if(sender() == btnStandPage)
    {
        ShowPage(NDT_PAGE_STAND);
    }

    if(sender() == btnTablePage)
    {
        ShowPage(NDT_PAGE_TABLE);
    }

    if(sender() == btnTubePage)
    {
        ShowPage(NDT_PAGE_TUBE);
    }

    if(sender() == btnMenuBack)
    {
        ShowPage(getPageIdxBuf());

        //停止自动控制定时器，停止所有电机
        tmAutoPosition->stop();
        SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
    }

    if(sender() == btnLongScan)
    {
        ShowPage(NDT_PAGE_SCAN_LONG);
    }

    if(sender() == btnArmScan)
    {
        ShowPage(NDT_PAGE_SCAN_ARM);
    }

    if(sender()  == btnRoundScan)
    {
        ShowPage(NDT_PAGE_SCAN_ROUND);

    }

    if(sender()  ==  btnSmallScan)
    {
        ShowPage(NDT_PAGE_SCAN_SMALL);
    }

    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_PAGE;
            keyBuf[1] = getPageIdx();
            g_netBase->PublishMessage();
        }
    }

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_SERVER)
    {
        if(g_netBase)
        {
            unsigned short * pBuf = g_netBase->getUdpBufferWrite();
            pBuf[0] = NET_CMD_KEY_PAGE;
            pBuf[1] = getPageIdx();

            g_netBase->BroadcastMsg();
        }
    }
}

void CMainBaseNdt10::OnPageChange(int mPage )
{
    ShowPage(mPage);
}
void CMainBaseNdt10::BuildMenuScanBtn()
{

    CButtonStable * pBtnTemp;

    pBtnTemp = new CButtonStable(this);
    pBtnTemp->setGeometry(SYS_WID(725),SYS_HEI(0),SYS_WID(75),SYS_HEI(600));
    pBtnTemp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/titleground.png);}");
    connect(pBtnTemp,SIGNAL(pressed()),this,SLOT(OnBtnTitlePressed()));
    arrBtnMenuScan.push_back(pBtnTemp);

    btnLongScan = new CButtonStable(this);
    btnLongScan->setGeometry(SYS_WID(604),SYS_HEI(103),SYS_WID(98),SYS_HEI(194));
    btnLongScan->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/stsm1.png);}");
    btnLongScan->raise();
    connect(btnLongScan,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnMenuScan.push_back(btnLongScan);

    btnArmScan = new CButtonStable(this);
    btnArmScan->setGeometry(SYS_WID(480),SYS_HEI(103),SYS_WID(98),SYS_HEI(194));
    btnArmScan->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/hbsm1.png);}");
    connect(btnArmScan,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnMenuScan.push_back(btnArmScan);

    btnRoundScan = new CButtonStable(this);
    btnRoundScan->setGeometry(SYS_WID(604),SYS_HEI(320),SYS_WID(98),SYS_HEI(194));
    btnRoundScan->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytsm1.png);}");
    connect(btnRoundScan,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnMenuScan.push_back(btnRoundScan);

    btnSmallScan = new CButtonStable(this);
    btnSmallScan->setGeometry(SYS_WID(480),SYS_HEI(320),SYS_WID(98),SYS_HEI(194));
    btnSmallScan->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytsm1.png);}");
    connect(btnSmallScan,SIGNAL(pressed()),this,SLOT(OnMenuCtrlPressed()));
    arrBtnMenuScan.push_back(btnSmallScan);
}

void CMainBaseNdt10::OnTubeCtrlPressed()
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnFidUp)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnFidDown)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSidLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSidRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnCepFront)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnCepBack)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnAngAdd)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnAngDec)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }
}

void CMainBaseNdt10::OnTubeCtrlReleased()
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnFidUp)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnFidDown)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnSidLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnSidRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnCepFront)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnCepBack)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnAngAdd)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnAngDec)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }
}

void CMainBaseNdt10::OnTubeFilmPressed(QKeyEvent * mKey)
{

    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_PRESS;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_TUBE;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_TUBE + 0:
        ShowPage(NDT_PAGE_STAND);
        break;
    case NDT_KEY_BASE_TUBE + 1:
        ShowPage(NDT_PAGE_TABLE);
        break;
    case NDT_KEY_BASE_TUBE + 2:
        ShowPage(NDT_PAGE_TUBE);
        break;
    case NDT_KEY_BASE_TUBE + 3:             //NULL
        btnAngAdd->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgzz2.png);}");
        SendKeySingle(NDT_KEY_IDX_ANG,g_motorMgr->getLimitMax(NDT_KEY_IDX_ANG));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_TUBE + 4:             //NULL
        btnAngDec->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgfz2.png);}");
        SendKeySingle(NDT_KEY_IDX_ANG,g_motorMgr->getLimitMin(NDT_KEY_IDX_ANG));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_TUBE + 5:
        btnCepFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxq2.png);}");
        SendKeySingle(NDT_KEY_IDX_CEP,g_motorMgr->getLimitMin(NDT_KEY_IDX_CEP));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_TUBE + 6:
        btnCepBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxh2.png);}");
        SendKeySingle(NDT_KEY_IDX_CEP,g_motorMgr->getLimitMax(NDT_KEY_IDX_CEP));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_TUBE + 7:
        btnSidLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxz2.png);}");
        SendKeySingle(NDT_KEY_IDX_SID,g_motorMgr->getLimitMin(NDT_KEY_IDX_SID));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_TUBE + 8:
        btnSidRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxy2.png);}");
        SendKeySingle(NDT_KEY_IDX_SID,g_motorMgr->getLimitMax(NDT_KEY_IDX_SID));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_TUBE + 9:
        btnFidUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sgxs2.png);}");
        SendKeySingle(NDT_KEY_IDX_FID,g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));

        break;
    case NDT_KEY_BASE_TUBE + 10:
        btnFidDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxx2.png);}");
        SendKeySingle(NDT_KEY_IDX_FID,g_motorMgr->getLimitMin(NDT_KEY_IDX_FID));

        break;
    default:
        break;
    }
}

void CMainBaseNdt10::OnTubeFilmReleased(QKeyEvent * mKey)
{
    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_RELEASE;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_TUBE;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_TUBE + 0:
        break;
    case NDT_KEY_BASE_TUBE + 1:
        break;
    case NDT_KEY_BASE_TUBE + 2:
        break;
    case NDT_KEY_BASE_TUBE + 3:             //NULL
        btnAngAdd->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgzz1.png);}");
        SendKeySingle(NDT_KEY_IDX_ANG,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TUBE + 4:             //NULL
        btnAngDec->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgfz1.png);}");
        SendKeySingle(NDT_KEY_IDX_ANG,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TUBE + 5:
        btnCepFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxq1.png);}");
        SendKeySingle(NDT_KEY_IDX_CEP,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TUBE + 6:
        btnCepBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxh1.png);}");
        SendKeySingle(NDT_KEY_IDX_CEP,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TUBE + 7:
        btnSidLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxz1.png);}");
        SendKeySingle(NDT_KEY_IDX_SID,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TUBE + 8:
        btnSidRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxy1.png);}");
        SendKeySingle(NDT_KEY_IDX_SID,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TUBE + 9:
        btnFidUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sgxs1.png);}");
        SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TUBE + 10:
        btnFidDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxx1.png);}");
        SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
        break;
    default:
        break;
    }
}

//球管页面动作按钮
void CMainBaseNdt10::BuidTubeCtrlBtn()
{

    btnAngAdd = new CButtonStable(this);
    btnAngAdd->setObjectName("qgzz");
    btnAngAdd->setGeometry(SYS_WID(80),SYS_HEI(80) ,SYS_WID(80),SYS_HEI(160));
    btnAngAdd->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgzz1.png);}");
    btnAngAdd->setVisible(false);
    connect(btnAngAdd,SIGNAL(pressed()),this,SLOT(OnTubeCtrlPressed()));
    connect(btnAngAdd,SIGNAL(released()),this,SLOT(OnTubeCtrlReleased()));
    arrBtnTube.push_back(btnAngAdd);

    btnAngDec = new CButtonStable(this);
    btnAngDec->setObjectName("qgfz");
    btnAngDec->setGeometry(SYS_WID(80),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnAngDec->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgfz1.png);}");
    btnAngDec->setVisible(false);
    connect(btnAngDec,SIGNAL(pressed()),this,SLOT(OnTubeCtrlPressed()));
    connect(btnAngDec,SIGNAL(released()),this,SLOT(OnTubeCtrlReleased()));
    arrBtnTube.push_back(btnAngDec);

    btnCepFront = new CButtonStable(this);
    btnCepFront->setObjectName("qgxq");
    btnCepFront->setGeometry(SYS_WID(160),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnCepFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxq1.png);}");
    btnCepFront->setVisible(false);
    connect(btnCepFront,SIGNAL(pressed()),this,SLOT(OnTubeCtrlPressed()));
    connect(btnCepFront,SIGNAL(released()),this,SLOT(OnTubeCtrlReleased()));
    arrBtnTube.push_back(btnCepFront);

    btnCepBack = new CButtonStable(this);
    btnCepBack->setObjectName("qgxh");
    btnCepBack->setGeometry(SYS_WID(160),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnCepBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxh1.png);}");
    btnCepBack->setVisible(false);
    connect(btnCepBack,SIGNAL(pressed()),this,SLOT(OnTubeCtrlPressed()));
    connect(btnCepBack,SIGNAL(released()),this,SLOT(OnTubeCtrlReleased()));
    arrBtnTube.push_back(btnCepBack);

    btnSidLeft = new CButtonStable(this);
    btnSidLeft->setObjectName("qgxz");
    btnSidLeft->setGeometry(SYS_WID(240),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnSidLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxz1.png);}");
    btnSidLeft->setVisible(false);
    connect(btnSidLeft,SIGNAL(pressed()),this,SLOT(OnTubeCtrlPressed()));
    connect(btnSidLeft,SIGNAL(released()),this,SLOT(OnTubeCtrlReleased()));
    arrBtnTube.push_back(btnSidLeft);

    btnSidRight = new CButtonStable(this);
    btnSidRight->setObjectName("qgxy");
    btnSidRight->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnSidRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxy1.png);}");
    btnSidRight->setVisible(false);
    connect(btnSidRight,SIGNAL(pressed()),this,SLOT(OnTubeCtrlPressed()));
    connect(btnSidRight,SIGNAL(released()),this,SLOT(OnTubeCtrlReleased()));
    arrBtnTube.push_back(btnSidRight);

    btnFidUp = new CButtonStable(this);
    btnFidUp->setObjectName("sgxs");
    btnFidUp->setGeometry(SYS_WID(320),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnFidUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sgxs1.png);}");
    btnFidUp->setVisible(false);
    connect(btnFidUp,SIGNAL(pressed()),this,SLOT(OnTubeCtrlPressed()));
    connect(btnFidUp,SIGNAL(released()),this,SLOT(OnTubeCtrlReleased()));
    arrBtnTube.push_back(btnFidUp);

    btnFidDown = new CButtonStable(this);
    btnFidDown->setObjectName("qgxx");
    btnFidDown->setGeometry(SYS_WID(320),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnFidDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/qgxx1.png);}");
    btnFidDown->setVisible(false);
    connect(btnFidDown,SIGNAL(pressed()),this,SLOT(OnTubeCtrlPressed()));
    connect(btnFidDown,SIGNAL(released()),this,SLOT(OnTubeCtrlReleased()));
    arrBtnTube.push_back(btnFidDown);

}

//平台页面动作按钮
void CMainBaseNdt10::BuidTableCtrlBtn()
{

    btnSrlZz = new CButtonStable(this);
    btnSrlZz->setGeometry(SYS_WID(80),SYS_HEI(80) ,SYS_WID(80),SYS_HEI(160));
    btnSrlZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz1.png);}");
    btnSrlZz->setVisible(false);
    connect(btnSrlZz,SIGNAL(pressed()),this,SLOT(OnTableCtrlPressed()));
    connect(btnSrlZz,SIGNAL(released()),this,SLOT(OnTableCtrlReleased()));
    arrBtnTable.push_back(btnSrlZz);

    btnSrlFz = new CButtonStable(this);
    btnSrlFz->setGeometry(SYS_WID(80),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnSrlFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz1.png);}");
    btnSrlFz->setVisible(false);
    connect(btnSrlFz,SIGNAL(pressed()),this,SLOT(OnTableCtrlPressed()));
    connect(btnSrlFz,SIGNAL(released()),this,SLOT(OnTableCtrlReleased()));
    arrBtnTable.push_back(btnSrlFz);

    btnRolZz = new CButtonStable(this);
    btnRolZz->setGeometry(SYS_WID(160),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnRolZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz1.png);}");
    btnRolZz->setVisible(false);
    connect(btnRolZz,SIGNAL(pressed()),this,SLOT(OnTableCtrlPressed()));
    connect(btnRolZz,SIGNAL(released()),this,SLOT(OnTableCtrlReleased()));
    arrBtnTable.push_back(btnRolZz);

    btnRolFz = new CButtonStable(this);
    btnRolFz->setGeometry(SYS_WID(160),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnRolFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz1.png);}");
    btnRolFz->setVisible(false);
    connect(btnRolFz,SIGNAL(pressed()),this,SLOT(OnTableCtrlPressed()));
    connect(btnRolFz,SIGNAL(released()),this,SLOT(OnTableCtrlReleased()));
    arrBtnTable.push_back(btnRolFz);

    btnRmvLeft = new CButtonStable(this);
    btnRmvLeft->setGeometry(SYS_WID(240),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnRmvLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz1.png);}");
    btnRmvLeft->setVisible(false);
    connect(btnRmvLeft,SIGNAL(pressed()),this,SLOT(OnTableCtrlPressed()));
    connect(btnRmvLeft,SIGNAL(released()),this,SLOT(OnTableCtrlReleased()));
    arrBtnTable.push_back(btnRmvLeft);

    btnRmvRight = new CButtonStable(this);
    btnRmvRight->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnRmvRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy1.png);}");
    btnRmvRight->setVisible(false);
    connect(btnRmvRight,SIGNAL(pressed()),this,SLOT(OnTableCtrlPressed()));
    connect(btnRmvRight,SIGNAL(released()),this,SLOT(OnTableCtrlReleased()));
    arrBtnTable.push_back(btnRmvRight);

    btnLmvLeft = new CButtonStable(this);
    btnLmvLeft->setGeometry(SYS_WID(320),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnLmvLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz1.png);}");
    btnLmvLeft->setVisible(false);
    connect(btnLmvLeft,SIGNAL(pressed()),this,SLOT(OnTableCtrlPressed()));
    connect(btnLmvLeft,SIGNAL(released()),this,SLOT(OnTableCtrlReleased()));
    arrBtnTable.push_back(btnLmvLeft);

    btnLmvRight = new CButtonStable(this);
    btnLmvRight->setGeometry(SYS_WID(320),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnLmvRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy1.png);}");
    btnLmvRight->setVisible(false);
    connect(btnLmvRight,SIGNAL(pressed()),this,SLOT(OnTableCtrlPressed()));
    connect(btnLmvRight,SIGNAL(released()),this,SLOT(OnTableCtrlReleased()));
    arrBtnTable.push_back(btnLmvRight);

}


void CMainBaseNdt10::OnTableCtrlPressed()
{

    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnSrlZz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSrlFz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnRolZz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnRolFz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnRmvLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnRmvRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnLmvLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnLmvRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }

}

void CMainBaseNdt10::OnTableCtrlReleased()
{

    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnSrlZz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnSrlFz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnRolZz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnRolFz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnRmvLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnRmvRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLmvLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLmvRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }
}

void CMainBaseNdt10::OnTableFilmPressed(QKeyEvent * mKey)
{
    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_PRESS;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_TABLE;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_TABLE + 0:
        ShowPage(NDT_PAGE_STAND);
        break;
    case NDT_KEY_BASE_TABLE + 1:
        ShowPage(NDT_PAGE_TABLE);
        break;
    case NDT_KEY_BASE_TABLE + 2:
        ShowPage(NDT_PAGE_TUBE);
        break;
    case NDT_KEY_BASE_TABLE + 3:             //NULL
        btnSrlZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz2.png);}");
        SendKeySingle(NDT_KEY_IDX_SRL,g_motorMgr->getLimitMax(NDT_KEY_IDX_SRL)  );
        break;
    case NDT_KEY_BASE_TABLE + 4:             //NULL
        btnSrlFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz2.png);}");
        SendKeySingle(NDT_KEY_IDX_SRL,g_motorMgr->getLimitMin(NDT_KEY_IDX_SRL ));
        break;
    case NDT_KEY_BASE_TABLE + 5:
        btnRolZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz2.png);}");
        SendKeySingle(NDT_KEY_IDX_ROL,g_motorMgr->getLimitMax(NDT_KEY_IDX_ROL));
        break;
    case NDT_KEY_BASE_TABLE + 6:
        btnRolFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz2.png);}");
        //SendKeySingle(NDT_KEY_IDX_ROL,g_motorMgr->getLimitMax(NDT_KEY_IDX_ROL ) * -1);
        SendKeySingle(NDT_KEY_IDX_ROL,g_motorMgr->getLimitMin(NDT_KEY_IDX_ROL ));
        break;
    case NDT_KEY_BASE_TABLE + 7:
        btnRmvLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz2.png);}");
        SendKeySingle(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMin(NDT_KEY_IDX_RMV));
        break;
    case NDT_KEY_BASE_TABLE + 8:
        btnRmvRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy2.png);}");
        SendKeySingle(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));
        break;
    case NDT_KEY_BASE_TABLE + 9:
        btnLmvLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        SendKeySingle(NDT_KEY_IDX_LMV,g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
        break;
    case NDT_KEY_BASE_TABLE + 10:
        btnLmvRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        SendKeySingle(NDT_KEY_IDX_LMV,g_motorMgr->getLimitMax(NDT_KEY_IDX_LMV));
        break;
    default:
        break;
    }
}

void CMainBaseNdt10::OnTableFilmReleased(QKeyEvent *mKey)
{
    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_RELEASE;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_TABLE;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_TABLE + 0:
        break;
    case NDT_KEY_BASE_TABLE + 1:
        break;
    case NDT_KEY_BASE_TABLE + 2:
        break;
    case NDT_KEY_BASE_TABLE + 3:             //NULL
        btnSrlZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz1.png);}");
        SendKeySingle(NDT_KEY_IDX_SRL,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TABLE + 4:             //NULL
        btnSrlFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz1.png);}");
        SendKeySingle(NDT_KEY_IDX_SRL,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TABLE + 5:
        btnRolZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz1.png);}");
        SendKeySingle(NDT_KEY_IDX_ROL,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TABLE + 6:
        btnRolFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz1.png);}");
        SendKeySingle(NDT_KEY_IDX_ROL,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TABLE + 7:
        btnRmvLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz1.png);}");
        SendKeySingle(NDT_KEY_IDX_RMV,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TABLE + 8:
        btnRmvRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy1.png);}");
        SendKeySingle(NDT_KEY_IDX_RMV,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TABLE + 9:
        btnLmvLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz1.png);}");
        SendKeySingle(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
        break;
    case NDT_KEY_BASE_TABLE + 10:
        btnLmvRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy1.png);}");
        SendKeySingle(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
        break;
    default:
        break;
    }
}
//大圆台扫描页面动作支持
void CMainBaseNdt10::BuidSmartSmallCtrlBtn()
{

    btnSmallExpStill = new CButtonStable(this);
    btnSmallExpStill->setGeometry(SYS_WID(80),SYS_HEI(80) ,SYS_WID(80),SYS_HEI(160));
    btnSmallExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg1.png);}");
    btnSmallExpStill->setVisible(false);
    connect(btnSmallExpStill,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallExpStill,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallExpStill);

    btnSmallHeiDown = new CButtonStable(this);
    btnSmallHeiDown->setGeometry(SYS_WID(80),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnSmallHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
    btnSmallHeiDown->setVisible(false);
    btnSmallHeiDown->setEnabled(false);
    connect(btnSmallHeiDown,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallHeiDown,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallHeiDown);

    btnSmallExpMove = new CButtonStable(this);
    btnSmallExpMove->setGeometry(SYS_WID(160),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnSmallExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg2.png);}");
    btnSmallExpMove->setVisible(false);
    connect(btnSmallExpMove,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallExpMove,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallExpMove);

    btnSmallHeiUp = new CButtonStable(this);
    btnSmallHeiUp->setGeometry(SYS_WID(160),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnSmallHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
    btnSmallHeiUp->setVisible(false);
    btnSmallHeiUp->setEnabled(false);
    connect(btnSmallHeiUp,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallHeiUp,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallHeiUp);

    btnSmallManual = new CButtonStable(this);
    btnSmallManual->setGeometry(SYS_WID(240),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnSmallManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");
    btnSmallManual->setVisible(false);
    connect(btnSmallManual,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallManual,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallManual);

    btnSmallTableFz = new CButtonStable(this);
    btnSmallTableFz->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnSmallTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz2.png);}");
    btnSmallTableFz->setVisible(false);
    btnSmallTableFz->setEnabled(false);
    connect(btnSmallTableFz,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallTableFz,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallTableFz);

    btnSmallAuto = new CButtonStable(this);
    btnSmallAuto->setGeometry(SYS_WID(320),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnSmallAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw1.png);}");
    btnSmallAuto->setVisible(false);
    connect(btnSmallAuto,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallAuto,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallAuto);

    btnSmallTableZz = new CButtonStable(this);
    btnSmallTableZz->setGeometry(SYS_WID(320),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnSmallTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz2.png);}");
    btnSmallTableZz->setVisible(false);
    btnSmallTableZz->setEnabled(false);
    connect(btnSmallTableZz,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallTableZz,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallTableZz);

    btnSmallTableR60 = new CButtonStable(this);
    btnSmallTableR60->setGeometry(SYS_WID(655),SYS_HEI(465),SYS_WID(60),SYS_HEI(100));
    btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd602.png);}");
    btnSmallTableR60->setVisible(false);
    btnSmallTableR60->setEnabled(false);
    connect(btnSmallTableR60,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallTableR60,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallTableR60);

    btnSmallTableR45 = new CButtonStable(this);
    btnSmallTableR45->setGeometry(SYS_WID(575),SYS_HEI(465),SYS_WID(60),SYS_HEI(100));
    btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd451.png);}");
    btnSmallTableR45->setVisible(false);
    btnSmallTableR45->setEnabled(true);
    connect(btnSmallTableR45,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallTableR45,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallTableR45);

    btnSmallTableR40 = new CButtonStable(this);
    btnSmallTableR40->setGeometry(SYS_WID(495),SYS_HEI(465),SYS_WID(60),SYS_HEI(100));
    btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd401.png);}");
    btnSmallTableR40->setVisible(false);
    btnSmallTableR40->setEnabled(true);
    connect(btnSmallTableR40,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallTableR40,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallTableR40);

    btnSmallTableR36 = new CButtonStable(this);
    btnSmallTableR36->setGeometry(SYS_WID(415),SYS_HEI(465),SYS_WID(60),SYS_HEI(100));
    btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd361.png);}");
    btnSmallTableR36->setVisible(false);
    btnSmallTableR36->setEnabled(true);
    connect(btnSmallTableR36,SIGNAL(pressed()),this,SLOT(OnSmartSmallCtrlPressed()));
    connect(btnSmallTableR36,SIGNAL(released()),this,SLOT(OnSmartSmallCtrlReleased()));
    arrBtnSmartSmall.push_back(btnSmallTableR36);

}

//大圆台扫描页面动作支持，按下
void CMainBaseNdt10::OnSmartSmallCtrlPressed()
{

    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnSmallExpStill)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSmallHeiDown)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSmallExpMove)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;

    }
    if(sender() == btnSmallHeiUp)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSmallManual)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableFz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnSmallAuto)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableZz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnSmallTableR60)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 20 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableR45)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 21 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableR40)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 22 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableR36)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 23 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }

}

//大圆台扫描页面动作支持，释放
void CMainBaseNdt10::OnSmartSmallCtrlReleased()
{

    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnSmallExpStill)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnSmallHeiDown)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }


    if(sender() == btnSmallExpMove)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnSmallHeiUp)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnSmallManual)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnSmallTableFz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnSmallAuto)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableZz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnSmallTableR60)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 20 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableR45)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 21 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableR40)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 22 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnSmallTableR36)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 23 + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }

}

void CMainBaseNdt10::OnSmartSmallFilmPressed(QKeyEvent * mKey)
{

    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_PRESS;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_SMALL;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_SMALL + 0:
        break;
    case NDT_KEY_BASE_SMALL + 1:
        ShowPage(getPageIdxBuf());
        break;
    case NDT_KEY_BASE_SMALL + 2:
        break;
    case NDT_KEY_BASE_SMALL + 3:             //NULL

        btnSmallExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg1.png);}");
        btnSmallExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg2.png);}");
        bLongExpStill = true;
        break;
    case NDT_KEY_BASE_SMALL + 4:             //NULL
        btnSmallHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");

        SendKeySingle(NDT_KEY_IDX_HEI,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_HEI));
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);
        mTubeFollowStart = g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI];
        mExpDelayCtr = NDT_EXP_DELAY_LONG;
        SetInfoText("Wait for machine movement.");

        break;
    case NDT_KEY_BASE_SMALL + 5:

        btnSmallExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg2.png);}");
        btnSmallExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg1.png);}");
        bLongExpStill = false;

        break;
    case NDT_KEY_BASE_SMALL + 6:
        btnSmallHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");

        SendKeySingle(NDT_KEY_IDX_HEI,g_motorMgr->getLimitMax(NDT_KEY_IDX_HEI));
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);
        mTubeFollowStart = g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI];
        mExpDelayCtr = NDT_EXP_DELAY_LONG;
        SetInfoText("Wait for machine movement.");

        break;
    case NDT_KEY_BASE_SMALL + 7:

        mMoveReadyMask = true;
        AutoPositionIndex = NDT_AUTO_MODE_SMALL;
        bManualPosition = true;
        statSmallTableAuto = NDT_AUTO_STAT11;
        btnSmallManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw2.png);}");
        tmAutoPosition->start();

        break;
    case NDT_KEY_BASE_SMALL + 8:

        if(mSmallPanelIndex <= 2)
            return;

        arrRenderSmall->at(2)->setFillColor(Qt::red);

        btnSmallHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
        btnSmallHeiDown->setEnabled(false);
        btnSmallHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
        btnSmallHeiUp->setEnabled(false);
        btnSmallTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz2.png);}");
        btnSmallTableFz->setEnabled(false);
        btnSmallTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz2.png);}");
        btnSmallTableZz->setEnabled(false);

        for(int mIdx =  3; mIdx < mSmallPanelIndex  ; mIdx++)
            arrRenderSmall->at(mIdx)->setFillColor(arrRenderSmall->at(mIdx+1)->getFillColor());

        arrRenderSmall->at(mSmallPanelIndex)->setBeShow(false);

        mSmallPanelIndex -= mSmallExpDir;

        SendKeySingle(NDT_KEY_IDX_SRL,(mSmallPanelIndex - 2) * mSmallAngleRotate);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

        SetInfoText("Wait for machine movement.");

        mExpDelayCtr = NDT_EXP_DELAY_SMALL;

        break;
    case NDT_KEY_BASE_SMALL + 9:

        SendKeySingle(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);        //禁止曝光

        AutoPositionIndex = NDT_AUTO_MODE_SMALL;
        statSmallTableAuto = NDT_AUTO_STAT00;

        isLongTablePos   = false;
        isRoundTablePos = false;
        isArmTablePos     = false;

        if(bManualPosition)
        {
            mMoveReadyMask = false;
            bManualPosition = false;                        //清除手动到位标记
#ifdef QT_ARCH_ARM
            mMoveReadyMask = false;
#endif
        }

        btnSmallManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");
        btnSmallAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw2.png);}");

        tmAutoPosition->start();
        break;
    case NDT_KEY_BASE_SMALL + 10:

        if(mSmallPanelIndex >= arrRenderSmall->size() -1)
            return;

        arrRenderSmall->at(2)->setFillColor(Qt::red);

        mSmallPanelIndex += mSmallExpDir;

        SendKeySingle(NDT_KEY_IDX_SRL,(mSmallPanelIndex - 2) * mSmallAngleRotate);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

        btnSmallHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
        btnSmallHeiDown->setEnabled(false);
        btnSmallHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
        btnSmallHeiUp->setEnabled(false);
        btnSmallTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz2.png);}");
        btnSmallTableFz->setEnabled(false);
        btnSmallTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz2.png);}");
        btnSmallTableZz->setEnabled(false);

        for(int mIdx = mSmallPanelIndex ; mIdx >2  ; mIdx--)
            arrRenderSmall->at(mIdx)->setFillColor(arrRenderSmall->at(mIdx-1)->getFillColor());

        arrRenderSmall->at(3)->setFillColor(Qt::gray);
        arrRenderSmall->at(mSmallPanelIndex)->setBeShow(true);

        SetInfoText("Wait for machine movement.");

        mExpDelayCtr = NDT_EXP_DELAY_SMALL;

        break;
    case NDT_KEY_BASE_SMALL + 20:
        arrRenderSmall = &arrRenderSmallR60;
        mSmallAngleRotate = 60;

        btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd602.png);}");
        btnSmallTableR60->setEnabled(false);
        btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd451.png);}");
        btnSmallTableR45->setEnabled(true);
        btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd401.png);}");
        btnSmallTableR40->setEnabled(true);
        btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd361.png);}");
        btnSmallTableR36->setEnabled(true);

        break;
    case NDT_KEY_BASE_SMALL + 21:
        arrRenderSmall = &arrRenderSmallR45;
        mSmallAngleRotate = 45;
        btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd601.png);}");
        btnSmallTableR60->setEnabled(true);
        btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd452.png);}");
        btnSmallTableR45->setEnabled(false);
        btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd401.png);}");
        btnSmallTableR40->setEnabled(true);
        btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd361.png);}");
        btnSmallTableR36->setEnabled(true);
        break;
    case NDT_KEY_BASE_SMALL + 22:
        arrRenderSmall = &arrRenderSmallR40;
        mSmallAngleRotate = 40;
        btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd601.png);}");
        btnSmallTableR60->setEnabled(true);
        btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd451.png);}");
        btnSmallTableR45->setEnabled(true);
        btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd402.png);}");
        btnSmallTableR40->setEnabled(false);
        btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd361.png);}");
        btnSmallTableR36->setEnabled(true);
        break;
    case NDT_KEY_BASE_SMALL + 23:
        arrRenderSmall = &arrRenderSmallR36;
        mSmallAngleRotate = 36;
        btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd601.png);}");
        btnSmallTableR60->setEnabled(true);
        btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd451.png);}");
        btnSmallTableR45->setEnabled(true);
        btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd401.png);}");
        btnSmallTableR40->setEnabled(true);
        btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd362.png);}");
        btnSmallTableR36->setEnabled(false);
        break;
    default:
        break;
    }
}
void CMainBaseNdt10::OnSmartSmallFilmReleased(QKeyEvent * mKey)
{
    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_RELEASE;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_SMALL;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_SMALL + 0:
        break;
    case NDT_KEY_BASE_SMALL + 1:
        break;
    case NDT_KEY_BASE_SMALL + 2:
        break;
    case NDT_KEY_BASE_SMALL + 3:             //NULL
        break;
    case NDT_KEY_BASE_SMALL + 4:             //NULL
        btnSmallHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx1.png);}");
        SendKeySingle(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);
        tmArmTubeFollow->start();
        break;
    case NDT_KEY_BASE_SMALL + 5:
        break;
    case NDT_KEY_BASE_SMALL + 6:
        btnSmallHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs1.png);}");
        SendKeySingle(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);
        tmArmTubeFollow->start();
        break;
    case NDT_KEY_BASE_SMALL + 7:
        break;
    case NDT_KEY_BASE_SMALL + 8:
        btnSmallTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz1.png);}");
        break;
    case NDT_KEY_BASE_SMALL + 9:
        btnSmallAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw1.png);}");
        break;
    case NDT_KEY_BASE_SMALL + 10:
        btnSmallTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz1.png);}");
        break;
    case NDT_KEY_BASE_SMALL + 20:
        break;
    case NDT_KEY_BASE_SMALL + 21:
        break;
    case NDT_KEY_BASE_SMALL + 22:
        break;
    case NDT_KEY_BASE_SMALL + 23:
        break;
    default:
        break;
    }
}

//大圆台扫描页面动作支持
void CMainBaseNdt10::BuidSmartRoundCtrlBtn()
{

    btnRoundExpStill = new CButtonStable(this);
    btnRoundExpStill->setGeometry(SYS_WID(80),SYS_HEI(80) ,SYS_WID(80),SYS_HEI(160));
    btnRoundExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg1.png);}");
    btnRoundExpStill->setVisible(false);
    connect(btnRoundExpStill,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundExpStill,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundExpStill);

    btnRoundTableLeft = new CButtonStable(this);
    btnRoundTableLeft->setGeometry(SYS_WID(80),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnRoundTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz2.png);}");
    btnRoundTableLeft->setVisible(false);
    btnRoundTableLeft->setEnabled(false);
    connect(btnRoundTableLeft,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundTableLeft,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundTableLeft);

    btnRoundExpMove = new CButtonStable(this);
    btnRoundExpMove->setGeometry(SYS_WID(160),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnRoundExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg2.png);}");
    btnRoundExpMove->setVisible(false);
    connect(btnRoundExpMove,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundExpMove,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundExpMove);

    btnRoundTableRight = new CButtonStable(this);
    btnRoundTableRight->setGeometry(SYS_WID(160),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnRoundTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy2.png);}");
    btnRoundTableRight->setVisible(false);
    btnRoundTableRight->setEnabled(false);
    connect(btnRoundTableRight,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundTableRight,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundTableRight);

    btnRoundManual = new CButtonStable(this);
    btnRoundManual->setGeometry(SYS_WID(240),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnRoundManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");
    btnRoundManual->setVisible(false);
    connect(btnRoundManual,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundManual,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundManual);

    btnRoundTableFz = new CButtonStable(this);
    btnRoundTableFz->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz2.png);}");
    btnRoundTableFz->setVisible(false);
    btnRoundTableFz->setEnabled(false);
    connect(btnRoundTableFz,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundTableFz,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundTableFz);

    btnRoundAuto = new CButtonStable(this);
    btnRoundAuto->setGeometry(SYS_WID(320),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnRoundAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw1.png);}");
    btnRoundAuto->setVisible(false);
    connect(btnRoundAuto,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundAuto,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundAuto);

    btnRoundTableZz = new CButtonStable(this);
    btnRoundTableZz->setGeometry(SYS_WID(320),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz2.png);}");
    btnRoundTableZz->setVisible(false);
    btnRoundTableZz->setEnabled(false);
    connect(btnRoundTableZz,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundTableZz,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundTableZz);

    btnRoundTableR30 = new CButtonStable(this);
    btnRoundTableR30->setGeometry(SYS_WID(655),SYS_HEI(465),SYS_WID(60),SYS_HEI(100));
    btnRoundTableR30->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd302.png);}");
    btnRoundTableR30->setVisible(false);
    btnRoundTableR30->setEnabled(false);
    btnRoundTableR30->setFocusPolicy(Qt::NoFocus);
    connect(btnRoundTableR30,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundTableR30,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundTableR30);

    btnRoundTableR20 = new CButtonStable(this);
    btnRoundTableR20->setGeometry(SYS_WID(575),SYS_HEI(465),SYS_WID(60),SYS_HEI(100));
    btnRoundTableR20->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd201.png);}");
    btnRoundTableR20->setVisible(false);
    btnRoundTableR20->setEnabled(true);
    btnRoundTableR20->setFocusPolicy(Qt::NoFocus);
    connect(btnRoundTableR20,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundTableR20,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundTableR20);

    btnRoundTableR18 = new CButtonStable(this);
    btnRoundTableR18->setGeometry(SYS_WID(495),SYS_HEI(465),SYS_WID(60),SYS_HEI(100));
    btnRoundTableR18->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd181.png);}");
    btnRoundTableR18->setVisible(false);
    btnRoundTableR18->setEnabled(true);
    btnRoundTableR18->setFocusPolicy(Qt::NoFocus);
    connect(btnRoundTableR18,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundTableR18,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundTableR18);

    btnRoundTableR15 = new CButtonStable(this);
    btnRoundTableR15->setGeometry(SYS_WID(415),SYS_HEI(465),SYS_WID(60),SYS_HEI(100));
    btnRoundTableR15->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd151.png);}");
    btnRoundTableR15->setVisible(false);
    btnRoundTableR15->setEnabled(true);
    btnRoundTableR15->setFocusPolicy(Qt::NoFocus);
    connect(btnRoundTableR15,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundTableR15,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundTableR15);

    btnRoundFlat = new CButtonStable(this);
    btnRoundFlat->setGeometry(SYS_WID(495),SYS_HEI(35),SYS_WID(60),SYS_HEI(100));
    btnRoundFlat->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zdpw2.png);}");
    btnRoundFlat->setVisible(false);
    btnRoundFlat->setEnabled(false);
    btnRoundFlat->setFocusPolicy(Qt::NoFocus);
    connect(btnRoundFlat,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundFlat,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundFlat);

    btnRoundAngle = new CButtonStable(this);
    btnRoundAngle->setGeometry(SYS_WID(415),SYS_HEI(35),SYS_WID(60),SYS_HEI(100));
    btnRoundAngle->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zdxw1.png);}");
    btnRoundAngle->setVisible(false);
    btnRoundAngle->setEnabled(true);
    btnRoundAngle->setFocusPolicy(Qt::NoFocus);
    connect(btnRoundAngle,SIGNAL(pressed()),this,SLOT(OnSmartRoundCtrlPressed()));
    connect(btnRoundAngle,SIGNAL(released()),this,SLOT(OnSmartRoundCtrlReleased()));
    arrBtnSmartRound.push_back(btnRoundAngle);

}


//大圆台扫描页面动作支持，按下
void CMainBaseNdt10::OnSmartRoundCtrlPressed()
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnRoundExpStill)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundExpMove)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundManual)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableFz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundAuto)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableZz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableR30)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 21 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableR20)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 22 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableR18)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 23 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableR15)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 24 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundFlat)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 30 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnRoundAngle)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 31 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }
}

//大圆台扫描页面动作支持，释放
void CMainBaseNdt10::OnSmartRoundCtrlReleased()
{

    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnRoundExpStill)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnRoundExpMove)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnRoundTableRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }


    if(sender() == btnRoundManual)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnRoundTableFz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnRoundAuto)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnRoundTableZz)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }

}

void CMainBaseNdt10::OnSmartRoundFilmPressed(QKeyEvent * mKey)
{

    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_PRESS;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_ROUND;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_ROUND + 0:
        break;
    case NDT_KEY_BASE_ROUND + 1:
        ShowPage(getPageIdxBuf());
        break;
    case NDT_KEY_BASE_ROUND + 2:
        break;
    case NDT_KEY_BASE_ROUND + 3:             //NULL
        btnRoundExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg2.png);}");
        btnRoundExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg1.png);}");
        bLongExpStill = true;
        break;
    case NDT_KEY_BASE_ROUND + 4:             //NULL
        btnRoundTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz2.png);}");
        SendKeySingle(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMin(NDT_KEY_IDX_RMV));
        break;
    case NDT_KEY_BASE_ROUND + 5:

        btnRoundExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg1.png);}");
        btnRoundExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg2.png);}");
        bLongExpStill = false;

        break;
    case NDT_KEY_BASE_ROUND + 6:
        btnRoundTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy2.png);}");
        SendKeySingle(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));
        break;
    case NDT_KEY_BASE_ROUND + 7:

        mMoveReadyMask = true;
        AutoPositionIndex = NDT_AUTO_MODE_ROUND_FLAT;
        bManualPosition = true;
        statRoundTableAuto = NDT_AUTO_STAT11;
        btnRoundManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw2.png);}");
        tmAutoPosition->start();

        break;
    case NDT_KEY_BASE_ROUND + 8:
        btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz2.png);}");

        if(mRoundPanelIndex < 3)
            return;

        btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz2.png);}");
        btnRoundTableZz->setEnabled(false);

        btnRoundTableFz->setEnabled(false);

        arrRenderRound->at(mRoundPanelIndex)->setBeShow(false);

        arrRenderRound->at(2)->setFillColor(Qt::red);

        for(int mIdx = 3 ; mIdx < mRoundPanelIndex ; mIdx++)
            arrRenderRound->at(mIdx)->setFillColor(arrRenderRound->at(mIdx+1)->getFillColor());

        mRoundPanelIndex -= mRoundExpDir;

        SendKeySingle(NDT_KEY_IDX_ROL,(mRoundPanelIndex - 2 )* mRoundTableRotateStep);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

        SetInfoText("Wait for machine movement.");
        mExpDelayCtr = NDT_EXP_DELAY_ROUND;

        break;
    case NDT_KEY_BASE_ROUND + 9:

        SendKeySingle(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);        //禁止曝光

        btnRoundAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw2.png);}");
        btnRoundManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");

        if(AutoPositionIndex != NDT_AUTO_MODE_ROUND_ANG)
            AutoPositionIndex = NDT_AUTO_MODE_ROUND_FLAT;

        statRoundTableAuto = NDT_AUTO_STAT00;
        mRoundPanelIndex = 2;

        tmAutoPosition->start();

        isLongTablePos   = false;
        isSmallTablePos  = false;
        isArmTablePos    = false;

        if(bManualPosition)
        {
            mMoveReadyMask = false;
            isRoundTablePos = false;
#ifdef QT_ARCH_ARM
            mMoveReadyMask = false;
#endif
        }

        break;
    case NDT_KEY_BASE_ROUND + 10:
        btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz2.png);}");

        if(mRoundPanelIndex >= (360/mRoundTableRotateStep + 1))
            return;

        btnRoundTableZz->setEnabled(false);

        btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz2.png);}");
        btnRoundTableFz->setEnabled(false);

        mRoundPanelIndex += mRoundExpDir;

        arrRenderRound->at(2)->setFillColor(Qt::red);

        for(int mIdx = mRoundPanelIndex ; mIdx >2  ; mIdx--)
            arrRenderRound->at(mIdx)->setFillColor(arrRenderRound->at(mIdx-1)->getFillColor());

        arrRenderRound->at(3)->setFillColor(Qt::lightGray);
        arrRenderRound->at(mRoundPanelIndex)->setBeShow(true);

        SendKeySingle(NDT_KEY_IDX_ROL,(mRoundPanelIndex - 2 )* mRoundTableRotateStep);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

        SetInfoText("Wait for machine movement.");
        mExpDelayCtr = NDT_EXP_DELAY_ROUND;

        break;
    case NDT_KEY_BASE_ROUND + 21:

        mRoundTableRotateStep = 30;
        arrRenderRound = &arrRenderRoundR30;

        btnRoundTableR30->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd302.png);}");
        btnRoundTableR30->setEnabled(false);
        btnRoundTableR20->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd201.png);}");
        btnRoundTableR20->setEnabled(true);
        btnRoundTableR18->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd181.png);}");
        btnRoundTableR18->setEnabled(true);
        btnRoundTableR15->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd151.png);}");
        btnRoundTableR15->setEnabled(true);

        break;
    case NDT_KEY_BASE_ROUND + 22:

        mRoundTableRotateStep = 20;
        arrRenderRound = &arrRenderRoundR20;

        btnRoundTableR30->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd301.png);}");
        btnRoundTableR30->setEnabled(true);
        btnRoundTableR20->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd202.png);}");
        btnRoundTableR20->setEnabled(false);
        btnRoundTableR18->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd181.png);}");
        btnRoundTableR18->setEnabled(true);
        btnRoundTableR15->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd151.png);}");
        btnRoundTableR15->setEnabled(true);

        break;
    case NDT_KEY_BASE_ROUND + 23:

        mRoundTableRotateStep = 18;
        arrRenderRound = &arrRenderRoundR18;

        btnRoundTableR30->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd301.png);}");
        btnRoundTableR30->setEnabled(true);
        btnRoundTableR20->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd201.png);}");
        btnRoundTableR20->setEnabled(true);
        btnRoundTableR18->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd182.png);}");
        btnRoundTableR18->setEnabled(false);
        btnRoundTableR15->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd151.png);}");
        btnRoundTableR15->setEnabled(true);
        break;
    case NDT_KEY_BASE_ROUND + 24:

        mRoundTableRotateStep = 15;
        arrRenderRound = &arrRenderRoundR15;

        btnRoundTableR30->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd301.png);}");
        btnRoundTableR30->setEnabled(true);
        btnRoundTableR20->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd201.png);}");
        btnRoundTableR20->setEnabled(true);
        btnRoundTableR18->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd181.png);}");
        btnRoundTableR18->setEnabled(true);
        btnRoundTableR15->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd152.png);}");
        btnRoundTableR15->setEnabled(false);

        break;
    case NDT_KEY_BASE_ROUND + 30:
        if(AutoPositionIndex != NDT_AUTO_MODE_ROUND_FLAT)
        {
            isRoundTablePos = false;
            AutoPositionIndex = NDT_AUTO_MODE_ROUND_FLAT;

            btnRoundFlat->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zdpw2.png);}");
            btnRoundFlat->setEnabled(false);
            btnRoundAngle->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zdxw1.png);}");
            btnRoundAngle->setEnabled(true);
        }
        break;
    case NDT_KEY_BASE_ROUND + 31:
        if(AutoPositionIndex != NDT_AUTO_MODE_ROUND_ANG)
        {
            isRoundTablePos = false;
            AutoPositionIndex = NDT_AUTO_MODE_ROUND_ANG;

            btnRoundFlat->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zdpw1.png);}");
            btnRoundFlat->setEnabled(true);
            btnRoundAngle->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zdxw2.png);}");
            btnRoundAngle->setEnabled(false);
        }
        break;
    default:
        break;
    }
}
void CMainBaseNdt10::OnSmartRoundFilmReleased(QKeyEvent * mKey)
{
    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_RELEASE;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_ROUND;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_ROUND + 0:
        break;
    case NDT_KEY_BASE_ROUND + 1:
        break;
    case NDT_KEY_BASE_ROUND + 2:
        break;
    case NDT_KEY_BASE_ROUND + 3:             //NULL
        break;
    case NDT_KEY_BASE_ROUND + 4:             //NULL
        btnRoundTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz1.png);}");
        break;
    case NDT_KEY_BASE_ROUND + 5:
        break;
    case NDT_KEY_BASE_ROUND + 6:
        btnRoundTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy1.png);}");
        break;
    case NDT_KEY_BASE_ROUND + 7:
        break;
    case NDT_KEY_BASE_ROUND + 8:
        btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz1.png);}");
        break;
    case NDT_KEY_BASE_ROUND + 9:
        btnRoundAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw1.png);}");
        break;
    case NDT_KEY_BASE_ROUND + 10:
        btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz1.png);}");
        break;
    default:
        break;
    }
}
//长台扫描页面动作支持
void CMainBaseNdt10::BuidSmartLongCtrlBtn()
{

    btnLongExpStill = new CButtonStable(this);
    btnLongExpStill->setGeometry(SYS_WID(80),SYS_HEI(80) ,SYS_WID(80),SYS_HEI(160));
    btnLongExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg1.png);}");
    btnLongExpStill->setVisible(false);
    connect(btnLongExpStill,SIGNAL(pressed()),this,SLOT(OnSmartLongCtrlPressed()));
    connect(btnLongExpStill,SIGNAL(released()),this,SLOT(OnSmartLongCtrlReleased()));
    arrBtnSmartLong.push_back(btnLongExpStill);

    btnLongPanelBack = new CButtonStable(this);
    btnLongPanelBack->setGeometry(SYS_WID(80),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
    btnLongPanelBack->setVisible(false);
    connect(btnLongPanelBack,SIGNAL(pressed()),this,SLOT(OnSmartLongCtrlPressed()));
    connect(btnLongPanelBack,SIGNAL(released()),this,SLOT(OnSmartLongCtrlReleased()));
    arrBtnSmartLong.push_back(btnLongPanelBack);

    btnLongExpMove = new CButtonStable(this);
    btnLongExpMove->setGeometry(SYS_WID(160),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnLongExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg2.png);}");
    btnLongExpMove->setVisible(false);
    connect(btnLongExpMove,SIGNAL(pressed()),this,SLOT(OnSmartLongCtrlPressed()));
    connect(btnLongExpMove,SIGNAL(released()),this,SLOT(OnSmartLongCtrlReleased()));
    arrBtnSmartLong.push_back(btnLongExpMove);

    btnLongPanelFront = new CButtonStable(this);
    btnLongPanelFront->setGeometry(SYS_WID(160),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
    btnLongPanelFront->setVisible(false);
    connect(btnLongPanelFront,SIGNAL(pressed()),this,SLOT(OnSmartLongCtrlPressed()));
    connect(btnLongPanelFront,SIGNAL(released()),this,SLOT(OnSmartLongCtrlReleased()));
    arrBtnSmartLong.push_back(btnLongPanelFront);

    btnLongManual = new CButtonStable(this);
    btnLongManual->setGeometry(SYS_WID(240),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnLongManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");
    btnLongManual->setVisible(false);
    connect(btnLongManual,SIGNAL(pressed()),this,SLOT(OnSmartLongCtrlPressed()));
    connect(btnLongManual,SIGNAL(released()),this,SLOT(OnSmartLongCtrlReleased()));
    arrBtnSmartLong.push_back(btnLongManual);

    btnLongTableLeft = new CButtonStable(this);
    btnLongTableLeft->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
    btnLongTableLeft->setVisible(false);
    connect(btnLongTableLeft,SIGNAL(pressed()),this,SLOT(OnSmartLongCtrlPressed()));
    connect(btnLongTableLeft,SIGNAL(released()),this,SLOT(OnSmartLongCtrlReleased()));
    arrBtnSmartLong.push_back(btnLongTableLeft);

    btnLongAuto = new CButtonStable(this);
    btnLongAuto->setGeometry(SYS_WID(320),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnLongAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw1.png);}");
    btnLongAuto->setVisible(false);
    connect(btnLongAuto,SIGNAL(pressed()),this,SLOT(OnSmartLongCtrlPressed()));
    connect(btnLongAuto,SIGNAL(released()),this,SLOT(OnSmartLongCtrlReleased()));
    arrBtnSmartLong.push_back(btnLongAuto);

    btnLongTableRight = new CButtonStable(this);
    btnLongTableRight->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnLongTableRight->setGeometry(SYS_WID(320),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
    btnLongTableRight->setVisible(false);
    connect(btnLongTableRight,SIGNAL(pressed()),this,SLOT(OnSmartLongCtrlPressed()));
    connect(btnLongTableRight,SIGNAL(released()),this,SLOT(OnSmartLongCtrlReleased()));
    arrBtnSmartLong.push_back(btnLongTableRight);

}

//长台扫描页面动作支持，按下
void CMainBaseNdt10::OnSmartLongCtrlPressed()
{

    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnLongExpStill)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }
    if(sender() == btnLongPanelFront)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnLongExpMove)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnLongPanelBack)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnLongManual)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnLongTableLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnLongAuto)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnLongTableRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }

}

//长台扫描页面动作支持，释放
void CMainBaseNdt10::OnSmartLongCtrlReleased()
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnLongExpStill)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLongPanelFront)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLongExpMove)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLongPanelBack)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLongManual)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLongTableLeft)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLongAuto)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnLongTableRight)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

}


void CMainBaseNdt10::OnSmartLongFilmPressed(QKeyEvent * mKey)
{
    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_PRESS;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_LONG;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_LONG + 0:
        break;
    case NDT_KEY_BASE_LONG + 1:
        ShowPage(getPageIdxBuf());
        break;
    case NDT_KEY_BASE_LONG + 2:
        break;
    case NDT_KEY_BASE_LONG + 3:

        btnLongExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg2.png);}");
        btnLongExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg1.png);}");
        bLongExpStill = true;

        break;
    case NDT_KEY_BASE_LONG + 4:

        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        SendKeySingle(NDT_KEY_IDX_UID,mPanelYStepMin);
        SendKeyMulti(NDT_KEY_IDX_CEP,mTubeYStepMin);
        mPanelBorderType =  NDT_PANEL_BORDER_BACK;          //记录是扫面长台的前段

        for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
        {
            QRect mRect = pBtnLongCentor.at(mIdx)->geometry();
            mRect.moveLeft(SYS_WID(470));
            pBtnLongCentor.at(mIdx)->setGeometry(mRect);
        }

        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);
        mExpDelayCtr = NDT_EXP_DELAY_LONG;
        SetInfoText("Wait for machine movement.");

        break;
    case NDT_KEY_BASE_LONG + 5:

        btnLongExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg1.png);}");
        btnLongExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg2.png);}");
        bLongExpStill = false;

        break;
    case NDT_KEY_BASE_LONG + 6:

        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        SendKeySingle(NDT_KEY_IDX_UID,mPanelYStepMax);
        SendKeyMulti(NDT_KEY_IDX_CEP,mTubeYStepMax);
        mPanelBorderType = NDT_PANEL_BORDER_FRONT;               //记录是扫面长台的后段

        for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
        {
            QRect mRect = pBtnLongCentor.at(mIdx)->geometry();
            mRect.moveLeft(SYS_WID(550));
            pBtnLongCentor.at(mIdx)->setGeometry(mRect);
        }

        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);
        mExpDelayCtr = NDT_EXP_DELAY_LONG;
        SetInfoText("Wait for machine movement.");
        break;
    case NDT_KEY_BASE_LONG + 7:
        if(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA] < 2 && g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI] < 560 &&
                g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] > 1200)
        {
            mMoveReadyMask = true;
            AutoPositionIndex = NDT_AUTO_MODE_TABLE;
            bManualPosition = true;
            statLongTableAuto = NDT_AUTO_STAT11;
            btnLongManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw2.png);}");
            tmAutoPosition->start();
        }

        break;
    case NDT_KEY_BASE_LONG + 8:         //长台向左

        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(4));       //绿色

        if(statLongTableStepCounter > 0)
            statLongTableStepCounter -= 1;
        pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(1));       //红色

        SendKeySingle(NDT_KEY_IDX_LMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_LMV) + statLongTableStepCounter * mLongTableRunStep);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

        //运动时关闭手动调整按钮
        btnLongPanelBack->setEnabled(false);
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setEnabled(false);
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setEnabled(false);
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setEnabled(false);
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");

        mExpDelayCtr = NDT_EXP_DELAY_LONG;

        SetInfoText("Wait for machine movement.");

        break;
    case NDT_KEY_BASE_LONG + 9:

        isRoundTablePos   = false;
        isSmallTablePos     = false;
        isArmTablePos       = false;

        if(bManualPosition)
        {
            bManualPosition = false;                        //清除手动到位标记
            isLongTablePos = false;

#ifdef QT_ARCH_ARM
            mMoveReadyMask = false;
#endif
        }

        btnLongManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");
        SendKeySingle(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);        //禁止曝光

        btnLongAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw2.png);}");
        AutoPositionIndex = NDT_AUTO_MODE_TABLE;    //初始化变量
        statLongTableAuto = NDT_AUTO_STAT00;

        for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
            pBtnLongCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

        statLongTableStepCounter = 0;
        pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(1));

        //运动时关闭手动调整按钮
        btnLongPanelBack->setEnabled(false);
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setEnabled(false);
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setEnabled(false);
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setEnabled(false);
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");

        tmAutoPosition->start();                                            //开启自动运行定时器
        break;
    case NDT_KEY_BASE_LONG + 10:           //长台向右

        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");

        pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(4));       //绿色
        if(statLongTableStepCounter < pBtnLongCentor.size() - 1)
            statLongTableStepCounter += 1;
        pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(1));       //红色

        SendKeySingle(NDT_KEY_IDX_LMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_LMV) + statLongTableStepCounter * mLongTableRunStep);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

        //运动时关闭手动调整按钮
        btnLongPanelBack->setEnabled(false);
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setEnabled(false);
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setEnabled(false);
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setEnabled(false);
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");

        mExpDelayCtr = NDT_EXP_DELAY_LONG;

        SetInfoText("Wait for machine movement.");
        break;
    default:
        break;
    }

}
void CMainBaseNdt10::OnSmartLongFilmReleased(QKeyEvent * mKey)
{

    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_RELEASE;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_LONG;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_LONG + 0:
        break;
    case NDT_KEY_BASE_LONG + 1:
        break;
    case NDT_KEY_BASE_LONG + 2:
        break;
    case NDT_KEY_BASE_LONG + 3:
        //btnLongManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");
        break;
    case NDT_KEY_BASE_LONG + 4:
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
        break;
    case NDT_KEY_BASE_LONG + 5:

        break;
    case NDT_KEY_BASE_LONG + 6:
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh1.png);}");
        break;
    case NDT_KEY_BASE_LONG + 7:

        break;
    case NDT_KEY_BASE_LONG + 8:
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz1.png);}");
        break;
    case NDT_KEY_BASE_LONG + 9:
        btnLongAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw1.png);}");
        break;
    case NDT_KEY_BASE_LONG + 10:
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy1.png);}");
        break;
    default:
        break;
    }
}
//横臂扫描页面动作支持
void CMainBaseNdt10::BuidSmartArmCtrlBtn()
{

    btnArmExpStill = new CButtonStable(this);
    btnArmExpStill->setGeometry(SYS_WID(80),SYS_HEI(80) ,SYS_WID(80),SYS_HEI(160));
    btnArmExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg1.png);}");
    btnArmExpStill->setVisible(false);
    connect(btnArmExpStill,SIGNAL(pressed()),this,SLOT(OnSmartArmCtrlPressed()));
    connect(btnArmExpStill,SIGNAL(released()),this,SLOT(OnSmartArmCtrlReleased()));
    arrBtnSmartArm.push_back(btnArmExpStill);

    btnArmPanelBack = new CButtonStable(this);
    btnArmPanelBack->setGeometry(SYS_WID(80),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
    btnArmPanelBack->setVisible(false);
    connect(btnArmPanelBack,SIGNAL(pressed()),this,SLOT(OnSmartArmCtrlPressed()));
    connect(btnArmPanelBack,SIGNAL(released()),this,SLOT(OnSmartArmCtrlReleased()));
    arrBtnSmartArm.push_back(btnArmPanelBack);

    btnArmExpMove = new CButtonStable(this);
    btnArmExpMove->setGeometry(SYS_WID(160),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnArmExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg2.png);}");
    btnArmExpMove->setVisible(false);
    connect(btnArmExpMove,SIGNAL(pressed()),this,SLOT(OnSmartArmCtrlPressed()));
    connect(btnArmExpMove,SIGNAL(released()),this,SLOT(OnSmartArmCtrlReleased()));
    arrBtnSmartArm.push_back(btnArmExpMove);

    btnArmPanelFront = new CButtonStable(this);
    btnArmPanelFront->setGeometry(SYS_WID(160),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
    btnArmPanelFront->setVisible(false);
    connect(btnArmPanelFront,SIGNAL(pressed()),this,SLOT(OnSmartArmCtrlPressed()));
    connect(btnArmPanelFront,SIGNAL(released()),this,SLOT(OnSmartArmCtrlReleased()));
    arrBtnSmartArm.push_back(btnArmPanelFront);

    btnArmManual = new CButtonStable(this);
    btnArmManual->setGeometry(SYS_WID(240),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnArmManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");
    btnArmManual->setVisible(false);
    connect(btnArmManual,SIGNAL(pressed()),this,SLOT(OnSmartArmCtrlPressed()));
    connect(btnArmManual,SIGNAL(released()),this,SLOT(OnSmartArmCtrlReleased()));
    arrBtnSmartArm.push_back(btnArmManual);

    btnArmPanelDown = new CButtonStable(this);
    btnArmPanelDown->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
    btnArmPanelDown->setVisible(false);
    connect(btnArmPanelDown,SIGNAL(pressed()),this,SLOT(OnSmartArmCtrlPressed()));
    connect(btnArmPanelDown,SIGNAL(released()),this,SLOT(OnSmartArmCtrlReleased()));
    arrBtnSmartArm.push_back(btnArmPanelDown);

    btnArmAuto = new CButtonStable(this);
    btnArmAuto->setGeometry(SYS_WID(320),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnArmAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw1.png);}");
    btnArmAuto->setVisible(false);
    connect(btnArmAuto,SIGNAL(pressed()),this,SLOT(OnSmartArmCtrlPressed()));
    connect(btnArmAuto,SIGNAL(released()),this,SLOT(OnSmartArmCtrlReleased()));
    arrBtnSmartArm.push_back(btnArmAuto);

    btnArmPanelUp = new CButtonStable(this);
    btnArmPanelUp->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnArmPanelUp->setGeometry(SYS_WID(320),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
    btnArmPanelUp->setVisible(false);
    connect(btnArmPanelUp,SIGNAL(pressed()),this,SLOT(OnSmartArmCtrlPressed()));
    connect(btnArmPanelUp,SIGNAL(released()),this,SLOT(OnSmartArmCtrlReleased()));
    arrBtnSmartArm.push_back(btnArmPanelUp);

}

//长台扫描页面动作支持，按下
void CMainBaseNdt10::OnSmartArmCtrlPressed()
{

    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnArmExpStill)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnArmPanelFront)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnArmExpMove)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnArmPanelBack)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnArmManual)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnArmPanelUp)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnArmAuto)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnArmPanelDown)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

}

//长台扫描页面动作支持，释放
void CMainBaseNdt10::OnSmartArmCtrlReleased()
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnArmExpStill)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 3 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnArmPanelFront)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 4 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnArmExpMove)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnArmPanelBack)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnArmManual)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnArmPanelUp)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnArmAuto)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnArmPanelDown)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

}


void CMainBaseNdt10::OnSmartArmFilmPressed(QKeyEvent * mKey)
{
    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_PRESS;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_ARM;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_ARM + 0:
        break;
    case NDT_KEY_BASE_ARM + 1:
        ShowPage(getPageIdxBuf());
        break;
    case NDT_KEY_BASE_ARM + 2:
        break;
    case NDT_KEY_BASE_ARM + 3:

        btnArmExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg2.png);}");
        btnArmExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg1.png);}");
        bLongExpStill = true;

        break;
    case NDT_KEY_BASE_ARM + 4:          //平板向前

        pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(4));       //绿色

        if(statArmTableStepCounter  <  3)
            statArmTableStepCounter += 1;

        pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(1));       //红色

        SendKeySingle(NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_UID) - statArmTableStepCounter * mArmTableRunStep);
        SendKeyMulti(NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_CEP) - statArmTableStepCounter * mArmTableRunStep);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);        //禁止曝光

        btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
        btnArmPanelUp->setEnabled(false);
        btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
        btnArmPanelDown->setEnabled(false);
        btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnArmPanelFront->setEnabled(false);
        btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnArmPanelBack->setEnabled(false);

        mExpDelayCtr = NDT_EXP_DELAY_SMALL;
        SetInfoText("Wait for machine movement.");
        break;
    case NDT_KEY_BASE_ARM + 5:

        btnLongExpStill->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/jzbg1.png);}");
        btnLongExpMove->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ldbg2.png);}");
        bLongExpStill = false;

        break;
    case NDT_KEY_BASE_ARM + 6:          //平板向后

        pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(4));       //绿色

        if(statArmTableStepCounter > 0)
            statArmTableStepCounter -= 1;

        pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(1));       //红色

        btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
        btnArmPanelUp->setEnabled(false);
        btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
        btnArmPanelDown->setEnabled(false);
        btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnArmPanelFront->setEnabled(false);
        btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnArmPanelBack->setEnabled(false);

        SendKeySingle(NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_UID) - statArmTableStepCounter * mArmTableRunStep);
        SendKeyMulti(NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_CEP) - statArmTableStepCounter * mArmTableRunStep);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);        //禁止曝光

        mExpDelayCtr = NDT_EXP_DELAY_SMALL;
        SetInfoText("Wait for machine movement.");
        break;
    case NDT_KEY_BASE_ARM + 7:
        if(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI] > 1400 && g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP] > 3500)
        {
            mMoveReadyMask = true;
            AutoPositionIndex = NDT_AUTO_MODE_ARM;
            bManualPosition = true;
            statArmTableAuto = NDT_AUTO_STAT11;
            btnArmManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw2.png);}");
            tmAutoPosition->start();
        }
        break;
    case NDT_KEY_BASE_ARM + 8:       // 横臂向上

        btnArmPanelUp->setEnabled(false);
        btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");

        SendKeySingle(NDT_KEY_IDX_HEI,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_HEI) );
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);
        mTubeFollowStart = g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI];
        mExpDelayCtr = NDT_EXP_DELAY_LONG;
        SetInfoText("Wait for machine movement.");
        break;
    case NDT_KEY_BASE_ARM + 9:                              //横臂扫描，自动到位

        isLongTablePos = false;
        isSmallTablePos = false;
        isRoundTablePos = false;

        if(bManualPosition)                        //清除手动到位标记
        {
            bManualPosition = false;
            mMoveReadyMask = false;
#ifdef QT_ARCH_ARM
            mMoveReadyMask = false;
#endif
        }

        AutoPositionIndex = NDT_AUTO_MODE_ARM;    //初始化变量
        statArmTableAuto = NDT_AUTO_STAT00;

        btnArmManual->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/sddw1.png);}");
        SendKeySingle(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);        //禁止曝光

        btnArmAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw2.png);}");

        for(int mIdx = 0 ; mIdx < pBtnArmCentor.size() ; mIdx++)
            pBtnArmCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

        //运动时关闭手动调整按钮
        btnArmPanelBack->setEnabled(false);
        btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnArmPanelFront->setEnabled(false);
        btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnArmPanelUp->setEnabled(false);
        btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
        btnArmPanelDown->setEnabled(false);
        btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");

        tmAutoPosition->start();                                            //开启自动运行定时器
        break;
    case NDT_KEY_BASE_ARM + 10:     // 横臂向下,按下

        SendKeySingle(NDT_KEY_IDX_HEI,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_HEI) -  400);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);
        mTubeFollowStart = g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI];
        mExpDelayCtr = NDT_EXP_DELAY_LONG;
        SetInfoText("Wait for machine movement.");
        break;
    default:
        break;
    }

}
void CMainBaseNdt10::OnSmartArmFilmReleased(QKeyEvent * mKey)
{

    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_RELEASE;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_ARM;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_ARM + 0:
        break;
    case NDT_KEY_BASE_ARM + 1:
        break;
    case NDT_KEY_BASE_ARM + 2:
        break;
    case NDT_KEY_BASE_ARM + 3:
        break;
    case NDT_KEY_BASE_ARM + 4:

        btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
        break;
    case NDT_KEY_BASE_ARM + 5:

        break;
    case NDT_KEY_BASE_ARM + 6:

        btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh1.png);}");
        break;
    case NDT_KEY_BASE_ARM + 7:

        break;
    case NDT_KEY_BASE_ARM + 8:

        SendKeySingle(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);

        btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs1.png);}");

        tmArmTubeFollow->start();

        break;
    case NDT_KEY_BASE_ARM + 9:
        btnArmAuto->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zddw1.png);}");
        break;

    case NDT_KEY_BASE_ARM + 10:     // 横臂向下,抬起

        SendKeySingle(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);

        btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx1.png);}");

        tmArmTubeFollow->start();

        break;
    default:
        break;
    }
}
void CMainBaseNdt10::BuidStandCtrlBtn()
{

    btnNullLeft = new CButtonStable(this);
    btnNullLeft->setGeometry(SYS_WID(80),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnNullLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/kb.png);}");
    arrBtnStand.push_back(btnNullLeft);

    btnNullRight = new CButtonStable(this);
    btnNullRight->setGeometry(SYS_WID(80),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnNullRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/kb.png);}");
    arrBtnStand.push_back(btnNullRight);

    btnDtaDec = new CButtonStable(this);
    btnDtaDec->setGeometry(SYS_WID(160),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnDtaDec->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbsp1.png);}");
    connect(btnDtaDec,SIGNAL(pressed()),this,SLOT(OnStandCtrlPressed()));
    connect(btnDtaDec,SIGNAL(released()),this,SLOT(OnStandCtrlReleased()));
    arrBtnStand.push_back(btnDtaDec);

    btnDtaAdd = new CButtonStable(this);
    btnDtaAdd->setGeometry(SYS_WID(160),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnDtaAdd->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbcz1.png);}");
    connect(btnDtaAdd,SIGNAL(pressed()),this,SLOT(OnStandCtrlPressed()));
    connect(btnDtaAdd,SIGNAL(released()),this,SLOT(OnStandCtrlReleased()));
    arrBtnStand.push_back(btnDtaAdd);

    btnUidFront = new CButtonStable(this);
    btnUidFront->setGeometry(SYS_WID(240),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnUidFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
    connect(btnUidFront,SIGNAL(pressed()),this,SLOT(OnStandCtrlPressed()));
    connect(btnUidFront,SIGNAL(released()),this,SLOT(OnStandCtrlReleased()));
    arrBtnStand.push_back(btnUidFront);

    btnUidBack = new CButtonStable(this);
    btnUidBack->setGeometry(SYS_WID(240),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnUidBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh1.png);}");
    connect(btnUidBack,SIGNAL(pressed()),this,SLOT(OnStandCtrlPressed()));
    connect(btnUidBack,SIGNAL(released()),this,SLOT(OnStandCtrlReleased()));
    arrBtnStand.push_back(btnUidBack);

    btnHeiUp = new CButtonStable(this);
    btnHeiUp->setGeometry(SYS_WID(320),SYS_HEI(80),SYS_WID(80),SYS_HEI(160));
    btnHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs1.png);}");
    connect(btnHeiUp,SIGNAL(pressed()),this,SLOT(OnStandCtrlPressed()));
    connect(btnHeiUp,SIGNAL(released()),this,SLOT(OnStandCtrlReleased()));
    arrBtnStand.push_back(btnHeiUp);

    btnHeiDown = new CButtonStable(this);
    btnHeiDown->setGeometry(SYS_WID(320),SYS_HEI(360),SYS_WID(80),SYS_HEI(160));
    btnHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx1.png);}");
    connect(btnHeiDown,SIGNAL(pressed()),this,SLOT(OnStandCtrlPressed()));
    connect(btnHeiDown,SIGNAL(released()),this,SLOT(OnStandCtrlReleased()));
    arrBtnStand.push_back(btnHeiDown);
}

void CMainBaseNdt10::OnStandCtrlPressed()
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnHeiUp)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnHeiDown)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnUidFront)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnUidBack)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnDtaDec)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmPressed(keyEventBtn);
        return;
    }

    if(sender() == btnDtaAdd)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmPressed(keyEventBtn);
        return;
    }

}

void CMainBaseNdt10::OnStandCtrlReleased()
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(sender() == btnHeiUp)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 9 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnHeiDown)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 10 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnUidFront)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 7 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmReleased(keyEventBtn);
        return;
    }
    if(sender() == btnUidBack)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 8 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnDtaDec)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 5 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmReleased(keyEventBtn);
        return;
    }

    if(sender() == btnDtaAdd)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress, 6 + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmReleased(keyEventBtn);
        return;
    }
}

void CMainBaseNdt10::OnStandFilmPressed(QKeyEvent * mKey)
{
    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_PRESS;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_STAND;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_STAND + 0:
        ShowPage(NDT_PAGE_STAND);
        break;
    case NDT_KEY_BASE_STAND + 1:
        ShowPage(NDT_PAGE_TABLE);
        break;
    case NDT_KEY_BASE_STAND + 2:
        ShowPage(NDT_PAGE_TUBE);
        break;
    case NDT_KEY_BASE_STAND + 3:             //NULL
        break;
    case NDT_KEY_BASE_STAND + 4:             //NULL
        break;
    case NDT_KEY_BASE_STAND + 5:
        btnDtaDec->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbsp2.png);}");
        SendKeySingle(NDT_KEY_IDX_DTA,g_motorMgr->getLimitMin(NDT_KEY_IDX_DTA));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_STAND + 6:
        btnDtaAdd->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbcz2.png);}");
        SendKeySingle(NDT_KEY_IDX_DTA,g_motorMgr->getLimitMax(NDT_KEY_IDX_DTA));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_STAND + 7:
        btnUidFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        SendKeySingle(NDT_KEY_IDX_UID,g_motorMgr->getLimitMin(NDT_KEY_IDX_UID));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_STAND + 8:
        btnUidBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        SendKeySingle(NDT_KEY_IDX_UID,g_motorMgr->getLimitMax(NDT_KEY_IDX_UID));

        //禁止按钮控制
        btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
        btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");
        break;
    case NDT_KEY_BASE_STAND + 9:
        btnHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
        SendKeySingle(NDT_KEY_IDX_HEI,g_motorMgr->getLimitMax(NDT_KEY_IDX_HEI));

        break;
    case NDT_KEY_BASE_STAND + 10:
        btnHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
        SendKeySingle(NDT_KEY_IDX_HEI,g_motorMgr->getLimitMin(NDT_KEY_IDX_HEI));

        break;
    default:
        break;
    }

}

void CMainBaseNdt10::OnStandFilmReleased(QKeyEvent * mKey)
{

    //如果是客户端，先通过网络将该命令发送给服务端
    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        if(mKey && g_netBase)
        {
            unsigned short * keyBuf = g_netBase->getBufWrite();
            keyBuf[0] = NET_CMD_KEY_RELEASE;
            keyBuf[1] = mKey->key() - NDT_KEY_BASE_STAND;
            g_netBase->PublishMessage();
            //fprintf(stderr, "PublishMessage: %d\n", keyBuf[1]);
        }
    }

    switch(mKey->key())
    {
    case NDT_KEY_BASE_STAND + 0:
        break;
    case NDT_KEY_BASE_STAND + 1:
        break;
    case NDT_KEY_BASE_STAND + 2:
        break;
    case NDT_KEY_BASE_STAND + 3:             //NULL
        break;
    case NDT_KEY_BASE_STAND + 4:             //NULL
        break;
    case NDT_KEY_BASE_STAND + 5:
        btnDtaDec->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbsp1.png);}");
        SendKeySingle(NDT_KEY_IDX_DTA,NDT_MOTOR_STOP);      //动作停止，删除安全检测
        break;
    case NDT_KEY_BASE_STAND + 6:
        btnDtaAdd->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbcz1.png);}");
        SendKeySingle(NDT_KEY_IDX_DTA,NDT_MOTOR_STOP);      //动作停止，删除安全检测
        break;
    case NDT_KEY_BASE_STAND + 7:
        btnUidFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
        SendKeySingle(NDT_KEY_IDX_UID,NDT_MOTOR_STOP);      //动作停止，删除安全检测
        break;
    case NDT_KEY_BASE_STAND + 8:
        btnUidBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh1.png);}");
        SendKeySingle(NDT_KEY_IDX_UID,NDT_MOTOR_STOP);      //动作停止，删除安全检测
        break;
    case NDT_KEY_BASE_STAND + 9:
        btnHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs1.png);}");
        SendKeySingle(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);      //动作停止，删除安全检测
        break;
    case NDT_KEY_BASE_STAND + 10:
        btnHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx1.png);}");
        SendKeySingle(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);      //动作停止，删除安全检测
        break;
    default:
        break;
    }
}
//数据显示更新
//安全检测
//间隔NDT_FRESH_INTERVAL   400ms运行一次
void CMainBaseNdt10::OnNdtDataFresh()
{

#define NDT_WATCH_DOG_DELAY 1

    if(++mWatchDogCtr  >NDT_WATCH_DOG_DELAY)
    {
        unsigned short keyBuf[8];
        keyBuf[0] = CMD_KEEP_ALIVE_DATA;
        g_taskComCtrl->CreateTask(CMD_KEEP_ALIVE_HEADER,keyBuf,1);

        mWatchDogCtr = 0;
    }

    ExpControl();       //曝光消息检测与运动步进运动控制

    //更新碰撞检测的数据
    mech->FreshDatas(g_systemDb->g_iArrNdtState);

    //运行碰撞检测
    mech->CollisionDetect();

    //更新显示
    switch(getPageIdx())
    {
    case NDT_PAGE_STAND:

        pLcdDisplay[0]->setVisible(false);
        pLcdDisplay[1]->setVisible(true);
        pLcdDisplay[1]->display(short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA]));
        pLcdDisplay[2]->setVisible(true);
        pLcdDisplay[2]->display(short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID]));
        pLcdDisplay[3]->setVisible(true);
        pLcdDisplay[3]->display(short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI]));

        break;
    case NDT_PAGE_TABLE:
        pLcdDisplay[0]->setVisible(true);
        pLcdDisplay[0]->display(short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SRL]));
        pLcdDisplay[1]->setVisible(true);
        pLcdDisplay[1]->display(short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ROL]));
        pLcdDisplay[2]->setVisible(true);
        pLcdDisplay[2]->display(short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV]));
        pLcdDisplay[3]->setVisible(true);
        pLcdDisplay[3]->display(short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV]));
        break;
    case NDT_PAGE_TUBE:
        pLcdDisplay[0]->setVisible(true);
        pLcdDisplay[0]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG]));
        pLcdDisplay[1]->setVisible(true);
        pLcdDisplay[1]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP]));
        pLcdDisplay[2]->setVisible(true);
        pLcdDisplay[2]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID]));
        pLcdDisplay[3]->setVisible(true);
        pLcdDisplay[3]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID]));
        break;
    case NDT_PAGE_SCAN_LONG:
        pLcdDisplay[0]->setVisible(true);
        pLcdDisplay[0]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP]));
        pLcdDisplay[1]->setVisible(true);
        pLcdDisplay[1]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID]));
        pLcdDisplay[2]->setVisible(true);
        pLcdDisplay[2]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID]));
        pLcdDisplay[3]->setVisible(true);
        pLcdDisplay[3]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV]));
        break;
    case NDT_PAGE_SCAN_ARM:
        pLcdDisplay[0]->setVisible(true);
        pLcdDisplay[0]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP]));
        pLcdDisplay[1]->setVisible(true);
        pLcdDisplay[1]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID]));
        pLcdDisplay[2]->setVisible(true);
        pLcdDisplay[2]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID]));
        pLcdDisplay[3]->setVisible(true);
        pLcdDisplay[3]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI]));
        break;
    case NDT_PAGE_SCAN_ROUND:
        pLcdDisplay[0]->setVisible(true);
        pLcdDisplay[0]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA]));
        pLcdDisplay[1]->setVisible(true);
        pLcdDisplay[1]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV]));
        pLcdDisplay[2]->setVisible(true);
        pLcdDisplay[2]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG]));
        pLcdDisplay[3]->setVisible(true);
        pLcdDisplay[3]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ROL]));
        break;
    case NDT_PAGE_SCAN_SMALL:
        pLcdDisplay[0]->setVisible(true);
        pLcdDisplay[0]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID]));
        pLcdDisplay[1]->setVisible(true);
        pLcdDisplay[1]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI]));
        pLcdDisplay[2]->setVisible(true);
        pLcdDisplay[2]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG]));
        pLcdDisplay[3]->setVisible(true);
        pLcdDisplay[3]->display( short(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SRL]));
        break;
    default:
        break;
    }

    unsigned short mEmStopBuf = 0;
    for (int mIdx = NDT_KEY_IDX_UID ; mIdx <= NDT_KEY_IDX_HEI ; mIdx++)
    {
        mEmStopBuf += g_systemDb->g_iArrNdtState[mIdx];
    }

    if(!g_systemDb->g_bCommunicate)
    {
        SetWarningText("Communication failure!");
    }else if(mEmStopBuf == 0)
    {
        SetWarningText("Please Check Emergency Stop!");
        update();
        //return;
    }else
    {
        if(gStrWarnings == "Please Check Emergency Stop!")
        {
            gStrWarnings = "";
            update();
        }
        if(gStrWarnings == "Communication failure!")
        {
            gStrWarnings = "";
            update();
        }
    }
}

void CMainBaseNdt10::ExpControl()
{

    if(mExpDelayCtr <= NDT_EXP_DELAY_EN)                    //每次循环，更新曝光延时计数器
        mExpDelayCtr = NDT_EXP_DELAY_EN;
    else
        mExpDelayCtr --;

    if(mExpDelayCtr != NDT_EXP_DELAY_EN)                    //延时时间未到，不进行控制
        return;

    if(tmAutoPosition->isActive() || bLongExpStill)         //定时器未关闭或者手动曝光模式，不进行控制
        return;

    switch(m_pageIdx)
    {
    case NDT_PAGE_SCAN_LONG:
        ExpControlLongV2();
        break;
    case NDT_PAGE_SCAN_ARM:
        ExpControlArmV1();
        break;
    case NDT_PAGE_SCAN_ROUND:
        ExpControlRound();
        break;
    case NDT_PAGE_SCAN_SMALL:
        ExpControlSmall();
        break;
    default:
        break;
    }

}

void CMainBaseNdt10::ExpControlLongV2()
{

    //处于长台扫描模式，且已经到位
    if(AutoPositionIndex != NDT_AUTO_MODE_TABLE || !isLongTablePos)
        return;

    //输出曝光允许信号
    //if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_LMV_STOP_MASK) == 0 && (g_systemDb->g_iArrNdtState[NDT_KEY_IDX_IN] & 0x0001) == 0 )
    if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_LMV_STOP_MASK) == 0 )
    {
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);
        pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(2));

        if(statLongTableStepCounter == 0 || statLongTableStepCounter == mLongTableRunStepNumber )
        {
            if(mPanelBorderType ==  NDT_PANEL_BORDER_BACK)
            {
                btnLongPanelFront->setEnabled(true);
                btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
                btnLongPanelBack->setEnabled(false);
                btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
            }

            if(mPanelBorderType ==  NDT_PANEL_BORDER_FRONT)
            {
                btnLongPanelFront->setEnabled(false);
                btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
                btnLongPanelBack->setEnabled(true);
                btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh1.png);}");
            }

            if(mPanelBorderType ==  NDT_PANEL_BORDER_CENTOR)
            {
                btnLongPanelFront->setEnabled(true);
                btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
                btnLongPanelBack->setEnabled(true);
                btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh1.png);}");
            }
        }

        if(statLongTableStepCounter != 0)
        {
            btnLongTableLeft->setEnabled(true);
            btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz1.png);}");
        }
        if(statLongTableStepCounter != mLongTableRunStepNumber )
        {
            btnLongTableRight->setEnabled(true);
            btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy1.png);}");
        }

        SetInfoText("Ready for image capture.");
    }

    //等待曝光信号输入
    if((g_systemDb->g_iArrNdtState[NDT_KEY_IDX_IN] & 0x000f) == 0 )
        return;

    //只扫描中心线的方式
    //走完步数之后，切换Step的符号
    if(statLongTableStepCounter == 0)       //第一个曝光位置的处理
    {
        if(mLongExpDir == 1)                //正向第一次曝光
        {

        }else                                           //反向最后一次曝光
        {
            //mLongTableRunStep *= -1;            //步进数据进行反向
            mLongExpDir = 1;                            //运行方向为正
            statLongTableStepCounter = 0;       //计数器清0
            SendKeySingle(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

            for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)           //所有背景颜色清空
                pBtnLongCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

            //需要曝光的位置值为黄色
            // pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(2));
            pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(1));
            mExpDelayCtr = NDT_EXP_DELAY_LONG;

            if(mPanelBorderType ==  NDT_PANEL_BORDER_BACK)
            {
                mPanelBorderType = NDT_PANEL_BORDER_FRONT;
                SendKeyMulti(NDT_KEY_IDX_UID,mPanelYStepMax);
                SendKeyMulti(NDT_KEY_IDX_CEP,mTubeYStepMax);

                for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
                {
                    QRect mRect = pBtnLongCentor.at(mIdx)->geometry();
                    mRect.moveLeft(SYS_WID(550));
                    pBtnLongCentor.at(mIdx)->setGeometry(mRect);
                }
            }else if(mPanelBorderType ==  NDT_PANEL_BORDER_FRONT)
            {

                mPanelBorderType = NDT_PANEL_BORDER_BACK;
                SendKeyMulti(NDT_KEY_IDX_UID,mPanelYStepMin);
                SendKeyMulti(NDT_KEY_IDX_CEP,mTubeYStepMin);

                for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
                {
                    QRect mRect = pBtnLongCentor.at(mIdx)->geometry();
                    mRect.moveLeft(SYS_WID(470));
                    pBtnLongCentor.at(mIdx)->setGeometry(mRect);
                }
            }

            SetInfoText("Wait for machine movement.");
            return;
        }
    }

    if(statLongTableStepCounter == mLongTableRunStepNumber)
    {
        if(mLongExpDir == 1)                //正向最后一次曝光
        {
            for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
                pBtnLongCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

            pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(1));

            mLongExpDir = -1;

            SendKeySingle(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

            if(mPanelBorderType ==  NDT_PANEL_BORDER_BACK)
            {
                mPanelBorderType = NDT_PANEL_BORDER_FRONT;
                SendKeyMulti(NDT_KEY_IDX_UID,mPanelYStepMax);
                SendKeyMulti(NDT_KEY_IDX_CEP,mTubeYStepMax);

                for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
                {
                    QRect mRect = pBtnLongCentor.at(mIdx)->geometry();
                    mRect.moveLeft(SYS_WID(550));
                    pBtnLongCentor.at(mIdx)->setGeometry(mRect);
                }
            }else if(mPanelBorderType ==  NDT_PANEL_BORDER_FRONT)
            {

                mPanelBorderType = NDT_PANEL_BORDER_BACK;
                SendKeyMulti(NDT_KEY_IDX_UID,mPanelYStepMin);
                SendKeyMulti(NDT_KEY_IDX_CEP,mTubeYStepMin);

                for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)
                {
                    QRect mRect = pBtnLongCentor.at(mIdx)->geometry();
                    mRect.moveLeft(SYS_WID(470));
                    pBtnLongCentor.at(mIdx)->setGeometry(mRect);
                }
            }

            //运动时关闭手动调整按钮
            btnLongPanelBack->setEnabled(false);
            btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
            btnLongPanelFront->setEnabled(false);
            btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
            btnLongTableLeft->setEnabled(false);
            btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
            btnLongTableRight->setEnabled(false);
            btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");

            SetInfoText("Wait for machine movement.");

            mExpDelayCtr = NDT_EXP_DELAY_LONG;
            return;
        }
    }

    pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(3));       //绿色
    statLongTableStepCounter += mLongExpDir;
    pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(1));       //红色

    //修正由于电机速度提高造成的绝对误差
    SendKeySingle(NDT_KEY_IDX_LMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_LMV) + statLongTableStepCounter * mLongTableRunStep);
    SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

    SetInfoText("Wait for machine movement.");

    //运动时关闭手动调整按钮
    btnLongPanelBack->setEnabled(false);
    btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
    btnLongPanelFront->setEnabled(false);
    btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
    btnLongTableLeft->setEnabled(false);
    btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
    btnLongTableRight->setEnabled(false);
    btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");

    mExpDelayCtr = NDT_EXP_DELAY_LONG;

}

void CMainBaseNdt10::ExpControlArmV1()
{

    //处于长台扫描模式，且已经到位
    if(AutoPositionIndex != NDT_AUTO_MODE_ARM || !isArmTablePos)
        return;

    //输出曝光允许信号
    //if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_UID_STOP_MASK) == 0 && (g_systemDb->g_iArrNdtState[NDT_KEY_IDX_IN] & 0x0001) == 0 )
    if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_UID_STOP_MASK) == 0 )
    {
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);
        pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(2));

        if(statArmTableStepCounter == pBtnArmCentor.size() - 1)
        {
            btnArmPanelFront->setEnabled(false);
            btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
        }else
        {
            btnArmPanelFront->setEnabled(true);
            btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
        }

        if(statArmTableStepCounter == 0)
        {
            btnArmPanelBack->setEnabled(false);
            btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
        }else
        {
            btnArmPanelBack->setEnabled(true);
            btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh1.png);}");
        }

        btnArmPanelUp->setEnabled(true);
        btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs1.png);}");
        btnArmPanelDown->setEnabled(true);
        btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx1.png);}");

        SetInfoText("Ready for image capture.");
    }

    //等待曝光信号输入
    if((g_systemDb->g_iArrNdtState[NDT_KEY_IDX_IN] & 0x000f) == 0 )
        return;

    //只扫描中心线的方式
    //走完步数之后，切换Step的符号
    if(statArmTableStepCounter == 0)       //第一个曝光位置的处理
    {
        if(mArmExpDir != 1)                //正向第一次曝光
        {
            mArmExpDir = 1;                            //运行方向为正
            statArmTableStepCounter = 0;       //计数器清0

            for(int mIdx = 0 ; mIdx < pBtnArmCentor.size() ; mIdx++)           //所有背景颜色清空
                pBtnArmCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

            //需要曝光的位置值为黄色
            pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(2));
            SetInfoText("Wait for machine movement.");

            mExpDelayCtr = NDT_EXP_DELAY_LONG;
            return;
        }
    }

    if(statArmTableStepCounter == mArmTableRunStepNumber)
    {
        if(mArmExpDir == 1)                //正向最后一次曝光
        {
            for(int mIdx = 0 ; mIdx < pBtnArmCentor.size() ; mIdx++)
                pBtnArmCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

            statArmTableStepCounter = pBtnArmCentor.size() - 1;
            pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(1));

            mArmExpDir = -1;

            //运动时关闭手动调整按钮
            btnArmPanelBack->setEnabled(false);
            btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
            btnArmPanelFront->setEnabled(false);
            btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
            btnArmPanelUp->setEnabled(false);
            btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
            btnArmPanelDown->setEnabled(false);
            btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");

            SetInfoText("Wait for machine movement.");

            mExpDelayCtr = NDT_EXP_DELAY_LONG;
            return;
        }
    }

    pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(3));       //绿色
    statArmTableStepCounter += mArmExpDir;
    pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(1));       //红色

    //修正由于电机速度提高造成的绝对误差
    SendKeySingle(NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_UID) - statArmTableStepCounter * mArmTableRunStep);
    SendKeyMulti(NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_CEP) - statArmTableStepCounter * mArmTableRunStep);
    SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);        //禁止曝光

    //运动时关闭手动调整按钮
    btnArmPanelBack->setEnabled(false);
    btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
    btnArmPanelFront->setEnabled(false);
    btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
    btnArmPanelUp->setEnabled(false);
    btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
    btnArmPanelDown->setEnabled(false);
    btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");

    SetInfoText("Wait for machine movement.");
    mExpDelayCtr = NDT_EXP_DELAY_LONG;

}

void CMainBaseNdt10::ExpControlRound()
{

    //处于圆台扫描，且已经到位

    if(AutoPositionIndex != NDT_AUTO_MODE_ROUND_FLAT  &&  AutoPositionIndex != NDT_AUTO_MODE_ROUND_ANG)
        return;

    if( !isRoundTablePos)
        return;

    //输出曝光允许信号
    if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_ROL_STOP_MASK) == 0 )
    {
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);
        arrRenderRound->at(2)->setFillColor(Qt::yellow);

        if(mRoundPanelIndex == 2)
        {
            btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz2.png);}");
            btnRoundTableFz->setEnabled(false);

            if(mRoundTableRotateStep == 30)
            {
                btnRoundTableR30->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd302.png);}");
                btnRoundTableR30->setEnabled(false);
            }else
            {
                btnRoundTableR30->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd301.png);}");
                btnRoundTableR30->setEnabled(true);
            }

            if(mRoundTableRotateStep == 20)
            {
                btnRoundTableR20->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd202.png);}");
                btnRoundTableR20->setEnabled(false);
            }else
            {
                btnRoundTableR20->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd201.png);}");
                btnRoundTableR20->setEnabled(true);
            }

            if(mRoundTableRotateStep == 18)
            {
                btnRoundTableR18->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd182.png);}");
                btnRoundTableR18->setEnabled(false);
            }else
            {
                btnRoundTableR18->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd181.png);}");
                btnRoundTableR18->setEnabled(true);
            }

            if(mRoundTableRotateStep == 15)
            {
                btnRoundTableR15->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd152.png);}");
                btnRoundTableR15->setEnabled(false);
            }else
            {
                btnRoundTableR15->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd151.png);}");
                btnRoundTableR15->setEnabled(true);
            }

        }else
        {

            btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz1.png);}");
            btnRoundTableFz->setEnabled(true);

            if(btnRoundTableR30->isEnabled() || btnRoundTableR20->isEnabled()  || btnRoundTableR18->isEnabled()  || btnRoundTableR15->isEnabled() )
            {
                btnRoundTableR30->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd302.png);}");
                btnRoundTableR30->setEnabled(false);
                btnRoundTableR20->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd202.png);}");
                btnRoundTableR20->setEnabled(false);
                btnRoundTableR18->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd182.png);}");
                btnRoundTableR18->setEnabled(false);
                btnRoundTableR15->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd152.png);}");
                btnRoundTableR15->setEnabled(false);
            }
        }

        if(mRoundPanelIndex ==  (360 / mRoundTableRotateStep + 1))
        {
            btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz2.png);}");
            btnRoundTableZz->setEnabled(false);
        }else
        {
            btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz1.png);}");
            btnRoundTableZz->setEnabled(true);
        }

        btnRoundTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz1.png);}");
        btnRoundTableFz->setEnabled(true);
        btnRoundTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy1.png);}");
        btnRoundTableRight->setEnabled(true);

        SetInfoText("Ready for image capture.");
    }

    //等待曝光信号输入
    if((g_systemDb->g_iArrNdtState[NDT_KEY_IDX_IN] & 0x000f) == 0 )
        return;

    //不进行逆时针拍摄，顺时针360度后直接返回0度
    if(mRoundPanelIndex >=  (360 / mRoundTableRotateStep + 1) )
    {
        //360度扫描完后，将部分可视部分隐藏
        for( int mIdx = 3; mIdx <= mRoundPanelIndex ; mIdx ++)
            arrRenderRound->at(mIdx)->setBeShow(false);

        btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz2.png);}");
        btnRoundTableZz->setEnabled(false);
        btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz2.png);}");
        btnRoundTableFz->setEnabled(false);
        btnRoundTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz2.png);}");
        btnRoundTableFz->setEnabled(false);
        btnRoundTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy2.png);}");
        btnRoundTableRight->setEnabled(false);

        //参数初始化
        mRoundPanelIndex = 2;
        mExpDelayCtr = NDT_EXP_DELAY_ROUND;

        SendKeySingle(NDT_KEY_IDX_ROL,0);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);        //禁止曝光

        SetInfoText("Wait for machine movement.");
        return;
    }else
    {
        btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz2.png);}");
        btnRoundTableZz->setEnabled(false);
        btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz2.png);}");
        btnRoundTableFz->setEnabled(false);
        btnRoundTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz2.png);}");
        btnRoundTableFz->setEnabled(false);
        btnRoundTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy2.png);}");
        btnRoundTableRight->setEnabled(false);

        arrRenderRound->at(2)->setFillColor(Qt::red);
        mRoundPanelIndex += mRoundExpDir;
        arrRenderRound->at(mRoundPanelIndex)->setBeShow(true);

        for( int mIdx = mRoundPanelIndex; mIdx > 2 ; mIdx --)
            arrRenderRound->at(mIdx)->setFillColor(arrRenderRound->at(mIdx-1)->getFillColor());

        arrRenderRound->at(3)->setFillColor(Qt::green);

        //运动控制指令
        SendKeySingle(NDT_KEY_IDX_ROL,(mRoundPanelIndex - 2 )* mRoundTableRotateStep);
        mExpDelayCtr = NDT_EXP_DELAY_ROUND;

        SetInfoText("Wait for machine movement.");

        return;
    }
}


void CMainBaseNdt10::ExpControlSmall()
{

    //处于小圆台扫描模式，且已经到位
    if(AutoPositionIndex != NDT_AUTO_MODE_SMALL || !isSmallTablePos)
        return;

    //输出曝光允许信号
    //if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_SRL_STOP_MASK) == 0 && (g_systemDb->g_iArrNdtState[NDT_KEY_IDX_IN] & 0x0001) == 0 )
    if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_SRL_STOP_MASK) == 0 )
    {
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);
        arrRenderSmall->at(2)->setFillColor(Qt::yellow);

        btnSmallHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx1.png);}");
        btnSmallHeiDown->setEnabled(true);

        btnSmallHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs1.png);}");
        btnSmallHeiUp->setEnabled(true);

        if(mSmallPanelIndex == 2)
        {
            btnSmallTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz2.png);}");
            btnSmallTableFz->setEnabled(false);

            if(mSmallAngleRotate != 60)
            {
                btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd601.png);}");
                btnSmallTableR60->setEnabled(true);
            }
            if(mSmallAngleRotate != 45)
            {
                btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd451.png);}");
                btnSmallTableR45->setEnabled(true);
            }
            if(mSmallAngleRotate != 40)
            {
                btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd401.png);}");
                btnSmallTableR40->setEnabled(true);
            }
            if(mSmallAngleRotate != 36)
            {
                btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd361.png);}");
                btnSmallTableR36->setEnabled(true);
            }
        }else
        {
            btnSmallTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz1.png);}");
            btnSmallTableFz->setEnabled(true);

            btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd602.png);}");
            btnSmallTableR60->setEnabled(false);
            btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd452.png);}");
            btnSmallTableR45->setEnabled(false);
            btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd402.png);}");
            btnSmallTableR40->setEnabled(false);
            btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd362.png);}");
            btnSmallTableR36->setEnabled(false);
        }

        if(mSmallPanelIndex  >= arrRenderSmall->size() -1)
        {
            btnSmallTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz2.png);}");
            btnSmallTableZz->setEnabled(false);
        }else
        {
            btnSmallTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz1.png);}");
            btnSmallTableZz->setEnabled(true);
        }

        SetInfoText("Ready for image capture.");
    }

    if((g_systemDb->g_iArrNdtState[NDT_KEY_IDX_IN] & 0x000f) == 0 )
        return;

    if(mSmallPanelIndex >= arrRenderSmall->size() -1)
    {
        arrRenderSmall->at(2)->setFillColor(Qt::red);

        for( int mIdx = 3; mIdx <= mSmallPanelIndex ; mIdx ++)
            arrRenderSmall->at(mIdx)->setBeShow(false);

        mSmallPanelIndex = 2;

        mExpDelayCtr = NDT_EXP_DELAY_SMALL;
        SendKeySingle(NDT_KEY_IDX_SRL,0);

        btnSmallHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
        btnSmallHeiDown->setEnabled(false);
        btnSmallHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
        btnSmallHeiUp->setEnabled(false);
        btnSmallTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz2.png);}");
        btnSmallTableFz->setEnabled(false);
        btnSmallTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz2.png);}");
        btnSmallTableZz->setEnabled(false);

        btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd602.png);}");
        btnSmallTableR60->setEnabled(false);
        btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd452.png);}");
        btnSmallTableR45->setEnabled(false);
        btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd402.png);}");
        btnSmallTableR40->setEnabled(false);
        btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd362.png);}");
        btnSmallTableR36->setEnabled(false);

        SetInfoText("Wait for machine movement.");
        return;

    }

    mSmallPanelIndex += mSmallExpDir;

    for(int mIdx = mSmallPanelIndex ; mIdx >2  ; mIdx--)
        arrRenderSmall->at(mIdx)->setFillColor(arrRenderSmall->at(mIdx-1)->getFillColor());

    arrRenderSmall->at(2)->setFillColor(Qt::red);
    arrRenderSmall->at(3)->setFillColor(Qt::green);
    arrRenderSmall->at(mSmallPanelIndex)->setBeShow(true);

    SendKeySingle(NDT_KEY_IDX_SRL,(mSmallPanelIndex - 2) * mSmallAngleRotate);
    SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);

    btnSmallHeiDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx2.png);}");
    btnSmallHeiDown->setEnabled(false);
    btnSmallHeiUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs2.png);}");
    btnSmallHeiUp->setEnabled(false);
    btnSmallTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytfz2.png);}");
    btnSmallTableFz->setEnabled(false);
    btnSmallTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/xytzz2.png);}");
    btnSmallTableZz->setEnabled(false);

    btnSmallTableR60->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd602.png);}");
    btnSmallTableR60->setEnabled(false);
    btnSmallTableR45->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd452.png);}");
    btnSmallTableR45->setEnabled(false);
    btnSmallTableR40->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd402.png);}");
    btnSmallTableR40->setEnabled(false);
    btnSmallTableR36->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/zd362.png);}");
    btnSmallTableR36->setEnabled(false);

    SetInfoText("Wait for machine movement.");

    mExpDelayCtr = NDT_EXP_DELAY_SMALL;

}

void CMainBaseNdt10::OnFilmKeyDown(int key)
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(getPageIdx() == NDT_PAGE_STAND)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmPressed(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_TABLE)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmPressed(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_TUBE)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmPressed(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_SCAN_LONG)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmPressed(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_SCAN_ARM)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmPressed(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_SCAN_ROUND)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmPressed(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_SCAN_SMALL)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmPressed(keyEventBtn);
        return;
    }

}

void CMainBaseNdt10::OnFilmKeyUp(int key)
{
    if(keyEventBtn)
    {
        delete keyEventBtn;
        keyEventBtn = NULL;
    }

    if(getPageIdx() == NDT_PAGE_STAND)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_STAND,Qt::NoModifier);
        OnStandFilmReleased(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_TABLE)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_TABLE,Qt::NoModifier);
        OnTableFilmReleased(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_TUBE)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_TUBE,Qt::NoModifier);
        OnTubeFilmReleased(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_SCAN_LONG)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_LONG,Qt::NoModifier);
        OnSmartLongFilmReleased(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_SCAN_ARM)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_ARM,Qt::NoModifier);
        OnSmartArmFilmReleased(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_SCAN_ROUND)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_ROUND,Qt::NoModifier);
        OnSmartRoundFilmReleased(keyEventBtn);
        return;
    }

    if(getPageIdx() == NDT_PAGE_SCAN_SMALL)
    {
        keyEventBtn = new QKeyEvent(QEvent::KeyPress,key + NDT_KEY_BASE_SMALL,Qt::NoModifier);
        OnSmartSmallFilmReleased(keyEventBtn);
        return;
    }

}

int CMainBaseNdt10::getPageIdx()
{
    return m_pageIdx;
}
int CMainBaseNdt10::getPageIdxBuf()
{
    return m_pageIdxBuf;
}
void CMainBaseNdt10::setPageIdx(int mPage)
{
    m_pageIdxBuf = m_pageIdx;
    m_pageIdx = mPage;
}

void CMainBaseNdt10::mousePressEvent(QMouseEvent *event)
{
    //print left button down point.
    qDebug()<< event->pos().x() << event->pos().y();

    //非工作区域的位置按下，停止自动运行定时器
    tmAutoPosition->stop();

    //非工作区域的位置按下，发送停止命令
    SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
}
//title pressed ,switch page to setting page
void CMainBaseNdt10::OnBtnTitlePressed()
{
    if(arrBtnMenuScan.size() <= 0)
        return;

    if(sender() == arrBtnMenuScan.at(NDT_BTN_TITLE))
    {
        emit ViewChange(VIEW_PASSWORD);
    }
}

void CMainBaseNdt10::paintEvent(QPaintEvent *)
{

    DrawTable(getPageIdx());

    DrawMessageText();              //显示提示信息和警告信息

}


void CMainBaseNdt10::OnPopupShow(int )
{

}

bool CMainBaseNdt10::DrawRender(QList<CButtonRender*> & mRender)
{
    for(QList<CButtonRender*>::iterator ptr = mRender.begin();ptr != mRender.end(); ptr++)
    {

        if(!(*ptr)->BeShow())
            continue;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.setPen(QPen((*ptr)->getPenColor(), 2, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));

        painter.setBrush((*ptr)->getBrush());
        painter.drawPath((*ptr)->getPainterPath());

        painter.setBrush(Qt::NoBrush);
    }

    return true;
}

bool CMainBaseNdt10::DrawTable(int pageIdx)
{
    //draw in special page
    switch(pageIdx)
    {
    case NDT_PAGE_STAND:
    case NDT_PAGE_TABLE:
    case NDT_PAGE_TUBE:
        return false;
    case NDT_PAGE_SCAN_ROUND:
        DrawRender(*arrRenderRound);
        break;
    case NDT_PAGE_SCAN_SMALL:
        DrawRender(*arrRenderSmall);
        break;
    default:
        return true;
    }



    return true;
}
void CMainBaseNdt10::SetWarningText(QString warn)
{
    gStrWarnings = warn;
    mBrColor = Qt::red;

    update();
}
void CMainBaseNdt10::SetInfoText(QString info)
{
    gStrInfos = info;
    mBrColor = Qt::green;

    update();
}
bool CMainBaseNdt10::DrawMessageText()
{
    QPainter painter(this);

    QString drawText;
    int startXPos;
    painter.setBrushOrigin(0,0);

    painter.translate(SYS_WID(600.0),SYS_HEI(0.0));
    painter.rotate(90);

    QFont font;
    font.setPixelSize(SYS_HEI(24));
    painter.setFont(font);

    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    drawText = QApplication::translate("CMainBaseNdt10", gStrWarnings.toStdString().c_str());
    startXPos = SYS_HEI((600 - 24 * drawText.length() ) / 2);
    painter.drawText(startXPos, SYS_WID(185),  drawText);

    painter.setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    drawText = QApplication::translate("CMainBaseNdt10", gStrInfos.toStdString().c_str());
    startXPos = SYS_HEI((600 - 24 * drawText.length() ) / 2);
    painter.drawText(startXPos, SYS_WID(-100),  drawText);

    return true;
}
bool CMainBaseNdt10::CmdDataValidCheck(int idx,int key)
{

#ifndef QT_ARCH_ARM
    return true;
#endif

    //停止与忽略按键，直接返回true，允许发送
    if(key == NDT_MOTOR_STOP || key == NDT_MOTOR_IGNORE)
        return true;

    switch(idx)
    {
    case NDT_KEY_IDX_FID:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_FID))
        {
            SetWarningText("FID LimitMin!");
            qDebug()<<"FID LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_FID))
        {
            SetWarningText("FID LimitMax!");
            qDebug()<<"FID LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_SID:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_SID))
        {
            SetWarningText("SID LimitMin!");
            qDebug()<<"SID LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_SID))
        {
            SetWarningText("SID LimitMax!");
            qDebug()<<"SID LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_ANG:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_ANG))
        {
            SetWarningText("ANG LimitMin!");
            qDebug()<<"ANG LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_ANG))
        {
            SetWarningText("ANG LimitMax!");
            qDebug()<<"ANG LimitMax!";
            return false;
        }
        break;
    case  NDT_KEY_IDX_CEP:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_CEP))
        {
            SetWarningText("CEP LimitMin!");
            qDebug()<<"CEP LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_CEP))
        {
            SetWarningText("CEP LimitMax!");
            qDebug()<<"CEP LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_UID:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_UID))
        {
            SetWarningText("UID LimitMin!");
            qDebug()<<"UID LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_UID))
        {
            SetWarningText("UID LimitMax!");
            qDebug()<<"UID LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_DTA:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_DTA))
        {
            SetWarningText("DTA LimitMin!");
            qDebug()<<"DTA LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_DTA))
        {
            SetWarningText("DTA LimitMax!");
            qDebug()<<"DTA LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_ROL:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_ROL))
        {
            SetWarningText("ROL LimitMin!");
            qDebug()<<"ROL LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_ROL))
        {
            SetWarningText("ROL LimitMax!");
            qDebug()<<"ROL LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_SRL:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_SRL))
        {
            SetWarningText("SRL LimitMin!");
            qDebug()<<"SRL LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_SRL))
        {
            SetWarningText("SRL LimitMax!");
            qDebug()<<"SRL LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_RMV:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_RMV))
        {
            SetWarningText("RMV LimitMin!");
            qDebug()<<"RMV LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV))
        {
            SetWarningText("RMV LimitMax!");
            qDebug()<<"RMV LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_LMV:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV))
        {
            SetWarningText("LMV LimitMin!");
            qDebug()<<"LMV LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_LMV))
        {
            SetWarningText("LMV LimitMax!");
            qDebug()<<"LMV LimitMax!";
            return false;
        }
        break;
    case  NDT_KEY_IDX_HEI:
        if(key < g_motorMgr->getLimitMin(NDT_KEY_IDX_HEI))
        {
            SetWarningText("HEI LimitMin!");
            qDebug()<<"HEI LimitMin!";
            return false;
        }
        if(key > g_motorMgr->getLimitMax(NDT_KEY_IDX_HEI))
        {
            SetWarningText("HEI LimitMax!");
            qDebug()<<"HEI LimitMax!";
            return false;
        }
        break;
    case NDT_KEY_IDX_OUT:
        break;
    default:
        break;
    }

    return true;
}

//统一的安全检测函数添加机制
bool CMainBaseNdt10::CmdSafeFuncAdd(int idx,int key)
{
    switch(idx)
    {
    case NDT_KEY_IDX_FID:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID])
        {
            if(mech->isTubeDownSafe())
            {
                mech->AddAutoCheck("isTubeDownSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID])
        {
            if(mech->isTubeUpSafe())
            {
                mech->AddAutoCheck("isTubeUpSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case NDT_KEY_IDX_SID:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID])
        {
            if(mech->isTubeLeftSafe())
            {
                mech->AddAutoCheck("isTubeLeftSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID])
        {
            if(mech->isTubeRightSafe())
            {
                mech->AddAutoCheck("isTubeRightSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case NDT_KEY_IDX_ANG:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG])
        {
            if(mech->isTubeTurnFzSafe())
            {
                mech->AddAutoCheck("isTubeTurnFzSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG])
        {
            if(mech->isTubeTurnZzSafe())
            {
                mech->AddAutoCheck("isTubeTurnZzSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case  NDT_KEY_IDX_CEP:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP])
        {
            if(mech->isTubeForwordSafe())
            {
                mech->AddAutoCheck("isTubeForwordSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP])
        {
            if(mech->isTubeBackwordSafe())
            {
                mech->AddAutoCheck("isTubeBackwordSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case NDT_KEY_IDX_UID:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID])
        {
            if(mech->isPanelForwordSafe())
            {
                mech->AddAutoCheck("isPanelForwordSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID])
        {
            if(mech->isPanelBackwordSafe())
            {
                mech->AddAutoCheck("isPanelBackwordSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case NDT_KEY_IDX_DTA:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA])
        {
            if(mech->isPanelTurnHSafe())
            {
                mech->AddAutoCheck("isPanelTurnHSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA])
        {
            if(mech->isPanelTurnVSafe())
            {
                mech->AddAutoCheck("isPanelTurnVSafe");
                return true;
            }else
            {
                return false;
            }
        }

        gStrWarnings = "";  //清空错误消息
        return false;       //目标位置与实际位置相同，返回false，不执行动作
    case NDT_KEY_IDX_ROL:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ROL])
        {
            if(mech->isRoundFzSafe())
            {
                mech->AddAutoCheck("isRoundFzSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ROL])
        {
            if(mech->isRoundZzSafe())
            {
                mech->AddAutoCheck("isRoundZzSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case NDT_KEY_IDX_SRL:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SRL])
        {
            if(mech->isSmallFzSafe())
            {
                mech->AddAutoCheck("isSmallFzSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SRL])
        {
            if(mech->isSmallZzSafe())
            {
                mech->AddAutoCheck("isSmallZzSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case NDT_KEY_IDX_RMV:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV])
        {
            if(mech->isRoundTableLeftSafe())
            {
                mech->AddAutoCheck("isRoundTableLeftSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV])
        {
            if(mech->isRoundTableRightSafe())
            {
                mech->AddAutoCheck("isRoundTableRightSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case NDT_KEY_IDX_LMV:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV])
        {
            if(mech->isLongTableLeftSafe())
            {
                mech->AddAutoCheck("isLongTableLeftSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV])
        {
            if(mech->isLongTableRightSafe())
            {
                mech->AddAutoCheck("isLongTableRightSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case  NDT_KEY_IDX_HEI:
        if(key < g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI])
        {
            if(mech->isUarmDownSafe())
            {
                mech->AddAutoCheck("isUarmDownSafe");
                return true;
            }else
            {
                return false;
            }
        }

        if(key >  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI])
        {
            if(mech->isUarmUpSafe())
            {
                mech->AddAutoCheck("isUarmUpSafe");
                return true;
            }else
            {
                return false;
            }
        }
        break;
    case NDT_KEY_IDX_OUT:
        break;
    default:
        break;
    }
    return true;
}
bool CMainBaseNdt10::CmdSafeFuncDel(int idx)
{

    switch(idx)
    {
    case NDT_KEY_IDX_FID:
        mech->DelAutoCheck("isTubeDownSafe");
        mech->DelAutoCheck("isTubeUpSafe");
        break;
    case NDT_KEY_IDX_SID:
        mech->DelAutoCheck("isTubeLeftSafe");
        mech->DelAutoCheck("isTubeRightSafe");
        break;
    case NDT_KEY_IDX_ANG:
        mech->DelAutoCheck("isTubeTurnFzSafe");
        mech->DelAutoCheck("isTubeTurnZzSafe");
        break;
    case  NDT_KEY_IDX_CEP:
        mech->DelAutoCheck("isTubeForwordSafe");
        mech->DelAutoCheck("isTubeBackwordSafe");
        break;
    case NDT_KEY_IDX_UID:
        mech->DelAutoCheck("isPanelForwordSafe");
        mech->DelAutoCheck("isPanelBackwordSafe");
        break;
    case NDT_KEY_IDX_DTA:
        mech->DelAutoCheck("isPanelTurnHSafe");
        mech->DelAutoCheck("isPanelTurnVSafe");
        break;
    case NDT_KEY_IDX_ROL:
        mech->DelAutoCheck("isRoundFzSafe");
        mech->DelAutoCheck("isRoundZzSafe");
        break;
    case NDT_KEY_IDX_SRL:
        mech->DelAutoCheck("isSmallFzSafe");
        mech->DelAutoCheck("isSmallZzSafe");
        break;
    case NDT_KEY_IDX_RMV:
        mech->DelAutoCheck("isRoundTableLeftSafe");
        mech->DelAutoCheck("isRoundTableRightSafe");
        break;
    case NDT_KEY_IDX_LMV:
        mech->DelAutoCheck("isLongTableLeftSafe");
        mech->DelAutoCheck("isLongTableRightSafe");
        break;
    case  NDT_KEY_IDX_HEI:
        mech->DelAutoCheck("isUarmDownSafe");
        mech->DelAutoCheck("isUarmUpSafe");
        break;
    case NDT_KEY_IDX_OUT:
        break;
    default:
        break;
    }

    return true;
}

bool CMainBaseNdt10::CmdSafeFuncCheck(int idx ,int key)
{
    //停止与忽略按键，直接返回true，允许发送
    if(key == NDT_MOTOR_STOP)
    {

        return CmdSafeFuncDel(idx);
    }else
    {
        return CmdSafeFuncAdd(idx,key);
    }

}

void CMainBaseNdt10::SendKeySingle(short idx,short key)
{
    //check if the key index valid
    if(idx < NDT_KEY_IDX_MIN || idx > NDT_KEY_IDX_MAX)
    {
        qDebug()<<"LINE["<<__LINE__<<"]::FUNC["<<__FUNCTION__<<"]::FILE["<<__FILE__<<"]::key index invalid!";
        return ;
    }

    //如果是客户端，不发送串口消息
    if(   g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
        return;

    if(!CmdDataValidCheck(idx,key))
        return;

    if(!CmdSafeFuncCheck(idx,key))
        return;

    //cleare buffer to default state
    unsigned short keyBuf[NDT_KEY_BUF_SIZE];
    for(int mIdx = 0 ; mIdx < NDT_KEY_BUF_SIZE ; mIdx++)
        keyBuf[mIdx] = NDT_MOTOR_STOP;

    //set key value and send key
    keyBuf[idx] = key;

    g_taskComCtrl->CreateTask(CMD_NDT_RUN,keyBuf,NDT_KEY_BUF_SIZE);
}

void CMainBaseNdt10::SendKeyMulti(short idx0,short key0,short idx1,short key1)
{
    //check if the key index valid
    if(idx0 < NDT_KEY_IDX_MIN || idx0 > NDT_KEY_IDX_MAX)
    {
        qDebug()<<"LINE["<<__LINE__<<"]::FUNC["<<__FUNCTION__<<"]::FILE["<<__FILE__<<"]::key index invalid!";
        return ;
    }

    if(!CmdDataValidCheck(idx0,key0))
        return;

    CmdSafeFuncCheck(idx0,key0);

    //cleare buffer to default state
    unsigned short keyBuf[NDT_KEY_BUF_SIZE];
    for(int mIdx = 0 ; mIdx < NDT_KEY_BUF_SIZE ; mIdx++)
        keyBuf[mIdx] = NDT_MOTOR_IGNORE;

    keyBuf[idx0] = key0;

    if(idx1 >= NDT_KEY_IDX_MIN && idx1 <= NDT_KEY_IDX_MAX)
    {
        if(CmdDataValidCheck(idx1,key1))
        {
            CmdSafeFuncCheck(idx1,key1);
            keyBuf[idx1] = key1;
        }
    }

    g_taskComCtrl->CreateTask(CMD_NDT_RUN,keyBuf,NDT_KEY_BUF_SIZE);
}
void CMainBaseNdt10::SendKeyStop(short key0,short key1 ,short key2 ,short key3 ,short key4)
{

    CmdSafeFuncDel(key0);
    CmdSafeFuncDel(key1);
    CmdSafeFuncDel(key2);
    CmdSafeFuncDel(key3);
    CmdSafeFuncDel(key4);

}
void CMainBaseNdt10::showEvent(QShowEvent * event)
{

    tmNdtFresh->start();

    //告诉下位机，进入正常模式
    unsigned short buf[10];
    buf[0]=0;
    buf[1]=SYS_CMD_NORMAL;
    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);

    //判断是否显示网络图标
    if(g_netBase && g_dbsys.utility.mNetShow)
    {
        g_netBase->setParent(this);
        g_netBase->move(SYS_WID(636),SYS_HEI(5));
        g_netBase->setVisible(true);
        g_netBase->raise();
    }

    if( g_dbsys.utility.mShutdownShow )     //判断是否显示关机按钮
    {
        RsMgr->g_exitBase->setParent(this);
        RsMgr->g_exitBase->setVisible(true);
        RsMgr->g_exitBase->move(SYS_WID(726),SYS_HEI(500));
        RsMgr->g_exitBase->raise();
    }

    //mask
    return;

    CMainBase::showEvent(event);

}
void CMainBaseNdt10::hideEvent(QHideEvent * event)
{

    CMainBase::hideEvent(event);
}

void CMainBaseNdt10::OnViewChange(int view)
{
    switch(view)
    {
    case VIEW_GEN_CFG:                                  //发生器参数配置模式

        break;
    case VIEW_PASSWORD:                     //密码界面模式
        viewMotion->hide();                 //隐藏动画界面
        viewStatus->hide();                 //隐藏状态栏界面
        viewGen->hide();                    //隐藏发生器界面
        viewPopup->hide();                  //隐藏弹出框界面
        viewInfo->hide();                   //隐藏消息框界面

        emit ViewChange(VIEW_PASSWORD);
        break;
    case VIEW_CONFIRM:                      //密码到期模式
        viewMotion->hide();                 //隐藏动画界面
        viewInfo->hide();                   //隐藏消息框界面
        viewGen->hide();                    //隐藏发生器界面
        viewPopup->hide();                  //隐藏弹出框界面

        emit ViewChange(VIEW_CONFIRM);
        break;
    case VIEW_INSTALL:                      //密码到期模式
        viewMotion->hide();                 //隐藏动画界面
        viewInfo->hide();                   //隐藏消息框界面
        viewGen->hide();                    //隐藏发生器界面
        viewPopup->hide();                  //隐藏弹出框界面

        emit ViewChange(VIEW_INSTALL);
        break;
    case VIEW_GEN:                          //发生器显示模式
        break;
    case VIEW_MOTION:                       //动画显示模式
        viewMotion->show();                 //显示动画界面
        viewStatus->show();                 //显示状态栏界面
        viewGen->hide();                    //隐藏发生器界面
        viewPopup->hide();                  //隐藏弹出框界面
        m_iViewer = VIEW_MOTION;
        emit ViewChange(VIEW_MOTION);
        break;
    case VIEW_MAIN:                         //主界面显示模式
        m_iViewDir =   m_iViewDirBuf;

        g_mainFrame->setRotate(0);
        g_mainFrame->setSceneWidget(this);
        g_mainSetting->hide();

        emit ViewChange(VIEW_MAIN);

        break;
    default:
        break;
    }
}

void CMainBaseNdt10::OnTimerTubeFollow()
{
    int mTubeFollowDistance;
    if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_HEI_STOP_MASK )) == 0)
    {
        tmArmTubeFollow->stop();

        mTubeFollowDistance = g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI] - mTubeFollowStart;

        SendKeySingle(NDT_KEY_IDX_FID,g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] + mTubeFollowPatch + mTubeFollowDistance);
    }
}

void CMainBaseNdt10::OnAutoPositionTimer()
{

    //如果处于长台扫描模式，运行长台扫描到位进程
    if(AutoPositionIndex == NDT_AUTO_MODE_TABLE)
    {
        if(!isLongTablePos)
            OnLongTablePosition();          //如果没有处于长台扫描模式，执行进入长台扫描模式
        else
            OnLongTableRestart();           //如果已经处于长台扫描模式，执行将平板和长台复位

        LongVisableCtrl();                       //控制运动过程中的颜色更新

        return;
    }

    //如果处于长台扫描模式，运行长台扫描到位进程
    if(AutoPositionIndex == NDT_AUTO_MODE_ARM)
    {
        if(!isArmTablePos)
            OnArmTablePosition();          //如果没有处于长台扫描模式，执行进入长台扫描模式
        else
            OnArmTableRestart();           //如果已经处于长台扫描模式，执行将平板和长台复位

        ArmVisableCtrl();                       //控制运动过程中的颜色更新

        return;
    }

    if(AutoPositionIndex == NDT_AUTO_MODE_ROUND_FLAT)
    {
        RoundVisableCtrl();

        if(!isRoundTablePos)
        {
            OnRoundTablePositionFlat();
        }else
        {
            OnRoundTableRestart();
        }

        return;
    }

    if(AutoPositionIndex == NDT_AUTO_MODE_ROUND_ANG)
    {
        RoundVisableCtrl();

        if(!isRoundTablePos)
        {
            OnRoundTablePositionAngle();
        }else
        {
            OnRoundTableRestart();
        }

        return;
    }

    if(AutoPositionIndex == NDT_AUTO_MODE_SMALL)
    {
        SmallVisableCtrl();

        if(!isSmallTablePos)
            OnSmallTablePosition();
        else
            OnSmallTableRestart();

        return;
    }

}


//长台扫描到位控制
//按解耦方式运行，不添加运动保护
void CMainBaseNdt10::OnLongTablePosition()
{
    int aValue1,aValue2,aValue3,aValue4;

    switch(statLongTableAuto)
    {
    case NDT_AUTO_STAT00:                                                                                                        //发送球管到安全位置的指令
        SendKeySingle(NDT_KEY_IDX_FID,g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));
        statLongTableAuto = NDT_AUTO_STAT01;
        SetInfoText("Move tube up to safe position.");
        break;
    case NDT_AUTO_STAT01:                                                                                              //等待球管到位
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_FID_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));

            if(mMoveReadyMask || (aValue1 < 20))                                                    //
            {
                statLongTableAuto = NDT_AUTO_STAT02;
                SendKeyMulti(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            }
        }
        break;
    case NDT_AUTO_STAT02:                                                                                                     //发送长台到安全位置的指令
        SendKeySingle(NDT_KEY_IDX_LMV,g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
        SendKeyMulti(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));

        statLongTableAuto = NDT_AUTO_STAT03;
        SetInfoText("Move two table to safe position.");
        break;
    case NDT_AUTO_STAT03:                                                                           //    等待大圆台//长台到位
        SetInfoText("Wait for two table stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_RMV_STOP_MASK | NDT_LMV_STOP_MASK)) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV] - g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20) )                                                   //
            {
                statLongTableAuto = NDT_AUTO_STAT06;
                SendKeyStop(NDT_KEY_IDX_LMV,NDT_KEY_IDX_RMV);
            }
        }
        break;
    case NDT_AUTO_STAT06:                                                                                               //    发送横臂到位指令
        SetInfoText("Move panel to imaging position.");
        SendKeySingle(NDT_KEY_IDX_HEI,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_HEI));
        SendKeyMulti(NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_UID),
                     NDT_KEY_IDX_DTA,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_DTA));
        statLongTableAuto = NDT_AUTO_STAT07;

        break;
    case NDT_AUTO_STAT07:                                                                                           //    等待横臂运行到位
        SetInfoText("Wait for flat panel stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_STAND_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_HEI));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_UID));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_DTA));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 && aValue3 <= 20) )                                                   //
            {
                statLongTableAuto = NDT_AUTO_STAT08;

                SendKeyStop(NDT_KEY_IDX_HEI,NDT_KEY_IDX_UID,NDT_KEY_IDX_DTA);
            }
        }
        break;
    case NDT_AUTO_STAT08:                                                                                            //发送长台到位命令
        SendKeySingle(NDT_KEY_IDX_LMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_LMV));
        statLongTableAuto = NDT_AUTO_STAT09;
        SetInfoText("Move long table to imaging position.");
        break;
    case NDT_AUTO_STAT09:                                                                                 //等待长台到位
        SetInfoText("Wait for long table stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_LMV_STOP_MASK) == 0)
        {
            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_LMV));

            if(mMoveReadyMask || (aValue1 <= 20 ) )                                                   //
            {
                statLongTableAuto = NDT_AUTO_STAT10;
                SendKeyMulti(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);
            }
        }
        break;
    case NDT_AUTO_STAT10:                                                                                             //发送球管到位命令
        SendKeyMulti(NDT_KEY_IDX_FID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_FID),
                     NDT_KEY_IDX_SID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_SID));
        SendKeyMulti(NDT_KEY_IDX_ANG,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_ANG),
                     NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_CEP));

        statLongTableAuto = NDT_AUTO_STAT11;
        SetInfoText("Move tube to imaging position.");
        break;
    case NDT_AUTO_STAT11:                                                                                    //等待球管到位
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_TUBE_STOP_MASK) == 0)
        {
            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_FID));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_SID));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_ANG));
            aValue4 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_CEP));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 && aValue3 <= 20  && aValue4 <= 20 ) )                                                   //
            {
                statLongTableAuto = NDT_AUTO_STAT00;

                SendKeyStop(NDT_KEY_IDX_FID,NDT_KEY_IDX_SID,NDT_KEY_IDX_ANG,NDT_KEY_IDX_CEP);

                tmAutoPosition->stop();
                isLongTablePos = true;          //标记进入长台扫描模式
                mPanelBorderType = NDT_PANEL_BORDER_CENTOR;

                SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);

                for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)           //所有背景颜色清空
                    pBtnLongCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

                statLongTableStepCounter = 0;
                pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(2));           //需要曝光的位置值为黄色

                for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)                                   //重新居中
                {
                    QRect mRect = pBtnLongCentor.at(mIdx)->geometry();
                    mRect.moveLeft(SYS_WID(510));
                    pBtnLongCentor.at(mIdx)->setGeometry(mRect);
                }

                //允许按钮控制
                btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh1.png);}");
                btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
                btnLongTableLeft->setEnabled(false);
                btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
                btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy1.png);}");

                SetInfoText("Long table scan mode.");
            }
        }
        break;

    default:
        SendKeySingle(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
        SetWarningText("OnLongTablePosition state error!");
        break;
    }

}


//仍然处于长台扫描模式，只使长台和平板到位
void CMainBaseNdt10::OnLongTableRestart()
{
    int mIdx;
    int aValue1,aValue2,aValue3;

    switch(statLongTableAuto)
    {
    case NDT_AUTO_STAT00:
        SendKeySingle(NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_CEP));
        SendKeyMulti(NDT_KEY_IDX_LMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_LMV),
                     NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_UID));
        SendKeyMulti(NDT_KEY_IDX_ANG,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_ANG),
                     NDT_KEY_IDX_SID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_SID));
        statLongTableAuto = NDT_AUTO_STAT01;

        SetInfoText("Wait for machine movement.");
        break;
    case NDT_AUTO_STAT01:
        if( (g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_LMV_STOP_MASK | NDT_UID_STOP_MASK) )== 0)
        {
            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_CEP));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_LMV));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_TABLE,NDT_KEY_IDX_UID));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 && aValue3 <= 20  ) )                                                   //
            {

                statLongTableAuto = NDT_AUTO_STAT00;

                SendKeyStop(NDT_KEY_IDX_CEP,NDT_KEY_IDX_LMV,NDT_KEY_IDX_UID);

                isLongTablePos = true;          //标记进入长台扫描模式
                tmAutoPosition->stop();

                for(mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)           //所有背景颜色清空
                    pBtnLongCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

                statLongTableStepCounter = 0;
                pBtnLongCentor.at(statLongTableStepCounter)->setStyleSheet(*listPanelColor.at(2));           //需要曝光的位置值为黄色

                if( mPanelBorderType != NDT_PANEL_BORDER_CENTOR)
                {
                    for(int mIdx = 0 ; mIdx < pBtnLongCentor.size() ; mIdx++)                                   //重新居中
                    {
                        QRect mRect = pBtnLongCentor.at(mIdx)->geometry();
                        mRect.moveLeft(SYS_WID(510));
                        pBtnLongCentor.at(mIdx)->setGeometry(mRect);
                    }
                    mPanelBorderType = NDT_PANEL_BORDER_CENTOR;
                }

                SetInfoText("Long table scan mode.");
            }
        }
        break;
    default:
        SendKeySingle(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
        SetWarningText("OnLongTableRestart state error!");
        break;
    }
}


//长台扫描到位控制
//按解耦方式运行，不添加运动保护
void CMainBaseNdt10::OnArmTablePosition()
{
    int aValue1,aValue2,aValue3;

    switch(statArmTableAuto)
    {
    case NDT_AUTO_STAT00:                                                                                                        //发送球管到安全位置的指令
        SendKeySingle(NDT_KEY_IDX_FID,g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));
        statArmTableAuto = NDT_AUTO_STAT01;
        SetInfoText("Move tube up to safe position.");
        break;
    case NDT_AUTO_STAT01:                                                                                              //等待球管到位
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_FID_STOP_MASK) == 0)
        {
            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));

            if(mMoveReadyMask || (aValue1 < 20))                                                    //
            {
                statArmTableAuto = NDT_AUTO_STAT02;
                SendKeyMulti(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            }
        }
        break;
    case NDT_AUTO_STAT02:                                                                                                     //发送长台到安全位置的指令

        SendKeySingle(NDT_KEY_IDX_LMV,g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
        SendKeyMulti(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));
        statArmTableAuto = NDT_AUTO_STAT03;
        SetInfoText("Move two table to safe position.");
        break;
    case NDT_AUTO_STAT03:                                                                           //    等待大圆台//长台到位
        SetInfoText("Wait for two table stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_RMV_STOP_MASK | NDT_LMV_STOP_MASK)) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV] - g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20) )                                                   //
            {
                statArmTableAuto = NDT_AUTO_STAT04;
                SendKeyStop(NDT_KEY_IDX_LMV,NDT_KEY_IDX_RMV);
            }
        }
        break;
    case NDT_AUTO_STAT04:
        SendKeySingle(NDT_KEY_IDX_SID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_SID));
        SendKeyMulti(NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_CEP));
        statArmTableAuto = NDT_AUTO_STAT05;
        SetInfoText("Move tube to imaging position.");
        break;
    case NDT_AUTO_STAT05:
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_TUBE_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_SID));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_CEP));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 ) )
            {
                statArmTableAuto = NDT_AUTO_STAT06;
                SendKeyStop(NDT_KEY_IDX_SID,NDT_KEY_IDX_CEP);
            }
        }
        break;
    case NDT_AUTO_STAT06:                                                                                               //    发送横臂到位指令
        SendKeySingle(NDT_KEY_IDX_HEI,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_HEI));
        SendKeyMulti(NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_UID),
                     NDT_KEY_IDX_DTA,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_DTA));
        statArmTableAuto = NDT_AUTO_STAT07;
        SetInfoText("Move panel to imaging position.");
        break;
    case NDT_AUTO_STAT07:                                                                                           //    等待横臂运行到位
        SetInfoText("Wait for flat panel stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_STAND_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_HEI));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_UID));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_DTA));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 && aValue3 <= 20) )                                                   //
            {
                statArmTableAuto = NDT_AUTO_STAT08;

                SendKeyStop(NDT_KEY_IDX_HEI,NDT_KEY_IDX_UID,NDT_KEY_IDX_DTA);
            }
        }
        break;
    case NDT_AUTO_STAT08:                                                                                            //发送长台到位命令
        SendKeySingle(NDT_KEY_IDX_LMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_LMV));
        statArmTableAuto = NDT_AUTO_STAT09;
        SetInfoText("Move long table to imaging position.");
        break;
    case NDT_AUTO_STAT09:                                                                                 //等待长台到位
        SetInfoText("Wait for long table stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_LMV_STOP_MASK) == 0)
        {
            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_LMV));

            if(mMoveReadyMask || (aValue1 <= 20) )                                                   //
            {
                statArmTableAuto = NDT_AUTO_STAT10;

                SendKeyMulti(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
            }
        }
        break;
    case NDT_AUTO_STAT10:                                                                                             //发送球管到位命令
        SendKeySingle(NDT_KEY_IDX_FID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_FID));
        SendKeyMulti(NDT_KEY_IDX_ANG,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_ANG));

        statArmTableAuto = NDT_AUTO_STAT11;
        SetInfoText("Move tube to imaging position.");
        break;
    case NDT_AUTO_STAT11:                                                                                    //等待球管到位
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_TUBE_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_FID));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_ANG));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20) )
            {
                statArmTableAuto = NDT_AUTO_STAT00;
                SendKeyStop(NDT_KEY_IDX_FID,NDT_KEY_IDX_ANG);

                tmAutoPosition->stop();
                isArmTablePos = true;          //标记进入长台扫描模式

                SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);
                statArmTableStepCounter = 0;
                pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(2));

                //允许按钮控制
                btnArmPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
                btnArmPanelBack->setEnabled(false);
                btnArmPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq1.png);}");
                btnArmPanelFront->setEnabled(true);
                btnArmPanelUp->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxs1.png);}");
                btnArmPanelUp->setEnabled(true);
                btnArmPanelDown->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxx1.png);}");
                btnArmPanelDown->setEnabled(true);

                SetInfoText("Enter ARM scan mode.");
            }
        }
        break;

    default:
        qDebug()<<"Error state!";
        break;
    }

}

//仍然处于长台扫描模式，只使长台和平板到位
void CMainBaseNdt10::OnArmTableRestart()
{
    int mIdx;

    int aValue1,aValue2,aValue3;

    switch(statArmTableAuto)
    {
    case NDT_AUTO_STAT00:
        SendKeySingle(NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_CEP));
        SendKeyMulti(NDT_KEY_IDX_LMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_LMV),
                     NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_UID));
        SendKeyMulti(NDT_KEY_IDX_LMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_LMV),
                     NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_UID));

        statArmTableAuto = NDT_AUTO_STAT09;

        SetInfoText("Wait for machine movement.");
        break;
    case NDT_AUTO_STAT09:
        if( (g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_LMV_STOP_MASK | NDT_UID_STOP_MASK) )== 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_CEP));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_LMV));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ARM,NDT_KEY_IDX_UID));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 && aValue3 <= 20 ) )
            {
                statArmTableAuto = NDT_AUTO_STAT00;

                SendKeyStop(NDT_KEY_IDX_CEP,NDT_KEY_IDX_LMV,NDT_KEY_IDX_UID);

                isArmTablePos = true;          //标记进入长台扫描模式
                tmAutoPosition->stop();

                for(mIdx = 0 ; mIdx < pBtnArmCentor.size() ; mIdx++)           //所有背景颜色清空
                    pBtnArmCentor.at(mIdx)->setStyleSheet("background-color:lightGray;");

                //需要曝光的位置值为黄色
                statArmTableStepCounter = 0;
                pBtnArmCentor.at(statArmTableStepCounter)->setStyleSheet(*listPanelColor.at(2));

                for(int mIdx = 0 ; mIdx < pBtnArmCentor.size() ; mIdx++)
                {
                    QRect mRect = pBtnArmCentor.at(mIdx)->geometry();
                    mRect.moveLeft(SYS_WID(510));
                    pBtnArmCentor.at(mIdx)->setGeometry(mRect);
                }

                SetInfoText("Enter ARM scan mode.");
            }
        }
        break;
    default:
        SendKeySingle(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
        break;
    }
}
//大圆台扫描到位控制
void CMainBaseNdt10::OnRoundTablePositionFlat()
{
    int aValue1,aValue2,aValue3,aValue4,aValue5;

    switch(statRoundTableAuto)
    {
    case NDT_AUTO_STAT00:       //    发送球管到安全位置的指令
        SendKeySingle(NDT_KEY_IDX_FID,g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));
        statRoundTableAuto = NDT_AUTO_STAT01;
        SetInfoText("Move tube up to safe position.");
        break;
    case NDT_AUTO_STAT01:   //    等待球管到位
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_FID_STOP_MASK) == 0)
        {
            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));

            if(mMoveReadyMask || (aValue1 <= 20  ) )
            {
                statRoundTableAuto = NDT_AUTO_STAT02;

                SendKeyMulti(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            }
        }
        break;
    case NDT_AUTO_STAT02:     //    发送长台到安全位置的指令
        SendKeySingle(NDT_KEY_IDX_LMV,g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
        SendKeyMulti(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV),
                     NDT_KEY_IDX_ROL,0);
        statRoundTableAuto = NDT_AUTO_STAT03;
        SetInfoText("Move two table to safe position.");
        break;
    case NDT_AUTO_STAT03:          //    等待大圆台//长台到位
        SetInfoText("Wait for two table stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_RMV_STOP_MASK | NDT_LMV_STOP_MASK)) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
            aValue2 =  qAbs((short)(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ROL]) - 0);
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV] - g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));

            if(mMoveReadyMask || (aValue1 <= 20  && aValue2 <= 20 && aValue3 <= 20 ) )
            {
                statRoundTableAuto = NDT_AUTO_STAT06;

                SendKeyStop(NDT_KEY_IDX_LMV,NDT_KEY_IDX_ROL,NDT_KEY_IDX_RMV);

            }
        }
        break;
    case NDT_AUTO_STAT06:           //    发送横臂到位指令
        SendKeySingle(NDT_KEY_IDX_HEI,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_HEI));
        SendKeyMulti(NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_UID),
                     NDT_KEY_IDX_DTA,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_DTA));
        statRoundTableAuto = NDT_AUTO_STAT07;
        SetInfoText("Move panel to imaging position.");
        break;
    case NDT_AUTO_STAT07:           //    等待横臂运行到位
        SetInfoText("Wait for flat panel stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_STAND_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI] -  g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_HEI));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_UID));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_DTA));

            if(mMoveReadyMask || (aValue1 <= 20  && aValue2 <= 20 && aValue3 <= 20) )
            {
                statRoundTableAuto = NDT_AUTO_STAT08;

                SendKeyStop(NDT_KEY_IDX_HEI,NDT_KEY_IDX_UID,NDT_KEY_IDX_DTA);

            }
        }
        break;
    case NDT_AUTO_STAT08:
        SetInfoText("Move table and tube to imaging position.");
        SendKeySingle(NDT_KEY_IDX_RMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_RMV));
        SendKeyMulti(NDT_KEY_IDX_FID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_FID),
                     NDT_KEY_IDX_SID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_SID));
        SendKeyMulti(NDT_KEY_IDX_ANG,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_ANG),
                     NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_CEP));


        statRoundTableAuto = NDT_AUTO_STAT11;
        break;
    case NDT_AUTO_STAT11:
        SetInfoText("Wait for table and tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_TUBE_STOP_MASK | NDT_RMV_STOP_MASK)) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV] -  g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_RMV));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_FID));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_SID));
            aValue4 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_ANG));
            aValue5 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_FLAT,NDT_KEY_IDX_CEP));

            if(mMoveReadyMask || (aValue1 <= 20  && aValue2 <= 20 && aValue3 <= 20 && aValue4 <= 20 && aValue5 <= 20) )
            {
                statRoundTableAuto = NDT_AUTO_STAT00;

                SendKeyStop(NDT_KEY_IDX_RMV,NDT_KEY_IDX_FID,NDT_KEY_IDX_SID,NDT_KEY_IDX_ANG,NDT_KEY_IDX_CEP);

                isRoundTablePos = true;
                isSmallTablePos = false;
                isArmTablePos = false;
                isLongTablePos = false;

                //禁止按钮控制
                btnRoundTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz1.png);}");
                btnRoundTableLeft->setEnabled(true);
                btnRoundTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy1.png);}");
                btnRoundTableRight->setEnabled(true);
                btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz1.png);}");
                btnRoundTableZz->setEnabled(true);
                btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz1.png);}");
                btnRoundTableFz->setEnabled(true);

                tmAutoPosition->stop();
                SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);
                SendKeyMulti(NDT_KEY_IDX_ROL,0);

                mRoundPanelIndex = 2;
                for( int mIdx = 3; mIdx < arrRenderRound->size() ; mIdx ++)
                    arrRenderRound->at(mIdx)->setBeShow(false);

                arrRenderRound->at(mRoundPanelIndex)->setPenColor(Qt::yellow);
                arrRenderRound->at(mRoundPanelIndex)->setFillColor(Qt::yellow);
                arrRenderRound->at(mRoundPanelIndex)->setBeShow(true);

                SetInfoText("Enter LRound scan mode.");
            }
        }
        break;

    default:
        gStrWarnings = "OnRoundTablePosition error";
        SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
        break;
    }
}

//大圆台扫描到位控制
void CMainBaseNdt10::OnRoundTablePositionAngle()
{
    int aValue1,aValue2,aValue3,aValue4;

    switch(statRoundTableAuto)
    {
    case NDT_AUTO_STAT00:       //    发送球管到安全位置的指令
        SendKeySingle(NDT_KEY_IDX_FID,g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));
        statRoundTableAuto = NDT_AUTO_STAT01;
        SetInfoText("Move tube up to safe position.");
        break;
    case NDT_AUTO_STAT01:   //    等待球管到位
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_FID_STOP_MASK) == 0)
        {
            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] -  g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));

            if(mMoveReadyMask || (aValue1 <= 20 ) )
            {
                statRoundTableAuto = NDT_AUTO_STAT02;

                SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            }
        }
        break;
    case NDT_AUTO_STAT02:     //    发送长台到安全位置的指令

        SendKeySingle(NDT_KEY_IDX_LMV,g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
        SendKeyMulti(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV),
                     NDT_KEY_IDX_ROL,0);

        statRoundTableAuto = NDT_AUTO_STAT03;
        SetInfoText("Move two table to safe position.");
        break;
    case NDT_AUTO_STAT03:          //    等待大圆台//长台到位
        SetInfoText("Wait for two table stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_RMV_STOP_MASK | NDT_LMV_STOP_MASK)) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV] - g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));
            aValue3 =  g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ROL];

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20  && aValue3 <= 20) )                                                   //
            {

                SendKeyStop(NDT_KEY_IDX_LMV,NDT_KEY_IDX_RMV,NDT_KEY_IDX_ROL);

                statRoundTableAuto = NDT_AUTO_STAT04;
            }
        }
        break;
    case NDT_AUTO_STAT04:

        SendKeySingle(NDT_KEY_IDX_HEI,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_HEI));
        SendKeyMulti(NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_UID),
                     NDT_KEY_IDX_DTA,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_DTA));

        statRoundTableAuto = NDT_AUTO_STAT05;
        SetInfoText("Move panel to imaging position.");
        break;
    case NDT_AUTO_STAT05:                                                                                           //    等待横臂运行到位
        SetInfoText("Wait for flat panel stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_STAND_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_HEI));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_UID));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_DTA));
            //aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA] );

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 && aValue3 <= 20) )                                                   //
            {
                statRoundTableAuto = NDT_AUTO_STAT06;

                SendKeyStop(NDT_KEY_IDX_HEI,NDT_KEY_IDX_UID,NDT_KEY_IDX_DTA);
            }
        }
        break;
    case NDT_AUTO_STAT06:                                                                                             //发送球管到位命令
        SendKeySingle(NDT_KEY_IDX_FID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_FID));
        SendKeyMulti(NDT_KEY_IDX_SID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_SID));
        SendKeyMulti(NDT_KEY_IDX_ANG,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_ANG),
                     NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_CEP));

        statRoundTableAuto = NDT_AUTO_STAT07;
        SetInfoText("Move tube to imaging position.");
        break;
    case NDT_AUTO_STAT07:
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_TUBE_STOP_MASK | NDT_RMV_STOP_MASK)) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_FID));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_SID));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_ANG));
            aValue4 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_CEP));

            if(mMoveReadyMask || (aValue1 <= 20  && aValue2 <= 20 && aValue3 <= 20 && aValue4 <= 20 ) )
            {
                SendKeyStop(NDT_KEY_IDX_FID,NDT_KEY_IDX_SID,NDT_KEY_IDX_ANG,NDT_KEY_IDX_CEP);

                statRoundTableAuto = NDT_AUTO_STAT08;
            }
        }
        break;
    case NDT_AUTO_STAT08:
        SendKeyMulti(NDT_KEY_IDX_RMV,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_RMV));
        SetInfoText("Wait for two table stop.");
        statRoundTableAuto = NDT_AUTO_STAT11;
        break;
    case NDT_AUTO_STAT11:
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_RMV_STOP_MASK)) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_ROUND_ANG,NDT_KEY_IDX_RMV));

            if(mMoveReadyMask || (aValue1 <= 20 ) )
            {
                statRoundTableAuto = NDT_AUTO_STAT00;

                SendKeyMulti(NDT_KEY_IDX_RMV,NDT_MOTOR_STOP);

                isRoundTablePos = true;
                isSmallTablePos = false;
                isArmTablePos = false;
                isLongTablePos = false;

                //禁止按钮控制
                btnRoundTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxz1.png);}");
                btnRoundTableLeft->setEnabled(true);
                btnRoundTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytxy1.png);}");
                btnRoundTableRight->setEnabled(true);
                btnRoundTableZz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytzz1.png);}");
                btnRoundTableZz->setEnabled(true);
                btnRoundTableFz->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/dytfz1.png);}");
                btnRoundTableFz->setEnabled(true);

                tmAutoPosition->stop();
                SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);
                SendKeyMulti(NDT_KEY_IDX_ROL,0);

                for( int mIdx = 3; mIdx < arrRenderRound->size() ; mIdx ++)
                    arrRenderRound->at(mIdx)->setBeShow(false);

                mRoundPanelIndex = 2;
                arrRenderRound->at(mRoundPanelIndex)->setPenColor(Qt::yellow);
                arrRenderRound->at(mRoundPanelIndex)->setFillColor(Qt::yellow);
                arrRenderRound->at(mRoundPanelIndex)->setBeShow(true);

                SetInfoText("Enter LRound angle mode.");
            }
        }
        break;
    default:
        gStrWarnings = "OnRoundTablePosition error";
        SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
        break;
    }
}
// 大圆台扫描归零，主要平板角度归零
void CMainBaseNdt10::OnRoundTableRestart()
{
    int aValue1;

    switch(statRoundTableAuto)
    {
    case NDT_AUTO_STAT00:       //    发送球管到安全位置的指令

        SendKeySingle(NDT_KEY_IDX_ROL,0);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);
        statRoundTableAuto = NDT_AUTO_STAT01;

        SetInfoText("Wait for machine movement.");

        break;
    case NDT_AUTO_STAT01:   //    等待球管到位
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & ( NDT_ROL_STOP_MASK )) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ROL] - 0);

            if(mMoveReadyMask || (aValue1 <= 20  ) )
            {
                tmAutoPosition->stop();

                statRoundTableAuto = NDT_AUTO_STAT00;

                isRoundTablePos = true;
                isLongTablePos = false;
                isSmallTablePos = false;
                isArmTablePos = false;

                btnLongPanelBack->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxh2.png);}");
                btnLongPanelFront->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/pbxq2.png);}");
                btnLongTableLeft->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxz2.png);}");
                btnLongTableRight->setStyleSheet("QPushButton{border-image: url(:/QRes/8090/png00/ctxy2.png);}");

                for( int mIdx = 3; mIdx < arrRenderRound->size() ; mIdx ++)
                    arrRenderRound->at(mIdx)->setBeShow(false);

                mRoundPanelIndex = 2;
                arrRenderRound->at(mRoundPanelIndex)->setPenColor(Qt::yellow);
                arrRenderRound->at(mRoundPanelIndex)->setFillColor(Qt::yellow);
                arrRenderRound->at(mRoundPanelIndex)->setBeShow(true);

                SendKeySingle(NDT_KEY_IDX_ROL,NDT_MOTOR_STOP);
                SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);

                SetInfoText("Ready for image capture.");
            }
        }
        break;
    default:
        break;
    }
}

//小圆台扫描到位控制
void CMainBaseNdt10::OnSmallTablePosition()
{
    int aValue1,aValue2,aValue3;

    switch(statSmallTableAuto)
    {
    case NDT_AUTO_STAT00:       //    发送球管到安全位置的指令
        SendKeySingle(NDT_KEY_IDX_FID,g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));
        statSmallTableAuto = NDT_AUTO_STAT01;
        SetInfoText("Move tube up to safe position.");
        break;

    case NDT_AUTO_STAT01:   //    等待球管到位
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_FID_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_motorMgr->getLimitMax(NDT_KEY_IDX_FID));

            if(mMoveReadyMask || (aValue1 <= 20 ) )                                                   //
            {
                statSmallTableAuto = NDT_AUTO_STAT02;

                SendKeyMulti(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            }
        }

        break;
    case NDT_AUTO_STAT02:     //    发送长台到安全位置的指令
        SendKeySingle(NDT_KEY_IDX_LMV,g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
        SendKeyMulti(NDT_KEY_IDX_RMV,g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV) ,
                     NDT_KEY_IDX_SRL,0);

        statSmallTableAuto = NDT_AUTO_STAT03;
        SetInfoText("Move two table to safe position.");
        break;
    case NDT_AUTO_STAT03:
        SetInfoText("Wait for two table stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & (NDT_SRL_STOP_MASK | NDT_RMV_STOP_MASK | NDT_LMV_STOP_MASK )) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_LMV] - g_motorMgr->getLimitMin(NDT_KEY_IDX_LMV));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_RMV] - g_motorMgr->getLimitMax(NDT_KEY_IDX_RMV));
            aValue3 =  qAbs((short)(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SRL]) - 0);

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 && aValue3 <= 20 ) )                                                   //
            {
                statSmallTableAuto = NDT_AUTO_STAT04;

                SendKeyStop(NDT_KEY_IDX_LMV,NDT_KEY_IDX_RMV,NDT_KEY_IDX_SRL);
            }
        }
        break;
    case NDT_AUTO_STAT04:
        SendKeySingle(NDT_KEY_IDX_CEP,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_CEP));
        SendKeyMulti(NDT_KEY_IDX_SID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_SID));
        statSmallTableAuto = NDT_AUTO_STAT05;
        SetInfoText("Move tube up to safe position.");
        break;
    case NDT_AUTO_STAT05:
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_TUBE_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_CEP] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_CEP));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_SID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_SID));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 ) )                                                   //
            {
                statSmallTableAuto = NDT_AUTO_STAT06;

                SendKeyStop(NDT_KEY_IDX_CEP,NDT_KEY_IDX_SID);
            }
        }
        break;
    case NDT_AUTO_STAT06:           //    发送横臂到位指令
        SendKeySingle(NDT_KEY_IDX_HEI,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_HEI));
        SendKeyMulti(NDT_KEY_IDX_UID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_UID),
                     NDT_KEY_IDX_DTA,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_DTA));

        statSmallTableAuto = NDT_AUTO_STAT07;
        SetInfoText("Move panel to imaging position.");
        break;

    case NDT_AUTO_STAT07:           //    等待横臂运行到位
        SetInfoText("Wait for flat panel stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_STAND_STOP_MASK) == 0)
        {

            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_HEI] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_HEI));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_UID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_UID));
            aValue3 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_DTA] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_DTA));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 && aValue3 <= 20) )                                                   //
            {
                statSmallTableAuto = NDT_AUTO_STAT08;

                SendKeyStop(NDT_KEY_IDX_HEI,NDT_KEY_IDX_UID,NDT_KEY_IDX_DTA);

            }
        }

        break;
    case NDT_AUTO_STAT08:
        SendKeySingle(NDT_KEY_IDX_FID,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_FID));
        SendKeyMulti(NDT_KEY_IDX_ANG,g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_ANG));
        statSmallTableAuto = NDT_AUTO_STAT11;
        SetInfoText("Move tube to imaging position.");
        break;
    case NDT_AUTO_STAT11:
        SetInfoText("Wait for tube stop.");
        if((g_systemDb->g_iArrNdtState[NDT_STAT_STS] & NDT_TUBE_STOP_MASK) == 0)
        {
            aValue1 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_FID] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_FID));
            aValue2 =  qAbs(g_systemDb->g_iArrNdtState[NDT_KEY_IDX_ANG] - g_systemDb->NdtSmartDataGet(NDT_AUTO_MODE_SMALL,NDT_KEY_IDX_ANG));

            if(mMoveReadyMask || (aValue1 <= 20 && aValue2 <= 20 ) )                                                   //
            {
                tmAutoPosition->stop();

                statSmallTableAuto = NDT_AUTO_STAT00;
                isSmallTablePos = true;

                SendKeyStop(NDT_KEY_IDX_FID,NDT_KEY_IDX_ANG);
                SendKeySingle(NDT_KEY_IDX_OUT,NDT_XRAY_OPEN);
                SendKeyMulti(NDT_KEY_IDX_SRL,0);

                mSmallPanelIndex = 2;
                arrRenderSmall->at(mSmallPanelIndex)->setBeShow(true);

                for( int mIdx = 3; mIdx < arrRenderSmall->size() ; mIdx ++)
                    arrRenderSmall->at(mIdx)->setBeShow(false);

                SetInfoText("Enter SRound scan mode.");
            }
        }
        break;

    default:
        break;
    }
}
void CMainBaseNdt10::OnSmallTableRestart()
{

    switch(statSmallTableAuto)
    {
    case NDT_AUTO_STAT00:
        SendKeySingle(NDT_KEY_IDX_SRL,0);
        SendKeyMulti(NDT_KEY_IDX_OUT,NDT_XRAY_CLOSE);
        statSmallTableAuto = NDT_AUTO_STAT01;

        SetInfoText("Wait for machine movement.");
        break;
    case NDT_AUTO_STAT01:
        if( (g_systemDb->g_iArrNdtState[NDT_STAT_STS] &  NDT_SRL_STOP_MASK )== 0)
        {
            tmAutoPosition->stop();

            statSmallTableAuto = NDT_AUTO_STAT00;
            isSmallTablePos = true;          //标记进入长台扫描模式
            mSmallPanelIndex = 2;

            for( int mIdx = 3; mIdx < arrRenderSmall->size() ; mIdx ++)
                arrRenderSmall->at(mIdx)->setBeShow(false);

            SetInfoText("Enter SRound scan mode.");
        }
        break;
    default:
        SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
        break;
    }
}



