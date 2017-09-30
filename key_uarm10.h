#ifndef KEY_UARM10_H
#define KEY_UARM10_H

#include "key_base10.h"


class CKeyUarm10 : public CKeyBase10
{
    Q_OBJECT
    
public:
    explicit CKeyUarm10(QWidget *parent = 0);

protected:
    void keyCodeInit();
};

#endif // KEY_UARM10_H
