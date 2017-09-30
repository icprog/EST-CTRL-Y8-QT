#include "main_uarm8.h"

#include "resource_manager.h"

CMainUarm8::CMainUarm8(QWidget *parent) :
    CMainBase8(parent)
{
    setObjectName("CMainUarm8");    //设置对象名

    resize(g_sysWidth,g_sysHeight); //设置大小

    myPopupPosInit();               //位置初始化

    OnViewDirChange(m_iViewDir);    //显示角度切换

    //判断安装方位，镜像动画显示
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        QTransform Tmatrax;
        Tmatrax.setMatrix(-1,0,0,0,1,0,600,0,1);
        viewMotion->setTransform(Tmatrax);
    }

}

void CMainUarm8::myPopupPosInit()
{

    CMainBase8::myPopupPosInit();

    //状态栏位置初始化
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_R180]   = QRect(SYS_WID(485),SYS_HEI(90),SYS_WID(315),SYS_HEI(315));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_NORMAL] = QRect(SYS_WID(485),SYS_HEI(65),SYS_WID(150),SYS_HEI(315));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_LEFT]   = QRect(SYS_WID(615),SYS_HEI(300),SYS_WID(300),SYS_HEI(300));
    PopInfoPos[SYS_POPUP_STATUS][VIEW_DIR_RIGHT]  = QRect(SYS_WID(75),SYS_HEI(0),SYS_WID(110),SYS_HEI(315));

    //液晶按钮位置初始化
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_R180]      = QRect(SYS_WID(635),SYS_HEI(90),SYS_WID(150),SYS_HEI(315));
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_NORMAL]    = QRect(SYS_WID(650),SYS_HEI(65),SYS_WID(150),SYS_HEI(315));
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_LEFT]      = QRect(SYS_WID(135),SYS_HEI(0),SYS_WID(315),SYS_HEI(150));
    PopInfoPos[SYS_POPUP_KEY][VIEW_DIR_RIGHT]     = QRect(SYS_WID(350),SYS_HEI(450),SYS_WID(315),SYS_HEI(150));

    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_R180]     = QRect(SYS_WID(360), SYS_HEI(420), SYS_WID(90), SYS_HEI(80));
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_NORMAL]   = QRect(SYS_WID(355), SYS_HEI(430), SYS_WID(90), SYS_HEI(80));
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_LEFT]     = QRect(SYS_WID(455), SYS_HEI(160), SYS_WID(80), SYS_HEI(90));
    PopInfoPos[SYS_POPUP_FAST][VIEW_DIR_RIGHT]    = QRect(SYS_WID(76), SYS_HEI(239), SYS_WID(80), SYS_HEI(90));

}
