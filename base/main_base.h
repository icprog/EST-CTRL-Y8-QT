#ifndef MAIN_BASE_H
#define MAIN_BASE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>

#include "./system/system_defines.h"



class CMainBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CMainBase(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);       //通用信息显示控制
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

    virtual void myViewInit();          //通用视图控件初始化
    virtual void mySceneInit();         //通用场景初始化

    QFrame *frameBack;                  //主界面背景图片
public:
    QGraphicsView   * viewPopup;                    //显示控件，用于所有的弹出消息
    QGraphicsView   * viewGen;                      //显示控件，发生器控制页面
    QGraphicsScene  * pSceneArray[SYS_POPUP_MAX];   //场景，启动画面，主画面，调试画面

protected:

    int m_iViewDir;                 //当前显示的视角，支持//VIEW_DIR_NORMAL//VIEW_DIR_LEFT//VIEW_DIR_RIGHT//VIEW_DIR_R180
    int m_iViewDirBuf;              //显示视角备份
    int m_iViewer;                  //当前的画面,发生器,机架,默认参数为VIEW_MOTION

    QGraphicsView   * viewMotion;   //显示控件，动画区域
    QGraphicsView   * viewMenu;     //显示控件，菜单区域
    QGraphicsView   * viewInfo;     //显示控件，消息区域
    QGraphicsView   * viewStatus;   //显示控件，状态区域
    QGraphicsView   * viewFast;     //显示控件，快捷区域
    QGraphicsView   * viewTech;     //显示控件，曝光技术区域

    int m_iViewSwitch[VIEW_DIR_MAX][VIEW_DIR_MAX];      //视角切换转换关系
    QRect PopInfoPos[SYS_POPUP_MAX][VIEW_DIR_MAX];      //弹出消息框位置

    QPushButton * lbCompletionTips;

public slots:
    virtual void OnPageChange(int);
    virtual void OnFilmKeyDown(int);            //film key down
    virtual void OnFilmKeyUp(int);                  //film key up

    virtual void OnGenTechChange(int );     //发生器技术选择变更
    virtual void OnViewChange(int);         //显示视图变更
    virtual void OnViewDirChange(int);      //显示视角变更
    virtual void OnPopupShow(int popIdx);   //弹出消息
    virtual void OnPopupHide(QWidget *);    //隐藏弹出消息

    void OnCompletionTip();                 //completion tips handle
signals:
    void SmartPressed(int);
    void ViewChange(int );                  //发送消息给,用于控制弹出框
};

#endif // MAIN_BASE_H
