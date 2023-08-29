# Welcome to My Malloc
***

## Task

The task at hand is to implement a memory management system using my own implementation of the malloc, free, calloc, and realloc functions in C. The challenge lies in managing the memory efficiently and avoiding memory leaks, fragmentation, and other common issues associated with dynamic memory allocation

## Description

The malloc function allocates a block of memory of the requested size and returns a pointer to the start of the block. The free function deallocates the block of memory pointed to by the pointer passed to it. The calloc function allocates a block of memory for an array of num elements, each of them size bytes long, and returns a pointer to the first byte of the block. The realloc function changes the size of the memory block pointed to by ptr to size bytes

The calculation of the position of a returned pointer  is based on an unsigned char placed just before the allocation; the allocation and return of slots rely on this and on a bitmap arranged on each page. The bitmaps are linked in a linked list manner.

For each page:
StartPage|bitmap|data

No matter the multiple of sizepage that the page does, it is always divided according to the bitmap. That is 32bytes*8 = 256 slots. In terms of overhead, it is very reasonable, knowing that within the tree you only store the address of the pages and not the allocations.

So if you return a pointer, it finds the address of the page by itself and makes the slot available.

This design ensures efficient use of memory with minimal overhead, as only the addresses of the pages are stored in the tree, not the allocations
Returning a pointer automatically makes the corresponding slot available, optimizing memory managemement.

## Installation

This malloc lib can run a substitute for stdlib.h on malloc, calloc, realloc, free and malloc_usable_size using LD_PRELOAD trick : 

Insert inside the terminal : 
1.
```bash
make
```
2.
```bash
LD_PRELOAD=./libmymalloc.so ls
```
3.
```bash
unset LD_PRELOAD
```
4.
```bash
make fclean
```

/!\ make debug do not produce a usable binary/!\

## Usage

To use the malloc function, simply call it with the size of the block of memory you want to allocate. For example:

```c
void* ptr = malloc(100); // allocates 100 bytes of memory
```

To use the free function, simply call it with a pointer to the block of memory you want to deallocate. For example:
```c
free(ptr); // deallocates the memory pointed to by ptr
```

### The Core Team
* [Lorris BELUS](//github.com/Lbelus) - Developer


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
