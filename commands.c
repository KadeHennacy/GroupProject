#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commands.h"


void memDump(void) {
	//print the array as hex values. Only do ones that aren't zero for readability
	printf("\n\nMEMORY DUMP:\n");
	for (int j = 0; j < 65536; j++) {
		if (mem[j] != 0) {
			printf("\nmem[%d]:%x", j, mem[j]);
		}
	}
	printf("\n\nN: %d, Z: %d, V: %d, C: %d\n", n, z, v, c);
}

//######part 2######//

void STBr() {
	//STBA d = 1111 0001 = F1 = 241
	if (is == 241) {
		//fc16 is output device
		if (os == 64534) printf("%c", a % 256);
		else mem[os] = a % 256;
	}
	//STBA n = 1111 0010 = F2 = 242
	if (is == 242) {
		mem[mem[os]] = a % 256;  //256 since could be a word
	}
	//STBA s = 1111 0011 = F3 = 243
	if (is == 243) {
		if (os > 32767) {
			mem[sp + os - 65536] = a % 256;
		}
		else mem[sp + os] = a % 256;
	}
	//STBA sf = 1111 0100 = F4 = 244
	if (is == 244) {
		mem[mem[sp + os]] = a % 256;
	}
	//STBA x = 1111 0101 = F5 = 245
	if (is == 245) {
		mem[os + x] = a % 256;
	}
	//STBA sx = 1111 0110 = F6 = 246
	if (is == 246) {
		mem[sp + os + x] = a % 256;
	}
	//STBA sfx = 1111 0111 = F7 = 247
	if (is == 247) {
		mem[mem[sp + os] + x] = a % 256;
	}
	
	//STBX d = 1111 1001 = F9 = 249
	if (is == 249) {
		if (os == 64534) {
			printf("%c", x % 256);
		}
		else mem[os] = x % 256;
	}
	
	//STBX n = 1111 1010 = FA = 250
	if (is == 250) {
		mem[mem[os]] = x % 256;
	}
	//STBX s = 1111 1011 = FB = 251
	if (is == 251) {
		mem[sp + os] = x % 256;
	}
	//STBX sf = 1111 1100 = FC = 252
	if (is == 252) {
		mem[mem[sp + os]] = x % 256;
	}
	//STBX X = 1111 1101 = FD = 253
	if (is == 253) {
		mem[os + x] = x % 256;
	}
	//STBX sx = 1111 1110 = FE = 254
	if (is == 254) {
		mem[sp + os + x] = x % 256;
	}
	//STBX sfx = 1111 1111 = FF = 255
	if (is == 255) {
		mem[mem[sp + os] + x] = x % 256;
	}
	
}
void LDBr() {
	//LDBA i = 1101 0000 = D0 = 208
	if (is == 208) {
		//only rightmost byte
		a = os % 256;
	}
	//LDBA d = 1101 0001 = D1 = 209
	if (is == 209) {
		//fc15 is input device
		if (os == 64533) {


			//original input style, commented out for debugging
			//printf("Enter Input: ");
			//store as character
			if (scanf("%c", &a) > 0) {
				//printf("You entered %c\n", a);
				//ensure user doen't enter more than a byte
				a = a % 256;
			}
			else printf("You didn't enter anything.\n");



		}
		else a = mem[os] % 256;
	}
	//LDBA n = 1101 0010 = D2 = 210
	if (is == 210) {
		a = mem[mem[os]] % 256;
	}
	//LDBA s = 1101 0011 = D3 = 211
	if (is == 211) {
		a = mem[sp + os] % 256;
	}
	//LDBA sf = 1101 0100 = D4 = 212
	if (is == 212) {
		a = mem[mem[sp + os]] % 256;
	}
	//LDBA x = 1101 0101 = D5 = 213
	if (is == 213) {
		a = mem[os + x] % 256;
	}
	//LDBA sx = 1101 0110 = D6 = 214
	if (is == 214) {
		a = mem[sp + os + x] % 256;
	}
	//LDBA sfx = 1101 0111 = D7 = 215
	if (is == 215) {
		a = mem[mem[sp + os] + x];
	}
	
	//LDBX i = 1101 1000 = D8 = 216
	if (is == 216) {
		x = os % 256;
	}

	//LDBX d = 1101 1001 = D9 = 217
	if (is == 217) {
		//fc15 is input device
		if (os == 64533) {
			printf("Enter Input: ");
			if (scanf("%d", &x) > 0) {
				printf("You entered %d\n", x);
				//ensure user doesn't enter more than a byte
				x = x % 256;
			}
			else printf("You didn't enter anything.\n");
		}
		else x = mem[os] % 256;
	}
	
	//LDBX n = 1101 1010 = DA = 218
	if (is == 218) {
		x = mem[mem[os]] % 256;
	}

	//LDBX s = 1101 1011 = DB = 219
	if (is == 219) {
		x = mem[sp + os] % 256;
	}

	//LDBX sf = 1101 1100 = DC = 220
	if (is == 220) {
		x = mem[mem[sp + os]] % 256;
	}

	//LDBX x = 1101 1101 = DD = 221
	if (is == 221) {
		x = mem[os + x] % 256;
	}

	//LDBX sx = 1101 1110 = DE = 222
	if (is == 222) {
		x = mem[sp + os + x] % 256;
	}
	//LDBX sfx = 1101 1111 = DF = 223 
	if (is == 223) {
		x = mem[mem[sp + os] + x] % 256;
	}
	 
}

//######part3######
void DECO() {
	//because deco outputs a word, convert 2 bytes from mem into one value
	int word = mem[os] * 256 + mem[os + 1];
	//DECO i = 0011 1000 = 38 = 56
	if (is == 56) {
		//if OS is negative
		if (os > 32767) {
			printf("%d", -65536 + os);
		}
		else printf("%d", os);
	}
	//DECO d = 0011 1001 = 39 = 57
	if (is == 57) {
		//if mem[os] is negative
		if (word > 32767) {
			printf("%d", -65536 + word);
		}
		else printf("%d", word);
	}
	//DECO n = 0011 1010 = 3A = 58
	if (is == 58) {
		//word = mem[mem[os - 1] * 256 + mem[os] - 1] * 256 + mem[mem[os - 1] * 256 + mem[os]]; doesn't work for most cases.
		word = mem[mem[os] * 256 + mem[os + 1]] * 256 + mem[mem[os] * 256 + mem[os + 1] + 1];
		if (word > 32767) {
			printf("%d", -65536 + word);
		}
		else printf("%d", word);
	}
	//DECO s = 0011 1011 = 3B = 59
	if (is == 59) {
		if (os > 32767) {
			printf("%d", mem[os - 65536 + sp] * 256 + mem[os - 65536 + sp + 1]);
		}
		else printf("%d", mem[os + sp] * 256 + mem[os + sp + 1]);
	}
	//DECO sf = 0011 1100 = 3C = 60
	if (is == 60) {
		//if()test
	}
	//DECO x = 0011 1101 = 3D = 61
	//DECO sx = 0011 1110 = 3E = 62
	//DECO sfx = 0011 1111 = 3F = 63 

}
//######Part 4######//
void BR() {
	//BR i = 0001 0010 = 12 = 18 tested, works
	if (is == 18) {
		pc = os - 1;
	}
	//BR x = 0001 0011 = 13 = 19 tested, works
	if (is == 19) {
		pc = mem[os + 1] -1 + x;
	}
}
void LDWr() {
	//1100 raaa all
	//at part 4 we need i, d, s
	//int word = mem[os] * 256 + mem[os + 1];
	//LDWA i = 1100 0000 = 192 tested, works
	if (is == 192) {
		a = os;
	}
	//LDWA d = 1100 0001 = 193
	if (is == 193) {
		if (os == 64533) {
			printf("Enter Input: ");
			//store as character
			if (scanf("%c", &a) > 0) {
				printf("You entered %c\n", a);
			}
			else printf("You didn't enter anything.\n");
		}
		else a = mem[os] * 256 + mem[os + 1];
	}
	//LDWA n tested, works
	if (is == 194) {
		a = mem[mem[os] * 256 + mem[os + 1]] * 256 + mem[mem[os] * 256 + mem[os + 1] + 1];
	}
	//LDWA s tested, works
	if (is == 195) {
		if (os > 32767) {
			a = mem[os - 65536 + sp] * 256 + mem[os - 65535 + sp];
		}
		else {
			a = mem[os + sp] * 256 + mem[os + sp + 1];
		}
		//handle status bits, copied from addr()
		if (a > 65535) {
			c = 1;
			a -= 65536;
			n = z = v = 0;
		}
		else if (a > 32767) {
			n = 1;
			z = c = v = 0;
		}
		else if (a == 0) {
			z = 1;
			n = c = v = 0;
		}
		else if (a <= -32768) {
			v = 1;
		}
	}

	//from ldbr, just to look at
	//LDBA n = 1101 0010 = D2 = 210
	if (is == 210) {
		a = mem[mem[os]] % 256;
	}
	//LDBA s = 1101 0011 = D3 = 211
	if (is == 211) {
		a = mem[sp + os] % 256;
	}
	//LDBA sf = 1101 0100 = D4 = 212
	if (is == 212) {
		a = mem[mem[sp + os]] % 256;
	}
	//LDBA x = 1101 0101 = D5 = 213
	if (is == 213) {
		a = mem[os + x] % 256;
	}
	//LDBA sx = 1101 0110 = D6 = 214
	if (is == 214) {
		a = mem[sp + os + x] % 256;
	}
	//LDBA sfx = 1101 0111 = D7 = 215
	if (is == 215) {
		a = mem[mem[sp + os] + x];
	}

	//LDBX i = 1101 1000 = D8 = 216
	if (is == 216) {
		x = os % 256;
	}

	//LDBX d = 1101 1001 = D9 = 217
	if (is == 217) {
		//fc15 is input device
		if (os == 64533) {
			printf("Enter Input: ");
			if (scanf("%d", &x) > 0) {
				printf("You entered %d\n", x);
				//ensure user doesn't enter more than a byte
				x = x % 256;
			}
			else printf("You didn't enter anything.\n");
		}
		else x = mem[os] % 256;
	}

	//LDBX n = 1101 1010 = DA = 218
	if (is == 218) {
		x = mem[mem[os]] % 256;
	}

	//LDBX s = 1101 1011 = DB = 219
	if (is == 219) {
		x = mem[sp + os] % 256;
	}

	//LDBX sf = 1101 1100 = DC = 220
	if (is == 220) {
		x = mem[mem[sp + os]] % 256;
	}

	//LDBX x = 1101 1101 = DD = 221
	if (is == 221) {
		x = mem[os + x] % 256;
	}

	//LDBX sx = 1101 1110 = DE = 222
	if (is == 222) {
		x = mem[sp + os + x] % 256;
	}
	//LDBX sfx = 1101 1111 = DF = 223 
	if (is == 223) {
		x = mem[mem[sp + os] + x] % 256;
	}
}
void STWr() {
	//1110 raaa all but i
	//same as stbr without the mod. Haven't tested cuz it should work since STBr works.
	//STWA d tested, works
	if (is == 225) {
		//stba will output the value of the byte in the word, stwa outputs the first byte. So divide it by 256.
		if (os == 64534) printf("%c", a);
		//+1 fixes off by 1 error
		else {
			mem[os] = a / 256;
			mem[os + 1] = a % 256;
		}
	}
	//STWA n tested, works
	if (is == 226) {
		mem[mem[os] * 256 + mem[os + 1]] = a / 256;
		mem[mem[os] * 256 + mem[os + 1] + 1] = a % 256;
	}
	//STWA s tested, works
	if (is == 227) {
		if (os > 32767) {
			mem[sp + os - 65536] = a / 256;
			mem[sp + os - 65535] = a % 256;
		}
		else {
			mem[sp + os] = a / 256;
			mem[sp + os + 1] = a % 256;
		}
	}
	//STWA sf
	if (is == 228) {
		mem[mem[sp + os]] = a;
	}
	//STWA x
	if (is == 229) {
		mem[os + x] = a;
	}
	//STWA sx
	if (is == 230) {
		mem[sp + os + x] = a;
	}
	//STWA sfx
	if (is == 231) {
		mem[mem[sp + os] + x] = a;
	}

	//STWX d
	if (is == 233) {
		if (os == 64534) {
			printf("%c", x);
		}
		else mem[os] = x;
	}

	//STWX n
	if (is == 234) {
		mem[mem[os]] = x;
	}
	//STWX s
	if (is == 235) {
		mem[sp + os] = x;
	}
	//STWX sf
	if (is == 236) {
		mem[mem[sp + os]] = x;
	}
	//STWX X
	if (is == 237) {
		mem[os + x] = x;
	}
	//STWX sx
	if (is == 238) {
		mem[sp + os + x] = x;
	}
	//STWX sfx
	if (is == 239) {
		mem[mem[sp + os] + x] = x;
	}
}
void SUBSP() {
	//0101 1aaa all
	if (is == 88) {
		sp = sp - os;
	}
	//SUBSP d = 0101 1001 = 89
	else if (is == 89) {
		sp = sp - mem[os];
	}
	//SUBSP n = 0101 1010 = 90
	else if (is == 90) {
		sp = sp - mem[mem[os]];
	}
	//SUBSP s = 0101 1011 = 91
	else if (is == 91) {
		sp = sp - mem[sp + os];
	}
	//SUBSP sf = 0101 1100 = 92
	else if (is == 92) {
		sp = sp - mem[mem[sp + os]];
	}
	//SUBSP x = 0101 1101 = 93
	else if (is == 93) {
		sp = sp - mem[os + x];
	}
	//SUBSP sx = 0101 1110 = 94
	else if (is == 94) {
		sp = sp - mem[sp + os + x];
	}
	//SUBSP sfx = 0101 0111 = 95
	else {
		sp = sp - mem[mem[sp + os] + x];
	}
}
void ADDSP() {
	//0101 0aaa all
	if (is == 80) {
		sp = sp + os;
	}
	//ADDSP d = 0101 0001 = 81
	else if (is == 81) {
		sp = sp + mem[os];
	}
	//ADDSP n = 0101 0010 = 82
	else if (is == 82) {
		sp = sp + mem[mem[os]];
	}
	//ADDSP s = 0101 0011 = 83
	else if (is == 83) {
		sp = sp + mem[sp + os];
	}
	//ADDSP sf = 0101 0100 = 84
	else if (is == 84) {
		sp = sp + mem[mem[sp + os]];
	}
	//ADDSP x = 0101 0101 = 85
	else if (is == 85) {
		sp = sp + mem[os + x];
	}
	//ADDSP sx = 0101 0110 = 86
	else if (is == 86) {
		sp = sp + mem[sp + os + x];
	}
	//ADDSP sfx = 0101 0111 = 87
	else {
		sp = sp + mem[mem[sp + os] + x];
	}
}
//######Part 5######//
void ADDr() {
	//0110 raaa all
	//ADDA immediate tesed, works
	if (is == 96) {
		a += os;
		if (a > 65535) {
			c = 1;
			a -= 65536;
			n = z = v = 0;
		}
		else if (a > 32767) {
			n = 1;
			z = c = v = 0;
		}
		else if (a == 0) {
			z = 1;
			n = c = v = 0;
		}
		else if (a <= -32768) {
			v = 1;
		}
		
	}
	//ADDA direct
	else if (is == 97) {
		//the +1 fixes the off by 1 that prevents it from outputting the same as PEP9. IDK if this fix will work for all cases yet.
		a += mem[os + 1];
	}
	//ADDA indirect
	else if (is == 98) {
		//this is the same exact code from DECO N. It appears to work.
		a += mem[mem[os] * 256 + mem[os + 1]] * 256 + mem[mem[os] * 256 + mem[os + 1] + 1];
	}
	//ADDA s
	else if (is == 99) {
		//tested, works
		if (os > 32767) {
			a += mem[os - 65536 + sp] * 256 + mem[os - 65536 + sp + 1];
		}
		else a += mem[os + sp] * 256 + mem[os + sp + 1];
	}
	//////havent tested the rest///////
	//ADDA sf
	else if (is == 100) {
		a += mem[mem[sp + os]];
	}
	//ADDA x 
	else if (is == 101) {
		a += mem[os + x];
	}
	//ADDA sx
	else if (is == 102) {
		a += mem[sp + os + x];
	}
	//ADDA sfx
	else if (is == 103) {
		a += mem[mem[sp + os] + x];
	}
	//ADDX immediate
	else if (is == 104) {
		x += os;
	}
	//ADDX direct
	else if (is == 105) {
		x += mem[os];
	}
	//ADDX n 
	else if (is == 106) {
		x += mem[mem[os]];
	}
	//ADDX s
	else if (is == 107) {
		x += mem[sp + os];
	}
	//ADDX sf
	else if (is == 108) {
		x += mem[mem[sp + os]];
	}
	//ADDX x
	else if (is == 109) {
		x += mem[os + x];
	}
	//ADDX sx
	else if (is == 110) {
		x += mem[sp + os + x];
	}
	//ADDX sfx
	else if (is == 111) {
		x += mem[mem[sp + os] + x];
	}
}

void SUBr() {
	//0111 raaa all
	//SUBA immediate
	if (is == 112) {
		a -= os;
	}
	//SUBA direct
	else if (is == 113) {
		a -= mem[os + 1];
	}
	//SUBA n
	else if (is == 114) {
		a -= mem[mem[os] * 256 + mem[os + 1]] * 256 + mem[mem[os] * 256 + mem[os + 1] + 1];
	}
	//SUBA s
	else if (is == 115) {
		if (os > 32767) {
			a += mem[os - 65536 + sp] * 256 + mem[os - 65536 + sp + 1];
		}
		else a += mem[os + sp] * 256 + mem[os + sp + 1];
	}

	////these ^ should work b/c same as addr. Havent tested rest./////
	
	//SUBA sf
	else if (is == 116) {
		a -= mem[mem[sp + os]];
	}
	//SUBA x 
	else if (is == 117) {
		a -= mem[os + x];
	}
	//SUBA sx
	else if (is == 118) {
		a -= mem[sp + os + x];
	}
	//SUBA sfx
	else if (is == 119) {
		a -= mem[mem[sp + os] + x];
	}

	//SUBX immediate
	else if (is == 120) {
		x -= os;
	}
	//SUBX direct
	else if (is == 121) { 
		x -= mem[os];
	}
	//SUBX n
	else if (is == 122) {
		x -= mem[mem[os]];
	}
	//SUBX s
	else if (is == 123) {
		x -= mem[sp + os];
	}
	//SUBX sf
	else if (is == 124) {
		x -= mem[mem[sp + os]];
	}
	//SUBX x
	else if (is == 125) {
		x -= mem[os + x];
	}
	//SUBX sx
	else if (is == 126) {
		x -= mem[sp + os + x];
	}
	//SUBX sfx
	else if (is == 127) {
		x -= mem[mem[sp + os] + x];
	}
}
void ASLr() {
	//0000 1010
	if (is = 10) {
		//perform an Arithmatic Shift Left on the value in the Accumulator
		a = a * 2;
	}
	//0000 1011
	else {
		// perform an ASL on the value in the Index Register
		x = x * 2;
	}
}
void ASRr() {
	//0000 1100
	if (is == 12) {
		//perform an Arithmetic Shift Right on the value in the Accumulator
		a /= 2;
	}
	//0000 1101
	else {
		//perform an ASR on the value in the Index Register
		x = x / 2;
	}
}
void DECI() {
	//0011 0aaa all but i
	//DECI d = 49, tested, works
	if (is == 49) {
		if (scanf("%d", &mem[os]) > 0) {
			printf("You entered %d\n", mem[os]);
			if (mem[os] < 0) {
				printf("N set to 1\n");
				n = 1;
				v = z = c = 0;
			}
			else if (mem[os] == 0) {
				printf("Z set to 1\n");
				z = 1;
				v = c = n = 0;
			}
			else if (mem[os] <= -32768 || mem[os] >= 32767) {
				printf("V set to 1\n");
				v = 1;
				c = n = z = 0;
			}
			//convert to word after setting bits so I don't have to convert it to decimal for each comparison
			mem[os + 1] = mem[os] % 256;
			mem[os] /= 256;
		}
		else printf("You didn't enter a decimal.\n");
	}
	//DECI n = 50
	if (is == 50) {
	}
	//DECI s = 51, tested, works
	if (is == 51) {
		if (os > 32767) {
			if (scanf("%d", &mem[sp + os - 65546]) > 0) {
				printf("You entered %d\n", mem[sp + os - 65546]);
				if (mem[sp + os - 65546] < 0) {
					printf("N set to 1\n");
					n = 1;
				}
				else if (mem[sp + os - 65546] == 0) {
					printf("Z set to 1\n");
					z = 1;
				}
				else if (mem[sp + os - 65546] <= -32768 || mem[sp + os - 65546] >= 32767) {
					printf("V set to 1\n");
					v = 1;
				}
				//convert to word
				mem[sp + os - 65545] = mem[sp + os - 65546] % 256;
				mem[sp + os - 65546] /= 256;
			}
		}
		else if (scanf("%d", &mem[sp + os]) > 0) {
			printf("You entered %d\n", mem[sp + os]);
			if (mem[sp + os] < 0) {
				printf("N set to 1\n");
				n = 1;
			}
			else if (mem[sp + os] == 0) {
				printf("Z set to 1\n");
				z = 1;
			}
			else if (mem[sp + os] <= -32768 || mem[sp + os] >= 32767) {
				printf("V set to 1\n");
				v = 1;
			}
			//convert to word
			mem[sp + os + 1] = mem[sp + os] % 256;
			mem[sp + os] /= 256;
		}
		else printf("You didn't enter anything.\n");
	}
	//DECI sf = 52
	if (is == 52) {
		if (scanf("%d", &x) > 0) {
			printf("You entered %d\n", x);
			//ensure user doesn't enter more than a byte
			x = x % 256;
		}
		else printf("You didn't enter anything.\n");
	}



	//from stwr
	//direct
	if (is == 225) {
		//stba will output the value of the byte in the word, stwa outputs the first byte. So divide it by 256.
		if (os == 64534) printf("%c", a);
		//+1 fixes off by 1 error
		else {
			mem[os] = a / 256;
			mem[os + 1] = a % 256;
		}
	}
	//STWA n tested, works
	if (is == 226) {
		mem[mem[os] * 256 + mem[os + 1]] = a / 256;
		mem[mem[os] * 256 + mem[os + 1] + 1] = a % 256;
	}
	//STWA s tested, works
	if (is == 227) {
		if (os > 32767) {
			mem[sp + os - 65536] = a / 256;
			mem[sp + os - 65535] = a % 256;
		}
		else {
			mem[sp + os] = a / 256;
			mem[sp + os + 1] = a % 256;
		}
	}


	//from deco, just to look at
	int word = mem[os] * 256 + mem[os + 1];
	//DECO i = 0011 1000 = 38 = 56
	if (is == 56) {
		//if OS is negative
		if (os > 32767) {
			printf("%d", -65536 + os);
		}
		else printf("%d", os);
	}
	//DECO d = 0011 1001 = 39 = 57
	if (is == 57) {
		//if mem[os] is negative
		if (word > 32767) {
			printf("%d", -65536 + word);
		}
		else printf("%d", word);
	}
	//DECO n = 0011 1010 = 3A = 58
	if (is == 58) {
		//word = mem[mem[os - 1] * 256 + mem[os] - 1] * 256 + mem[mem[os - 1] * 256 + mem[os]]; doesn't work for most cases.
		word = mem[mem[os] * 256 + mem[os + 1]] * 256 + mem[mem[os] * 256 + mem[os + 1] + 1];
		if (word > 32767) {
			printf("%d", -65536 + word);
		}
		else printf("%d", word);
	}
	//DECO s = 0011 1011 = 3B = 59
	if (is == 59) {
		if (os > 32767) {
			printf("%d", mem[os - 65536 + sp] * 256 + mem[os - 65536 + sp + 1]);
		}
		else printf("%d", mem[os + sp] * 256 + mem[os + sp + 1]);
	}
	//DECO sf = 0011 1100 = 3C = 60
	if (is == 60) {
		//if()test
	}
}
void STRO() {
	//0100 1aaa d,n,s,sf,x
	//stro d tested, works
	if (is == 73) {
		for(int k = os; mem[k] != 0; k++){
			printf("%c", mem[k]);
			//subtracting i wont be neccesary once I enable the stop function, but this will stop it trying to read characters as instructions after it should have stopped.
			//i--;
		}
	}
}
//######Part 6######//
void BRLE() {
	//0001 0100
	if (is == 20) { //immediate addressing
		if ( a > 0) {
			pc = os;
		}
	}
	//0001 0101
	else {		//indexed addresing
		if ( a > 0) {
			pc = mem[os + x];
		}
	}
}
void BRLT() {
	//0001 0110
	if (is == 22){
		if (n == 1) {
			pc = os - 1;
		}
	}
	// kyrias
	//if (is == 22) { //immedate 
	//	if ( a >= 0){
	//		pc = os;
	//	}
	//}
	////0001 0111
	//else { // is == 23, indexed
	//	if( a >= 0){ 
	//		pc = mem[os + x];
	//	}
	//}
}
void BREQ() {
	//0001 1000
	if (is == 24) {
		if (z == 1) {
			pc = os - 1;
		}
	}

	//kyrias
	//if (is == 24) { //immediate
	//	if (a != 0) {
	//		pc = os;
	//	}
	//}
	////0001 1001
	//else { //is == 25, indexed
	//	if (a != 0) {
	//		pc = mem[os + x];
	//	}
	//}
}
void BRNE() {
	//0001 1010
	if (is == 26) {
		if (z == 0) {
			pc = os - 1;
		}
	}
	//kyrias
	//if (is == 26) { //immediate
	//	if (a == 0) {
	//		pc = os;
	//	}
	//}
	////0001 1011
	//else { //is == 27, indexed
	//	if (a == 0) {
	//		pc = mem[os + x];
	//	}
	//}
}
void BRGE() {
	//0001 1100 tested, works
	if (is == 28) {
		if (n == 0) {
			pc = os - 1;
		}
	}
	//0001 1101
	else { // is == 29
		if (a < 0) {
			pc = mem[os + x];
		}
	}
}
void BRGT() {
	//0001 1110
	if (is == 30) {
		if (a >= 0) {
			pc = os;
		}
	}
	//0001 1111 stack relative
	else { //is == 31
		if (a <= 0) {
			pc = mem[os + x];
		}
	}
}
void BRV() {
	//0010 0000
	//0010 0001
}
void NOTr() {
	//0000 0110
	if (is = 6) {
		a = ~a;  //NOTA, flip the bits
	}
	//0000 0111
	else {
		x = ~x;  //NOTX
	}
}
void NEGr() {
	//0000 1000
	if (is = 8) {
		a = ~a + 1;  //NEGA, flip the bits in the accumulator and add 1
	}
	//0000 1001
	else {
		x = ~x + 1;  //NEGX, flip the bits in the index register and add 1
	}
}
void CPWr() {
	n = z = v = c = 0;
	//1010 raaa all
	//CPWA i = 160
	//testing, works
	if (is == 160) {
		if (a - os > 0) {
			c = 1;
		}
		if (a - os < 0) {
			n = 1;
		}
		if (a - os == 0) {
			z = 1;
			c = 1;
		}
		if (a == 32768 && os == 32768) {
			v = 1;
			n = 1;
		}
	}




	//kirias
	//int T;
	////1010 raaa all
	////CPWA i
	//if (is == 160) {
	//	T = a - os;
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWA d
	//else if (is == 161) {
	//	T = a - mem[os];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWA n
	//else if (is == 162) {
	//	T = a - mem[mem[os]];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWA s
	//else if (is == 163) {
	//	T = a - mem[sp + os];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWA sf
	//else if (is == 164) {
	//	T = a - mem[mem[sp + os]];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWA x
	//else if (is == 165){
	//	T = a - mem[os + x];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWA sx
	//else if (is == 166){
	//	T = a - mem[sp + os + x];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWA sfx
	//else if (is == 167){
	//	T = a - mem[mem[sp + os] + x];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}

	////CPWX i
	//if (is == 168) {
	//	T = x - os;
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWX d
	//else if (is == 169) {
	//	T = x - mem[os];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWX n
	//else if (is == 170) {
	//	T = x - mem[mem[os]];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWX s
	//else if (is == 171) {
	//	T = x - mem[sp + os];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWX sf
	//else if (is == 172) {
	//	T = x - mem[mem[sp + os]];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWX x
	//else if (is == 173) {
	//	T = x - mem[os + x];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWX sx
	//else if (is == 174) {
	//	T = x - mem[sp + os + x];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
	////CPWX sfx
	//else if (is == 175) {
	//	T = x - mem[mem[sp + os] + x];
	//	if (T < 0) {
	//		//n bit = 1
	//	}
	//	else if (T == 0) {
	//		//z bit = 1
	//	}
	//	//v bit = overflow 
	//	//c bit = carry
	//	//n bit = n ^ v
	//}
}
void CPBr() {
	//1011 raaa all ,  is >= 176 && is <= 191
	//cpbr i = 1011 0000
	//same as cpwr, but %256
	n = z = v = c = 0;
	if (is == 176) {
		if (a - (os % 256) > 0) {
			c = 1;
		}
		if (a - (os % 256) < 0) {
			n = 1;
		}
		if (a - (os % 256) == 0) {
			z = 1;
			c = 1;
		}
		if (a == 32768 && (os % 256) == 32768) {
			v = 1;
			n = 1;
		}
	}

	//cpwr i
	/*if (is == 160) {
		if (a - os > 0) {
			printf("C is set to 1\n");
			c = 1;
		}
		if (a - os < 0) {
			printf("N set to 1\n");
			n = 1;
		}
		if (a - os == 0) {
			printf("Z and C set to 1\n");
			z = 1;
			c = 1;
		}
		if (a == 32768 && os == 32768) {
			printf("V set to 1\n");
			v = 1;
			n = 1;
		}
	}*/
}
//######Part 7######//
void CALL() {
	//0010 0100
	if (is == 36) { //immediate
		sp -= 2;
		mem[sp] = pc;
		pc = os;
	}
	//0010 0101
	else { //is == 37, indexed
		sp -= 2;
		mem[sp] = pc;
		pc = mem[os + x];
	}
}
void RET() {
	//0000 0001
	pc = mem[sp];
	sp += 2;
}
//######Part 8######//
void MOVSPA() {
	//0000 0011
}
