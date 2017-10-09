#ifndef SYSTEM_PASSWORD_H
#define SYSTEM_PASSWORD_H

#include "./base/system_base.h"


class CSystemPassword : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemPassword( QWidget* parent = 0 );

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:
    bool    m_bSkipPsdForm;        //是否跳过密码,系统开机后只需输入一次正确的密码

    QLabel *lbdyn;
    QLabel *lbinfo;
    QLabel *lbDateTime;
    QLabel *edpsw;

    QTimer * tmRefresh;             //time display refresh

    CButtonStable *btLock;
    CButtonStable *btGeneral;
    CButtonStable *btOk;

public slots:
    void OnPasswordPress();         //按钮按下
    void OnPasswordCheck();         //按钮按下
    void OnTimerFresh();            //时钟更新

};

#endif //SYSTEM_PASSWORD_H
