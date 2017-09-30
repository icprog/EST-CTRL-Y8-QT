#ifndef CLABELCLICK_H
#define CLABELCLICK_H

#include <QMouseEvent>
#include <QLabel>


class CLabelClick : public QLabel
{
    Q_OBJECT
public:
    explicit CLabelClick(QWidget *parent = 0);

signals:
    void Clicked(CLabelClick* clicked);

protected:
     void mouseReleaseEvent( QMouseEvent* );
};

#endif // CLABELCLICK_H
