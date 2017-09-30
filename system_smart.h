#ifndef SYSTEM_SMART_H
#define SYSTEM_SMART_H

#include "system_base.h"
#include "system_smart_ndt.h"

#define FAST_POSI_MAX           ( 8 )


class CSystemSmart : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemSmart( int mPlatform,QWidget* parent = 0 );

protected:

    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:
    int m_iBtnSaveIdx;
    int           m_iMotorMax;
    QTimer       * timerRefesh;

    QLabel       * labelInfo;                   //提示操作方法
    QLabel       * labelMsg;                    //提示警示信息，保存成功信息
    CButtonStable* pBtnGroup[FAST_POSI_MAX];
    QLabel       * pLabelAd[FAST_POSI_MAX];     //显示AD采样结果
    QLabel       * pLabelData[FAST_POSI_MAX];   //显示量化后的结果
    QLabel       * pLabelChannel[FAST_POSI_MAX];//显示AD通道

    QFrame       * pFrameGroup0;  //分割线
    QFrame       * pFrameGroup1;  //分割线

    unsigned short m_iFastPosiCode[FAST_POSI_MAX];

    void InitCfg(int mPf);

    CSystemSmartNdt * mSmartNdt;
    CButtonStable * pBtnNdtShow;
public slots:
    void OnTime();
    void OnFastPressed();
    void OnFastPressedSave();
    void OnNdtSmartShow();
};

#endif //SYSTEM_SMART_H
