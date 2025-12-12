# Arena Allocator

This is an implementation of an arena allocator, along with a benchmarking program.
To build the program, call "make"

```sh
make
```

then call benchmark, like so
```sh
./benchmark <num_blocks> <block_size>
```
example:
```sh
./benchmark 100000000 4
```

malloc/free is used as a baseline to compare performance to the arena
