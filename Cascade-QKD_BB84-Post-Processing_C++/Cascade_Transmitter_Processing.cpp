#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Cascade_Transmitter_Processing.h"
#include "Cascade_Transmitter.h"
#include "Cascade_Receiver_Processing.h"
#include "message_Struct.cpp"
#include "Cascade_Transmitter_Permute.h"
#include "Error_Check.h"
using namespace std;

void Cascade_Transmitter_Processing() {
	cout << "Transmitter Processing" << endl;

	message_Struct Transmitter_Received_Message;
	message_Struct Transmitter_Send_Message;
	Transmitter_Send_Message.Iter = 0;
	Transmitter_Send_Message.Pass = 0;
	Transmitter_Send_Message.block_num_Vect;

	vector<int> block;

	//temp check counter
	int counter = 0;

	int i,j,prevJ,k,l,m,n,parity = 0;
	for (i = 8; i <= sifted_Transmitter.size(); i *= 2 /*i*/ ) {
		
		cout << "Round " << counter << endl;
		Error_Check();

		//temp check counter
		counter += 1;
		if (counter == 6) break;

		Transmitter_Received_Message.block_num_Vect.clear();
		Transmitter_Received_Message.block_num_Parity_Vect.clear();

		////to be removed later
		//if (i == 32) {
		//	cout << "End" << endl;
		//	break;
		//}

		//to be removed later
		if (i > 4) Cascade_Transmitter_Permute();

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
				}
			}

			//cout << endl;
			for (int k = 0; k < Transmitter_Received_Message.block_num_Vect.size(); k++) {
				//cout << Transmitter_Received_Message.block_num_Parity_Vect[k] << " ";
			}
			prevJ = j;
			//cout << endl;
		}
		if (i == 8) i = 4;
		//cout << endl;
	}
}
