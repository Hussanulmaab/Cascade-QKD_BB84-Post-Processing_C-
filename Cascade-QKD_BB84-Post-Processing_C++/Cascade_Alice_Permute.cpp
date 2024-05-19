#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iterator>
#include <numeric>
#include "Cascade_Alice.h"
#include "Cascade_Bob_Permute.h"
using namespace std;

void AlicePermuteVector(vector<int>& vec, const vector<int>& permOrder) {
    vector<int> permutedVec(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        permutedVec[i] = vec[permOrder[i]];
    }
    vec = permutedVec;
}

void Cascade_Alice_Permute() {

    cout << "Alice Permute";

    // Generate the permutation order (indices)
    vector<int> permOrder(sifted_Alice.size());
    iota(permOrder.begin(), permOrder.end(), 0); // Fill with 0, 1, ..., n-1

    // Shuffle the permutation order
    random_device rd;
    default_random_engine rng(rd());
    shuffle(permOrder.begin(), permOrder.end(), rng);

    // Permute the Alice vector
    AlicePermuteVector(sifted_Alice, permOrder);

    // Sending the Permutation Order to Bob
    Cascade_Bob_Permute(permOrder);
}