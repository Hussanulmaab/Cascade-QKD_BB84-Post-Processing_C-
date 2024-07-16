#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Permute.h"
#include "Cascade_Transmitter.h"
#include "Cascade_Receiver.h"
using namespace std;

void permuteVectors(vector<int>& v1, vector<int>& v2) {
    vector<int> permutation(v1.size());
    for (int i = 0; i < permutation.size(); ++i) {
        permutation[i] = i;
    }

    random_device rd;
    mt19937 g(rd());

    shuffle(permutation.begin(), permutation.end(), g);

    vector<int> temp1(v1.size()), temp2(v2.size());
    for (int i = 0; i < v1.size(); ++i) {
        temp1[i] = v1[permutation[i]];
        temp2[i] = v2[permutation[i]];
    }

    v1 = temp1;
    v2 = temp2;
}

void Permute() {
    permuteVectors(sifted_Transmitter, corrected_Receiver);
}
