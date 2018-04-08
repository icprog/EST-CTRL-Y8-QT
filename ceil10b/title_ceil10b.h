#ifndef TITLE_BASE12_H
#define TITLE_BASE12_H

#include "./base/title_base.h"


class CTitleBase12 : public CTitleBase
{
    Q_OBJECT
    
public:
    explicit CTitleBase12(QWidget *parent = 0);

private:

    QLabel * pLabelIcon[TITLE8_LABEL_MAX];

public slots:
    virtual void OnTitleFresh();
    virtual void OnViewDirChange(int);  //显示视角切换
};
#endif // TITLE_BASE12_H
