CFILES = $(wildcard src/build/*/*.c)
CFILES2 = $(wildcard src/build/*.c)
CFILES3 = $(wildcard src/build/*/*/*.c)
CFILES4 = $(wildcard src/lib/blist/*.c)
COMPILE = gcc -Wall -o main.o src/main.c

.PHONY: run

MAIN_FILE = main.ats

run: 
	@${COMPILE} ${CFILES} ${CFILES2} ${CFILES3} ${CFILES4} && nasm -f elf *.s; ld -m elf_i386 -s -o demo cmpler.o && ./demo && ./main.o ${MAIN_FILE}

#check in prototype/examples/fib.ats

#thats fibonacci just me brainstorming, but I dont exactly like where this is going since the problem is having to enforce particular operations in a register is near impossible, we will need to brainstorm another way

# MOCA RESPONSE
# ^ I like the idea of enforcing things to be in specific spots tbh. I mean, each register does something specific. If you are wanting to change the concept..we're gonna have to change the WHOLE thing. I honestly like the idea of having the d register work with data that will be used later on, the p register working with ideals that will be printed etc. The user is not restricted to what they can do in many cases(such as calling functions, doing things with other register data etc). It really sets up a formal syntax where it is much more organized..ya'know?
# Like, we have all of the "data", or values to be used throughout the program, in the data register. Then we have everything we want printed out stored in the p register, then the global register is the key point of the program.
# Idk, the formal type of syntax it provides just kinda makes me look at it and like it even more...ya'know? I guess you can say it's "organized"

TronSI REPONSE:

yes, but sometimes some registers may be too heavily overloaded, for example the operator register will be overloaded, I guess we could make multi file support to keep it clean, since otherwise you're going to have like a 5000 line crap in operator register and everything else just be calling it. I like the concept too, I'm just scared it will be too "limiting"








#so far i'm just using very very high level dynamic operations where we can enforce an if statement in glb using : after an operator, and treat it as a function, where thing after it runs if the operator returns true

#we can introduce bitwise operations later, but just to confirm all variables in assembly are global variables right? (since it's basically from the stack/heap theres no local variables right)

#also I mean I guess this is a mix of esoteric as well, but we need a silghtly better register system imo, lmk what you think