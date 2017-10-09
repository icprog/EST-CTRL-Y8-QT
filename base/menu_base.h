#ifndef MENU_BASE_H
#define MENU_BASE_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "./base/button_stable.h"
#include "./system/system_defines.h"

class CMenuBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CMenuBase(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *event);

    void EmergencyStop();
protected:
    int m_iViewMode;                //gen//motion//
    int m_iViewDir;                 //VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT

public slots:
    virtual void OnViewDirChange(int viewerDir);
    virtual void OnViewChange(int );                //视图切换
    virtual void OnGenTechChange(int);              //发生器技术选择切换

signals:
    void ViewChange(int );                          //视图切换消息
    void MenuKeyDown(int);
};

#endif // MENU_BASE_H
