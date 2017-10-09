#ifndef SYSTEM_BASE_H
#define SYSTEM_BASE_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>

#include "button_stable.h"
#include "button_stable.h"
#include "./system/dialog_confirm.h"


class CSystemBase : public QWidget
{
    Q_OBJECT
public:
    explicit CSystemBase(QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

protected:
    QString m_strKeyBuff;
    int m_iFocusCurrent;

protected:
    QLabel      * textTitle;
    QWidget     * lineTitleLeft;
    QWidget     * lineTitleRight;
    QWidget     * lineBaseLeft;
    QWidget     * lineBaseRight;
    CButtonStable * btnExit;

signals:

    void ViewChange(int view);
    
public slots:
    
};

#endif // SYSTEM_BASE_H
