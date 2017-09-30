#ifndef MAIN_CEIL8_H
#define MAIN_CEIL8_H

#include "main_base8.h"


class CMainCeil8 : public CMainBase8
{
    Q_OBJECT
    
public:
    explicit CMainCeil8(QWidget *parent = 0);
    
protected:
    void myPopupPosInit();
};

#endif // MAIN_CEIL8_H
