#ifndef SKIN_BASE_H
#define SKIN_BASE_H

#include <QWidget>
#include <QMap>

#include "system_defines.h"


class CSkinBase : public QObject
{
    Q_OBJECT

public:
    explicit CSkinBase();

public:
    virtual QString GetStyleMapStr(int);            //获取图标字符串，V1，由序号索引的内容
    virtual QString GetStyleMapStr(QString);        //获取图标字符串，V2，由字符串索引的内容

    void ConfigResource(QString);                   //修改资源位置，默认为程序内部资源
protected:    
    static QMap<int , QString> pMapInt;             //图片资源目录，序号索引
    static QMap<QString , QString> pMapStr;         //图片资源，字符串索引

};

#endif // SKIN_BASE_H
