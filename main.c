#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct matriz{
    char **data;
    int row;
    int col;
}Matriz;



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

void * slowprintf ( void * arg ) {
    char * msg ;
    int i;
    msg = ( char *) arg ;
    for ( i = 0 ; i < strlen ( msg ) ; i ++ ) {
    printf (" %c " , msg [ i ]) ;
    fflush ( stdout ) ;
    usleep (1000000) ;
    }
}


int d = 0;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

void *doSomthing(void* args){
    int i=0;
    char *c = (char*) args;
    while(i<1000000){
        printf("%c-%d\n",*c,i);
        pthread_mutex_lock(&mylock);
        d++;
        pthread_mutex_unlock(&mylock);
        i++;
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



int main(){

    Matriz* matriz = matriz_create(5,5);
    printf("%d\n",matriz->col);
    printf("%p\n",matriz);
    matriz_fill(matriz);
    printMatriz(matriz);
    
    printf("%p\n",matriz);

    
    /*pthread_t h1 ;
    pthread_t h2 ;
    char * hola = "Hola";
    char * mundo = "mundo";
    pthread_create (& h1 , NULL , slowprintf , ( void *) hola ) ;
    pthread_create (& h2 , NULL , slowprintf , ( void *) mundo );
    pthread_join ( h1 , NULL ) ;
    pthread_join ( h2 , NULL ) ;
    printf ( " Fin \n ");*/

    /*pthread_t h1 ;
    pthread_t h2 ;
    
    char a = 'a';
    char b = 'b';
    pthread_create (& h1 , NULL , doSomthing , ( void *) &a ) ;
    pthread_create (& h2 , NULL , doSomthing , ( void *) &b );
    pthread_join ( h1 , NULL ) ;
    pthread_join ( h2 , NULL ) ;
    printf("%d",d);*/
    matriz_destroy(matriz);

    



    
    
 
     
    

    return 1;
}
