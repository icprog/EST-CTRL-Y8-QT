#ifndef INFO_BASE12_H
#define INFO_BASE12_H

#include "./base/info_base.h"


class CInfoBase12 : public CInfoBase
{
    Q_OBJECT
    
public:
    explicit CInfoBase12(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

    virtual void InfoDisplay();                 //信息显示
    virtual void InfoMonitor();                 //信息监视

public slots:
    virtual void OnInfoFresh();
    virtual void OnViewDirChange(int);      //显示视角切换

};

#endif // INFO_BASE12_H
