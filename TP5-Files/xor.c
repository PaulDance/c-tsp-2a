//
// Created by pauldance on 28/02/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const unsigned int BLOCK_SIZE = 1024;


void encode(const u_int8_t key, FILE* inFile, FILE* outFile) {
	unsigned char inChars[BLOCK_SIZE];
	unsigned char outChars[BLOCK_SIZE];
	unsigned int readLength;
	
	while ((readLength = fread(inChars, sizeof(char), BLOCK_SIZE, inFile))) {
		for (unsigned int i = 0; i < readLength; i++) {
			outChars[i] = key ^ inChars[i];
		}
		
		fwrite(outChars, sizeof(char), readLength, outFile);
	}
}


int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage: %s <key> <in-file> <out-file>\n"
						"\tkey: The key to use for XORing the input file. Must be included between 0 and 255.\n"
						"\tin-file: The file to read from and encode with the given key. If '-' then stdin is read.\n"
						"\tout-file: The file written to receive the encoded data. If '-' then stdout is used.\n",
				argv[0]);
		return EXIT_FAILURE;
	}
	else {
		const u_int8_t key = strtoul(argv[1], NULL, 0);
		FILE* inFile;
		FILE* outFile;
		
		if (key > 255) {
			fprintf(stderr, "Key should be an integer included between 0 and 255.\n");
			return EXIT_FAILURE;
		}
		
		if (strcmp(argv[2], "-") == 0) {
			inFile = stdin;
		}
		else {
			inFile = fopen(argv[2], "r");
			
			if (inFile == NULL) {
				fprintf(stderr, "Error when opening input file.\n");
				return EXIT_FAILURE;
			}
		}
		
		if (strcmp(argv[3], "-") == 0) {
			outFile = stdout;
		}
		else {
			outFile = fopen(argv[3], "w");
			
			if (outFile == NULL) {
				fprintf(stderr, "Error when opening output file.\n");
				return EXIT_FAILURE;
			}
		}
		
		encode(key, inFile, outFile);
		return EXIT_SUCCESS;
	}
}
