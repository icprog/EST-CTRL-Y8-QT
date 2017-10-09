#ifndef THREAD_JOYSTICK_H
#define THREAD_JOYSTICK_H

#include <QtGlobal>
#include <QThread>
#include <QTimer>
#include <QWidget>

//#include "./libusb-1.0.21-x86/libusb/libusb.h"
#include "./libusb-1.0.21/libusb/libusb.h"

struct SKey
{
    unsigned short addr;    //key address
    unsigned short mask;    //mask
    unsigned short val;     //last valid value
    unsigned short cur;     //current value just read from usb
    unsigned long key;      //for key event
};

struct SJoyKey
{
    SKey key1;
    SKey key2;
    SKey key3;
    SKey key4;
    SKey key5;
    SKey key6;
    SKey key7;
    SKey key8;
    SKey key9;
    SKey key10;
    SKey key11;
    SKey key12;
    SKey keyAL;
    SKey keyAR;
    SKey keyAD;
    SKey keyAU;
    union
    {
        unsigned char bBuf[16];     //store data read from usb device
        unsigned short wBuf[8];
    };
};

class CThreadJoystick : public QWidget
{
    Q_OBJECT

public:
    explicit CThreadJoystick(QWidget *parent = 0);

private:
    QTimer * timerScan;
    struct SJoyKey mJoykey;
    libusb_device **usbDevs;                //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *usbCtx;                 //a libusb session
    libusb_device_handle *usbHandle;        //a device handle

    void JoystickBufInit();

    int JoystickInputInit(unsigned short ,unsigned short);

    void JoystickInputClose();

public slots:
    void OnTimerJoystickScan();

};

#endif // THREAD_JOYSTICK_H
