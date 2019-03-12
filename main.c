#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct letter_frequency {
	char c;
	float f;
} LF;

int comp_letter_alph(const void *a_, const void *b_) {
	LF const *a = (LF const *)a_, *b = (LF const *)b_;
	return strncmp(&a->c, &a->c, 1);
}
int comp_letter_freq(const void *a_, const void *b_) {
	LF const *a = (LF const *)a_, *b = (LF const *)b_;
	return b->f - a->f;
}

int main() {
	char eng_letter_freq[] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'U', 'C', 'M', 'W', 'F', 'Y', 'G', 'P', 'B', 'V', 'K', 'X', 'J', 'Q', 'Z'};
	//char *cipher = "GFS WMY OG LGDVS MF SFNKYHOSU ESLLMRS, PC WS BFGW POL DMFRQMRS, PL OG CPFU M UPCCSKSFO HDMPFOSXO GC OIS LMES DMFRQMRS DGFR SFGQRI OG CPDD GFS LISSO GK LG, MFU OISF WS NGQFO OIS GNNQKKSFNSL GC SMNI DSOOSK. WS NMDD OIS EGLO CKSJQSFODY GNNQKKPFR DSOOSK OIS 'CPKLO', OIS FSXO EGLO GNNQKKPFR DSOOSK OIS 'LSNGFU' OIS CGDDGWPFR EGLO GNNQKKPFR DSOOSK OIS 'OIPKU', MFU LG GF, QFOPD WS MNNGQFO CGK MDD OIS UPCCSKSFO DSOOSKL PF OIS HDMPFOSXO LMEHDS. OISF WS DGGB MO OIS NPHISK OSXO WS WMFO OG LGDVS MFU WS MDLG NDMLLPCY POL LYEAGDL. WS CPFU OIS EGLO GNNQKKPFR LYEAGD MFU NIMFRS PO OG OIS CGKE GC OIS 'CPKLO' DSOOSK GC OIS HDMPFOSXO LMEHDS, OIS FSXO EGLO NGEEGF LYEAGD PL NIMFRSU OG OIS CGKE GC OIS 'LSNGFU' DSOOSK, MFU OIS CGDDGWPFR EGLO NGEEGF LYEAGD PL NIMFRSU OG OIS CGKE GC OIS 'OIPKU' DSOOSK, MFU LG GF, QFOPD WS MNNGQFO CGK MDD OIS CGKE GC OIS 'OIPKU' DSOOSK, MFU LG GF, QFOPD WS MNNGQFO CGK MDD LYEAGDL GC OIS NKYHOGRKME WS WMFO OG LGDVS.";

	//init cipher and plaintext
	char *cipher = "GS WMY OG LGVDS MF SFNKYHOSU ESLLMRS, PC WS BFGW POL DMFRQMRS, PL OG CPFU M UPCCSKSFO HDMPFOSXO GC OIS LMES DMFRQMRS DGFR SFGQRI OG CPDD GFS LISSO GK LG, MFU OISF WS NGQFO OIS GNNQKKSFNSL GC SMNI DSOOSK WS NMDD OIS EGLO CKSJQSFODY GNNQKKPFR DSOOSK OIS 'CPKLO' OIS FSXO EGLO GNNQKKPFR DSOOSK OIS 'LSNGFU' OIS CGDDGWPFR EGLO GNNQKKPFR DSOOSK OIS 'OIPKU', MFU LG GF, QFOPD WS MNNGQFO CGK MDD OIS UPCCSKSFO DSOOSKL PF OIS HDMPFOSXO LMEHDS. OISF WS DGGB MO OIS NPHISK OSXO WS WMFO OG LGDVS MFU WS MDLG NDMLLPCY POL LYEAGDL. WS CPFU OIS EGLO GNNQKKPFR LMEHDS, OIS FSXO EGLO NGEEGF LYEAGD PL NUMFRSU OG OIS CGKE GC OIS OIS CGKE GC OIS 'OIPKU' DSOOSK, MFU LG GF, QFOPD WS MNNGQFO CGK MDD LYEAGDL GC OIS NKYHOGRKME WS WMFO OG LGDVS.";
	char plntxt[strlen(cipher)];

	// array of frequencies of each letter
	LF freq[26] = { { .c='A', .f=0 }, { .c='B', .f=0 }, { .c='C', .f=0 }, { .c='D', .f=0 }, { .c='E', .f=0 }, { .c='F', .f=0 }, { .c='G', .f=0 }, { .c='H', .f=0 }, { .c='I', .f=0 }, { .c='J', .f=0 }, { .c='K', .f=0 }, { .c='L', .f=0 }, { .c='M', .f=0 }, { .c='N', .f=0 }, { .c='O', .f=0 }, { .c='P', .f=0 }, { .c='Q', .f=0 }, { .c='R', .f=0 }, { .c='S', .f=0 }, { .c='T', .f=0 }, { .c='U', .f=0 }, { .c='V', .f=0 }, { .c='W', .f=0 }, { .c='X', .f=0 }, { .c='Y', .f=0 }, { .c='Z', .f=0 } };


	for(int i = 0; i < strlen(cipher); i++) {
		//increment frequency count for each letter
		if(cipher[i] == ' ') continue;
		if((int)cipher[i] < 65 || (int)cipher[i] > 90) {
			plntxt[i] = cipher[i];
			continue;
		}
		freq[(int)cipher[i] - 65].f++;
	}

	for(int i = 0; i < 26; i++) {
		//printf("%c: %d\n", (char)(i+65), freq[i].f);
		printf("%c: %2.2f\n", freq[i].c, 100 * (float)freq[i].f / strlen(cipher));
	}

	qsort(&freq[0], 26, sizeof(LF), comp_letter_freq);
	printf("sorting....\n");

	for(int i = 0; i < 26; i++) {
		//printf("%c: %d\n", (char)(i+65), freq[i].f);
		printf("%c: %2.2f\n", freq[i].c, 100 * (float)freq[i].f / strlen(cipher));
	}

	for(int i = 0; i < strlen(cipher); i++) {
		if(cipher[i] == ' ') continue;
		if((int)cipher[i] < 65 || (int)cipher[i] > 90) {
			plntxt[i] = cipher[i];
			continue;
		}


		for(int j = 0; j < 26; j++) {
		}

	}

	return 0;
}
