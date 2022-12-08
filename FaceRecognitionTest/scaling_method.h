#ifndef SCALING_METHOD_H
#define SCALING_METHOD_H

#include "_Image.h"

////Scaling method////

void readScaledImageMatrix(_Image& image, const QImage qimage);

void writeScaledImagesFile(_Image& image, const std::string image_dir_name, const std::string& image_file_name);

// readScaledImage = readScaledImageMatrix and/or writeScaledImagesFile
void readScaledImage(_Image& image, const QImage& qimage,
                    const std::string& image_dir_name, const std::string& image_file_name);

double compareScaledImages(const _Image& image_1, const _Image& image_2);

#endif // SCALING_METHOD_H
