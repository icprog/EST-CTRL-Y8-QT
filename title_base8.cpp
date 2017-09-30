#include "title_base8.h"
#include "resource_manager.h"

CTitleBase8::CTitleBase8(QWidget *parent) :
    CTitleBase(parent)
{
    setObjectName("CTitleBase8");

    resize(SYS_WID(600),SYS_HEI(50));

    pLabelIcon[0] = new QLabel(this);
    pLabelIcon[1] = new QLabel(this);
    pLabelIcon[2] = new QLabel(this);
    pLabelIcon[3] = new QLabel(this);

    pLabelIcon[0]->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_TITLE_LOGO"));
    pLabelIcon[1]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_TITLE_BACK"));
    pLabelIcon[2]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_OFF"));
    pLabelIcon[3]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_OFF"));

    pLabelIcon[0]->setGeometry(SYS_WID(0),   SYS_HEI(0), SYS_WID(90), SYS_HEI(50));
    pLabelIcon[1]->setGeometry(SYS_WID(100), SYS_HEI(0), SYS_WID(90), SYS_HEI(50));
    pLabelIcon[2]->setGeometry(SYS_WID(200), SYS_HEI(0), SYS_WID(90), SYS_HEI(50));
    pLabelIcon[3]->setGeometry(SYS_WID(300), SYS_HEI(0), SYS_WID(90), SYS_HEI(50));

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(208,235,245));
    setPalette(pal);

    QFont font;
    font.setPixelSize(SYS_FONT(16));

    pLabelIcon[1]->setFont(font);
    pLabelIcon[2]->setFont(font);

    pLabelIcon[1]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    pLabelIcon[2]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

}


void CTitleBase8::OnTitleFresh()
{

    QString mStr,temp,strDate,strTime;

    QTime ts=QTime::currentTime();
    QDate dt=QDate::currentDate();

    strDate.sprintf("%2d.%02d.%02d",dt.year(),dt.month(),dt.day());
    strTime.sprintf("%02d:%02d:%02d",ts.hour(),ts.minute(),ts.second());

    mStr = strDate.right(8);
    mStr += "\n";
    mStr += strTime;
    pLabelIcon[1]->setText(mStr);

    if(g_dbsys.utility.mTubeTempShow)
    {
        mStr = QApplication::translate("CTitleBase", "Tube:");
        mStr += "\n";
        temp.setNum(g_systemDb->g_dbMachine.StateData[3] + g_dbsys.utility.mTemperatureAdj);
        mStr += temp;
        pLabelIcon[2]->setText(mStr);
    }else
    {
        pLabelIcon[2]->setText("");
    }
}
