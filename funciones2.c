#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "estructuras.h"
#include "funciones2.h"

Matriz* matriz_create(int n,int m){
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->row = n;
    matriz->col = m;
    matriz->data = (char**) malloc (sizeof(char*)*n);
    matriz->locks = (pthread_mutex_t*) malloc (sizeof(pthread_mutex_t)*n);
    int i;
    for(i=0;i<n;i++){
        matriz->data[i] = (char*) calloc (m,sizeof(char));
    }
    for(i=0;i<n;i++){

         pthread_mutex_init(& matriz->locks[i], NULL);
    }
    return matriz;
}
int can_write_row(Matriz* matriz,char* string, int row){
    int i=0;
    int max=0;
    int counter=0;
    for(i=0;i<matriz->col;i++){
        if(matriz->data[row][i]!='\0'){
            counter=0;
        }
        else{
            counter++;
        }
        if(counter>max){
            max=counter;
        }
    }
    if(max<strlen(string)){
        return 0;
    }
    return 1;
}

void matriz_destroy(Matriz* matriz){
    int i;  
    for(i=0;i<matriz->row;i++){
        free(matriz->data[i]);
    }
    free(matriz->data);
    free(matriz);

}

void matriz_show(Matriz *matriz){
    int i,j;
    for (i=0;i<matriz->row;i++){
        for(j=0;j<matriz->col;j++){
            //matriz->data[i][j] = 'X';
            printf("%c",matriz->data[i][j]);
        }
        printf("\n");
    }
}

char letter_min_rand(){
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
                buffer = letter_min_rand();
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

void rtrim(char* string){
	while(string[strlen(string)-1]==' ' 
		|| string[strlen(string)-1]=='\n' 
		|| string[strlen(string)-1]=='\t'
		|| string[strlen(string)-1]=='\r'){
		string[strlen(string)-1]='\0';
	}
}

Hebra** hebra_array_init(int hebras, int words, char* nameFile){
    
    FILE* file = fopen(nameFile,"r");
    
    Hebra** hebra_array;
    int words_per_hebra;
    char buffer[250];
    if(hebras<=0){
        return NULL;
    }
    else if(hebras<=words){
       
        hebra_array = (Hebra**) malloc(sizeof(Hebra*)*(hebras+1));
        hebra_array[hebras]=NULL;
        int j;
        for(j=0;j<hebras;j++){
            hebra_array[j]=(Hebra*) malloc(sizeof(Hebra));
            hebra_array[j]->int_words = 0;
        }
        
    }
    else{
        hebra_array = (Hebra**) malloc(sizeof(Hebra*)*(words+1));
        hebra_array[words]=NULL;
        int j;
        for(j=0;j<words;j++){
            hebra_array[j]=(Hebra*) malloc(sizeof(Hebra));
            hebra_array[j]->int_words = 0;
        }
    }
    int i=0;
    while(!feof(file)){
        memset(buffer,0,250);
        fgets(buffer,250,file);
        rtrim(buffer);
        //fscanf(file,"%s",buffer);
        //if(!feof(file)){
            strcpy(hebra_array[i%hebras]->words[hebra_array[i%hebras]->int_words],buffer);
            hebra_array[i%hebras]->int_words++;
            i++;
        //}
    }
    
    return hebra_array;
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
void hebra_array_show(Hebra** hebra_array,int n){
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

void position_rand(Position* position, int row, int col){
    position->row = rand()%row;
    position->col = rand()%col;
}

