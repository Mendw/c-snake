#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef enum Cell_Value { EMPTY, HEAD, BODY, FRUIT } Cell_Value_t;
typedef enum Direction { NORTH, EAST, SOUTH, WEST } Direction_t;

typedef struct Vector2 {
    int x;
    int y;
} Vector2_t;

typedef struct Snake_Node {
    Vector2_t position;
    
    struct Snake_Node * prev;
    struct Snake_Node * next;
} Snake_Node_t;

typedef struct Snake {
    Snake_Node_t * head;
    Snake_Node_t * tail;
    Direction_t direction;
} Snake_t;

typedef struct Board {
    int width;
    int height;
    int points;
    Direction_t direction;

    char** squares;
    Snake_t* snake;
    time_t start_time;
} Board_t;

Board_t *initialize_board(int, int, int, int, Direction_t, int);
void move_snake(Board_t*, bool*);

#endif