CFILES = $(wildcard src/build/*/*.c)
CFILES2 = $(wildcard src/build/*.c)
CFILES3 = $(wildcard src/build/*/*/*.c)
CFILES4 = $(wildcard src/lib/*/*.c)
COMPILE = gcc -Wall -o main.o src/main.c

.PHONY: run

MAIN_FILE = main.ats

run: 
	@${COMPILE} ${CFILES} ${CFILES2} ${CFILES3} ${CFILES4} && ./main.o ${MAIN_FILE} && nasm -f elf *.s; ld -m elf_i386 -s -o ./bin/32bit cmpler.o && ./bin/32bit
