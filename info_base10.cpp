#include "resource_manager.h"
#include "info_base10.h"


CInfoBase10::CInfoBase10(QWidget *parent) :
    CInfoBase(parent)
{

    setObjectName("CInfoBase10");

    resize(SYS_HEI(300),SYS_WID(50));

    lbMsgIcon->setGeometry(SYS_HEI(5),  SYS_WID(0), SYS_HEI(51),  SYS_WID(50));
    lbMsgInfo->setGeometry(SYS_HEI(89), SYS_WID(0), SYS_HEI(211), SYS_WID(50));

    if(g_dbsys.utility.mTubeTempShow)
    {
        OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_TEMPERATURE);
    }

    OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_DATE);
    OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_TIME);

    setStyleSheet("background-color : lightGray");
}

void CInfoBase10::OnInfoFresh()
{

    CInfoBase::OnInfoFresh();

    QString strTemp;
    if(g_dbsys.utility.mTubeTempShow)
    {
        strTemp.setNum(g_systemDb->g_dbMachine.StateData[3] + g_dbsys.utility.mTemperatureAdj);
        OnInfoMsgCtrl(INFO_CTRL_FRE,MSG_TEMPERATURE,&strTemp);
    }

    QTime ts = QTime::currentTime();
    QDate dt = QDate::currentDate();

    QString strDate,strTime;

    strDate.sprintf("%02d.%02d.%02d ",dt.year(),dt.month(),dt.day());
    OnInfoMsgCtrl(INFO_CTRL_FRE,MSG_DATE,&strDate);

    strTime.sprintf("%02d:%02d",ts.hour(),ts.minute());
    OnInfoMsgCtrl(INFO_CTRL_FRE,MSG_TIME,&strTime);

    if(m_iRunStatus != g_systemDb->g_dbMachine.StateData[2])
    {
        m_iRunStatus = g_systemDb->g_dbMachine.StateData[2];
        emit RunStatusChange(m_iRunStatus);
    }


}

