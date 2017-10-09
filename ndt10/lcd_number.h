#ifndef CLCDNUMBER_H
#define CLCDNUMBER_H

#include <QWidget>
#include <QFrame>
#include <QList>

class CLcdNumber : public QWidget
{
    Q_OBJECT
public:
    explicit CLcdNumber(QWidget *parent = 0);

    void display(int );

private:

    QList <QFrame *> imgHolder;
    QList <QString > numberHolder;
    int NumCounts;
    int gPosYStart;
    int gDispBuffer;
};

#endif // CLCDNUMBER_H
