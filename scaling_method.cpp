#include "scaling_method.h"

double compareScaledImages(const _Image& image_1, const _Image& image_2) {
    double distance = 0;
    for (size_t i = 0; i < image_1.scaled_image_matrix.size(); ++i) {
        for (size_t j = 0; j < image_1.scaled_image_matrix[i].size(); ++j) {
            distance += std::abs(image_1.scaled_image_matrix[i][j] - image_2.scaled_image_matrix[i][j]);
        }
    }
    return distance;
}

void readScaledImageMatrix(_Image& image, const QImage qimage) {
    for (int y = 0; y < qimage.height(); ++y) {
        std::vector<int> line;
        for (int x = 0; x < qimage.width(); ++x) {
            line.push_back(qGray(qimage.pixel(x,y)));
        }
        image.scaled_image_matrix.push_back(line);
    }
}

void writeScaledImagesFile(_Image& image, const std::string image_dir_name, const std::string& image_file_name) {
    FILE* new_image;
    std::string directoryPath = (QDir::currentPath() + "/scaled_images_dir").toStdString();
    if (mkdir(directoryPath.c_str(), 0755) == -1) {};

    directoryPath += '/' + image_dir_name;
    if (mkdir(directoryPath.c_str(), 0755) == -1) {};

    new_image = fopen((directoryPath + "/" + image_file_name).c_str(), "wb");

/*    QString directoryPath = QDir::currentPath() + "/masks_of_images/" + image.name;
    QDir dir;
    dir.mkpath(directoryPath);

    new_image = fopen(directoryPath.toStdStr().c_str()); */

    fprintf(new_image, "P2\n");
    fprintf(new_image, "%d %d\n", image.scaled_image_matrix[0].size(), image.scaled_image_matrix.size());
    fprintf(new_image, "255\n");

    for(int height = 0; height < image.scaled_image_matrix.size(); ++height) {
        for(int width = 0; width < image.scaled_image_matrix[0].size(); ++width) {
            fprintf(new_image, "%d ", image.scaled_image_matrix[height][width]);
        }
        fprintf(new_image, "\n");
    }
    fclose(new_image);
}

void readScaledImage(_Image& image, const QImage& qimage,
                     const std::string& image_dir_name, const std::string& image_file_name) {

    QImage tmp = qimage.scaled(qimage.width() * 0.4, qimage.height() * 0.4 , Qt::IgnoreAspectRatio); // IgnoreAspectRatio or KeepAspectRatio ???

    readScaledImageMatrix(image, tmp);
    writeScaledImagesFile(image, image_dir_name, image_file_name);

    return;
}
