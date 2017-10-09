#ifndef MAIN_SETTING_H
#define MAIN_SETTING_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QTimer>

#include "./base/button_stable.h"
#include "./system/system_defines.h"

#define SETTING_SCENCE_MAX       ( 64 )


class CMainSetting : public QWidget
{
    Q_OBJECT
    
public:
    explicit CMainSetting(QWidget *parent = 0);
    
    void setSceneWidget(QWidget *);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *);

private:

    CButtonStable *pb_left;
    CButtonStable *pb_right;
    QLabel *lbState;

    QGraphicsScene  * mScene[SETTING_SCENCE_MAX];
    QWidget         * mWidget[SETTING_SCENCE_MAX];

    int m_iSceneCounter;

    QGraphicsView *gViewer;

    int m_iCurrentAngle;
    int m_iViewerIdxLast;

    QTimer * timerRefresh;

public slots:
    void  turnPressed();
    void  turnReleased();

    void OnViewChange(int view);
    void OnDataRefresh();

};

#endif // MAIN_SETTING_H
