#ifndef MAIN_BASE_RF8A_H
#define MAIN_BASE_RF8A_H

#include "main_base.h"
#include "button_render.h"
#include "lcd_number.h"
#include "button_stable.h"
#include "system_mech.h"
#include <QPolygon>
#include <QFrame>


class CMainBaseRf8a : public CMainBase
{
    Q_OBJECT
    
public:
    explicit CMainBaseRf8a(QWidget *parent = 0);

private:
    CButtonStable *btnTableLeft;
    CButtonStable *btnTableRight;
    CButtonStable *btnTableRotateLeft;
    CButtonStable *btnTableRotateRight;
    CButtonStable *btnColiYOpen;
    CButtonStable *btnColiYClose;
    CButtonStable *btnColiXOpen;
    CButtonStable *btnColiXClose;
    CButtonStable *btnCompressorUp;
    CButtonStable *btnCompressorDown;
    CButtonStable *btnRotaryPedalLeft;
    CButtonStable *btnRotaryPedalRight;
    CButtonStable *btnTubeUp;
    CButtonStable *btnTubeDown;
    CButtonStable *btnTubeLeft;
    CButtonStable *btnTubeRight;
    CButtonStable *btnTitle;
    CButtonStable *btnBottom;

    QList<CButtonStable*> arrBtnMoveCtrl;

    void OnMoveCtrlInit();

    QLabel * lbTablePosi;
    QLabel * lbTableAngle;
    QLabel * lbColiXPosi;
    QLabel * lbColiYPosi;
    QLabel * lbCompressor;
    QLabel * lbRotaryPadel;
    QLabel * lbTubeHeight;
    QLabel * lbTubePosi;

    QList <QLabel *> lbTextArr;

    void OnTextLabelInit();

    void SendRf8Cmd(unsigned short key);

    void SendRf8KeyPress(int key);
    void SendRf8KeyRelease(int key);

    int mKeyBufPress;
    qint64 mTimeCounter;
    QTimer * tmKeyReleaseCheck;

    QTimer *tmDataFresh;            //data fresh timer and heart beat timer
    int mKeepAliveCtr;

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

    virtual void OnFilmKeyDown(int);            //film key down
    virtual void OnFilmKeyUp(int);                  //film key up

    virtual void OnViewChange(int);         //显示视图变更
    virtual void OnPopupShow(int popIdx);   //弹出消息

    void OnBtnMovePressed();
    void OnBtnMoveReleased();

    void OnKeyReleaseCheck();

    void OnRf8aDataFresh();

};

#endif // MAIN_BASE_RF8A_H
