#ifndef VOTING_METHOD_H
#define VOTING_METHOD_H

#include "_Image.h"

////Voting method: current version - (lbph + scaling + random)////

double testVotingMethod(std::vector<std::vector<_Image>>& database, std::vector<_Image>& dataset,
                        QMultiMap<int, int>& randomPixMask,
                        const int& p = 2, const int& q = 2);

#endif // VOTING_METHOD_H
