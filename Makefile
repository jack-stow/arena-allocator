EXECS = arena
all: $(EXECS)
arena: arena.c
	gcc arena.c -o arena
