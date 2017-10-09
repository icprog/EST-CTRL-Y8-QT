#ifndef MENU_BASE8_H
#define MENU_BASE8_H

#include "./base/menu_base.h"
#include "./base/button_stable.h"

class CMenuBase8 : public CMenuBase
{
    Q_OBJECT
    
public:
    explicit CMenuBase8(QWidget *parent = 0);

protected:
    CButtonStable *pbSystem;
    CButtonStable *pbGenerator;
    CButtonStable *pbMotion;

protected:

    CButtonStable     * pBtnGroup[CEIL8_KEY_MAX];             //所有按键数组
    unsigned short    keyBtnDown[CEIL8_KEY_MAX];            //按键按下代码
    unsigned short    keyBtnUp[CEIL8_KEY_MAX];              //按键按下代码


public slots:
    virtual void OnViewChange(int );

private slots:
    void OnMenuPressed();
    void OnBodyIndexChange(int);

};

#endif // MENU_BASE8_H
