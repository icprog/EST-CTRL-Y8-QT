
#ifndef BUTTON_RENDER_H
#define BUTTON_RENDER_H

#include <QWidget>
#include <QPainterPath>

class CButtonRender : public QWidget
{
    Q_OBJECT

public:
    CButtonRender(const QPainterPath &path, QWidget *parent = 0);

    QPainterPath getPainterPath();

    void setCornerPoints(QPolygon *);
    QPolygon getCornerPoints();

    void setPolygon(QPolygon *);
    QPolygon * getPolygon();

    void setPenColor(const QColor &color);
    QColor  getPenColor();

    void setBrush(const QBrush &brush);
    void setFillColor(Qt::GlobalColor);
    Qt::GlobalColor getFillColor();
    QBrush  getBrush();

    bool BeShow();
    void setBeShow(bool);

public slots:
    void setPenWidth(int width);

private:
    QPolygon    mCornerPoints;
    QPolygon    mBorderPolygon;
    QPainterPath mPath;

    Qt::GlobalColor  fillColor;
    QColor penColor;
    QColor penColorPressed;
    QGradient gradient;

    QBrush fillBrush;

    int penWidth;

    int rotationAngle;

    int m_iPressed;   

    int bShow;
};

#endif //BUTTON_RENDER_H
