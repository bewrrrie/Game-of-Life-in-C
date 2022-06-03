CC=gcc
LIBS=-lncurses

all: clean compile run_demo

game_of_life.o: game_of_life.h game_of_life.c
	$(CC) game_of_life.h game_of_life.c -c $(LIBS)

game_start_point.o: game_start_point.h game_start_point.c
	$(CC) game_start_point.h game_start_point.c -c $(LIBS)

compile: game_start_point.o game_of_life.o main.c
	$(CC) game_start_point.o game_of_life.o main.c -o gol $(LIBS)

run_demo: compile ../samples/gosper_gun.txt
	./gol < ../samples/gosper_gun.txt

diamond: compile ../samples/diamond_4_8_12.txt
	./gol < ../samples/diamond_4_8_12.txt

glider: compile ../samples/glider.txt
	./gol < ../samples/glider.txt

gosper_gun: compile ../samples/gosper_gun.txt
	./gol < ../samples/gosper_gun.txt

loaf: compile ../samples/loaf.txt
	./gol < ../samples/loaf.txt

pulsar: compile ../samples/pulsar.txt
	./gol < ../samples/pulsar.txt

spades: compile ../samples/spades.txt
	./gol < ../samples/spades.txt

clean:
	rm -f gol *.out *.o *.h.gch
