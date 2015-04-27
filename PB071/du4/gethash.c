#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_helper.h"

enum hash_type {md5, c16, c32, xor};

int main( int argc, char *argv[] )
{

	enum hash_type hash;
	unsigned char hex = 0;
	FILE *file = stdin;

	if(argc < 2){
		printf("Error: at least one option needed\n");
		printf("./gethash [-md5] [-c16] [-c32] [-xor] [-hex] [-f file]\n");
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-md5") == 0) {
			hash = md5;
		}
		else if (strcmp(argv[i], "-c16") == 0) {
			hash = c16;
		}
		else if (strcmp(argv[i], "-c32") == 0) {
			hash = c32;
		}
		else if (strcmp(argv[i], "-xor") == 0) {
			hash = xor;
		}
		else if (strcmp(argv[i], "-hex") == 0) {
			hex = 1;
		}
		else if (strcmp(argv[i], "-f") == 0) {
			if (i < argc - 1 && argv[i + 1][0] != '-' ){
				if((file = fopen(argv[i + 1], "r")) == NULL){
					printf("Error: unable to open file %s\n", argv[i+1]);
					return 4;
				}
			}
			else{
				printf("Error: -f option detected but no file name set\n");
				return 2;
			}
			i++;
		}
		else {
			printf("Error: unknown input option %s\n", argv[i]);
			return 3;
		}
	}

	return 0;
}
