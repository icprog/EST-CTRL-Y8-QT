#ifndef CTHREADTOUCHSCREEN_H
#define CTHREADTOUCHSCREEN_H

#include <QThread>


class CThreadTouchScreen : public QThread
{

public:
    CThreadTouchScreen();

protected:
    virtual void run();

};

#endif // CTHREADTOUCHSCREEN_H
