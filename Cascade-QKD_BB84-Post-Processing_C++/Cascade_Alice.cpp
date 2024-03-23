#include <iostream>
#include <fstream>
#include <vector>
#include "Cascade_Alice.h"
#include "Cascade_Alice_Processing.h"
using namespace std;

vector<int> sifted_Alice;

void Cascade_Alice() {
    cout << "Alice main " << endl;
    // Alice Reading the Bits file
    ifstream inFile;
    inFile.open("Alice_data.txt");
    if (inFile.fail()) { cout << "Error Opening File" << endl; }
    char c;
    string sifted_String = "";
    while (inFile.get(c)) {
        sifted_String.push_back(c);
    }
    inFile.close();

    // converting sifted string into vector
    for (char digit : sifted_String) {
        sifted_Alice.push_back(digit - '0');
    }
    Cascade_Alice_Processing();
}