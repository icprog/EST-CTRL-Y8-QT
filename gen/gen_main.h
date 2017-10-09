#ifndef GEN_MAIN_H
#define GEN_MAIN_H

#include <QWidget>
#include <QFrame>

#include "./base/button_stable.h"
#include "./system/system_defines.h"

#define GEN_BTN_AEC     (0)
#define GEN_BTN_KV      (1)
#define GEN_BTN_FOCUS   (2)
#define GEN_BTN_MA      (3)
#define GEN_BTN_MS      (4)
#define GEN_BTN_MAS     (5)
#define GEN_BTN_MAX     (6)

#define GEN_BODY_MAX    ( 10 )

#define ICON_IDX_0      (0)
#define ICON_IDX_1      (1)



class CGenMain : public QWidget
{
    Q_OBJECT
    
public:
    explicit CGenMain(int mPf,QWidget *parent = 0);

    void setGenForSave(bool );

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:

    QFrame * frame;

    CButtonStable * pBtnGroup[GEN_BTN_MAX];
    CButtonStable * pBtnBody[GEN_BODY_MAX];

    int m_iBodyIdx;
    int m_iIconIdx;
    bool m_bCanDataSave;
    void BodyParSet(unsigned char idx);

    QTimer *  timerRefresh;

    bool m_iTechButtonShow[SYS_TECH_MAX][GEN_BTN_MAX];

    void SetGenKv(int);
    void SetGenMas(int);
    void SetGenMs(int);
    void SetGenMa(int);
    void SetGenAec(int);
    void SetGenFocus(int);

public:
    int GetGenKv();

public slots:

    void OnParameterPressed();
    void OnBodyPressed();

    void OnFresh();

    void OnGenAecChange(int );
    void OnGenFocusChange(int);

    void OnParamChange(int,int);

    void OnGenTechChange(int tech);

    virtual void OnViewDirChange(int);      //显示视角切换
signals:
    void ParamShow(int);
    void PopupShow(int);
    void BodyIndexChange(int);
};

#endif // GEN_MAIN_H
