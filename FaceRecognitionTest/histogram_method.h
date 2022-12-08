#ifndef HISTOGRAM_METHOD_H
#define HISTOGRAM_METHOD_H

#include "_Image.h"

////Histogram method////

void getHistogram(_Image& Image, const int& histogram_step);

void readMatrix(const QImage& Image, images& Image_matrix); // universal method for matrix copy reading pattern

double findChebyshevDistance(const _Image& image_1, const _Image& image_2);

double findManhattanDistance(const _Image& image_1, const _Image& image_2);

double findDistance(const _Image& image_1, const _Image& image_2);

double findSteppedDistance(const _Image& image_1, const _Image& image_2,
                           const int& p = 2, const int& q = 2); // default equal to euclidean

double cosineSimilarity(const _Image& image_1, const _Image& image_2);



#endif // HISTOGRAM_METHOD_H
