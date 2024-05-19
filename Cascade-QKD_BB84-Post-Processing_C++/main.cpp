#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include "Cascade_Alice.h"
#include "Cascade_Bob.h"
#include "message_Struct.cpp"
#include "Cascade_Bob_Processing.h"
#include "Cascade_Alice_Permute.h"
#include "Cascade_Bob_Permute.h"
using namespace std;
 
// Iteration Horizontal Pass Vertical

int main()
{
    Cascade_Bob();
    Cascade_Alice();
    
    //cout << endl;
    //for (size_t i = 0; i < corrected_Bob.size(); ++i) {
    //    std::cout << corrected_Bob[i] << " ";
    //}

    cout << endl;
    cout << "- - - - - - - - - - - - -Final - - - - - - -- - - -" << endl;
    for (size_t i = 0; i < sifted_Alice.size(); ++i) {
        std::cout << sifted_Alice[i] << " ";
    }
    cout << endl;
    for (size_t i = 0; i < corrected_Bob.size(); ++i) {
        std::cout << corrected_Bob[i] << " ";
    }

    return 0;
}
