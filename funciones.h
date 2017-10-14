#include "estructuras.h"

#ifndef _FUNCIONES_H
#define _FUNCIONES_H

Matriz* matriz_create(int n,int m);
void matriz_destroy(Matriz* matriz);
void printMatriz(Matriz *matriz);
char randLetterMin();
void matriz_fill(Matriz* matriz);
void string_upper(char* string);
Hebra* hebra_init(int id,char* nameFile,int words);
void hebra_destroy(Hebra* hebra);    
    
#endif