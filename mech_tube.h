#ifndef MECH_TUBE_H
#define MECH_TUBE_H

#include "mech_obj.h"
#include <QObject>


class CMechTube : public CMechObj
{
    Q_OBJECT
public:
    CMechTube(QWidget *parent = 0);

    virtual void BuildSurface();
};

#endif // MECH_TUBE_H
