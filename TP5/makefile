OBJS	= main.o affichage.o emulateur.o
SOURCE	= main.c affichage.c emulateur.c
HEADER	= affichage.h emulateur.h
OUT	= test
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

affichage.o: affichage.c
	$(CC) $(FLAGS) affichage.c -std=c99

emulateur.o: emulateur.c
	$(CC) $(FLAGS) emulateur.c -std=c99


clean:
	rm -f $(OBJS)
