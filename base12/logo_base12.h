#ifndef TITLE_BASE12_H
#define TITLE_BASE12_H

#include "./base/title_base.h"


class CTitleBase12 : public CTitleBase
{
    Q_OBJECT
    
public:
    explicit CTitleBase12(QWidget *parent = 0);

public slots:
    virtual void OnViewDirChange(int);  //显示视角切换
};
#endif // TITLE_BASE12_H
