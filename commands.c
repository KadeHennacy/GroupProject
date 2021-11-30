#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commands.h"


void memDump(void) {
	//print the array as hex values. Only do ones that aren't zero for readability
	for (int j = 0; j < 65536; j++) {
		if (mem[j] != 0) {
			printf("\nmem[%d]:%x", j, mem[j]);
		}
	}
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
		return 0;
	}
	//STBA s = 1111 0011 = F3 = 243
	if (is == 243) {
		mem[sp + os] = a % 256;
		return 0;
	}
	//STBA sf = 1111 0100 = F4 = 244
	if (is == 244) {
		mem[mem[sp + os]] = a % 256;
		return 0;
	}
	//STBA x = 1111 0101 = F5 = 245
	if (is == 245) {
		mem[os + x] = a % 256;
		return 0;
	}
	//STBA sx = 1111 0110 = F6 = 246
	if (is == 246) {
		mem[sp + os + x] = a % 256;
		return 0;
	}
	//STBA sfx = 1111 0111 = F7 = 247
	if (is == 247) {
		mem[mem[sp + os] + x] = a % 256;
		return 0;
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
		return 0;
	}
	//STBX s = 1111 1011 = FB = 251
	if (is == 251) {
		mem[sp + os] = x % 256;
		return 0;
	}
	//STBX sf = 1111 1100 = FC = 252
	if (is == 252) {
		mem[mem[sp + os]] = x % 256;
		return 0;
	}
	//STBX X = 1111 1101 = FD = 253
	if (is == 253) {
		mem[os + x] = x % 256;
		return 0;
	}
	//STBX sx = 1111 1110 = FE = 254
	if (is == 254) {
		mem[sp + os + x] = x % 256;
		return 0;
	}
	//STBX sfx = 1111 1111 = FF = 255
	if (is == 255) {
		mem[mem[sp + os] + x] = x % 256;
		return 0;
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
			printf("Enter Input: ");
			if (scanf("%d", &a) > 0) {
				printf("You entered %d\n", a);
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
		return 0;
	}
	//LDBA s = 1101 0011 = D3 = 211
	if (is == 211) {
		a = mem[sp + os] % 256;
		return 0;
	}
	//LDBA sf = 1101 0100 = D4 = 212
	if (is == 212) {
		a = mem[mem[sp + os]] % 256;
		return 0;
	}
	//LDBA x = 1101 0101 = D5 = 213
	if (is == 213) {
		a = mem[os + x] % 256;
		return 0;
	}
	//LDBA sx = 1101 0110 = D6 = 214
	if (is == 214) {
		a = mem[sp + os + x] % 256;
		return 0;
	}
	//LDBA sfx = 1101 0111 = D7 = 215
	if (is == 215) {
		a = mem[mem[sp + os] + x];
		return 0;
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
		return 0;
	}

	//LDBX s = 1101 1011 = DB = 219
	if (is == 219) {
		x = mem[sp + os] % 256;
		return 0;
	}

	//LDBX sf = 1101 1100 = DC = 220
	if (is == 220) {
		x = mem[mem[sp + os]] % 256;
		return 0;
	}

	//LDBX x = 1101 1101 = DD = 221
	if (is == 221) {
		x = mem[os + x] % 256;
		return 0;
	}

	//LDBX sx = 1101 1110 = DE = 222
	if (is == 222) {
		x = mem[sp + os + x] % 256;
		return 0;
	}
	//LDBX sfx = 1101 1111 = DF = 223 
	if (is == 223) {
		x = mem[mem[sp + os] + x] % 256;
		return 0;
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
	//BR i = 0001 0010 = 12 = 18
	if (is == 18) {
		pc = os - 1;
	}
	//BR x = 0001 0011 = 13 = 19
}
void LDWr() {
	//1100 raaa all

}
void STWr() {
	//1110 raaa all but i
}
void SUBSP() {
	//0101 1aaa all
}
void ADDSP() {
	//0101 0aaa all
}
//######Part 5######//
void ADDr() {
	//0110 raaa all
}
void SUBr() {
	//0111 raaa all
}
void ASLr() {
	//0000 1010
	//0000 1011
}
void ASRr() {
	//0000 1100
	//0000 1101
}
void DECI() {
	//0011 0aaa all but i
}
void STRO() {
	//0100 1aaa d,n,s,sf,x
}
//######Part 6######//
void BRLE() {
	//0001 0100
	//0001 0101
}
void BRLT() {
	//0001 0110
	//0001 0111
}
void BREQ() {
	//0001 1000
	//0001 1001
}
void BRNE() {
	//0001 1010
	//0001 1011
}
void BRGE() {
	//0001 1100
	//0001 1101
}
void BRGT() {
	//0001 1110
	//0001 1111
}
void BRV() {
	//0010 0000
	//0010 0001
}
void NOTr() {
	//0000 0110
	//0000 0111
}
void NEGr() {
	//0000 1000
	//0000 1001
}
void CPWr() {
	//1010 raaa all
}
void CPBr() {
	//1011 raaa all
}
//######Part 7######//
void CALL() {
	//0010 0100
	//0010 0101
}
void RET() {
	//0000 0001
}
//######Part 8######//
void MOVSPA() {
	//0000 0011
}
