#include "../include/main.h"

void update_board(Board_t* board, char key, bool* game_over_ptr) {
    switch (board->direction) {
    case NORTH:
    case SOUTH:
        switch (key) {
        case 'a':
        case 'A':
            board->direction = WEST;
            break;
        case 'd':
        case 'D':
            board->direction = EAST;
            break;
        }
        break;
    case EAST:
    case WEST:
        switch (key) {
        case 'w':
        case 'W':
            board->direction = NORTH;
            break;
        case 's':
        case 'S':
            board->direction = SOUTH;
            break;
        }
        break;
    }

    move_snake(board, game_over_ptr);
}

char get_head_character(Board_t* board) {
    switch (board->direction) {
    case NORTH: return '^';
    case  EAST: return '>';
    case SOUTH: return 'v';
    case  WEST: return '<';
    }
}

void print_score(Board_t* board) {
    long elapsed_seconds = time(NULL) - board->start_time;

    // Storing minutes in x, seconds in y
    Vector2_t elapsed_time = { elapsed_seconds / 60, elapsed_seconds % 60 };

    printw("Score: %d\tTime: %02d:%02d\n", board->points, elapsed_time.x, elapsed_time.y);
}

void print_delimiter() {
    printw("|");
    for (int _ = 0; _ < WIDTH; _++) { 
        printw("--"); 
    }
    printw("-|\n");
}

void draw_board(Board_t* board) {
    erase();

    print_score(board);
    print_delimiter();
    for (int i = 0; i < HEIGHT; i++) {
        printw("| ");
        for (int j = 0; j < WIDTH; j++) {
            switch (board->squares[i][j]) {
            case EMPTY:
                printw("  ");
                break;
            case HEAD:
                printw("%c ", get_head_character(board));
                break;
            case BODY:
                printw("+ ");
                break;
            case FRUIT:
                printw(". ");
                break;
            }
        }
        printw("|\n");
    }
    print_delimiter();
    refresh();
}

void handle_game_paused() {
    
}

void handle_game_over(Board_t* board) {
    mvprintw(board->height / 2, board->width / 2, "\tGame Over!");
            
    refresh(); 
    timeout(-1); 
    ms_sleep(500); 

    move(12, 10);
    mvprintw(board->height / 2 + 2, board->width / 2, "Press any key to exit");
    refresh(); 
    flushinp(); 
    getch();
    flushinp(); 
}

int main(){
    initscr();
    timeout(0); cbreak(); noecho();

    Board_t *board = initialize_board(WIDTH, HEIGHT, HEAD_X, HEAD_Y, START_DIRECTION, START_SIZE);
    
    bool game_paused = false;
    bool game_over = false;
    for (char key = 0; !EXIT_KEY_PRESSED; key=getch()) {
        if (PAUSE_KEY_PRESSED) {
            game_paused =! game_paused;
            printw("\nGame Paused");
            refresh();
        }

        if (!game_paused) {
            update_board(board, key, &game_over);
            if (game_over) {
                handle_game_over(board);
                break;
            }

            draw_board(board);
        }

        ms_sleep(MAX(75, STEP_DURATION - board->points * 10));
    }

    endwin();
	return 0;
}