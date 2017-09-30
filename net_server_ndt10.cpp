#include "net_server_ndt10.h"

#include "resource_manager.h"

#include <QMessageBox>

CNetServerNdt10::CNetServerNdt10(QWidget *parent) :
    CNetServerBase(parent)
{
    setObjectName("CNetServerNdt10");
    setStyleSheet("background: transparent");

    resize(SYS_WID(170),SYS_HEI(100));

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QColor(68,68,68)));

    mFrame = new QFrame();
    mFrame->resize(SYS_WID(100),SYS_HEI(170));
    //mFrame->resize(SYS_HEI(100),SYS_WID(170));
    mFrame->setStyleSheet("background: transparent");
    mFrame->setPalette(palette);

    QFont font;
    font.setPixelSize(SYS_FONT(24));

    pbRemote = new CButtonStable(mFrame);
    //pbRemote->setGeometry(SYS_WID(5), SYS_HEI(116), SYS_WID(66), SYS_HEI(88));
    pbRemote->setGeometry(SYS_WID(5), SYS_HEI(5), SYS_WID(70), SYS_HEI(74));
    //pbRemote->setGeometry(SYS_HEI(5), SYS_WID(15), SYS_HEI(66), SYS_WID(88));
    //pbRemote->setGeometry(SYS_HEI(5), SYS_WID(15), SYS_HEI(66), SYS_WID(88));

    pbRemote->setFont(font);

    pbCtrl = new CButtonStable(mFrame);
    //pbCtrl->setGeometry(SYS_WID(5), SYS_HEI(15), SYS_WID(66), SYS_HEI(88));
    //pbCtrl->setGeometry(SYS_HEI(5), SYS_WID(116), SYS_HEI(66), SYS_WID(88));
    pbCtrl->setGeometry(SYS_WID(5), SYS_HEI(90), SYS_WID(70), SYS_HEI(74));

    pbCtrl->setFont(font);

    mScene = new QGraphicsScene(this);
    mScene->addWidget(mFrame);

    mView  = new QGraphicsView(this);
    mView->setFocusPolicy(Qt::NoFocus);
    mView->setFrameShape(QFrame::NoFrame);
    mView->setFrameShadow(QFrame::Plain);
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //mView->setAlignment( Qt::AlignLeft | Qt::AlignTop);
    mView->setScene(mScene);
    mView->setGeometry(0,0,SYS_WID(170),SYS_HEI(90));
    mView->rotate(90);

    pbCtrl->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));
    pbCtrl->raise();

    pbRemote->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));
    pbRemote->raise();

    QString mStr;
    mStr = QApplication::translate("CNetServerBase", "Func:" );
    mStr += "\n";
    mStr += QApplication::translate("CNetServerBase", "view" );
    pbCtrl->setText(mStr);

    mStr = QApplication::translate("CNetServerBase", "Remote:" );
    mStr += "\n";
    pbRemote->setText(mStr);

    connect(pbCtrl,                 SIGNAL(pressed()),this,SLOT(OnNetClientCtrl()));
    connect(pbRemote,               SIGNAL(pressed()),this,SLOT(OnNetClientRemote()));

    translateFontSize(this);

    m_bSkipRunCheck = true;
}

void CNetServerNdt10::OnCtrlChange(int idxCur,int func)
{
    QString mStr,mInfo;

    if(idxCur < 0)
    {
        pbCtrl->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));

        mStr = QApplication::translate("CNetServerBase", "Func:" );
        mStr += "\n";
        mStr += QApplication::translate("CNetServerBase", "view" );
        pbCtrl->setText(mStr);

        mStr = QApplication::translate("CNetServerBase", "Remote:" );
        mStr += "\n";
        pbRemote->setText(mStr);
        return;
    }

    pbCtrl->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_001"));

    mStr = QApplication::translate("CNetServerBase", "Remote:" );
    mStr += "\n";
    mInfo.setNum(idxCur);
    mStr += mInfo;
    pbRemote->setText(mStr);

    mStr = QApplication::translate("CNetServerBase", "Func:" );
    mStr += "\n";

    switch(func)
    {
    case CLIENT_FUNC_READ:
        mStr += QApplication::translate("CNetServerBase", "view" );
        break;
    case CLIENT_FUNC_RUN:
        mStr += QApplication::translate("CNetServerBase", "run" );
        break;
    case CLIENT_FUNC_SET:
        mStr += QApplication::translate("CNetServerBase", "conf" );
        break;
    }

    pbCtrl->setText(mStr);

}
void CNetServerNdt10::OnClientNumberChange(int mCount)
{

    if(mCount <= 0)
    {
        QString mStr;

        //this->hide();

        pbCtrl->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_002"));

        mStr = QApplication::translate("CNetServerBase", "Func:" );
        mStr += "\n";
        mStr += QApplication::translate("CNetServerBase", "view" );
        pbCtrl->setText(mStr);

        mStr = QApplication::translate("CNetServerBase", "Remote:" );
        mStr += "\n";
        pbRemote->setText(mStr);

    }else
    {
        this->show();
    }
}

void CNetServerNdt10::ProcessNetMessage(unsigned short * pCmdBuf)
{

    switch(pCmdBuf[CMD_FUNC_ADDR])
    {
    case CMD_FUNC_SMART:
        emit SmartChange(pCmdBuf[FUNC_WKEY_ADDR]);
        break;
    case CMD_FUNC_WKEY:
        break;
    case NET_CMD_KEY_PRESS:
        emit RemoteKeyPressed(pCmdBuf[FUNC_WKEY_ADDR]);
        RsMgr->g_filmBase->SetKeySound();
        break;
    case NET_CMD_KEY_RELEASE:
        emit RemoteKeyReleased(pCmdBuf[FUNC_WKEY_ADDR]);
        break;
    case NET_CMD_KEY_PAGE:
        emit RemotePageChange(pCmdBuf[FUNC_WKEY_ADDR]);
        RsMgr->g_filmBase->SetKeySound();
        break;
    case CMD_FUNC_COMMD:
        break;
    case CMD_FUNC_PARAM:
        break;
    case CMD_FUNC_MOTO:
        break;
    case CMD_FUNC_REBOOT:
        MySystem("reboot");
        break;
    case MSG_CTRL_HEARTBEAT:
        m_iHeartAckCounter++;
        m_iHeartAckChecker = m_iHeartAckCounter;
        break;
    default:
        break;
    }
}
