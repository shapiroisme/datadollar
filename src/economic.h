#ifndef ECONOMIC_H
#define ECONOMIC_H

#include "main.h"

#include "boost/asio.hpp"
#include <QObject>

#include <string>
#include <list>
#include <map>

#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_writer_template.h"
#include "json/json_spirit_utils.h"

using namespace std;
using namespace json_spirit;

class economic: public QObject
{
   Q_OBJECT
   public:
    economic();
    void GetEconomicData();
    bool DataLoaded;
    bool LoadError;
};

#endif // ECONOMIC_H


