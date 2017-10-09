#ifndef KEY_BASE12_H
#define KEY_BASE12_H

#include "./base/key_base.h"


class CKeyBase12 : public CKeyBase
{
    Q_OBJECT
public:
    explicit CKeyBase12(QWidget *parent = 0);

protected:
    void KeyBtnInit();
    void KeyBtnSlotInit();

    QFrame *frameAngleTube;                  //球管转动背景图片
private slots:
    void motionKeyPressed();                        //运动按键按下,发消息给OnUserKeyDown
    void motionKeyReleased();                       //运动按键抬起,发消息给OnUserKeyUp

public slots:
    virtual void OnViewDirChange(int viewerDir);    //角度视图切换槽
};

#endif // KEY_BASE12_H
