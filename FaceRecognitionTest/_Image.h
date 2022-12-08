#ifndef _IMAGE_H
#define _IMAGE_H

#include "all_libraries.h"

/*!
 * \brief The _Image class
 */
struct _Image {
    QImage image;
    QString name;
    images image_matrix;
    images scaled_image_matrix;
    std::vector<int> histogram;
    std::vector<int> betterHistogram;
};

////Read image functions aka _Image class non-oficial getters////

void readImageName(_Image& image, const QString& path);

void readImageMatrix(_Image& image, const QImage qimage);

// readData = readImageName + ( readImageMatrix and/or read readScaledImage and/or getHistogram and/or getBetterHistogram )
void readAllData(QStringList& list_of_images, const QString& path, std::vector<_Image>& image_set,
              const int& histogram_step = 1);

void readDataForMethod(QStringList& list_of_images, const QString& path, std::vector<_Image>& image_set,
                   const short& method_flag, const int& histogram_step);

void readAdditionalData(QStringList& list_of_images, const QString& path, std::vector<_Image>& image_set,
                   const short& method_flag, const int& histogram_step);

#endif // _IMAGE_H
