#ifndef LBPH_METHOD_H
#define LBPH_METHOD_H

#include <QImage>
#include "_Image.h"

////LBPH method////

void getMask(const _Image&, const images&, const int& name);

QImage getMask(const _Image& ); //overloaded method neede for vizualization

void getBetterHistogram(_Image& Image, const std::string& file_name);

double findChebyshevDistance_2(const _Image& x, const _Image& y);

double findManhattanDistance_2(const _Image& x, const _Image& y);

double findDistance_2(const _Image& x, const _Image& y);

double findSteppedDistance_2(const _Image& x, const _Image& y, const int& p = 2, const int& q = 2); // default equal to euclidean

double cosineSimilarity_2(const _Image& x, const _Image& y);



#endif // LBPH_METHOD_H
