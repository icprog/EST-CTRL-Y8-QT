#ifndef SYSTEM_SMART_NDT_H
#define SYSTEM_SMART_NDT_H

#include "./base/system_base.h"


class CSystemSmartNdt : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemSmartNdt( QWidget* parent = 0 );

protected:

    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

private:
    int            m_iBtnSaveIdx;
    QTimer       * timerRefesh;

    QLabel       * labelInfo;                   //提示操作方法
    QLabel       * labelMsg;                   //提示警示信息，保存成功信息

    QList <CButtonStable *> arrBtnGroup;
    QList <QLabel *> arrLbChannel;                  //显示AD通道
    QList <QLabel *> arrLbData;                         //显示量化后的结果

    QFrame       * pFrameGroup0;  //分割线
    QFrame       * pFrameGroup1;  //分割线

    CButtonStable* pBtnExportNdtParam;
    CButtonStable* pBtnImportNdtParam;

public slots:
    void OnTime();
    void OnNdtSavePressed();
    void OnNdtExitPressed();
};

#endif //SYSTEM_SMART_NDT_H
