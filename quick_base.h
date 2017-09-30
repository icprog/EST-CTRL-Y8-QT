#ifndef QUICK_BASE_H
#define QUICK_BASE_H

#include <QWidget>
#include "button_stable.h"

#define QUICK_BTN_MAX       ( 3 )
#define QUICK_BTN_00          ( 0 )
#define QUICK_BTN_01          ( 1 )
#define QUICK_BTN_02          ( 2 )
#define QUICK_KEY_INVALID   ( -1 )  /*代表长按按键无效*/

class CQuickBase : public QWidget
{
    Q_OBJECT
public:
    explicit CQuickBase(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
   void mousePressEvent(QMouseEvent *event);

protected:
    CButtonStable *pBtnQuick[QUICK_BTN_MAX];
    unsigned short m_codeQuickDown[QUICK_BTN_MAX];
    unsigned short m_codeQuickUp[QUICK_BTN_MAX];
    unsigned short m_codeQuickLong[QUICK_BTN_MAX];

    int m_iViewDir;                 //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT
    int m_iQuickIdx;                //用于按键长按的标记
    QTimer  * timerLongPress;       //延时定时器，用于按键长按动作
    virtual void quickBtnInit();
    virtual void quickBtnSlotInit();
    virtual void quickBtnViewInit();

    void SendCmdKey(int);               //发送给下位机的命令
private slots:
    virtual void quickPressed();
    virtual void quickReleased();

    virtual void OnKeyLongPress();                      //长按按键触发

public slots:
    virtual void OnViewDirChange(int);
    virtual void OnStatusChange(int ,QPushButton *); //快捷状态改变

signals:
    void SmartChange(int); //快捷位置变更
    void ViewChange(int);
    void QuickKeyDown(int);
};

#endif // QUICK_BASE_H
