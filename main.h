#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "board.h"
#include "sleep.h"
#include "config.h"

#define STEP_DURATION 300
#define EXIT_KEY_PRESSED (key == EXIT_KEY || key == EXIT_KEY + ('A' - 'a'))
#define PAUSE_KEY_PRESSED (key == PAUSE_KEY || key == PAUSE_KEY + ('A' - 'a'))

#define MAX(A,B) (((A)>(B))?(A):(B))