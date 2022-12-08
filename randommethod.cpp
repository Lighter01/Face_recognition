#include "randommethod.h"
#include "ui_randommethod.h"

#include <QPointF>

#include "FaceRecognitionTest/test_method.h"

randomMethod::randomMethod(std::vector<std::vector<_Image>> database_t, std::vector<_Image> dataset_t, QMultiMap<int, int> randPixMask_t,
                           QWidget *parent) :
    QWidget(parent),
    ui(new Ui::randomMethod),
    it(0),
    randPixMask(randPixMask_t),
    database(database_t),
    dataset(dataset_t)
{
    ui->setupUi(this);

    _Image tmp_t = dataset.at(it);
    _Image tmp_r = testMethodViz(this->database, this->dataset, random, this->randPixMask, it).second;

    ui->test_image->resize(tmp_t.image.width() * 2, tmp_t.image.height() * 2);
    ui->test_image->show();
    ui->test_image->setPixmap(QPixmap::fromImage(colorizePixels(tmp_t)).scaled(tmp_t.image.width() * 2, tmp_t.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->answer_image->resize(tmp_r.image.width() * 2, tmp_r.image.height() * 2);
    ui->answer_image->show();
    ui->answer_image->setPixmap(QPixmap::fromImage(colorizePixels(tmp_r)).scaled(tmp_t.image.width() * 2, tmp_t.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    upper_bound_test = new QtCharts::QLineSeries();
    int max_y = 255;
    int tmp_i = 0;
    for (auto it = this->randPixMask.begin(); it != this->randPixMask.end(); ++it, ++tmp_i) {
        *upper_bound_test << QPointF(tmp_i, tmp_t.image_matrix[it.value()][it.key()]);
//        if (tmp_t.image_matrix[it.value()][it.key()] > max_y) {
//            max_y = tmp_t.image_matrix[it.value()][it.key()]; // not neccesary, may be changed just onto 255
//        }
    }
    series_test = new QtCharts::QAreaSeries(upper_bound_test);
    series_test->setName("test image area");
//    series_test->setBrush(Qt::Dense5Pattern);
    series_test->setColor(Qt::blue);

    chart_test = new QtCharts::QChart();
    chart_test->addSeries(series_test);
    chart_test->setTitle("test image");
    chart_test->createDefaultAxes();
    chart_test->axes(Qt::Horizontal).first()->setRange(0, this->randPixMask.size());
    chart_test->axes(Qt::Vertical).first()->setRange(0, max_y);

    tmp_i = 0;
//    max_y = -1;
    upper_bound_answer = new QtCharts::QLineSeries();
    for (auto it = this->randPixMask.begin(); it != this->randPixMask.end(); ++it, ++tmp_i) {
        *upper_bound_answer << QPointF(tmp_i, tmp_r.image_matrix[it.value()][it.key()]);
//        if (tmp_r.image_matrix[it.value()][it.key()] > max_y) {
//            max_y = tmp_r.image_matrix[it.value()][it.key()]; // not neccesary, may be changed just onto 255
//        }
    }
    series_answer = new QtCharts::QAreaSeries(upper_bound_answer);
    series_answer->setName("answer image area");
//    series_answer->setBrush(Qt::Dense6Pattern);
    series_answer->setColor(Qt::red);

    chart_answer = new QtCharts::QChart();
    chart_answer->addSeries(series_answer);
    chart_answer->setTitle("answer image");
    chart_answer->createDefaultAxes();
    chart_answer->axes(Qt::Horizontal).first()->setRange(0, this->randPixMask.size());
    chart_answer->axes(Qt::Vertical).first()->setRange(0, max_y);

    chartView = new QtCharts::QChartView(chart_test, ui->histogramWidget);
    chartView->resize(600, 400);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();

    chartView_2 = new QtCharts::QChartView(chart_answer, ui->histogramWidget_2);
    chartView_2->resize(600, 400);
    chartView_2->setRenderHint(QPainter::Antialiasing);
    chartView_2->show();

}

randomMethod::~randomMethod()
{
    delete ui;
}

void randomMethod::getDatabase(std::vector<std::vector<_Image>> database)
{
    this->database = database;
    return;
}
void randomMethod::getDataset(std::vector<_Image> dataset)
{
    this->dataset = dataset;
    return;
}
void randomMethod::getRandPixMask(QMultiMap<int, int> randPixMask)
{
    this->randPixMask = randPixMask;
    return;
}

void randomMethod::on_nextImageButton_clicked()
{
    if ( (this->it) + 1 >= this->dataset.size() ) {
        it = -1;
    }
    it++;

    _Image tmp_t = this->dataset.at(it);
    _Image tmp_r = testMethodViz(this->database, this->dataset, random, this->randPixMask, it).second;

    ui->test_image->clear();
    ui->test_image->setPixmap(QPixmap::fromImage(colorizePixels(tmp_t)).scaled(tmp_t.image.width() * 2, tmp_t.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->answer_image->clear();
    ui->answer_image->setPixmap(QPixmap::fromImage(colorizePixels(tmp_r)).scaled(tmp_r.image.width() * 2, tmp_r.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    upper_bound_test->clear();
//    int max_y = -1;
    int tmp_i = 0;
    for (auto it = this->randPixMask.begin(); it != this->randPixMask.end(); ++it, ++tmp_i) {
        *upper_bound_test << QPointF(tmp_i, tmp_t.image_matrix[it.value()][it.key()]);
//        if (tmp_t.image_matrix[it.value()][it.key()] > max_y) {
//            max_y = tmp_t.image_matrix[it.value()][it.key()]; // not neccesary, may be changed just onto 255
//        }
    }
    series_test->setUpperSeries(upper_bound_test);
//    series_test = new QtCharts::QAreaSeries(upper_bound_test);
//    chart_test->axes(Qt::Vertical).first()->setRange(0, max_y);

    tmp_i = 0;
    upper_bound_answer->clear();
    for (auto it = this->randPixMask.begin(); it != this->randPixMask.end(); ++it, ++tmp_i) {
        *upper_bound_answer << QPointF(tmp_i, tmp_r.image_matrix[it.value()][it.key()]);
//        if (tmp_r.image_matrix[it.value()][it.key()] > max_y) {
//            max_y = tmp_r.image_matrix[it.value()][it.key()]; // not neccesary, may be changed just onto 255
//        }
    }
    series_answer->setUpperSeries(upper_bound_answer);
//    series_answer = new QtCharts::QAreaSeries(upper_bound_answer);
//    chart_answer->axes(Qt::Vertical).first()->setRange(0, max_y);

    return;
}

void randomMethod::on_prevImageButton_clicked()
{
    if ( (this->it) - 1 < 0 ) {
        it = this->dataset.size();
    }
    it--;

    _Image tmp_t = this->dataset.at(it);
    _Image tmp_r = testMethodViz(this->database, this->dataset, random, this->randPixMask, it).second;

    ui->test_image->clear();
    ui->test_image->setPixmap(QPixmap::fromImage(colorizePixels(tmp_t)).scaled(tmp_t.image.width() * 2, tmp_t.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->answer_image->clear();
    ui->answer_image->setPixmap(QPixmap::fromImage(colorizePixels(tmp_r)).scaled(tmp_r.image.width() * 2, tmp_r.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    delete upper_bound_test;
    upper_bound_test = new QtCharts::QLineSeries();
//    int max_y = -1;
    int tmp_i = 0;
    for (auto it = this->randPixMask.begin(); it != this->randPixMask.end(); ++it, ++tmp_i) {
        *upper_bound_test << QPointF(tmp_i, tmp_t.image_matrix[it.value()][it.key()]);
//        if (tmp_t.image_matrix[it.value()][it.key()] > max_y) {
//            max_y = tmp_t.image_matrix[it.value()][it.key()]; // not neccesary, may be changed just onto 255
//        }
    }

    series_test->setUpperSeries(upper_bound_test);
//    series_test = new QtCharts::QAreaSeries(upper_bound_test);
//    chart_test->axes(Qt::Vertical).first()->setRange(0, max_y);

    tmp_i = 0;
//    int max_y = -1;
    delete upper_bound_answer;
    upper_bound_answer = new QtCharts::QLineSeries();
    for (auto it = this->randPixMask.begin(); it != this->randPixMask.end(); ++it, ++tmp_i) {
        *upper_bound_answer << QPointF(tmp_i, tmp_r.image_matrix[it.value()][it.key()]);
//        if (tmp_r.image_matrix[it.value()][it.key()] > max_y) {
//            max_y = tmp_r.image_matrix[it.value()][it.key()]; // not neccesary, may be changed just onto 255
//        }
    }

    series_answer->setUpperSeries(upper_bound_answer);
//    series_answer = new QtCharts::QAreaSeries(upper_bound_answer);
//    chart_answer->axes(Qt::Vertical).first()->setRange(0, max_y);

    return;
}

QImage randomMethod::colorizePixels(_Image& img)
{
    QImage tmp_img(img.image.width(), img.image.height(), QImage::Format_RGB32);
    tmp_img = img.image.convertToFormat(QImage::Format_RGB32);
    for (auto it = randPixMask.begin(); it != randPixMask.end(); ++it) {
        tmp_img.setPixelColor(it.key(), it.value(), QColor("light green"));
    }
    return tmp_img;
}

void randomMethod::on_exitButton_clicked()
{
    this->close();
    emit mainWindow();
}

int randomMethod::findDistance(_Image& img_1, _Image& img_2)
{
    int res = 0;
    for (auto it = randPixMask.begin(); it != randPixMask.end(); ++it) {
        res += abs(img_1.image_matrix.at(it.value()).at(it.key()) - img_2.image_matrix.at(it.value()).at(it.key()));
    }
    return res;
}
