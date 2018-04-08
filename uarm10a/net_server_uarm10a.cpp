#include "net_server_base10.h"

#include "resource_manager.h"

#include <QMessageBox>

CNetServer10::CNetServer10(QWidget *parent) :
    CNetServerBase(parent)
{
    setObjectName("CNetServer10");

    resize(SYS_HEI(200),SYS_WID(200));

    mFrame = new QFrame();
    mFrame->setGeometry(0,0,SYS_HEI(90),SYS_WID(200));
    mFrame->setStyleSheet("background-color: rgb(0, 0, 0)");

    QFont font;
    font.setPixelSize(SYS_FONT(24));

    pbRemote = new CButtonStable(mFrame);
    pbRemote->setGeometry(SYS_HEI(10), SYS_WID(20), SYS_HEI(70), SYS_WID(70));
    pbRemote->setFont(font);

    pbCtrl = new CButtonStable(mFrame);
    pbCtrl->setGeometry(SYS_HEI(10), SYS_WID(110), SYS_HEI(70), SYS_WID(70));
    pbCtrl->setFont(font);


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
}

void CNetServer10::OnCtrlChange(int idxCur,int func)
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
void CNetServer10::OnClientNumberChange(int mCount)
{

    if(mCount <= 0)
    {
        QString mStr;

        this->hide();

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

void CNetServer10::OnViewDirChange(int mViewDir)
{
    int m_rotAngle = 0;
    switch(mViewDir)
    {
    case VIEW_DIR_NORMAL:
        m_rotAngle = 90;
//        mView->setGeometry(0,0,SYS_WID(200),SYS_HEI(90));
//        mView->resetTransform();
//        mView->rotate(m_rotAngle);
        mFrame->setGeometry(0,0,SYS_WID(90),SYS_HEI(200));
        pbRemote->setGeometry(SYS_WID(10), SYS_HEI(20), SYS_WID(70), SYS_HEI(70));
        pbCtrl->setGeometry(SYS_WID(10), SYS_HEI(110), SYS_WID(70), SYS_HEI(70));
        break;
    case VIEW_DIR_LEFT:
        m_rotAngle = 0;
//        mView->setGeometry(0,0,SYS_WID(200),SYS_HEI(90));
//        mView->resetTransform();
//        mView->rotate(m_rotAngle);
        mFrame->setGeometry(0,0,SYS_WID(200),SYS_HEI(160));
        pbRemote->setGeometry(SYS_WID(110), SYS_HEI(65), SYS_WID(70), SYS_HEI(70));
        pbCtrl->setGeometry(SYS_WID(20), SYS_HEI(65), SYS_WID(70), SYS_HEI(70));
        break;
    case VIEW_DIR_RIGHT:
        m_rotAngle = 180;
//        mView->setGeometry(0,0,SYS_WID(200),SYS_HEI(90));
//        mView->resetTransform();
//        mView->rotate(m_rotAngle);
        mFrame->setGeometry(0,0,SYS_WID(200),SYS_HEI(160));
        pbRemote->setGeometry(SYS_WID(20), SYS_HEI(65), SYS_WID(70), SYS_HEI(70));
        pbCtrl->setGeometry(SYS_WID(110), SYS_HEI(65), SYS_WID(70), SYS_HEI(70));
        break;
    case VIEW_DIR_R180:
        m_rotAngle = 0;
        break;
    default:
        return;
    }
}
