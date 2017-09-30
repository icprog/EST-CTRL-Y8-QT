#include <QFileInfo>
#include <QTest>
#include "face_base.h"
#include "resource_manager.h"

CFaceBase::CFaceBase(QWidget *parent) :
    QWidget(parent)
{
    QFont font;                         //设置显示字体大小
    font.setPixelSize(SYS_FONT(22));

    lbBackGround = new QLabel(this);    //背景图片
    lbBackGround->setGeometry(0, 0, g_sysWidth, g_sysHeight);
    lbBackGround->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BACK_FACE"));
    lbBackGround->raise();

    stInfo = new QLabel();              //初始化信息，启动信息
    stInfo->setGeometry(0, 0, g_sysWidth, SYS_HEI(50));
    stInfo->setFont(font);
    stInfo->setStyleSheet("background : transparent ; color : blue");
    stInfo->setText(QApplication::translate("CFaceBase", "The system self-testing..." ));
    stInfo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    stInfo->raise();

    infoScene   = new QGraphicsScene();     //用于消息显示的场景
    infoScene->addWidget(stInfo);

    infoView    = new QGraphicsView(this);  //用于消息显示的视图
    infoView->setFocusPolicy(Qt::NoFocus);
    infoView->setFrameShape(QFrame::NoFrame);
    infoView->setFrameShadow(QFrame::Plain);
    infoView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    infoView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    infoView->setStyleSheet("background:transparent");
    infoView->setScene(infoScene);

    progressBar = new QProgressBar();       //初始化进度条
    progressBar->setStyleSheet("QProgressBar{ background-color: black; text-align: center;color:red}"
                               "QProgressBar::chunk {background-color: green;width: 10px;margin: 1px;}");
    //progressBar->setGeometry(0, SYS_HEI(0),  SYS_WID(400), SYS_HEI(40));
    progressBar->setRange(0,SYS_START_FINISH);
    progressBar->setValue(0);
    progressBar->raise();
    progressBar->setFont(font);

    barScene = new QGraphicsScene(this);    //用于进度条显示的视图
    barScene->addWidget(progressBar);

    barView = new QGraphicsView(this);      //用于进度条显示的场景
    barView->setFocusPolicy(Qt::NoFocus);
    barView->setFrameShape(QFrame::NoFrame);
    barView->setFrameShadow(QFrame::Plain);
    barView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    barView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    barView->setAlignment(Qt::AlignTop | Qt::AlignVCenter);
    barView->setStyleSheet("background:transparent");
    barView->setScene(barScene);

    stHospital = new QLabel();              //初始化信息，启动信息
    stHospital->setStyleSheet("background : transparent ; color : black");

    versionScene   = new QGraphicsScene();     //用于消息显示的场景
    versionScene->addWidget(stHospital);

    stHospital->setGeometry(0, 0, g_sysWidth, SYS_HEI(80));
    stHospital->setGeometry(20, 0, g_sysWidth, SYS_HEI(80));
    versionView    = new QGraphicsView(this);  //用于消息显示的视图
    versionView->setFocusPolicy(Qt::NoFocus);
    versionView->setFrameShape(QFrame::NoFrame);
    versionView->setFrameShadow(QFrame::Plain);
    versionView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    versionView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    versionView->setStyleSheet("background:transparent");
    versionView->setScene(versionScene);

    timerStartUp    = new QTimer();         //用于软件启动与完成检测的定时器
    timerStartUp->setSingleShot(true);
    connect(timerStartUp,SIGNAL(timeout()),this,SLOT(OnStartUp()));

    timerStartFinish    = new QTimer();         //用于软件启动与完成检测的定时器
    timerStartFinish->setSingleShot(true);
    connect(timerStartFinish,SIGNAL(timeout()),this,SLOT(OnStartFinish()));

    setVisible(false);

    OnViewDirChange(g_systemDb->g_startAngle);
}

void CFaceBase::OnViewDirChange(int sAngle)
{
    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:

        break;
    case VIEW_DIR_LEFT:

        break;
    case VIEW_DIR_RIGHT:

        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }

}

void CFaceBase::setProgressBar(int mPercent)
{

    //打印初始化日志到控制台
    fprintf(stderr, "Init Percent:%d\n\r",mPercent);

    //打印初始化日志到日志文件
    QString mBuf;
    mBuf.sprintf("Init Percent:%d",mPercent);
    RsMgr->InfoRecord(mBuf);

    progressBar->setValue(mPercent);
    QCoreApplication::processEvents();

    //测试启动画面，延时
    //QTest::qSleep(250);
}

void CFaceBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);

    timerStartUp->start(20);

}
void CFaceBase::hideEvent(QHideEvent *)
{

    RsMgr->VisibleWidgetDel(this);
}
void CFaceBase::mousePressEvent(QMouseEvent */*event*/)
{
}
void CFaceBase::OnStartUp()
{
    //初始化
    RsMgr->InitView(g_dbsys.utility.mPlatform,INIT_STAGE_0);
    RsMgr->InitSlot(INIT_STAGE_0);

    //判断主窗体是否有效
    if(!RsMgr->g_mainBase)
    {
        stInfo->setText(QApplication::translate("CFaceBase", "The main windows is invalid." ));
        return;
    }

    //设置进度条为100
    RsMgr->setInitStage(SYS_START_FINISH);

    //如果是无损检测系统，默认屏幕旋转90度
    if(g_dbsys.utility.mPlatform == PF_NDT_10_A)
        g_mainFrame->setRotate(0);

    //显示主窗体
    g_mainFrame->setSceneWidget( RsMgr->g_mainBase);

    timerStartFinish->start(100);

    //隐藏自身
    this->hide();
}
void CFaceBase::OnStartFinish()
{
    RsMgr->InitView(g_dbsys.utility.mPlatform,INIT_STAGE_1);
    RsMgr->InitSlot(INIT_STAGE_1);
}

