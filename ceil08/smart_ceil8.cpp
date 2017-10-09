#include "smart_ceil8.h"
#include "resource_manager.h"

CSmartCeil8::CSmartCeil8(QWidget *parent) :
    CSmartBase8(parent)
{
    setObjectName("CSmartCeil8");

    resize(SYS_WID(380),SYS_HEI(330));

    mSmartMax = CEIL8_SMART_MAX;

    pBtnGroup[1]->setText(QApplication::translate("CSmartBase", "Stand 1.8m"));
    pBtnGroup[2]->setText(QApplication::translate("CSmartBase", "Stand 1.1m"));
    pBtnGroup[3]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[4]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[5]->setText(QApplication::translate("CSmartBase", "Table Position"));
    pBtnGroup[6]->setText(QApplication::translate("CSmartBase", "Table Slash"));
    pBtnGroup[0]->setText(QApplication::translate("CSmartBase", "Free Move"));

    QFont font;
    font.setPixelSize(SYS_FONT(22));

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

    m_iSmartRunMax = 12;
    m_iSmartRun[0] = 1;
    m_iSmartRun[1] = 2;
    m_iSmartRun[2] = 3;
    m_iSmartRun[3] = 4;
    m_iSmartRun[4] = 5;
    m_iSmartRun[5] = 6;

    m_codeSmart[0] = 0x0050;
    m_codeSmart[1] = 0x0051;
    m_codeSmart[2] = 0x0052;
    m_codeSmart[3] = 0x0053;
    m_codeSmart[4] = 0x0054;
    m_codeSmart[5] = 0x0055;
    m_codeSmart[6] = 0x0056;
}
void CSmartCeil8::OnSelfRunControl()
{

    if( m_iSmartState == SMART_STATE_CMD_WAIT)      //等待命令到位
    {
        if(SmartCmdWait())                          //执行完毕
        {
            m_iSmartState = SMART_STATE_SLASH_WAIT;
            m_iTimerCounter = 0;                    //重新计数
        }
        return;
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

        m_iSmartState = SMART_STATE_CMD_WAIT;
    }
}
void CSmartCeil8::OnSmartChange(int mPos )
{
    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_00)
        OnSmartChange00(mPos);

    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_01)
        OnSmartChange01(mPos);
}
void CSmartCeil8::OnSmartChange01(int mPos )
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
void CSmartCeil8::OnSmartChange00(int mPos )
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

    emit RunStatusChange(0 ,0);

    int mRes;
    switch(mPos)
    {
    case SMART_POS_00:
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

int CSmartCeil8::SmartCmdWait()
{
    if(g_systemDb->g_dbMachine.CurrentData[16] == 1 || g_systemDb->g_dbMachine.CurrentData[17] == 1 || g_systemDb->g_dbMachine.CurrentData[18] == 1 )
        return true;    //一键为已经到位，还需要等待斜线到位

    return false;
}
