#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "estructuras.h"
#include "funciones.h"



Hebra** hebra_array = NULL;
Matriz* matriz = NULL;
List** ocupando = NULL;
List** escrito = NULL;
pthread_mutex_t lockPrint;
int dflag = 0; //bandera


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
                if((matriz->data[pos.row][pos.col+e]) != (' ')){
                    status = 0;
                    break;   
                }
            }
            if (status == 1){
                    memset(buffer,0,250);
                    strcpy(buffer,hebra_array[index]->words[i]);
                    string_upper(buffer);
                    insert_word(matriz,buffer,pos);
                    not_next = 0;
                if(dflag == 1){
                    pthread_mutex_lock(& lockPrint);
                    printf("Hebra: %d\n",index);
                    printf("Insertando palabra: %s\n",buffer);
                    position_Show(pos);
                    matriz_show(matriz); 
                    printf("\n\n");  
                    pthread_mutex_unlock(&lockPrint);
                }

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
int main(int argc, char** argv){

    pthread_mutex_init(&lockPrint, NULL);

    char ivalue[300]; //nombre archivo entrada
    int hvalue; //cantidad de hebras
    int cvalue; //cantidad de palabras
    int nvalue; //ancho matriz
    int mvalue; //largo matriz
    char svalue[300]; //nombre archivo salida
    int c;

    if(argc > 14){
        printf("Sobran parametros.\n");
        return 0;
    }else if(argc < 13){
        printf("Faltan parametros.\n");
        return 0;
    }

    while ((c = getopt(argc,argv,"i:h:c:n:m:s:d")) != -1){
        switch(c){
            case 'i':
                strcpy(ivalue,optarg);
                break;
            case 'h':
                sscanf(optarg, "%d", &hvalue);
                break;
            case 'c':
                sscanf(optarg, "%d", &cvalue);
                break;
            case 'n':
                sscanf(optarg, "%d", &nvalue);
                break;
            case 'm':
                sscanf(optarg, "%d", &mvalue);
                break;;
            case 'd':
                dflag = 1;
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

    if(verifyArguments(ivalue,hvalue,cvalue,nvalue,mvalue,svalue) == 0) 
        return 0;

    srand(time(NULL));
    int hebras=hvalue;
    int filas = mvalue;
    int col= nvalue;
    int words = cvalue;



    if(hebras > words)
        hebras = words;
    hebra_array = hebra_array_init(hebras,words,ivalue);
    if(dflag == 1){
        hebra_array_show(hebra_array);
    }
    
    matriz = matriz_create2(filas,col);
    int i;

    for(i=0;i<hebras;i++){
        pthread_create(&hebra_array[i]->thread , NULL , insert , NULL );
    }
    for(i=0;i<hebras;i++){
        pthread_join ( hebra_array[i]->thread , NULL ) ;
    } 

    FILE* archivoSalida = fopen(svalue,"w");
    matriz_fill(matriz);
    if(dflag == 1){
        printf("Matriz final: \n");
        matriz_show(matriz);
    }
    matriz_print(matriz, archivoSalida);
    matriz_destroy(matriz);
    hebra_array_destroy(hebra_array);
    
    return 1;
}