#include <QSettings>
#include <QFileInfo>

#include "resource_manager.h"
#include "face_base8.h"

CFaceBase8::CFaceBase8( QWidget* parent):
    CFaceBase(parent)
{
    setObjectName("CFaceBase8");

    resize(g_sysWidth,g_sysHeight);

    QFont font;
    font.setPixelSize(SYS_FONT(24));

    QSettings * configClientInfo = new QSettings(QCoreApplication::applicationDirPath() + "/clientinfo.ini",QSettings::IniFormat);
    QString hostpitalName = "    ";
    hostpitalName  += QString::fromUtf8(configClientInfo->value("/client/HospitalName","            伊士通(上海)医疗器械有限公司").toByteArray());

    hostpitalName += "\n                                                    v:";

    hostpitalName += g_dbsys.softVersion;

    hostpitalName += "\n                                                    d:";

    QFileInfo * pMainProgramInfo = new QFileInfo(QCoreApplication::applicationFilePath());
    QDateTime mDate = pMainProgramInfo->lastModified();

    hostpitalName += mDate.toString(Qt::ISODate).left(10);

    stHospital->setFont(font);
    stHospital->setText(hostpitalName);

    infoView->setGeometry(0,SYS_HEI(460),g_sysWidth,SYS_HEI(50));

    barView->setGeometry(0,SYS_HEI(555),g_sysWidth,SYS_HEI(50));

}
