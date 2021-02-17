OBJS	= main.o decoder.o
SOURCE	= main.c decoder.c
HEADER	= decoder.h
OUT	= Interpreteur
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99 -lcunit

decoder.o: decoder.c
	$(CC) $(FLAGS) decoder.c -std=c99 -lcunit


clean:
	rm -f $(OBJS) $(OUT)
