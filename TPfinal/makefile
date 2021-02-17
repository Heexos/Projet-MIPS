OBJS	= main.o emulateur.o registre_emul.o ram_emul.o decoder.o
OUT	= test
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

emulateur.o: emulateur/emulateur.c
	make -C emulateur/

decoder.o: decoder/decoder.c
	make -C decoder/

registre_emul.o ram_emul.o: Vregistre_VRAM/registre_emul.c Vregistre_VRAM/ram_emul.c
	make -C Vregistre_VRAM/

clean:
	rm -f $(OBJS)
