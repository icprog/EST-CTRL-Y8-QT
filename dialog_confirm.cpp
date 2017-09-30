#include "dialog_confirm.h"
#include "resource_manager.h"

CDialogConFirm::CDialogConFirm(QWidget *parent) :
    QWidget(parent)
{

    setStyleSheet("QWidget{background : transparent;}");

    QFont font;
    font.setPixelSize(SYS_FONT(24));

    if(parent)
        setGeometry(parent->geometry());
    else
        setGeometry(0,0,300,300);

    frameShow = new QFrame(this);
    frameShow->setGeometry(100,150,400,300);

    lbTitle = new QLabel(frameShow);
    lbTitle->setGeometry(0,50,400,50);
    lbTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbTitle->setFont(font);

    lbText = new QLabel(frameShow);
    lbText->setGeometry(0,100,400,100);
    lbText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbText->setFont(font);

    for(int mIdx = 0 ; mIdx < CONFIRM_BTN_MAX ; mIdx++)
    {
        mBtnAry[mIdx] = new CButtonStable(frameShow);
        connect(mBtnAry[mIdx],SIGNAL(pressed()),this,SLOT(OnDialogPressed()));
        mBtnAry[mIdx]->setFont(font);
        mBtnAry[mIdx]->setStyleSheet("background-color : cyan");
        mBtnAry[mIdx]->setVisible(false);
    }

    m_iBtnNumber = 0;

    setVisible(false);
}
void CDialogConFirm::setText(const QString & text)
{
    lbText->setText(text);
}
void CDialogConFirm::setTitle(const QString & text)
{
    lbTitle->setText(text);
}
void CDialogConFirm::setIcon(int icon)
{
    if(icon > SYS_STR_INFO || icon< SYS_STR_CRITICAL)
        return;

    switch(icon)
    {
    case SYS_STR_CRITICAL:
        lbTitle->setStyleSheet("color : red");
        lbText->setStyleSheet("color : red");
        frameShow->setStyleSheet("QFrame{background-color : black;}");
        break;
    case SYS_STR_ERROR:
        lbTitle->setStyleSheet("color : yellow");
        lbText->setStyleSheet("color : yellow");
        frameShow->setStyleSheet("QFrame{background-color : darkGray;}");
        break;
    case SYS_STR_WARNING:
        lbTitle->setStyleSheet("color : cyan");
        lbText->setStyleSheet("color : cyan");
        frameShow->setStyleSheet("QFrame{background-color : gray;}");
        break;
    case SYS_STR_QUESTION:
        lbTitle->setStyleSheet("color : blue");
        lbText->setStyleSheet("color : blue");
        frameShow->setStyleSheet("QFrame{background-color : lightGray;}");
        break;
    case SYS_STR_INFO:
        lbTitle->setStyleSheet("color : green");
        lbText->setStyleSheet("color : green");
        frameShow->setStyleSheet("QFrame{background-color : lightGray;}");
        break;
    default:
        break;
    }

}

QAbstractButton *  CDialogConFirm::addButton(const QString & text)
{
    if(m_iBtnNumber >= CONFIRM_BTN_MAX)
        return 0;

    mBtnAry[m_iBtnNumber]->setText(text);
    mBtnAry[m_iBtnNumber]->setVisible(true);
    mBtnAry[m_iBtnNumber]->raise();

    ChangeBtnPosition(m_iBtnNumber);

    m_iBtnNumber++;

    return mBtnAry[m_iBtnNumber -1];
}
void CDialogConFirm::ChangeBtnPosition(int btnCount)
{
    if(btnCount == 0)
    {
        mBtnAry[0]->setGeometry(150,215,100,70);

        return;
    }

    if(btnCount == 1)
    {

        mBtnAry[0]->setGeometry(230,215,100,70);
        mBtnAry[1]->setGeometry(70,215,100,70);

        return;
    }
}

void CDialogConFirm::OnDialogPressed()
{
    setVisible(false);
    m_iBtnNumber = 0;

    for(int mIdx = 0 ; mIdx < CONFIRM_BTN_MAX ;mIdx++)
    {
        mBtnAry[mIdx]->setVisible(false);
    }

    for(int mIdx = 0 ; mIdx < CONFIRM_BTN_MAX ;mIdx++)
    {
        if(sender() == mBtnAry[mIdx])
        {
            emit buttonClicked(mBtnAry[mIdx]);
        }
    }

}

void CDialogConFirm::hideEvent(QHideEvent *event)
{
    releaseKeyboard();

    QWidget::hideEvent(event);
}
void CDialogConFirm::showEvent(QShowEvent *event)
{
    grabKeyboard();

    QWidget::showEvent(event);
}
void CDialogConFirm::keyPressEvent( QKeyEvent *  event)
{
    event->accept();

    switch(event->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        setVisible(false);
        emit buttonClicked(mBtnAry[1]);
        break;

    case Qt::Key_Escape:
        setVisible(false);
        emit buttonClicked(mBtnAry[0]);
        break;

    default:
        break;

    }
}
