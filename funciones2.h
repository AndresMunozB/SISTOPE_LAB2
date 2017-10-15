Matriz* matriz_create(int n,int m);
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
void hebra_show(Hebra* hebra);
void hebra_array_show(Hebra** hebra_array,int n);    
        