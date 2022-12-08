#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FaceRecognitionTest/_Image.h"

#include <QMainWindow>
#include <QPushButton>

#include <votingmethod.h>
#include <histogrammethod.h>
#include <scalingmethod.h>
#include <randommethod.h>
#include <lbphmethod.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getDatabase(std::vector<std::vector<_Image>>);
    void getDataset(std::vector<_Image>);
    void getRandPixMask(QMultiMap<int, int>);

private slots:
    void on_votingPushButton_clicked();
    void on_histogramPushButton_clicked();
    void on_scalingPushButton_clicked();
    void on_randomPushButton_clicked();
    void on_lbphPushButton_clicked();

private:
    Ui::MainWindow *ui;

    QMultiMap<int, int> randPixMask;
    std::vector<std::vector<_Image>> database;
    std::vector<_Image> dataset;

    votingMethod *votingWindow;
    histogramMethod *histogramWindow;
    scalingMethod *scalingWindow;
    randomMethod *randomWindow;
    lbphMethod *lbphWindow;
};
#endif // MAINWINDOW_H
