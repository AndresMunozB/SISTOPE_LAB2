#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"



Hebra** hebra_array = NULL;
Matriz* matriz = NULL;  



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
    for (i=0;i<hebra_array[index]->int_words;i++){
        not_next = 1;
        //printf("%s\n",hebra_array[index]->words[i]);
        int counter = 0;
        while(not_next){
            position_rand(&pos,matriz->row,matriz->col);
            Range range = range_generate(pos,hebra_array[index]->words[i]);
            if(range.fin.col<matriz->col){              
                pthread_mutex_lock(&matriz->locks[pos.row]);
                //list_show(matriz->wrote[pos.row]);
                if(list_range_valid(matriz->wrote[pos.row],range) ){
                    list_add(matriz->wrote[pos.row],range);
                    not_next =0;
                }
                pthread_mutex_unlock(&matriz->locks[pos.row]);
            }
            if(not_next == 0){
                //printf("insertando palabra\n");
                memset(buffer,0,250);
                strcpy(buffer,hebra_array[index]->words[i]);
                string_upper(buffer);
                insert_word(matriz,buffer,pos);
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