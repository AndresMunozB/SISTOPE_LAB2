#include "estructuras.h"

#ifndef _FUNCIONES_H
#define _FUNCIONES_H

Matriz* matriz_create(int n,int m);
void matriz_destroy(Matriz* matriz);
void printMatriz(Matriz *matriz);
char randLetterMin();
void matriz_fill(Matriz* matriz);
void string_upper(char* string);
Hebra* hebra_init(int id,FILE* file,int words);
void hebra_show(Hebra* hebra);    
void hebra_destroy(Hebra* hebra);    
Hebra** hebra_array_init(int hebras, int words, char* nameFile);
void hebra_array_show(Hebra** hebra_array);
void hebra_array_destroy(Hebra** hebra_array);
Params* params_init(int rows,int cols,int hebras,int words,char* nameFile);
void params_destroy(Params* params);
void position_rand(Position* position, int row, int col);
int capacity_max(char* fila,int cols);    
int is_valid_string(int capacity_max,char*string);    
int is_valid_position(Matriz* matriz,char* string, Position position);
int inser_word(Matriz* matriz, char* string,Position position);    
    
    
    
#endif