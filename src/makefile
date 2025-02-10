EXE=anthill
CFLAGS=-Wall -ansi -pedantic -g
CC=gcc
CLIB = -L../lib -lscreen


all: $(EXE)
anthill: command.o space.o game.o game_reader.o  game_actions.o game_loop.o graphic_engine.o 
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c $<

space.o: space.c space.h types.h
	$(CC) $(CFLAGS) -c $<

game.o: game.c game.h command.h types.h space.h game_reader.h
	$(CC) $(CFLAGS) -c $<

game_reader.o: game_reader.c game.h command.h types.h space.h
	$(CC) $(CFLAGS) -c $<

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h
	$(CC) $(CFLAGS) -c $<

game_loop.o: game_loop.c command.h types.h game.h space.h  game_actions.h graphic_engine.h
	$(CC) $(CFLAGS) -c $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h  command.h types.h space.h libscreen.h
	$(CC) $(CFLAGS) -c $<

.PHONY clean:
	rm -f *.o $(EXE)