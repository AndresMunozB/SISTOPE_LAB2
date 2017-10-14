#ifndef _FUNCIONES_H
#define _FUNCIONES_H
#include "estructuras.h"
Matriz* matriz_create(int n,int m);
void matriz_destroy(Matriz* matriz);
void printMatriz(Matriz *matriz);
char randLetterMin();
void matriz_fill(Matriz* matriz);

#endif