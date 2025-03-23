all: build execute clean

build: src/main.c src/board.c src/sleep.c
	gcc src/main.c src/board.c src/sleep.c -o snake.out -lncurses

execute:
	@./snake.out

clean:
	find . -name '*.out' -delete