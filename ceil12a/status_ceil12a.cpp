#include "status_rail12a.h"
#ifdef USE_CEIL_12_A


CStatusCeil12a::CStatusCeil12a(QWidget *parent) :
    CStatusBase12(parent)
{

    setObjectName("CStatusCeil12a");

    lbIcon[tRAIL_FID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_FID"));
    lbIcon[tRAIL_SID]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_SID"));
    lbIcon[tRAIL_ANG]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_ANG"));
    lbIcon[tRAIL_DTH]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_DTH"));
    lbIcon[tRAIL_BEH]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_MEASURE_BEH"));

    //根据配置，设置需要显示的控件
    lbIcon[tRAIL_FID]->setVisible(true);
    lbIcon[tRAIL_SID]->setVisible(true);
    lbIcon[tRAIL_ANG]->setVisible(true);
    lbIcon[tRAIL_DTH]->setVisible(true);
    lbIcon[tRAIL_BEH]->setVisible(true);

    lcd[tRAIL_FID]->setVisible(true);
    lcd[tRAIL_SID]->setVisible(true);
    lcd[tRAIL_ANG]->setVisible(true);
    lcd[tRAIL_DTH]->setVisible(true);
    lcd[tRAIL_BEH]->setVisible(true);

    //设置LCD显示颜色，根据按键颜色
    lcd[tRAIL_FID]->setStyleSheet("color : rgb(233,234,236)");
    lcd[tRAIL_SID]->setStyleSheet("color : rgb(49,108,166)");
    lcd[tRAIL_ANG]->setStyleSheet("color : rgb(233,234,236)");
    lcd[tRAIL_DTH]->setStyleSheet("color : rgb(49,108,166)");
    lcd[tRAIL_BEH]->setStyleSheet("color : rgb(233,234,236)");

    lcd[tRAIL_FID]->raise();
    lcd[tRAIL_SID]->raise();
    lcd[tRAIL_ANG]->raise();
    lcd[tRAIL_DTH]->raise();
    lcd[tRAIL_BEH]->raise();

    QList<QRect> mRectTmp;

    //图标位置//NORMAL
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/ICON_FID"  ,QRect(SYS_HEI(1), SYS_WID(188)  ,SYS_HEI(213), SYS_WID(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/ICON_SID"  ,QRect(SYS_HEI(1), SYS_WID(267)  ,SYS_HEI(213), SYS_WID(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/ICON_ANG"  ,QRect(SYS_HEI(238), SYS_WID(237),SYS_HEI(213), SYS_WID(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/ICON_DTH"  ,QRect(SYS_HEI(473), SYS_WID(187),SYS_HEI(213), SYS_WID(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/ICON_BEH"  ,QRect(SYS_HEI(475), SYS_WID(270),SYS_HEI(213), SYS_WID(68))).toRect());
    pRectStatusIcon.append(mRectTmp);

    //LEFT
    mRectTmp.clear();
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/ICON_FID"  ,QRect(SYS_WID(245), SYS_HEI(29) ,SYS_WID(213), SYS_HEI(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/ICON_SID"  ,QRect(SYS_WID(246), SYS_HEI(113) ,SYS_WID(213), SYS_HEI(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/ICON_ANG"  ,QRect(SYS_WID(244), SYS_HEI(221),SYS_WID(213), SYS_HEI(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/ICON_DTH"  ,QRect(SYS_WID(243), SYS_HEI(335),SYS_WID(213), SYS_HEI(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/ICON_BEH"  ,QRect(SYS_WID(244), SYS_HEI(421),SYS_WID(213), SYS_HEI(68))).toRect());
    pRectStatusIcon.append(mRectTmp);

    //RIGHT
    mRectTmp.clear();
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/ICON_FID"  ,QRect(SYS_WID(245), SYS_HEI(29) ,SYS_WID(213), SYS_HEI(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/ICON_SID"  ,QRect(SYS_WID(246), SYS_HEI(113) ,SYS_WID(213), SYS_HEI(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/ICON_ANG"  ,QRect(SYS_WID(244), SYS_HEI(221),SYS_WID(213), SYS_HEI(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/ICON_DTH"  ,QRect(SYS_WID(243), SYS_HEI(335),SYS_WID(213), SYS_HEI(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/ICON_BEH"  ,QRect(SYS_WID(244), SYS_HEI(421),SYS_WID(213), SYS_HEI(68))).toRect());
    pRectStatusIcon.append(mRectTmp);

    //REVERSE
    mRectTmp.clear();
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/ICON_FID"  ,QRect(SYS_HEI(1), SYS_WID(188)  ,SYS_HEI(213), SYS_WID(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/ICON_SID"  ,QRect(SYS_HEI(1), SYS_WID(267) ,SYS_HEI(213), SYS_WID(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/ICON_ANG"  ,QRect(SYS_HEI(238), SYS_WID(237),SYS_HEI(213), SYS_WID(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/ICON_DTH"  ,QRect(SYS_HEI(473), SYS_WID(187),SYS_HEI(213), SYS_WID(68))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/ICON_BEH"  ,QRect(SYS_HEI(475), SYS_WID(270),SYS_HEI(213), SYS_WID(68))).toRect());
    pRectStatusIcon.append(mRectTmp);

    //LCD数码显示位置//normal
    mRectTmp.clear();
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/LCD_FID"  ,QRect(SYS_HEI(36), SYS_WID(198)  , SYS_HEI(145), SYS_WID(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/LCD_SID"  ,QRect(SYS_HEI(36), SYS_WID(277) , SYS_HEI(145), SYS_WID(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/LCD_ANG"  ,QRect(SYS_HEI(271), SYS_WID(247), SYS_HEI(145), SYS_WID(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/LCD_DTH"  ,QRect(SYS_HEI(496), SYS_WID(198), SYS_HEI(145), SYS_WID(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL/LCD_BEH"  ,QRect(SYS_HEI(496), SYS_WID(277), SYS_HEI(145), SYS_WID(50))).toRect());
    pRectStatusLcd.append(mRectTmp);

    //left
    mRectTmp.clear();
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/LCD_FID"  ,QRect(SYS_WID(283), SYS_HEI(39) , SYS_WID(145), SYS_HEI(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/LCD_SID"  ,QRect(SYS_WID(283), SYS_HEI(123), SYS_WID(145), SYS_HEI(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/LCD_ANG"  ,QRect(SYS_WID(283), SYS_HEI(231), SYS_WID(145), SYS_HEI(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/LCD_DTH"  ,QRect(SYS_WID(283), SYS_HEI(345), SYS_WID(145), SYS_HEI(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT/LCD_BEH"  ,QRect(SYS_WID(283), SYS_HEI(431), SYS_WID(145), SYS_HEI(50))).toRect());
    pRectStatusLcd.append(mRectTmp);

    //right
    mRectTmp.clear();
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/LCD_FID"  ,QRect(SYS_WID(283), SYS_HEI(39) , SYS_WID(145), SYS_HEI(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/LCD_SID"  ,QRect(SYS_WID(283), SYS_HEI(123), SYS_WID(145), SYS_HEI(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/LCD_ANG"  ,QRect(SYS_WID(283), SYS_HEI(231), SYS_WID(145), SYS_HEI(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/LCD_DTH"  ,QRect(SYS_WID(283), SYS_HEI(345), SYS_WID(145), SYS_HEI(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT/LCD_BEH"  ,QRect(SYS_WID(283), SYS_HEI(431), SYS_WID(145), SYS_HEI(50))).toRect());
    pRectStatusLcd.append(mRectTmp);

    //reverse
    mRectTmp.clear();
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/LCD_FID"  ,QRect(SYS_HEI(36), SYS_WID(198)  , SYS_HEI(145), SYS_WID(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/LCD_SID"  ,QRect(SYS_HEI(36), SYS_WID(277) , SYS_HEI(145), SYS_WID(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/LCD_ANG"  ,QRect(SYS_HEI(271), SYS_WID(247), SYS_HEI(145), SYS_WID(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/LCD_DTH"  ,QRect(SYS_HEI(496), SYS_WID(198), SYS_HEI(145), SYS_WID(50))).toRect());
    mRectTmp.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE/LCD_BEH"  ,QRect(SYS_HEI(496), SYS_WID(277), SYS_HEI(145), SYS_WID(50))).toRect());
    pRectStatusLcd.append(mRectTmp);

    //窗体位置
    pRectStatusWid.append(g_sysDb->value("CStatusCeil12a/VDIR_NORMAL"  ,QRect(SYS_HEI(0), SYS_WID(0)  , SYS_HEI(696), SYS_WID(520))).toRect());
    pRectStatusWid.append(g_sysDb->value("CStatusCeil12a/VDIR_LEFT"    ,QRect(SYS_WID(0), SYS_HEI(0)  , SYS_WID(696), SYS_HEI(520))).toRect());
    pRectStatusWid.append(g_sysDb->value("CStatusCeil12a/VDIR_RIGHT"   ,QRect(SYS_WID(0), SYS_HEI(0)  , SYS_WID(696), SYS_HEI(520))).toRect());
    pRectStatusWid.append(g_sysDb->value("CStatusCeil12a/VDIR_REVERSE" ,QRect(SYS_HEI(0), SYS_WID(0)  , SYS_HEI(696), SYS_WID(520))).toRect());

    OnViewDirChange(g_sysDb->g_startAngle);

    m_iViewDir = g_sysDb->g_startAngle; //预定义赋值
}

void CStatusCeil12a::OnStatusFresh()
{
    TypeViewDir mDirTemp = m_iViewDir;
    //界面根据角度切换
    if( g_sysDb->CurrentData[2] + 50 < 0)
    {

        if(g_sysDb->mDetectorStandDir == DirStandRight)
            mDirTemp = VDirLEFT;
        else
            mDirTemp = VDirRIGHT;
    }else if( g_sysDb->CurrentData[2] - 50 < 0)
    {
        mDirTemp = VDirREVERSE;
    }else if(g_sysDb->CurrentData[2] > 50)
    {

        if(g_sysDb->mDetectorStandDir == DirStandRight)
            mDirTemp = VDirLEFT;
        else
            mDirTemp =VDirRIGHT ;
    }

    if(mDirTemp != m_iViewDir)
    {
        if(!g_sysDb->mAutoRotate)
            return;

        m_iViewDir = mDirTemp;

        OnViewDirChange(m_iViewDir);
        emit ViewDirChange(m_iViewDir);
    }

    //刷新显示数据
    int mFid = g_sysDb->CurrentData[tRAIL_FID] - g_sysDb->CurrentData[tRAIL_BEH];
    lcd[tRAIL_FID]->display(mFid);
    lcd[tRAIL_SID]->display(g_sysDb->CurrentData[tRAIL_SID]);
    lcd[tRAIL_ANG]->display(g_sysDb->CurrentData[tRAIL_ANG]);
    lcd[tRAIL_DTH]->display(g_sysDb->CurrentData[tRAIL_DTH]);
    lcd[tRAIL_BEH]->display(g_sysDb->CurrentData[tRAIL_BEH]);

}

#endif
