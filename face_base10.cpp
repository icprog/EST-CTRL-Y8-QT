#include <QSettings>
#include <QFileInfo>

#include "resource_manager.h"
#include "face_base10.h"

CFaceBase10::CFaceBase10( QWidget* parent):
    CFaceBase(parent)
{

    setObjectName("CFaceBase10");

    resize(g_sysWidth,g_sysHeight);

    QFont font;
    font.setPixelSize(SYS_FONT(24));

    QSettings * configClientInfo = new QSettings(QCoreApplication::applicationDirPath() + "/clientinfo.ini",QSettings::IniFormat);
    QString hostpitalName = "    ";
    hostpitalName  += QString::fromUtf8(configClientInfo->value("/client/HospitalName","伊士通(上海)医疗器械有限公司").toByteArray());

    hostpitalName += "\n                                        v:";

    hostpitalName += g_dbsys.softVersion;

    hostpitalName += "\n                                        d:";

    QFileInfo * pMainProgramInfo = new QFileInfo(QCoreApplication::applicationFilePath());
    QDateTime mDate = pMainProgramInfo->lastModified();

    hostpitalName += mDate.toString(Qt::ISODate).left(10);

    stHospital->setFont(font);
    stHospital->setText(hostpitalName);

    infoView->setGeometry(SYS_WID(100),0,SYS_WID(50),g_sysHeight);
    infoView->rotate(90);

    barView->setGeometry(SYS_WID(50 ),0,SYS_WID(40),g_sysHeight);
    barView->rotate(90);

    versionView->setGeometry(SYS_WID(680 ),0,SYS_WID(100),g_sysWidth);
    versionView->rotate(90);

}


