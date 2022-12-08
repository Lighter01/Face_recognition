#include "lbphmethod.h"
#include "ui_lbphmethod.h"

#include "FaceRecognitionTest/test_method.h"
#include "FaceRecognitionTest/lbph_method.h"

#include <QMainWindow>

lbphMethod::lbphMethod(std::vector<std::vector<_Image>> database_t, std::vector<_Image> dataset_t, QMultiMap<int, int> randPixMask_t,
                       QWidget *parent) :
    QWidget(parent),
    randPixMask(randPixMask_t),
    database(database_t),
    dataset(dataset_t),

    it(0),
    ui(new Ui::lbphMethod)
{
    faults = 0, avg_dist = 0;
    testMethodAcc(database, dataset, lbph_manhattan, randPixMask, faults, avg_dist);

    ui->setupUi(this);

    ui->textBrowser_2->setFont(QFont("Times",20));
    ui->textBrowser_2->setText(QString::number(avg_dist));
    ui->textBrowser_3->setFont(QFont("Times",20));
    ui->textBrowser_3->setText(QString::number(faults));

    // Set images
    _Image tmp_test = dataset.at(it);
    _Image tmp_ans  = testMethodViz(this->database, this->dataset, manhattan, this->randPixMask, it).second;

    ui->textBrowser->setFont(QFont("Times",20));
    ui->textBrowser->setText(QString::number(findDistance(tmp_test, tmp_ans)));


    ui->lbph_test->resize(tmp_test.image.width() * 2, tmp_test.image.height() * 2);
    ui->lbph_test->show();
    ui->lbph_test->setPixmap(QPixmap::fromImage(tmp_test.image).scaled(tmp_test.image.width() * 2, tmp_test.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer->resize(tmp_ans.image.width() * 2, tmp_ans.image.height() * 2);
    ui->lbph_answer->show();
    ui->lbph_answer->setPixmap(QPixmap::fromImage(tmp_ans.image).scaled(tmp_ans.image.width() * 2, tmp_ans.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    QImage test_modified(getMask(tmp_test)),
           answer_modified(getMask(tmp_ans));

    ui->lbph_test_2->resize(test_modified.width() * 2, test_modified.height() * 2);
    ui->lbph_test_2->show();
    ui->lbph_test_2->setPixmap(QPixmap::fromImage(test_modified, Qt::AutoColor).scaled(test_modified.width() * 2, test_modified.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer_2->resize(answer_modified.width() * 2, answer_modified.height() * 2);
    ui->lbph_answer_2->show();
    ui->lbph_answer_2->setPixmap(QPixmap::fromImage(answer_modified).scaled(answer_modified.width() * 2, answer_modified.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    // Set histogram
    upper_bound_test = new QtCharts::QLineSeries();
    upper_bound_answer = new QtCharts::QLineSeries();
    int max_y = 255, tmp_i = 0, tmp_j = 0;
    for (auto at = tmp_test.image_matrix.begin(), jt = tmp_ans.image_matrix.begin(); at != tmp_test.image_matrix.end() && jt != tmp_ans.image_matrix.end(); ++at, ++jt) {
        for (auto kt : *at) {
            *upper_bound_test   << QPointF(tmp_i++, kt);
        }
        for (auto kt : *jt) {
            *upper_bound_answer << QPointF(tmp_j++, kt);
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
    chart_test->axes(Qt::Horizontal).first()->setRange(0, tmp_test.betterHistogram.size());
    chart_test->axes(Qt::Vertical).first()->setRange(0, max_y);

    series_answer = new QtCharts::QAreaSeries(upper_bound_answer);
    series_answer->setName("answer image area");
//    series_answer->setBrush(Qt::Dense6Pattern);
    series_answer->setColor(Qt::red);

    chart_answer = new QtCharts::QChart();
    chart_answer->addSeries(series_answer);
    chart_answer->setTitle("answer image");
    chart_answer->createDefaultAxes();
    chart_answer->axes(Qt::Horizontal).first()->setRange(0, tmp_ans.betterHistogram.size());
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

lbphMethod::~lbphMethod()
{
    delete ui;
}

void lbphMethod::getDatabase(std::vector<std::vector<_Image>> database)
{
    this->database = database;
    return;
}
void lbphMethod::getDataset(std::vector<_Image> dataset)
{
    this->dataset = dataset;
    return;
}
void lbphMethod::getRandPixMask(QMultiMap<int, int> randPixMask)
{
    this->randPixMask = randPixMask;
    return;
}

void lbphMethod::on_exitButton_clicked()
{
    this->close();
    emit mainWindow();
}

void lbphMethod::on_nextImageButton_clicked()
{
    if ( (this->it) + 1 >= this->dataset.size() ) {
        it = -1;
    }
    it++;

    _Image tmp_test = this->dataset.at(it);
    _Image tmp_ans = testMethodViz(this->database, this->dataset, lbph_manhattan, this->randPixMask, it).second;

    ui->textBrowser->clear();
    ui->textBrowser->setText(QString::number(findDistance(tmp_test, tmp_ans)));

    ui->lbph_test->clear();
    ui->lbph_test->setPixmap(QPixmap::fromImage(tmp_test.image).scaled(tmp_test.image.width() * 2, tmp_test.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer->clear();
    ui->lbph_answer->setPixmap(QPixmap::fromImage(tmp_ans.image).scaled(tmp_ans.image.width() * 2, tmp_ans.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    QImage test_modified(getMask(tmp_test)),
           answer_modified(getMask(tmp_ans));

    ui->lbph_test_2->clear();
    ui->lbph_test_2->setPixmap(QPixmap::fromImage(test_modified).scaled(test_modified.width() * 2, test_modified.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer_2->clear();
    ui->lbph_answer_2->setPixmap(QPixmap::fromImage(answer_modified).scaled(answer_modified.width() * 2, answer_modified.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    delete upper_bound_test;
    upper_bound_test = new QtCharts::QLineSeries();
    delete upper_bound_answer;
    upper_bound_answer = new QtCharts::QLineSeries();

    int tmp_i = 0, tmp_j = 0;
    for (auto at = tmp_test.image_matrix.begin(), jt = tmp_ans.image_matrix.begin(); at != tmp_test.image_matrix.end() && jt != tmp_ans.image_matrix.end(); ++at, ++jt) {
        for (auto kt : *at) {
            *upper_bound_test   << QPointF(tmp_i++, kt);
        }
        for (auto kt : *jt) {
            *upper_bound_answer << QPointF(tmp_j++, kt);
        }
    }
    series_test->setUpperSeries(upper_bound_test);
    series_answer->setUpperSeries(upper_bound_answer);
}

void lbphMethod::on_prevImageButton_clicked()
{
    if ( (this->it) - 1 < 0 ) {
        it = this->dataset.size();
    }
    it--;

    _Image tmp_test = this->dataset.at(it);
    _Image tmp_ans = testMethodViz(this->database, this->dataset, lbph_manhattan, this->randPixMask, it).second;

    ui->textBrowser->clear();
    ui->textBrowser->setText(QString::number(findDistance(tmp_test, tmp_ans)));

    ui->lbph_test->clear();
    ui->lbph_test->setPixmap(QPixmap::fromImage(tmp_test.image).scaled(tmp_test.image.width() * 2, tmp_test.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer->clear();
    ui->lbph_answer->setPixmap(QPixmap::fromImage(tmp_ans.image).scaled(tmp_ans.image.width() * 2, tmp_ans.image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    QImage test_modified(getMask(tmp_test)),
           answer_modified(getMask(tmp_ans));

    ui->lbph_test_2->clear();
    ui->lbph_test_2->setPixmap(QPixmap::fromImage(test_modified).scaled(test_modified.width() * 2, test_modified.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer_2->clear();
    ui->lbph_answer_2->setPixmap(QPixmap::fromImage(answer_modified).scaled(answer_modified.width() * 2, answer_modified.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    delete upper_bound_test;
    upper_bound_test = new QtCharts::QLineSeries();
    delete upper_bound_answer;
    upper_bound_answer = new QtCharts::QLineSeries();

    int tmp_i = 0, tmp_j = 0;
    for (auto at = tmp_test.image_matrix.begin(), jt = tmp_ans.image_matrix.begin(); at != tmp_test.image_matrix.end() && jt != tmp_ans.image_matrix.end(); ++at, ++jt) {
        for (auto kt : *at) {
            *upper_bound_test   << QPointF(tmp_i++, kt);
        }
        for (auto kt : *jt) {
            *upper_bound_answer << QPointF(tmp_j++, kt);
        }
    }
    series_test->setUpperSeries(upper_bound_test);
    series_answer->setUpperSeries(upper_bound_answer);

}

int lbphMethod::findDistance(_Image& img_1, _Image& img_2)
{
    int res = 0;
    for (auto it = img_1.betterHistogram.begin(), jt = img_2.betterHistogram.begin();
         it != img_1.betterHistogram.end() && jt != img_2.betterHistogram.end(); ++it, ++jt)
    {
        res += abs(*it - * jt);
    }
    return res;
}
