EXE=hormiguero
CFLAGS=-Wall -ansi -pedantic
CC=gcc
LIBS=-L. -lscreen

all: $(EXE)

$(EXE): command.o game_actions.o game_loop.o game.o graphic_engine.o space.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

command.o: command.c
	$(CC) $(CFLAGS) -c $<

game_actions.o: game_actions.c
	$(CC) $(CFLAGS) -c $<

game_loop.o: game_loop.c
	$(CC) $(CFLAGS) -c $<

game.o: game.c
	$(CC) $(CFLAGS) -c $<

graphic_engine.o: graphic_engine.c
	$(CC) $(CFLAGS) -c $<

space.o: space.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f *.o $(EXE)
