#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "funciones.h"


void * slowprintf ( void * arg ) {
    char * msg ;
    int i;
    msg = ( char *) arg ;
    for ( i = 0 ; i < strlen ( msg ) ; i ++ ) {
        printf (" %c " , msg [ i ]) ;
        fflush ( stdout ) ;
        usleep (1000000) ;
    }
    void* ret=NULL;
    return ret;
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
    void* ret=NULL;
    return ret;
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
