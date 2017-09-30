#include "smart_uarm8.h"
#include "resource_manager.h"

CSmartUarm8::CSmartUarm8(QWidget *parent) :
    CSmartBase8(parent)
{
    setObjectName("CSmartUarm8");

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    mSmartMax = UARM8_SMART_MAX;
    resize(SYS_WID(380),SYS_HEI(330));

    pBtnGroup[1]->setText(QApplication::translate("CSmartBase", "Stand 1.8m"));
    pBtnGroup[2]->setText(QApplication::translate("CSmartBase", "Stand 1.1m"));
    pBtnGroup[3]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[4]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[5]->setText(QApplication::translate("CSmartBase", "Table Position"));
    pBtnGroup[6]->setText(QApplication::translate("CSmartBase", "Table Slash"));
    pBtnGroup[0]->setText(QApplication::translate("CSmartBase", "Free Move"));

    for(int mIdx = mSmartMax - 1; mIdx > 0 ; mIdx--)
    {
        pBtnGroup[mIdx]->setGeometry(pBtnGroup[mIdx - 1]->geometry());
        pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + mIdx));
        pBtnGroup[mIdx]->setFont(font);
    }

    pBtnGroup[0]->setGeometry(pBtnGroup[7]->geometry());
    pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1));

    pBtnGroup[7]->setVisible(false);
    pBtnGroup[8]->setVisible(false);

    m_iSmartRunMax = 6;
    m_iSmartRun[0] = 1;
    m_iSmartRun[1] = 2;
    m_iSmartRun[2] = 3;
    m_iSmartRun[3] = 4;
    m_iSmartRun[4] = 5;
    m_iSmartRun[5] = 6;
    m_iSmartRun[6] = 4;
    m_iSmartRun[7] = 4;
    m_iSmartRun[8] = 5;
    m_iSmartRun[9] = 5;
    m_iSmartRun[10] = 6;
    m_iSmartRun[11] = 6;

    m_codeSmart[0] = 0x0050;
    m_codeSmart[1] = 0x0051;
    m_codeSmart[2] = 0x0052;
    m_codeSmart[3] = 0x0053;
    m_codeSmart[4] = 0x0054;
    m_codeSmart[5] = 0x0055;
    m_codeSmart[6] = 0x0056;
    m_codeSmart[7] = 0x0057;
}
void CSmartUarm8::OnSmartChange(int mPos )
{
    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_00)
        OnSmartChange00(mPos);

    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_01)
        OnSmartChange01(mPos);
}
void CSmartUarm8::OnSmartChange01(int mPos )
{

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)
    {
        unsigned short  buf[2];
        buf[0] = 0;
        buf[1] = mPos;
        g_taskComCtrl->CreateTask(CMD_FUNC_SMART,buf,2);
        return;
    }

    if(g_systemDb->g_bMotionSimulate)
    {
        emit ComKeyCommand(m_codeSmart[mPos]);
        return;
    }

    if(mPos < SMART_POS_00 || mPos >= mSmartMax)
        return;

    switch(mPos)
    {
    case SMART_POS_00:
        SendCmdKey(0x0058);
        break;
    case SMART_POS_01:
        SendCmdKey(0x0050);
        break;
    case SMART_POS_02:
        SendCmdKey(0x0051);
        break;
    case SMART_POS_03:
        SendCmdKey(0x0052);
        break;
    case SMART_POS_04:
        SendCmdKey(0x0053);
        break;
    case SMART_POS_05:
        SendCmdKey(0x0054);
        break;
    case SMART_POS_06:
        SendCmdKey(0x0055);
        break;
    case SMART_POS_07:
        SendCmdKey(0x0056);
        break;
    default:
        return;
    }

}
void CSmartUarm8::OnSmartChange00(int mPos )
{

    if(g_dbsys.utility.mNetTcpMode == TARGET_TCP_CLIENT)    //如果时网络客户端，直接将命令发出去
    {
        unsigned short  buf[2];
        buf[0] = 0;
        buf[1] = mPos;
        g_taskComCtrl->CreateTask(CMD_FUNC_SMART,buf,2);
        return;
    }

    if(g_systemDb->g_bMotionSimulate)           //如果时模拟模式，将命令发给模拟控制控件
    {
        emit ComKeyCommand(m_codeSmart[mPos]);
        return;
    }

    if(mPos < SMART_POS_00 || mPos >= mSmartMax)
        return;

    emit RunStatusChange(0 ,0);         //通知Fast模块切换图标

    int mRes;
    switch(mPos)
    {
    case SMART_POS_00:          //用于取消当前一键命令，根据当前一键位，发送不同取消指令
        SmartCancel();
        m_iSmartChannel = SMART_NULL;
        m_iSmartState = SMART_STATE_FREE;
        return;
    case SMART_POS_01:
        mRes = SmartChannelGet();
        if(mRes == SMART_STAND || mRes == SMART_STAND_SLASH )
        {
            SendCmdKey(0x0051);
            m_iSmartState = SMART_STATE_FREE;
            m_iSmartChannel = SMART_NULL;
            return;
        }
        m_iSmartChannel = SMART_STAND;
        break;
    case SMART_POS_02:
        m_iSmartChannel = SMART_STAND;
        break;
    case SMART_POS_03:
    case SMART_POS_04:
        m_iSmartChannel = SMART_STAND_SLASH;
        break;
    case SMART_POS_05:
        mRes = SmartChannelGet();
        if(mRes == SMART_TABLE || mRes == SMART_TABLE_SLASH )
        {
            SendCmdKey(0x0053);
            m_iSmartState = SMART_STATE_FREE;
            m_iSmartChannel = SMART_NULL;
            return;
        }
        m_iSmartChannel = SMART_TABLE;
        break;
    case SMART_POS_06:
        m_iSmartChannel = SMART_TABLE_SLASH;
        break;
    default:
        return;
    }

    m_iSmartTarget = mPos;
    m_iSmartState = SMART_STATE_PARAM_SEND;
    timerSmartRun->start();
}


void CSmartUarm8::OnSelfRunControl()
{

    if( m_iSmartState == SMART_STATE_CMD_WAIT)      //等待命令到位
    {
        if(true == SmartCmdWait())                          //执行完毕
        {
            m_iSmartState = SMART_STATE_SLASH_WAIT;
            m_iTimerCounter = 0;                    //重新计数
            return;
        }

        //    if(-1 == SmartCmdWait())                          //没有执行
        //    {
        //        m_iSmartState = SMART_STATE_SLASH_WAIT;
        //        m_iTimerCounter = 0;                    //重新计数
        //        return;
        //   }

    }

    if(m_iSmartState == SMART_STATE_SLASH_WAIT)
    {
        if(m_iTimerCounter < g_systemDb->m_SelfRunInterval) //判断时间间隔是否到达
            return;
        else
            m_iSmartState = SMART_STATE_FREE;
    }

    if(  m_iSmartState == SMART_STATE_FREE)     //发送快捷命令
    {
        OnSmartChange(m_iSmartRun[m_iSmartIndex]);

        m_iSmartIndex ++;
        if(m_iSmartIndex >= m_iSmartRunMax)
            m_iSmartIndex = 0;

        m_iSmartState = SMART_STATE_CMD_WAIT;   //执行完毕后，处于等待状态
    }
}

int CSmartUarm8::SmartCmdWait()
{
    if(g_systemDb->g_dbMachine.CurrentData[16] == 1 || g_systemDb->g_dbMachine.CurrentData[17] == 1)
        return true;    //一键为已经到位，还需要等待斜线到位

    return false;
}


void CSmartUarm8::OnSelfRunCtrlSoft()
{
    if(m_iTimerCounter < g_systemDb->m_SelfRunInterval) //判断时间间隔是否到达
        return;

    m_iTimerCounter = 0;

    switch(m_iCtrlSoftStat)
    {
    case SELF_RUN_SOFT_00:
        SendCmdKey(0x0022);              //HEI min        //0x0022
        m_iCtrlSoftStat = SELF_RUN_SOFT_01;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[8];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_01:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[8];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
        {
            m_iCtrlSoftStat = SELF_RUN_SOFT_02;
        }

        break;
    case SELF_RUN_SOFT_02:
        SendCmdKey(0x0020);              //HEI max         0x0020
        m_iCtrlSoftStat = SELF_RUN_SOFT_03;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[8];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_03:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[8];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_04;

        break;
    case SELF_RUN_SOFT_04:
        SendCmdKey(0x0020);              //tube max         0x0020
        m_iCtrlSoftStat = SELF_RUN_SOFT_05;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[8];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_05:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[8];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_06;

        break;
    case SELF_RUN_SOFT_06:
        SendCmdKey(0x002c);              //det max          //0x002c
        m_iCtrlSoftStat = SELF_RUN_SOFT_07;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[11];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_07:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[11];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_08;

        break;

    case SELF_RUN_SOFT_08:
        SendCmdKey(0x002e);              //det min          //0x002e
        m_iCtrlSoftStat = SELF_RUN_SOFT_09;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[11];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_09:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[11];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_10;

        break;
    case SELF_RUN_SOFT_10:
        SendCmdKey(0x0026);              //sid min      0x0026
        m_iCtrlSoftStat = SELF_RUN_SOFT_11;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[9];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_11:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[9];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_12;

        break;

    case SELF_RUN_SOFT_12:
        SendCmdKey(0x0024);              //sid max      0x0024
        m_iCtrlSoftStat = SELF_RUN_SOFT_13;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[9];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_13:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[9];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_14;

        break;
    case SELF_RUN_SOFT_14:
        SendCmdKey(0x0036);              //bucky min        //0x0036
        m_iCtrlSoftStat = SELF_RUN_SOFT_15;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[13];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_15:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[13];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_16;

        break;

    case SELF_RUN_SOFT_16:
        SendCmdKey(0x0034);              //bucky max        //0x0034
        m_iCtrlSoftStat = SELF_RUN_SOFT_17;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[13];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_17:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[13];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_18;

        break;
    case SELF_RUN_SOFT_18:
        SendCmdKey(0x002a);              //angle min        //0x002a
        m_iCtrlSoftStat = SELF_RUN_SOFT_19;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[10];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_19:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[10];

        if(mCurBuf[0]  >= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_20;

        break;

    case SELF_RUN_SOFT_20:
        SendCmdKey(0x0028);              //angle max        //0x0028
        m_iCtrlSoftStat = SELF_RUN_SOFT_21;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[10];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_21:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[10];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_22;

        break;
    case SELF_RUN_SOFT_22:
        SendCmdKey(0x0030);              //table max        //0x0030
        m_iCtrlSoftStat = SELF_RUN_SOFT_23;
        mCurBuf[0] =  g_systemDb->g_dbMachine.CurrentData[12];
        mCurBuf[1]  =  mCurBuf[0] ;
        break;

    case SELF_RUN_SOFT_23:
        mCurBuf[2]  = mCurBuf[1];
        mCurBuf[1]  = mCurBuf[0];
        mCurBuf[0]  =  g_systemDb->g_dbMachine.CurrentData[12];

        if(mCurBuf[0]  <= (mCurBuf[1] + mCurBuf[2] ) / 2)
            m_iCtrlSoftStat = SELF_RUN_SOFT_00;

        break;
    default:
        break;
    }

}
void CSmartUarm8::OnSelfRunCtrlHard()
{
    unsigned long  wData;

    wData =(unsigned short)g_systemDb->g_dbMachine.StateData[5] << 16;
    wData +=(unsigned short)g_systemDb->g_dbMachine.StateData[4];
}

void CSmartUarm8::OnSelfRunCtrlMach()
{


}
