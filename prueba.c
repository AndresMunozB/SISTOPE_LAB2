#include <stdio.h>
#include <ctype.h>
#include "funciones.h"
 
int main()
{
    char string[] = "hola como estas!";
    string_upper(string);
    printf("%s\n",string);
    return 1;
}