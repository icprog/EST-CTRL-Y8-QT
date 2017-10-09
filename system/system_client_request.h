#ifndef SYSTEM_CLIENT_REQUEST_H
#define SYSTEM_CLIENT_REQUEST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#define FUNC_WAIT_TIME          ( 5 )
#define FUNC_WAIT_INTVERAL      ( 1000 )


class CSystemClient : public QWidget
{
    Q_OBJECT
    
public:
    explicit CSystemClient(QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

private slots:
    void OnButtonPressed();
    void OnTimeOut();

private:
    QTimer * timerClick;
    int     m_iSecondPassed;

    QLabel *lbClientIdx;
    QLabel *label;
    QLabel *label_2;

    QPushButton *pbAccept;
    QPushButton *pbReject;

    int m_bAutoAccept;
signals:
    void ClientAck(int);
    void PopupHide(QWidget *);
};

#endif // SYSTEM_CLIENT_REQUEST_H
