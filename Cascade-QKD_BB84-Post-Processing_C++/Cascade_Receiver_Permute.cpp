#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iterator>
#include <numeric>
#include "Cascade_Receiver.h"
using namespace std;

void ReceiverPermuteVector(vector<int>& vec, const vector<int>& permOrder) {
    vector<int> permutedVec(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        permutedVec[i] = vec[permOrder[i]];
    }
    vec = permutedVec;
}

void Cascade_Receiver_Permute(vector <int> permOrder) {
    // Permute the Receiver vector
    ReceiverPermuteVector(corrected_Receiver, permOrder);
}