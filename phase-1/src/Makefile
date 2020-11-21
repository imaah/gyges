OBJS   = main.o input_output.o board.o
TODEL  = main.o input_output.o
SOURCE = main.c input_output.c 
HEADER = input_output.h board.h
OUT    = gyges
DOUT   = test-gyges
CC     = gcc
FLAGS  = -g -c -Wall
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c

input_output.o: input_output.c
	$(CC) $(FLAGS) input_output.c

test: main.c
	$(CC) $(FLAGS) main.c -DTEST
	$(CC) $(FLAGS) input_output.c
	$(CC) -g $(OBJS) -o $(DOUT) $(LFLAGS)

clean:
	rm -f $(OUT) $(TODEL)

move:
	mv $(TODEL) ../build/
	cp board.o ../build/