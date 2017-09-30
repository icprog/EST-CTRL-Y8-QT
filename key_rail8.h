#ifndef KEY_RAIL8_H
#define KEY_RAIL8_H

#include "key_base8.h"


class CKeyRail8 : public CKeyBase8
{
    Q_OBJECT
    
public:
    explicit CKeyRail8(QWidget *parent = 0);

protected:

    void keyCodeInit();

};

#endif // KEY_RAIL8_H
