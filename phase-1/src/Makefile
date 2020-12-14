OBJS   = main.o input_output.o game.o board.o
TODEL  = main.o input_output.o game.o
SOURCE = main.c input_output.c game.c
HEADER = input_output.h board.h game.h
OUT    = gyges.out
CC     = gcc
FLAGS  = -c -Wall -pedantic -Wextra

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAGS) main.c

input_output.o: input_output.c
	$(CC) $(FLAGS) input_output.c

game.o: game.c
	$(CC) $(FLAGS) game.c

clean:
	rm -f $(OUT) $(TODEL)

move:
	mv $(TODEL) $(OUT) ../build/
	cp board.o ../build/

tar:
	tar -czvf gyges-phase-1-Clément_GUIBOUT-Esteban_MORISSE.tar.gz *
	mv gyges-phase-1-Clément_GUIBOUT-Esteban_MORISSE.tar.gz /media/sf_shared