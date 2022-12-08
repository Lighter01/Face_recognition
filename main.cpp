#include "mainwindow.h"
#include <QApplication>

#include "FaceRecognitionTest/recognition_call.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMultiMap<int, int> randomPixMask;
    std::vector<std::vector<_Image>> database;
    std::vector<_Image> dataset;
    //TODO: rewrite "prepareData" function and  remove dataBase_size and dataSet_size variables, they are useless and ugly
    prepareData(database, dataset, randomPixMask, 0, 0, random);

    MainWindow w;
    w.getDatabase(database);
    w.getDataset(dataset);
    w.getRandPixMask(randomPixMask);
    w.show();

    return a.exec();
}
