#include "title_base.h"

#include "resource_manager.h"

CTitleBase::CTitleBase(QWidget *parent) :
    QWidget(parent)
{

    pLabelList.insert(TITLE_IDX_MARK,new QLabel(this));
    pLabelList.insert(TITLE_IDX_TIME,new QLabel(this));

    pLabelList[TITLE_IDX_MARK]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_TITLE_LOGO"));
    pLabelList[TITLE_IDX_TIME]->setStyleSheet(g_skinBase->GetStyleMapStr("ICON_TITLE_TIME_BACK"));

    pLabelList[TITLE_IDX_MARK]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    pLabelList[TITLE_IDX_TIME]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    timerTitleFresh = new QTimer(this);
    connect(timerTitleFresh,SIGNAL(timeout()),this,SLOT(OnTitleFresh()));
    timerTitleFresh->setInterval(TIME_INFO_FRESH);
}

void CTitleBase::showEvent(QShowEvent *)
{
    timerTitleFresh->start();
    RsMgr->VisibleWidgetAdd(this);
}
void CTitleBase::hideEvent(QHideEvent *)
{
    timerTitleFresh->stop();
    RsMgr->VisibleWidgetDel(this);
}
void CTitleBase::OnTitleFresh()
{
    QString mStr,temp,strDate,strTime;

    QTime ts=QTime::currentTime();
    QDate dt=QDate::currentDate();

    strDate.sprintf("%2d.%02d.%02d",dt.year(),dt.month(),dt.day());
    strTime.sprintf("%02d:%02d:%02d",ts.hour(),ts.minute(),ts.second());

    mStr = strDate.right(8);
    mStr += "\n";
    mStr += strTime;
    pLabelList[TITLE_IDX_TIME]->setText(mStr);

    /*
    if(g_dbsys.utility.mTubeTempShow)
    {
        mStr = QApplication::translate("CTitleBase", "Tube:");
        mStr += "\n";
        temp.setNum(g_systemDb->g_dbMachine.StateData[3] + g_dbsys.utility.mTemperatureAdj);
        mStr += temp;
        pLabelIcon[2]->setText(mStr);
    }else
    {
        pLabelIcon[2]->setText("");
    }
    */
}
void CTitleBase::mousePressEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        unsigned short keyBuf[2];
        keyBuf[0] =0;
        keyBuf[1] = EMG_STOP_V1;
        g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
    }
}
void CTitleBase::OnViewDirChange(int )
{
}
