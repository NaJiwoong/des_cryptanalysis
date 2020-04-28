/* 20170201 NaJiwoong */
/* 2020 April 28 */

/* Code for 
 * 
 * - s4-box XDT generation
 * - s5-box LDT generation
 */

/* Environment
	 
	 Ubuntu 16.04.12
	 gcc 5.4.0 */


/* Execution

	 "make"
	  - make output.txt
	 "make clean"
	  - clean execution file, and output.txt */


#include <stdio.h>
#include <stdlib.h>

#include "sbox.h"


// Function for generate s4-box xdt
short **
xdt_generate(void){
	int i;
	short **xdt = malloc(sizeof(short *) * 64);
	for (i = 0; i < 64; i++){
		xdt[i] = malloc(sizeof(short) * 16);
	}

	int x, xd, y, yd, delx, dely;
	for (x = 0; x < 64; x++){
		for (delx = 0; delx < 64; delx++){
			xd = x^delx;
			y = s4box(x);
			yd = s4box(xd);
			dely = y^yd;
			xdt[delx][dely]++;
		}
	}
	
	return xdt;
}

int equal_parity(int a, int b){
	int x, y;
	x = a ^ (a >> 1);
	x = x ^ (x >> 2);
	x = x ^ (x >> 4);
	x = x ^ (x >> 8);
	x = x ^ (x >> 16);
	x &= 1;
	y = b ^ (b >> 1);
	y = y ^ (y >> 2);
	y = y ^ (y >> 4);
	y = y ^ (y >> 8);
	y = y ^ (y >> 16);
	y &= 1;
	
	return (x == y);
}

// Function for generate s5-box ldt
short **
ldt_generate(void){
	int i;
	short **ldt = malloc(sizeof(short *) * 63);
	for (i = 0; i < 63; i++){
		ldt[i] = malloc(sizeof(short) * 15);
	}

	int a, b, x, y, ax, by;
	for (a = 0; a < 63; a++){
		for (b = 0; b < 15; b++){
			for (x = 0; x < 64; x++){
				y = s5box(x);
				ax = (a+1) & x;
				by = (b+1) & y;
				if (equal_parity(ax, by)){
					ldt[a][b]++;
				}
			}
		}
	}
	return ldt;
}


int main(void){
	FILE *fp;
	int i, j;
	short **xdt = xdt_generate();
	short **ldt = ldt_generate();

	fp = fopen("./output.txt", "wt");
	if (fp == NULL){
		printf("Error occured opening file\n");
		return -1;
	}
	
	fprintf(fp, "    < Result of s4-box XDT generation and s5-box LDT generation > \n\n\n");

	// String for XDT CASE
	fprintf(fp, "    < Result of XDT of S4-box > \n\n");
	fprintf(fp, "  input  |                                          Output XOR                                            \n");
	fprintf(fp, "   XOR   |  0x    1x    2x    3x    4x    5x    6x    7x    8x    9x    Ax    Bx    Cx    Dx    Ex    Fx  \n");
	fprintf(fp, "---------+------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < 64; i++){
		fprintf(fp, "   %02Xx   |", i);
		for (j = 0; j < 16; j++){
			fprintf(fp, "  %2d  ", xdt[i][j]);
		}
		fprintf(fp, "\n");
	}

	
	// String for LDT CASE
	fprintf(fp, "\n\n    < Result of LDT of S5-box > \n\n");
	fprintf(fp, "         |                                            beta                                          \n");
	fprintf(fp, "  alpha  |   1     2     3     4     5     6     7     8     9    10    11    12    13    14    15  \n");
	fprintf(fp, "---------+------------------------------------------------------------------------------------------\n");
	for (i = 0; i < 63; i++){
		fprintf(fp, "   %2d    |", i+1);
		for (j = 0; j < 15; j++){
			fprintf(fp, "  %2d  ", ldt[i][j]-32);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n\n   <END>");



	for (i = 0; i<64; i++){
		free(xdt[i]);
	}
	free(xdt);
	for (i = 0; i<63; i++){
		free(ldt[i]);
	}
	free(ldt);

	fclose(fp);

	return 0;
}



