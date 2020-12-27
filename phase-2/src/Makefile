OBJS	 = main.o input_output.o game.o board.o
SOURCE	 = main.c input_output.c game.c board.c
HEADER	 = game.h board.h
OUT	     = gyges.out
CC	     = gcc
FLAGS	 = -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

input_output.o: input_output.c
	$(CC) $(FLAGS) input_output.c 

game.o: game.c
	$(CC) $(FLAGS) game.c 

board.o: board.c
	$(CC) $(FLAGS) board.c 

move:
	mv $(OBJS) $(OUT) $(WIN-OUT) ../build/

clean:
	rm -f $(OBJS) $(OUT)