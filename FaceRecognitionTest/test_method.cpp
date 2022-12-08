#include "test_method.h"
#include "random_pixels_method.h"
#include "histogram_method.h"
#include "lbph_method.h"
#include "scaling_method.h"
#include "voting_method.h"

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
std::pair<double, _Image> getMethodAnswer(_Image& test_image, std::vector<std::vector<_Image>>& database,
                       const int& method_flag, QMultiMap<int, int>& randomPixMask,
                       const int& p, const int& q)
{

    std::pair<double, _Image> closest_answer;

    switch (method_flag)
    {
        case euclidean :     closest_answer.first = DBL_MAX; break;
        case stepped :       closest_answer.first = DBL_MAX; break;
        case manhattan:      closest_answer.first = DBL_MAX; break;
        case chebyshev:      closest_answer.first = DBL_MAX; break;
        case cosine:         closest_answer.first = -1.01;   break;
        case lbph_euclidean: closest_answer.first = DBL_MAX; break;
        case lbph_manhattan: closest_answer.first = DBL_MAX; break;
        case lbph_cosine:    closest_answer.first = -1.01;   break;
        case scaling:        closest_answer.first = DBL_MAX; break;
        case random:         closest_answer.first = DBL_MAX; break;
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
                    closest_answer.second = it;
                }
            }
            else
            {
                if ((1 - check_distance) < (1 - closest_answer.first)) // 1 - check_distance < closest_answer
                {
                    closest_answer.first = check_distance;
                    closest_answer.second = it;
                }
            }
        }
    }

    return closest_answer;
}

std::pair<double, _Image> testMethodAcc(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                       const int& method_flag, QMultiMap<int, int>& randomPixMask, int& faults, int& avg_dist,
                       const int& p, const int& q)
{
    faults = 0;
    avg_dist = 0;
    std::pair<double, _Image> closest_answer;

    for (_Image& it : dataset) {
        closest_answer = getMethodAnswer(it, database, method_flag, randomPixMask, p, q);
        if (closest_answer.second.name.left(9) != it.name.left(9)) {
            ++faults;
        } else {
            avg_dist += closest_answer.first;
        }
    }

    avg_dist /= (dataset.size() - faults); // average distance among all answers

    return closest_answer;
}

// Return base testMethod() function here, without visualization

std::pair<double, _Image> testMethodViz(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                       const int& method_flag, QMultiMap<int, int>& randomPixMask,
                       int& index, const int& p, const int& q)
{
//    faults = 0;
    std::pair<double, _Image> closest_answer;

    _Image& it = dataset[index];
    closest_answer = getMethodAnswer(it, database, method_flag, randomPixMask, p, q);
//    if (closest_answer.second.name.left(9) != it.name.left(9)) ++faults;

    return closest_answer;
}
