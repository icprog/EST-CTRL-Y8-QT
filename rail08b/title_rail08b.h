#ifndef TITLE_BASE8_H
#define TITLE_BASE8_H

#include "./base08/title_base08.h"


class CTitleRail08b : public CTitleBase08
{
    Q_OBJECT
    
public:
    explicit CTitleRail08b(QWidget *parent = 0);

private:

    QLabel * pLabelIcon[TITLE8_LABEL_MAX];

public slots:
   virtual void OnTitleFresh();

};
#endif // TITLE_BASE8_H
