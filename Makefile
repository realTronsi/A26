CFILES = $(wildcard src/build/*/*.c)
CFILES2 = $(wildcard src/build/*.c)
CFILES3 = $(wildcard src/build/*/*/*.c)
COMPILE = gcc -Wall -o main.o src/main.c

.PHONY: run

run: 
	@${COMPILE} ${CFILES} ${CFILES2} ${CFILES3} && ./main.o && nasm -f elf *.s; ld -m elf_i386 -s -o demo cmpler.o && ./demo