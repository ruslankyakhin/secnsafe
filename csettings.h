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
        QString confPath;
    public:
        CSettings();
        static CSettings& instance();
        void loadSettings(QString settingsFile);
        void setConfPath(QString path);
        QString getConfPath();

        QString getValue(QString path, QString name);
        QStringList getPaths();
};

#endif // CSETTINGS_H
