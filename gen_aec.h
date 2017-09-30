#ifndef GEN_AEC_H
#define GEN_AEC_H

#include <QWidget>

#include "button_stable.h"

#define GEN_AEC_MAX     ( 7 )


class CGenAec : public QWidget
{
    Q_OBJECT
    
public:
    explicit CGenAec(int mPf,QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

public slots:
    void OnBtnPress();
    void OnBodyIndexChange(int);            //部位协议改变

signals:
    void GenAecChange(int aec);             //AEC改变信号,
    void PopupHide(QWidget *);              //隐藏AEC界面

private:
    int m_iCurAec;                          //当前选择的AEC

    CButtonStable * pBtnGroup[GEN_AEC_MAX];

};

#endif // GEN_AEC_H
