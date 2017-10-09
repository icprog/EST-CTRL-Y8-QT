#ifndef SYSTEM_CONSOLE1_H
#define SYSTEM_CONSOLE1_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QTextEdit>
#include <QTextStream>
#include <QDir>


class CSystemConsole1 : public QWidget
{ 
    Q_OBJECT
public:
    CSystemConsole1(QWidget* parent = 0 );

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:
    QTextEdit * pDispbox;
    int mDispboxLines;

    QLabel * pInputBox;

    QString mBufInput;

    QString strBufferIn;
    QString outBufferFile;

    //QTextStream * streamIn;
    //QTextStream * streamOut;

    QDir dirManager;

    void RunAndDisp();
    void MoveCursorEnd();
public slots:
    bool eventFilter(QObject *, QEvent *);
};

#endif //SYSTEM_CONSOLE1_H
