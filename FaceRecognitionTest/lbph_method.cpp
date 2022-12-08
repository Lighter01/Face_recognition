#include "lbph_method.h"

void getMask(const _Image& image, images& transformed_image, const std::string& file_name) {

    FILE* new_image;
    std::string directoryPath = (QDir::currentPath() + "/masks_of_images").toStdString();
    if (mkdir(directoryPath.c_str(), 0755) == -1) {};

    directoryPath += "/" + image.name.toStdString();
    if (mkdir(directoryPath.c_str(), 0755) == -1) {};

    // QT libs variant of realisation
    /*    QString directoryPath = QDir::currentPath() + "/masks_of_images/" + image.name;
        QDir dir;
        dir.mkpath(directoryPath);

        new_image = fopen(directoryPath.toStdStr().c_str()); */

    new_image = fopen((directoryPath + "/" + file_name).c_str(), "wb");

    fprintf(new_image, "P2\n");
    fprintf(new_image, "%d %d\n", static_cast<int>(image.image_matrix[0].size() - 2), image.image_matrix.size() - 2);
    fprintf(new_image, "255\n");


    // may optimize boundaries to avoid giving _Image image. Need to play with tr_image size
    for (std::size_t line = 1; line < image.image_matrix.size() - 1; ++line) { // start from zero and end on size(), if you define pixels out of ranges of image
        for (std::size_t column = 1; column < image.image_matrix[line].size() - 1; ++column) {
//            std::cout << line << " " << column << "\n";
            //Redo this part following the circle instead of moving matrix, need this to be able to scale
            std::vector<int> window; // matrix 3 x 3 - clockwise
            // Read a window 3 x 3
            for (std::size_t i = line - 1; i < line + 2; ++i) {
                for (std::size_t j = column - 1; j < column + 2; ++j) {
                    // use this for defenition of pixels outside the image
//                    if (i < 0 || j < 0 || i >= image.image_matrix.size() || j >= image.image_matrix[line].size())
//                    {
//                        window.push_back(255);
//                    }
//                    else
//                    {
//                        window.push_back(image.image_matrix[i][j]);
//                    }
                    window.push_back(image.image_matrix[i][j]);
                }
            }
            std::size_t middle_cell = window.size() / 2;
            std::size_t threshold = window.at(middle_cell); // cell (1,1) in 3 x 3 from (0,0) to (2,2)
            QString byte;
            for (std::size_t pos = 0; pos < window.size(); ++pos) {
                if (pos != middle_cell) {
                    if (window.at(pos) < threshold)
                    {
                        byte += QString::number(0);
                    }
                    else
                    {
                        byte += QString::number(1);
                    }
                }
            }
            bool ok;
//            image.image_matrix[line][column] = byte.toInt(&ok, 2);
            transformed_image[line - 1][column - 1] = byte.toInt(&ok, 2); // image_matrix.size() > transformed_image.size() , so -1, -1
            fprintf(new_image, "%d ", transformed_image[line - 1][column - 1]);
        }
        fprintf(new_image, "\n");
    }

    fclose(new_image);
    return;
}

void getBetterHistogram(_Image& image, const std::string& file_name) {
    // can use collections, but saved this form for my better understanding
    images transformed_image (image.image_matrix.size() - 2, std::vector<int>(image.image_matrix[0].size() - 2) ); // 110 x 90
    getMask(image, transformed_image, file_name);

    int tr_image_width = transformed_image[0].size();
    int tr_image_height = transformed_image.size();

    int cell_width = tr_image_width / 4;
    int cell_height = tr_image_height / 8;

    images new_histogram(32, std::vector<int>(256,0));
    for (size_t grid_row = 0; grid_row < cell_height; ++grid_row) { // height
        for (size_t grid_column = 0; grid_column < cell_width; ++grid_column) { // width
            for (size_t line = grid_row * 14; line < grid_row * 14 + 14 && line < tr_image_height; ++line) {
                for (size_t column = grid_column * 23; column < grid_column * 23 + 23 && column < tr_image_width; ++column) {
                    ++new_histogram.at(4 * grid_row + grid_column).at(transformed_image[line][column]);
                }
            }
        }
    }
    for (const auto& it : new_histogram) {
        for (const auto& jt : it) {
            image.betterHistogram.push_back(jt);
        }
    }

    return;
}

double cosineSimilarity_2(const _Image& x, const _Image& y) {
    double composition = 0;
    for (size_t i = 0; i < x.betterHistogram.size(); ++i) {
        composition += x.betterHistogram[i] * y.betterHistogram[i];
    }
    double length = 0;
    auto find_length = []( _Image a){
        double l = 0;
        for (size_t i = 0; i < a.betterHistogram.size(); ++i) {
            l += a.betterHistogram[i] * a.betterHistogram[i];
        }
        return sqrt(l);
    };
    length = find_length(x) * find_length(y);
    return composition / length;
}

double findChebyshevDistance_2(const _Image& x, const _Image& y) {
    double distance = -1;
    for (size_t i = 0; i < x.betterHistogram.size(); ++i) {
        double tmp = std::abs(x.betterHistogram[i] - y.betterHistogram[i]);
        if (tmp > distance) {
            distance = tmp;
        }
    }
    return distance;
}

double findManhattanDistance_2(const _Image& x, const _Image& y) {
    double distance = 0;
    for (size_t i = 0; i < x.betterHistogram.size(); ++i) {
        distance += std::abs(x.betterHistogram[i] - y.betterHistogram[i]);
    }
    return distance;
}

double findSteppedDistance_2(const _Image& x, const _Image& y, const int& p, const int& q) {
    double distance = 0;
    for (size_t i = 0; i < x.betterHistogram.size(); ++i) {
        distance += pow(x.betterHistogram[i] - y.betterHistogram[i], p);
    }
//    return nthRoot(distance, q);
    return pow(distance, 1.0 / q);
}

double findDistance_2(const _Image& x, const _Image& y) {
    double distance = 0;
    for (size_t i = 0; i < x.betterHistogram.size(); ++i) {
        distance += (x.betterHistogram[i] - y.betterHistogram[i]) * (x.betterHistogram[i] - y.betterHistogram[i]);
    }
    return sqrt(distance);
}

QImage getMask(const _Image& _img) {
    QImage *tmp_modified = new QImage(_img.image_matrix.at(0).size() - 2, _img.image_matrix.size() - 2, QImage::Format_RGB32);

    for (int line = 1; line < _img.image_matrix.size() - 1; ++line) { // start from zero and end on size(), if you define pixels out of ranges of image
        for (int column = 1; column < _img.image_matrix[line].size() - 1; ++column) {
            //Redo this part following the circle instead of moving matrix, need this to be able to scale
            std::vector<int> window; // matrix 3 x 3 - clockwise
            // Read a window 3 x 3
            for (int i = line - 1; i < line + 2; ++i) {
                for (int j = column - 1; j < column + 2; ++j) {
                    // use this for defenition of pixels outside the image
//                    if (i < 0 || j < 0 || i >= image.image_matrix.size() || j >= image.image_matrix[line].size())
//                    {
//                        window.push_back(255);
//                    }
//                    else
//                    {
//                        window.push_back(image.image_matrix[i][j]);
//                    }
                    window.push_back(_img.image_matrix[i][j]);
                }
            }
            int middle_cell = window.size() / 2;
            int threshold = window.at(middle_cell); // cell (1,1) in 3 x 3 from (0,0) to (2,2)
            QString byte;
            for (size_t pos = 0; pos < window.size(); ++pos) {
                if (pos != middle_cell) {
                    if (window.at(pos) < threshold)
                    {
                        byte += QString::number(0);
                    }
                    else
                    {
                        byte += QString::number(1);
                    }
                }
            }
            bool ok;
            int gray_color = byte.toInt(&ok, 2);
            tmp_modified->setPixel(column - 1, line - 1, qRgb(gray_color ,gray_color, gray_color));
        }
    }

    return *tmp_modified;
}
