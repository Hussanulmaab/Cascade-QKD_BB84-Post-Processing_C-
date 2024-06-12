#include <iostream>
#include <vector>
#include <fstream>
#include "Cascade_Receiver.h"
#include "Cascade_Transmitter.h"
#include "message_Struct.cpp"
using namespace std;

message_Struct Cascade_Receiver_Processing(message_Struct message) {

	//cout << "\n--------------------------------Cascade Receiver Processing" << endl;

	int i, l, j;
	message_Struct Receiver_Send_Message;
	message_Struct Receiver_Received_Message;

	Receiver_Received_Message = message;

	vector<int> block;
	int parityA = 0;
	int parityB = 0;
	int parityF = 0;

	//cout << "i -> " << Receiver_Received_Message.Iter << "\t j -> " << Receiver_Received_Message.Pass << endl;
	//cout << "block vector size " << Receiver_Received_Message.block_num_Parity_Vect.size();

	for (i = 0; i < Receiver_Received_Message.block_num_Vect.size(); i++) {

		 //----------------------------> Transmitter
		if (i % 100 == 0) {
			//cout << "\nAli Block -> ";
		}
		for (l = 0; l < Receiver_Received_Message.Pass; l++) {
			if (i % 100 == 0) {
				//cout << sifted_Transmitter[(Receiver_Received_Message.Pass * Receiver_Received_Message.block_num_Vect[i] + l)] << " ";
			}
			block.push_back(sifted_Transmitter[(Receiver_Received_Message.Pass * Receiver_Received_Message.block_num_Vect[i] + l)]);
		}
		for (j = 0; j < Receiver_Received_Message.Pass; j++) {
			if (block[j] == 0) continue;
			else if (block[j] == 1) parityA += 1;
		}
		block.clear();


		//----------------------------> Receiver
		if (i % 100 == 0) {
			//cout << "\nReceiver Block -> ";
		}
		for (l = 0; l < Receiver_Received_Message.Pass; l++) {
			if (i % 100 == 0) {
				//cout << corrected_Receiver[(Receiver_Received_Message.Pass * Receiver_Received_Message.block_num_Vect[i] + l)] << " ";
			}
			block.push_back(corrected_Receiver[(Receiver_Received_Message.Pass * Receiver_Received_Message.block_num_Vect[i] + l)]);
		}
		for (j = 0; j < Receiver_Received_Message.Pass; j++) {
			if (block[j] == 0) continue;
			else if (block[j] == 1) parityB += 1;
		}
		parityB = parityB % 2;
		parityA = Receiver_Received_Message.block_num_Parity_Vect[i];
		block.clear();

		if (i % 100 == 0) {
			//cout << "\n-----------> A" << parityA << " B" << parityB;
		}

		//final parity
		parityF = (parityA + parityB) % 2;
		if (i % 100 == 0) {
			//cout << "\nFin Parity " << parityF;
		}
		if (parityF == 1 && Receiver_Received_Message.Pass > 1) {
			Receiver_Send_Message.Iter = Receiver_Received_Message.Iter;
			Receiver_Send_Message.Pass = Receiver_Received_Message.Pass;
			Receiver_Send_Message.block_num_Vect.push_back(Receiver_Received_Message.block_num_Vect[i]);
			Receiver_Send_Message.block_num_Parity_Vect.push_back(parityF);
		}

		else if (parityF == 1 && Receiver_Received_Message.Pass == 1) {
			Receiver_Send_Message.Iter = Receiver_Received_Message.Iter;
			Receiver_Send_Message.Pass = Receiver_Received_Message.Pass;
			Receiver_Send_Message.block_num_Vect.push_back(Receiver_Received_Message.block_num_Vect[i]);
			Receiver_Send_Message.block_num_Parity_Vect.push_back(parityF);

			//correcting
			if (corrected_Receiver[Receiver_Received_Message.block_num_Vect[i]] == 1){
				corrected_Receiver[Receiver_Received_Message.block_num_Vect[i]] = 0;
			}
			else if (corrected_Receiver[Receiver_Received_Message.block_num_Vect[i]] == 0) {
				corrected_Receiver[Receiver_Received_Message.block_num_Vect[i]] = 1;
			}
		}

		parityA = parityB = parityF = 0;
	}
	//cout << "\n--------------------------------bob end " << endl;

	return Receiver_Send_Message;
}