#include "title_base12.h"
#include "resource_manager.h"

CTitleBase12::CTitleBase12(QWidget *parent) :
    CTitleBase(parent)
{
    setObjectName("CTitleBase12");

    pLabelIcon[0] = new QLabel(this);
    pLabelIcon[1] = new QLabel(this);

    pLabelIcon[0]->setStyleSheet(g_skinBase->GetStyleMapStr("CEIL8_TITLE_LOGO"));
    pLabelIcon[1]->setStyleSheet(g_skinBase->GetStyleMapStr("BASE8_TITLE_BACK"));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(208,235,245)");
    }

    QFont font;
    font.setPixelSize(SYS_FONT(18));

    // pLabelIcon[0]->setFont(font);
    pLabelIcon[1]->setFont(font);

    // pLabelIcon[0]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    pLabelIcon[1]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    OnViewDirChange(g_systemDb->g_startAngle);

}


void CTitleBase12::OnTitleFresh()
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
        //pLabelIcon[2]->setText(mStr);
    }else
    {
        //pLabelIcon[2]->setText("");
    }
}
void CTitleBase12::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(208),SYS_WID(208));
        pLabelIcon[0]->setGeometry(SYS_HEI(0),   SYS_WID(64), SYS_HEI(117), SYS_WID(80));
        pLabelIcon[1]->setGeometry(SYS_HEI(117), SYS_WID(64), SYS_HEI(90), SYS_WID(72));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(208),SYS_HEI(208));
        pLabelIcon[0]->setGeometry(SYS_WID(0),   SYS_HEI(64), SYS_WID(117), SYS_HEI(80));
        pLabelIcon[1]->setGeometry(SYS_WID(117), SYS_HEI(64), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(208),SYS_HEI(208));
        pLabelIcon[0]->setGeometry(SYS_WID(0),   SYS_HEI(64), SYS_WID(117), SYS_HEI(80));
        pLabelIcon[1]->setGeometry(SYS_WID(117), SYS_HEI(64), SYS_WID(90), SYS_HEI(72));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }
}
