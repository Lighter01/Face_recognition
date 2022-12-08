#include "recognition_call.h"

int main()
{
    std::vector<std::vector<_Image>> database(0);
    std::vector<_Image> dataset(0);
    int dataBase_size = 0, dataSet_size = 0;

    makeATandTTest(database, dataset, dataBase_size, dataSet_size, lbph_manhattan, 3);

    return 0;
}
