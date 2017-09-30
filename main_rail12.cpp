#include "main_rail12.h"
#include "resource_manager.h"

CMainRail12::CMainRail12(QWidget *parent) :
    CMainBase12(parent)
{
    setObjectName("CMainRail12");        //设置对象名

    resize(g_sysWidth,g_sysHeight);     //重新设置显示大小

    myPopupPosInit();                   //位置初始化

    //判断安装方位，镜像动画显示
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        QTransform Tmatrax;
        Tmatrax.setMatrix(-1,0,0,0,1,0,600,0,1);
        viewMotion->setTransform(Tmatrax);
    }

    OnViewDirChange(g_systemDb->g_startAngle);        //显示视角切换

}

void CMainRail12::myPopupPosInit()
{
    CMainBase12::myPopupPosInit();

    //初始化状态栏显示位置
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_R180]   = QRect(SYS_WID(485),SYS_HEI(90),SYS_WID(315),SYS_HEI(315));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_NORMAL] = QRect(SYS_WID(226),SYS_HEI(32),SYS_WID(146),SYS_HEI(696));//竖屏，正屏
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_LEFT]   = QRect(SYS_WID(584),SYS_HEI(85),SYS_WID(220),SYS_HEI(470));//向左，90度
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_RIGHT]  = QRect(SYS_WID(220),SYS_HEI(213),SYS_WID(220),SYS_HEI(470));//向右，90度

    //初始化液晶按键显示位置
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_R180]      = QRect(SYS_WID(635),SYS_HEI(90),SYS_WID(150),SYS_HEI(375));
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_NORMAL]    = QRect(SYS_WID(14),SYS_HEI(30),SYS_WID(210),SYS_HEI(700));//竖屏，正屏
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_LEFT]      = QRect(SYS_WID(790),SYS_HEI(50),SYS_WID(210),SYS_HEI(530));  //向左，90度
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_RIGHT]     = QRect(SYS_WID(24),SYS_HEI(188),SYS_WID(210),SYS_HEI(530));//向右，90度

    //初始化快捷按键显示位置
    PopInfoPos[SYS_POPUP_QUICK][VIEW_DIR_R180]      = QRect(SYS_WID(635),SYS_HEI(90),SYS_WID(150),SYS_HEI(375));
    PopInfoPos[SYS_POPUP_QUICK][VIEW_DIR_NORMAL]    = QRect(SYS_WID(609),SYS_HEI(623),SYS_WID(230),SYS_HEI(111));//竖屏，正屏
    PopInfoPos[SYS_POPUP_QUICK][VIEW_DIR_LEFT]      = QRect(SYS_WID(666),SYS_HEI(590),SYS_WID(330),SYS_HEI(80));    //向左，90度
    PopInfoPos[SYS_POPUP_QUICK][VIEW_DIR_RIGHT]     = QRect(SYS_WID(28),SYS_HEI(90),SYS_WID(330),SYS_HEI(80));//向右，90度

    //判断安装位置，旋转动画区域
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_R180]     = QRect(SYS_WID(360), SYS_HEI(420), SYS_WID(90), SYS_HEI(80));
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_NORMAL]   = QRect(SYS_WID(842), SYS_HEI(607), SYS_WID(124), SYS_HEI(125));    //竖屏，正屏
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_LEFT]     = QRect(SYS_WID(545), SYS_HEI(615), SYS_WID(125), SYS_HEI(124));//向左90度
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_RIGHT]    = QRect(SYS_WID(354), SYS_HEI(29), SYS_WID(125), SYS_HEI(124));//向右，90度


}

void CMainRail12::OnViewDirChange(int viewPoint)
{

    CMainBase12::OnViewDirChange(viewPoint);

    switch(viewPoint)
    {
    case VIEW_DIR_R180:
        break;
    case VIEW_DIR_NORMAL:
        frameBack->setStyleSheet("QFrame{ border-image: url(:/QRes/8010/png00/background-v.png);}");
        break;
    case VIEW_DIR_LEFT:
        frameBack->setStyleSheet("QFrame{ border-image: url(:/QRes/8010/png00/background-l.png);}");
        break;
    case VIEW_DIR_RIGHT:
        frameBack->setStyleSheet("QFrame{ border-image: url(:/QRes/8010/png00/background-r.png);}");
        break;
    default:
        break;
    }


}
