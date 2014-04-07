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
    QStringList listPaths;

    if(QFile::exists(settingsFile)) {
        QFile file(settingsFile);
        if(file.open(QFile::ReadOnly) ) {
            while(!file.atEnd()){
                QString line = file.readLine();
                QRegExp regExp(QRegExp::escape("[")+"(.*)"+QRegExp::escape("]"));

                if(regExp.indexIn(line) != -1) {
                    listPaths = regExp.cap(1).split(",");
                }

                QStringList keyValue = line.split("=");

                if (keyValue.count() == 2)
                {
                    foreach(QString path, listPaths)
                    {

                    }
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
   // return settings_[name].replace("\"","").trimmed();
    return "";
}

void CSettings::setValue(QString name, QString value)
{
    //settings_[name] = value;
}
