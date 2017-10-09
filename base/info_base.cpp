#include "info_base.h"
#include "resource_manager.h"

CInfoBase::CInfoBase(QWidget *parent) :
    QWidget(parent)
{

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    lbMsgIcon = new QFrame(this);

    lbMsgInfo = new QLabel(this);
    lbMsgInfo->setFont(font);
    lbMsgInfo->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    pmMsgIcon[INFO_PIC_CRITICAL] = new QString(g_skinBase->GetStyleMapStr("SYS_STR_CRITICAL"));
    pmMsgIcon[INFO_PIC_INFO]     = new QString(g_skinBase->GetStyleMapStr("SYS_STR_INFO"));
    pmMsgIcon[INFO_PIC_WARNING]  = new QString(g_skinBase->GetStyleMapStr("SYS_STR_WARNING"));
    pmMsgIcon[INFO_PIC_ERROR]    = new QString(g_skinBase->GetStyleMapStr("SYS_STR_ERROR"));
    pmMsgIcon[INFO_PIC_QUESTION] = new QString(g_skinBase->GetStyleMapStr("SYS_STR_QUESTION"));

    timerInfoFresh = new QTimer(this);
    connect(timerInfoFresh,SIGNAL(timeout()),this,SLOT(OnInfoFresh()));
    timerInfoFresh->setInterval(TIME_INFO_FRESH);

    //m_iPosiCaliValid = false;       //默认没有完成位置校正
    m_iPosiCaliValid = true;       //关闭位置检查功能

    m_iLimitMask    = 0xffff;
    m_iMsgNum       = 0;
    m_iMsgDispInx   = 0;

    m_iLevelPtr     = INFO_PIC_CRITICAL;

    for(int mIdx = 0 ; mIdx < INFO_SCROLL_MAX; mIdx++)
    {
        m_iMsgCode[mIdx]    = 0;        //用于显示的信息
        m_iMsgPicture[mIdx] = 0;        //用于显示的图片
    }

    for(int mIdx = 0 ; mIdx < INFO_PIC_MAX; mIdx++)
    {
        m_iMsgLevel[mIdx]   = 0;
    }
    setVisible(false);
}

void CInfoBase::OnViewDirChange(int )
{
}

void CInfoBase::InfoFresh(int msgCode,void * param)
{

    int mMsgPos = -1;

    for(int mIdx = 0 ;mIdx < m_iMsgNum ;mIdx++)
    {
        if(m_iMsgCode[mIdx] == msgCode)
        {
            mMsgPos = mIdx;
            break;
        }
    }

    if(mMsgPos == -1)
        return;

    m_iMsgInfo[mMsgPos] = GetInfoMsg(msgCode);
    m_iMsgInfo[mMsgPos] += *(QString*) param;

}
void CInfoBase::InfoAdd(int msgCode,void *  param)
{

    if(m_iMsgNum >= INFO_SCROLL_MAX)
        return;

    for(int mIdx = 0 ;mIdx < m_iMsgNum ;mIdx++)
    {
        if(m_iMsgCode[mIdx] == msgCode)
            return;
    }

    m_iMsgCode[m_iMsgNum] = msgCode;
    m_iMsgPicture[m_iMsgNum] = GetInfoIcon(msgCode,1);

    m_iMsgInfo[m_iMsgNum] = GetInfoMsg(msgCode);

    if(param != 0)
    {
        m_iMsgInfo[m_iMsgNum].append((QString *)param);
    }

    m_iMsgNum++;

}
void CInfoBase::InfoDel(int msgCode)
{

    int iErrorPos = -1;

    for(int mIdx = 0 ;mIdx < m_iMsgNum ;mIdx++)                 //exist error
    {
        if(m_iMsgCode[mIdx] == msgCode)
        {
            iErrorPos = mIdx;
            break;
        }
    }

    if(iErrorPos == -1)
        return;

    for(int mIdx = iErrorPos ;mIdx< m_iMsgNum ;mIdx++)
    {
        m_iMsgCode[mIdx] = m_iMsgCode[mIdx + 1];
        m_iMsgPicture[mIdx] = m_iMsgPicture[mIdx + 1] ;
        m_iMsgInfo[mIdx] = m_iMsgInfo[mIdx + 1] ;
    }

    if((m_iMsgDispInx >= iErrorPos) && (m_iMsgDispInx != 0))
    {
        m_iMsgDispInx--;
    }

    m_iMsgNum--;

    GetInfoIcon(msgCode,-1);

}


void CInfoBase::InfoDisplay()
{

    if(m_iMsgLevel[m_iLevelPtr] != 0)               //当前优先级有待显示信息
    {

        int mLevel = m_iMsgPicture[m_iMsgDispInx];  //获取当前待显示信息的等级

        while(mLevel != m_iLevelPtr)                //判断当前的等级是否需要显示
        {
            m_iMsgDispInx++;
            if(m_iMsgDispInx >= m_iMsgNum )
            {
                m_iMsgDispInx = 0;
                return;
            }

            mLevel = m_iMsgPicture[m_iMsgDispInx];
        }

        lbMsgIcon->setStyleSheet(*pmMsgIcon[m_iMsgPicture[m_iMsgDispInx]]);
        lbMsgInfo->setText(m_iMsgInfo[m_iMsgDispInx]);

        m_iMsgDispInx++;

        //if(m_iMsgDispInx >= m_iMsgLevel[m_iLevelPtr])
        if(m_iMsgDispInx >= m_iMsgNum)
            m_iMsgDispInx = 0;

        return;
    }

}
void CInfoBase::InfoMonitor()
{
    QString mBuf;

    if(g_dbsys.operation.bTimeNeedSet)              //分期付款到期
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_TIME_NEED_SET);
        return;
    }

    if(g_dbsys.operationx.keyNeed)              //分期付款到期
    {
        emit ViewChange(VIEW_INSTALL);
        return;
    }

    if(g_dbsys.operation.bTimeout)              //分期付款到期
    {
        emit ViewChange(VIEW_CONFIRM);
        return;
    }

    if( g_systemDb->g_bNoApp)                            //优先级 0
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_FIRMWARE_LOST);
        return;
    }

    if(!g_systemDb->g_bCommunicate)                     //优先级 1
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_COM_LOST);
        return;
    }else
    {
        OnInfoMsgCtrl(INFO_CTRL_DEL,MSG_COM_LOST);
    }

    //增加初始化过程中的错误提示
    unsigned int mInitState = g_systemDb->getInitState() ;
    switch(mInitState)
    {
    case INIT_STATE_NORMAL:
        break;
    case INIT_STATE_INFO:
        break;
    case INIT_STATE_WARNING:
        break;
    case INIT_STATE_ERROR:
        if(g_systemDb->getInitError() == INIT_ERROR_FILM_KEY)
        {

            mBuf.sprintf("%x",g_systemDb->getInitParam());
            OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_INIT_FILM_PRESS,&mBuf); //创建提示消息
            g_systemDb->setInitState(INIT_STATE_CLEAR,0,0);              //清除当前状态
            RsMgr->g_filmBase->filmCtrl(FILM_FUNC_STOP_RUN);        //停止薄膜按键执行
        }
        break;
    case INIT_STATE_FATAL:
        break;
    default:
        g_systemDb->setInitState(INIT_STATE_CLEAR,0,0);
        break;
    }

    if(g_systemDb->g_dbMachine.StateData[0])                //优先级 2
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_EMERGESTOP);
        return;
    }else
    {
        OnInfoMsgCtrl(INFO_CTRL_DEL,MSG_EMERGESTOP);
    }


    if(g_systemDb->g_dbMachine.StateData[1] & CAN1_LOST_MASK)                //优先级 4/can1 lost
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_CAN_LOST_1);
        return;
    }else
    {
        OnInfoMsgCtrl(INFO_CTRL_DEL,MSG_CAN_LOST_1);
    }

    if(g_systemDb->g_dbMachine.StateData[1] & CAN2_LOST_MASK)                //优先级 4/can2 lost
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_CAN_LOST_2);
        return;
    }else
    {
        OnInfoMsgCtrl(INFO_CTRL_DEL,MSG_CAN_LOST_2);
    }

    //位置或角度传感器出错
    //下位机没有完全支持，暂时屏蔽，20151119

    int mPositionState = (unsigned short)g_systemDb->g_dbMachine.StateData[7];

    if(mPositionState != 0)
    {
        //mBuf.sprintf(":%d",mPositionState);   //十进制显示错误代码
        mBuf.setNum(mPositionState,2);          //二进制显示错误代码
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_RUN_POSITION_ERR,&mBuf);
        OnInfoMsgCtrl(INFO_CTRL_FRE,MSG_RUN_POSITION_ERR,&mBuf);
        return;
    }else
    {
        OnInfoMsgCtrl(INFO_CTRL_DEL,MSG_RUN_POSITION_ERR);
    }


    if(g_motorMgr != 0 && m_iPosiCaliValid == false)
    {

        int mMotorLostIdx = g_motorMgr->motorCheck();

        if(mMotorLostIdx == 0)
        {
            m_iPosiCaliValid = true;
        }else
        {
            mBuf.setNum(mMotorLostIdx);
            OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_MOTOR_CALI_ERR,&mBuf);
            OnInfoMsgCtrl(INFO_CTRL_FRE,MSG_MOTOR_CALI_ERR,&mBuf);
        }
    }

    //限位故障处理
    unsigned short mLimitStatus;
    mLimitStatus =(unsigned short)g_systemDb->g_dbMachine.StateData[4];
    mLimitStatus &= m_iLimitMask;

    mBuf.setNum(mLimitStatus^ m_iLimitMask,16);
    if(mLimitStatus != m_iLimitMask)                              //优先级 3
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_LIMITIBIT,&mBuf);
        OnInfoMsgCtrl(INFO_CTRL_FRE,MSG_LIMITIBIT,&mBuf);
        return;
    }else
    {
        OnInfoMsgCtrl(INFO_CTRL_DEL,MSG_LIMITIBIT);
    }

    //EB90 1008  DATA[1] == 0Xaa for old version
    //EB90 1008  DATA[1] == 0Xaa & 0x0001 for new version
    if((g_systemDb->g_dbMachine.StateData[1] & SAFE_DISTANCE_MASK) || (g_systemDb->g_dbMachine.StateData[1]  == 0xaa))                //优先级 4
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_SAFEDISTANCE);
        return;
    }else
    {
        OnInfoMsgCtrl(INFO_CTRL_DEL,MSG_SAFEDISTANCE);
    }

    if(g_dbsys.dbsystem.mOperationTime >= g_dbsys.dbsystem.mMaintenanceTime)     //优先级 5
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_TIMEOVER);
        return;
    }

    if(g_systemDb->g_bAutoRunOpen)
    {
        if(g_dbsys.dbsystem.mSelfRunTime >= g_dbsys.dbsystem.mSelfRunTotal)     //优先级 5
        {
            OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_TEST_FINISHED);
        }else
        {
            OnInfoMsgCtrl(INFO_CTRL_DEL,MSG_TEST_FINISHED);
        }
    }

}
void CInfoBase::OnInfoFresh()
{

    InfoMonitor();
    InfoDisplay();
}
void CInfoBase::OnInfoMsgCtrl(int ctrl,int msgCode,void * msgParam)
{

    switch(ctrl)
    {
    case INFO_CTRL_ADD:
        InfoAdd(msgCode,msgParam);
        break;
    case INFO_CTRL_DEL:
        InfoDel(msgCode);
        break;
    case INFO_CTRL_FRE:
        InfoFresh(msgCode,msgParam);
        break;
    default:
        break;
    }

    InfoLevelFresh();
}
int CInfoBase::GetInfoIcon(int iconIdx,int det)
{

    switch(iconIdx)
    {
    case MSG_FIRMWARE_LOST:
        m_iMsgLevel[INFO_PIC_CRITICAL] += det;
        return INFO_PIC_CRITICAL;

    case MSG_TIME_NEED_SET:
    case MSG_CAN_LOST_1:
    case MSG_CAN_LOST_2:
    case MSG_RUN_POSITION_ERR:
    case MSG_INIT_FILM_PRESS:
    case MSG_COM_LOST:
    case MSG_EMERGESTOP:
        m_iMsgLevel[INFO_PIC_ERROR] += det;
        return INFO_PIC_ERROR;

    case MSG_MOTOR_CALI_ERR:
    case MSG_FAST_EXE_ERR:
    case MSG_FAST_SLASH_ERR:
    case MSG_FAST_NOT_SET:
    case MSG_FAST_SET_ERR:
    case MSG_LIMITIBIT:
    case MSG_TEST_FINISHED:
    case MSG_NET_RESTART:
    case MSG_SELF_RUN:
        m_iMsgLevel[INFO_PIC_WARNING] += det;
        return INFO_PIC_WARNING;

    case MSG_TIMEOVER:
    case MSG_NET_REMOTE_LOST:
        m_iMsgLevel[INFO_PIC_QUESTION] += det;
        return INFO_PIC_QUESTION;

    case MSG_TEMPERATURE:
    case MSG_DATE:
    case MSG_TIME:
    case MSG_SAFEDISTANCE:
    case MSG_NET_START_FAIL:
    case MSG_NET_SIGNAL_WARN:
    case MSG_MODE_DEMO:
    case MSG_NORMAL:
        m_iMsgLevel[INFO_PIC_INFO] += det;
        return INFO_PIC_INFO;
    default:
        return MSG_UNKNWON;
    }

}
QString CInfoBase::GetInfoMsg(int msgIdx)
{
    switch(msgIdx)
    {
    case MSG_TIME_NEED_SET:
        return QApplication::translate("CInfoBase", "System time battery low!");

    case MSG_FIRMWARE_LOST:
        return QApplication::translate("CInfoBase", "System firmware Lost!");

    case MSG_COM_LOST:
        return QApplication::translate("CInfoBase", "Communication failure!");

    case MSG_LIMITIBIT:
        return QApplication::translate("CInfoBase", "Limit detected!");

    case MSG_TIMEOVER:
        return QApplication::translate("CInfoBase", "Time to maintain!");

    case MSG_SAFEDISTANCE:
        return QApplication::translate("CInfoBase", "Distance Protection!");

    case MSG_NET_START_FAIL:
        return QApplication::translate("CInfoBase", "Network failure!");

    case MSG_NET_SIGNAL_WARN:
        return QApplication::translate("CInfoBase", "Network signal warnning!");

    case MSG_NET_REMOTE_LOST:
        return QApplication::translate("CInfoBase", "Network remote lost!");

    case MSG_NET_RESTART:
        return QApplication::translate("CInfoBase", "Network restart!");

    case MSG_EMERGESTOP:
        return QApplication::translate("CInfoBase", "Emergency pressed!");

    case MSG_MODE_DEMO:
        return QApplication::translate("CInfoBase", "Simulate Mode!");

    case MSG_SELF_RUN:
        return QApplication::translate("CInfoBase", "Self-run mode.");

    case MSG_TEMPERATURE:
        return QApplication::translate("CInfoBase", "Tube Temperature:");

    case MSG_DATE:
        return QApplication::translate("CInfoBase", "Date:");

    case MSG_TIME:
        return QApplication::translate("CInfoBase", "Time:");

    case MSG_NORMAL:
        return QApplication::translate("CInfoBase", "System run normal!");

    case MSG_FAST_NOT_SET:
        return QApplication::translate("CInfoBase", "Fast Position not set!");

    case MSG_TEST_FINISHED:
        return QApplication::translate("CInfoBase", "Self-Run Test Finished!");

    case MSG_FAST_SET_ERR:
        return QApplication::translate("CInfoBase", "Fast Position set err!");

    case MSG_FAST_EXE_ERR:
        return QApplication::translate("CInfoBase", "Fast Position run err!");

    case MSG_FAST_SLASH_ERR:
        return QApplication::translate("CInfoBase", "Fast slash err!");

    case MSG_INIT_FILM_PRESS:
        return QApplication::translate("CInfoBase", "KEY pressed during startup!");

    case MSG_RUN_POSITION_ERR:
        return QApplication::translate("CInfoBase", "Position feedback error!");

    case MSG_MOTOR_CALI_ERR:
        return QApplication::translate("CInfoBase", "Position cali lost!");

    case MSG_CAN_LOST_1:
        return QApplication::translate("CInfoBase", "CAN1 connection lost!");

    case MSG_CAN_LOST_2:
        return QApplication::translate("CInfoBase", "CAN2 connection lost!");

    default:
        return QApplication::translate("CInfoBase", "Message Unknown!");

    }
}

void CInfoBase::InfoLevelFresh()
{
    //有新消息加入后，重新刷新最高优先级
    for(int mIdx = 0 ; mIdx < INFO_PIC_MAX ;mIdx++)
    {
        if(m_iMsgLevel[mIdx] != 0)
        {
            m_iLevelPtr = mIdx;
            break;
        }
    }
}

void CInfoBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
    timerInfoFresh->start();
}
void CInfoBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
    timerInfoFresh->stop();
}
void CInfoBase::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"CInfoBase::mousePressEvent";

    if(event->type() == QEvent::MouseButtonPress)
    {
        unsigned short keyBuf[2];
        keyBuf[0] =0;
        keyBuf[1] = EMG_STOP_V1;
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
    }
}
