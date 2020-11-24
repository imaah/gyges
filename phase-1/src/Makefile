OBJS   = main.o input_output.o game.o board.o 
TODEL  = main.o input_output.o game.o
SOURCE = main.c input_output.c game.c
HEADER = input_output.h board.h game.h
OUT    = gyges
DOUT   = test-gyges
CC     = gcc
FLAGS  = -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c

input_output.o: input_output.c
	$(CC) $(FLAGS) input_output.c

clean:
	rm -f $(OUT) $(TODEL)

move:
	mv $(TODEL) ../build/
	cp board.o ../build/