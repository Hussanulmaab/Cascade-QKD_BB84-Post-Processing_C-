#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <Python.h>
#include <Windows.h>
#include <random>
#include "Cascade_Transmitter.h"
#include "Cascade_Receiver.h"
#include "message_Struct.cpp"
#include <chrono>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace chrono;

// Iteration Horizontal Pass Vertical

int main()
{
    // Get the number of bits from the user
    int numBits;
    cout << "Enter the number of bits: ";
    cin >> numBits;
    float errorPercentage;
    cout << "Enter the percentage of error (e.g., 5.5 for 5.5%): ";
    cin >> errorPercentage;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> bitDist(0, 1);
    uniform_real_distribution<> probDist(0.0, 1.0);
    ofstream transmitterFile("Transmitter_data.txt");
    if (!transmitterFile) {
        cout << "Error creating Transmitter_data file.\n";
        return 1;
    }

    ofstream receiverFile("Receiver_data.txt");
    if (!receiverFile) {
        cout << "Error creating Receiver_data file.\n";
        return 1;
    }

    for (int i = 0; i < numBits; ++i) {
        int bit = bitDist(gen);
        transmitterFile << bit;
        receiverFile << bit;
    }
    transmitterFile.close();
    receiverFile.close();
    fstream receiverFileRW("Receiver_data.txt");
    if (!receiverFileRW) {
        cout << "Error opening Receiver_data file for reading and writing.\n";
        return 1;
    }
    for (int i = 0; i < numBits; ++i) {
        int pos = i;
        receiverFileRW.seekg(pos, std::ios::beg);
        char bit;
        receiverFileRW.get(bit);
        if (probDist(gen) < (errorPercentage / 100.0f)) {
            receiverFileRW.seekp(pos, std::ios::beg);
            receiverFileRW.put(bit == '0' ? '1' : '0');
        }
    }
    receiverFileRW.close();

    //Timer Start
    auto start_time = system_clock::now();

    //Adaptable Error Reconciliation and Randomness Extraction
    Cascade_Receiver();
    Cascade_Transmitter();

    // Timer End 
    auto end_time = system_clock::now();
    duration<double> elapsed_seconds = end_time - start_time;
    cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
