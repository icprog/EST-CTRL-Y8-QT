#ifndef KEY_CEIL10_B_H
#define KEY_CEIL10_B_H

#include "key_base10.h"


class CKeyCeil10b : public CKeyBase10
{
    Q_OBJECT
    
public:
    explicit CKeyCeil10b(QWidget *parent = 0);

protected:
    void keyCodeInit();

};
#endif // KEY_CEIL10_B_H
