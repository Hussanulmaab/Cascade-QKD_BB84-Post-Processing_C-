#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cstdlib>
#include "Cascade_Alice.h"
#include "Cascade_Alice_Processing.h"
using namespace std;

vector<int> sifted_Alice;

void Cascade_Alice() {
    cout << "Alice main " << endl;


    // -------------------------> Alice Reading the text Bits file
    std::ifstream inputFile("Alice_data.txt"); 

    if (inputFile.is_open()) {
        char digit;
        while (inputFile >> digit) {
            if (digit == '0' || digit == '1') {
                sifted_Alice.push_back(digit - '0'); // Convert char '0' or '1' to int 0 or 1
            }
            else {
                std::cerr << "Invalid character found in file: " << digit << std::endl;
                return; // Exit with error code
            }
        }
        inputFile.close();
    }
    else {
        std::cerr << "Unable to open file." << std::endl;
        return; // Exit with error code
    }


    ////----------------------> Alice Sifting bin file
    //std::ifstream file("receiver_key.bin", std::ios::binary);

    //if (!file.is_open()) {
    //    std::cerr << "Failed to open the file." << std::endl;
    //}

    //// Read the file bit by bit
    //unsigned char byte;
    //while (file.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char))) {
    //    // Convert the byte to a bitset and push each bit to sifted_Bob
    //    std::bitset<8> bits(byte);
    //    for (int i = 7; i >= 0; --i) {
    //        sifted_Alice.push_back(bits[i]);
    //    }
    //}

    //// Close the file
    //file.close();

    Cascade_Alice_Processing();
}