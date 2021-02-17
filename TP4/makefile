OBJS	= main_test.o registre_emul.o ram_emul.o
SOURCE	= main_test.c registre_emul.c ram_emul.c
HEADER	= registre_emul.h ram_emul.h
OUT	= test
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main_test.o: main_test.c
	$(CC) $(FLAGS) main_test.c -std=c99 $(LFLAGS)

registre_emul.o: registre_emul.c
	$(CC) $(FLAGS) registre_emul.c -std=c99 $(LFLAGS)

ram_emul.o: ram_emul.c
	$(CC) $(FLAGS) ram_emul.c -std=c99 $(LFLAGS)


clean:
	rm -f $(OBJS)
