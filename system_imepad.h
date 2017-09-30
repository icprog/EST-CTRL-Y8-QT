#ifndef SYSTEM_IMEPAD_H
#define SYSTEM_IMEPAD_H

#include "button_stable.h"


class CSystemImepad : public QWidget
{
    Q_OBJECT
public:
    CSystemImepad(QWidget* parent = 0,int bCanClose = 1);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    QWidget * pParent;
    int m_bCanClose;

    CButtonStable * btnKey[12];

public slots:
    void ImePadPressed();
    void ImePadReleased();
};

#endif //SYSTEM_IMEPAD_H
