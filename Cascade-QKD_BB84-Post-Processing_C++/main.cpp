#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <Python.h>
#include <Windows.h>
#include "Cascade_Transmitter.h"
#include "Cascade_Receiver.h"
#include "message_Struct.cpp"
#include <chrono>
using namespace std;
 
// Iteration Horizontal Pass Vertical

int main()
{
    auto start = chrono::high_resolution_clock::now();

    //Adaptable Error Reconciliation and Randomness Extraction
    Cascade_Receiver();
    Cascade_Transmitter();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}
