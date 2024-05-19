#include <iostream>
#include <vector>
#include <fstream>
#include "Cascade_Bob.h"
#include "Cascade_Alice.h"
#include "message_Struct.cpp"
using namespace std;

message_Struct Cascade_Bob_Processing(message_Struct message) {

	cout << "\n--------------------------------Cascade Bob Processing" << endl;

	int i, l, j;
	message_Struct Bob_Send_Message;
	message_Struct Bob_Received_Message;

	Bob_Received_Message = message;

	vector<int> block;
	int parityA = 0;
	int parityB = 0;
	int parityF = 0;

	cout << "i -> " << Bob_Received_Message.Iter << "\t j -> " << Bob_Received_Message.Pass << endl;
	cout << "block vector size " << Bob_Received_Message.block_num_Parity_Vect.size();

	for (i = 0; i < Bob_Received_Message.block_num_Vect.size(); i++) {

		 //----------------------------> Alice
		cout << "\nAli Block -> ";
		for (l = 0; l < Bob_Received_Message.Pass; l++) {
			cout << sifted_Alice[(Bob_Received_Message.Pass * Bob_Received_Message.block_num_Vect[i] + l)] << " ";
			block.push_back(sifted_Alice[(Bob_Received_Message.Pass * Bob_Received_Message.block_num_Vect[i] + l)]);
		}
		for (j = 0; j < Bob_Received_Message.Pass; j++) {
			if (block[j] == 0) continue;
			else if (block[j] == 1) parityA += 1;
		}
		block.clear();


		//----------------------------> Bob
		cout << "\nBob Block -> ";
		for (l = 0; l < Bob_Received_Message.Pass; l++) {
			cout << corrected_Bob[(Bob_Received_Message.Pass * Bob_Received_Message.block_num_Vect[i] + l)] << " ";
			block.push_back(corrected_Bob[(Bob_Received_Message.Pass * Bob_Received_Message.block_num_Vect[i] + l)]);
		}
		for (j = 0; j < Bob_Received_Message.Pass; j++) {
			if (block[j] == 0) continue;
			else if (block[j] == 1) parityB += 1;
		}
		parityB = parityB % 2;
		parityA = Bob_Received_Message.block_num_Parity_Vect[i];
		block.clear();

		cout << "\n-----------> A" << parityA << " B" << parityB;

		//final parity
		parityF = (parityA + parityB) % 2;
		cout << "\nFin Parity " << parityF;

		if (parityF == 1 && Bob_Received_Message.Pass > 1) {
			Bob_Send_Message.Iter = Bob_Received_Message.Iter;
			Bob_Send_Message.Pass = Bob_Received_Message.Pass;
			Bob_Send_Message.block_num_Vect.push_back(Bob_Received_Message.block_num_Vect[i]);
			Bob_Send_Message.block_num_Parity_Vect.push_back(parityF);
		}

		else if (parityF == 1 && Bob_Received_Message.Pass == 1) {
			Bob_Send_Message.Iter = Bob_Received_Message.Iter;
			Bob_Send_Message.Pass = Bob_Received_Message.Pass;
			Bob_Send_Message.block_num_Vect.push_back(Bob_Received_Message.block_num_Vect[i]);
			Bob_Send_Message.block_num_Parity_Vect.push_back(parityF);

			//correcting
			if (corrected_Bob[Bob_Received_Message.block_num_Vect[i]] == 1){
				corrected_Bob[Bob_Received_Message.block_num_Vect[i]] = 0;
			}
			else if (corrected_Bob[Bob_Received_Message.block_num_Vect[i]] == 0) {
				corrected_Bob[Bob_Received_Message.block_num_Vect[i]] = 1;
			}
		}

		parityA = parityB = parityF = 0;
	}
	cout << "\n--------------------------------bob end " << endl;

	return Bob_Send_Message;
}