#ifndef GEN_FOCUS_H
#define GEN_FOCUS_H

#include <QWidget>

#include "button_stable.h"


class CGenFocus : public QWidget
{
    Q_OBJECT
    
public:
    explicit CGenFocus(int mPf, QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

public slots:
    void OnFocusPressed();
    void OnBodyIndexChange(int);

signals:
    void GenFocusChange(int focus);
    void PopupHide(QWidget *);

private:
    int m_iFocusIdx;

    CButtonStable *btFocusSmall;
    CButtonStable *btFocusLarge;
};

#endif // GEN_FOCUS_H
