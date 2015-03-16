/**
 * @author  Pavel Ondračka <pavel.ondracka@gmail.com>
 * @version 1.0
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define MAXINPUT 1000
#define PI 3.14159265

/**
 * Multiplies vector with 3 components with 3x3 matrix
 *
 * @param input vector
 * @param result vector
 * @param input matrix,
 */
void vec3_mat3x3_mult(double *vec1, double *vec2, double *mat){
   for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
         vec2[i] += mat[3 * i + j] * vec1[j];
      }
   }
}

/**
 * Translate input vector by selected offset
 *
 * @param input vector
 * @param result vector
 * @param x offset
 * @param y offset
 */
void translate(double *vec1, double *vec2, double offset_x, double offset_y){
   double mat[9] = {1.0, 0.0, offset_x,
                    0.0, 1.0, offset_y,
                    0.0, 0.0, 1.0};
   vec3_mat3x3_mult(vec1, vec2, mat);
}

/**
 * Rotate input vector by selected angle (in degrees)
 *
 * @param input vector
 * @param result vector
 * @param angle
 */
void rotate(double *vec1, double *vec2, double angle){
   double mat[9] = {cos(angle), -sin(angle), 0.0,
                    sin(angle), cos(angle), 0.0,
                    0.0, 0.0, 1.0};
   vec3_mat3x3_mult(vec1, vec2, mat);
}

/**
 * Multiply input vector by selected scale
 *
 * @param input vector
 * @param result vector
 * @param x scale
 * @param y scale
 */
void scale(double *vec1, double *vec2, double scale_x, double scale_y){
   double mat[9] = {scale_x, 0.0, 0.0,
                    0.0, scale_y, 0.0,
                    0.0, 0.0, 1.0};
   vec3_mat3x3_mult(vec1, vec2, mat);
}

/**
 * Read standard input until EOF or newline is reached
 *
 * Input is stored in a zero terminated string, max lenght of
 * input is defined by MAXINPUT. Terminatin newline is not stored.
 *
 * @param strint for storage of input
 */
void read_input(char *str){
   int i = 0;
   while((str[i] = getchar()) != EOF){
      if(str[i] == '\n'){
         break;
      }
      if(i == (MAXINPUT - 2)){
         printf("input too long!\n");
         exit(4);
      }
      i++;
   }
   /* we want a zero terminated char */
   str[i] = 0;
}

/**
 * Read next floating point number from string previously passed to strtok
 *
 * This is basically a wrapper for strtod function plus some
 * additional cripling to disallow some formats normally that
 * are normally being accepted, but are disallowed in this
 * exercise such as 1e5, +5.0 etc.
 */
double parse_number(){
   char *str;
   if((str = strtok(NULL, " ")) == NULL){
      printf("chybny format!");
      exit(2);
   }

   /* check validity of format */
   char have_dot = 0;
   size_t l = strlen(str);
   for(size_t i = 0; i < l; i++){
      if(str[i] >= '0' && str[i] <= '9')
         continue;
      if(i == 0 && str[i] == '-')
         continue;
      if(i > 0 && i < l - 1 && str[i] == '.' && !have_dot++)
         continue;
      printf("chybny argument!");
      exit(3);
   }

   return strtod(str, NULL);
}

/**
 * Calculates some basic tranformation of 2D vectors
 *
 * Reads transformation type, input vector and transfomration
 * parameters from standard input and prints the resulting vector.
 *
 * Expected syntax:
 * <transformation shortcut> <input vector> <transformation parameters>
 */
int main(){

   char input[MAXINPUT];
   read_input(input);

   char *str;
   str = strtok(input, " ");

   enum transforms {t, r, s} trans_type;

   if(strcmp(str, "t") == 0)
      trans_type = t;
   else if(strcmp(str, "r") == 0)
      trans_type = r;
   else if(strcmp(str, "s") == 0)
      trans_type = s;
   else{
      printf("neznama transformace!");
      return 1;
   }

   double r1[3], r2[3] = {0};
   r1[0] = parse_number();
   r1[1] = parse_number();
   r1[2] = 1.0;

   double arg1 = parse_number(), arg2;
   if(trans_type != r)
      arg2 = parse_number();

   switch(trans_type){
      case(t):
         translate(r1, r2, arg1, arg2);
         break;
      case(r):
         rotate(r1, r2, arg1 * PI / 180.0);
         break;
      case(s):
         scale(r1, r2, arg1, arg2);
         break;
   }

   if((strtok(NULL, " ")) != NULL){
      printf("chybny format!");
      return 2;
   }

   printf("[%.2f, %.2f]\n", r2[0], r2[1]);

   return 0;
}
