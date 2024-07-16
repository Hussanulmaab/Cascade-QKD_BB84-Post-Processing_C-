#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cstdlib>
#include "Cascade_Transmitter.h"
#include "Cascade_Transmitter_Processing.h"
using namespace std;

vector<int> sifted_Transmitter;

void Cascade_Transmitter() {
    cout << "Transmitter main " << endl;

    // -------------------------> Transmitter Reading the text Bits file
    std::ifstream inputFile("Transmitter_data.txt"); 

    if (inputFile.is_open()) {
        char digit;
        while (inputFile >> digit) {
            if (digit == '0' || digit == '1') {
                sifted_Transmitter.push_back(digit - '0'); // Convert char '0' or '1' to int 0 or 1
            }
            else {
                std::cerr << "Invalid character found in file: " << digit << std::endl;
            }
        }
        inputFile.close();
    }
    else {
        std::cerr << "Unable to open file." << std::endl;
    }

    ////----------------------> Transmitter Sifting bin file
    //std::ifstream file("transmitter_sift.bin", std::ios::binary);

    //if (!file.is_open()) {
    //    std::cerr << "Failed to open the file." << std::endl;
    //}

    //// Read the file bit by bit
    //unsigned char byte;
    //while (file.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char))) {
    //    // Convert the byte to a bitset and push each bit to sifted_Receiver
    //    std::bitset<8> bits(byte);
    //    for (int i = 7; i >= 0; --i) {
    //        sifted_Transmitter.push_back(bits[i]);
    //    }
    //}

    //// Close the file
    //file.close();

    Cascade_Transmitter_Processing();
}