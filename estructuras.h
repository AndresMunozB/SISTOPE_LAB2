#include <pthread.h>
#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct matriz{
    char **data;
    int row;
    int col;
}Matriz;

typedef struct position{
    int row;
    int col;
}Position;

typedef struct globalParams{
    pthread_mutex_t *mutex_array;
    
}GlobalParams;

typedef struct hebra{
    int id;
    int int_words;
    Position position;
    char** words;
}Hebra;

#endif