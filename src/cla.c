#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

//EXAMPLE DATA STRUCTURE DESIGN AND LAYOUT FOR CLA
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
//character array to store the final hex answer
char hexAns[digits];

/**
 * simple hex char to binary conversion
 * @param hex: a single hex value in character form (0-F)
 * @param bin: an int array pointer at which to store the 4 calculated binary values
 */
void hexToBin(char hex, unsigned int* bin) {
	int decimal = (9*!!(hex&64))+(hex&15);
	*bin = decimal&1;
	*(bin+1) = decimal>>1&1;
	*(bin+2) = decimal>>2&1;
	*(bin+3) = decimal>>3&1;
}

/**
 * simple binary to hex char conversion
 * @param bin: an int array pointer at which the 4 calculated binary values are stored
 */
char binToHex(int* bin) {
	int decimalVal = *bin + 2**(bin+1) + 4**(bin+2) + 8**(bin+3);
	return decimalVal < 10 ? decimalVal + '0' : 55+decimalVal;
}

/**
 * step 1: calculate gi and pi, using bin1 and bin2
 * gi is the generate function. It tells us if we generated a carry in the ith stage (occurs when a[i] and b[i] are both 1) for the current bit.
 * pi is the propagate function. It tells us if we propagated a carry in the ith stage for the current bit.
 */
void calc_gi_pi() {
	for (int i = 0; i < bits; ++i) {
		gi[i] = bin1[i] * bin2[i];
		pi[i] = (bin1[i] + bin2[i]); //% 2;
	}
}

/**
 * step 2: calculate ggj and gpj, using gi and pi
 * ggj is the generate function for the current 8-bit group.
 * gpj is the propagate function for the current 8-bit group.
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
 * step 3: calculate sgk and spk, using ggj and gpj
 * sgk is the generate function for the current 64-bit section.
 * spk is the propagate function for the current 64-bit section.
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
 * step 4: calculate ssgl and sspl, using sgk and spk
 * ssgl is the generate function for the current 512-bit super section.
 * sspl is the propagate function for the current 512-bit super section.
 */
void calc_ssgl_sspl() {
	for (int i = 0; i < nsupersections; ++i) {
		int r = block_size*i;
		ssgl[i] = sgk[r+7] +
				spk[r+7]*sgk[r+6] +
				spk[r+7]*spk[r+6]*sgk[r+5] +
				spk[r+7]*spk[r+6]*spk[r+5]*sgk[r+4] +
				spk[r+7]*spk[r+6]*spk[r+5]*spk[r+4]*sgk[r+3] +
				spk[r+7]*spk[r+6]*spk[r+5]*spk[r+4]*spk[r+3]*sgk[r+2] +
				spk[r+7]*spk[r+6]*spk[r+5]*spk[r+4]*spk[r+3]*spk[r+2]*sgk[r+1] +
				spk[r+7]*spk[r+6]*spk[r+5]*spk[r+4]*spk[r+3]*spk[r+2]*spk[r+1]*sgk[r];
		sspl[i] = spk[r+7]*spk[r+6]*spk[r+5]*spk[r+4]*spk[r+3]*spk[r+2]*spk[r+1]*spk[r];
	}
}

/**
 * step 5: calculate sscl, using ssgl and sspl, and 0 for ssc-1
 * sscl stores whether or not there is a carry bit for the current 512-bit super section.
 */
void calc_sscl() {
	sscl[0] = 0;
	for (int i = 1; i < nsupersections; ++i) {
		sscl[i] = ssgl[i] + sspl[i]*sscl[i-1];
	}
}
/**
 * step 6: calculate sck, using sgk and spk, as well as correct sscl
 * sck stores whether or not there is a carry bit for the current 64-bit section
 */
void calc_sck() {
	//TODO: this should be using sscl somewhere
	sck[0] = sgk[0];
	for (int i = 1; i < nsections; ++i) {
		sck[i] = sgk[i] + spk[i]*sck[i-1];
	}
}
/**
 * step 7: calculate gcj, using ggj and gpj, as well as correct sck
 * gcj stores whether or not there is a carry bit for the current 8-bit group
 */
void calc_gcj() {
	//TODO: this should be using sck somewhere
	gcj[0] = ggj[0];
	for (int i = 1; i < ngroups; ++i) {
		gcj[i] = ggj[i] + gpj[i]*gcj[i-1];
	}
}
/**
 * step 8: calculate ci, using gi and pi, as well as correct gcj
 * ci stores whether or not there is a carry bit for the current bit
 */
void calc_ci() {
	//TODO: this should be using gcj somewhere
	ci[0] = gi[0];
	for (int i = 1; i < bits; ++i) {
		ci[i] = gi[i] + pi[i]*ci[i-1];
	}
}

/**
 * step 9: calculate sumi
 * sumi stores the final sum for the current bit
 */
void calc_sumi() {
	sumi[0] = 0;
	for (int i = 1; i < bits; ++i) {
		sumi[i] = bin1[i] ^ bin2[i] ^ ci[i-1];
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
	printf("0%s\n",hexAns);
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
