/**
 * @author  Pavel Ondračka <pavel.ondracka@gmail.com>
 * @version 1.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_helper.h"

#define ALLOC_CHUNK 100

#define MD5 1
#define C16 2
#define C32 4
#define XOR 8
#define HEX 16

/**
 * Reads input from file or stdin to array of chars
 *
 * @param input file
 * @param length of the array
 */
char* read_file(FILE* file, unsigned int *length){
   int c;
   unsigned int bufsize = 0;
   char *data = NULL;
   *length = 0;

   while((c = fgetc(file)) != EOF){
      if(*length + 2 > bufsize){
         bufsize += ALLOC_CHUNK;
         data = realloc(data, bufsize * sizeof(char));
      }
      data[*length] = c;
      (*length)++;
   }

   data = realloc(data, *length * sizeof(char));

   return data;  
}

/**
 * Parse input arguments
 *
 * @param number of input arguments
 * @param string array with input arguments
 * @param bitfield with types of hash to be calculated
 * @param file handle to input file
 */
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

/**
 * Calculates number of hashes from stdin or from files 
 *
 * Expected input ./gethash [-md5] [-c16] [-c32] [-xor] [-hex] [-f file]
 */
int main( int argc, char *argv[] )
{

   unsigned char hash = 0;
   FILE *file = stdin;

   parse_args(argc, argv, &hash, &file);

   unsigned int length;
   char *data = read_file(file, &length);
   

   printf("Length: %i bytes\n", length);

   if(hash & XOR){
      printf("XOR: ");
      if(hash & HEX)
         printf("0x%02x\n", xor_compute(data, length));
      else
         printf("%u\n", xor_compute(data, length));
   }

   if(hash & C16){
      printf("CRC-16: ");
      if(hash & HEX)
         printf("0x%04x\n", crc16_compute(data, length));
      else
         printf("%u\n", crc16_compute(data, length));
   }

   if(hash & C32){
      printf("CRC-32: ");
      if(hash & HEX)
         printf("0x%08x\n", crc32_compute(data, length));
      else
         printf("%u\n", crc32_compute(data, length));
   }

   if(hash & MD5){
      unsigned char result[16];
      md5_compute(data, length, result);

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
