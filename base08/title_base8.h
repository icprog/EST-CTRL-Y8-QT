#ifndef TITLE_BASE8_H
#define TITLE_BASE8_H

#include "./base/title_base.h"


class CTitleBase8 : public CTitleBase
{
    Q_OBJECT
    
public:
    explicit CTitleBase8(QWidget *parent = 0);

private:

    QLabel * pLabelIcon[TITLE8_LABEL_MAX];

public slots:
   virtual void OnTitleFresh();

};
#endif // TITLE_BASE8_H
