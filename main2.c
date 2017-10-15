#include <stdio.h>
#include "estructuras.h"
#include "funciones2.h"

int main(){
    Hebra** hebra_array = hebra_array_init(10,7,"words.txt");
    hebra_array_show(hebra_array,1);
    return 1;
}