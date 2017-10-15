#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"


void* funcion(void* arg){
    int id = *((int*)arg);
    
    printf("%d",id);
    
}

Params* params;
//srand(time(NULL));
void* words_insert(void* args){
    int id = *((int*) args);
    Position position;
    int i;
    for(i=0;i<params->hebra_array[id]->int_words;i++){

    }
    pthread_mutex_lock(&params->mutex_array[0]);
}
int pueda(int* puede,int filas){
    int i;
    for(i=0;i<filas;i++){
        if(puede[i]==1){
            return 1;
        }
    }
    return 0;
}
void* insert(char** words,int filas,int int_words){
    int i=0;
    int puede[filas];
    int capacity;
    for (i=0;i<filas;i++){
        puede[i]=1;
    }
    Position position;
    for(i=0;i<int_words;i++){
        while(pueda(puede,filas)){
            capacity = capacity_max(params->matriz->data[position.row],params->matriz->col);
            if(is_valid_string(capacity,words[i])){
                if(inser_word(params->matriz,words[i],position)){
                    i++;
                }
            }   
            else{
                puede[position.row]=0;
            }
        }
        position_rand(&position,params->matriz->row,params->matriz->col);
        
    }
    

    
}


int main()
{
    //srand(time(NULL));
    /*char string[] = "hola como estas!";
    string_upper(string);   
    printf("%s\n",string);
*/
    //filas columnas, hebras, palabras,
    /*params = (Params*)  params_init(10,10,3,3,"words.txt");

    
    insert(params->hebra_array[0]->words,params->matriz->row,params->hebra_array[0]->int_words);
    printMatriz(params->matriz);
    params_destroy(params);*/
    /*pthread_t arreglo[20];
    int i;
    for(i=0;i<20;i++){
        pthread_create (& arreglo[i] , NULL , funcion , ( void *) &i ) ;
    }*/
    /*Matriz* matriz= (Matriz*) matriz_create(4,4);
    
    
    Position position;
    position_rand(&position,4,4);
    printf("%d\n",inser_word(matriz,"HOLA",position));
    printf("valido:%d\n",is_valid_string(matriz->col,"HOLaA"));
    printMatriz(matriz);
    printf("%d,%d\n",position.row,position.col);
        
    
    matriz_destroy(matriz);
    char string[10];
    memset(string,0,10);
    string[5]='1';
    printf("capacity:%d",capacity_max(string,10));*/
    
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
    
    

    
    
    
    FILE* file = fopen("words.txt","r");
    Hebra** hebra_array = (Hebra**) hebra_array_init(3, 6, "words.txt");
    hebra_show(hebra_array[0]);
    hebra_show(hebra_array[1]);
    hebra_show(hebra_array[2]);
    //int i;

    hebra_destroy(hebra_array[0]);
    hebra_destroy(hebra_array[1]);
    hebra_destroy(hebra_array[2]);

    



    
    return 1;
}