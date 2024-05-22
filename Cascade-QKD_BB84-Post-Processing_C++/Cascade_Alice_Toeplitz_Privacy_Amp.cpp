#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void Cascade_Alice_Toeplitz_Privacy_Amp(vector<int> & vec) {

    vector<int> Final_Alice;
    
    int i, j, k, val = 0, negativeInd = 3, tempNeg = 10, sum = 0;

    // Making Toeplitz Matrix
    int toeplitz_Mat[10][10];

    for (i = 0; i < 10; i++) {

        if (i == 0);
        else {
            tempNeg = tempNeg - 1;
            negativeInd = tempNeg;
        }

        for (j = 0; j < 10; j++) {
            val = j;
            val = val % 10;
            if (i == 0) {
                toeplitz_Mat[i][j] = val;
            }
            else {
                if(j >= i) toeplitz_Mat[i][j] = toeplitz_Mat[i - 1][j - 1];
                else {
                    negativeInd = negativeInd % 10;
                    toeplitz_Mat[i][j] = negativeInd;
                    negativeInd += 1;
                }
            }
        }
    }

    // Vector Multiplication with Toeplitz Matrix for Privacy Amplification

    for (i = 0; i < vec.size() / 10; i++) {
        for (j = 0; j < 10; j++) {
            sum = 0;
            for (k = 0; k < 10; k++) {
                sum += (vec[(10*i) + k] * toeplitz_Mat[j][k]);
            }
            sum = sum % 2;
            Final_Alice.push_back(sum);
        }
    }
    
    // Saving
    ofstream outFile("Alice_Final.txt");

    for (const auto& element : Final_Alice) {
        outFile << element;
    }

    outFile.close();

    cout << endl;
}