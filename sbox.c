/* 20170201 NaJiwoong */
/* 2020 April 19 */

/* Environment
	 
	 Ubuntu 16.04.12
	 gcc 5.4.0 */


/* Execution

	 "make"
	  - make execution file, and output.txt
	 "make clean"
	  - clean executino file, and output.txt */

#include <stdio.h>
#include <stdlib.h>

/* Function for S4-box mapping */
int s4box(int input){
	if (input >= 64 || input < 0){	// Check validity of input
		return 16;										// Error case
	}
	
	int bits[2];
	bits[0] = ((input >> 4) & 2) + (input & 1);		// bits[0] is outer bits
	bits[1] = (input >> 1) & 0xF;									// bits[1] is inner bits
	
	int box[4][16] = {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15}
										,{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9}
										,{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4}
										,{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}};

	return (int)box[bits[0]][bits[1]];
}

/* Function for S5-box mapping */
int s5box(int input){
	if (input >= 64 || input < 0){	// Check validity of input
		return 16;										// Error case
	}
	
	int bits[2];
	bits[0] = ((input >> 4) & 2) + (input & 1);		// bits[0] is outer bits
	bits[1] = (input >> 1) & 0xF;									// bits[1] is inner bits
	
	int box[4][16] = {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9}
										,{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6}
										,{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14}
										,{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}};

	return (int)box[bits[0]][bits[1]];
}

/* Function for hamming distance */
int hamming(int a, int b){
	int ham = 0;
	int i;
	for (i=0; i<6; i++){
		ham += ((a >> i) & 1) == ((b >> i) & 1) ? 0 : 1;
	}
	return ham;
}

/* Function for binary printing */
char *tobinary(int x,int n){
	int i;
	char *b = malloc (sizeof (char)*n);
	for (i = 0; i < n; i++){
		b[i] = (x >> (n-1-i)) & 1 ? '1' : '0';
	}
	return b;
}





