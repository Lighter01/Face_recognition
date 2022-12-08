#include "recognition_call.h"

int main()
{
    std::vector<std::vector<_Image>> database(0);
    std::vector<_Image> dataset(0);
    int dataBase_size = 0, dataSet_size = 0;

    for (int i = 1; i < 10; ++i)
        makeATandTTest(database, dataset, dataBase_size, dataSet_size, random, i, 8);

    return 0;
}
