#ifndef VOTINGMETHOD_H
#define VOTINGMETHOD_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include "FaceRecognitionTest/_Image.h"

namespace Ui {
class votingMethod;
}

class votingMethod : public QWidget
{
    Q_OBJECT

public:

    explicit votingMethod(std::vector<std::vector<_Image>> database, std::vector<_Image> dataset, QMultiMap<int, int> randPixMask,
                          QWidget *parent = 0);
    ~votingMethod();


    void getDatabase(std::vector<std::vector<_Image>>);
    void getDataset(std::vector<_Image>);
    void getRandPixMask(QMultiMap<int, int>);

signals:
    void mainWindow();

private slots:
    void on_exitButton_clicked();
    void on_nextImageButton_clicked();
    void on_prevImageButton_clicked();

private:
    int it = 0;

    Ui::votingMethod *ui;

    QMultiMap<int, int> randPixMask;
    std::vector<std::vector<_Image>> database;
    std::vector<_Image> dataset;

};

#endif // VOTINGMETHOD_H
