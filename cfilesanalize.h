#ifndef CFILESANALIZE_H
#define CFILESANALIZE_H

#include <csettings.h>

class CFilesAnalize
{
    private:
        QString getMarker(QFileInfo info);
        QStringList fileTypes_;
        QStringList exclusions_;

        QHash<QString, QString> addedItems_;
        QHash<QString, QString> changedItems_;
        QHash<QString, QString> deletedItems_;

        QHash<QString, QString> deserializeData(QString path);
        void serializeData(QString path,QHash<QString, QString> data);
    public:
        CFilesAnalize();
        void setFileTypes(QString fileTypes);
        void setExclusions(QString exclusions);
        void getState(QString path);
        void checkState(QString path);

        QHash<QString, QString> getAddedItems();
        QHash<QString, QString> getChangedItmes();
        QHash<QString, QString> getDeletedItmes();
};

#endif // CFILESANALIZE_H
