#ifndef TEST_METHOD_H
#define TEST_METHOD_H

#include "_Image.h"

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
std::pair<double, _Image> getMethodAnswer(_Image& test_image, std::vector<std::vector<_Image>>& database,
                       const int& method_flag, QMultiMap<int, int>& randomPixMask,
                       const int& p = 2, const int& q = 2);

// method to calculate accuracy of any face recognition method
std::pair<double, _Image> testMethodAcc(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                       const int& method_flag, QMultiMap<int, int>& randomPixMask, int& faults, int& avg_dist,
                       const int& p = 2, const int& q = 2); // faults for the number of mistakes, avg_dist for making cleare how accurate method is when showing results in vizualiztion

// redefinition
// method to get _Image object for getting QImage from it and show it on ui form (vizuilize)
std::pair<double, _Image> testMethodViz(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                       const int& method_flag, QMultiMap<int, int>& randomPixMask,
                       int& index, const int& p = 2, const int& q = 2); // with index for visualization function

////////////////////////////////////////


#endif // TEST_METHOD_H
