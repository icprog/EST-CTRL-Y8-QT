#ifndef TITLE_BASE_H
#define TITLE_BASE_H

#include "system/system_defines.h"
#include <QWidget>
#include <QTimer>
#include <QLabel>

class CTitleBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CTitleBase(QWidget *parent = 0);
    
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *);

    QTimer * timerTitleFresh;

public slots:
    virtual void OnTitleFresh();
    virtual void OnViewDirChange(int);  //显示视角切换
};

#endif // TITLE_BASE_H
