#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#include "system_base.h"
#include "system_defines.h"

#define LENGTH_MAX_MAINTANCE     ( 4 )
#define LENGTH_MAX_DATE          ( 10 )
#define LENGTH_MAX_TIME          ( 5 )

#define CFG_FOCUS_DATE           ( 0 )
#define CFG_FOCUS_TIME           ( 1 )
#define CFG_FOCUS_MANT           ( 2 )


class CSystemConfig : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemConfig( QWidget* parent = 0);

protected:

    void hideEvent(QHideEvent *);                       //隐藏
    void showEvent(QShowEvent *);                       //显示

    void keyPressEvent ( QKeyEvent * event );           //按键处理
private:
    int         flag_NeedReboot;                        //需要重启
    int         m_StrMaxLength;

    CButtonStable *btSaveDate;
    CButtonStable *btLang[LANGUAGE_MAX];                //俄语
    CButtonStable *btMaintenanceSet;
    CButtonStable *btStandOnLeft;
    CButtonStable *btStandOnRight;
    CButtonStable *btRestart;


    QLabel *stCtrl_2;
    QLabel *stCtrl_3;
    QLabel *stCtrl_5;
    QLabel *stCtrl_4;
    QLabel *stCtrl_6;

    QLabel *lbInfoDateTime;
    QLabel *edHoursRun;

    QLabel *edHours;
    QLabel *dateEdit;
    QLabel *timeEdit;
    QFrame *line_1;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;

public slots:
    void OnLanguageChange();                            //语言切换处理
    void OnButtonPressed();                             //按键按下
    void OnBtnSaveDate();                             //按键按下
    bool eventFilter(QObject *, QEvent *);              //消息过滤，处理FocusIn  FocusOut
};

#endif //SYSTEM_CONFIG_H
