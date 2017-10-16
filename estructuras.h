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

typedef struct range{
    Position init;
    Position fin;
}Range;

typedef struct list{
    Range* data;
    int lentght;
}List;
typedef struct matriz{
    char **data;
    pthread_mutex_t* locks;
    pthread_mutex_t** locks2;
    List** wrote;
    int row;
    int col;
}Matriz;

#endif