#include <iostream>
#include <vector>
#include <fstream>
#include "Cascade_Transmitter.h"
#include "Cascade_Receiver.h"
using namespace std;

void Error_Check() {
    // Creating Transmitter Error Reconciliated File
    ofstream outFileA("Transmitter_Error_Reconciliated.txt");

    if (!outFileA) {
        cerr << "Error: Could not open the file 'Final_Transmitter.txt' for writing." << endl;
    }

    for (const auto& element : sifted_Transmitter) {
        outFileA << element;
    }

    outFileA.close();

    // Creating Receiver Error Reconciliated File
    ofstream outFileB("Receiver_Error_Reconciliated.txt");

    if (!outFileB) {
        cerr << "Error: Could not open the file 'Final_Receiver.txt' for writing." << endl;
    }

    for (const auto& element : corrected_Receiver) {
        outFileB << element;
    }

    outFileB.close();

    //Check Error Final
    int errorCount = 0;
    int totalElements = sifted_Transmitter.size();

    for (size_t i = 0; i < totalElements; ++i) {
        if (sifted_Transmitter[i] != corrected_Receiver[i]) {
            ++errorCount;
        }
    }

    double errorPercentage = (static_cast<double>(errorCount) / totalElements) * 100;
    std::cout << "Error Percentage: " << errorPercentage << "%" << std::endl;
}