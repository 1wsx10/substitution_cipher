#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct letter_frequency {
	char c;
	float f;
} LF;

typedef struct letter_substitution {
	char from;
	char to;
} LC;

//compare 'letter_substitution' alphabetically
int comp_letter_alph(const void *a_, const void *b_) {
	LF const *a = (LF const *)a_, *b = (LF const *)b_;
	return strncmp(&a->c, &a->c, 1);
}
//compare 'letter_substitution' by frequency
int comp_letter_freq(const void *a_, const void *b_) {
	LF const *a = (LF const *)a_, *b = (LF const *)b_;
	return b->f - a->f;
}

/** read a text file into a string on the heap
 * @param dest	address of ptr to string where dest is stored
 *				dest should be NULL, or previously malloc'd
 *				dest should be freed
 * @param dest_len	the length of dest, after it has been realloc'd
 * @param fname		the name of the file to read
 * @return success	0 on success, errno on anything else
 *					if error, no realloc is called; no free nessecary
 */
int read_textfile(char **dest_addr, size_t *dest_len, char *fname) {
	//set destval to the position pointed to by dest_addr
	char *destval = *dest_addr;
	//this is because the pointer changes when you use realloc

	FILE *file = fopen(fname, "r");
	if(!file) {
		//no such file or directory
		perror(fname);
		return errno;
	}

	size_t bufmax = 256;
	size_t buflen;
	do {
		char buf[bufmax];
		buflen = fread(buf, sizeof(*buf), bufmax, file);

		//realloc + 1, so that there is room for null byte added later
		destval = realloc(destval, *dest_len + buflen + 1);

		//copy buffer into dest
		strncpy(destval + *dest_len, buf, buflen);
		*dest_len += buflen;
	} while(buflen == bufmax);// buflen is 0 (or <= bufmax) at eof
	fclose(file);

	destval[*dest_len] = '\0';
	*dest_len += 1;

#if 0
	//test for off-by-ones
	printf("dest_len: %d\n", *dest_len);
	printf("strlen(dest): %d\n", strlen(destval));
#endif

	//re-set the address of destination, since it has probably been changed
	*dest_addr = destval;

	return 0;//success
}


/* must be <= 26 */
#define MAX_LETTERS 2

int main(int argc, char *argv[]) {
	char eng_letter_freq[] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'U', 'C', 'M', 'W', 'F', 'Y', 'G', 'P', 'B', 'V', 'K', 'X', 'J', 'Q', 'Z'};
	//char eng_letter_freq[] = {'E', 'A', 'R', 'N', 'S', 'T', 'S', 'H', 'R', 'D', 'L', 'U', 'C', 'M', 'W', 'F', 'Y', 'G', 'P', 'B', 'V', 'K', 'X', 'J', 'Q', 'Z'};

	// place where the ciphertext is stored
	char *cipher = NULL;
	size_t cipher_len = 0;
	char *fname = "./ciphertext";

	switch(argc) {
		case INT_MAX:
		case 3:
			//TODO 2nd arg is number of sunstitutions
		case 2:
			//first arg is the name of ciphertext file
			fname = argv[1];
			break;
	}

	printf("opening cipher \"%s\"\n", fname);
	int err;
	if((err = read_textfile(&cipher, &cipher_len, fname))) {
		return err;
	}

	//init plaintext (same size as cipher)
	char plntxt[cipher_len];

	// array of frequencies of each letter
	LF freq[26] = { { .c='A', .f=0 }, { .c='B', .f=0 }, { .c='C', .f=0 }, { .c='D', .f=0 }, { .c='E', .f=0 }, { .c='F', .f=0 }, { .c='G', .f=0 }, { .c='H', .f=0 }, { .c='I', .f=0 }, { .c='J', .f=0 }, { .c='K', .f=0 }, { .c='L', .f=0 }, { .c='M', .f=0 }, { .c='N', .f=0 }, { .c='O', .f=0 }, { .c='P', .f=0 }, { .c='Q', .f=0 }, { .c='R', .f=0 }, { .c='S', .f=0 }, { .c='T', .f=0 }, { .c='U', .f=0 }, { .c='V', .f=0 }, { .c='W', .f=0 }, { .c='X', .f=0 }, { .c='Y', .f=0 }, { .c='Z', .f=0 } };

	//LC subst[] = { };
	LC subst[] = { 
		{.from='G', .to='o'}, 
		{.from='F', .to='n'}, // for 'different'
		{.from='O', .to='t'}, // for 'different'
		{.from='I', .to='h'},
		{.from='P', .to='i'},// for 'different'
		{.from='L', .to='s'},
		{.from='M', .to='a'},// for 'and', 'a'
		{.from='U', .to='d'},// for 'and' 'different'
		{.from='C', .to='f'},// for 'if' 'different'
		{.from='K', .to='r'},// for 'first' 'different'
		{.from='D', .to='l'},
		{.from='X', .to='x'},
		{.from='N', .to='c'},
		{.from='Y', .to='y'},
		{.from='J', .to='q'},//frequently
		{.from='Q', .to='u'},//frequently
		{.from='H', .to='p'},
		{.from='H', .to='p'},
		{.from='W', .to='w'},//way
		{.from='R', .to='g'},//occurring
		{.from='B', .to='k'},
		{.from='E', .to='m'},//symbols
		{.from='A', .to='b'},//symbols
		{.from='V', .to='v'},
	};
	//LC subst[] = { { .from='C', .to='s' }, { .from='P', .to='u' }, { .from='I', .to='h' } };

	printf("counting frequencies...\n");
	//count the frequency of each letter
	for(int i = 0; i < cipher_len; i++) {
		//increment frequency count for each letter
		if(cipher[i] == ' ') continue;
		if((int)cipher[i] < 65 || (int)cipher[i] > 90) {
			plntxt[i] = cipher[i];
			continue;
		}
		freq[(int)cipher[i] - 65].f++;
	}

#if 0
	for(int i = 0; i < 26; i++) {
		//printf("%c: %d\n", (char)(i+65), freq[i].f);
		printf("%c: %2.2f\n", freq[i].c, 100 * (float)freq[i].f / strlen(cipher));
	}
#endif

	//sort the frequency count
	printf("sorting frequencies....\n");
	qsort(&freq[0], 26, sizeof(LF), comp_letter_freq);

	//print the frequencies, and which substitutions will happen
	for(int i = 0; i < 26; i++) {
		//printf("%c: %d\n", (char)(i+65), freq[i].f);
		if(i < MAX_LETTERS) {
			//    freq in text, char cipher, char plain
			printf("%2.2f: %c -> %c\n", 100 * (float)freq[i].f / strlen(cipher), freq[i].c, eng_letter_freq[i]+32);
		} else {
			printf("%2.2f: %c    %c\n", 100 * (float)freq[i].f / strlen(cipher), freq[i].c, eng_letter_freq[i]+32);
		}
	}

	for(int i = 0; i < strlen(cipher); i++) {
		//itterate the letters

		// just copy any non-alphabetic characters across
		if((int)cipher[i] < 65 || (int)cipher[i] > 90) {
			plntxt[i] = cipher[i];
			continue;
		}

		// replace only the most common letters
		int replaced = 0;
		for(int j = 0; j < MAX_LETTERS && j < 26; j++) {
			if(cipher[i] == freq[j].c) {
				replaced = 1;
				plntxt[i] = eng_letter_freq[j] + 32;
				break;
			}
		}

		//copy across the rest of the letters
		if(!replaced) {
			plntxt[i] = cipher[i];
			for(int j = 0; j < sizeof(subst) / sizeof(subst[0]); j++) {
				if(cipher[i] == subst[j].from) {
					plntxt[i] = subst[j].to;
					break;
				}
			}
		}

	}


	printf("================\n");
	printf("%s\n", plntxt);
	printf("================\n");

	free(cipher);

	return 0;
}
