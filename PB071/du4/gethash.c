#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_helper.h"

#define ALLOC_SIZE 50

#define MD5 1
#define C16 2
#define C32 4
#define XOR 8
#define HEX 16

char* read_file(FILE* file){
   char c;
   char *str = NULL;
   int length = 0, bufsize = 0;

   while((c = getc(file)) != EOF){
      if(length + 2 > bufsize){
         bufsize += ALLOC_SIZE;
         str = realloc(str, bufsize * sizeof(char));
      }
      str[length++] = c;
      str[length] = 0;
   }

   return str;  
}

void parse_args(int argc, char *argv[], unsigned char *hash, FILE **file){
   if(argc < 2){
      fprintf(stderr, "Error: at least one option needed\n");
      fprintf(stderr, "./gethash [-md5] [-c16] [-c32] [-xor] [-hex] [-f file]\n");
      exit(1);
   }

   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-md5") == 0) {
         *hash |= MD5;
      }
      else if (strcmp(argv[i], "-c16") == 0) {
         *hash |= C16;
      }
      else if (strcmp(argv[i], "-c32") == 0) {
         *hash |= C32;
      }
      else if (strcmp(argv[i], "-xor") == 0) {
         *hash |= XOR;
      }
      else if (strcmp(argv[i], "-hex") == 0) {
         *hash |= HEX;
      }
      else if (strcmp(argv[i], "-f") == 0) {
         if (i < argc - 1 && argv[i + 1][0] != '-' ){
            if((*file = fopen(argv[i + 1], "r")) == NULL){
               fprintf(stderr, "Error: unable to open file %s\n", argv[i+1]);
               exit(4);
            }
         }
         else{
            fprintf(stderr, "Error: -f option detected but no file name set\n");
            exit(2);
         }
         i++;
      }
      else {
         fprintf(stderr, "Error: unknown input option %s\n", argv[i]);
         exit(3);
      }
   }
}

int main( int argc, char *argv[] )
{

   unsigned char hash = 0;
   FILE *file = stdin;

   parse_args(argc, argv, &hash, &file);

   char *data = read_file(file);

   printf("Length: %lu bytes\n", strlen(data));

   if(hash & XOR){
      printf("XOR: ");
      if(hash & HEX)
         printf("0x%02x\n", xor_compute(data));
      else
         printf("%u\n", xor_compute(data));
   }

   if(hash & C16){
      printf("CRC-16: ");
      if(hash & HEX)
         printf("0x%04x\n", crc16_compute(data));
      else
         printf("%u\n", crc16_compute(data));
   }

   if(hash & C32){
      printf("CRC-32: ");
      if(hash & HEX)
         printf("0x%08x\n", crc32b(data));
      else
         printf("%u\n", crc32b(data));
   }

   if(hash & MD5){
      unsigned char result[16];
      md5_compute(data, result);

      printf("MD5: ");
      for (int i = 0; i < 16; i++){
         printf("%02x", result[i]);
      }
      printf("\n");
   }

   free(data);
   fclose(file);

   return 0;
}
