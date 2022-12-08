#ifndef HISTOGRAMMETHOD_H
#define HISTOGRAMMETHOD_H

#include "FaceRecognitionTest/_Image.h"

#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QWidget>
//#include <QPushButton>

namespace Ui {
class histogramMethod;
}

class histogramMethod : public QWidget
{
    Q_OBJECT

public:
    explicit histogramMethod(std::vector<std::vector<_Image>> database, std::vector<_Image> dataset,
                             QWidget *parent = nullptr);
    ~histogramMethod();

    void getDatabase(std::vector<std::vector<_Image>>);
    void getDataset(std::vector<_Image>);
    void getRandPixMask(QMultiMap<int, int>);

signals:
    void mainWindow();

private slots:
    void on_nextImageButton_clicked();
    void on_prevImageButton_clicked();
    void on_exitButton_clicked();

private:
    int it = 0;

    QtCharts::QBarSet *test_set;
    QtCharts::QBarSet *answer_set;

    QtCharts::QBarSeries *test_series;
    QtCharts::QBarSeries *answer_series;

    QtCharts::QChart *histograms;

    QStringList test_categories;

    QtCharts::QBarCategoryAxis *axisX;

    QtCharts::QValueAxis *axisY;

    QtCharts::QChartView *chartView;

    QMultiMap<int, int> randPixMask;
    std::vector<std::vector<_Image>> database;
    std::vector<_Image> dataset;

    Ui::histogramMethod *ui;
};

#endif // HISTOGRAMMETHOD_H
