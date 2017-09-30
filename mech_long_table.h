#ifndef MECH_LONG_TABLE_H
#define MECH_LONG_TABLE_H

#include "button_stable.h"
#include "mech_obj.h"
#include <QObject>
#include <QList>


class CMechLongTable : public CMechObj
{
    Q_OBJECT
public:
    CMechLongTable(QWidget *parent = 0);

    void BuildSurface();            //构建长台表面，用于碰撞检测

};

#endif // MECH_LONG_TABLE_H
