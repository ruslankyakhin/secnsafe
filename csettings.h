#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QFile>
#include <QHash>
#include <QtCore>
#include <iostream>

using namespace std;

class CSettings
{
    private:\
        static CSettings instance_;
        QHash<QString,QHash<QString,QString> > settings_;
    public:
        CSettings();
        static CSettings& instance();
        void loadSettings(QString settingsFile);
        void setValue(QString name, QString value);
        QString getValue(QString name);
};

#endif // CSETTINGS_H
