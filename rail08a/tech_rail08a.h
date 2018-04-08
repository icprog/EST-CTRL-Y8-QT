#ifndef TECH_RAIL08B_H
#define TECH_RAIL08B_H

#include "./base08/tech_base8.h"


class CTechRail08b : public CTechBase8
{
    Q_OBJECT

public:
    explicit CTechRail08b(QWidget *parent = 0);

public slots:
    virtual void OnBodyIndexChange(int bodyIdx);    //部位选择切换槽
    virtual void OnGenTechChange(int);
    virtual void OnTechPressed();                   //曝光技术按钮按下
    virtual void OnViewDirChange(int);  //显示视角切换
};

#endif // TECH_RAIL08B_H
