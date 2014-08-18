#ifndef ECONOMIC_H
#define ECONOMIC_H

#include "main.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QScriptValue>
#include <QScriptEngine>
#include <QObject>
#include <QDebug>

class economic: public QObject
{
   Q_OBJECT
   public:
    economic();
    void GetEconomicData();
    bool DataLoaded;
    bool LoadError;
   public slots:
    void finishedSlot(QNetworkReply* reply);
   private:
    QNetworkAccessManager* nam;



};

#endif // ECONOMIC_H


