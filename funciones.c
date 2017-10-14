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

Hebra* hebra_init(int id,char* nameFile,int words){
    FILE* file = fopen(nameFile,"r");
    //(long int)linesProccess*i
    //fseek(file,position,SEEK_SET);
    int i=0;
    char buffer[10000];
    Hebra* hebra=(Hebra*)malloc(sizeof(Hebra));
    hebra->id = id;
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
void hebra_destroy(Hebra* hebra){
    int i;
    for(i=0;i<hebra->int_words;i++){
        free(hebra->words[i]);
    }
    free(hebra->words);
    free(hebra);
}

