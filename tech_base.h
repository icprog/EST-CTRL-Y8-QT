#ifndef TECH_BASE_H
#define TECH_BASE_H

#include <QWidget>

#include "system_defines.h"
#include "button_stable.h"


class CTechBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CTechBase(QWidget *parent = 0);
    
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *event);
protected:

    CButtonStable * pBtnGroup[SYS_TECH_MAX];//曝光技术切换MaMs
    int m_iCurTech;

public slots:
    virtual void OnViewDirChange(int);  //显示视角切换
    virtual void OnBodyIndexChange(int bodyIdx);    //部位选择切换槽
    virtual void OnGenTechChange(int);
    virtual void OnTechPressed();                   //曝光技术按钮按下

signals:
    void GenTechChange(int tech);           //发生器技术切换信号
};

#endif // TECH_BASE_H
