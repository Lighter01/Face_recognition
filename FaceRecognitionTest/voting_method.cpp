#include "voting_method.h"
#include "test_method.h"

double testVotingMethod(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                        QMultiMap<int, int>& randomPixMask,
                        const int& p, const int& q)
{
    int faults = 0;
    std::pair<double, _Image> lbph_closest_answer, random_closest_answer, scaling_closest_answer;

    for (_Image& it : dataset) {
        lbph_closest_answer = getMethodAnswer(it, database, lbph_manhattan, randomPixMask, p, q);
        random_closest_answer = getMethodAnswer(it, database, random, randomPixMask, p, q);
        scaling_closest_answer = getMethodAnswer(it, database, scaling, randomPixMask, p, q);

        QMap<QString, int> answers_freq;
        answers_freq[lbph_closest_answer.second.name]++;
        answers_freq[random_closest_answer.second.name]++;
        answers_freq[scaling_closest_answer.second.name]++;

        QString final_answer;

        if (answers_freq.size() != 3) {
            final_answer = std::max_element(answers_freq.begin(), answers_freq.end()).key();
        }
        else { // if all answers are different, prefer lbph
            final_answer = lbph_closest_answer.second.name;
        }

        if (final_answer != it.name.left(9)) ++faults;  // why 9? Just because 9

    }

//    std::cout << faults <<"\n";
    return (1.0 - (double) faults / dataset.size()) * 100; // in %
}
