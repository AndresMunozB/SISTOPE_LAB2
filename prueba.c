#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "estructuras.h"
#include "funciones.h"
 
int main()
{
    char string[] = "hola como estas!";
    string_upper(string);   
    printf("%s\n",string);
    /*Hebra hebra;
    hebra.id = 1;
    hebra.position.row = 2;
    hebra.position.col = 3;
    hebra.words = (char**)malloc(sizeof(char*)*10);
    hebra.words[0] = (char*)malloc(sizeof(char)*4);
    hebra.words[0][0]='s';
    hebra.words[0][1]='o';
    hebra.words[0][2]='l';
    hebra.words[0][3]='\0';
    printf("%s\n",hebra.words[0]);
    printf("%d\n",hebra.id);
    printf("%d\n",hebra.position.row);
    printf("%d\n",hebra.position.col);*/
    
    Hebra* hebra = (Hebra*)hebra_init(1,"words.txt",3);
    //int i;
    printf("%s\n",hebra->words[2]);
    hebra_destroy(hebra);
    



    
    return 1;
}