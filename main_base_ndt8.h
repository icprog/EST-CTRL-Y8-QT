#ifndef MAIN_BASE_NDT8_H
#define MAIN_BASE_NDT8_H

#include "main_base.h"
#include "button_render.h"
#include "lcd_number.h"
#include "button_stable.h"
#include "system_mech.h"

#include <QPolygon>
#include <QFrame>


class CMainBaseNdt8 : public CMainBase
{
    Q_OBJECT
    
public:
    explicit CMainBaseNdt8(QWidget *parent = 0);

private:
    CButtonStable *btnYaxisAdd;
    CButtonStable *btnYaxisDec;
    CButtonStable *btnXaxisAdd;
    CButtonStable *btnXaxisDec;
    CButtonStable *btnFidUp;
    CButtonStable *btnFidDown;
    CButtonStable *btnPanel;
    CButtonStable *btnSetting;
    CButtonStable *btnBottom;

    QList<CButtonStable*> arrBtnMoveCtrl;

    QTimer *tmDataFresh;            //data fresh timer and heart beat timer
    int mKeepAliveCtr;

    int mPreDirBuf;                 //current valid dir of panel
    void OnMoveCtrlInit();

    void SendNdt8Cmd(unsigned short key);
    void SendNdt8KeyPress(int key);
    void SendNdt8KeyRelease(int key);

protected:

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    virtual void mySceneInit();         //通用场景初始化
    virtual void myViewInit();          //通用视图控件初始化

public slots:

    virtual void OnViewChange(int);         //显示视图变更
    virtual void OnPopupShow(int popIdx);   //弹出消息

    void OnBtnMovePressed();
    void OnBtnMoveReleased();

    void OnNdt8aDataFresh();

};

#endif // MAIN_BASE_NDT8_H
