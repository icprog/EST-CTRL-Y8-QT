#ifndef KEY_CEIL8_H
#define KEY_CEIL8_H

#include "key_base8.h"


class CKeyCeil8 : public CKeyBase8
{
    Q_OBJECT
    
public:
    explicit CKeyCeil8(QWidget *parent = 0);

protected:

    void keyCodeInit();

};


#endif // KEY_CEIL8_H
