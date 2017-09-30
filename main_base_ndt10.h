#ifndef MAIN_BASE_NDT10_H
#define MAIN_BASE_NDT10_H

#include "main_base.h"
#include "button_render.h"
#include "lcd_number.h"
#include "button_stable.h"
#include "system_mech.h"

#include <QPolygon>
#include <QFrame>


class CMainBaseNdt10 : public CMainBase
{
    Q_OBJECT
    
public:
    explicit CMainBaseNdt10(QWidget *parent = 0);

    void SendKeySingle(short idx,short key);        //send key for single motor move//idx for motor index//key for value
    void SendKeyMulti(short idx0,short key0,short idx1 = -1,short key1 = 0);         //不影响上一条指令的情况下，再增加一个动作
    void SendKeyStop(short key0,short key1 ,short key2 = -1,short key3 = -1,short key4 = -1);         //

    void SetWarningText(QString );                       //设定警示信息
    void SetInfoText(QString );                              //设定提示信息
private:

    //横臂扫描的可视化部分
    QList <CButtonStable *> pBtnArmCentor;            //中间平板提示框
    QFrame * pArmBackBorder;                         //横臂扫描可视化部分背景
    int mArmColorIndex;                                     //
    int mArmExpDir;
    void BuildArmVisiable();                              //横臂扫描的可视化模块
    void ArmVisableCtrl();                                 //自动到位之前的横臂颜色控制

    //长台扫描的可视化部分
    QList <CButtonStable *> pBtnLongCentor;            //中间平板提示框
    QFrame * pLongBackBorder;                         //长台扫描可视化部分背景
    QList <QString *> listPanelColor;                    //长台可视化扫描颜色
    int mLongColorIndex;                                     //
    int mLongExpDir;
    void BuildLongVisiable();                              //长台扫描的可视化模块
    void LongVisableCtrl();                                 //自动到位之前的长台颜色控制

    QList<CButtonRender*> arrRenderSmallR60;           //小圆台扫描可视化部件
    QList<CButtonRender*> arrRenderSmallR45;           //小圆台扫描可视化部件
    QList<CButtonRender*> arrRenderSmallR40;           //小圆台扫描可视化部件
    QList<CButtonRender*> arrRenderSmallR36;           //小圆台扫描可视化部件
    QList<CButtonRender*> * arrRenderSmall;

    int mSmallAngleRotate;                      //当前模式要转动的角度
    int mSmallPanelIndex;
    int mSmallExpDir;
    void BuildSmallVisiable(QList<CButtonRender*> & ,int angle);
    void SmallVisableCtrl();

    bool CmdDataValidCheck(int idx,int key);        //判断待发送的数据是否超过该路电机限位
    bool CmdSafeFuncCheck(int idx,int key);
    bool CmdSafeFuncAdd(int idx,int key);
    bool CmdSafeFuncDel(int idx);

    int mPanelBorderType;                       //记录是扫面长台的前，后，中间
    int mLongTableRunStepNumber; //记录一共需要多少个步进完成扫描
    int mArmTableRunStepNumber; //记录一共需要多少个步进完成扫描

    int mMoveReadyMask;              //是否判断部件运动到位
    int mLongTableRunStep;          //长台扫描一次转动的角度
    int mArmTableRunStep;          //长台扫描一次转动的角度
    int mPanelYStepMin;               //平板在长台下前后移动的距离
    int mPanelYStepMax;               //平板在长台下前后移动的距离
    int mTubeYStepMin;               //平板在长台下前后移动的距离
    int mTubeYStepMax;               //平板在长台下前后移动的距离
    int mPanelZStepMin;               //平板在长台下前后移动的距离
    int mTubeFollowPatch;               //大圆台扫描X方向步进最大值

    void ParamLoad();                   //加载参数

    CLcdNumber * pLcdDisplay[4];

    QTimer * tmNdtFresh;
    QTimer * tmArmTubeFollow;       //横臂扫描模式的球管延时跟随定时器
    QTimer * tmAutoPosition;       //自动位控制定时器

    int mTubeFollowStart;
    int mWatchDogCtr;
    int mExpDelayCtr;                   //曝光延时计数器，一定时间内，不再发送步进命令
    int AutoPositionIndex;              //区分哪一种扫描方式，长台，圆台，小圆台

    void ExpControl();                //曝光消息检测与运动步进运动控制
    void ExpControlLongV2();
    void ExpControlArmV1();
    void ExpControlRound();
    void ExpControlSmall();

    int bLongExpStill;
    int bManualPosition;                  //手动到位标记，目前手动模式下，不支持联动
    int statLongTableAuto;              //长台自动到位状态
    int statLongTableStepCounter; //记录一共需要多少个步进完成扫描
    int isLongTablePos;                      //是否处于长台扫描模式，进入长台扫描模式后，球管，平板没有动过。
    void OnLongTablePosition();     //长台扫描到位控制
    void OnLongTableRestart();      //长台扫描归零操作，主要平板和长台归零

    int statArmTableAuto;              //长台自动到位状态
    int statArmTableStepCounter; //记录一共需要多少个步进完成扫描
    int isArmTablePos;                      //是否处于长台扫描模式，进入长台扫描模式后，球管，平板没有动过。
    void OnArmTablePosition();     //长台扫描到位控制
    void OnArmTableRestart();      //长台扫描归零操作，主要平板和长台归零

    int statSmallTableAuto;                 //小圆台自动到位状态
    int isSmallTablePos;                        //是否处于小圆台扫描模式，进入小圆台扫描模式后，球管，平板没有动过。
    void OnSmallTablePosition();        //小圆台扫描到位控制
    void OnSmallTableRestart();         //小圆台角度归零操作

    CSystemMech * mech;

    //功能选择按钮,包含标题栏
    CButtonStable* btnLongScan;
    CButtonStable* btnArmScan;
    CButtonStable* btnRoundScan;
    CButtonStable* btnSmallScan;
    QList<CButtonStable*> arrBtnMenuScan;
    void BuildMenuScanBtn();

    //底部页面切换功能按钮
    CButtonStable* btnStandPage;
    CButtonStable* btnTablePage;
    CButtonStable* btnTubePage;
    QList<CButtonStable*> arrBtnMenuBottom;
    CButtonStable* btnMenuBack;
    CButtonStable* btnMenuNc1;
    CButtonStable* btnMenuNc2;
    QList<CButtonStable*> arrBtnScanBottom;
    void BuidMenuBottonBtn();

    //立柱页面动作按钮
    CButtonStable * btnHeiUp;
    CButtonStable * btnHeiDown;
    CButtonStable * btnUidFront;
    CButtonStable * btnUidBack;
    CButtonStable * btnDtaAdd;
    CButtonStable * btnDtaDec;
    CButtonStable* btnNullLeft;
    CButtonStable* btnNullRight;
    QList<CButtonStable*> arrBtnStand;
    void BuidStandCtrlBtn();

    //球管页面动作按钮
    CButtonStable * btnFidUp;
    CButtonStable * btnFidDown;
    CButtonStable * btnSidLeft;
    CButtonStable * btnSidRight;
    CButtonStable * btnCepFront;
    CButtonStable * btnCepBack;
    CButtonStable * btnAngAdd;
    CButtonStable * btnAngDec;
    QList<CButtonStable*> arrBtnTube;
    void BuidTubeCtrlBtn();

    //平台页面动作按钮
    CButtonStable* btnLmvRight;
    CButtonStable* btnLmvLeft;
    CButtonStable* btnRmvLeft;
    CButtonStable* btnRmvRight;
    CButtonStable* btnRolZz;
    CButtonStable* btnRolFz;
    CButtonStable* btnSrlZz;
    CButtonStable* btnSrlFz;
    QList<CButtonStable*> arrBtnTable;
    void BuidTableCtrlBtn();

    //长台扫描页面按钮
    CButtonStable* btnLongAuto;
    CButtonStable* btnLongManual;
    CButtonStable* btnLongExpMove;
    CButtonStable* btnLongExpStill;
    CButtonStable* btnLongTableLeft;
    CButtonStable* btnLongTableRight;
    CButtonStable* btnLongPanelFront;
    CButtonStable* btnLongPanelBack;
    QList<CButtonStable*> arrBtnSmartLong;
    void BuidSmartLongCtrlBtn();

    //横臂扫描页面按钮
    CButtonStable* btnArmAuto;
    CButtonStable* btnArmManual;
    CButtonStable* btnArmExpMove;
    CButtonStable* btnArmExpStill;
    CButtonStable* btnArmPanelUp;
    CButtonStable* btnArmPanelDown;
    CButtonStable* btnArmPanelFront;
    CButtonStable* btnArmPanelBack;
    QList<CButtonStable*> arrBtnSmartArm;
    void BuidSmartArmCtrlBtn();

    QList<CButtonRender*> arrRenderRoundR30;           //大圆台扫描可视化部件
    QList<CButtonRender*> arrRenderRoundR20;           //大圆台扫描可视化部件
    QList<CButtonRender*> arrRenderRoundR18;           //大圆台扫描可视化部件
    QList<CButtonRender*> arrRenderRoundR15;           //大圆台扫描可视化部件
    QList<CButtonRender*> * arrRenderRound;           //大圆台扫描可视化部件

    int mRoundPanelIndex;               //当前平板图形序号
    int mRoundExpDir;                       //步进长度，默认为1
    void BuildRoundVisiable(QList<CButtonRender*> & ,int angle);          //构建大圆台可视部分
    void RoundVisableCtrl();             //大圆台自动运动的颜色控制

    int statRoundTableAuto;             //大圆台自动到位状态
    int mRoundTableRotateStep;      //大圆台扫描一次转动的角度
    int isRoundTablePos;                   //是否处于大圆台扫描模式，进入大圆台扫描模式后，球管，平板没有动过。
    void OnRoundTablePositionFlat();    //大圆台扫描到位控制
    void OnRoundTablePositionAngle();    //大圆台扫描到位控制
    void OnRoundTableRestart();     // 大圆台扫描归零，主要平板角度归零

    //大圆台扫描页面按钮
    CButtonStable* btnRoundAuto;
    CButtonStable* btnRoundManual;
    CButtonStable* btnRoundExpMove;
    CButtonStable* btnRoundExpStill;
    CButtonStable* btnRoundTableLeft;
    CButtonStable* btnRoundTableRight;
    CButtonStable* btnRoundTableZz;
    CButtonStable* btnRoundTableFz;
    CButtonStable* btnRoundTableR30;
    CButtonStable* btnRoundTableR20;
    CButtonStable* btnRoundTableR18;
    CButtonStable* btnRoundTableR15;
    CButtonStable* btnRoundFlat;
    CButtonStable* btnRoundAngle;

    QList<CButtonStable*> arrBtnSmartRound;
    void BuidSmartRoundCtrlBtn();

    //小圆台扫描页面按钮
    CButtonStable* btnSmallAuto;
    CButtonStable* btnSmallExpMove;
    CButtonStable* btnSmallExpStill;
    CButtonStable* btnSmallManual;
    CButtonStable* btnSmallHeiUp;
    CButtonStable* btnSmallHeiDown;
    CButtonStable* btnSmallTableZz;
    CButtonStable* btnSmallTableFz;
    CButtonStable* btnSmallTableR60;
    CButtonStable* btnSmallTableR45;
    CButtonStable* btnSmallTableR40;
    CButtonStable* btnSmallTableR36;
    QList<CButtonStable*> arrBtnSmartSmall;
    void BuidSmartSmallCtrlBtn();

    void BuildLcdDisplay();

    void HideAllButton();

    bool DrawRender(QList<CButtonRender*> &);    //real draw function

    bool DrawTable(int);     //draw round talbe

    QKeyEvent * keyEventBtn;

    //get page index for button scan
    int m_pageIdx,m_pageIdxBuf;
    int getPageIdx();
    int getPageIdxBuf();
    void setPageIdx(int mPage);

    QBrush mBrColor;
    QString gStrWarnings;
    QString gStrInfos;
    bool DrawMessageText();         //绘制文字消息

    void myPopupPosInit();           //初始化弹出框位置
protected:

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    virtual void mySceneInit();         //通用场景初始化
    virtual void myViewInit();          //通用视图控件初始化

public slots:

    void OnNdtDataFresh();              //timer for fresh

    virtual void OnFilmKeyDown(int);            //film key down
    virtual void OnFilmKeyUp(int);                  //film key up
    virtual void OnPageChange(int);

    virtual void OnViewChange(int);         //显示视图变更
    virtual void OnPopupShow(int popIdx);   //弹出消息

    void OnBtnTitlePressed();                   //title pressed ,switch page to setting page
    void OnMenuCtrlPressed();       //平板页面动作支持
    void ShowPage(int );                //根据序号显示页面

    void OnStandCtrlPressed();       //立柱页面动作支持
    void OnStandCtrlReleased();       //立柱页面动作支持
    void OnStandFilmPressed(QKeyEvent *);       //立柱页面动作支持
    void OnStandFilmReleased(QKeyEvent *);       //立柱页面动作支持

    void OnTableCtrlPressed();       //平板页面动作支持
    void OnTableCtrlReleased();       //平板页面动作支持
    void OnTableFilmPressed( QKeyEvent *);       //平板页面动作支持
    void OnTableFilmReleased( QKeyEvent *);       //平板页面动作支持

    void OnTubeCtrlPressed();       //球管页面动作支持
    void OnTubeCtrlReleased();
    void OnTubeFilmPressed(QKeyEvent *);       //球管页面动作支持
    void OnTubeFilmReleased(QKeyEvent *);

    void OnSmartLongCtrlPressed();       //长台扫描页面动作支持
    void OnSmartLongCtrlReleased();       //长台扫描页面动作支持
    void OnSmartLongFilmPressed(QKeyEvent *);       //长台扫描页面动作支持
    void OnSmartLongFilmReleased(QKeyEvent *);       //长台扫描页面动作支持

    void OnSmartArmCtrlPressed();       //长台扫描页面动作支持
    void OnSmartArmCtrlReleased();       //长台扫描页面动作支持
    void OnSmartArmFilmPressed(QKeyEvent *);       //长台扫描页面动作支持
    void OnSmartArmFilmReleased(QKeyEvent *);       //长台扫描页面动作支持

    void OnSmartRoundCtrlPressed();       //大圆台扫描页面动作支持
    void OnSmartRoundCtrlReleased();       //大圆台扫描页面动作支持
    void OnSmartRoundFilmPressed(QKeyEvent *);       //大圆台扫描页面动作支持
    void OnSmartRoundFilmReleased(QKeyEvent *);       //大圆台扫描页面动作支持

    void OnSmartSmallCtrlPressed();              //小圆台扫描页面动作支持
    void OnSmartSmallCtrlReleased();
    void OnSmartSmallFilmPressed(QKeyEvent *);              //小圆台扫描页面动作支持
    void OnSmartSmallFilmReleased(QKeyEvent *);

    void OnAutoPositionTimer();
    void OnTimerTubeFollow();
};

#endif // MAIN_BASE_NDT10_H
