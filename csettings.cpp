#include "csettings.h"

CSettings CSettings::instance_;

CSettings::CSettings()
{

}

CSettings& CSettings::instance()
{
    return instance_;
}

void CSettings::loadSettings(QString settingsFile)
{
    if(QFile::exists(settingsFile)) {
        QSettings settings(settingsFile, QSettings::IniFormat);
        foreach(QString group, settings.childGroups()) {
            settings.beginGroup(group);
            QString path = settings.value("path").toString();
            QHash<QString,QString> keysValues;
            foreach (QString key, settings.childKeys()) {
                QString value = settings.value(key).toString();
                if(path != value) {
                    keysValues.insert(key,value);
                }
            }
            settings_.insert(path,keysValues);
            settings.endGroup();
        }
    }
    else {
        cout << "Settings file " + settingsFile.toStdString() + " should be available." << endl;
    }
}
QString CSettings::getValue(QString path, QString name)
{
   // return settings_[name].replace("\"","").trimmed();
    return "";
}

QStringList CSettings::getPaths()
{
    return settings_.keys();
}

QString CSettings::getConfPath()
{
    return confPath;
}
void CSettings::setConfPath(QString path)
{
    confPath = path;
}
