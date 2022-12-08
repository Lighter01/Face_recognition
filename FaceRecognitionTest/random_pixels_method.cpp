#include "random_pixels_method.h"

void getRandomPixMask(const double& image_percentage,
                  QMultiMap<int, int>& randomPixMask,
                      const QString& path) {

    QImage tmp = QImage(path);
    int tmp_size = tmp.height() * tmp.width(); // probably may be changed to QImage::sizeInBytes()
    int pixels_in_mask = static_cast<int>(tmp_size * image_percentage);

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int x = 0, y = 0;
    for (int i = 0; i < pixels_in_mask; ++i) {
        x = std::uniform_int_distribution<int>(0, tmp.width() - 1)(rng);
        y = std::uniform_int_distribution<int>(0, tmp.height() - 1)(rng);
//        randomPixMask.push_back(std::make_pair(x, y));
        randomPixMask.insert(x, y);
    }
    return;
}

double compareRandomPix(const _Image& image_1, const _Image& image_2, QMultiMap<int, int>& randomPixMask) {
    double distance = 0;
    QMap<int, int>::const_iterator it;
    for (it = randomPixMask.constBegin(); it != randomPixMask.constEnd(); ++it) {
        distance += std::abs(image_1.image_matrix[it.value()][it.key()] - image_2.image_matrix[it.value()][it.key()]);
    }
    return distance;
}
