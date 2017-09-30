#ifndef BUTTON_STABLE_H
#define BUTTON_STABLE_H

#include <QPushButton>
#include <QMouseEvent>

/*1.防止按键抖动的Button，方法是不处理任何MouseMove事件*/
/*2.按下会触发声音，方法是调用声音函数*/
class CButtonStable : public QPushButton
{
    Q_OBJECT
public:
    explicit CButtonStable(QWidget *parent = 0);

protected:
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void mouseDoubleClickEvent ( QMouseEvent * event );
};

#endif // BUTTON_STABLE_H
