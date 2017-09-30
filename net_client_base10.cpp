#include "net_client_base10.h"
#include "resource_manager.h"

CNetClient10::CNetClient10(QWidget *parent) :
    CNetClientBase(parent)
{
    setObjectName("CNetClient10");

    resize(SYS_WID(200),SYS_HEI(90));

    QFont font;
    font.setPixelSize(SYS_FONT(18));

    mFrame = new QFrame();
    mFrame->resize(SYS_WID(90),SYS_HEI(200));
    mFrame->setStyleSheet("background-color: rgb(0, 0, 0)");

    pbCtrlIndex = new CButtonStable(mFrame);
    pbCtrlIndex->setGeometry(SYS_WID(10), SYS_HEI(15), SYS_WID(70), SYS_HEI(70));
    pbCtrlIndex->setFont(font);

    pbCtrlRequest = new CButtonStable(mFrame);
    pbCtrlRequest->setGeometry(SYS_WID(10), SYS_HEI(100), SYS_WID(70), SYS_HEI(70));
    pbCtrlRequest->setFont(font);

    mScene = new QGraphicsScene(this);
    mScene->addWidget(mFrame);

    mView  = new QGraphicsView(this);
    mView->setFocusPolicy(Qt::NoFocus);
    mView->setFrameShape(QFrame::NoFrame);
    mView->setFrameShadow(QFrame::Plain);
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mView->setScene(mScene);
    mView->rotate(90);

    pbCtrlIndex->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));
    pbCtrlIndex->setText(QApplication::translate("CNetClientBase", "Comm\nFail" ));

    pbCtrlRequest->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));
    pbCtrlRequest->setText(QApplication::translate("CNetClientBase", "Trying\n..." ));

    connect(pbCtrlIndex,    SIGNAL(pressed()),this,SLOT(OnClientCtrlPressed()));
    connect(pbCtrlRequest,  SIGNAL(pressed()),this,SLOT(OnClientCtrlPressed()));

}
