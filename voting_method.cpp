#include "voting_method.h"
#include "recognition_call.h"

int step_1 = 0, step_2 = 0, step_3 = 0, step_4 = 0;

double testVotingMethod(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                        const std::vector<std::pair<int, int>>& randomPixMask,
                        const int& p, const int& q)
{
    int faults = 0;
    int faults_hist = 0, faults_scale = 0, faults_rand = 0, faults_lbph = 0;
    std::pair<double, QString> lbph_closest_answer, random_closest_answer, scaling_closest_answer, histogram_closest_answer;

    for (_Image& it : dataset) {
        lbph_closest_answer = getMethodAnswer(it, database, lbph_manhattan, randomPixMask, p, q);
        random_closest_answer = getMethodAnswer(it, database, random, randomPixMask, p, q);
        scaling_closest_answer = getMethodAnswer(it, database, scaling, randomPixMask, p, q);
        histogram_closest_answer = getMethodAnswer(it, database, manhattan, randomPixMask, p, q);

        QMap<QString, int> answers_freq;
        answers_freq[lbph_closest_answer.second] += 10 + step_1;
        answers_freq[random_closest_answer.second] += 5 + step_2;
        answers_freq[scaling_closest_answer.second] += 5 + step_3;
        answers_freq[histogram_closest_answer.second] += 0 + step_4;

        QString final_answer;

        final_answer = std::max_element(answers_freq.begin(), answers_freq.end()).key();

//        if (answers_freq.size() != 4) {
//            final_answer = std::max_element(answers_freq.begin(), answers_freq.end()).key();
//        }
//        else { // if all answers are different, prefer lbph
//            final_answer = lbph_closest_answer.second;
//        }



        if (final_answer != it.name.left(9)) ++faults;  // why 9? Just because 9

        if (lbph_closest_answer.second != it.name.left(9)) ++faults_lbph;
        if (random_closest_answer.second != it.name.left(9)) ++faults_rand;
        if (scaling_closest_answer.second != it.name.left(9)) ++faults_scale;
        if (histogram_closest_answer.second != it.name.left(9)) ++faults_hist;

    }

    step_1 += 1, step_2 += 2, step_3 += 2, step_4 += 3;

    std::cout << faults_hist << " " << faults_scale << " " << faults_rand << " " << faults_lbph << '\n';
    return (1.0 - (double) faults / dataset.size()) * 100; // in %
}
