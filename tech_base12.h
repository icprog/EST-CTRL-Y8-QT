#ifndef TECH_BASE12_H
#define TECH_BASE12_H

#include "tech_base.h"


class CTechBase12 : public CTechBase
{
    Q_OBJECT

public:
    explicit CTechBase12(QWidget *parent = 0);

public slots:
    virtual void OnBodyIndexChange(int bodyIdx);    //部位选择切换槽
    virtual void OnGenTechChange(int);
    virtual void OnTechPressed();                   //曝光技术按钮按下
    virtual void OnViewDirChange(int);  //显示视角切换
};

#endif // TECH_BASE12_H
