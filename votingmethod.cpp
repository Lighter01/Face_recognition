#include "votingmethod.h"
#include "ui_votingmethod.h"
#include "FaceRecognitionTest/test_method.h"
//#include <QCoreApplication>

votingMethod::votingMethod(std::vector<std::vector<_Image>> database_t, std::vector<_Image> dataset_t, QMultiMap<int, int> randPixMask_t,
                           QWidget *parent) :
    QWidget(parent),
    it(0),
    ui(new Ui::votingMethod),
    randPixMask(randPixMask_t),
    database(database_t),
    dataset(dataset_t)
{
    ui->setupUi(this);

    QImage tmp_t = dataset.at(0).image;
    QImage tmp_h;
    QImage tmp_s;
    QImage tmp_r;
    QImage tmp_l;

    int faults_h = 0;
    int faults_s = 0;
    int faults_r = 0;
    int faults_l = 0;

    testMethodViz(this->database, this->dataset, manhattan, this->randPixMask, faults_h);
    testMethodViz(this->database, this->dataset, scaling, this->randPixMask, faults_s);
    testMethodViz(this->database, this->dataset, random, this->randPixMask, faults_r);
    testMethodViz(this->database, this->dataset, lbph_manhattan, this->randPixMask, faults_l);

    tmp_h = testMethodViz(this->database, this->dataset, manhattan, this->randPixMask, it).second.image;
    tmp_s = testMethodViz(this->database, this->dataset, scaling, this->randPixMask, it).second.image;
    tmp_r = testMethodViz(this->database, this->dataset, random, this->randPixMask, it).second.image;
    tmp_l = testMethodViz(this->database, this->dataset, lbph_manhattan, this->randPixMask, it).second.image;

    ui->test_image->resize(tmp_t.width() * 2, tmp_t.height() * 2);
    ui->test_image->show();
    ui->test_image->setPixmap(QPixmap::fromImage(tmp_t).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->histogram_answer->resize(tmp_h.width() * 2, tmp_t.height() * 2);
    ui->histogram_answer->show();
    ui->histogram_answer->setPixmap(QPixmap::fromImage(tmp_h).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->random_answer->resize(tmp_r.width() * 2, tmp_r.height() * 2);
    ui->random_answer->show();
    ui->random_answer->setPixmap(QPixmap::fromImage(tmp_r).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer->resize(tmp_s.width() * 2, tmp_s.height() * 2);
    ui->scaling_answer->show();
    ui->scaling_answer->setPixmap(QPixmap::fromImage(tmp_s).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer->resize(tmp_l.width() * 2, tmp_l.height() * 2);
    ui->lbph_answer->show();
    ui->lbph_answer->setPixmap(QPixmap::fromImage(tmp_l).scaled(tmp_t.width() * 2, tmp_t.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

}

votingMethod::~votingMethod()
{
    delete ui;
}

void votingMethod::on_exitButton_clicked()
{
    this->close();
    emit mainWindow();
    this->it = 0;
}

void votingMethod::getDatabase(std::vector<std::vector<_Image>> database)
{
    this->database = database;
    return;
}
void votingMethod::getDataset(std::vector<_Image> dataset)
{
    this->dataset = dataset;
    return;
}
void votingMethod::getRandPixMask(QMultiMap<int, int> randPixMask)
{
    this->randPixMask = randPixMask;
    return;
}

void votingMethod::on_nextImageButton_clicked()
{
    if ( (this->it) + 1 >= this->dataset.size() ) {
        it = -1;
    }
    it++;

    QImage hist_res = testMethodViz(this->database, this->dataset, manhattan, this->randPixMask, it).second.image;
    QImage rand_res = testMethodViz(this->database, this->dataset, random, this->randPixMask, it).second.image;
    QImage scal_res = testMethodViz(this->database, this->dataset, scaling, this->randPixMask, it).second.image;
    QImage lbph_res = testMethodViz(this->database, this->dataset, lbph_manhattan, this->randPixMask, it).second.image;

    ui->test_image->clear();
    ui->test_image->setPixmap(QPixmap::fromImage(this->dataset[it].image).scaled(this->dataset[it].image.width() * 2, this->dataset[it].image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->histogram_answer->clear();
    ui->histogram_answer->setPixmap(QPixmap::fromImage(hist_res).scaled(hist_res.width() * 2, hist_res.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->random_answer->clear();
    ui->random_answer->setPixmap(QPixmap::fromImage(rand_res).scaled(rand_res.width() * 2, rand_res.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer->clear();
    ui->scaling_answer->setPixmap(QPixmap::fromImage(scal_res).scaled(scal_res.width() * 2, scal_res.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer->clear();
    ui->lbph_answer->setPixmap(QPixmap::fromImage(lbph_res).scaled(lbph_res.width() * 2, lbph_res.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

}

void votingMethod::on_prevImageButton_clicked()
{
    if ( (this->it) - 1 < 0 ) {
        it = this->dataset.size();
    }
    it--;

    QImage hist_res = testMethodViz(this->database, this->dataset, manhattan, this->randPixMask, it).second.image;
    QImage rand_res = testMethodViz(this->database, this->dataset, random, this->randPixMask, it).second.image;
    QImage scal_res = testMethodViz(this->database, this->dataset, scaling, this->randPixMask, it).second.image;
    QImage lbph_res = testMethodViz(this->database, this->dataset, lbph_manhattan, this->randPixMask, it).second.image;

    ui->test_image->clear();
    ui->test_image->setPixmap(QPixmap::fromImage(this->dataset[it].image).scaled(this->dataset[it].image.width() * 2, this->dataset[it].image.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->histogram_answer->clear();
    ui->histogram_answer->setPixmap(QPixmap::fromImage(hist_res).scaled(hist_res.width() * 2, hist_res.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->random_answer->clear();
    ui->random_answer->setPixmap(QPixmap::fromImage(rand_res).scaled(rand_res.width() * 2, rand_res.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->scaling_answer->clear();
    ui->scaling_answer->setPixmap(QPixmap::fromImage(scal_res).scaled(scal_res.width() * 2, scal_res.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->lbph_answer->clear();
    ui->lbph_answer->setPixmap(QPixmap::fromImage(lbph_res).scaled(lbph_res.width() * 2, lbph_res.height() * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation));

}
