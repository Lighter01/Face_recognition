#include "_Image.h"
#include "histogram_method.h"
#include "lbph_method.h"
#include "scaling_method.h"

void readImageName(_Image& image, const QString& path) {
    QStringList tmp_list = path.split("/");
    tmp_list.removeLast();
    image.name = tmp_list.last();
    return;
}

void readImageMatrix(_Image& image, const QImage& qimage) { // permanent change. No opportunity to expand matrix using this method
    //read image line by line
    for (int y = 0; y < qimage.height(); ++y) {
        std::vector<int> line;
        for (int x = 0; x < qimage.width(); ++x) {
            line.push_back(qGray(qimage.pixel(x,y)));
        }
        image.image_matrix.push_back(line);
    }
}

void getQImage(_Image& image, const QImage& qimage) {
    image.image = qimage; //POOOOOWAAAAAAHHHHHHHH!!!!!111!!
}

void readAllData(QStringList& list_of_images, const QString& path, std::vector<_Image>& image_set,
              int& set_size, const int& histogram_step)
{
    set_size += list_of_images.size(); // += for AT&T set , may delete
    for (QString &filename : list_of_images)
    {
        QImage Image = QImage(path + filename, "PGM");

//        std::cout << Image.width() << " " << Image.height() << "\n";
//        Image.convertTo(QImage::Format_Grayscale8);

        _Image tmp;

        readImageName(tmp, path);
        readImageMatrix(tmp, Image);
        readScaledImage(tmp, Image, tmp.name.toStdString(), filename.toStdString());
        getHistogram(tmp, histogram_step);
        getBetterHistogram(tmp, filename.toStdString());
        getQImage(tmp, Image);

        image_set.push_back(tmp);
    }
    return;
}

void readDataForMethod(QStringList& list_of_images, const QString& path, std::vector<_Image>& image_set,
                   const short& method_flag, const int& histogram_step)
{
    for (QString &filename : list_of_images)
    {
        QImage Image = QImage(path + filename, "PGM");

//        std::cout << Image.width() << " " << Image.height() << "\n";
//        Image.convertTo(QImage::Format_Grayscale8);

        _Image tmp;
        readImageName(tmp, path);

        switch(method_flag) {
        case euclidean:
        case stepped:
        case chebyshev:
        case cosine:
        case manhattan: {
            readImageMatrix(tmp, Image);
            getHistogram(tmp, histogram_step);
            break;
        }
        case lbph_manhattan: {
            readImageMatrix(tmp, Image);
            getBetterHistogram(tmp, filename.toStdString());
            break;
        }
        case random: {
            readImageMatrix(tmp, Image);
            break;
        }
        case scaling: {
            readScaledImage(tmp, Image, tmp.name.toStdString(), filename.toStdString());
            break;
        }
        };

        image_set.push_back(tmp);
    }
    return;
}

void readAdditionalData(QStringList& list_of_images, const QString& path, std::vector<_Image>& image_set,
                   const short& method_flag, const int& histogram_step)
{
    int pos = image_set.size() - list_of_images.size();
    for (QString &filename : list_of_images)
    {
        QImage Image = QImage(path + filename, "PGM");

//        std::cout << Image.width() << " " << Image.height() << "\n";
//        Image.convertTo(QImage::Format_Grayscale8);

        _Image tmp;

        switch(method_flag) {
        case manhattan: {
            getHistogram(image_set[pos], histogram_step);
            break;
        }
        case lbph_manhattan: {
            getBetterHistogram(image_set[pos], filename.toStdString());
            break;
        }
        case random: {
            break;
        }
        case scaling: {
            readScaledImage(image_set[pos], Image, image_set[pos].name.toStdString(), filename.toStdString());
            break;
        }
        };
        ++pos;
    }
    return;
}
