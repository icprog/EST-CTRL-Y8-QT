#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QWidget>

#include "./system/system_defines.h"


#define MAINFRAME_SCENE_MAX           (5)

class CMainFrame : public QWidget
{ 
    Q_OBJECT
    
public:

    CMainFrame( QWidget* parent = 0);

    void setSceneWidget(QWidget * pWidgetNew);

    void setRotate(int );
protected:

    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void mousePressEvent(QMouseEvent *event);

private:

    QTimer *internalTimer;

    QGraphicsView           * pViewFrame;                               //显示控件
    QGraphicsScene          * pSceneFrame[MAINFRAME_SCENE_MAX];        //场景，启动画面，主画面，调试画面
    QWidget                 * pSceneWidget[MAINFRAME_SCENE_MAX];
    int                     m_iSceneCount;

    int                     m_iRotate;                               //

public slots:
    void OnMainFresh();
    void OnViewChange(int);         //显示视图变更
};


#endif   //MAIN_FRAME_H
