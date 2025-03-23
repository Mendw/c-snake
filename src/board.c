#include "../include/board.h"

Snake_Node_t* create_snake_node(int x, int y) {
    Snake_Node_t* node = malloc(sizeof(Snake_Node_t));

    node->prev = NULL;
    node->position.x = x;
    node->position.y = y;
    node->next = NULL;

    return node;
}

Vector2_t delta_from_direction(Direction_t direction) {
    Vector2_t delta = { 0, 0 };
    switch (direction) {
    case NORTH:
        delta.y = -1;
        break;
    case EAST:
        delta.x =  1;
        break;
    case SOUTH:
        delta.y =  1;
        break;
    case WEST:
        delta.x = -1;
        break;
    }

    return delta;
}

Snake_t* initialize_snake(int head_x, int head_y, Direction_t direction, int length) {
    Snake_t* snake = malloc(sizeof(Snake_t));
    snake->head = create_snake_node(head_x, head_y);
    Vector2_t delta = delta_from_direction(direction);
    
    Snake_Node_t* snake_ptr = snake->head;
    for (int i = 1; i < length + 1; i++) {
        snake_ptr->next = create_snake_node(head_x - delta.x*i, head_y - delta.y*i);
        snake_ptr->next->prev = snake_ptr;
        snake_ptr = snake_ptr->next;
    }

    snake->tail = snake_ptr;
    return snake;
}

char** initialize_squares(int width, int height, Snake_t* snake) {
    char** squares = malloc(sizeof(char *) * width);
    for (int i = 0; i < height; i++) {
        squares[i] = malloc(sizeof(char) * height);
        for (int j = 0; j < width; j++) {
            squares[i][j] = EMPTY;
        }
    }


    squares[snake->head->position.y][snake->head->position.x] = HEAD;
    for(
        Snake_Node_t* snake_node = snake->head->next; 
        snake_node != NULL; 
        snake_node = snake_node->next
    ) { squares[snake_node->position.y][snake_node->position.x] = BODY; }

    return squares;
}

Vector2_t generate_random_fruit(Board_t* board) {
    Vector2_t fruit;
    while (true) {
        fruit.x = rand() % board->width;
        fruit.y = rand() % board->height;

        if (board->squares[fruit.y][fruit.x] == EMPTY) {
            break;
        }
    }
    
    board->squares[fruit.y][fruit.x] = FRUIT;
}

Board_t *initialize_board(int width, int height, int head_x, int head_y, Direction_t direction, int lenght) {
    srand(time(NULL));
    Board_t *board = malloc(sizeof(Board_t));

    board->width = width;
    board->height = height;
    board->start_time = time(NULL);
    board->direction = direction;
    board->points = 0;

    board->snake = initialize_snake(head_x, head_y, direction, lenght);
    board->squares = initialize_squares(width, height, board->snake);

    generate_random_fruit(board);

    return board;
}

Vector2_t remove_tail(Board_t* board) {
    Snake_Node_t* old_tail = board->snake->tail;
    
    if (board->squares[old_tail->position.y][old_tail->position.x] == BODY) {
        board->squares[old_tail->position.y][old_tail->position.x] = EMPTY;
    }

    Snake_Node_t* new_tail = old_tail->prev;
    new_tail->next = NULL;
    free(old_tail);
    
    board->snake->tail = new_tail;
}

void move_head(Board_t* board, bool* game_over_ptr, bool* got_fruit_ptr) {
    Snake_Node_t* old_head = board->snake->head;
    Vector2_t delta = delta_from_direction(board->direction);

    Vector2_t new_position = { old_head->position.x + delta.x, old_head->position.y + delta.y  };
    if ( // Bounds check
        new_position.x < 0 || new_position.x >= board->width || 
        new_position.y < 0 || new_position.y >= board->height ||
        board->squares[new_position.y][new_position.x] == BODY && !(
            new_position.x == board->snake->tail->position.x &&
            new_position.y == board->snake->tail->position.y
        )
    ) { *game_over_ptr = true; return; }
    
    Snake_Node_t* new_head = create_snake_node(new_position.x, new_position.y);
    new_head->next = old_head;
    old_head->prev = new_head;
    
    *got_fruit_ptr = board->squares[new_position.y][new_position.x] == FRUIT;
    board->squares[new_head->position.y][new_head->position.x] = HEAD;
    board->squares[old_head->position.y][old_head->position.x] = BODY;

    board->snake->head = new_head;
}

void move_snake(Board_t* board, bool* game_over_ptr) {
    bool got_fruit;
    move_head(board, game_over_ptr, &got_fruit);

    if (got_fruit) {
        board->points++;
        generate_random_fruit(board);
    } else {
        remove_tail(board);
    }
} 