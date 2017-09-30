#ifndef MECH_SMALL_TABLE_H
#define MECH_SMALL_TABLE_H

#include "mech_obj.h"
#include <QObject>


class CMechSmallTable : public CMechObj
{
    Q_OBJECT
public:
    CMechSmallTable(QWidget *parent = 0);

    void BuildSurface();

};

#endif // MECH_SMALL_TABLE_H
