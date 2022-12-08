#ifndef ALL_LIBRARIES_H
#define ALL_LIBRARIES_H

#include <direct.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <QImage>
#include <QDir>
#include <QStringList>
#include <QColor>
#include <QVector>
#include <QMap>
#include <iomanip>
#include <cmath>
#include <float.h>
#include <random>
#include <algorithm>
#include <chrono>
#include <QPainter>
#include <QColor>

#include <windows.h>
#define mkdir(dir, mode) _mkdir(dir)

#define images std::vector<std::vector<int>>

enum method
{
    euclidean = 0,
    stepped = 1,
    manhattan = 2,
    chebyshev = 3,
    cosine = 4,

    lbph_euclidean = 5,
    lbph_manhattan = 6,
    lbph_cosine = 7,
    scaling = 8,
    random = 9,

    voting = 10,
};


#endif // ALL_LIBRARIES_H
