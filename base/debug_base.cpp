#include "debug_base.h"
#include "resource_manager.h"

CDebugBase::CDebugBase(QWidget *parent) :
    CSystemBase(parent)
{
    setObjectName("CDebugBase");

    m_lLimitBuf = 0;        //默认参数
    m_iMotorMax = 0;        //默认参数
    m_iBtnIdx   = -1;       //无效

    pLineAry[0] = new QFrame(this);
    pLineAry[0]->setGeometry(QRect(50, 155, 500, 10));
    pLineAry[0]->setFrameShape(QFrame::HLine);
    pLineAry[0]->setFrameShadow(QFrame::Sunken);
    pLineAry[1] = new QFrame(this);
    pLineAry[1]->setGeometry(QRect(50, 218, 500, 10));
    pLineAry[1]->setFrameShape(QFrame::HLine);
    pLineAry[1]->setFrameShadow(QFrame::Sunken);
    pLineAry[2] = new QFrame(this);
    pLineAry[2]->setGeometry(QRect(50, 400, 500, 10));
    pLineAry[2]->setFrameShape(QFrame::HLine);
    pLineAry[2]->setFrameShadow(QFrame::Sunken);

    QString mStr;
    for(int mIdx = 0 ; mIdx < CHANNEL_MAX ; mIdx++)
    {
        pLimitFrame[2 * mIdx] = new QFrame(this);
        pLimitFrame[2 * mIdx]->setGeometry(    QRect(65 + mIdx * 95, 130, 20, 20));
        pLimitFrame[2 * mIdx]->setStyleSheet("QFrame { background-color : white;}");

        pLimitFrame[2 * mIdx + 1] = new QFrame(this);
        pLimitFrame[2 * mIdx + 1]->setGeometry(QRect(65 + mIdx * 95, 100, 20, 20));
        pLimitFrame[2 * mIdx + 1]->setStyleSheet("QFrame { background-color : white;}");

        mStr.sprintf("IN%d",2 * mIdx + 1);
        pLimitText[2 * mIdx] = new QLabel(this);
        pLimitText[2 * mIdx]->setGeometry(    QRect(15 + mIdx * 95, 130, 61, 20));
        pLimitText[2 * mIdx]->lower();
        pLimitText[2 * mIdx]->setText(mStr);

        mStr.sprintf("IN%d",2 * mIdx + 2);
        pLimitText[2 * mIdx + 1] = new QLabel(this);
        pLimitText[2 * mIdx + 1]->setGeometry(QRect(15 + mIdx * 95, 100, 61, 20));
        pLimitText[2 * mIdx + 1]->lower();
        pLimitText[2 * mIdx + 1]->setText(mStr);

        pLabelAd[mIdx] = new QLabel(this);
        pLabelAd[mIdx]->setGeometry(QRect(25 + mIdx * 95, 180, 75, 28));
        pLabelAd[mIdx]->setStyleSheet("background-color : yellow ; color : blue ; border : 1px solid black");
        pLabelAd[mIdx]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        pBtnGroup[2 * mIdx] = new CButtonStable(this);
        pBtnGroup[2 * mIdx]->setGeometry(    QRect(25 + mIdx * 95, 320, 75, 75));
        connect(pBtnGroup[2 * mIdx],SIGNAL(pressed()),this,SLOT(OnDebugPressed()));
        connect(pBtnGroup[2 * mIdx],SIGNAL(released()),this,SLOT(OnDebugReleased()));

        pBtnGroup[2 * mIdx + 1] = new CButtonStable(this);
        pBtnGroup[2 * mIdx + 1]->setGeometry(QRect(25 + mIdx * 95, 230, 75, 75));
        connect(pBtnGroup[2 * mIdx + 1],SIGNAL(pressed()),this,SLOT(OnDebugPressed()));
        connect(pBtnGroup[2 * mIdx + 1],SIGNAL(released()),this,SLOT(OnDebugReleased()));
    }

    timerDebugRefresh = new QTimer(this);
    connect(timerDebugRefresh,SIGNAL(timeout()),this,SLOT(OnDebugFresh()));

}


void CDebugBase::SendCmdKey(int mKey)
{
    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = mKey;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}

void CDebugBase::showEvent(QShowEvent *event)
{
    //jsy 20150812 屏蔽无任何保护的调试模式
    //bufComMessage[0]=0;
    //bufComMessage[1]=SYS_CMD_DEBUG;
    //g_taskComCtrl->CreateTask(CMD_FUNC_COMMD,bufComMessage,SYS_CMD_LENGTH);

    UpdateSampleData();

    timerDebugRefresh->start(TIME_SCREEN_FRESH);

    grabKeyboard();

    CSystemBase::showEvent(event);
}

void CDebugBase::hideEvent(QHideEvent *event)
{
    timerDebugRefresh->stop();

    releaseKeyboard();

    CSystemBase::hideEvent(event);
}
void CDebugBase::keyPressEvent( QKeyEvent * event )
{

    int mKey = event->key();
    switch (mKey) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        break;

    case Qt::Key_Backspace:
        break;
    case Qt::Key_Close:
        break;
    case Qt::Key_Escape:
        this->hide();
        g_mainSetting->setSceneWidget(RsMgr->g_systemMenu);
        break;
    case Qt::Key_Tab:
        break;
    default:
        break;
    }
}
void CDebugBase::UpdateSampleData()
{

}
void CDebugBase::OnDebugFresh()
{

}
void CDebugBase::OnDebugPressed()
{

}
void CDebugBase::OnDebugReleased()
{

}
