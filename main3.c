#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"



Hebra** hebra_array = NULL;
Matriz* matriz = NULL;
List** ocupando = NULL;
List** escrito = NULL;


int getIndex(){
    int index;
    int i=0;
    while(hebra_array[i]!=NULL){
        if(hebra_array[i]->thread == pthread_self()){
            index = i;
        }
        i++;
    }
    return index;
}
int can_write(int* array,int n){
    int i;
    for(i=0;i<n;i++){
        if(array[i]==1){
            return 1;
        }
    }
    return 0;
}

void* insert(void* args){
    int index=getIndex();
    int i;
    int not_next;
    Position pos;
    char buffer[250];
    int counter;
    int e;
    int status;
    for (i=0;i<hebra_array[index]->int_words;i++){
        not_next = 1;
        counter = 0;
        while(not_next){
            status = 1;
            position_rand(&pos,matriz->row,matriz->col);
            for(e=0;e<strlen(hebra_array[index]->words[i]);e++){
                if(pos.col+e>=matriz->col){
                    status = 0;
                    break;
                }
                pthread_mutex_lock(&matriz->locks2[pos.row][pos.col+e]);
                if((matriz->data[pos.row][pos.col+e]) != ('\0')){
                    status = 0;
                    break;   
                }
            }
            if (status == 1){
                //printf("insertando palabra:\n");
                //position_Show(pos);
                memset(buffer,0,250);
                strcpy(buffer,hebra_array[index]->words[i]);
                string_upper(buffer);
                insert_word(matriz,buffer,pos);
                not_next = 0;
            }
            while(e>=0){
                pthread_mutex_unlock(&matriz->locks2[pos.row][pos.col+e]);
                e--; 
            }
            if(counter == (matriz->row*matriz->col)*50){
                not_next =0;
            }
            counter ++;
        }
    }
    void* ret = NULL;
    return ret;
}
int main(){
    srand(time(NULL));
    int hebras=7;
    int filas = 1;
    int col= 50;
    hebra_array = hebra_array_init(hebras,7,"words.txt");
    //hebra_array_show(hebra_array);
    
    matriz = matriz_create2(filas,col);
    int i;
    for(i=0;i<hebras;i++){
        pthread_create(&hebra_array[i]->thread , NULL , insert , NULL );
    }
    for(i=0;i<hebras;i++){
        pthread_join ( hebra_array[i]->thread , NULL ) ;
    } 
    matriz_fill(matriz);
    matriz_show(matriz);
    matriz_destroy(matriz);
    hebra_array_destroy(hebra_array);
    
    return 1;
}