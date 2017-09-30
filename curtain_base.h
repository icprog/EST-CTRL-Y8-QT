#ifndef CURTAIN_BASE_H
#define CURTAIN_BASE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "button_stable.h"

class CCurtainBase : public QWidget
{
    Q_OBJECT
public:
    explicit CCurtainBase(QWidget *parent = 0);

private:
    QTimer *tmCurtainStateFresh;  

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *);

    QPushButton *pbCurtainSwitch;
    QGraphicsView   * viewCurtain;
    QGraphicsScene  * sceneCurtain;

public slots:
    virtual void OnCurtainSwitch();
    virtual void OnCurtainStateFresh();
    virtual void OnViewDirChange(int);      //显示视角切换

};

#endif // CURTAIN_BASE_H
