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
int* bin1=NULL;
int* bin2=NULL;
//Character array of inputs in hex form
char* hex1=NULL;
char* hex2=NULL;

void s1() {

}

void cla() {

}

void parseInput(char* fName) {

}

int main(int argc, char* argv) {
	parseInput(argv[0]);

}
