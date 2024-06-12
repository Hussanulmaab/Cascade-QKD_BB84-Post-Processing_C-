#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iterator>
#include <numeric>
#include "Cascade_Transmitter.h"
#include "Cascade_Receiver_Permute.h"
using namespace std;

void TransmitterPermuteVector(vector<int>& vec, const vector<int>& permOrder) {
    vector<int> permutedVec(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        permutedVec[i] = vec[permOrder[i]];
    }
    vec = permutedVec;
}

void Cascade_Transmitter_Permute() {

    // Generate the permutation order (indices)
    vector<int> permOrder(sifted_Transmitter.size());
    iota(permOrder.begin(), permOrder.end(), 0); // Fill with 0, 1, ..., n-1

    // Shuffle the permutation order
    random_device rd;
    default_random_engine rng(rd());
    shuffle(permOrder.begin(), permOrder.end(), rng);

    // Permute the Transmitter vector
    TransmitterPermuteVector(sifted_Transmitter, permOrder);

    // Sending the Permutation Order to Receiver
    Cascade_Receiver_Permute(permOrder);
}