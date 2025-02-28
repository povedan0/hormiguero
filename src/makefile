EXE=anthill set_test character_test
CFLAGS=-Wall -ansi -pedantic -g
CC=gcc
CLIB = -L. -lscreen


all: $(EXE)

anthill: command.o space.o game.o game_reader.o set.o character.o game_actions.o game_loop.o graphic_engine.o player.o object.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

set_test: set_test.o set.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

character_test: character_test.o character.o
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

player.o: player.c types.h
	$(CC) $(CFLAGS) -c $<

object.o: object.c types.h
	$(CC) $(CFLAGS) -c $<

set.o: set.c types.h 
	$(CC) $(CFLAGS) -c $<

set_test.o: set_test.c set.h types.h set_test.h test.h
	$(CC) $(CFLAGS) -c $<

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -c $<

character_test.o: character_test.c character.h types.h character_test.h test.h
	$(CC) $(CFLAGS) -c $<

run:
	./anthill anthill.dat

.PHONY clean:
	rm -f *.o $(EXE)