#ifndef SKIN_MANAGER_H
#define SKIN_MANAGER_H

#include "skin_base.h"


class CSkinManager : public QObject
{
    Q_OBJECT

public:
    explicit CSkinManager();
    CSkinBase * skinInit(unsigned short ,unsigned short);

private:
    CSkinBase * m_skinBase;
};

#endif // SKIN_MANAGER_H
