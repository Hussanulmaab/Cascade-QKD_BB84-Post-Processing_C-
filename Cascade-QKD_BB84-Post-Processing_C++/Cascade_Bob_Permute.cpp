#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iterator>
#include <numeric>
#include "Cascade_Bob.h"
using namespace std;

void BobPermuteVector(vector<int>& vec, const vector<int>& permOrder) {
    vector<int> permutedVec(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        permutedVec[i] = vec[permOrder[i]];
    }
    vec = permutedVec;
}

void Cascade_Bob_Permute(vector <int> permOrder) {
    // Permute the Bob vector
    BobPermuteVector(corrected_Bob, permOrder);
}