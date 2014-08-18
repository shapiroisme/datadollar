#include "economic.h"

economic::economic()
{
    nam = new QNetworkAccessManager(this);
    DataLoaded = false;
    LoadError = false;
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
}

void economic::GetEconomicData()
{
    QUrl url("http://datadollar.info/GDPs.json");
    nam->get(QNetworkRequest(url));
}

void economic::finishedSlot(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QString data = reply->readAll();

        QScriptValue value;
        QScriptEngine engine;
        value = engine.evaluate("(" + data + ")");

        if(value.property("MaxMoney").isNumber()) {
            MAX_MONEY = value.property("MaxMoney").toNumber();
        } else {
            LoadError = true;
        }
    }
    else
    {
        LoadError = true;
    }
    DataLoaded = true;
}


// { "MaxMoney":12332434234 }
