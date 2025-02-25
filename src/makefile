
EXE=anthill space_test set_test
CFLAGS=-Wall -ansi -pedantic -g
CC=gcc
CLIB = -L. -lscreen
SRC=command.o space.o game.o game_reader.o game_actions.o game_loop.o graphic_engine.o player.o object.o set.o

all: $(EXE)

############################## anthill executable ########################################

anthill: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

############################ test module executables #####################################

space_test: space_test.o space.o set.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

set_test: set_test.o set.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIB)

############################## anthil source code ########################################

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

################################### test module source ###################################

space_test.o: space_test.c space.h types.h set.h test.h
	$(CC) $(CFLAGS) -c $<

set_test.o: set_test.c set.h types.h set_test.h test.h
	$(CC) $(CFLAGS) -c $<

################################## instructions ##########################################

run:
	./anthill anthill.dat

.PHONY clean:
	rm -f *.o $(EXE)