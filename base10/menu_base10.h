#ifndef MENU_BASE10_H
#define MENU_BASE10_H

#include "./base/menu_base.h"


class CMenuBase10 : public CMenuBase
{
    Q_OBJECT
    
public:
    explicit CMenuBase10(QWidget *parent = 0);

protected:

    QLabel              * keyLabel[MENU10_BTN_VIEW_MAX];
    QGraphicsScene      * keyScene[MENU10_BTN_VIEW_MAX];
    QGraphicsView       * keyView[MENU10_BTN_VIEW_MAX];
    CButtonStable       * pBtnView[MENU10_BTN_VIEW_MAX];

    CButtonStable     * pBtnGroup[MENU10_KEY_MAX];             //所有按键数组

    void myButtonSlotInit();                                //按键槽初始化
    void myButtonViewInit();

    CButtonStable *pbLeft5;
    CButtonStable *pbLeft6;
    CButtonStable *pbRight5;
    CButtonStable *pbRight6;
    void myButtonInit();

public slots:
    virtual void OnViewChange(int );
    virtual void OnGenTechChange(int);
    void OnViewDirChange(int viewerDir);

private slots:
    void OnViewerSwitch();                                  //界面切换控制，机架、发生器、配置、发生器配置

};

#endif // MENU_BASE10_H
