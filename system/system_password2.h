#ifndef SYSTEM_PASSWORD2_H
#define SYSTEM_PASSWORD2_H

#include "./system/system_defines.h"
#include "./base/system_base.h"


class CSystemPassword2 : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemPassword2( QWidget* parent = 0 );

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void keyPressEvent ( QKeyEvent * event );
    bool eventFilter(QObject *, QEvent *);

    void mousePressEvent(QMouseEvent *event);
private:

    bool    m_bSkipPsdForm;        //是否跳过密码,系统开机后只需输入一次正确的密码

    QLabel *lbdyn;
    QLabel *lbinfo;
    QLabel *lbDateTime;
    QLabel *edpsw;
    QLabel *lbVer;

    QTimer * tmRefresh;             //time display refresh

    CButtonStable *btLock;
    CButtonStable *btGeneral;
    CButtonStable *btPswCheck;

    int calcPassword();
    int ConsoleCheck();

    char mStrMachineCode[MACHINE_CODE_LEN + 1];
    void GenerateMachCode();

    int PwdFiltered(QString);        //time change enable password can only use once
public slots:
    void OnPasswordPress();         //按钮按下
    void OnPasswordCheck();         //按钮按下
    void OnTimerFresh();            //时钟更新

signals:
    void ViewChange(int );                  //视图切换
};

#endif //SYSTEM_PASSWORD2_H
