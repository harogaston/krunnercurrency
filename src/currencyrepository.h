#pragma once

#include<QMap>
#include<QString>
#include <qstringliteral.h>

class CurrencyRepository 
{

public:
    static QMap<QString, QString> currencies;
};