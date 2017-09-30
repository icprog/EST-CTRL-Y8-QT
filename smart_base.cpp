#include "smart_base.h"
#include "resource_manager.h"

CSmartBase::CSmartBase(QWidget *parent) :
    QWidget(parent)
{

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    //创建设置快捷按钮
    for(int mIdx = 0 ; mIdx < 3 ; mIdx++)
    {
        for(int mCtr = 0 ; mCtr < 3 ; mCtr++)
        {
            pBtnGroup[mIdx * 3 + mCtr] =  new CButtonStable(this);
            pBtnGroup[mIdx * 3 + mCtr]->setFlat(true);
            pBtnGroup[mIdx * 3 + mCtr]->setAutoDefault(false);
            pBtnGroup[mIdx * 3 + mCtr]->setFont(font);

            connect(pBtnGroup[mIdx * 3 + mCtr],SIGNAL(pressed()),this,SLOT(OnSmartPressed()));
        }
    }

    m_iTimerCounter = 0;
    m_iSmartIndex   = 0;
    m_iSmartRunMax  = 0;

    m_iCtrlSoftStat = 0;

    for(int mIdx = 0 ; mIdx < M_CUR_BUF_MAX; mIdx++)
        mCurBuf[mIdx] = 0;


    for(int mIdx = 0 ; mIdx < SMART_RUN_MAX ; mIdx++)
        m_iSmartRun[mIdx] = 0;

    timerAutoRun = new QTimer(this);
    timerAutoRun->setInterval(1000);            //以秒为单位，与m_SelfRunInterval比较
    connect(timerAutoRun,SIGNAL(timeout()),this,SLOT(OnSmartFresh()));
    timerAutoRun->start();

    setVisible(false);

}

void CSmartBase::showEvent(QShowEvent *)
{

    RsMgr->VisibleWidgetAdd(this);
}
void CSmartBase::hideEvent(QHideEvent *)
{

    RsMgr->VisibleWidgetDel(this);
}
void CSmartBase::mousePressEvent(QMouseEvent */*event*/)
{
    qDebug()<<"CSmartBase::mousePressEvent";
}


void CSmartBase::SendCmdKey(int mKey)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = mKey;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}

void CSmartBase::OnSmartChange(int)
{
}
void CSmartBase::OnKeyPressed(int)
{

}
void CSmartBase::OnSmartPressed(int mKeyIdx)
{

    emit PopupHide(this );          //隐藏Popup

    hide();                         //隐藏自己

    OnSmartChange(mKeyIdx);           //发射快捷按钮消息

    g_systemDb->setPopSmartShowState(false);    //记录已经关闭Pop的信息

    return;

}
//按钮按下处理
void CSmartBase::OnSmartPressed()
{
    for(int mIdx = 0; mIdx < mSmartMax ;mIdx++)
    {
        if(pBtnGroup[mIdx] == sender())
        {
            OnSmartPressed(mIdx);

            return;
        }
    }
}

//快捷状态切换
void CSmartBase::OnStatusChange(int mPos)
{
    if( (mPos < 0) || (mPos > mSmartMax))
        return;

    if(0 == mPos)
        emit RunStatusChange(mPos,(QPushButton*)(0));
    else
        emit RunStatusChange(mPos,pBtnGroup[mPos]);
}

void CSmartBase::OnViewDirChange(int)
{

}

void CSmartBase::OnSmartFresh()
{
    if(!g_systemDb->g_bAutoRunOpen)
        return;

    if(g_systemDb->isAutoRun())
    {
        m_iTimerCounter++;
        switch(g_systemDb->g_iAutoRunMode)
        {
        case AUTO_RUN_MODE_FAST:
            OnSelfRunControl();
            break;

        case AUTO_RUN_MODE_SOFT:
            OnSelfRunCtrlSoft();
            break;

        case AUTO_RUN_MODE_SWITCH:
            OnSelfRunCtrlHard();
            break;

        case AUTO_RUN_MODE_HARD:
            OnSelfRunCtrlMach();
            break;
        default:
            break;
        }

        emit InfoMsgCtrl(INFO_CTRL_ADD,MSG_SELF_RUN);
    }else
    {
        emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_SELF_RUN);
        g_systemDb->g_bAutoRunOpen = false;
        m_iSmartState = SMART_STATE_FREE;
    }
}

void CSmartBase::OnSelfRunControl()
{

}
int CSmartBase::SmartCmdWait()
{

    return false;
}

void CSmartBase::OnSelfRunCtrlSoft()
{

}
void CSmartBase::OnSelfRunCtrlHard()
{

}
void CSmartBase::OnSelfRunCtrlMach()
{


}
