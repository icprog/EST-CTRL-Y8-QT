#ifndef MECH_PANEL_BRACE_H
#define MECH_PANEL_BRACE_H

#include "mech_obj.h"
#include <QObject>


class CMechPanelBrace : public CMechObj
{
    Q_OBJECT
public:
    CMechPanelBrace(QWidget *parent = 0);

    virtual void BuildSurface();
};

#endif // MECH_PANEL_BRACE_H
