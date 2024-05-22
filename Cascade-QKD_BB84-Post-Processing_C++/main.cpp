#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <Python.h>
#include <Windows.h>
#include "Cascade_Alice.h"
#include "Cascade_Bob.h"
#include "message_Struct.cpp"
#include "Cascade_Bob_Processing.h"
#include "Cascade_Alice_Permute.h"
#include "Cascade_Bob_Permute.h"
#include "Cascade_Alice_Privacy_Amp.h"
#include "Cascade_Bob_Privacy_Amp.h"
using namespace std;
 
// Iteration Horizontal Pass Vertical

int main()
{

    //Error Reconciliation
    Cascade_Bob();
    Cascade_Alice();

    // Creating Final Alice Error Reconciliated File
    std::ofstream outFileA("Alice_Error_Reconciliated.txt");

    if (!outFileA) {
        cerr << "Error: Could not open the file 'Final_Alice.txt' for writing." << std::endl;
        return 1;
    }

    for (const auto& element : sifted_Alice) {
        outFileA << element;
    }

    outFileA.close();

    // Creating Final Bob Error Reconciliated File
    std::ofstream outFileB("Bob_Error_Reconciliated.txt");

    if (!outFileB) {
        cerr << "Error: Could not open the file 'Final_Bob.txt' for writing." << std::endl;
        return 1;
    }

    for (const auto& element : corrected_Bob) {
        outFileB << element;
    }

    outFileB.close();

    //Check Error Final
    int errorCount = 0;
    int totalElements = sifted_Alice.size();

    for (size_t i = 0; i < totalElements; ++i) {
        if (sifted_Alice[i] != corrected_Bob[i]) {
            ++errorCount;
        }
    }

    double errorPercentage = (static_cast<double>(errorCount) / totalElements) * 100;
    std::cout << "Error Percentage: " << errorPercentage << "%" << std::endl;

    //Privacy Amplification
    cout << "Privacy Amplification " << endl;

    Cascade_Alice_Privacy_Amp();
    cout << endl;
    Cascade_Bob_Privacy_Amp();

    return 0;
}
