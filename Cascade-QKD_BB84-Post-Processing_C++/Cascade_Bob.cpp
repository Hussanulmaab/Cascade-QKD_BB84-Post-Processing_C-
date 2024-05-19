#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "Cascade_Bob.h"
#include "Cascade_Bob_Processing.h"
#include "message_Struct.cpp"
using namespace std;

vector<int> sifted_Bob;
vector<int> corrected_Bob;

void Cascade_Bob() {
    int i;

    // -------------------------> Bob Reading the text Bits file
    ifstream inputFile("Bob_data.txt");

    if (inputFile.is_open()) {
        char digit;
        while (inputFile >> digit) {
            if (digit == '0' || digit == '1') {
                sifted_Bob.push_back(digit - '0'); // Convert char '0' or '1' to int 0 or 1
            }
            else {
                cerr << "Invalid character found in file: " << digit << endl;
                return; // Exit with error code
            }
        }
        inputFile.close();
    }
    else {
        cerr << "Unable to open file." << endl;
        return; // Exit with error code
    }

    corrected_Bob = sifted_Bob;

    ////----------------------> Bob Sifting bin file
    //std::ifstream file("receiver_key.bin", std::ios::binary);

    //if (!file.is_open()) {
    //    std::cerr << "Failed to open the file." << std::endl;
    //}

    //// Read the file byte by byte
    //unsigned char byte;
    //while (file.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char))) {
    //    // Convert the byte to a bitset and push each bit to sifted_Bob
    //    std::bitset<8> bits(byte);
    //    for (int i = 7; i >= 0; --i) {
    //        sifted_Bob.push_back(bits[i]);
    //    }
    //}

    //// Close the file
    //file.close();


    //// --------------->Bob getting the Alice file to check error Percentage (QBER)
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

    ////--------------->converting sifted string into vector
    //for (char digit : sifted_String) {
    //    sifted_Bob.push_back(digit - '0');
    //}
}
