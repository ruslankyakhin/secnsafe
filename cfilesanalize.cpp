#include "cfilesanalize.h"

CFilesAnalize::CFilesAnalize()
{
}

QString CFilesAnalize::getMarker(QFileInfo info)
{
    return QString::number(info.size());
}

void CFilesAnalize::setExclusions(QString exclusions)
{
    foreach(QString exclusion,exclusions.split(","))
    {
        exclusions_ << exclusion;
    }
}

void CFilesAnalize::setFileTypes(QString fileTypes)
{
    foreach(QString fileType,fileTypes.split(","))
    {
        fileTypes_ << fileType;
    }
}

void CFilesAnalize::serializeData(QString path,QHash<QString, QString> data)
{
    QFileInfo info(path);
    QString database = CSettings::instance().getValue("dbfolder") + "/" + info.fileName() + ".db";

    QFile file(database);
    if(file.open(QIODevice::WriteOnly)){
        QDataStream stream(&file);
        stream << data;
        file.close();
    }
}

QHash<QString, QString> CFilesAnalize::deserializeData(QString path)
{
    QHash<QString, QString> data;
    QFileInfo info(path);
    QString database = CSettings::instance().getValue("dbfolder") + "/" + info.fileName() + ".db";

    if(QFile::exists(database)){
        QFile file(database);
        if(file.open(QIODevice::ReadOnly)){
            QDataStream stream(&file);
            stream >> data;
            file.close();
        }
    }
    return data;
}

void CFilesAnalize::getState(QString path)
{
    QHash<QString, QString> filesInfo;
    QDirIterator dirIterator(path, fileTypes_, QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::System | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    while (dirIterator.hasNext()) {
        dirIterator.next();

        QString marker   = getMarker(dirIterator.fileInfo());
        QString filePath = dirIterator.fileInfo().filePath();

        bool isExcluded = false;

        foreach(QString exclusion, exclusions_) {
            if(filePath.contains(QRegExp("^" + exclusion + "$"))){
                isExcluded = true;
            }
        }

        if(!isExcluded) {
            filesInfo.insert(filePath,marker);
        }
    }
    serializeData(path,filesInfo);
}

void CFilesAnalize::checkState(QString path)
{
     QHash<QString, QString> filesInfo = deserializeData(path);

     if(filesInfo.count() <= 0 )
     {
         return;
     }

     QDirIterator dirIterator(path, fileTypes_, QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::System | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

     while (dirIterator.hasNext()) {
         dirIterator.next();

         QString marker   = getMarker(dirIterator.fileInfo());
         QString filePath = dirIterator.fileInfo().filePath();

         bool isExcluded = false;

         foreach(QString exclusion, exclusions_) {
             if(filePath.contains(QRegExp("^" + exclusion + "$"))){
                 isExcluded = true;
             }
         }

         if(!isExcluded) {
             if(!filesInfo.contains(filePath)){
                 QString info = dirIterator.fileInfo().lastModified().toString();
                 QString size = QString::number(dirIterator.fileInfo().size());

                 addedItems_.insert(filePath,info + " " + size + " " + filePath);
             }
             else {
                 if(filesInfo[filePath] != marker) {
                     QString info = dirIterator.fileInfo().lastModified().toString();
                     QString size = QString::number(dirIterator.fileInfo().size());

                     changedItems_.insert(filePath,info + " " + size + " " + filePath);
                 }
                 filesInfo.remove(filePath);
             }
         }
     }
     foreach(QString key, filesInfo.keys()){
         bool isExcluded = false;

         foreach(QString exclusion, exclusions_) {
             if(key.contains(QRegExp("^" + exclusion + "$"))){
                 isExcluded = true;
             }
         }
         if(!isExcluded) {
             deletedItems_.insert(key, key);
         }
     }
}
QHash<QString, QString> CFilesAnalize::getAddedItems()
{
    return addedItems_;
}

QHash<QString, QString> CFilesAnalize::getChangedItmes()
{
    return changedItems_;
}

QHash<QString, QString> CFilesAnalize::getDeletedItmes()
{
    return deletedItems_;
}
