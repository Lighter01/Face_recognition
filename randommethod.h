#ifndef RANDOMMETHOD_H
#define RANDOMMETHOD_H

#include <QWidget>
#include "FaceRecognitionTest/_Image.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
//#include <QPushButton>

namespace Ui {
class randomMethod;
}

class randomMethod : public QWidget
{
    Q_OBJECT

private:
    Ui::randomMethod *ui;

    int it = 0;

    QMultiMap<int, int> randPixMask;
    std::vector<std::vector<_Image>> database;
    std::vector<_Image> dataset;

    QtCharts::QLineSeries *upper_bound_test, *upper_bound_answer;

    QtCharts::QAreaSeries *series_test, *series_answer;

    QtCharts::QChart *chart_test, *chart_answer;

    QtCharts::QChartView *chartView, *chartView_2;

public:
    explicit randomMethod(std::vector<std::vector<_Image>> database, std::vector<_Image> dataset, QMultiMap<int, int> randPixMask,
                          QWidget *parent = nullptr);
    ~randomMethod();

    void getDatabase(std::vector<std::vector<_Image>>);
    void getDataset(std::vector<_Image>);
    void getRandPixMask(QMultiMap<int, int>);

    QImage colorizePixels(_Image& );

    int findDistance(_Image& , _Image& );

signals:
    void mainWindow();

private slots:
    void on_nextImageButton_clicked();
    void on_prevImageButton_clicked();
    void on_exitButton_clicked();

};

#endif // RANDOMMETHOD_H
