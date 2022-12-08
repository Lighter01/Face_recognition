#ifndef LBPHMETHOD_H
#define LBPHMETHOD_H

#include "FaceRecognitionTest/_Image.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

#include <QWidget>
//#include <QPushButton>

namespace Ui {
class lbphMethod;
}

class lbphMethod : public QWidget
{
    Q_OBJECT

private:
    QMultiMap<int, int> randPixMask;
    std::vector<std::vector<_Image>> database;
    std::vector<_Image> dataset;

public:
    explicit lbphMethod(std::vector<std::vector<_Image>> database, std::vector<_Image> dataset, QMultiMap<int, int> randPixMask,
                        QWidget *parent = nullptr);
    ~lbphMethod();

    void getDatabase(std::vector<std::vector<_Image>>);
    void getDataset(std::vector<_Image>);
    void getRandPixMask(QMultiMap<int, int>);

    int findDistance(_Image& , _Image& );

signals:
    void mainWindow();

private slots:
    void on_exitButton_clicked();
    void on_nextImageButton_clicked();
    void on_prevImageButton_clicked();

private:
    int it = 0;
    int avg_dist = 0;
    int faults = 0;

    QtCharts::QLineSeries *upper_bound_test, *upper_bound_answer;

    QtCharts::QAreaSeries *series_test, *series_answer;

    QtCharts::QChart *chart_test, *chart_answer;

    QtCharts::QChartView *chartView, *chartView_2;

    Ui::lbphMethod *ui;
};

#endif // LBPHMETHOD_H
