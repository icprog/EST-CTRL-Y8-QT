#ifndef MECH_ROUND_TABLE_H
#define MECH_ROUND_TABLE_H

#include "mech_obj.h"
#include <QWidget>


class CMechRoundTable : public CMechObj
{
    Q_OBJECT
public:
    explicit CMechRoundTable(QWidget *parent = 0);

    virtual void BuildSurface();

};

#endif // MECH_ROUND_TABLE_H
