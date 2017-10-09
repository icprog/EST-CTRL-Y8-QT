#ifndef EXIT_BASE_H
#define EXIT_BASE_H

#include <QWidget>

#include "button_stable.h"

class CExitBase : public QWidget
{
    Q_OBJECT
public:
    explicit CExitBase(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *);

protected:
    QPushButton *pbSystemExit;
    
public slots:
    void OnSystemExit();
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // EXIT_BASE_H
