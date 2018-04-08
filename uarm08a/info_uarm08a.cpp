#include "info_base8.h"
#include "resource_manager.h"

CInfoBase8::CInfoBase8(QWidget *parent) :
    CInfoBase(parent)
{

    setObjectName("CInfoBase8");

    resize(SYS_WID(300),SYS_HEI(50));

    lbMsgIcon->setGeometry(SYS_WID(0),  SYS_HEI(0), SYS_WID(50), SYS_HEI(50));
    lbMsgInfo->setGeometry(SYS_WID(50), SYS_HEI(0), SYS_WID(250), SYS_HEI(50));

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(208,235,245));
    setPalette(pal);

    OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_NORMAL);
}

void CInfoBase8::OnInfoFresh()
{

    CInfoBase::OnInfoFresh();

    if(m_iRunStatus != g_systemDb->g_dbMachine.StateData[2])
    {
        m_iRunStatus = g_systemDb->g_dbMachine.StateData[2];
        emit RunStatusChange(m_iRunStatus);
    }
}
