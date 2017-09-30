#ifndef SYSTEM_MENU_H
#define SYSTEM_MENU_H

#include "system_base.h"

#define BTN_MENU_MAX        ( 12 )


class CSystemMenu : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemMenu( QWidget* parent = 0 );

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:
    CButtonStable * pBtnGroup[BTN_MENU_MAX];
    QWidget     * pWidGroup[BTN_MENU_MAX];

    QLabel *TextLabel1;
    QLabel *TextLabel3;
    QLabel *TextLabel2;

public slots:
    void OnButtonPressed();

};

#endif //SYSTEM_MENU_H
