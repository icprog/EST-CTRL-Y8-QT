#ifndef MECH_ARM_H
#define MECH_ARM_H

#include "mech_obj.h"
#include <QObject>


class CMechArm : public CMechObj
{
    Q_OBJECT
public:
    CMechArm(QWidget *parent = 0);

    void BuildSurface();
};

#endif // MECH_ARM_H
