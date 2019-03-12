#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct letter_frequency {
	char l;
	float f;
} LF;

int main() {
	char letter_freq[] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'U', 'C', 'M', 'W', 'F', 'Y', 'G', 'P', 'B', 'V', 'K', 'X', 'J', 'Q', 'Z'};
	//char *cipher = "GFS WMY OG LGDVS MF SFNKYHOSU ESLLMRS, PC WS BFGW POL DMFRQMRS, PL OG CPFU M UPCCSKSFO HDMPFOSXO GC OIS LMES DMFRQMRS DGFR SFGQRI OG CPDD GFS LISSO GK LG, MFU OISF WS NGQFO OIS GNNQKKSFNSL GC SMNI DSOOSK. WS NMDD OIS EGLO CKSJQSFODY GNNQKKPFR DSOOSK OIS 'CPKLO', OIS FSXO EGLO GNNQKKPFR DSOOSK OIS 'LSNGFU' OIS CGDDGWPFR EGLO GNNQKKPFR DSOOSK OIS 'OIPKU', MFU LG GF, QFOPD WS MNNGQFO CGK MDD OIS UPCCSKSFO DSOOSKL PF OIS HDMPFOSXO LMEHDS. OISF WS DGGB MO OIS NPHISK OSXO WS WMFO OG LGDVS MFU WS MDLG NDMLLPCY POL LYEAGDL. WS CPFU OIS EGLO GNNQKKPFR LYEAGD MFU NIMFRS PO OG OIS CGKE GC OIS 'CPKLO' DSOOSK GC OIS HDMPFOSXO LMEHDS, OIS FSXO EGLO NGEEGF LYEAGD PL NIMFRSU OG OIS CGKE GC OIS 'LSNGFU' DSOOSK, MFU OIS CGDDGWPFR EGLO NGEEGF LYEAGD PL NIMFRSU OG OIS CGKE GC OIS 'OIPKU' DSOOSK, MFU LG GF, QFOPD WS MNNGQFO CGK MDD OIS CGKE GC OIS 'OIPKU' DSOOSK, MFU LG GF, QFOPD WS MNNGQFO CGK MDD LYEAGDL GC OIS NKYHOGRKME WS WMFO OG LGDVS.";

	char *cipher = "GS WMY OG LGVDS MF SFNKYHOSU ESLLMRS, PC WS BFGW POL DMFRQMRS, PL OG CPFU M UPCCSKSFO HDMPFOSXO GC OIS LMES DMFRQMRS DGFR SFGQRI OG CPDD GFS LISSO GK LG, MFU OISF WS NGQFO OIS GNNQKKSFNSL GC SMNI DSOOSK WS NMDD OIS EGLO CKSJQSFODY GNNQKKPFR DSOOSK OIS 'CPKLO' OIS FSXO EGLO GNNQKKPFR DSOOSK OIS 'LSNGFU' OIS CGDDGWPFR EGLO GNNQKKPFR DSOOSK OIS 'OIPKU', MFU LG GF, QFOPD WS MNNGQFO CGK MDD OIS UPCCSKSFO DSOOSKL PF OIS HDMPFOSXO LMEHDS. OISF WS DGGB MO OIS NPHISK OSXO WS WMFO OG LGDVS MFU WS MDLG NDMLLPCY POL LYEAGDL. WS CPFU OIS EGLO GNNQKKPFR LMEHDS, OIS FSXO EGLO NGEEGF LYEAGD PL NUMFRSU OG OIS CGKE GC OIS OIS CGKE GC OIS 'OIPKU' DSOOSK, MFU LG GF, QFOPD WS MNNGQFO CGK MDD LYEAGDL GC OIS NKYHOGRKME WS WMFO OG LGDVS.";
	char *plntxt = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ";

	// array of frequencies of each letter
	LF freq[26] = { { .l='A', .f=0 }, { .l='B', .f=0 }, { .l='C', .f=0 }, { .l='D', .f=0 }, { .l='E', .f=0 }, { .l='F', .f=0 }, { .l='G', .f=0 }, { .l='H', .f=0 }, { .l='I', .f=0 }, { .l='J', .f=0 }, { .l='K', .f=0 }, { .l='L', .f=0 }, { .l='M', .f=0 }, { .l='N', .f=0 }, { .l='O', .f=0 }, { .l='P', .f=0 }, { .l='Q', .f=0 }, { .l='R', .f=0 }, { .l='S', .f=0 }, { .l='T', .f=0 }, { .l='U', .f=0 }, { .l='V', .f=0 }, { .l='W', .f=0 }, { .l='X', .f=0 }, { .l='Y', .f=0 }, { .l='Z', .f=0 } };


	for(int i = 0; i < strlen(cipher); i++) {
		//increment frequency count for each letter
		freq[(int)cipher[i] - 65]++;
	}

	for(int i = 0; i < 26; i++) {
		//printf("%c: %d\n", (char)(i+65), freq[i]);
		printf("%c: %2.2f\n", (char)(i+65), 100 * (float)freq[i] / strlen(cipher));
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

	printf("a: %d z: %d\n", (int)'A', (int)'Z');

	return 0;
}
