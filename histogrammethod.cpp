#include "histogrammethod.h"
#include "ui_histogrammethod.h"

#include "FaceRecognitionTest/test_method.h"
#include <QMainWindow>

histogramMethod::histogramMethod(std::vector<std::vector<_Image>> database_t, std::vector<_Image> dataset_t,
                                 QWidget *parent) :
    QWidget(parent),
    it(0),
    database(database_t),
    dataset(dataset_t),
    ui(new Ui::histogramMethod)
{
    ui->setupUi(this);

    int faults_h = 0;

    // Set images
    _Image tmp_test = dataset.at(it);
    _Image tmp_ans = testMethodViz(this->database, this->dataset, manhattan, this->randPixMask, it).second;

    ui->test_image->resize(tmp_test.image.width() * 2, tmp_test.image.height() * 2);
    ui->test_image->show();
    ui->test_image->setPixmap(QPixmap::fromImage(tmp_test.image).scaled(tmp_test.image.width() * 2, tmp_test.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->answer_image->resize(tmp_ans.image.width() * 2, tmp_ans.image.height() * 2);
    ui->answer_image->show();
    ui->answer_image->setPixmap(QPixmap::fromImage(tmp_ans.image).scaled(tmp_ans.image.width() * 2, tmp_ans.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    // Set histogram
    test_set = new QtCharts::QBarSet("тестовое");
    answer_set = new QtCharts::QBarSet("найденное");
    test_set->setColor(Qt::blue);
    answer_set->setColor(Qt::red);
    for (int it: tmp_test.histogram) {
        *test_set << it;
    }
    for (int it: tmp_ans.histogram) {
        *answer_set << it;
    }

    test_series = new QtCharts::QBarSeries();
    answer_series = new QtCharts::QBarSeries();
    test_series->append(test_set);
    answer_series->append(answer_set);
    test_series->setBarWidth(0.9);
    answer_series->setBarWidth(0.9);

    histograms = new QtCharts::QChart();
    histograms->addSeries(test_series);
    histograms->addSeries(answer_series);

    histograms->setTitle("test image histogram");
    histograms->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    int max_hist_value = -1;
    if (tmp_test.histogram.size() != 256)
    {
        // here must be known histogram step
    }
    else
    {
        for (int i = 0; i < tmp_test.histogram.size(); ++i) {
            tmp_test.histogram.at(i) > max_hist_value ? max_hist_value = tmp_test.histogram.at(i) : max_hist_value;
            test_categories << QString::number(i);
        }
    }

    axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(test_categories);
    histograms->addAxis(axisX, Qt::AlignBottom);
    test_series->attachAxis(axisX);

    axisY = new QtCharts::QValueAxis();
    axisY->setRange(0, max_hist_value);
    histograms->addAxis(axisY, Qt::AlignLeft);
    test_series->attachAxis(axisY);

    histograms->legend()->setVisible(true);
    histograms->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QtCharts::QChartView(histograms, ui->histogramWidget);
    chartView->setRubberBand(QtCharts::QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1150, 670);
    chartView->show();

}

histogramMethod::~histogramMethod()
{
    delete ui;
}

void histogramMethod::getDatabase(std::vector<std::vector<_Image>> database)
{
    this->database = database;
    return;
}
void histogramMethod::getDataset(std::vector<_Image> dataset)
{
    this->dataset = dataset;
    return;
}
void histogramMethod::getRandPixMask(QMultiMap<int, int> randPixMask)
{
    this->randPixMask = randPixMask;
    return;
}

void histogramMethod::on_nextImageButton_clicked()
{
    if ( (this->it) + 1 >= this->dataset.size() ) {
        it = -1;
    }
    it++;

    _Image tmp_test = dataset.at(it);
    _Image tmp_ans = testMethodViz(this->database, this->dataset, manhattan, this->randPixMask, it).second;

    ui->test_image->clear();
    ui->test_image->setPixmap(QPixmap::fromImage(tmp_test.image).scaled(tmp_test.image.width() * 2, tmp_test.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->answer_image->clear();
    ui->answer_image->setPixmap(QPixmap::fromImage(tmp_ans.image).scaled(tmp_ans.image.width() * 2, tmp_ans.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    test_set->remove(0, test_set->count());
    answer_set->remove(0, answer_set->count());
    for (int it: tmp_test.histogram) {
        *test_set << it;
    }
    for (int it: tmp_ans.histogram) {
        *answer_set << it;
    }

    int max_hist_value = -1;
    if (tmp_test.histogram.size() != 256)
    {
        // here must be known histogram step
    }
    else
    {
        for (int i = 0; i < tmp_test.histogram.size(); ++i) {
            tmp_test.histogram.at(i) > max_hist_value ? max_hist_value = tmp_test.histogram.at(i) : max_hist_value;
        }
    }

    axisY->setRange(0, max_hist_value);

//    histograms->update();
//    chartView->update(); // what does "update" do?

}

void histogramMethod::on_prevImageButton_clicked()
{
    if ( (this->it) - 1 < 0 ) {
        it = this->dataset.size();
    }
    it--;

    _Image tmp_test = dataset.at(it);
    _Image tmp_ans = testMethodViz(this->database, this->dataset, manhattan, this->randPixMask, it).second;

    ui->test_image->clear();
    ui->test_image->setPixmap(QPixmap::fromImage(tmp_test.image).scaled(tmp_test.image.width() * 2, tmp_test.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->answer_image->clear();
    ui->answer_image->setPixmap(QPixmap::fromImage(tmp_ans.image).scaled(tmp_ans.image.width() * 2, tmp_ans.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    test_set->remove(0, test_set->count());
    answer_set->remove(0, answer_set->count());
    for (int it: tmp_test.histogram) {
        *test_set << it;
    }
    for (int it: tmp_ans.histogram) {
        *answer_set << it;
    }

    int max_hist_value = -1;
    if (tmp_test.histogram.size() != 256)
    {
        // here must be known histogram step
    }
    else
    {
        for (int i = 0; i < tmp_test.histogram.size(); ++i) {
            tmp_test.histogram.at(i) > max_hist_value ? max_hist_value = tmp_test.histogram.at(i) : max_hist_value;
        }
    }

    axisY->setRange(0, max_hist_value);

//    histograms->update();
//    chartView->update(); // what does "update" do?

}

void histogramMethod::on_exitButton_clicked()
{
    this->close();
    emit mainWindow();
}

