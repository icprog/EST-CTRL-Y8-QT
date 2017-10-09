#ifndef SYSTEM_ADVANCE_H
#define SYSTEM_ADVANCE_H

#include <QMenu>
#include <QAction>

#include "./base/system_base.h"


class CSystemAdvance : public CSystemBase
{
    Q_OBJECT
    
public:
    explicit CSystemAdvance(QWidget *parent = 0);
    
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void keyPressEvent( QKeyEvent *  );
private:

    CDialogConFirm * msgBox;
    QAbstractButton * mBtnYes;
    QAbstractButton * mBtnNo;

    CButtonStable *btnShutDown;
    CButtonStable *btnNetWork;
    CButtonStable *btnSimCtrl;
    CButtonStable *btnAutoRotate;
    CButtonStable *btnCursorShow;
    CButtonStable *btnTubeTemp;
    CButtonStable *btnSystemReset;
    CButtonStable *btnGenShow;
    CButtonStable *btnSmartShow;
    CButtonStable *btnKeyFilmCtrl;
    CButtonStable *btnKeyScreenCtrl;
    CButtonStable *btnKeyProtocol;      //通信协议控制
    CButtonStable *btnLightCurtain;      //光幕

    void SystemReset();

private slots:
    void OnStateChanged();
    void OnButtonPressed();

    void OnProtocolChange();            //用户切换通信协议

    void OnLightCurtainCtrl();           //光幕控制界面

public slots:
    void OnConfirmClicked(QAbstractButton * );
};

#endif // SYSTEM_ADVANCE_H
