#ifndef SCALINGMETHOD_H
#define SCALINGMETHOD_H

#include <QWidget>
#include "FaceRecognitionTest/_Image.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
//#include <QPushButton>

namespace Ui {
class scalingMethod;
}

class scalingMethod : public QWidget
{
    Q_OBJECT

private:
    Ui::scalingMethod *ui;

    int it = 0;

    QMultiMap<int, int> randPixMask;
    std::vector<std::vector<_Image>> database;
    std::vector<_Image> dataset;

    QtCharts::QLineSeries *upper_bound_test, *upper_bound_answer;

    QtCharts::QAreaSeries *series_test, *series_answer;

    QtCharts::QChart *chart_test, *chart_answer;

    QtCharts::QChartView *chartView, *chartView_2;

public:
    explicit scalingMethod(std::vector<std::vector<_Image>> database, std::vector<_Image> dataset,
                           QWidget *parent = nullptr);
    ~scalingMethod();

    void getDatabase(std::vector<std::vector<_Image>>);
    void getDataset(std::vector<_Image>);
    void getRandPixMask(QMultiMap<int, int>);

signals:
    void mainWindow();

private slots:
    void on_nextImageButton_clicked();
    void on_prevImageButton_clicked();
    void on_exitButton_clicked();

};

std::vector<int> getScaledImageHist(_Image& ); // Already exist in histogram_mathod.h, remove later

#endif // SCALINGMETHOD_H
