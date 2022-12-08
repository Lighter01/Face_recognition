#ifndef RECOGNITION_CALL_H
#define RECOGNITION_CALL_H

#include "_Image.h"

////main////
void makeATandTTest(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                  int& dataBase_size, int& dataSet_size, const int& method_flag = lbph_euclidean,
                  const int& number_of_examples = 1, const int& histogram_step = 1);
////////////

////Main function - test any method////

// for single reference value
/*std::pair<double, QString> getMethodAnswer(_Image& test_image, std::vector<_Image>& database,
                       const int& method_flag, const std::vector<std::pair<int, int>>& randomPixMask,
                       const int& p, const int& q);
*/

/*double testMethod(std::vector<_Image>& database, std::vector<_Image>& dataset,
                       const int& method_flag = euclidean,
                       const std::vector<std::pair<int, int>>& randomPixMask = std::vector<std::pair<int,int>>(0),
                       const int& p = 2, const int& q = 2 );
*/


// for multiple reference values
std::pair<double, QString> getMethodAnswer(_Image& test_image, std::vector<std::vector<_Image>>& database,
                       const int& method_flag, const std::vector<std::pair<int, int>>& randomPixMask,
                       const int& p = 2, const int& q = 2);

double testMethod(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                       const int& method_flag, const std::vector<std::pair<int, int>>& randomPixMask,
                       const int& p = 2, const int& q = 2);
////////////////////////////////////////

#endif // RECOGNITION_CALL_H
