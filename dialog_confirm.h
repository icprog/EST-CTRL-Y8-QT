#ifndef DIALOG_CONFIRM_H
#define DIALOG_CONFIRM_H

#include <QWidget>
#include <QLabel>
#include "button_stable.h"

#define CONFIRM_BTN_MAX     (5)


class CDialogConFirm : public QWidget
{
    Q_OBJECT
public:
    explicit CDialogConFirm(QWidget *parent = 0);
    
    QAbstractButton * addButton(const QString & text);
    void setText(const QString & text);
    void setTitle(const QString & text);
    void setIcon(int icon);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent( QKeyEvent *  );

private:
    QLabel * lbTitle;
    QLabel * lbText;
    QFrame * frameShow;

    CButtonStable * mBtnAry[CONFIRM_BTN_MAX];

    int m_iBtnNumber;

    void ChangeBtnPosition(int);

private slots:
    void OnDialogPressed();

signals:
    void buttonClicked(QAbstractButton * button );
};

#endif // DIALOG_CONFIRM_H
