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

    QString confPath = "C:/Users/test/Documents/secnsafe";
    //QString confPath = "/etc/secnsafe";

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    CFilesAnalize *analizator = new CFilesAnalize();
    CReport *report           = new CReport();
    CSettings &settings       = CSettings::instance();

    settings.setConfPath(confPath);
    settings.loadSettings(confPath + "/secnsafe.conf");

    if(qstrcmp(argv[1],"-init") == 0) {
        foreach(QString path, settings.getPaths()){
            analizator->setFileTypes(settings.getValue(path, "filetypes"));
            analizator->setExclusions(settings.getValue(path, "exclusions"));
            analizator->getState(path);
        }
    }
    else if(qstrcmp(argv[1],"-check") == 0) {
            foreach(QString path, settings.getPaths()){
                analizator->setFileTypes(settings.getValue(path, "filetypes"));
                analizator->setExclusions(settings.getValue(path, "exclusions"));
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
