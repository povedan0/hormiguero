EXE=anthill
CFLAGS=-Wall -ansi -pedantic -g
CC=gcc
CLIB = -L. -lscreen


all: $(EXE)
anthill: command.o space.o game.o game_reader.o  game_actions.o game_loop.o graphic_engine.o 
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

command.o: command.c
	$(CC) $(CFLAGS) -c $<

space.o: space.c
	$(CC) $(CFLAGS) -c $<

game.o: game.c
	$(CC) $(CFLAGS) -c $<

game_reader.o: game_reader.c
	$(CC) $(CFLAGS) -c $<

game_actions.o: game_actions.c
	$(CC) $(CFLAGS) -c $<

game_loop.o: game_loop.c
	$(CC) $(CFLAGS) -c $<

graphic_engine.o: graphic_engine.c
	$(CC) $(CFLAGS) -c $<

.PHONY clean:
	rm -f *.o $(EXE)