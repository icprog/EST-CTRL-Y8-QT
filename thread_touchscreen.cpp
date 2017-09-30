#include "thread_touchscreen.h"

#include "unistd.h"
#include <stdio.h>

#include <QCoreApplication>
#include <QApplication>
#include <QMouseEvent>
#include <QWidget>
#include <QLibrary>
#include<QDebug>

struct ts_sample {
    int		x;
    int		y;
    unsigned int	pressure;
    struct timeval	tv;
};

CThreadTouchScreen::CThreadTouchScreen()
{

}

void CThreadTouchScreen::run()
{

    struct tsdev *ts;

    struct tsdev * (*ts_open)(const char *,int );
    int (*ts_config)(struct tsdev *);
    int (*ts_read)(struct tsdev *, struct ts_sample *, int);

    QLibrary libTs("/lib/libts.so");

    ts_open = (struct tsdev *(*)(const char *,int))libTs.resolve("ts_open");
    if(ts_open == NULL)
    {
        qDebug()<<"ts_open == NULL@LINE["<<__LINE__<<"]::FUNC["<<__FUNCTION__<<"]::FILE["<<__FILE__<<"]";
        return ;
    }

    ts_config = (int (*)(struct tsdev *))libTs.resolve("ts_config");
    if(ts_config == NULL)
    {
        fprintf(stderr,"ts_config == NULL.\n");
        return ;
    }

    ts_read = ( int (*)(struct tsdev *, struct ts_sample *, int))libTs.resolve("ts_read");
    if(ts_read == NULL)
    {
        fprintf(stderr,"ts_read == NULL.\n");
        return ;
    }

    char *tsdevice = NULL;

    if ((tsdevice = getenv("TSLIB_TSDEVICE")) == NULL)
    {
        tsdevice = strdup ("/dev/ctp");
    }

    ts = ts_open(tsdevice, 0);

    if (!ts)
    {
        fprintf(stderr,"ts_open(%s,0) failed.\n",tsdevice);
        return ;
    }

    if (ts_config(ts))
    {
        fprintf(stderr,"ts_config(ts) failed.\n");
        return ;
    }

    int mSampState = 0;

    while (1) {

        struct ts_sample samp;
        int ret;

        ret = ts_read(ts, &samp, 1);

        if(ret < 1)
            continue;

        if (samp.pressure == 0)
        {

            QPoint mPoint(samp.x,samp.y);

            QMouseEvent * mouseEventPress;
            mouseEventPress = new QMouseEvent(QEvent::MouseButtonRelease,mPoint,Qt::LeftButton,Qt::NoButton,Qt::NoModifier);

            QWidget *pWids = QApplication::widgetAt(samp.x,samp.y);

            qApp->postEvent(pWids,mouseEventPress);

            mSampState = QEvent::MouseButtonRelease;

            continue;
        }

        if (samp.pressure == 1)
        {
            QPoint mPoint(samp.x,samp.y);

            QMouseEvent * mouseEventPress;


            QWidget *pWids = QApplication::widgetAt(samp.x,samp.y);

            if(  mSampState == QEvent::MouseButtonPress)
            {
                //not support mouse move now. the arrow can't moved. //20160303 jinsongyang
                //mouseEventPress = new QMouseEvent(QEvent::MouseMove,mPoint,Qt::NoButton,Qt::NoButton,Qt::NoModifier);
                //qApp->postEvent(pWids,mouseEventPress);
            }else
            {
                mouseEventPress = new QMouseEvent(QEvent::MouseButtonPress,mPoint,Qt::LeftButton,Qt::NoButton,Qt::NoModifier);
                qApp->postEvent(pWids,mouseEventPress);
            }
            mSampState = QEvent::MouseButtonPress;

            continue;
        }
    }
}

