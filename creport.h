#ifndef CREPORT_H
#define CREPORT_H

#include <QtCore>
#include <QtNetwork/QHostInfo>
#include <iostream>

using namespace std;

class CReport
{
    private:
        QHash<QString, QString> addedItems_;
        QHash<QString, QString> changedItems_;
        QHash<QString, QString> deletedItems_;
    public:
        CReport();

        void setAddedItems(QHash<QString, QString> data);
        void setChangedItmes(QHash<QString, QString> data);
        void setDeletedItmes(QHash<QString, QString> data);\

        void showReport();
};

#endif // CREPORT_H
