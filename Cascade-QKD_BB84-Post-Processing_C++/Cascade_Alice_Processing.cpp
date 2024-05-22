#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Cascade_Alice_Processing.h"
#include "Cascade_Alice.h"
#include "Cascade_Bob_Processing.h"
#include "message_Struct.cpp"
#include "Cascade_Alice_Permute.h"
using namespace std;

void Cascade_Alice_Processing() {
	cout << "Alice Processing" << endl;

	message_Struct Alice_Received_Message;
	message_Struct Alice_Send_Message;
	Alice_Send_Message.Iter = 0;
	Alice_Send_Message.Pass = 0;
	Alice_Send_Message.block_num_Vect;

	vector<int> block;

	//temp check counter
	int counter = 0;

	int i,j,prevJ,k,l,m,n,parity = 0;
	for (i = 8; i <= sifted_Alice.size(); i *= 2 /*i*/ ) {
		
		//temp check counter
		counter += 1;
		if (counter == 100) break;

		Alice_Received_Message.block_num_Vect.clear();
		Alice_Received_Message.block_num_Parity_Vect.clear();

		////to be removed later
		//if (i == 32) {
		//	cout << "End" << endl;
		//	break;
		//}

		//to be removed later
		if (i > 4) Cascade_Alice_Permute();

		for (l = 0; l < sifted_Alice.size()/(i*2); l++) {
			Alice_Received_Message.block_num_Vect.push_back(l);
		}
		prevJ = i*2;

		for (j = i; j >= 1; j = j/2) {

			for (k = 0; k < Alice_Received_Message.block_num_Vect.size(); k++) {

				for (l = 0; l < 2; l++) {
					for (m = 0; m < j; m++) {
						block.push_back(sifted_Alice[(prevJ * Alice_Received_Message.block_num_Vect[k]) + (j * l) + m]);
						}
					for (n = 0; n < j; n++) {
						if (block[n] == 0) continue;
						else if (block[n] == 1) parity += 1;
					}
					Alice_Send_Message.block_num_Vect.push_back((prevJ * Alice_Received_Message.block_num_Vect[k] / j) + l);
					parity = parity % 2;
					Alice_Send_Message.block_num_Parity_Vect.push_back(parity);
					block.clear();
					parity = 0;
				}
			}
			Alice_Send_Message.Iter = i;
			Alice_Send_Message.Pass = j;
			Alice_Received_Message = Cascade_Bob_Processing(Alice_Send_Message);
			Alice_Send_Message.block_num_Vect.clear();
			Alice_Send_Message.block_num_Parity_Vect.clear();

			cout << "--------------------------------Alice back " << endl;
			for (int k = 0; k < Alice_Received_Message.block_num_Vect.size(); k++) {
				cout << "P" << j << "[" << Alice_Received_Message.block_num_Vect[k] << "]" << " ";

				for (l = 0; l < Alice_Received_Message.Pass; l++) {
					cout << sifted_Alice[(Alice_Received_Message.Pass * Alice_Received_Message.block_num_Vect[k] + l)] << " ";
				}
			}

			cout << endl;
			for (int k = 0; k < Alice_Received_Message.block_num_Vect.size(); k++) {
				cout << Alice_Received_Message.block_num_Parity_Vect[k] << " ";
			}
			prevJ = j;
			cout << endl;
		}
		cout << endl;
	}
}
