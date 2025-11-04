EXECS = arena
all: $(EXECS)
arena: arena.c
	gcc -shared arena.c -o arena.o
