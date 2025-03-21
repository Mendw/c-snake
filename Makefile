all: build execute clean

build: main.c board.c sleep.c
	gcc main.c board.c sleep.c -o snake.out -lncurses

execute:
	@./snake.out

clean:
	find . -name '*.out' -delete