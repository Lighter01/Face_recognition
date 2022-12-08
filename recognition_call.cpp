#include "recognition_call.h"
#include "random_pixels_method.h"
#include "histogram_method.h"
#include "lbph_method.h"
#include "scaling_method.h"
#include "voting_method.h"
//#include "voting_method.h"

void readFolderFiles(QStringList& files_folder, const QString& files_dir_path,
                     std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                     int& dataBase_size, int& dataSet_size, const int& method_flag,
                     const int& number_of_examples, const int& histogram_step) {

    int database_reference_index = 0;
    for (const QString& directory_name : files_folder) { // folder entry
        QDir current_dir(files_dir_path + directory_name);
        QString path_to_current_images_dir =  files_dir_path + directory_name + '/';
        QStringList tests_1 = current_dir.entryList(QStringList() << "*.pgm" << "*.PGM", QDir::Files);

        // Sort list of images
        QMap<int, QString> tmp_examples;
        for (const QString& it : tests_1) {
            QString tmp = it;
            tmp.chop(4); // x.pgm, where is if in [1..10]
            tmp_examples[tmp.toInt()] = it;
        }
        tests_1 = QStringList(tmp_examples.values());
        tmp_examples.clear();

        QStringList references_1;
        if (number_of_examples == 1)
        {
            references_1 = QStringList() << tests_1[0];
            tests_1.removeFirst();
        }
        else
        {
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
            int random_index;
            // Take random n images as examples, delete them from test set
            for (int i = 0; i < number_of_examples; ++i) {
                random_index = std::uniform_int_distribution<int>(0, tests_1.size() - 1)(rng);
                references_1 += QStringList() << tests_1[random_index];
                tests_1.erase(tests_1.begin() + random_index);
            }
        }

        readAllData(references_1, path_to_current_images_dir, database[database_reference_index++], dataBase_size, histogram_step);
        readAllData(tests_1, path_to_current_images_dir, dataset, dataSet_size, histogram_step);
//        readDataForMethod(references_1, path_to_current_images_dir, database[database_reference_index++], method_flag, histogram_step);
//        readDataForMethod(tests_1, path_to_current_images_dir, dataset, method_flag, histogram_step);
    }
}

// dataBase_size may be usefull for refactoring dataset initialization
void makeATandTTest(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                    int& dataBase_size, int& dataSet_size, const int& method_flag,
                    const int& number_of_examples, const int& histogram_step) {

//    QDir pictures_directory("D:/Face_datasets/AT&T_grayscale_normilized");
//    QString pictures_dir_path = "D:/Face_datasets/AT&T_grayscale_normilized/";

    QDir pictures_directory(QDir::currentPath() + "/AT&T_grayscale_normilized");
    QString pictures_dir_path = QDir::currentPath() + "/AT&T_grayscale_normilized/";
    QStringList pictures_folder = pictures_directory.entryList(QDir::Dirs);  // list of all folders in directory
    pictures_folder.removeAll(".");
    pictures_folder.removeAll("..");
//    std::cout << pictures.size() << "\n";

    //Sort list of folders
    QMap<int, QString> tmp_pictures;
    for (const auto& it : pictures_folder) {
        QString tmp = it;
        tmp.remove(0,1); // sx, where x is in [1..40]
        tmp_pictures[tmp.toInt()] = it;
    }
    pictures_folder = QStringList(tmp_pictures.values());
    tmp_pictures.clear();

    //random method lives here, need to change
    std::vector<std::pair<int, int>> randomPixMask(0); // maybe better to change to map to avoid repetitions
    switch (method_flag) { // could be "if", but who knows, maybe something else will be added in the future
        case random: {
            QDir first_image_dir (pictures_dir_path + pictures_folder[0]);
            QStringList tmp_list = first_image_dir.entryList(QStringList() << "*.pgm" << "*.PGM", QDir::Files);
            QString fisrt_image_path = pictures_dir_path + pictures_folder[0] + '/' + tmp_list[0];
            getRandomPixMask(0.1, randomPixMask, fisrt_image_path);
            break;
        }
        default: break;
    }

    database.resize(pictures_folder.size()); // pictures_folder includes number of folders equal to number of different people
    //Read all images from each directory: directory with folders (s1 , ... , s40) ---> folder with images (1 , ... , 10)
    readFolderFiles(pictures_folder, pictures_dir_path, database, dataset, dataBase_size, dataSet_size, method_flag, number_of_examples, histogram_step);
//    std::cout << testMethod(database, dataset, method_flag, randomPixMask) << "% is the accuracy of face recognition\n";
    std::cout << testVotingMethod(database, dataset, randomPixMask) << "% is the accuracy of face recognition\n";
    database.clear(); dataset.clear();
}

// for one reference value, left here if ever need again
/*std::pair<double, QString> getMethodAnswer(_Image& test_image, std::vector<_Image>& database,
                       const int& method_flag, const std::vector<std::pair<int, int>>& randomPixMask,
                       const int& p, const int& q)
{

    std::pair<double, QString> closest_answer;

    switch (method_flag)
    {
        case euclidean :     closest_answer = {DBL_MAX, "none"}; break;
        case stepped :       closest_answer = {DBL_MAX, "none"}; break;
        case manhattan:      closest_answer = {DBL_MAX, "none"}; break;
        case chebyshev:      closest_answer = {DBL_MAX, "none"}; break;
        case cosine:         closest_answer = {-1.01, "none"};   break;
        case lbph_euclidean: closest_answer = {DBL_MAX, "none"}; break;
        case lbph_manhattan: closest_answer = {DBL_MAX, "none"}; break;
        case lbph_cosine:    closest_answer = {-1.01, "none"};   break;
        case scaling:        closest_answer = {DBL_MAX, "none"}; break;
        case random:         closest_answer = {DBL_MAX, "none"}; break;
    };

    double check_distance = 0;

    for (_Image& it : database)
    {
        switch (method_flag)
        {
            case euclidean :        check_distance = findDistance(test_image, it);                      break;
            case stepped :          check_distance = findSteppedDistance(test_image, it, p, q);         break;
            case manhattan:         check_distance = findManhattanDistance(test_image, it);             break;
            case chebyshev:         check_distance = findChebyshevDistance(test_image, it);             break;
            case cosine:            check_distance = cosineSimilarity(test_image, it);                  break;
            case lbph_euclidean:    check_distance = findDistance_2(test_image, it);                    break;
            case lbph_manhattan:    check_distance = findManhattanDistance_2(test_image, it);           break;
            case lbph_cosine:       check_distance = cosineSimilarity_2(test_image, it);                break;
            case scaling:           check_distance = compareScaledImages(test_image, it);               break;
            case random:            check_distance = compareRandomPix(test_image, it, randomPixMask);   break;
            default:                                                                                    break;
        };

        if (method_flag != cosine && method_flag != lbph_cosine)
        {
            if (check_distance < closest_answer.first)
            {
                closest_answer.first = check_distance;
                closest_answer.second = it.name.left(9);
            }
        }
        else
        {
            if ((1 - check_distance) < (1 - closest_answer.first)) // 1 - check_distance < closest_answer
            {
                closest_answer.first = check_distance;
                closest_answer.second = it.name.left(9);
            }
        }
    }

    return closest_answer;
}*/

// for multiple reference values
std::pair<double, QString> getMethodAnswer(_Image& test_image, std::vector<std::vector<_Image>>& database,
                       const int& method_flag, const std::vector<std::pair<int, int>>& randomPixMask,
                       const int& p, const int& q)
{

    std::pair<double, QString> closest_answer;

    switch (method_flag)
    {
        case euclidean :     closest_answer = {DBL_MAX, "none"}; break;
        case stepped :       closest_answer = {DBL_MAX, "none"}; break;
        case manhattan:      closest_answer = {DBL_MAX, "none"}; break;
        case chebyshev:      closest_answer = {DBL_MAX, "none"}; break;
        case cosine:         closest_answer = {-1.01, "none"};   break;
        case lbph_euclidean: closest_answer = {DBL_MAX, "none"}; break;
        case lbph_manhattan: closest_answer = {DBL_MAX, "none"}; break;
        case lbph_cosine:    closest_answer = {-1.01, "none"};   break;
        case scaling:        closest_answer = {DBL_MAX, "none"}; break;
        case random:         closest_answer = {DBL_MAX, "none"}; break;
    };

    double check_distance = 0;

    for (auto& jt : database) {
        for (_Image& it : jt)
        {
            switch (method_flag)
            {
                case euclidean :        check_distance = findDistance(test_image, it);                      break;
                case stepped :          check_distance = findSteppedDistance(test_image, it, p, q);         break;
                case manhattan:         check_distance = findManhattanDistance(test_image, it);             break;
                case chebyshev:         check_distance = findChebyshevDistance(test_image, it);             break;
                case cosine:            check_distance = cosineSimilarity(test_image, it);                  break;
                case lbph_euclidean:    check_distance = findDistance_2(test_image, it);                    break;
                case lbph_manhattan:    check_distance = findManhattanDistance_2(test_image, it);           break;
                case lbph_cosine:       check_distance = cosineSimilarity_2(test_image, it);                break;
                case scaling:           check_distance = compareScaledImages(test_image, it);               break;
                case random:            check_distance = compareRandomPix(test_image, it, randomPixMask);   break;
                default:                                                                                    break;
            };

            if (method_flag != cosine && method_flag != lbph_cosine)
            {
                if (check_distance < closest_answer.first)
                {
                    closest_answer.first = check_distance;
                    closest_answer.second = it.name.left(9);
                }
            }
            else
            {
                if ((1 - check_distance) < (1 - closest_answer.first)) // 1 - check_distance < closest_answer
                {
                    closest_answer.first = check_distance;
                    closest_answer.second = it.name.left(9);
                }
            }
        }
    }

    return closest_answer;
}


double testMethod(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                       const int& method_flag, const std::vector<std::pair<int, int>>& randomPixMask,
                       const int& p, const int& q)
{
    int faults = 0;
    std::pair<double, QString> closest_answer;

    for (_Image& it : dataset) {
        closest_answer = getMethodAnswer(it, database, method_flag, randomPixMask, p, q);
        if (closest_answer.second != it.name.left(9)) ++faults;
    }

    std::cout << faults <<"\n";
    return (1.0 - (double) faults / dataset.size()) * 100; // in %
}
