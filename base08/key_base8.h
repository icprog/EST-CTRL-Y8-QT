#ifndef KEY_BASE8_H
#define KEY_BASE8_H

#include "./base/key_base.h"


class CKeyBase8 : public CKeyBase
{
    Q_OBJECT
public:
    explicit CKeyBase8(QWidget *parent = 0);
    
protected:
    void KeyBtnInit();
    void KeyBtnSlotInit();
    
private slots:
    void motionKeyPressed();                        //运动按键按下,发消息给OnUserKeyDown
    void motionKeyReleased();                       //运动按键抬起,发消息给OnUserKeyUp
    
};

#endif // KEY_BASE8_H
