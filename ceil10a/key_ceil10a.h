#ifndef KEY_CEIL10_A_H
#define KEY_CEIL10_A_H

#include "./base10/key_base10.h"


class CKeyCeil10a : public CKeyBase10
{
    Q_OBJECT
    
public:
    explicit CKeyCeil10a(QWidget *parent = 0);

protected:
    void keyCodeInit();

};
#endif // KEY_CEIL10_A_H
