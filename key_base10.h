#ifndef KEY_BASE10_H
#define KEY_BASE10_H

#include "key_base.h"


class CKeyBase10 : public CKeyBase
{
    Q_OBJECT
public:
    explicit CKeyBase10(QWidget *parent = 0);
    
protected:

    void KeyBtnInit();

    void KeyBtnSlotInit();                                //按键槽初始化
    
private slots:
    void motionKeyPressed();                        //运动按键按下,发消息给OnUserKeyDown
    void motionKeyReleased();                       //运动按键抬起,发消息给OnUserKeyUp

public slots:
    void OnViewDirChange(int viewerDir);

signals:
};

#endif // KEY_BASE10_H
