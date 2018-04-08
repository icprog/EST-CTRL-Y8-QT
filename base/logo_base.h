#ifndef TITLE_BASE_H
#define TITLE_BASE_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QList>

#define TITLE_IDX_MARK  ( 0 )
#define TITLE_IDX_TIME  ( 1 )

class CTitleBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CTitleBase(QWidget *parent = 0);
    
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *);

    QTimer * timerTitleFresh;
    QList <QLabel *> pLabelList;
public slots:
    virtual void OnTitleFresh();
    virtual void OnViewDirChange(int);  //显示视角切换
};

#endif // TITLE_BASE_H
