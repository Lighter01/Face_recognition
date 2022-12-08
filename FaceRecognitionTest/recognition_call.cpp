#include "recognition_call.h"
#include "random_pixels_method.h"

void readFolderFiles(QStringList& files_folder, const QString& files_dir_path,
                     std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                     const int& dataBase_size, const int& dataSet_size, const int& method_flag,
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

        // Choosing n random references
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

        readAllData(references_1, path_to_current_images_dir, database[database_reference_index++], histogram_step);
        readAllData(tests_1, path_to_current_images_dir, dataset, histogram_step);
    }
}

// dataBase_size may be usefull for refactoring dataset initialization
void prepareData(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset, QMultiMap <int, int>& randomPixMask,
                    const int& dataBase_size, const int& dataSet_size, const int& method_flag,
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
//    std::cout << testVotingMethod(database, dataset, randomPixMask) << "% is the accuracy of face recognition\n";

//    database.clear(); dataset.clear();
}

