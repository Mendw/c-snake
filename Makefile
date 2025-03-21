all: build execute

build: main.c board.c sleep.c
	gcc main.c board.c sleep.c -o snake.out -lncurses

execute:
	@./snake.out