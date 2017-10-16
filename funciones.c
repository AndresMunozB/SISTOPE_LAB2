#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "estructuras.h"
#include "funciones.h"

Matriz* matriz_create(int n,int m){
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->row = n;
    matriz->col = m;
    matriz->data = (char**) malloc (sizeof(char*)*n);
    matriz->locks = (pthread_mutex_t*) malloc (sizeof(pthread_mutex_t)*n);
    int i;
    for(i=0;i<n;i++){
        matriz->data[i] = (char*) calloc (m,sizeof(char));
        pthread_mutex_init(& matriz->locks[i], NULL);
        /*matriz->data[i] = (char*) malloc (sizeof(char)*m);
        for(j=0;j<matriz->row;j++){
            matriz->data[i][j]='x';
        }*/
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
    //int words_per_hebra;
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
void hebra_destroy(Hebra* hebra){
    free(hebra);
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
void hebra_array_destroy(Hebra** hebra_array){
    int i=0;
    if(hebra_array==NULL){
        return;
    }
    while (hebra_array[i]!=NULL){
        //printf("Hebra:%d\n",i);
        //hebra_show(hebra_array[i]);
        //printf("\n");
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
int is_valid_position(Matriz* matriz,char* string, Position position){
    int i;
    if(position.col+strlen(string)-1>=matriz->col){
        //printf("se sale de matriz\n");
        return 0;
    }
    for (i=0;i<strlen(string);i++){
        if(matriz->data[position.row][i+position.col]!= '\0'){
            //printf("caracter no vacio:%c-%d,%d",matriz->data[position.row][i+position.col],position.row,position.col);
            return 0;
        }
    }
    return 1;
    
}

void insert_word(Matriz* matriz, char* string,Position position){
    int i;
    //printf("insertando:%s\n",string);
    for(i=0;i<strlen(string);i++){
        matriz->data[position.row][position.col+i] = string[i]; 
    }
    
}

Matriz* matriz_create2(int n,int m){
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->row = n;
    matriz->col = m;
    matriz->data = (char**) malloc (sizeof(char*)*n);
    matriz->locks = (pthread_mutex_t*) malloc (sizeof(pthread_mutex_t)*n);
    matriz->locks2 = (pthread_mutex_t**) malloc (sizeof(pthread_mutex_t*)*n);
    matriz->wrote = (List**) malloc(sizeof(List*)*n);
    int i,j;
    for(i=0;i<n;i++){
        matriz->data[i] = (char*) calloc (m,sizeof(char));
        pthread_mutex_init(& matriz->locks[i], NULL);
        matriz->locks2[i] = (pthread_mutex_t*) malloc (sizeof(pthread_mutex_t)*m);
        matriz->wrote[i] = list_init();
        for(j=0;j<m;j++){
            pthread_mutex_init(& matriz->locks2[i][j], NULL);
        }
    }
    
    return matriz;
}




Position position_create(int row,int col){
    Position pos;
    pos.row = row;
    pos.col = col;
    return pos;
}
int position_cmp(Position pos1,Position pos2){
    if(pos1.row == pos2.row && pos1.col == pos2.col ){
        return 1;
    }
    else{
        return 0;
    }
}
Range range_create(Position init, Position fin){
    Range range;
    range.init = init;
    range.fin = fin;
    return range;
}
Range range_rand(int row,int col){
    Range range;
    Position init;
    Position fin;
    position_rand(&init,row,col);
    position_rand(&fin,row,col);
    range.init = init;
    range.fin = fin;
    return range;
}
void range_show(Range range){
    printf("Range:\n");
    position_Show(range.init);
    position_Show(range.fin);
    printf("\n");
}
int range_valid(Range orig,Range new){
    if(orig.init.row != new.init.row){
        return 1;
    }
    if(new.init.col >= orig.init.col && new.init.col <= orig.fin.col){
        return 0;
    }
    if(new.fin.col >= orig.init.col && new.init.col <= orig.fin.col){
        return 0;
    }
    return 1;
}
int range_cmp(Range r1,Range r2){
    if(position_cmp(r1.init,r2.init) && position_cmp(r1.fin,r2.fin) ){
        return 1;
    }
    else{
        return 0;
    }
}
Position position_generate(Position init, char* string){
    int len = strlen(string);
    Position fin = position_create(init.row,init.col+len-1);
    return fin;
}
void position_Show(Position pos){
    printf("%d,%d\n",pos.row,pos.col);
}
Range range_generate(Position init, char* string){
    int len = strlen(string);
    Range range;
    Position fin = position_create(init.row,init.col+len-1);
    range.init = init;
    range.fin = fin;
    return range;
    
}

List* list_init(){
    List* list= (List*) malloc(sizeof(list));
    list->data = NULL;
    list->lentght = 0;
    return list;
}
void list_add(List* list,Range range){
    if(list->lentght == 0){
        list->data = (Range*) malloc (sizeof(Range));
        list->data[list->lentght] = range;
        list->lentght++;
    }
    else{
        list->lentght++;
        list->data =(Range*) realloc (list->data, sizeof(Range)*(list->lentght));
        list->data[list->lentght-1] = range;
        
    }
}
int list_find(List* list,Range range){
    int i=0;
    for(i=0;i<list->lentght;i++){
        if(range_cmp(list->data[i],range)){
            return i;
        }
    }
    return -1;
}

void list_remove(List* list,Range range){
    int index = list_find(list,range);
    if(index!=-1){
        int i;
        for(i=index;i<list->lentght-1;i++){
            list->data[i] = list->data[i+1];
        }
        //printf("hola");
        list->lentght--;
        list->data =(Range*) realloc (list->data, sizeof(Range)*(list->lentght));

    }
}

int list_range_valid(List* list,Range range){
    int i;
    for(i=0;i<list->lentght;i++){
        if(!range_valid(list->data[i],range)){
            //printf("este choca:\n");
            //range_show(list->data[i]);
            return 0;
        }
    }
    return 1;
}   

void list_show(List* list){
    int i;
    printf("list_show:\n");
    for (i=0;i<list->lentght;i++){
        printf("%d\n",i);
        range_show(list->data[i]);
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
int verifyArguments(char* ivalue, int hvalue, int cvalue, int nvalue, int mvalue, char* svalue){
    printf("ivalue = %s, hvalue = %d, cvalue = %d, nvalue = %d, mvalue = %d, svalue = %s\n", ivalue , hvalue, cvalue, nvalue, mvalue, svalue);
    if(fileExists(ivalue) == 0){
        printf("ERROR: Archivo no Encontrado.\n");
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