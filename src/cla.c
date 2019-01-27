#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// EXAMPLE DATA STRUCTURE DESIGN AND LAYOUT FOR CLA
#define input_size 1024
#define block_size 8
//Do not touch these defines
#define digits (input_size+1)
#define bits digits*4
#define ngroups bits/block_size
#define nsections ngroups/block_size
#define nsupersections nsections/block_size

//Global definitions of the various arrays used in steps for easy access
int gi[bits] = {0};
int pi[bits] = {0};
int ci[bits] = {0};
int ggj[ngroups] = {0};
int gpj[ngroups] = {0};
int gcj[ngroups] = {0};
int sgk[nsections] = {0};
int spk[nsections] = {0};
int sck[nsections] = {0};
int ssgl[nsupersections] = {0} ;
int sspl[nsupersections] = {0} ;
int sscl[nsupersections] = {0} ;
int sumi[bits] = {0};
//Integer array of inputs in binary form
int bin1[bits];
int bin2[bits];
//Character array of inputs in hex form
char hex1[digits];
char hex2[digits];

void s1() {

}

/**
 * simple hex to binary conversion
 * @param hex: a single hex value in character form (0-F)
 * @param bin: an int array pointer at which to store the 4 calculated binary values
 */
void hexToBin(char hex, int* bin) {
	switch (hex) {
		case '0': *bin = 0; *(bin+1) = 0; *(bin+2) = 0; *(bin+3) = 0; break;
		case '1': *bin = 1; *(bin+1) = 0; *(bin+2) = 0; *(bin+3) = 0; break;
		case '2': *bin = 0; *(bin+1) = 1; *(bin+2) = 0; *(bin+3) = 0; break;
		case '3': *bin = 1; *(bin+1) = 1; *(bin+2) = 0; *(bin+3) = 0; break;
		case '4': *bin = 0; *(bin+1) = 0; *(bin+2) = 1; *(bin+3) = 0; break;
		case '5': *bin = 1; *(bin+1) = 0; *(bin+2) = 1; *(bin+3) = 0; break;
		case '6': *bin = 0; *(bin+1) = 1; *(bin+2) = 1; *(bin+3) = 0; break;
		case '7': *bin = 1; *(bin+1) = 1; *(bin+2) = 1; *(bin+3) = 0; break;
		case '8': *bin = 0; *(bin+1) = 0; *(bin+2) = 0; *(bin+3) = 1; break;
		case '9': *bin = 1; *(bin+1) = 0; *(bin+2) = 0; *(bin+3) = 1; break;
		case 'A': *bin = 0; *(bin+1) = 1; *(bin+2) = 0; *(bin+3) = 1; break;
		case 'B': *bin = 1; *(bin+1) = 1; *(bin+2) = 0; *(bin+3) = 1; break;
		case 'C': *bin = 0; *(bin+1) = 0; *(bin+2) = 1; *(bin+3) = 1; break;
		case 'D': *bin = 1; *(bin+1) = 0; *(bin+2) = 1; *(bin+3) = 1; break;
		case 'E': *bin = 0; *(bin+1) = 1; *(bin+2) = 1; *(bin+3) = 1; break;
		case 'F': *bin = 1; *(bin+1) = 1; *(bin+2) = 1; *(bin+3) = 1; break;
	}
}

void cla() {

}

void parseInput(char* fName) {
	scanf("%s", hex1);
	for (int i = 0; i < input_size; hexToBin(hex1[i],bin1+4*(input_size-i-1)), ++i);

	for (int i = 0; i < input_size*4; ++i) {
		printf("%d",bin1[i]);
	}
	puts("");

	scanf("%s", hex2);
	for (int i = 0; i < input_size; hexToBin(hex2[i],bin2+4*(input_size-i-1)), ++i);

	for (int i = 0; i < input_size*4; ++i) {
		printf("%d",bin2[i]);
	}
	puts("");
}

int main(int argc, char* argv) {
	parseInput(argv[0]);
	//cla();
}
