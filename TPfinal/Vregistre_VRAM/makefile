OBJS	= ../ram_emul.o ../registre_emul.o
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: ram_emul.o registre_emul.o

ram_emul.o: ram_emul.c
	gcc $(FLAGS) ram_emul.c -o ../ram_emul.o

registre_emul.o: registre_emul.c
	gcc $(FLAGS) registre_emul.c -o ../registre_emul.o

clean:
	rm -f $(OBJS)
