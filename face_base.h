#ifndef FACE_BASE_H
#define FACE_BASE_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QProgressBar>

/*1.软件启动画面*/
/*2.支持8寸液晶屏与10寸液晶屏*/
/*3.支持启动进度显示*/


class CFaceBase : public QWidget
{
    Q_OBJECT
public:
    explicit CFaceBase(QWidget *parent = 0);

public:
    void setProgressBar(int load = 0);  //设置启动进度，当进度为100时，显示主窗口

protected:
    void hideEvent(QHideEvent *);       //隐藏消息
    void showEvent(QShowEvent *);       //显示消息，启动
    void mousePressEvent(QMouseEvent *);

protected:

    QTimer          * timerStartUp;     //软件初始化时钟，只执行一次
    QTimer          * timerStartFinish; //软件初始化时钟，只执行一次

    QLabel          * lbBackGround;     //background of start up face，背景

    QProgressBar    * progressBar;      //progressbar，进度条
    QGraphicsScene  * barScene;
    QGraphicsView   * barView;

    QLabel          * stInfo;           //msg，消息
    QGraphicsScene  * infoScene;
    QGraphicsView   * infoView;

    QLabel          * stHospital;       //医院名称
    QGraphicsScene  * versionScene;
    QGraphicsView   * versionView;

public slots:

    void OnStartUp();                   //软件初始化函数，由定时器启动
    void OnStartFinish();                   //软件初始化函数，由定时器启动
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // FACE_BASE_H
