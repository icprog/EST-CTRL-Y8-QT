#include "info_base_ndt8.h"
#include "resource_manager.h"

CInfoBaseNdt8::CInfoBaseNdt8(QWidget *parent) :
    CInfoBase(parent)
{

    setObjectName("CInfoBaseNdt8");

    resize(SYS_WID(86),SYS_HEI(600));

    lbMsgIcon->setGeometry(SYS_WID(18),  SYS_HEI(0), SYS_WID(50), SYS_HEI(50));
    lbMsgInfo->setGeometry(SYS_WID(18), SYS_HEI(50), SYS_WID(50), SYS_HEI(500));

    QFont font;
    font.setPointSize(32);
    lbMsgInfo->setFont(font);
    //lbMsgInfo->setScaledContents(true);
    lbMsgInfo->setWordWrap(true);

    //QPalette pal = palette();
    //pal.setColor(QPalette::Background, QColor(208,235,245));
    //setPalette(pal);

    OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_NORMAL);
}

void CInfoBaseNdt8::OnInfoFresh()
{

    CInfoBase::OnInfoFresh();

    if(m_iRunStatus != g_systemDb->g_dbMachine.StateData[2])
    {
        m_iRunStatus = g_systemDb->g_dbMachine.StateData[2];
        emit RunStatusChange(m_iRunStatus);
    }
}
