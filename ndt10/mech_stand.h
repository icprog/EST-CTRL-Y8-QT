#ifndef MECH_STAND_H
#define MECH_STAND_H

#include "mech_obj.h"
#include <QObject>


class CMechStand : public CMechObj
{
    Q_OBJECT
public:
    CMechStand(QWidget *parent = 0);

    virtual void BuildSurface();
};

#endif // MECH_STAND_H
