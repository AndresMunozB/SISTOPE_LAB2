#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include "estructuras.h"
#include "funciones.h"


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

void matriz_destroy(Matriz* matriz){
    int i;  
    for(i=0;i<matriz->row;i++){
        free(matriz->data[i]);
        free( matriz->locks[i]);
    }
    free(matriz->data);
    free(matriz);
}

void matriz_show(Matriz *matriz){
    int i,j;
    for (i=0;i<matriz->row;i++){
        for(j=0;j<matriz->col;j++){
            printf("|%c",matriz->data[i][j]);
        }
        printf("\n");
    }
}

void matriz_print(Matriz *matriz, FILE* archivo){
    int i,j;
    for (i=0;i<matriz->row;i++){
        for(j=0;j<matriz->col;j++){
            fprintf(archivo,"%c",matriz->data[i][j]);
        }
        fprintf(archivo,"\n");
    }
}

char letter_min_rand(){
    char random;
    random = rand()%26;
    random+=97;
    return random;
}

//Llena la matriz con letras aleatorias
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

//Cambia el string de minusuculas a mayusculas
void string_upper(char* string){
    int i;
    for(i=0;i<strlen(string);i++){
        string[i]=toupper(string[i]);
    }
}




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

void hebra_destroy(Hebra* hebra){
    free(hebra);
}

void hebra_show(Hebra* hebra){
    printf("Cantidad de palabras: %d\n",hebra->int_words);
    int i=0;
    while (i<hebra->int_words){
        printf("%s ",hebra->words[i]);
        i++;
    }
    printf("\n");
}
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

void position_rand(Position* position, int row, int col){
    position->row = rand()%row;
    position->col = rand()%col;
}

void position_show(Position pos){
    printf("Coordenadas: %d,%d\n",pos.row,pos.col);
}

void insert_word(Matriz* matriz, char* string,Position position){
    int i;
    //printf("insertando:%s\n",string);
    for(i=0;i<strlen(string);i++){
        matriz->data[position.row][position.col+i] = string[i]; 
    }
}

int fileExists(char* nombreArchivo){
    FILE* archivo;
    archivo = fopen(nombreArchivo, "r");
    if(archivo == NULL)
        return 0;
    else
        return 1;
}
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