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
        QFile file(settingsFile);
        if(file.open(QFile::ReadOnly) ) {
            while(!file.atEnd()){
                QString line = file.readLine();
                QStringList splitedLine = line.split("=");
                if(splitedLine.count() > 0) {
                    settings_[splitedLine[0]] = splitedLine[1];
                }
            }
        }
        file.close();
    }
    else {
        cout << "Settings file " + settingsFile.toStdString() + " should be available." << endl;
    }
}
QString CSettings::getValue(QString name)
{
    return settings_[name].replace("\"","").trimmed();
}

void CSettings::setValue(QString name, QString value)
{
    settings_[name] = value;
}
