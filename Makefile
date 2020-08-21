
CC=gcc

all: assembler

assembler: main.c utils.c
	$(CC) -o assembler main.c utils.c

test: 
	./assembler test.asm test.hack

realtest:
	./assembler maxL.asm realtest.hack

clean: 
	rm *.hack