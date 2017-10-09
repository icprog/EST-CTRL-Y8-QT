#include "net_client_ndt10.h"
#include "resource_manager.h"

CNetClientNdt10::CNetClientNdt10(QWidget *parent) :
    CNetClient10(parent)
{

    setObjectName("CNetClientNdt10");
    setStyleSheet("background: transparent");
    resize(SYS_WID(200),SYS_HEI(100));

    Q_ASSERT(mFrame != NULL);
    mFrame->resize(SYS_WID(100),SYS_HEI(200));
    mFrame->setStyleSheet("background: transparent");

    Q_ASSERT(pbCtrlIndex != NULL);
    Q_ASSERT(pbCtrlRequest != NULL);
    pbCtrlIndex->setGeometry(SYS_WID(5), SYS_HEI(15), SYS_WID(66), SYS_HEI(88));
    pbCtrlRequest->setGeometry(SYS_WID(5), SYS_HEI(116), SYS_WID(66), SYS_HEI(88));


}
