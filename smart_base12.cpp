#include "smart_base12.h"

#include "resource_manager.h"

CSmartBase12::CSmartBase12(QWidget *parent)
    :CSmartBase(parent)
{

    m_iSmartState = SMART_STATE_FREE;
    m_iSmartChannel = SMART_NULL;

    timerMenuMsgWaig = new QTimer(this);
    timerMenuMsgWaig->setSingleShot(true);
    timerMenuMsgWaig->setInterval(4000);
    connect(timerMenuMsgWaig,SIGNAL(timeout()),this,SLOT(OnMenuMsgWait()));

    timerSmartRun = new QTimer(this);
    timerSmartRun->setInterval(100);
    connect(timerSmartRun,SIGNAL(timeout()),this,SLOT(OnTimerSmartRun()));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(70,90,130,150)");
    }

    OnViewDirChange(g_systemDb->g_startAngle);
}

//根据快捷按键的通道，发送下位机一键动作指令。
//立位与立位斜线，发送0x0051
//卧位与卧位斜线，发送0x0053
void CSmartBase12::SmartCmdSend()
{
    unsigned short buf[10];
    buf[0] = 0;

    switch(m_iSmartChannel)
    {
    case SMART_STAND:
        buf[1] = 0x0051;
        break;
    case SMART_STAND_SLASH:
        buf[1] = 0x0051;
        break;
    case SMART_TABLE:
        buf[1] = 0x0053;
        break;
    case SMART_TABLE_SLASH:
        buf[1] = 0x0053;
        break;
    default:
        return;
    }

    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,buf,2);

}

//等待命令执行完成
//先判断一键动作是否执行到位，后判断是否继续执行斜线动作
int CSmartBase12::SmartCmdWait()
{

    if(g_systemDb->g_dbMachine.CurrentData[16] == 1 || g_systemDb->g_dbMachine.CurrentData[17] == 1)
    {
        if(SMART_STAND == m_iSmartChannel || SMART_TABLE == m_iSmartChannel)
        {
            emit RunStatusChange(m_iSmartTarget ,0);
            return 0;   //目标就是一键立位或一键卧位，无后续动作
        }

        return 1;       //一键为已经到位，还需要等待斜线到位
    }

    return -1;      //一键立位或一键卧位都没有到位

}
//有按键按下时，取消当前正在执行的快捷按钮
void CSmartBase12::OnKeyPressed(int)
{
    timerSmartRun->stop();
    m_iSmartChannel = SMART_NULL;
    m_iSmartState = SMART_STATE_FREE;

}
void CSmartBase12::SmartSlashSend()
{
    CSmartBase::SendCmdKey(0x0055);     //直接发送斜线指令
}

//等待斜线执行完成
//斜线执行完成标志为CurrentData[18]
int CSmartBase12::SmartSlashWait()
{
    if(g_systemDb->g_dbMachine.CurrentData[18] == 1)    //执行完毕
    {
        emit RunStatusChange(m_iSmartTarget ,0);
        return 1;
    }

    return 0;
}
//等待参数发送完毕
bool CSmartBase12::SmartParamWait()
{
    if(!g_systemDb->g_bDataSaved)
        return false;

    return true;
}
void CSmartBase12::OnTimerSmartRun()
{
    int mRes;

    switch(m_iSmartState)
    {
    case SMART_STATE_FREE:                          //可以执行下一个快捷命令
        break;
    case SMART_STATE_PARAM_SEND:
        ReloadSmartData(m_iSmartTarget);            //根据当前快捷按键，重新下载位置代码
        m_iSmartState = SMART_STATE_PARAM_WAIT;
        m_iWaitCounter = 0;
        break;
    case SMART_STATE_PARAM_WAIT:                    //等待下位己确认发送的参数
        if(!SmartParamWait())                       //连续多次确认失败，给出提示消息
        {
            m_iWaitCounter++;
            if(m_iWaitCounter > 5)               /*间隔40ms，5次200ms*/
            {
                emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_FAST_SET_ERR);
                m_iSmartState = SMART_STATE_FREE;
                timerSmartRun->stop();              //立位已经到位，停止定时器
            }
            return;
        }
        emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_FAST_SET_ERR);
        m_iSmartState = SMART_STATE_CMD_SEND;
        break;
    case SMART_STATE_CMD_SEND:
        SmartCmdSend();
        m_iSmartState = SMART_STATE_CMD_WAIT;
        m_iWaitCounter = 0;
        break;
    case SMART_STATE_CMD_WAIT:
        mRes = SmartCmdWait();              //等待命令发送完成
        if(mRes == -1)                      //命令没有完成
        {
            m_iWaitCounter++;
            if(m_iWaitCounter > 200)
            {
                emit InfoMsgCtrl(INFO_CTRL_ADD,MSG_FAST_EXE_ERR);
                m_iSmartState = SMART_STATE_FREE;
                timerSmartRun->stop();              //立位已经到位，停止定时器
            }
            return;
        }

        emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_FAST_EXE_ERR);

        if(mRes == 0)                           //命令已经完成，且无后续命令
        {
            m_iSmartState = SMART_STATE_FREE;
            timerSmartRun->stop();              //立位已经到位，停止定时器
            return;
        }

        if(mRes == 1)                           //命令已经完成，但仍有后续命令
        {
            m_iSmartState = SMART_STATE_SLASH_SEND;
            break;
        }
        break;
    case SMART_STATE_SLASH_SEND:
        SmartSlashSend();
        m_iSmartState = SMART_STATE_SLASH_WAIT;
        m_iWaitCounter = 0;
        break;
    case SMART_STATE_SLASH_WAIT:
        mRes = SmartSlashWait();
        if(mRes == 0)
        {
            m_iWaitCounter++;
            if(m_iWaitCounter > 200)
            {
                emit InfoMsgCtrl(INFO_CTRL_ADD,MSG_FAST_SLASH_ERR);
                m_iSmartChannel = SMART_NULL;
                m_iSmartState = SMART_STATE_FREE;
                timerSmartRun->stop();              //立位已经到位，停止定时器
            }
            return;
        }

        emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_FAST_SLASH_ERR);
        m_iSmartState = SMART_STATE_FREE;
        timerSmartRun->stop();
        break;
    default:
        emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_UNKNWON);
        break;
    }
}
int CSmartBase12::SmartChannelGet()
{
    if(g_systemDb->g_dbMachine.CurrentData[16] == 2 ||
            g_systemDb->g_dbMachine.CurrentData[17] == 2 ||
            g_systemDb->g_dbMachine.CurrentData[18] == 2 ) //正在执行
        return SMART_NULL;

    if(g_systemDb->g_dbMachine.CurrentData[18] == 1)    //斜线到位
    {
        if(g_systemDb->g_dbMachine.CurrentData[16] == 1)
            return SMART_STAND_SLASH;

        if(g_systemDb->g_dbMachine.CurrentData[17] == 1)
            return SMART_TABLE_SLASH;
    }

    if( g_systemDb->g_dbMachine.CurrentData[16] == 1)
        return SMART_STAND;

    if( g_systemDb->g_dbMachine.CurrentData[17] == 1)
        return SMART_TABLE;

    return SMART_NULL;
}

void CSmartBase12::SmartCancel()
{
    int mRes = SmartChannelGet();

    switch(mRes)
    {
    case SMART_STAND_SLASH:
    case SMART_STAND:
        SendCmdKey(0x0051);
        break;
    case SMART_TABLE:
    case SMART_TABLE_SLASH:
        SendCmdKey(0x0053);
        break;
    case SMART_NULL:
    default:
        SendCmdKey(0x0050);
        break;
    }
}
void CSmartBase12::OnMenuMsgWait()
{
    emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_FAST_NOT_SET);
}

void CSmartBase12::OnSelfRunControl()
{

    if(m_iSmartState != SMART_STATE_FREE)
    {
        m_iTimerCounter = 0;
        return;
    }

    if(m_iTimerCounter >= g_systemDb->m_SelfRunInterval)
    {
        m_iTimerCounter = 0;

        OnSmartChange(m_iSmartRun[m_iSmartIndex]);

        m_iSmartIndex++;

        if(m_iSmartIndex >= m_iSmartRunMax)
            m_iSmartIndex = 0;
    }
}

void CSmartBase12::ReloadSmartData(int mSmartPos)
{
    unsigned short  buf[10];
    buf[0] = 0;
    unsigned short * pDataBuf;
    pDataBuf = g_systemDb->FastDataGet(mSmartPos);

    if(!pDataBuf)
    {
        emit InfoMsgCtrl(INFO_CTRL_ADD,MSG_FAST_NOT_SET);
        timerMenuMsgWaig->start();
        return;
    }

    for(int mIdx = 2 ; mIdx < 10; mIdx++)
        buf[mIdx] = pDataBuf[mIdx - 2];

    g_systemDb->g_bDataSaved = false;

    switch(m_iSmartChannel)
    {
    case SMART_STAND:
    case SMART_STAND_SLASH:
        buf[1] = 0x0050;
        break;
    case SMART_TABLE:
    case SMART_TABLE_SLASH:
        buf[1] = 0x0051;
        break;
    default:
        return;
    }

    g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,buf,10);
}
void CSmartBase12::OnViewDirChange(int sAngle)
{
    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(505),SYS_WID(525));
        pBtnGroup[0]->setGeometry(SYS_HEI(43),SYS_WID(47),SYS_HEI(125),SYS_WID(124));
        pBtnGroup[1]->setGeometry(SYS_HEI(184),SYS_WID(47),SYS_HEI(125),SYS_WID(124));
        pBtnGroup[2]->setGeometry(SYS_HEI(329),SYS_WID(47),SYS_HEI(125),SYS_WID(124));
        pBtnGroup[3]->setGeometry(SYS_HEI(43),SYS_WID(213),SYS_HEI(125),SYS_WID(124));
        pBtnGroup[4]->setGeometry(SYS_HEI(184),SYS_WID(213),SYS_HEI(125),SYS_WID(124));
        pBtnGroup[5]->setGeometry(SYS_HEI(329),SYS_WID(213),SYS_HEI(125),SYS_WID(124));
        pBtnGroup[6]->setGeometry(SYS_HEI(43),SYS_WID(360),SYS_HEI(125),SYS_WID(124));
        pBtnGroup[7]->setGeometry(SYS_HEI(184),SYS_WID(360),SYS_HEI(125),SYS_WID(124));
        pBtnGroup[8]->setGeometry(SYS_HEI(329),SYS_WID(360),SYS_HEI(125),SYS_WID(124));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(505),SYS_HEI(525));
        pBtnGroup[0]->setGeometry(SYS_WID(43),SYS_HEI(47),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[1]->setGeometry(SYS_WID(184),SYS_HEI(47),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[2]->setGeometry(SYS_WID(329),SYS_HEI(47),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[3]->setGeometry(SYS_WID(43),SYS_HEI(213),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[4]->setGeometry(SYS_WID(184),SYS_HEI(213),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[5]->setGeometry(SYS_WID(329),SYS_HEI(213),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[6]->setGeometry(SYS_WID(43),SYS_HEI(360),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[7]->setGeometry(SYS_WID(184),SYS_HEI(360),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[8]->setGeometry(SYS_WID(329),SYS_HEI(360),SYS_WID(125),SYS_HEI(124));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(505),SYS_HEI(525));
        pBtnGroup[0]->setGeometry(SYS_WID(43),SYS_HEI(47),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[1]->setGeometry(SYS_WID(184),SYS_HEI(47),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[2]->setGeometry(SYS_WID(329),SYS_HEI(47),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[3]->setGeometry(SYS_WID(43),SYS_HEI(213),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[4]->setGeometry(SYS_WID(184),SYS_HEI(213),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[5]->setGeometry(SYS_WID(329),SYS_HEI(213),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[6]->setGeometry(SYS_WID(43),SYS_HEI(360),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[7]->setGeometry(SYS_WID(184),SYS_HEI(360),SYS_WID(125),SYS_HEI(124));
        pBtnGroup[8]->setGeometry(SYS_WID(329),SYS_HEI(360),SYS_WID(125),SYS_HEI(124));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }
}
void CSmartBase12::mousePressEvent(QMouseEvent */*event*/)
{
    emit PopupHide(this );          //隐藏Popup

    hide();                         //隐藏自己

    g_systemDb->setPopSmartShowState(false);    //记录已经关闭Pop的信息

    return;

}
