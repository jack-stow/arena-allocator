#include "arena.h"
#include<stdio.h>
#include<stdlib.h>

// Allocates memory or the Arena struct and the large underlying memory block.
// Returns a pointer to the new, initialized Arena, or NULL on failure
Arena *ArenaAlloc(size_t capacity){
	
}

// Returns the large block of memory managed by the arena back to the operating system.
// Should be called when the arena is no longer needed.
void ArenaRelease(Arena *arena){
	
}

// Allocates 'size' bytes from the arena using bump allocation
// Returns a pointer to the new memory, or NULL if capcity is exceeded.
void *ArenaPush(Arena *arena, U64 size){
	
}

// Allocates 'size' bytes and initializes the memory block to zero.
// Returns a pointer to the new, zeroed memory.
void *ArenaPushZero(Arena *arena, U64 size){
	
}

// Gets the current offset (or position) of the next allocation.
// This value can be saved to later reset the arena's state
U64 ArenaGetPos(Arena *arena){
	
}

// Moves the 'bump' pointer backward by 'size' bytes.
// This is dangerous and hsould only be used if 'size' exactly matches the last allocation's size (including padding).
void ArenaPop(Arena *arena, U64 size){
	
}

// Resets the 'bump' pointer to a previously saved position ('pos').
// All memory allocated since 'pos is instantaneously reclaimed for future allocations.
void ArenaSetPosBack(Arena *arena, U64 pos){
	
}

// Resets the 'bump' pointer to the very beginning (position 0).
// Effectively frees all allocated memory without returning the block to the OS.
void ArenaClear(Arena *arena){
	
}

