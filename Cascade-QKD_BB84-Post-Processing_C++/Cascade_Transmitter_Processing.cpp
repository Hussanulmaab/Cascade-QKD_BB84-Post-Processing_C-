#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include "Cascade_Transmitter_Processing.h"
#include "Cascade_Transmitter.h"
#include "Cascade_Receiver_Processing.h"
#include "message_Struct.cpp"
#include "Toeplitz.h"
#include "Error_Check.h"
#include "Circulant.h"
#include "Dodis.h"
#include "Permute.h"
using namespace std;

void Cascade_Transmitter_Processing() {

	float err = Error_Check(sifted_Transmitter, corrected_Receiver);
	cout << "Initial Error Percentage -- " << err << endl;

	//cout << "Transmitter Processing" << endl;

	double Err_Val;
	message_Struct Transmitter_Received_Message;
	message_Struct Transmitter_Send_Message;
	Transmitter_Send_Message.Iter = 0;
	Transmitter_Send_Message.Pass = 0;
	Transmitter_Send_Message.block_num_Vect;

	vector<int> block;
	vector<int> removalIndexes;
	vector<int> Discard_Indexes;
	vector<int> T_RA;
	vector<int> R_RA;
	set<int> s;
	int DI;

	//temp check counter
	int counter = 0;
	int Channel_Uses = 0;

	cout << "Round " << counter << endl;
	Err_Val = Error_Check(sifted_Transmitter, corrected_Receiver);
	cout << "Err val " << Err_Val << endl;

	int i,j,prevJ,k,l,m,n,parity = 0;

	//double small_err_Val = (Err_Val / 100.0);
	//double temp_i = 0.92 / small_err_Val;
	//temp_i = floor(temp_i);
	//cout << "Initial block size " << temp_i << endl;

	//int tempo;

	for (i = 8; i <= sifted_Transmitter.size(); i *= 2 /*i*/) {

		//tempo = i;

		//if (i == 8) {
		//	i = 125;
		//}
		//if (i == 16) {
		//	i = 400;
		//}
		//if (i == 32) {
		//	i = 400;
		//}
		//else i = 400;

		//temp check counter
		counter += 1;
		if (counter == 50) break;

		cout << " -----------Round--------------- " << counter << endl;

		// initializing for new round
		Transmitter_Received_Message.block_num_Vect.clear();
		Transmitter_Received_Message.block_num_Parity_Vect.clear();
		removalIndexes.clear();
		s.clear();
		Err_Val = 0;
		T_RA.clear();
		R_RA.clear();

		for (l = 0; l < sifted_Transmitter.size()/(i*2); l++) {
			Transmitter_Received_Message.block_num_Vect.push_back(l);
			removalIndexes.push_back((i * 2) * (l + 1) - 1);
			removalIndexes.push_back((i * 2) * (l + 1) - 1 - i);
		}
		prevJ = i*2;

		for (j = i; j >= 1; j = j/2) {

			for (k = 0; k < Transmitter_Received_Message.block_num_Vect.size(); k++) {

				for (l = 0; l < 2; l++) {
					for (m = 0; m < j; m++) {
						block.push_back(sifted_Transmitter[(prevJ * Transmitter_Received_Message.block_num_Vect[k]) + (j * l) + m]);
						}
					for (n = 0; n < j; n++) {
						if (block[n] == 0) continue;
						else if (block[n] == 1) parity += 1;
					}
					Transmitter_Send_Message.block_num_Vect.push_back((prevJ * Transmitter_Received_Message.block_num_Vect[k] / j) + l);
					parity = parity % 2;
					Transmitter_Send_Message.block_num_Parity_Vect.push_back(parity);
					block.clear();
					parity = 0;
				}
			}
			Transmitter_Send_Message.Iter = i;
			Transmitter_Send_Message.Pass = j;
			Transmitter_Received_Message = Cascade_Receiver_Processing(Transmitter_Send_Message);
			Channel_Uses += 2;
			Transmitter_Send_Message.block_num_Vect.clear();
			Transmitter_Send_Message.block_num_Parity_Vect.clear();

			//cout << "--------------------------------Transmitter back " << endl;
			for (int k = 0; k < Transmitter_Received_Message.block_num_Vect.size(); k++) {
				//cout << "P" << j << "[" << Transmitter_Received_Message.block_num_Vect[k] << "]" << " ";

				for (l = 0; l < Transmitter_Received_Message.Pass; l++) {
					//cout << sifted_Transmitter[(Transmitter_Received_Message.Pass * Transmitter_Received_Message.block_num_Vect[k] + l)] << " ";
					if (Transmitter_Received_Message.Pass != 1) {
						if (l == Transmitter_Received_Message.Pass - 1) {
							removalIndexes.push_back(Transmitter_Received_Message.Pass * Transmitter_Received_Message.block_num_Vect[k] + l);
						}
					}
					else continue;
				}
			}

			//cout << endl;
			for (int k = 0; k < Transmitter_Received_Message.block_num_Vect.size(); k++) {
				//cout << Transmitter_Received_Message.block_num_Parity_Vect[k] << " ";
			}
			prevJ = j;
			//cout << endl;
		}

		//Discarding 
		s.insert(removalIndexes.begin(), removalIndexes.end());
		Discard_Indexes.assign(s.begin(), s.end());
		sort(Discard_Indexes.begin(), Discard_Indexes.end(), std::greater<int>());

		// Remove elements from sifted_Transmitter based on Discard_Indexes
		for (int index : Discard_Indexes) {
			if (index >= 0 && index < sifted_Transmitter.size()) {
				sifted_Transmitter.erase(sifted_Transmitter.begin() + index);
				corrected_Receiver.erase(corrected_Receiver.begin() + index);
			}
		}

		// adapting and checking

		ofstream T_RA_Public("T_EC_Bits.txt");
		if (T_RA_Public.is_open()) {
			for (int number : sifted_Transmitter) {
				T_RA_Public << number;
			}
			T_RA_Public.close();
		}
		else {
			cerr << "Unable to open file." << endl;
		}

		ofstream R_RA_Public("R_EC_Bits.txt");
		if (R_RA_Public.is_open()) {
			for (int number : corrected_Receiver) {
				R_RA_Public << number;
			}
			R_RA_Public.close();
		}
		else {
			cerr << "Unable to open file." << endl;
		}

		// Adaptable Randomness Extraction
		cout << "Adaptable Randomness Extraction ...." << endl;
		Circulant();

		ifstream file1("T_RA_Public_Check_A.txt");
		if (file1.is_open()) {
			char bit;
			while (file1 >> bit) {
				T_RA.push_back(bit - '0');
			}
			file1.close();
		}

		ifstream file2("R_RA_Public_Check_A.txt");
		if (file2.is_open()) {
			char bit;
			while (file2 >> bit) {
				R_RA.push_back(bit - '0');
			}
			file2.close();
		}

		Err_Val = Error_Check(sifted_Transmitter, corrected_Receiver);
		cout << "Err val SIFT : " << Err_Val << "%" << endl;
		Err_Val = Error_Check(T_RA, R_RA);
		cout << "Err val GOSU : " << Err_Val << "%" << endl;

		sifted_Transmitter.clear();
		corrected_Receiver.clear();

		ifstream file3("T_EC_Bits.txt");
		if (file3.is_open()) {
			char bit;
			while (file3 >> bit) {
				sifted_Transmitter.push_back(bit - '0');
			}
			file3.close();
		}

		ifstream file4("R_EC_Bits.txt");
		if (file4.is_open()) {
			char bit;
			while (file4 >> bit) {
				corrected_Receiver.push_back(bit - '0');
			}
			file4.close();
		}
		Channel_Uses += 2;	

		// Private Randomness Extraction for Enhanced Security
		if (Err_Val == 0) {
			Channel_Uses += 1;
			Circulant();
			ifstream inputFile("Seed_Size.txt");
			int n2_T;
			inputFile >> n2_T;
			cout << "INITIAL Key SIZE ----------------------------------- : " << sifted_Receiver.size() << endl;
			cout << "Final Error Corrected SIZE ----------------------------------- : " << corrected_Receiver.size() << endl;
			cout << "Channel Uses --------------------------------------------- : " << Channel_Uses << endl;
			cout << "Final Seed Size ----------------------------------- : " << n2_T << endl;
			cout << "Final (Randomness Extracted) Length ----------------------------------- : R :: " << R_RA.size() << "|| T:: " << T_RA.size() << endl;
			return;
		}

		Channel_Uses += 1;
		Permute();
	}
}
