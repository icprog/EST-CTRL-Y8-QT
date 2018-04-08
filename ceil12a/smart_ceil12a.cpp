#include "smart_rail12a.h"

#ifdef USE_CEIL_12_A


CSmartCeil12a::CSmartCeil12a(QWidget *parent) :
    CSmartBase12(parent)
{
    setObjectName("CSmartCeil12a");

    mSmartMax = RAIL8_SMART_MAX;

    m_iSmartRunMax = 7;
    m_iSmartRun.append(1);
    m_iSmartRun.append(2);
    m_iSmartRun.append(3);
    m_iSmartRun.append(4);
    m_iSmartRun.append(5);
    m_iSmartRun.append(6);
    m_iSmartRun.append(7);

    m_codeSmart.append(0x0050);
    m_codeSmart.append(0x0051);
    m_codeSmart.append(0x0052);
    m_codeSmart.append(0x0053);
    m_codeSmart.append(0x0054);
    m_codeSmart.append(0x0055);
    m_codeSmart.append(0x0056);
    m_codeSmart.append(0x0057);

    pListBtnSmart[0]->setVisible(false);
    pListBtnSmart[8]->setVisible(false);

    QList<QRect> mRectTmp;

    mRectTmp.append(QRect(SYS_HEI(0),SYS_WID(0),SYS_HEI(0),SYS_WID(0)));
    mRectTmp.append(QRect(SYS_HEI(43),SYS_WID(47),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(184),SYS_WID(47),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(329),SYS_WID(47),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(43),SYS_WID(213),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(184),SYS_WID(213),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(329),SYS_WID(213),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(184),SYS_WID(360),SYS_HEI(125),SYS_WID(124)));
    pRectSmartBtn.append(mRectTmp);

    mRectTmp.clear();
    mRectTmp.append(QRect(SYS_HEI(0),SYS_WID(0),SYS_HEI(0),SYS_WID(0)));
    mRectTmp.append(QRect(SYS_WID(43),SYS_HEI(47),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(184),SYS_HEI(47),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(329),SYS_HEI(47),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(43),SYS_HEI(213),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(184),SYS_HEI(213),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(329),SYS_HEI(213),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(184),SYS_HEI(360),SYS_WID(125),SYS_HEI(124)));
    pRectSmartBtn.append(mRectTmp);

    mRectTmp.clear();
    mRectTmp.append(QRect(SYS_HEI(0),SYS_WID(0),SYS_HEI(0),SYS_WID(0)));
    mRectTmp.append(QRect(SYS_WID(43),SYS_HEI(47),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(184),SYS_HEI(47),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(329),SYS_HEI(47),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(43),SYS_HEI(213),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(184),SYS_HEI(213),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(329),SYS_HEI(213),SYS_WID(125),SYS_HEI(124)));
    mRectTmp.append(QRect(SYS_WID(184),SYS_HEI(360),SYS_WID(125),SYS_HEI(124)));
    pRectSmartBtn.append(mRectTmp);

    mRectTmp.clear();
    mRectTmp.append(QRect(SYS_HEI(0),SYS_WID(0),SYS_HEI(0),SYS_WID(0)));
    mRectTmp.append(QRect(SYS_HEI(43),SYS_WID(47),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(184),SYS_WID(47),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(329),SYS_WID(47),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(43),SYS_WID(213),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(184),SYS_WID(213),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(329),SYS_WID(213),SYS_HEI(125),SYS_WID(124)));
    mRectTmp.append(QRect(SYS_HEI(184),SYS_WID(360),SYS_HEI(125),SYS_WID(124)));
    pRectSmartBtn.append(mRectTmp);

    pRectSmartWid.append(QRect(SYS_HEI(0),SYS_WID(0),SYS_HEI(505),SYS_WID(525)));
    pRectSmartWid.append(QRect(SYS_WID(0),SYS_HEI(0),SYS_WID(505),SYS_HEI(525)));
    pRectSmartWid.append(QRect(SYS_WID(0),SYS_HEI(0),SYS_WID(505),SYS_HEI(525)));
    pRectSmartWid.append(QRect(SYS_HEI(0),SYS_WID(0),SYS_HEI(505),SYS_WID(525)));

    OnViewDirChange(g_sysDb->g_startAngle);
}
void CSmartCeil12a::OnSmartChange(int mPos )
{
    if(g_sysDb->g_bMotionSimulate)
    {
        if(mPos < m_codeSmart.count())
            emit ComKeyCommand(m_codeSmart[mPos]);
        return;
    }

    if(g_sysDb->mNetTcpMode == TARGET_TCP_CLIENT)
    {
        unsigned short  buf[2];
        buf[0] = 0;
        buf[1] = mPos;
        g_taskComCtrl->CreateTask(CmdFuncSmart,buf,2);
        return;
    }

    if(mPos < SmartPos00 || mPos >= mSmartMax)
        return;

    switch(mPos)
    {
    case SmartPos00:
        SendCmdKey(0x0058);
        break;
    case SmartPos01:
        SendCmdKey(0x0050);
        break;
    case SmartPos02:
        SendCmdKey(0x0051);
        break;
    case SmartPos03:
        SendCmdKey(0x0052);
        break;
    case SmartPos04:
        SendCmdKey(0x0053);
        break;
    case SmartPos05:
        SendCmdKey(0x0054);
        break;
    case SmartPos06:
        SendCmdKey(0x0055);
        break;
    case SmartPos07:
        SendCmdKey(0x0056);
        break;
    default:
        return;
    }
}


void CSmartCeil12a::OnSelfRunCtrlSoft()
{
    if(m_iTimerCounter < g_sysDb->m_SelfRunInterval) //判断时间间隔是否到达
        return;

    m_iTimerCounter = 0;

    switch(m_iCtrlSoftStat)
    {
    case SELF_RUN_SOFT_00:
        SendCmdKey(0x0032);              //table min        //0x0032
        m_iCtrlSoftStat = SELF_RUN_SOFT_01;
        mCurBuf[0] =  g_sysDb->CurrentData[12];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_01:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[12];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_02;

        break;
    case SELF_RUN_SOFT_02:
        SendCmdKey(0x0022);              //tube min         0x0022
        m_iCtrlSoftStat = SELF_RUN_SOFT_03;
        mCurBuf[0] =  g_sysDb->CurrentData[8];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_03:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[8];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_04;

        break;
    case SELF_RUN_SOFT_04:
        SendCmdKey(0x0020);              //tube max         0x0020
        m_iCtrlSoftStat = SELF_RUN_SOFT_05;
        mCurBuf[0] =  g_sysDb->CurrentData[8];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_05:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[8];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_06;

        break;
    case SELF_RUN_SOFT_06:
        SendCmdKey(0x002c);              //det max          //0x002c
        m_iCtrlSoftStat = SELF_RUN_SOFT_07;
        mCurBuf[0] =  g_sysDb->CurrentData[11];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_07:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[11];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_08;

        break;

    case SELF_RUN_SOFT_08:
        SendCmdKey(0x002e);              //det min          //0x002e
        m_iCtrlSoftStat = SELF_RUN_SOFT_09;
        mCurBuf[0] =  g_sysDb->CurrentData[11];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_09:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[11];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_10;

        break;
    case SELF_RUN_SOFT_10:
        SendCmdKey(0x0026);              //sid min      0x0026
        m_iCtrlSoftStat = SELF_RUN_SOFT_11;
        mCurBuf[0] =  g_sysDb->CurrentData[9];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_11:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[9];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_12;

        break;

    case SELF_RUN_SOFT_12:
        SendCmdKey(0x0024);              //sid max      0x0024
        m_iCtrlSoftStat = SELF_RUN_SOFT_13;
        mCurBuf[0] =  g_sysDb->CurrentData[9];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_13:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[9];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_14;

        break;
    case SELF_RUN_SOFT_14:
        SendCmdKey(0x0036);              //bucky min        //0x0036
        m_iCtrlSoftStat = SELF_RUN_SOFT_15;
        mCurBuf[0] =  g_sysDb->CurrentData[13];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_15:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[13];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_16;

        break;

    case SELF_RUN_SOFT_16:
        SendCmdKey(0x0034);              //bucky max        //0x0034
        m_iCtrlSoftStat = SELF_RUN_SOFT_17;
        mCurBuf[0] =  g_sysDb->CurrentData[13];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_17:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[13];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_18;

        break;
    case SELF_RUN_SOFT_18:
        SendCmdKey(0x002a);              //angle min        //0x002a
        m_iCtrlSoftStat = SELF_RUN_SOFT_19;
        mCurBuf[0] =  g_sysDb->CurrentData[10];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_19:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[10];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_20;

        break;

    case SELF_RUN_SOFT_20:
        SendCmdKey(0x0028);              //angle max        //0x0028
        m_iCtrlSoftStat = SELF_RUN_SOFT_21;
        mCurBuf[0] =  g_sysDb->CurrentData[10];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_21:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[10];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_22;

        break;
    case SELF_RUN_SOFT_22:
        SendCmdKey(0x0030);              //table max        //0x0030
        m_iCtrlSoftStat = SELF_RUN_SOFT_23;
        mCurBuf[0] =  g_sysDb->CurrentData[12];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_23:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_sysDb->CurrentData[12];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_00;

        break;
    default:
        break;
    }

}
void CSmartCeil12a::OnSelfRunCtrlHard()
{

}
void CSmartCeil12a::OnSelfRunCtrlMach()
{


}


#endif
