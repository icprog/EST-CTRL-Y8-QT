#include "main_ceil8.h"
#include "resource_manager.h"

CMainCeil8::CMainCeil8(QWidget *parent) :
    CMainBase8(parent)
{

    setObjectName("CMainCeil8");    //设置对象名

    resize(g_sysWidth,g_sysHeight); //大小调整

    myPopupPosInit();               //位置初始化

    OnViewDirChange(m_iViewDir);    //显示角度切换

    //判断安装位置，旋转viewMotion
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        QTransform Tmatrax;
        Tmatrax.setMatrix(-1,0,0,0,1,0,600,0,1);
        viewMotion->setTransform(Tmatrax);
    }
}

void CMainCeil8::myPopupPosInit()
{
    CMainBase8::myPopupPosInit();       //调用基类的位置初始化

    //根据需要，处理部分位置初始化
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_R180]   = QRect(SYS_WID(485),SYS_HEI(90),SYS_WID(315),SYS_HEI(315));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_NORMAL] = QRect(SYS_WID(490),SYS_HEI(25),SYS_WID(150),SYS_HEI(350));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_LEFT]   = QRect(SYS_WID(580),SYS_HEI(300),SYS_WID(300),SYS_HEI(300));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_RIGHT]  = QRect(SYS_WID(50),SYS_HEI(0),SYS_WID(200),SYS_HEI(300));

    //液晶按键位置初始化
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_R180]      = QRect(SYS_WID(635),SYS_HEI(90),SYS_WID(150),SYS_HEI(375));
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_NORMAL]    = QRect(SYS_WID(650),SYS_HEI(12),SYS_WID(150),SYS_HEI(375));
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_LEFT]      = QRect(SYS_WID(137),SYS_HEI(0),SYS_WID(375),SYS_HEI(150));
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_RIGHT]     = QRect(SYS_WID(288),SYS_HEI(450),SYS_WID(375),SYS_HEI(150));

    //判断安装位置，旋转动画区域
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_R180]     = QRect(SYS_WID(360), SYS_HEI(420), SYS_WID(90), SYS_HEI(80));
        PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_NORMAL]   = QRect(SYS_WID(355), SYS_HEI(430), SYS_WID(90), SYS_HEI(80));
        PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_LEFT]     = QRect(SYS_WID(455), SYS_HEI(160), SYS_WID(80), SYS_HEI(90));
        PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_RIGHT]    = QRect(SYS_WID(76), SYS_HEI(239), SYS_WID(80), SYS_HEI(90));
    }else
    {
        PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_R180]     = QRect(SYS_WID(360), SYS_HEI(420), SYS_WID(90), SYS_HEI(80));
        PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_NORMAL]   = QRect(SYS_WID(355), SYS_HEI(430), SYS_WID(90), SYS_HEI(80));
        PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_LEFT]     = QRect(SYS_WID(455), SYS_HEI(160), SYS_WID(80), SYS_HEI(90));
        PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_RIGHT]    = QRect(SYS_WID(76), SYS_HEI(239), SYS_WID(80), SYS_HEI(90));
    }

    //判断显示关机按钮
    if(g_dbsys.utility.mShutdownShow)
    {
        PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_NORMAL] = QRect(SYS_WID(485),SYS_HEI(50),SYS_WID(150),SYS_HEI(350));
    }

}
