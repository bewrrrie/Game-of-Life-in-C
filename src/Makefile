CC=gcc
LIBS=-lncurses

all: clean compile run_demo

game_of_life.o: game_of_life.h game_of_life.c
	$(CC) game_of_life.h game_of_life.c -c $(LIBS)

game_start_point.o: game_start_point.h game_start_point.c
	$(CC) game_start_point.h game_start_point.c -c $(LIBS)

compile: game_start_point.o game_of_life.o main.c
	$(CC) game_start_point.o game_of_life.o main.c -o gol $(LIBS)

run_demo: compile gosper_gun.txt
	./gol < gosper_gun.txt

diamond: compile diamond_4_8_12.txt
	./gol < diamond_4_8_12.txt

glider: compile glider.txt
	./gol < glider.txt

gosper_gun: compile gosper_gun.txt
	./gol < gosper_gun.txt

loaf: compile loaf.txt
	./gol < loaf.txt

pulsar: compile pulsar.txt
	./gol < pulsar.txt

spades: compile spades.txt
	./gol < spades.txt

clean:
	rm -f gol *.out *.o *.h.gch
