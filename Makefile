CC = gcc
CFLAGS = -O2 -Wall -Wextra

SRC = benchmark.c arena.c
OBJ = $(SRC:.c=.o)

all: benchmark

benchmark: $(OBJ)
	$(CC) $(CFLAGS) -o benchmark $(OBJ)

%.o: %.c arena.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o benchmark
