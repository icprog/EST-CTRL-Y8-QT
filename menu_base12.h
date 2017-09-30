#ifndef MENU_BASE12_H
#define MENU_BASE12_H

#include "menu_base.h"
#include "button_stable.h"
#include "button_stable.h"

class CMenuBase12 : public CMenuBase
{
    Q_OBJECT

public:
    explicit CMenuBase12(QWidget *parent = 0);

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
    virtual void OnViewDirChange(int viewerDir);

private slots:
    void OnMenuPressed();
    void OnBodyIndexChange(int);

};

#endif // MENU_BASE12_H
