#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"

Matriz* matriz_create(int n,int m){
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->row = n;
    matriz->col = m;
    matriz->data = (char**) malloc (sizeof(char*)*n);
    int i;
    for(i=0;i<n;i++){
        matriz->data[i] = (char*) calloc (m,sizeof(char));
    }
    return matriz;
}

void matriz_destroy(Matriz* matriz){
    int i;  
    for(i=0;i<matriz->row;i++){
        free(matriz->data[i]);
    }
    free(matriz->data);
    free(matriz);

}

void printMatriz(Matriz *matriz){
    int i,j;
    for (i=0;i<matriz->row;i++){
        for(j=0;j<matriz->col;j++){
            //matriz->data[i][j] = 'X';
            printf("%c",matriz->data[i][j]);
        }
        printf("\n");
    }
}

char randLetterMin(){
    char random;
    random = rand()%26;
    random+=97;
    return random;
}

void matriz_fill(Matriz* matriz){

    int i,j;
    char buffer;
    srand(time(NULL)); 
    for (i=0;i<matriz->row;i++){
        for(j=0;j<matriz->col;j++){
            if(matriz->data[i][j]=='\0'){
                buffer = randLetterMin();
                matriz->data[i][j] = buffer;
            }
        }
    }
}

void string_upper(char* string){
    int i;
    for(i=0;i<strlen(string);i++){
        string[i]=toupper(string[i]);
    }
}

Hebra* hebra_init(int id,FILE* file,int words){
    int i=0;
    char buffer[10000];
    Hebra* hebra=(Hebra*)malloc(sizeof(Hebra));
    hebra->int_words = words;
    hebra->words = (char**)malloc(sizeof(char*)*words);
    while(i<words){
        memset(buffer,0,10000);
        fscanf(file,"%s",buffer);
        hebra->words[i] = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(hebra->words[i],buffer);
        string_upper(hebra->words[i]);
        i++;

    }
    return hebra;
}
void hebra_show(Hebra* hebra){
    printf("int_words:%d\n",hebra->int_words);
    int i=0;
    while (i<hebra->int_words){
        printf("%s,",hebra->words[i]);
        i++;
    }
    printf("\n");
}
void hebra_destroy(Hebra* hebra){
    int i;
    for(i=0;i<hebra->int_words;i++){
        free(hebra->words[i]);
    }
    free(hebra->words);
    free(hebra);
}
Hebra** hebra_array_init(int hebras, int words, char* nameFile){
    FILE* file = fopen(nameFile,"r");
    int counter_words=0;
    int i;
    Hebra** hebra_array;
    printf("hola");
    if(hebras<=words){
        int words_per_hebra = words/hebras;
        int mod_words_per_hebras = words%hebras;
        hebra_array=(Hebra**) malloc(sizeof(Hebra*)*hebras+1);
        for(i=0;i<hebras;i++){
            if(i==hebras-1){
                hebra_array[i] = hebra_init(i,file,words_per_hebra+mod_words_per_hebras);
            }
            else{
                hebra_array[i] = hebra_init(i,file,words_per_hebra);
            }
             
        }
        hebra_array[hebras]=NULL;
        return hebra_array;
    }
    else if(hebras>words){
        int words_per_hebra = words/hebras;
        int mod_words_per_hebras = words%hebras;
        hebra_array=(Hebra**) malloc(sizeof(Hebra*)*words+1);
        for(i=0;i<words;i++){
            hebra_array[i] = hebra_init(i,file,1);
        }
        hebra_array[hebras]=NULL;
        return hebra_array;
    }  
}

void hebra_array_show(Hebra** hebra_array){
    int i=0;
    while(hebra_array[i]!=NULL){
        hebra_show(hebra_array[i]);
        i++;
    }
}
void hebra_array_destroy(Hebra** hebra_array){
    int i=0;
    while(hebra_array[i]!=NULL){
        hebra_destroy(hebra_array[i]);
        i++;
    }
}

Params* params_init(int rows,int cols,int hebras,int words,char* nameFile){
    Params* params = (Params*) malloc(sizeof(Params));
    params->capacity_max = (int*)malloc(sizeof(int)*rows);
    params->mutex_array = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*rows);
    params->hebra_array = (Hebra**) hebra_array_init(hebras,words,nameFile);
    params->matriz = matriz_create(rows,cols);
    params->rows = rows;
    params->hebras = hebras;
}

void params_destroy(Params* params){
    free(params->capacity_max);
    free(params->mutex_array);
    hebra_array_destroy(params->hebra_array);
    matriz_destroy(params->matriz);
    free(params);
}
void position_rand(Position* position, int row, int col){
    position->row = rand()%row;
    position->col = rand()%col;
}

int capacity_max(char* fila,int cols){
    int i=0;
    int max =0;
    int counter=0;
    for(i=0;i<cols;i++){
        printf("counter: %d(%c)\n",counter,fila[i]);

        if(fila[i]!='\0'){
            counter=0;
        }
        else{
            counter++;
        }
        if(counter>max){
            max=counter;
        }
        
    }
    return max;
}
int is_valid_string(int capacity_max,char*string){
    if(capacity_max<strlen(string)){
        return 0;
    }
    return 1;
}
int is_valid_position(Matriz* matriz,char* string, Position position){
    int i;
    if(position.col+strlen(string)-1>=matriz->col){
        return 0;
    }
    for (i=0;i<strlen(string);i++){
        if(matriz->data[position.row][i+position.col]!= '\0'){
            return 0;
        }
    }
    return 1;
    
}
int inser_word(Matriz* matriz, char* string,Position position){
    if(!is_valid_position(matriz,string,position)){
        return 0;
    }
    else{
        int i;
        for(i=0;i<strlen(string);i++){
            matriz->data[position.row][position.col+i] = string[i]; 
        }
    }
    return 1;
}





