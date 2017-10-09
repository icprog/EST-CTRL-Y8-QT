
#include "system_imepad.h"
#include "resource_manager.h"

CSystemImepad::CSystemImepad(QWidget* parent,int bCanClose):
    QWidget(parent)
{

    setObjectName("CSystemImepad");

    resize(215,285);

    pParent         = parent;
    m_bCanClose     = bCanClose;

    setWindowFlags(Qt::FramelessWindowHint);

    QString mStrName;
    for(int mIdx = 0 ; mIdx < 4 ; mIdx++)
    {
        for(int mCtr = 0 ; mCtr < 3 ; mCtr++)
        {
            btnKey[mIdx * 3 + mCtr] = new CButtonStable(this);
            mStrName.sprintf("bt%d",mIdx * 3 + mCtr + 1);
            btnKey[mIdx * 3 + mCtr]->setObjectName(mStrName);
            btnKey[mIdx * 3 + mCtr]->setGeometry(QRect(mCtr * 70 + 5, mIdx * 70 + 5, 65, 65));
            btnKey[mIdx * 3 + mCtr]->setFocusPolicy(Qt::TabFocus);
            btnKey[mIdx * 3 + mCtr]->setStyleSheet( "QPushButton{background-color : lightGray; border : 1px solid black}");
            connect(btnKey[mIdx * 3 + mCtr],SIGNAL(pressed()),this,SLOT(ImePadPressed()) );
            connect(btnKey[mIdx * 3 + mCtr],SIGNAL(released()),this,SLOT(ImePadReleased()) );
        }
    }

    btnKey[9]->setObjectName("bt0");

    btnKey[0]->setText(QApplication::translate("CSystemImepad", "1"));
    btnKey[1]->setText(QApplication::translate("CSystemImepad", "2"));
    btnKey[2]->setText(QApplication::translate("CSystemImepad", "3"));
    btnKey[3]->setText(QApplication::translate("CSystemImepad", "4"));
    btnKey[4]->setText(QApplication::translate("CSystemImepad", "5"));
    btnKey[5]->setText(QApplication::translate("CSystemImepad", "6"));
    btnKey[6]->setText(QApplication::translate("CSystemImepad", "7"));
    btnKey[7]->setText(QApplication::translate("CSystemImepad", "8"));
    btnKey[8]->setText(QApplication::translate("CSystemImepad", "9"));
    btnKey[9]->setText(QApplication::translate("CSystemImepad", "0"));
    btnKey[10]->setText(QString::fromUtf8("←"));
    btnKey[11]->setText(QApplication::translate("CSystemImepad", "X"));

    translateFontSize( this );

    setVisible(false);
}

void CSystemImepad::ImePadPressed()
{
    QKeyEvent * keyEvent;

    QString name =((QPushButton*)sender())->objectName();
    int i = name.mid(2).toInt();

    if(i == 11)
    {
        keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
        qApp->postEvent(pParent,keyEvent);

    }else if(i == 12)
    {
        keyEvent = new QKeyEvent(QEvent::KeyPress,Qt::Key_Close,Qt::NoModifier);
        qApp->postEvent(pParent,keyEvent);

        if(m_bCanClose)
            this->hide();
    }else
    {
        keyEvent = new QKeyEvent(QEvent::KeyPress,'0' + i,Qt::NoModifier,QString('0' + i));
        qApp->postEvent(pParent,keyEvent);
    }

    ((QPushButton*)sender())->setStyleSheet("background-color : cyan ; border : 2px solid green");
}
void CSystemImepad::ImePadReleased()
{
    ((QPushButton*)sender())->setStyleSheet("background-color : lightGray; border : 1px solid black");
}

void CSystemImepad::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
}
void CSystemImepad::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
