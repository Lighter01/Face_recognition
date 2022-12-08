#include "scalingmethod.h"
#include "ui_scalingmethod.h"

#include "FaceRecognitionTest/test_method.h"

std::vector<int> getScaledImageHist(_Image& );

scalingMethod::scalingMethod(std::vector<std::vector<_Image>> database_t, std::vector<_Image> dataset_t,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scalingMethod),
    it(0),
    database(database_t),
    dataset(dataset_t)
{
    ui->setupUi(this);

    _Image test = dataset.at(it),
           answer = testMethodViz(this->database, this->dataset, scaling, this->randPixMask, it).second;

    QImage tmp_t = test.image;
    QImage tmp_s = answer.image;
    QImage scaled_tmp_t = tmp_t.scaled(tmp_t.width() * 0.25, tmp_t.height() * 0.25 , Qt::IgnoreAspectRatio);
    QImage scaled_tmp_s = tmp_s.scaled(tmp_s.width() * 0.25, tmp_s.height() * 0.25 , Qt::IgnoreAspectRatio);

    int faults_s = 0;

    ui->test_image->resize(tmp_t.width() * 2, tmp_t.height() * 2);
    ui->test_image->show();
    ui->test_image->setPixmap(QPixmap::fromImage(tmp_t).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer->resize(tmp_s.width() * 2, tmp_s.height() * 2);
    ui->scaling_answer->show();
    ui->scaling_answer->setPixmap(QPixmap::fromImage(tmp_s).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->test_scaled->resize(tmp_t.width() * 2, tmp_t.height() * 2);
    ui->test_scaled->show();
    ui->test_scaled->setPixmap(QPixmap::fromImage(scaled_tmp_t).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer_scaled->resize(tmp_s.width() * 2, tmp_s.height() * 2);
    ui->scaling_answer_scaled->show();
    ui->scaling_answer_scaled->setPixmap(QPixmap::fromImage(scaled_tmp_s).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));


    std::vector<int> test_hist   = getScaledImageHist(test),
                     answer_hist = getScaledImageHist(answer);

    // Set histogram
    upper_bound_test = new QtCharts::QLineSeries();
    upper_bound_answer = new QtCharts::QLineSeries();
    int max_y = -1, tmp_i = 0;
    for (auto it = test_hist.begin(), jt = answer_hist.begin(); it != test_hist.end() && jt != answer_hist.end(); ++it, ++jt) {
        *upper_bound_test   << QPointF(tmp_i, *it);
        *upper_bound_answer << QPointF(tmp_i++, *jt);
        if (max_y < *it) {
            max_y = *it;
        }
        if (max_y < *jt) {
            max_y = *jt;
        }
    }
    series_test = new QtCharts::QAreaSeries(upper_bound_test);
    series_test->setName("test image area");
//    series_test->setBrush(Qt::Dense5Pattern);
    series_test->setColor(Qt::blue);

    chart_test = new QtCharts::QChart();
    chart_test->addSeries(series_test);
    chart_test->setTitle("test image");
    chart_test->createDefaultAxes();
    chart_test->axes(Qt::Horizontal).first()->setRange(0, test_hist.size());
    chart_test->axes(Qt::Vertical).first()->setRange(0, max_y);

    series_answer = new QtCharts::QAreaSeries(upper_bound_answer);
    series_answer->setName("answer image area");
//    series_answer->setBrush(Qt::Dense6Pattern);
    series_answer->setColor(Qt::red);

    chart_answer = new QtCharts::QChart();
    chart_answer->addSeries(series_answer);
    chart_answer->setTitle("answer image");
    chart_answer->createDefaultAxes();
    chart_answer->axes(Qt::Horizontal).first()->setRange(0, answer_hist.size());
    chart_answer->axes(Qt::Vertical).first()->setRange(0, max_y);

    chartView = new QtCharts::QChartView(chart_test, ui->histogramWidget);
    chartView->resize(ui->histogramWidget->size());
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();

    chartView_2 = new QtCharts::QChartView(chart_answer, ui->histogramWidget_2);
    chartView_2->resize(ui->histogramWidget_2->size());
    chartView_2->setRenderHint(QPainter::Antialiasing);
    chartView_2->show();
}

scalingMethod::~scalingMethod()
{
    delete ui;
}

void scalingMethod::getDatabase(std::vector<std::vector<_Image>> database)
{
    this->database = database;
    return;
}
void scalingMethod::getDataset(std::vector<_Image> dataset)
{
    this->dataset = dataset;
    return;
}
void scalingMethod::getRandPixMask(QMultiMap<int, int> randPixMask)
{
    this->randPixMask = randPixMask;
    return;
}

void scalingMethod::on_nextImageButton_clicked()
{
    if ( (this->it) + 1 >= this->dataset.size() ) {
        it = -1;
    }
    it++;

    _Image test = dataset.at(it),
           answer = testMethodViz(this->database, this->dataset, scaling, this->randPixMask, it).second;

    QImage tmp_t = test.image;
    QImage tmp_s = answer.image;
    QImage scaled_tmp_t = tmp_t.scaled(tmp_t.width() * 0.25, tmp_t.height() * 0.25 , Qt::IgnoreAspectRatio);
    QImage scaled_tmp_s = tmp_s.scaled(tmp_s.width() * 0.25, tmp_s.height() * 0.25 , Qt::IgnoreAspectRatio);

    ui->test_image->clear();
    ui->test_image->setPixmap(QPixmap::fromImage(tmp_t).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->test_scaled->clear();
    ui->test_scaled->setPixmap(QPixmap::fromImage(scaled_tmp_t).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer->clear();
    ui->scaling_answer->setPixmap(QPixmap::fromImage(tmp_s).scaled(tmp_s.width() * 2, tmp_s.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer_scaled->clear();
    ui->scaling_answer_scaled->setPixmap(QPixmap::fromImage(scaled_tmp_s).scaled(tmp_s.width() * 2, tmp_s.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    std::vector<int> test_hist   = getScaledImageHist(test),
                     answer_hist = getScaledImageHist(answer);

    upper_bound_test->clear();
    upper_bound_answer->clear();
    int max_y = -1, tmp_i = 0;
    for (auto it = test_hist.begin(), jt = answer_hist.begin(); it != test_hist.end() && jt != answer_hist.end(); ++it, ++jt) {
        *upper_bound_test   << QPointF(tmp_i, *it);
        *upper_bound_answer << QPointF(tmp_i++, *jt);
        if (max_y < *it) {
            max_y = *it;
        }
        if (max_y < *jt) {
            max_y = *jt;
        }
    }

    chart_test->axes(Qt::Vertical).first()->setRange(0, max_y);
    chart_answer->axes(Qt::Vertical).first()->setRange(0, max_y);

    series_test->setUpperSeries(upper_bound_test);
    series_answer->setUpperSeries(upper_bound_answer);

}

void scalingMethod::on_prevImageButton_clicked()
{
    if ( (this->it) - 1 < 0 ) {
        it = this->dataset.size();
    }
    it--;

    _Image test = dataset.at(it),
           answer = testMethodViz(this->database, this->dataset, scaling, this->randPixMask, it).second;

    QImage tmp_t = test.image;
    QImage tmp_s = answer.image;
    QImage scaled_tmp_t = tmp_t.scaled(tmp_t.width() * 0.25, tmp_t.height() * 0.25 , Qt::IgnoreAspectRatio);
    QImage scaled_tmp_s = tmp_s.scaled(tmp_s.width() * 0.25, tmp_s.height() * 0.25 , Qt::IgnoreAspectRatio);

    ui->test_image->clear();
    ui->test_image->setPixmap(QPixmap::fromImage(tmp_t).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->test_scaled->clear();
    ui->test_scaled->setPixmap(QPixmap::fromImage(scaled_tmp_t).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer->clear();
    ui->scaling_answer->setPixmap(QPixmap::fromImage(tmp_s).scaled(tmp_s.width() * 2, tmp_s.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer_scaled->clear();
    ui->scaling_answer_scaled->setPixmap(QPixmap::fromImage(scaled_tmp_s).scaled(tmp_s.width() * 2, tmp_s.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    std::vector<int> test_hist   = getScaledImageHist(test),
                     answer_hist = getScaledImageHist(answer);

    upper_bound_test->clear();
    upper_bound_answer->clear();
    int max_y = -1, tmp_i = 0;
    for (auto it = test_hist.begin(), jt = answer_hist.begin(); it != test_hist.end() && jt != answer_hist.end(); ++it, ++jt) {
        *upper_bound_test   << QPointF(tmp_i, *it);
        *upper_bound_answer << QPointF(tmp_i++, *jt);
        if (max_y < *it) {
            max_y = *it;
        }
        if (max_y < *jt) {
            max_y = *jt;
        }
    }

    chart_test->axes(Qt::Vertical).first()->setRange(0, max_y);
    chart_answer->axes(Qt::Vertical).first()->setRange(0, max_y);

    series_test->setUpperSeries(upper_bound_test);
    series_answer->setUpperSeries(upper_bound_answer);

}

void scalingMethod::on_exitButton_clicked()
{
    this->close();
    emit mainWindow();
}

std::vector<int> getScaledImageHist(_Image& image)
{
    std::vector<int> tmp_hist;
    for (auto it : image.scaled_image_matrix) {
        for (auto jt : it) {
            tmp_hist.push_back(jt);
        }
    }
    return tmp_hist;
}

//QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + j * depth); // cool method how to convert number into pixel color when reading QImage
