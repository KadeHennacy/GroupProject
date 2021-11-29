/*
* Kade Hennacy
* Kyria Blough
* November 13th, 2021
* CSCI 220
* Group Project
*
* Describe program here
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commands.h"
//an array of integers that simulates Pep/9 main memory
int mem[65536];
//index for loader traversing mem, program counter, stack pointer, instruction specifier, operand specifier, accumulator, index register
int i, pc, sp, is, os, a, x;

int main() {
	//load the machine language program from input.pepo into mem. Best practices would be to make a separate function for this loader, but I can't get a file to work as an arguament at all.
	i = 0;
	//variable to store a character. This is neccessary because the loader traverses one character at a time, but each integer in the file is two characters
	char ch;
	//This loader is based on the tutorial https://www.geeksforgeeks.org/basics-file-handling-c/
	//Declare the file pointer
	FILE* fPointer;
	//Open input.pepo using fopen. Must be in same directory as source code
	fPointer = fopen("input.pepo", "r");
	//Declare variable that the data will be read from
	char singleLine[150];

	//Check if file was accessed successfully
	if (fPointer == NULL) {
		printf("input.pepo failed to open");
	}
	else
	{
		printf("File opened. \n");
		//feof tests the end of file indicator, so loop while the file hasn't reached its end
		while (!feof(fPointer)) {
			//store first char in ch as its ascii value
			ch = getc(fPointer);
			//break if ch is z, the end of file sentinel
			if (ch == 122) {
				break;
			}
			//if the char is between 0 and 9...
			if (ch < 58 && ch > 47) {
				//subtract 48 so ch contains decimal value of input
				ch -= 48;
				//the value at the index i in memory will be 16 times the decimal value of the tens place of the hexidecimal input
				mem[i] = ch * 16;
			}
			//if the char is a letter A-F
			else if (ch < 71 && ch > 64) {
				//subtract 55 so ch contains decimal value of input
				ch -= 55;
				//the value at the index i in memory will be 16 times the decimal value of the tens place of the hexidecimal input
				mem[i] = ch * 16;
			}
			else {
				printf("Invalid input");
				break;
			}
			//////////// Do the same stuff for the second character//////////

			//store first char in ch as its ascii value
			ch = getc(fPointer);
			//break if ch is z, the end of file sentinel
			if (ch == 122) {
				break;
			}
			//if the char is between 0 and 9...
			if (ch < 58 && ch > 47) {
				//subtract 48 so ch contains decimal value of input
				ch -= 48;
				//add the decimal value of the ones place of the hexidecimal input to the value from the 16s place thats already at index i in mem
				mem[i] += ch;
			}
			//if the char is a letter A-F
			else if (ch < 71 && ch > 64) {
				//subtract 55 so ch contains decimal value of input
				ch -= 55;
				//add the decimal value of the ones place of the hexidecimal input to the value from the 16s place thats already at index i in mem
				mem[i] += ch;
			}
			else {
				printf("Invalid input");
				break;
			}
			//call getc again to advance the position indicator by one and skip the space between hex values
			getc(fPointer);
			//increment index
			i++;
		}
	}

	//Von Neuman Cycle
	//Initialize SP at FB8F
	sp = 64399;
	//Initialize PC at 0. Loop until it reaches the end, which is i because i is still the index of the last machine instruction that was loaded. Later will remove this once I uncomment the stop function so it just loops until stop returns 0***
	for (pc = 0; pc < i; pc++) {
		//fetch the next instruction and decode

		//instruction specifier is the byte at the program counter
		is = mem[pc];
		//operand specifier is the next 2 bytes. Convert them and store in os the decimal value.
		os = (mem[pc + 1] / 16) * 4096 + (mem[pc + 1] % 16) * 256 + (mem[pc + 2] / 16) * 16 + mem[pc + 2] % 16;
		//increment pc
		pc += 2;

		//execute instruction fetched

		//######part 2#######//

		//this represents STOP()
		if (is == 0) {
			//return 0; cant do mem dump if it actually stops. remember to uncomment.
		}
		//STBA i = 1111 0000 = F0 = 240 | STBA d = 1111 0001 = F1 = 241| STBX i = 1111 1000 = F8 = 248 | STBX d = 1111 1001 = F9 = 249
		if (is == 241 || is == 249) {
			STBr();
		}
		if (is == 240 || is == 248) {
			printf("Error. cannot STBr with immdediate addressing");
		}
		//LDBA i = 1101 0000 = D0 = 208 | LDBA d = 1101 0001 = D1 = 209 | LDBX i = 1101 1000 = D8 = 216 | LDBX d = 1101 1001 = D9 = 217
		if (is == 208 || is == 209 || is == 216 || is == 217) {
			LDBr();
		}

		//######part 3######//

		//DECO i = 0011 1000 = 56 = 38 | DECO d = 0011 1001 = 57 = 39 | DECO n = 0011 1010 = 58 = 3A | DECO s = 0011 1011 = 59 = 3B | DECO sf = 0011 1100 = 60 = 3C | DECO x = 0011 1101 = 61 = 3D | DECO sx = 0011 1110 = 62 = 3E | DECO sfx = 0011 1111 = 63 = 3F 
		if (is < 64 && is > 55) {
			DECO();
		}
	}
	memDump();
	return 0;
}