#ifndef KEY_UARM8_H
#define KEY_UARM8_H

#include "./base08/key_base8.h"


class CKeyUarm8 : public CKeyBase8
{
    Q_OBJECT
    
public:
    explicit CKeyUarm8(QWidget *parent = 0);
    
protected:
    void keyCodeInit();

};

#endif // KEY_UARM8_H
