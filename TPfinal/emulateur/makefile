OBJS	= emulateur.o
SOURCE	= emulateur.c
OUT	= ../emulateur.o
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 =

emulateur.o: emulateur.c
	$(CC) $(FLAGS) emulateur.c -o $(OUT) -std=c99

clean:
	rm -f $(OBJS)
