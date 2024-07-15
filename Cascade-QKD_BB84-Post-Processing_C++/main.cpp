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
#include "Cascade_Receiver_Processing.h"
#include "Cascade_Transmitter_Permute.h"
#include "Cascade_Receiver_Permute.h"
#include "Cascade_Transmitter_Privacy_Amp.h"
#include "Cascade_Receiver_Privacy_Amp.h"
#include "Error_Check.h"
using namespace std;
 
// Iteration Horizontal Pass Vertical

int main()
{

    //Error Reconciliation
    Cascade_Receiver();
    Cascade_Transmitter();

    //checking Error
    Error_Check();

    //Privacy Amplification
    cout << "Privacy Amplification ...." << endl;

    //Cascade_Transmitter_Privacy_Amp();
    //cout << endl;
    //Cascade_Receiver_Privacy_Amp();

    //vector<int> vec = { 1, 2, 3, 4, 5 };

    //vec.erase(vec.begin() + 1);
    //vec.erase(vec.begin() + 1);
    //vec.erase(vec.begin() + 1);
    //vec.erase(vec.begin() + 1);
    //

    //for (int i = 0; i < vec.size(); ++i) {
    //    std::cout << vec[i] << " ";
    //}

    return 0;
}
