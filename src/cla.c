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
unsigned int bin1[bits];
unsigned int bin2[bits];
//Character array of inputs in hex form
char hex1[digits];
char hex2[digits];

char hexAns[digits];

/**
 * simple hex to binary conversion
 * @param hex: a single hex value in character form (0-F)
 * @param bin: an int array pointer at which to store the 4 calculated binary values
 */
void hexToBin(char hex, unsigned int* bin) {
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

/**
 * simple binary to hex conversion
 * @param bin: an int array pointer at which the 4 calculated binary values are stored
 */
char binToHex(int* bin) {
	switch (*bin + 2**(bin+1) + 4**(bin+2) + 8**(bin+3)) {
	case 0: return '0'; break;
	case 1: return '1'; break;
	case 2: return '2'; break;
	case 3: return '3'; break;
	case 4: return '4'; break;
	case 5: return '5'; break;
	case 6: return '6'; break;
	case 7: return '7'; break;
	case 8: return '8'; break;
	case 9: return '9'; break;
	case 10: return 'A'; break;
	case 11: return 'B'; break;
	case 12: return 'C'; break;
	case 13: return 'D'; break;
	case 14: return 'E'; break;
	case 15: return 'F'; break;
	}
	return '0';
}

/**
 * step 1: calculate gi and pi
 */
void calc_gi_pi() {
	for (int i = 0; i < bits; ++i) {
		gi[i] = bin1[i] * bin2[i];
		pi[i] = (bin1[i] + bin2[i]) % 2;
	}
}

/**
 * step 2: calculate ggj and gpj
 */
void calc_ggj_gpj() {
	for (int i = 0; i < ngroups; ++i) {
		int r = block_size*i;
		ggj[i] = gi[r+7] +
				pi[r+7]*gi[r+6] +
				pi[r+7]*pi[r+6]*gi[r+5] +
				pi[r+7]*pi[r+6]*pi[r+5]*gi[r+4] +
				pi[r+7]*pi[r+6]*pi[r+5]*pi[r+4]*gi[r+3] +
				pi[r+7]*pi[r+6]*pi[r+5]*pi[r+4]*pi[r+3]*gi[r+2] +
				pi[r+7]*pi[r+6]*pi[r+5]*pi[r+4]*pi[r+3]*pi[r+2]*gi[r+1] +
				pi[r+7]*pi[r+6]*pi[r+5]*pi[r+4]*pi[r+3]*pi[r+2]*pi[r+1]*gi[r];
		gpj[i] = pi[r+7]*pi[r+6]*pi[r+5]*pi[r+4]*pi[r+3]*pi[r+2]*pi[r+1]*pi[r];
	}
}

/**
 * step 3: calculate sgk and spk
 */
void calc_sgk_spk() {
	for (int i = 0; i < nsections; ++i) {
		int r = block_size*i;
		sgk[i] = ggj[r+7] +
				gpj[r+7]*ggj[r+6] +
				gpj[r+7]*gpj[r+6]*ggj[r+5] +
				gpj[r+7]*gpj[r+6]*gpj[r+5]*ggj[r+4] +
				gpj[r+7]*gpj[r+6]*gpj[r+5]*gpj[r+4]*ggj[r+3] +
				gpj[r+7]*gpj[r+6]*gpj[r+5]*gpj[r+4]*gpj[r+3]*ggj[r+2] +
				gpj[r+7]*gpj[r+6]*gpj[r+5]*gpj[r+4]*gpj[r+3]*gpj[r+2]*ggj[r+1] +
				gpj[r+7]*gpj[r+6]*gpj[r+5]*gpj[r+4]*gpj[r+3]*gpj[r+2]*gpj[r+1]*ggj[r];
		spk[i] = gpj[r+7]*gpj[r+6]*gpj[r+5]*gpj[r+4]*gpj[r+3]*gpj[r+2]*gpj[r+1]*gpj[r];
	}
}

/**
 * step 4: calculate ssgl and sspl
 */
void calc_ssgl_sspl() {
	//TODO
	for (int i = 0; i < nsupersections; ++i) {
		int r = block_size*i;
		//ssgl[i] = ;
		//sspl[i] = ;
	}
}

/**
 * step 5: calculate sscl
 */
void calc_sscl() {
	//TODO
	for (int i = 0; i < nsupersections; ++i) {
		//sscl[i] = ;
	}
}
/**
 * step 6: calculate sck
 */
void calc_sck() {
	sck[0] = sgk[0];
	for (int i = 1; i < nsections; ++i) {
		sck[i] = sgk[i] + spk[i]*sck[i-1];
	}
}
/**
 * step 7: calculate gcj
 */
void calc_gcj() {
	gcj[0] = ggj[0];
	for (int i = 1; i < ngroups; ++i) {
		gcj[i] = ggj[i] + gpj[i]*gcj[i-1];
	}
}
/**
 * step 8: calculate ci
 */
void calc_ci() {
	ci[0] = gi[0];
	for (int i = 1; i < bits; ++i) {
		ci[i] = gi[i] + pi[i]*ci[i-1];
	}
}

/**
 * step 9: calculate sumi
 */
void calc_sumi() {
	//TODO: we don't have an ai or bi, so substitued with gi and pi for now
	sumi[0] = gi[0] ^ pi[0];
	for (int i = 1; i < bits; ++i) {
		sumi[i] = gi[i] ^ pi[i] ^ ci[i-1];
	}
}

/**
 * main cla routine; calls all of the different sub-steps in order
 */
void cla() {
	calc_gi_pi();
	calc_ggj_gpj();
	calc_sgk_spk();
	calc_ssgl_sspl();
	calc_sscl();
	calc_sck();
	calc_gcj();
	calc_ci();
	calc_sumi();
}

/**
 * convert the calculated sumi back into hex for final solution
 */
void convertAnswerToHex() {
	for (int i = 0; i < input_size; hexAns[i] = binToHex(sumi+4*(input_size-i-1)), ++i);
}

/**
 * parse the piped input, reading in two 1024 hex strings and converting them to 4096 byte arrays
 */
void parseInput() {
	//first hex string
	scanf("%s", hex1);
	for (int i = 0; i < input_size; hexToBin(hex1[i],bin1+4*(input_size-i-1)), ++i);
	//second hex string
	scanf("%s", hex2);
	for (int i = 0; i < input_size; hexToBin(hex2[i],bin2+4*(input_size-i-1)), ++i);
}

int main(void) {
	parseInput();
	cla();
	convertAnswerToHex();
}
