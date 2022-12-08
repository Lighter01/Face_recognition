#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QTimer>

#include "FaceRecognitionTest/_Image.h"
//#include "FaceRecognitionTest/recognition_call.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QTimer::singleShot(0, this, SLOT(showFullScreen()));
    setFixedSize(size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getDatabase(std::vector<std::vector<_Image>> database)
{
    this->database = database;
    return;
}
void MainWindow::getDataset(std::vector<_Image> dataset)
{
    this->dataset = dataset;
    return;
}
void MainWindow::getRandPixMask(QMultiMap<int, int> randPixMask)
{
    this->randPixMask = randPixMask;
    return;
}

void MainWindow::on_votingPushButton_clicked()
{
    votingWindow = new votingMethod(database, dataset, randPixMask);
    connect(votingWindow, &votingMethod::mainWindow, this, &MainWindow::show);
    votingWindow->getDatabase(this->database);
    votingWindow->getDataset(this->dataset);

    votingWindow->show();
    this->close();
}
void MainWindow::on_histogramPushButton_clicked()
{
    histogramWindow = new histogramMethod(database, dataset);
    connect(histogramWindow, &histogramMethod::mainWindow, this, &MainWindow::show);
    histogramWindow->getDatabase(this->database);
    histogramWindow->getDataset(this->dataset);

    histogramWindow->show();
    this->close();
}
void MainWindow::on_scalingPushButton_clicked()
{
    scalingWindow = new scalingMethod(database, dataset);
    connect(scalingWindow, &scalingMethod::mainWindow, this, &MainWindow::show);
    scalingWindow->getDatabase(this->database);
    scalingWindow->getDataset(this->dataset);

    scalingWindow->show();
    this->close();
}
void MainWindow::on_randomPushButton_clicked()
{
    randomWindow = new randomMethod(database, dataset, randPixMask);
    connect(randomWindow, &randomMethod::mainWindow, this, &MainWindow::show);
    randomWindow->getDatabase(this->database);
    randomWindow->getDataset(this->dataset);
    randomWindow->getRandPixMask(this->randPixMask);

    randomWindow->show();
    this->close();
}
void MainWindow::on_lbphPushButton_clicked()
{
    lbphWindow = new lbphMethod(database, dataset, randPixMask);
    connect(lbphWindow, &lbphMethod::mainWindow, this, &MainWindow::show);
    lbphWindow->getDatabase(this->database);
    lbphWindow->getDataset(this->dataset);
    lbphWindow->show();
    this->close();
}
