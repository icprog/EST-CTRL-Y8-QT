#include "label_click.h"

CLabelClick::CLabelClick(QWidget *parent) : QLabel(parent)
{

}

void CLabelClick::mouseReleaseEvent(QMouseEvent *)
{
    emit Clicked(this);
}
