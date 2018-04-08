#include "./base12/key_base12.h"
#ifdef USE_CEIL_12_A

#ifndef KEY_CEIL_12A_H
#define KEY_CEIL_12A_H


class CKeyCeil12a : public CKeyBase12
{
    Q_OBJECT

public:
    explicit CKeyCeil12a(QWidget *parent = 0);

protected:
    virtual void keyCodeInit();
    virtual void keyPositionInit();                 //按键位置初始化

};

#endif  //KEY_CEIL_12A_H
#endif  //USE_CEIL_12_A
