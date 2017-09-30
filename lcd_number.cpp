#include "lcd_number.h"
#include <QPainter>
#include <QCoreApplication>

#include "resource_manager.h"

#define LCD_WID 60
#define LCD_HEI 110
#define LCD_CH_WID 20

CLcdNumber::CLcdNumber(QWidget *parent) :
    QWidget(parent)
{

    setGeometry(0,0,SYS_WID(LCD_WID),SYS_HEI(LCD_HEI));

    //set background image

#ifdef QT_ARCH_ARM
#else
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QColor(36,36,36)));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
#endif

    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num0.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num1.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num2.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num3.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num4.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num5.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num6.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num7.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num8.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num9.png);}"));
    numberHolder.append( QString("QFrame{ border-image: url(:/QRes/8090/png00/num-.png);}"));
    numberHolder.append( QString("background: transparent"));

    QFrame * pframe;
    pframe = new QFrame(this);
    pframe->setGeometry(SYS_WID(0),SYS_HEI(-10),SYS_WID(46),SYS_HEI(29));
    pframe->setStyleSheet(numberHolder.at(11));
    pframe->setVisible(false);
    pframe->raise();
    imgHolder.append(pframe);

    pframe = new QFrame(this);
    pframe->setGeometry(SYS_WID(0),SYS_HEI(5),SYS_WID(46),SYS_HEI(29));
    pframe->setStyleSheet(numberHolder.at(1));
    pframe->setVisible(false);
    pframe->raise();
    imgHolder.append(pframe);

    pframe = new QFrame(this);
    pframe->setGeometry(SYS_WID(0),SYS_HEI(25),SYS_WID(46),SYS_HEI(29));
    pframe->setStyleSheet(numberHolder.at(2));
    pframe->setVisible(false);
    pframe->raise();
    imgHolder.append(pframe);

    pframe = new QFrame(this);
    pframe->setGeometry(SYS_WID(0),SYS_HEI(45),SYS_WID(46),SYS_HEI(29));
    pframe->setStyleSheet(numberHolder.at(3));
    pframe->setVisible(false);
    pframe->raise();
    imgHolder.append(pframe);

    pframe = new QFrame(this);
    pframe->setGeometry(SYS_WID(0),SYS_HEI(65),SYS_WID(46),SYS_HEI(29));
    pframe->setStyleSheet(numberHolder.at(4));
    pframe->setVisible(false);
    pframe->raise();
    imgHolder.append(pframe);

    pframe = new QFrame(this);
    pframe->setGeometry(SYS_WID(0),SYS_HEI(85),SYS_WID(46),SYS_HEI(29));
    pframe->setStyleSheet(numberHolder.at(5));
    pframe->setVisible(false);
    pframe->raise();
    imgHolder.append(pframe);

    NumCounts = 32767;
    gDispBuffer = 32767;
}
void CLcdNumber::display(int dat)
{

    //数据相同，不重复显示
    if(gDispBuffer == dat)
        return;
    else
        gDispBuffer = dat;

    int num0,num1,num2,num3,num4;
    bool iconOn = false;

    if(dat < 0)
    {
        iconOn = true;
        dat *= -1;
    }

    //high byte first
    num0 = dat / 10000;
    if(num0 >= 9 )
        num0 = 9;

    if(num0 == 0)
        NumCounts = 4;
    else
        NumCounts = 5;

    dat %= 10000;

    //high byte 4
    num1 = dat / 1000;
    if(num1 >= 9)
        num1 = 9;

    if(num1 == 0 && NumCounts == 4)
        NumCounts = 3;

    dat %= 1000;

    //high byte 3
    num2 = dat / 100;
    if(num2 >= 9)
        num2 = 9;

    if(num2 == 0 && NumCounts == 3)
        NumCounts = 2;

    dat %= 100;


    //high byte 2
    num3 = dat / 10;
    if(num3 >= 9)
        num3 = 9;

    if(num3 == 0 && NumCounts == 2)
        NumCounts = 1;

    //high byte last
    dat %= 10;
    num4 = dat ;
    if(num4 >= 9)
        num4 = 9;

    switch(NumCounts)
    {
    case 5:
        gPosYStart = -10;
        imgHolder.at(1)->move(SYS_WID(5),SYS_HEI(5));
        imgHolder.at(1)->setStyleSheet(numberHolder.at(num0));
        imgHolder.at(1)->setVisible(true);
        imgHolder.at(2)->move(SYS_WID(5),SYS_HEI(25));
        imgHolder.at(2)->setStyleSheet(numberHolder.at(num1));
        imgHolder.at(2)->setVisible(true);
        imgHolder.at(3)->move(SYS_WID(5),SYS_HEI(45));
        imgHolder.at(3)->setStyleSheet(numberHolder.at(num2));
        imgHolder.at(3)->setVisible(true);
        imgHolder.at(4)->move(SYS_WID(5),SYS_HEI(65));
        imgHolder.at(4)->setStyleSheet(numberHolder.at(num3));
        imgHolder.at(4)->setVisible(true);
        imgHolder.at(5)->move(SYS_WID(5),SYS_HEI(85));
        imgHolder.at(5)->setStyleSheet(numberHolder.at(num4));
        imgHolder.at(5)->setVisible(true);
        break;
    case 4:
        gPosYStart = 0;
        imgHolder.at(1)->move(SYS_WID(5),SYS_HEI(15));
        imgHolder.at(1)->setStyleSheet(numberHolder.at(num1));
        imgHolder.at(1)->setVisible(true);
        imgHolder.at(2)->move(SYS_WID(5),SYS_HEI(35));
        imgHolder.at(2)->setStyleSheet(numberHolder.at(num2));
        imgHolder.at(2)->setVisible(true);
        imgHolder.at(3)->move(SYS_WID(5),SYS_HEI(55));
        imgHolder.at(3)->setStyleSheet(numberHolder.at(num3));
        imgHolder.at(3)->setVisible(true);
        imgHolder.at(4)->move(SYS_WID(5),SYS_HEI(75));
        imgHolder.at(4)->setStyleSheet(numberHolder.at(num4));
        imgHolder.at(4)->setVisible(true);
        imgHolder.at(5)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(5)->setVisible(false);
        break;
    case 3:
        gPosYStart = 10;
        imgHolder.at(1)->move(SYS_WID(5),SYS_HEI(25));
        imgHolder.at(1)->setStyleSheet(numberHolder.at(num2));
        imgHolder.at(1)->setVisible(true);
        imgHolder.at(2)->move(SYS_WID(5),SYS_HEI(45));
        imgHolder.at(2)->setStyleSheet(numberHolder.at(num3));
        imgHolder.at(2)->setVisible(true);
        imgHolder.at(3)->move(SYS_WID(5),SYS_HEI(65));
        imgHolder.at(3)->setStyleSheet(numberHolder.at(num4));
        imgHolder.at(3)->setVisible(true);
        //imgHolder.at(4)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(4)->setVisible(false);
        //imgHolder.at(5)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(5)->setVisible(false);
        break;
    case 2:
        gPosYStart = 20;
        imgHolder.at(1)->move(SYS_WID(5),SYS_HEI(35));
        imgHolder.at(1)->setStyleSheet(numberHolder.at(num3));
        imgHolder.at(1)->setVisible(true);
        imgHolder.at(2)->move(SYS_WID(5),SYS_HEI(55));
        imgHolder.at(2)->setStyleSheet(numberHolder.at(num4));
        imgHolder.at(2)->setVisible(true);
        // imgHolder.at(3)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(3)->setVisible(false);
        //imgHolder.at(4)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(4)->setVisible(false);
        //imgHolder.at(5)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(5)->setVisible(false);
        break;
    case 1:
        gPosYStart = 30;
        imgHolder.at(1)->move(SYS_WID(5),SYS_HEI(45));
        imgHolder.at(1)->setStyleSheet(numberHolder.at(num4));
        imgHolder.at(1)->setVisible(true);
        //imgHolder.at(2)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(2)->setVisible(false);
        //imgHolder.at(3)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(3)->setVisible(false);
        //imgHolder.at(4)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(4)->setVisible(false);
        //imgHolder.at(5)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(5)->setVisible(false);
        break;
    }

    if(iconOn)
    {
        imgHolder.at(0)->move(SYS_WID(0),SYS_HEI(gPosYStart));
        imgHolder.at(0)->setStyleSheet(numberHolder.at(10));
        imgHolder.at(0)->setVisible(true);
    }else
    {
        imgHolder.at(0)->setStyleSheet(numberHolder.at(11));
        imgHolder.at(0)->setVisible(false);
    }

}
