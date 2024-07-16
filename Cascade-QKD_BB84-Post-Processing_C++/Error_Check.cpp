#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

double Error_Check(vector<int> Tran, vector<int> Rec) {
    //Check Error Final
    int errorCount = 0;
    int totalElements = Tran.size();

    for (size_t i = 0; i < totalElements; ++i) {
        if (Tran[i] != Rec[i]) {
            ++errorCount;
        }
    }

    double errorPercentage = (static_cast<double>(errorCount) / totalElements) * 100;
    return errorPercentage;
}