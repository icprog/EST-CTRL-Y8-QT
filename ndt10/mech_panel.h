#ifndef MECH_PANEL_H
#define MECH_PANEL_H

#include "mech_obj.h"
#include <QObject>


class CMechPanel : public CMechObj
{
    Q_OBJECT
public:
    CMechPanel(QWidget *parent = 0);

    virtual void BuildSurface();

    void setAngle(float );//设置平板角度，绝对值，

    virtual int getDistanceMin(CMechObj *);
};

#endif // MECH_PANEL_H
