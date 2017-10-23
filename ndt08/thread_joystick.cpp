#include "thread_joystick.h"
#include "resource_manager.h"

#define JOY_FIND_INTERVAL   2000    /*没有接设备时的扫描间隔*/
#define JOY_SCAN_INTERVAL   100     /*设备接入后的读取间隔*/
#define JOY_PACKAGE_SIZE    0x0008  /*数据包大小*/
#define JOY_USB_KEY_BTN     12      /*独立按键数量*/
#define JOY_USB_KEY_DIR     4       /*方向按键数量*/
#define JOY_USB_VID         0x0079  /**/
#define JOY_USB_PID         0x0006  /**/


/*
CThreadJoystick::CThreadJoystick(QWidget *parent) :
    QWidget(parent)
{
    //初始化变量
    JoystickBufInit();

    timerScan = new QTimer(this);
    timerScan->setInterval(JOY_FIND_INTERVAL);

    connect(timerScan, SIGNAL(timeout()), this, SLOT(OnTimerJoystickScan()));
    timerScan->start();

}

void CThreadJoystick::OnTimerJoystickScan()
{

    //如果设备没有打开，尝试打开设备
    if(usbHandle == NULL)
    {
        JoystickInputInit(JOY_USB_VID,JOY_USB_PID);
        return;
    }

    //与USB设备通信，读取信息
    int size;
    libusb_interrupt_transfer(usbHandle,
                              0x81,
                              mJoykey.bBuf,
                              JOY_PACKAGE_SIZE,
                              &size,
                              100);

    //判断返回的数据长度
    if(size != JOY_PACKAGE_SIZE)
    {
        JoystickInputClose();
        timerScan->setInterval(JOY_FIND_INTERVAL);
        return;
    }

    int mIdx;
    QKeyEvent * keyEvent;

    struct SKey * pKey;
    pKey = ( struct SKey * )(&mJoykey);

    for(mIdx = 0 ; mIdx < JOY_USB_KEY_BTN ; mIdx++)
    {
        pKey->cur = mJoykey.wBuf[pKey->addr] & pKey->mask;  //set current key value

        if(pKey->cur != pKey->val)      //判断数据是否有变化
        {
            pKey->val = pKey->cur;      //保存当前值

            if(pKey->val == pKey->mask) //数据为1代表按键按下
            {
                keyEvent = new QKeyEvent(QEvent::KeyPress,pKey->key,Qt::NoModifier);
                qApp->postEvent(RsMgr->g_mainBase,keyEvent);
            }else
            {
                keyEvent = new QKeyEvent(QEvent::KeyRelease,pKey->key,Qt::NoModifier);
                qApp->postEvent(RsMgr->g_mainBase,keyEvent);
            }
        }

        pKey++;
    }

    pKey = (&mJoykey.keyAL);        //指向第一个方向按键

    unsigned char mKeyT;

    for(mIdx = 0 ; mIdx < JOY_USB_KEY_DIR ; mIdx++)
    {
        mKeyT = mJoykey.bBuf[pKey->addr];

        if(pKey->val != mKeyT)
        {
            if(mKeyT == 0x7f)
            {
                pKey->val = 0x7f;
                keyEvent = new QKeyEvent(QEvent::KeyPress,pKey->key,Qt::NoModifier);
                qApp->postEvent(RsMgr->g_mainBase,keyEvent);

            }else if(mKeyT == pKey->mask)
            {
                pKey->val = mKeyT;

                keyEvent = new QKeyEvent(QEvent::KeyRelease,pKey->key,Qt::NoModifier);
                qApp->postEvent(RsMgr->g_mainBase,keyEvent);

            }
        }

        pKey++;
    }

}

//return value
//-1 system error ,can not support joystick
//0 joystick did not plug in ,can try to open again
//1 open success
int CThreadJoystick::JoystickInputInit(unsigned short vid,unsigned short pid)
{

    int res;                            //for return values
    if(!usbCtx)
    {
        res = libusb_init(&usbCtx);         //initialize a library session
        if(res < 0) {
            fprintf(stderr,"JoystickInputInit Error:do not support\n");
            return -1;
        }

        //set verbosity level to LIBUSB_LOG_LEVEL_INFO, as suggested in the documentation
        libusb_set_debug(usbCtx, LIBUSB_LOG_LEVEL_INFO);
    }

    ssize_t cnt;                   //holding number of devices in list
    cnt = libusb_get_device_list(usbCtx, &usbDevs); //get the list of devices
    if(cnt < 0) {
        printf("JoystickInputInit::libusb_get_device_list Error\n");
        return -1 ;
    }

    usbHandle = libusb_open_device_with_vid_pid(usbCtx, vid, pid); //open mouse
    if(usbHandle == NULL)
    {
        //fprintf(stderr,"Cannot open libusb device\n");
        libusb_free_device_list(usbDevs, 1); //free the list, unref the devices in it
        //libusb_exit(usbCtx);                 //close the session
        return 0;
    } else
    {
        printf("Joystick Device Opened\n");
        libusb_free_device_list(usbDevs, 1);                     //free the list, unref the devices in it
        if(libusb_kernel_driver_active(usbHandle, 0) == 1)      //find out if kernel driver is attached
        {
            printf("Kernel Driver Active\n");
            if(libusb_detach_kernel_driver(usbHandle, 0) == 0) //detach it
                printf("Kernel Driver Detached!\n");
        }

        res = libusb_claim_interface(usbHandle, 0);            //claim interface 0 (the first) of device (mine had jsut 1)
        if(res < 0)
        {
            printf("Cannot Claim Interface\n");
            return -1;
        }
    }

    timerScan->setInterval(JOY_SCAN_INTERVAL);
    return 1;
}

void CThreadJoystick::JoystickInputClose()
{

    int res;

    //release the claimed interface
    res = libusb_release_interface(usbHandle, 0);
    if(res!=0)
    {
        printf("Cannot Release Interface\n");
        return;
    }

    printf("Released Interface\n");
    libusb_attach_kernel_driver(usbHandle, 0);
    libusb_close(usbHandle);
    //libusb_exit(usbCtx); //close the session

    usbHandle = NULL;
}

void CThreadJoystick::JoystickBufInit()
{
    usbCtx = NULL;
    usbHandle = NULL;

    memset((void*)&mJoykey,0,sizeof(mJoykey));

    //实际键码的存储位置
    mJoykey.key1.addr = 2;
    mJoykey.key2.addr = 2;
    mJoykey.key3.addr = 2;
    mJoykey.key4.addr = 2;
    mJoykey.key5.addr = 3;
    mJoykey.key6.addr = 3;
    mJoykey.key7.addr = 3;
    mJoykey.key8.addr = 3;
    mJoykey.key9.addr = 3;
    mJoykey.key10.addr = 3;
    mJoykey.key11.addr = 3;
    mJoykey.key12.addr = 3;
    mJoykey.keyAL.addr = 0;
    mJoykey.keyAR.addr = 0;
    mJoykey.keyAD.addr = 1;
    mJoykey.keyAU.addr = 1;

    //实际键码与虚拟键码的对应关系
    mJoykey.key1.key = Qt::Key_1;//0x31//49**
    mJoykey.key2.key = Qt::Key_3;//0x33//51**
    mJoykey.key3.key = Qt::Key_Q;//0x51//81**
    mJoykey.key4.key = Qt::Key_E;//0x45//69**
    mJoykey.key5.key = Qt::Key_U;//0x55//85**
    mJoykey.key6.key = Qt::Key_P;//0x50//80**
    mJoykey.key7.key = Qt::Key_Escape;//0x01000000//16777216 **
    mJoykey.key8.key = Qt::Key_F4;//0x01000033//16777267 **
    mJoykey.key9.key = Qt::Key_H;//0x48//72**
    mJoykey.key10.key = Qt::Key_Apostrophe;//0x27//39**
    mJoykey.key11.key = Qt::Key_A;//0x41//65**
    mJoykey.key12.key = Qt::Key_D;//0x44//68**
    mJoykey.keyAL.key = Qt::Key_J;//0x4a//74**
    mJoykey.keyAR.key = Qt::Key_Semicolon;//0x3b//59**
    mJoykey.keyAD.key = Qt::Key_F6;
    mJoykey.keyAU.key = Qt::Key_L;//0x4c//76

    //实际键码的识别掩码
    mJoykey.key1.mask = 0x1000;
    mJoykey.key2.mask = 0x2000;
    mJoykey.key3.mask = 0x4000;
    mJoykey.key4.mask = 0x8000;
    mJoykey.key5.mask = 0x0001;
    mJoykey.key6.mask = 0x0002;
    mJoykey.key7.mask = 0x0004;
    mJoykey.key8.mask = 0x0008;
    mJoykey.key9.mask = 0x0010;
    mJoykey.key10.mask = 0x0020;
    mJoykey.key11.mask = 0x0040;
    mJoykey.key12.mask = 0x0080;
    mJoykey.keyAL.mask = 0x00;
    mJoykey.keyAR.mask = 0Xff;
    mJoykey.keyAD.mask = 0xff;
    mJoykey.keyAU.mask = 0x00;

    mJoykey.keyAL.val = 0x7f;
    mJoykey.keyAR.val = 0x7f;
    mJoykey.keyAD.val = 0x7f;
    mJoykey.keyAU.val = 0x7f;

}
*/

