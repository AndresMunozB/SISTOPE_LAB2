#include <pthread.h>
#ifndef _STRUCTS_H_
#define _STRUCTS_H_



typedef struct position{
    int row;
    int col;
}Position;

typedef struct hebra{
    int int_words;
    char words[3000][250];
    pthread_t thread;
}Hebra;


typedef struct matriz{
    char **data;
    pthread_mutex_t** locks;
    int row;
    int col;
}Matriz;

#endif