#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "funciones2.h"


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
        if(array[i]==0){
            return 0;
        }
    }
    return 1;
}
void* insert(void* args){
    int index=getIndex();
    printf("%d\n",index);
    int i;
    int not_next;
    int array_can_rows[matriz->row];
    Position pos;
    char buffer[250];
    for (i=0;i<hebra_array[index]->int_words;i++){
        int j=0;
        for(j=0;j<matriz->row;j++){
            array_can_rows[j]=1;
        }
        not_next = 1;
        printf("%s\n",hebra_array[index]->words[i]);
        while(can_write(array_can_rows,matriz->row) && not_next){
            position_rand(&pos,matriz->row,matriz->col);
            pthread_mutex_lock(&matriz->locks[pos.row]);
            if(can_write_row(matriz,hebra_array[index]->words[i],pos.row)){
                if(is_valid_position(matriz,hebra_array[index]->words[i],pos)){
                    
                    memset(buffer,0,250);
                    strcpy(buffer,hebra_array[index]->words[i]);
                    string_upper(buffer);
                    insert_word(matriz,buffer,pos);
                    not_next=0;
                }
            }
            else{
                array_can_rows[pos.row]=0;
            }
            //matriz_show(matriz);


            
            pthread_mutex_unlock(&matriz->locks[pos.row]);
        }
    }
}
int main(){
    srand(time(NULL));
    
    hebra_array = hebra_array_init(2,7,"words.txt");
    hebra_array_show(hebra_array,1);
    //printf("HOL!\n");
    
    matriz = matriz_create(20,20);
    int i;
    for(i=0;i<2;i++){
        pthread_create(&hebra_array[i]->thread , NULL , insert , NULL );
    }
    for(i=0;i<2;i++){
        pthread_join ( hebra_array[i]->thread , NULL ) ;
    }
    matriz_fill(matriz);
    matriz_show(matriz);

    /*int array_can_rows[matriz->row];
    int j=0;
    for(j=0;j<matriz->row;j++){
        array_can_rows[j]=1;
    }
    printf("Puedo escribir en matriz:%d\n",can_write(array_can_rows,matriz->row));
    printf("Puedo escribir en fila:%d\n",can_write_row(matriz,"hola2",0));*/
    
    return 1;
}