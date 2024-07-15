#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "Cascade_Receiver.h"
#include "Cascade_Receiver_Processing.h"
#include "message_Struct.cpp"
using namespace std;

vector<int> sifted_Receiver;
vector<int> corrected_Receiver;

void Cascade_Receiver() {
    int i;

    // -------------------------> Receiver Reading the text Bits file
    ifstream inputFile("Receiver_data.txt");

    if (inputFile.is_open()) {
        char digit;
        while (inputFile >> digit) {
            if (digit == '0' || digit == '1') {
                sifted_Receiver.push_back(digit - '0'); // Convert char '0' or '1' to int 0 or 1
            }
            else {
                cerr << "Invalid character found in file: " << digit << endl;
            }
        }
        inputFile.close();
    }
    else {
        cerr << "Unable to open file." << endl;
    }

    corrected_Receiver = sifted_Receiver;


    ////----------------------> Receiver Sifting bin file
    //std::ifstream file("receiver_sift.bin", std::ios::binary);

    //if (!file.is_open()) {
    //    std::cerr << "Failed to open the file." << std::endl;
    //}

    //// Read the file byte by byte
    //unsigned char byte;
    //while (file.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char))) {
    //    // Convert the byte to a bitset and push each bit to sifted_Receiver
    //    std::bitset<8> bits(byte);
    //    for (int i = 7; i >= 0; --i) {
    //        sifted_Receiver.push_back(bits[i]);
    //    }
    //}

    //// Close the file
    //file.close();

    //corrected_Receiver = sifted_Receiver;


    //// --------------->Receiver getting the Transmitter file to check error Percentage (QBER)
    //inFile.open("Transmitter_data.txt");
    //if (inFile.fail()) { cout << "Error Opening File" << endl; }
    //string sifted_Transmitter = "";
    //while (inFile.get(c)) {
    //    sifted_Transmitter.push_back(c);
    //}
    //inFile.close();
       
    // //measuring QBER 
    //float QBER;
    //float Error_Count = 0;
    //for (i = 0;i < sifted_String.size();i++) {
    //    if (sifted_Transmitter[i] != sifted_String[i]) Error_Count++;
    //    else continue;
    //}

    //QBER = Error_Count / sifted_String.size();
    //cout << "QBER -> " << QBER << endl;

    ////--------------->converting sifted string into vector
    //for (char digit : sifted_String) {
    //    sifted_Receiver.push_back(digit - '0');
    //}
}
