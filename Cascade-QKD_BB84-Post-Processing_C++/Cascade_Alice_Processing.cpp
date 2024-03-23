#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Cascade_Alice_Processing.h"
#include "Cascade_Alice.h"
#include "Cascade_Bob_Processing.h"
#include "message_Struct.cpp"
using namespace std;

void Cascade_Alice_Processing() {
	cout << "Alice Processing" << endl;

	message_Struct Alice_Parity_Message;
	Alice_Parity_Message.Iter = 0;
	Alice_Parity_Message.Pass = 0;
	Alice_Parity_Message.block_num_Vect;

	vector<int> block;

	int i,j,k,l,parity = 0;
	for (i = 4; i <= sifted_Alice.size(); i *= 2) {

		for (j = i; j >= 1; j = j/2) {

			for (k = 0; k < (sifted_Alice.size()/j); k++) {
				for (l = 0; l < j; l++) {
					block.push_back(sifted_Alice[(j * k) + l]);
				}
				for (l = 0; l < j; l++) {
					if (block[l] == 0) continue;
					else if(block[l] == 1) parity += 1;
				}
				parity = parity % 2;
				block.clear();
				Alice_Parity_Message.block_num_Vect.push_back(k);
				Alice_Parity_Message.block_num_Parity_Vect.push_back(parity);
				parity = 0;
			}
			Alice_Parity_Message.Iter = i;
			Alice_Parity_Message.Pass = j;
			Cascade_Bob_Processing(Alice_Parity_Message);
			Alice_Parity_Message.block_num_Vect.clear();
			Alice_Parity_Message.block_num_Parity_Vect.clear();
			cout << endl;
		}
		cout << endl;

		if (i == 8) break;
	}
}
