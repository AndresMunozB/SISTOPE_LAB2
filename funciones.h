#include "estructuras.h"

#ifndef _FUNCIONES_H
#define _FUNCIONES_H

Matriz* matriz_create(int n,int m);
int can_write_row(Matriz* matriz,char* string, int row);    
void matriz_destroy(Matriz* matriz);
void matriz_show(Matriz *matriz);
char letter_min_rand();
void matriz_fill(Matriz* matriz);
void string_upper(char* string);

/*
 * Funcion rtrim
 * funcion que elimina todos los caracteres de espacio (" ") al final de un string
 * @param char* string, string a modificar
*/
void rtrim(char* string);    
Hebra** hebra_array_init(int hebras, int words, char* nameFile);
void hebra_destroy(Hebra* hebra);    
void hebra_show(Hebra* hebra);
void hebra_array_destroy(Hebra** hebra_array);    
void hebra_array_show(Hebra** hebra_array);
void position_rand(Position* position, int row, int col);   
int is_valid_position(Matriz* matriz,char* string, Position position);
void insert_word(Matriz* matriz, char* string,Position position);


Matriz* matriz_create2(int n,int m);    
List* list_init();
void list_add(List* list,Range range);
int list_find(List* list,Range range);
void list_remove(List* list,Range range);
int list_range_valid(List* list,Range range);    
Position position_create(int row,int col);
Range range_create(Position init, Position fin);  
Range range_rand(int row,int col);  
int range_valid(Range orig,Range new);
int range_cmp(Range r1,Range r2);
Position position_generate(Position init, char* string);
void position_Show(Position pos);    
Range range_generate(Position init, char* string);    
void range_show(Range range);
void list_show(List* list);    
int fileExists(char* nombreArchivo);
int verifyArguments(char* ivalue,int hvalue,int cvalue,int nvalue,int mvalue,char* svalue);

#endif
        