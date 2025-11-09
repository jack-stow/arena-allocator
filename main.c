#include <stdio.h>
#include <string.h>
#include "arena.h"

int main() {
	// Create an arena with 1024 bytes
	Arena *arena = ArenaAlloc(1024);
	if (!arena) {
		printf("Arena allocation failed!\n");
		return 1;
	}

	// push a few integers
	int *arr = PushArray(arena, int, 5);
	for (int i = 0; i < 5; i++) arr[i] = i * 10;

	// push zeroed memory
	int *zeroed = PushArrayZero(arena, int, 5);
	for (int i = 0; i < 5; i++) {
		if (zeroed[i] != 0) {
			printf("Zeroed memory test failed!\n");
			return 1;
		}
	}

	// Save the current position
	U64 pos = ArenaGetPos(arena);

	// Push something else
	char *text = PushArray(arena, char, 10);
	strcpy(text, "hello");

	printf("Text in arena: %s\n", text);

	// Rollback to saved position
	ArenaSetPosBack(arena, pos);

	// After rollback, previous allocation should be gone
	char *text2 = PushArray(arena, char, 10);
	strcpy(text2, "world");
	printf("Text after rollback: %s\n", text2);

	// Clear the arena
	ArenaClear(arena);
	if (ArenaGetPos(arena) != 0) {
		printf("ArenaClear failed!\n");
		return 1;
	}

	// Release the arena
	ArenaRelease(arena);

	printf("All tests passed!\n");
	return 0;
}
