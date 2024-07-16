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
#include "Public_RA_Toeplitz.h"
#include "Private_RA_Toeplitz.h"
#include "Error_Check.h"
#include "Permute.h"
using namespace std;

void Cascade_Transmitter_Processing() {
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

	//temp check counter
	int counter = 0;

	cout << "Round " << counter << endl;
	Err_Val = Error_Check(sifted_Transmitter, corrected_Receiver);
	cout << "Err val " << Err_Val << endl;


	int i,j,prevJ,k,l,m,n,parity = 0;
	for (i = 8; i <= sifted_Transmitter.size(); i *= 2 /*i*/) {

		//temp check counter
		counter += 1;
		if (counter == 20) break;

		cout << " -----------Round--------------- " << counter << endl;

		// initializing for new round
		Transmitter_Received_Message.block_num_Vect.clear();
		Transmitter_Received_Message.block_num_Parity_Vect.clear();
		removalIndexes.clear();
		s.clear();
		Err_Val = 0;
		T_RA.clear();
		R_RA.clear();

		if (i>8) Permute();

		for (l = 0; l < sifted_Transmitter.size()/(i*2); l++) {
			Transmitter_Received_Message.block_num_Vect.push_back(l);
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
		sort(Discard_Indexes.begin(), Discard_Indexes.end(), greater<int>());
		for (int index : Discard_Indexes) {
			if (index >= 0 && index < sifted_Transmitter.size()) {
				sifted_Transmitter.erase(sifted_Transmitter.begin() + index);
				corrected_Receiver.erase(corrected_Receiver.begin() + index);
			}
		}
		s.insert(removalIndexes.begin(), removalIndexes.end());
		Discard_Indexes.assign(s.begin(), s.end());


		// adapting and checking

		ofstream T_RA_Public("T_RA_Public_Check_B.txt");
		if (T_RA_Public.is_open()) {
			for (int number : sifted_Transmitter) {
				T_RA_Public << number;
			}
			T_RA_Public.close();
		}
		else {
			cerr << "Unable to open file." << endl;
		}

		ofstream R_RA_Public("R_RA_Public_Check_B.txt");
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
		Public_RA_Toeplitz();

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

		// Private Randomness Extraction for Enhanced Security
		if (Err_Val == 0) {
			cout << "INITIAL KEY SIZE ----------------------------------- : " << sifted_Receiver.size() << endl;
			Private_RA_Toeplitz();
			return;
		}
	}
}
