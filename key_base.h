#ifndef KEY_BASE_H
#define KEY_BASE_H

#include <QWidget>
#include <QFrame>
#include "system_defines.h"
#include "button_stable.h"


class CKeyBase : public QWidget
{
    Q_OBJECT
public:
    explicit CKeyBase(QWidget *parent = 0);
    
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *event);

protected:

    CButtonStable   * pBtnGroup[SOFT_KEY_MAX];      //所有按键数组
    unsigned short  keyBtnDown[SOFT_KEY_MAX];       //按键按下代码
    unsigned short  keyBtnUp[SOFT_KEY_MAX];         //按键按下代码

    unsigned short m_iIconList[24];                 //按键图标数组
    unsigned short m_iSoftKeyMax;                   //记录实际按键数量
    int m_iViewDir;                                 //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT

    virtual void KeyBtnInit();                      //按键创建初始化
    virtual void KeyBtnSlotInit();                  //按键槽初始化
    virtual void keyCodeInit();                                 //按键代码初始化

    void SendCmdKey(int);               //发送给下位机的命令

signals:
    void softWareKeyDown(int);                      //用户按键按下信号
    void softWareKeyUp(int);                        //用户按键抬起信号
    void ViewChange(int);

private slots:
    virtual void motionKeyPressed();                        //运动按键按下,发消息给OnUserKeyDown
    virtual void motionKeyReleased();                       //运动按键抬起,发消息给OnUserKeyUp

public slots:
    virtual void OnViewDirChange(int viewerDir);    //角度视图切换槽

};

#endif // KEY_BASE_H
