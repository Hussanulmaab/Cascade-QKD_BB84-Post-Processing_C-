#include <iostream>
#include <fstream>
#include <vector>
#include "Cascade_Bob.h"
using namespace std;

vector<int> sifted_Bob;

void Cascade_Bob() {
    int i;
    // Alice Reading the Bits file
    ifstream inFile;
    inFile.open("Bob_data.txt");
    if (inFile.fail()) { cout << "Error Opening File" << endl; }
    char c;
    string sifted_String = "";
    while (inFile.get(c)) {
        sifted_String.push_back(c);
    }
    inFile.close();

    ////Bob getting the Alice file to check error Percentage (QBER)
    //inFile.open("Alice_data.txt");
    //if (inFile.fail()) { cout << "Error Opening File" << endl; }
    //string sifted_Alice = "";
    //while (inFile.get(c)) {
    //    sifted_Alice.push_back(c);
    //}
    //inFile.close();
       
    // //measuring QBER 
    //float QBER;
    //float Error_Count = 0;
    //for (i = 0;i < sifted_String.size();i++) {
    //    if (sifted_Alice[i] != sifted_String[i]) Error_Count++;
    //    else continue;
    //}

    //QBER = Error_Count / sifted_String.size();
    //cout << "QBER -> " << QBER << endl;

    // converting sifted string into vector
    for (char digit : sifted_String) {
        sifted_Bob.push_back(digit - '0');
    }
    for (int i = 0; i < sifted_Bob.size(); i++) {
        cout << sifted_Bob[i] << " ";
    }
}
