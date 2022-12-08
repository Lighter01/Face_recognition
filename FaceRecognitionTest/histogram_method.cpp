#include "histogram_method.h"

void getHistogram(_Image& Image, const int& histogram_step) {
    Image.histogram.resize(256 / histogram_step);
    for (const auto& it : Image.image_matrix) {
        for (int jt : it) {
            ++Image.histogram[jt / histogram_step];
        }
    }
        //Histogram check
    //    int x = 0;
    //    for (auto it : Histogram) {
    //        x += it;
    //    }
    //    std::cout << x << "\n";
}

void readMatrix(const QImage& Image, images& Image_matrix) {
    //read image line by line
    for (int y = 0; y < Image.height(); ++y) {
        std::vector<int> line;
        for (int x = 0; x < Image.width(); ++x) {
            line.push_back(qGray(Image.pixel(x,y)));
        }
        Image_matrix.push_back(line);
    }
}

double cosineSimilarity(const _Image& x, const _Image& y) {
    double composition = 0;
    for (size_t i = 0; i < x.histogram.size(); ++i) {
        composition += x.histogram[i] * y.histogram[i];
    }
    double length = 0;
    auto find_length = []( _Image a){
        double l = 0;
        for (size_t i = 0; i < a.histogram.size(); ++i) {
            l += a.histogram[i] * a.histogram[i];
        }
        return sqrt(l);
    };
    length = find_length(x) * find_length(y);
    return composition / length;
}

double findChebyshevDistance(const _Image& x, const _Image& y) {
    double distance = -1;
    for (size_t i = 0; i < x.histogram.size(); ++i) {
        double tmp = std::abs(x.histogram[i] - y.histogram[i]);
        if (tmp > distance) {
            distance = tmp;
        }
    }
    return distance;
}

double findManhattanDistance(const _Image& x, const _Image& y) {
    double distance = 0;
    for (size_t i = 0; i < x.histogram.size(); ++i) {
        distance += std::abs(x.histogram[i] - y.histogram[i]);
    }
    return distance;
}

double findSteppedDistance(const _Image& x, const _Image& y, const int& p, const int& q) {
    double distance = 0;
    for (size_t i = 0; i < x.histogram.size(); ++i) {
        distance += pow(x.histogram[i] - y.histogram[i], p);
    }
//    return nthRoot(distance, q);
    return pow(distance, 1.0 / q);
}

double findDistance(const _Image& x, const _Image& y) {
    double distance = 0;
    for (size_t i = 0; i < x.histogram.size(); ++i) {
        distance += (x.histogram[i] - y.histogram[i]) * (x.histogram[i] - y.histogram[i]);
    }
    return sqrt(distance);
}
