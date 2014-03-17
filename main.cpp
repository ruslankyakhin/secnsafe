#include <csettings.h>
#include <cfilesanalize.h>
#include <creport.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "usage: " <<  argv[0] << " <-init|-check>" << endl;
        return -1;
    }

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    CFilesAnalize *analizator = new CFilesAnalize();
    CReport *report           = new CReport();

    //CSettings::instance().loadSettings("/etc/secnsafe/secnsafe.conf");
    //CSettings::instance().setValue("dbfolder","/etc/secnsafe"

    CSettings::instance().loadSettings("C:/Users/test/Documents/secnsafe/secnsafe.conf");
    CSettings::instance().setValue("dbfolder","C:/Users/test/Documents/secnsafe/");

    if(qstrcmp(argv[1],"-init") == 0) {
        QStringList paths = CSettings::instance().getValue("path").split(",");
        foreach(QString path,paths){
            analizator->setFileTypes(CSettings::instance().getValue("filetypes"));
            analizator->setExclusions(CSettings::instance().getValue("exclusions"));
            analizator->getState(path);
        }
    }
    else if(qstrcmp(argv[1],"-check") == 0) {
         QStringList paths = CSettings::instance().getValue("path").split(",");
         foreach(QString path,paths){
             analizator->setFileTypes(CSettings::instance().getValue("filetypes"));
             analizator->setExclusions(CSettings::instance().getValue("exclusions"));
             analizator->checkState(path);

             report->setAddedItems(analizator->getAddedItems());
             report->setChangedItmes(analizator->getChangedItmes());
             report->setDeletedItmes(analizator->getDeletedItmes());

             report->showReport();
         }
    }
    else {
        cout << "usage: " <<  argv[0] << " <-init|-check>" << endl;
        return -1;
    }
    return 0;
}
