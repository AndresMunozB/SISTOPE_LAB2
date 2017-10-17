#include "estructuras.h"

#ifndef _FUNCIONES_H
#define _FUNCIONES_H

Matriz* matriz_create(int n,int m);
void matriz_destroy(Matriz* matriz);
void matriz_show(Matriz *matriz);
void matriz_print(Matriz *matriz, FILE* archivo);
char letter_min_rand();
void matriz_fill(Matriz* matriz);
void string_upper(char* string);
Hebra** hebra_array_init(int hebras, int words, char* nameFile);
void hebra_destroy(Hebra* hebra);    
void hebra_show(Hebra* hebra);
void hebra_array_destroy(Hebra** hebra_array);    
void hebra_array_show(Hebra** hebra_array);
void position_rand(Position* position, int row, int col); 
void position_show(Position pos);
void insert_word(Matriz* matriz, char* string,Position position);
int fileExists(char* nombreArchivo);    
int opt_get(int argc, char** argv,char ivalue[300],int* hvalue,int* cvalue,int* nvalue,int* mvalue,char svalue[300],int* dflag);
int verifyArguments(char* ivalue, int hvalue, int cvalue, int nvalue, int mvalue, char* svalue);



#endif
        