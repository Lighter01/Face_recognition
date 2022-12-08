#ifndef RANDOM_PIXELS_METHOD_H
#define RANDOM_PIXELS_METHOD_H

#include "_Image.h"

////Random pixels method/////

void getRandomPixMask(const double& image_percentage, std::vector<std::pair<int, int>>& randomPixMask, const QString& path);

double compareRandomPix(const _Image& image_1, const _Image& image_2, const std::vector<std::pair<int, int>>& randomPixMask);

#endif // RANDOM_PIXELS_METHOD_H
