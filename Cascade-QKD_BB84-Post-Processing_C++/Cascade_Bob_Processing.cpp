#include <iostream>
#include <vector>
#include <fstream>
#include "Cascade_Bob.h"
#include "Cascade_Alice.h"
#include "message_Struct.cpp"
using namespace std;

void Cascade_Bob_Processing(message_Struct message) {

	int i,l,j;
	cout << "\n--------------------------------Cascade Bob Processing" << endl;

	vector<int> block;
	int parityA = 0;
	int parityB = 0;
	int parityF = 0;

	cout << "i -> " << message.Iter << "\t j -> " << message.Pass << endl;
	cout << "block vector size " << message.block_num_Parity_Vect.size();

	for (i = 0; i < message.block_num_Vect.size(); i++) {

		// ----------------------------> Alice
		cout << "\nAli Block -> ";
		for (l = 0; l < message.Pass; l++) {
			cout << sifted_Alice[(message.Pass * message.block_num_Vect[i] + l)] << " ";
			block.push_back(sifted_Alice[(message.Pass * message.block_num_Vect[i] + l)]);
		}
		cout << " -> ";
		for (j = 0; j < message.Pass; j++) {
			if (block[j] == 0) continue;
			else if (block[j] == 1) parityA += 1;
		}
		parityA = parityA % 2;
		block.clear();
		cout << " -> " << parityA << " " << message.block_num_Parity_Vect[i];
		parityA = 0;
		

		// ----------------------------> Bob
		cout << "\nBob Block -> ";
		for (l = 0; l < message.Pass; l++) {
			cout << sifted_Bob[(message.Pass * message.block_num_Vect[i] + l)] << " ";
			block.push_back(sifted_Bob[(message.Pass * message.block_num_Vect[i] + l)]);
		}
		cout << " -> ";
		for (j = 0; j < message.Pass; j++) {
			if (block[j] == 0) continue;
			else if (block[j] == 1) parityB += 1;
		}
		parityB = parityB % 2;
		block.clear();
		cout << " -> " << parityB << " " << message.block_num_Parity_Vect[i];
		parityB = 0;


		parityF = (parityA + parityB) % 2;

		cout << "\nFin Parity " << parityF;
		parityA = parityB = parityF = 0;
	}
	cout << "\n--------------------------------bob end " << endl;
}