#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include "estructuras.h"
#include "funciones.h"

//ENTRADA: Enteros n y m, que representan las filas y columnas respectivamente
//SALIDA: Puntero a la estructura Matriz
//Esta función se encarga de crear una nueva matriz e inicializar cada posicion con caracter espacio.
Matriz* matriz_create(int n,int m){
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->row = n;
    matriz->col = m;
    matriz->data = (char**) malloc (sizeof(char*)*n);
    matriz->locks = (pthread_mutex_t**) malloc (sizeof(pthread_mutex_t*)*n);
    int i,j;
    for(i=0;i<n;i++){
        matriz->data[i] = (char*) malloc (sizeof(char)*m);
        matriz->locks[i] = (pthread_mutex_t*) malloc (sizeof(pthread_mutex_t)*m);
        for(j=0;j<m;j++){
            matriz->data[i][j] = ' ';
            pthread_mutex_init(& matriz->locks[i][j], NULL);
        }
    }
    return matriz;
}

//ENTRADA: Puntero a la estructura Matriz
//SALIDA: Void (Nada)
//Función se encarga de liberar la memoria utilizada por la matriz.
void matriz_destroy(Matriz* matriz){
    int i;  
    for(i=0;i<matriz->row;i++){
        free(matriz->data[i]);
        free( matriz->locks[i]);
    }
    free(matriz->data);
    free(matriz);
}

//ENTRADA: Puntero a la estructura Matriz
//SALIDA: Void (Nada)
//Función al cual le corresponde mostrar los datos de la matriz por consola
void matriz_show(Matriz *matriz){
    int i,j;
    for (i=0;i<matriz->row;i++){
        for(j=0;j<matriz->col;j++){
            printf("|%c",matriz->data[i][j]);
        }
        printf("\n");
    }
}

//ENTRADA: Puntero a la estructura Matriz y puntero a archivo
//SALIDA: Void (Nada)
//Función al cual le corresponde mostrar los datos de la matriz en un fichero de salida
void matriz_print(Matriz *matriz, FILE* archivo){
    int i,j;
    for (i=0;i<matriz->row;i++){
        for(j=0;j<matriz->col;j++){
            fprintf(archivo,"%c",matriz->data[i][j]);
        }
        fprintf(archivo,"\n");
    }
}

//ENTRADA: Void (nada)
//SALIDA: Caracter
//Entrega una letra minuscula aleatoriamente.
char letter_min_rand(){
    char random;
    random = rand()%26;
    random+=97;
    return random;
}

//ENTRADA: Puntero a la estructura Matriz
//SALIDA: Void (Nada)
//Función que se encarga del llenado de los espacios restantes de la matriz con letras aleatorias. 
void matriz_fill(Matriz* matriz){
    int i,j;
    char buffer;
    srand(time(NULL)); 
    for (i=0;i<matriz->row;i++){
        for(j=0;j<matriz->col;j++){
            if(matriz->data[i][j]==' '){
                buffer = letter_min_rand();
                matriz->data[i][j] = buffer;
            }
        }
    }
}

//ENTRADA: Puntero a un caracter (string)
//SALIDA: Void (Nada)
//Realiza la transformación de un string que contiene letras en minuscula a letras mayusculas
void string_upper(char* string){
    int i;
    for(i=0;i<strlen(string);i++){
        string[i]=toupper(string[i]);
    }
}

//ENTRADA: 2 enteros que corresponden a la cantidad de hebras y cantidad de palabras y un string que contiene
// el nombre del archivo
//SALIDA: Arreglo de dos dimensiones de Hebra (DUDA)
//Función que se encarga de inicializar la estructura de hebras
Hebra** hebra_array_init(int hebras, int words, char* nameFile){
    FILE* file = fopen(nameFile,"r");
    Hebra** hebra_array;
    char buffer[250];
    hebra_array = (Hebra**) malloc(sizeof(Hebra*)*(hebras+1));
    hebra_array[hebras]=NULL;
    int j;
    for(j=0;j<hebras;j++){
        hebra_array[j]=(Hebra*) malloc(sizeof(Hebra));
        hebra_array[j]->int_words = 0;
    }
    int i=0;
    while(i<words){
        memset(buffer,0,250);
        //fgets(buffer,250,file);
        //rtrim(buffer);
        fscanf(file,"%s",buffer);
        strcpy(hebra_array[i%hebras]->words[hebra_array[i%hebras]->int_words],buffer);
        hebra_array[i%hebras]->int_words++;
        i++;
    }
    return hebra_array;
}

//ENTRADA: Puntero a la estructura Hebra
//SALIDA: Void (Nada)
//Esta función se encarga de liberar la memoria que utiliza la hebra.
void hebra_destroy(Hebra* hebra){
    free(hebra);
}

//ENTRADA: Puntero a la estructura Hebra
//SALIDA: Void (Nada)
//Muestra la cantidad de palabras asignadas a la hebra. 
void hebra_show(Hebra* hebra){
    printf("Cantidad de palabras: %d\n",hebra->int_words);
    int i=0;
    while (i<hebra->int_words){
        printf("%s ",hebra->words[i]);
        i++;
    }
    printf("\n");
}

//ENTRADA: Arreglo de la estructura Hebra
//SALIDA: Void (Nada)
//Se libera la memoria que utiliza el arreglo de Hebras, llamando por cada hebra a la función anterior.
void hebra_array_destroy(Hebra** hebra_array){
    int i=0;
    if(hebra_array==NULL){
        return;
    }
    while (hebra_array[i]!=NULL){
        hebra_destroy(hebra_array[i]);
        i++;
    }
    free(hebra_array);
}

//ENTRADA: Arreglo de la estructura hebra
//SALIDA: Void (Nada)
//Se encarga de mostrar cada hebra por consola. 
void hebra_array_show(Hebra** hebra_array){
    int i=0;
    if(hebra_array==NULL){
        return;
    }
    while (hebra_array[i]!=NULL){
        printf("Hebra:%d\n",i);
        hebra_show(hebra_array[i]);
        printf("\n");
        i++;
    }
}

//ENTRADA: Puntero a la estructura posicion, 2 enteros donde row representa a las filas y col a las columnas 
//SALIDA: Void (Nada)
//Calcula una posición aleatoria. 
void position_rand(Position* position, int row, int col){
    position->row = rand()%row;
    position->col = rand()%col;
}

//ENTRADA: Una posición (fila y columna)
//SALIDA: Void (Nada)
//Se encarga de mostrar por pantalla la coordenada ingresada por parametro
void position_show(Position pos){
    printf("Coordenadas: %d,%d\n",pos.row,pos.col);
}

//ENTRADA: Puntero a la estructura Matriz, un string y una posición
//SALIDA: Void (Nada)
//Función que se encarga de insertar la palabra ingresada a la matriz en una posición
void insert_word(Matriz* matriz, char* string,Position position){
    int i;
    //printf("insertando:%s\n",string);
    for(i=0;i<strlen(string);i++){
        matriz->data[position.row][position.col+i] = string[i]; 
    }
}

//ENTRADA: String que corresponde al nombre del archivo
//SALIDA: Entero (0 o 1)
//Esta función se encarga de verificar si el archivo con el nombre ingresado por parámetro existe o no. 
// Si retorna 0, el archivo no existe y en caso contrario, retorna 1. 
int fileExists(char* nombreArchivo){
    FILE* archivo;
    archivo = fopen(nombreArchivo, "r");
    if(archivo == NULL)
        return 0;
    else
        return 1;
}

//ENTRADA: Todos los valores que ingresan por parametro con getopt
//SALIDA: Entero (0 o 1)
//Se encarga de tomar todos los valores ingresados por consola, de verificar si se ingresaron de manera correcta o no. 
int opt_get(int argc, char** argv,char ivalue[300],int* hvalue,int* cvalue,int* nvalue,int* mvalue,char svalue[300],int* dflag){
    if(argc > 14){
        printf("Sobran parametros.\n");
        return 0;
    }else if(argc < 13){
        printf("Faltan parametros.\n");
        return 0;
    }
    int c;

    while ((c = getopt(argc,argv,"i:h:c:n:m:s:d")) != -1){
        switch(c){
            case 'i':
                strcpy(ivalue,optarg);
                break;
            case 'h':
                sscanf(optarg, "%d", hvalue);
                break;
            case 'c':
                sscanf(optarg, "%d", cvalue);
                break;
            case 'n':
                sscanf(optarg, "%d", nvalue);
                break;
            case 'm':
                sscanf(optarg, "%d", mvalue);
                break;;
            case 'd':
                *dflag = 1;
                break;
            case 's':
                strcpy(svalue,optarg);
                break;
            case '?':
                if(isprint(optopt)){
                    printf("Opcion desconocida.\n");   
                    return 0;
                }
                else{ 
                    printf("Opcion con caracter desconocido\n");
                    return 0;
                }
            default:
                abort();
        }
    }
    return 1;
}

//ENTRADA: Todos los valores que ingresan por parametro con getopt
//SALIDA: Entero (0 o 1)
//Esta función abarca las pequeñas funciones anteriores, donde se verifican si todos los parametros cumplen las condiciones.
int verifyArguments(char* ivalue, int hvalue, int cvalue, int nvalue, int mvalue, char* svalue){
   if(fileExists(ivalue) == 0){
        printf("ERROR: Archivo no encontrado.\n");
        return 0;
    }else if(hvalue <= 0){
        printf("ERROR: Numero de hebras debe ser mayor que 0\n");
        return 0;
    }else if(cvalue <= 0){
        printf("ERROR: Cantidad de palabras debe ser mayor que 0\n");
        return 0;
    }else if(nvalue <= 0){
        printf("ERROR: Ancho de matriz debe ser mayor que 0\n");
        return 0;
    }else if(mvalue <= 0){
        printf("ERROR: Largo de matriz debe ser mayor que 0\n");
        return 0;
    }
    else 
        return 1;
}