#ifndef RECOGNITION_CALL_H
#define RECOGNITION_CALL_H

#include "_Image.h"

////main////
void prepareData(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset, QMultiMap <int, int>& randomPixMask,
                                 const int& dataBase_size = 0, const int& dataSet_size = 0, const int& method_flag = 5,
                                 const int& number_of_examples = 1, const int& histogram_step = 1);
////////////


#endif // RECOGNITION_CALL_H
