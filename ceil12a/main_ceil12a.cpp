#include "main_rail12a.h"

#ifdef USE_CEIL_12_A


CMainCeil12a::CMainCeil12a(QWidget *parent) :
    CMainBase12(parent)
{
    setObjectName("CMainCeil12a");        //设置对象名

    resize(g_sysWidth,g_sysHeight);     //重新设置显示大小

    myPopupPosInit();                   //位置初始化

    myViewInit();                       //初始化视图

    mySceneInit();                      //初始化场景

    //判断安装方位，镜像动画显示
    if(g_sysDb->mDetectorStandDir == DirStandRight)
    {
        QTransform Tmatrax;
        Tmatrax.setMatrix(-1,0,0,0,1,0,600,0,1);
        viewMotion->setTransform(Tmatrax);
    }

    OnViewDirChange(g_sysDb->g_startAngle);        //显示视角切换

}

void CMainCeil12a::myPopupPosInit()
{
    //角度切换数据初始化
    m_iViewSwitch[VDirNORM][VDirNORM]       = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,0).toInt();
    m_iViewSwitch[VDirNORM][VDirLEFT]       = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,-90).toInt();
    m_iViewSwitch[VDirNORM][VDirRIGHT]      = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,90).toInt();
    m_iViewSwitch[VDirNORM][VDirREVERSE]    = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,0).toInt();

    m_iViewSwitch[VDirLEFT][VDirNORM]       = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,90).toInt();
    m_iViewSwitch[VDirLEFT][VDirLEFT]       = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,0).toInt();
    m_iViewSwitch[VDirLEFT][VDirRIGHT]      = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,180).toInt();
    m_iViewSwitch[VDirLEFT][VDirREVERSE]    = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,-90).toInt();

    m_iViewSwitch[VDirRIGHT][VDirNORM]      = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,-90).toInt();
    m_iViewSwitch[VDirRIGHT][VDirLEFT]      = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,0).toInt();
    m_iViewSwitch[VDirRIGHT][VDirRIGHT]     = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,0).toInt();
    m_iViewSwitch[VDirRIGHT][VDirREVERSE]   = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,90).toInt();

    m_iViewSwitch[VDirREVERSE][VDirNORM]    = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,180).toInt();
    m_iViewSwitch[VDirREVERSE][VDirLEFT]    = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,90).toInt();
    m_iViewSwitch[VDirREVERSE][VDirRIGHT]   = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,-90).toInt();
    m_iViewSwitch[VDirREVERSE][VDirREVERSE] = g_sysDb->value("CMainCeil12a/VDirNORM/VDirNORM"  ,-90).toInt();


    //每个需要重新定位的部件的位置
    PopInfoPos[SYS_POPUP_FOCUS][VDirREVERSE]    = g_sysDb->value("CMainCeil12a/SYS_POPUP_FOCUS/VDirREVERSE" ,
                                                                 QRect(SYS_WID(125),SYS_HEI(225),SYS_WID(200),SYS_HEI(100))).toRect();
    PopInfoPos[SYS_POPUP_FOCUS][VDirNORM]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_FOCUS/VDirNORM" ,
                                                                 QRect(SYS_WID(675),SYS_HEI(165),SYS_WID(100),SYS_HEI(200))).toRect();
    PopInfoPos[SYS_POPUP_FOCUS][VDirLEFT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_FOCUS/VDirLEFT" ,
                                                                 QRect(SYS_WID(165),SYS_HEI(230),SYS_WID(200),SYS_HEI(100))).toRect();
    PopInfoPos[SYS_POPUP_FOCUS][VDirRIGHT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_FOCUS/VDirRIGHT" ,
                                                                 QRect(SYS_WID(659),SYS_HEI(438),SYS_WID(200),SYS_HEI(100))).toRect();

    PopInfoPos[SYS_POPUP_AEC][VDirREVERSE]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_AEC/VDirREVERSE" ,
                                                                 QRect(SYS_WID(25),SYS_HEI(150),SYS_WID(300),SYS_HEI(280))).toRect();
    PopInfoPos[SYS_POPUP_AEC][VDirNORM]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_AEC/VDirNORM" ,
                                                                 QRect(SYS_WID(583),SYS_HEI(65),SYS_WID(280),SYS_HEI(300))).toRect();
    PopInfoPos[SYS_POPUP_AEC][VDirLEFT]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_AEC/VDirLEFT" ,
                                                                 QRect(SYS_WID(65),SYS_HEI(140),SYS_WID(300),SYS_HEI(280))).toRect();
    PopInfoPos[SYS_POPUP_AEC][VDirRIGHT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_AEC/VDirRIGHT" ,
                                                                 QRect(SYS_WID(659),SYS_HEI(348),SYS_WID(300),SYS_HEI(280))).toRect();

    PopInfoPos[SYS_POPUP_SMART][VDirREVERSE]    = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirREVERSE" ,
                                                                 QRect(SYS_WID(130),SYS_HEI(213),SYS_WID(505),SYS_HEI(525))).toRect();
    PopInfoPos[SYS_POPUP_SMART][VDirNORM]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirNORM" ,
                                                                 QRect(SYS_WID(390),SYS_HEI(30),SYS_WID(505),SYS_HEI(525))).toRect();
    PopInfoPos[SYS_POPUP_SMART][VDirLEFT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirLEFT" ,
                                                                 QRect(SYS_WID(22),SYS_HEI(105),SYS_WID(505),SYS_HEI(525))).toRect();
    PopInfoPos[SYS_POPUP_SMART][VDirRIGHT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirRIGHT" ,
                                                                 QRect(SYS_WID(497),SYS_HEI(138),SYS_WID(505),SYS_HEI(525))).toRect();

    PopInfoPos[SYS_POPUP_REQUEST][VDirREVERSE]  = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirREVERSE" ,
                                                                 QRect(SYS_WID(120),SYS_HEI(190),SYS_WID(360),SYS_HEI(360))).toRect();
    PopInfoPos[SYS_POPUP_REQUEST][VDirNORM]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirNORM" ,
                                                                 QRect(SYS_WID(520),SYS_HEI(190),SYS_WID(360),SYS_HEI(360))).toRect();
    PopInfoPos[SYS_POPUP_REQUEST][VDirLEFT]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirLEFT" ,
                                                                 QRect(SYS_WID(290),SYS_HEI(258),SYS_WID(360),SYS_HEI(360))).toRect();
    PopInfoPos[SYS_POPUP_REQUEST][VDirRIGHT]    = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirRIGHT" ,
                                                                 QRect(SYS_WID(374),SYS_HEI(150),SYS_WID(360),SYS_HEI(360))).toRect();

    PopInfoPos[SYS_POPUP_GEN][VDirREVERSE]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirREVERSE" ,
                                                                 QRect(SYS_WID(124),SYS_HEI(268),SYS_WID(450),SYS_HEI(450))).toRect();
    PopInfoPos[SYS_POPUP_GEN][VDirNORM]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirNORM" ,
                                                                 QRect(SYS_WID(450),SYS_HEI(50),SYS_WID(450),SYS_HEI(450))).toRect();
    PopInfoPos[SYS_POPUP_GEN][VDirLEFT]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirLEFT" ,
                                                                 QRect(SYS_WID(50),SYS_HEI(105),SYS_WID(450),SYS_HEI(450))).toRect();
    PopInfoPos[SYS_POPUP_GEN][VDirRIGHT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_SMART/VDirRIGHT" ,
                                                                 QRect(SYS_WID(524),SYS_HEI(213),SYS_WID(450),SYS_HEI(450))).toRect();

    PopInfoPos[SYS_POPUP_MOTION][VDirREVERSE]   = g_sysDb->value("CMainCeil12a/SYS_POPUP_MOTION/VDirREVERSE" ,
                                                                 QRect(SYS_WID(124),SYS_HEI(268),SYS_WID(450),SYS_HEI(450))).toRect();
    PopInfoPos[SYS_POPUP_MOTION][VDirNORM]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_MOTION/VDirNORM" ,
                                                                 QRect(SYS_WID(460),SYS_HEI(50),SYS_WID(450),SYS_HEI(450))).toRect();
    PopInfoPos[SYS_POPUP_MOTION][VDirLEFT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_MOTION/VDirLEFT" ,
                                                                 QRect(SYS_WID(50),SYS_HEI(114),SYS_WID(450),SYS_HEI(450))).toRect();
    PopInfoPos[SYS_POPUP_MOTION][VDirRIGHT]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_MOTION/VDirRIGHT" ,
                                                                 QRect(SYS_WID(524),SYS_HEI(204),SYS_WID(450),SYS_HEI(450))).toRect();

    PopInfoPos[SYS_POPUP_INFO][VDirREVERSE]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_INFO/VDirREVERSE" ,
                                                                 QRect(SYS_WID(552),SYS_HEI(240),SYS_WID(72),SYS_HEI(500))).toRect();
    PopInfoPos[SYS_POPUP_INFO][VDirNORM]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_INFO/VDirNORM" ,
                                                                 QRect(SYS_WID(400),SYS_HEI(28),SYS_WID(72),SYS_HEI(500))).toRect();
    PopInfoPos[SYS_POPUP_INFO][VDirLEFT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_INFO/VDirLEFT" ,
                                                                 QRect(SYS_WID(24),SYS_HEI(660),SYS_WID(500),SYS_HEI(72))).toRect();
    PopInfoPos[SYS_POPUP_INFO][VDirRIGHT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_INFO/VDirRIGHT" ,
                                                                 QRect(SYS_WID(500),SYS_HEI(40),SYS_WID(500),SYS_HEI(72))).toRect();

    PopInfoPos[SYS_POPUP_PARAM][VDirREVERSE]    = g_sysDb->value("CMainCeil12a/SYS_POPUP_PARAM/VDirREVERSE" ,
                                                                 QRect(SYS_WID(80),SYS_HEI(20),SYS_WID(310),SYS_HEI(600))).toRect();
    PopInfoPos[SYS_POPUP_PARAM][VDirNORM]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_PARAM/VDirNORM" ,
                                                                 QRect(SYS_WID(350),SYS_HEI(60),SYS_WID(600),SYS_HEI(310))).toRect();
    PopInfoPos[SYS_POPUP_PARAM][VDirLEFT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_PARAM/VDirLEFT" ,
                                                                 QRect(SYS_WID(60),SYS_HEI(102),SYS_WID(310),SYS_HEI(600))).toRect();
    PopInfoPos[SYS_POPUP_PARAM][VDirRIGHT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_PARAM/VDirRIGHT" ,
                                                                 QRect(SYS_WID(654),SYS_HEI(66),SYS_WID(310),SYS_HEI(600))).toRect();

    //控制位置数据初始化
    PopInfoPos[SYS_POPUP_MENU][VDirREVERSE]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_MENU/VDirREVERSE" ,
                                                                 QRect(SYS_WID(423),SYS_HEI(32),SYS_WID(230),SYS_HEI(111))).toRect();
    PopInfoPos[SYS_POPUP_MENU][VDirNORM]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_MENU/VDirNORM" ,
                                                                 QRect(SYS_WID(371),SYS_HEI(625),SYS_WID(230),SYS_HEI(111))).toRect();
    PopInfoPos[SYS_POPUP_MENU][VDirLEFT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_MENU/VDirLEFT" ,
                                                                 QRect(SYS_WID(670),SYS_HEI(668),SYS_WID(330),SYS_HEI(80))).toRect();
    PopInfoPos[SYS_POPUP_MENU][VDirRIGHT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_MENU/VDirRIGHT" ,
                                                                 QRect(SYS_WID(24),SYS_HEI(20),SYS_WID(330),SYS_HEI(80))).toRect();

    //初始化状态栏显示位置
    PopInfoPos[SYS_POPUP_STATUS][VDirREVERSE]   = g_sysDb->value("CMainCeil12a/SYS_POPUP_STATUS/VDirREVERSE" ,
                                                                 QRect(SYS_WID(652),SYS_HEI(36),SYS_WID(146),SYS_HEI(696))).toRect();
    PopInfoPos[SYS_POPUP_STATUS][VDirNORM]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_STATUS/VDirNORM" ,
                                                                 QRect(SYS_WID(226),SYS_HEI(36),SYS_WID(146),SYS_HEI(696))).toRect();
    PopInfoPos[SYS_POPUP_STATUS][VDirLEFT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_STATUS/VDirLEFT" ,
                                                                 QRect(SYS_WID(560),SYS_HEI(95),SYS_WID(220),SYS_HEI(470))).toRect();
    PopInfoPos[SYS_POPUP_STATUS][VDirRIGHT]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_STATUS/VDirRIGHT" ,
                                                                 QRect(SYS_WID(244),SYS_HEI(203),SYS_WID(220),SYS_HEI(470))).toRect();

    PopInfoPos[SYS_POPUP_LOGO][VDirREVERSE]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_LOGO/VDirREVERSE" ,
                                                                 QRect(SYS_WID(19),SYS_HEI(633),SYS_WID(80),SYS_HEI(117))).toRect();
    PopInfoPos[SYS_POPUP_LOGO][VDirNORM]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_LOGO/VDirNORM" ,
                                                                 QRect(SYS_WID(925),SYS_HEI(18),SYS_WID(80),SYS_HEI(117))).toRect();
    PopInfoPos[SYS_POPUP_LOGO][VDirLEFT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_LOGO/VDirLEFT" ,
                                                                 QRect(SYS_WID(10),SYS_HEI(14),SYS_WID(117),SYS_HEI(80))).toRect();
    PopInfoPos[SYS_POPUP_LOGO][VDirRIGHT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_LOGO/VDirRIGHT" ,
                                                                 QRect(SYS_WID(888),SYS_HEI(672),SYS_WID(117),SYS_HEI(80))).toRect();

    PopInfoPos[SYS_POPUP_TECH][VDirREVERSE]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_TECH/VDirREVERSE" ,
                                                                 QRect(SYS_WID(185),SYS_HEI(34),SYS_WID(230),SYS_HEI(111))).toRect();
    PopInfoPos[SYS_POPUP_TECH][VDirNORM]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_TECH/VDirNORM" ,
                                                                 QRect(SYS_WID(609),SYS_HEI(623),SYS_WID(230),SYS_HEI(111))).toRect();
    PopInfoPos[SYS_POPUP_TECH][VDirLEFT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_TECH/VDirLEFT" ,
                                                                 QRect(SYS_WID(670),SYS_HEI(590),SYS_WID(330),SYS_HEI(80))).toRect();
    PopInfoPos[SYS_POPUP_TECH][VDirRIGHT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_TECH/VDirRIGHT" ,
                                                                 QRect(SYS_WID(24),SYS_HEI(90),SYS_WID(330),SYS_HEI(80))).toRect();

    //判断安装位置，旋转动画区域
    PopInfoPos[SYS_POPUP_FAST][VDirREVERSE]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_FAST/VDirREVERSE" ,
                                                                 QRect(SYS_WID(58), SYS_HEI(36), SYS_WID(124), SYS_HEI(125))).toRect();
    PopInfoPos[SYS_POPUP_FAST][VDirNORM]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_FAST/VDirNORM" ,
                                                                 QRect(SYS_WID(842), SYS_HEI(607), SYS_WID(124), SYS_HEI(125))).toRect();
    PopInfoPos[SYS_POPUP_FAST][VDirLEFT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_FAST/VDirLEFT" ,
                                                                 QRect(SYS_WID(542), SYS_HEI(615), SYS_WID(125), SYS_HEI(124))).toRect();
    PopInfoPos[SYS_POPUP_FAST][VDirRIGHT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_FAST/VDirRIGHT" ,
                                                                 QRect(SYS_WID(357), SYS_HEI(29), SYS_WID(125), SYS_HEI(124))).toRect();

    PopInfoPos[SYS_POPUP_POWER][VDirREVERSE]    = g_sysDb->value("CMainCeil12a/SYS_POPUP_POWER/VDirREVERSE" ,
                                                                 QRect(SYS_WID(22),SYS_HEI(182),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_POWER][VDirNORM]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_POWER/VDirNORM" ,
                                                                 QRect(SYS_WID(930),SYS_HEI(496),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_POWER][VDirLEFT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_POWER/VDirLEFT" ,
                                                                 QRect(SYS_WID(521),SYS_HEI(20),SYS_WID(90),SYS_HEI(72))).toRect();
    PopInfoPos[SYS_POPUP_POWER][VDirRIGHT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_POWER/VDirRIGHT" ,
                                                                 QRect(SYS_WID(413),SYS_HEI(676),SYS_WID(90),SYS_HEI(72))).toRect();

    PopInfoPos[SYS_POPUP_SIM][VDirREVERSE]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_SIM/VDirREVERSE" ,
                                                                 QRect(SYS_WID(22),SYS_HEI(362),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_SIM][VDirNORM]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_SIM/VDirNORM" ,
                                                                 QRect(SYS_WID(930),SYS_HEI(316),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_SIM][VDirLEFT]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_SIM/VDirLEFT" ,
                                                                 QRect(SYS_WID(331),SYS_HEI(20),SYS_WID(90),SYS_HEI(72))).toRect();
    PopInfoPos[SYS_POPUP_SIM][VDirRIGHT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_SIM/VDirRIGHT" ,
                                                                 QRect(SYS_WID(603),SYS_HEI(676),SYS_WID(90),SYS_HEI(72))).toRect();

    PopInfoPos[SYS_POPUP_NET][VDirREVERSE]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_NET/VDirREVERSE" ,
                                                                 QRect(SYS_WID(22),SYS_HEI(452),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_NET][VDirNORM]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_NET/VDirNORM" ,
                                                                 QRect(SYS_WID(930),SYS_HEI(226),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_NET][VDirLEFT]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_NET/VDirLEFT" ,
                                                                 QRect(SYS_WID(236),SYS_HEI(20),SYS_WID(90),SYS_HEI(72))).toRect();
    PopInfoPos[SYS_POPUP_NET][VDirRIGHT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_NET/VDirRIGHT" ,
                                                                 QRect(SYS_WID(698),SYS_HEI(676),SYS_WID(90),SYS_HEI(72))).toRect();

    //初始化液晶按键显示位置
    PopInfoPos[SYS_POPUP_KEY][VDirREVERSE]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_KEY/VDirREVERSE" ,
                                                                 QRect(SYS_WID(800),SYS_HEI(33),SYS_WID(210),SYS_HEI(700))).toRect();
    PopInfoPos[SYS_POPUP_KEY][VDirNORM]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_KEY/VDirNORM" ,
                                                                 QRect(SYS_WID(14),SYS_HEI(35),SYS_WID(210),SYS_HEI(700))).toRect();
    PopInfoPos[SYS_POPUP_KEY][VDirLEFT]         = g_sysDb->value("CMainCeil12a/SYS_POPUP_KEY/VDirLEFT" ,
                                                                 QRect(SYS_WID(790),SYS_HEI(60),SYS_WID(210),SYS_HEI(520))).toRect();
    PopInfoPos[SYS_POPUP_KEY][VDirRIGHT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_KEY/VDirRIGHT" ,
                                                                 QRect(SYS_WID(24),SYS_HEI(188),SYS_WID(210),SYS_HEI(530))).toRect();

    //初始化快捷按键显示位置
    PopInfoPos[SYS_POPUP_QUICK][VDirREVERSE]    = g_sysDb->value("CMainCeil12a/SYS_POPUP_QUICK/VDirREVERSE" ,
                                                                 QRect(SYS_WID(185),SYS_HEI(34),SYS_WID(230),SYS_HEI(111))).toRect();
    PopInfoPos[SYS_POPUP_QUICK][VDirNORM]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_QUICK/VDirNORM" ,
                                                                 QRect(SYS_WID(609),SYS_HEI(623),SYS_WID(230),SYS_HEI(111))).toRect();
    PopInfoPos[SYS_POPUP_QUICK][VDirLEFT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_QUICK/VDirLEFT" ,
                                                                 QRect(SYS_WID(670),SYS_HEI(590),SYS_WID(330),SYS_HEI(80))).toRect();
    PopInfoPos[SYS_POPUP_QUICK][VDirRIGHT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_QUICK/VDirRIGHT" ,
                                                                 QRect(SYS_WID(24),SYS_HEI(90),SYS_WID(330),SYS_HEI(80))).toRect();

    PopInfoPos[SYS_POPUP_CURTAIN][VDirREVERSE]  = g_sysDb->value("CMainCeil12a/SYS_POPUP_CURTAIN/VDirREVERSE" ,
                                                                 QRect(SYS_WID(22),SYS_HEI(272),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_CURTAIN][VDirNORM]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_CURTAIN/VDirNORM" ,
                                                                 QRect(SYS_WID(930),SYS_HEI(406),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_CURTAIN][VDirLEFT]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_CURTAIN/VDirLEFT" ,
                                                                 QRect(SYS_WID(426),SYS_HEI(20),SYS_WID(90),SYS_HEI(72))).toRect();
    PopInfoPos[SYS_POPUP_CURTAIN][VDirRIGHT]    = g_sysDb->value("CMainCeil12a/SYS_POPUP_CURTAIN/VDirRIGHT" ,
                                                                 QRect(SYS_WID(508),SYS_HEI(676),SYS_WID(90),SYS_HEI(72))).toRect();

    PopInfoPos[SYS_POPUP_NOTIFY][VDirREVERSE]   = g_sysDb->value("CMainCeil12a/SYS_POPUP_NOTIFY/VDirREVERSE" ,
                                                                 QRect(SYS_WID(114),SYS_HEI(338),SYS_WID(60),SYS_HEI(280))).toRect();
    PopInfoPos[SYS_POPUP_NOTIFY][VDirNORM]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_NOTIFY/VDirNORM" ,
                                                                 QRect(SYS_WID(850),SYS_HEI(150),SYS_WID(60),SYS_HEI(280))).toRect();
    PopInfoPos[SYS_POPUP_NOTIFY][VDirLEFT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_NOTIFY/VDirLEFT" ,
                                                                 QRect(SYS_WID(140),SYS_HEI(114),SYS_WID(280),SYS_HEI(60))).toRect();
    PopInfoPos[SYS_POPUP_NOTIFY][VDirRIGHT]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_NOTIFY/VDirRIGHT" ,
                                                                 QRect(SYS_WID(600),SYS_HEI(594),SYS_WID(280),SYS_HEI(60))).toRect();

    PopInfoPos[SYS_POPUP_DATE][VDirREVERSE]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_DATE/VDirREVERSE" ,
                                                                 QRect(SYS_WID(22),SYS_HEI(542),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_DATE][VDirNORM]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_DATE/VDirNORM" ,
                                                                 QRect(SYS_WID(930),SYS_HEI(136),SYS_WID(72),SYS_HEI(90))).toRect();
    PopInfoPos[SYS_POPUP_DATE][VDirLEFT]        = g_sysDb->value("CMainCeil12a/SYS_POPUP_DATE/VDirLEFT" ,
                                                                 QRect(SYS_WID(141),SYS_HEI(20),SYS_WID(90),SYS_HEI(72))).toRect();
    PopInfoPos[SYS_POPUP_DATE][VDirRIGHT]       = g_sysDb->value("CMainCeil12a/SYS_POPUP_DATE/VDirRIGHT" ,
                                                                 QRect(SYS_WID(793),SYS_HEI(676),SYS_WID(90),SYS_HEI(72))).toRect();

    PopInfoPos[SYS_POPUP_QRCODE][VDirREVERSE]   = g_sysDb->value("CMainCeil12a/SYS_POPUP_QRCODE/VDirREVERSE" ,
                                                                 QRect(SYS_WID(300),SYS_HEI(358),SYS_WID(240),SYS_HEI(240))).toRect();
    PopInfoPos[SYS_POPUP_QRCODE][VDirNORM]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_QRCODE/VDirNORM" ,
                                                                 QRect(SYS_WID(480),SYS_HEI(170),SYS_WID(240),SYS_HEI(240))).toRect();
    PopInfoPos[SYS_POPUP_QRCODE][VDirLEFT]      = g_sysDb->value("CMainCeil12a/SYS_POPUP_QRCODE/VDirLEFT" ,
                                                                 QRect(SYS_WID(230),SYS_HEI(300),SYS_WID(240),SYS_HEI(240))).toRect();
    PopInfoPos[SYS_POPUP_QRCODE][VDirRIGHT]     = g_sysDb->value("CMainCeil12a/SYS_POPUP_QRCODE/VDirRIGHT" ,
                                                                 QRect(SYS_WID(554),SYS_HEI(230),SYS_WID(240),SYS_HEI(240))).toRect();
}

#endif
