zalloc
======

An allocation library for safety-over-speed enthusiats.

### What?
`zalloc` is a tiny dynamic allocation library for C/C++ that wraps the typical `calloc` and `free` functions to add
ensured correctness features. Principally, `zalloc` has a well-defined interface and aims to provide no undefined 
behaviour for any permutation of its inputs our outputs.

### How?
`zalloc` provides three functions - `zalloc`, `zfree`, and `zsize`.

------------------------------------------------------------------------------------------------------------------------
`void* zalloc(size_t size)`

Allocates a block of zero-initialized memory. The block carries a memory overhead of 12 bytes.

------------------------------------------------------------------------------------------------------------------------
`bool zfree(void** mem)`

Frees a block of memory allocated by `zfree`. This zeroes the allocated region, and sets the referenced pointer to null.

------------------------------------------------------------------------------------------------------------------------
`size_t zsize(const void* mem)`

Determines the size of a memory block allocated by `zfree`.

### Benefits?
All memory allocated by `zalloc` is zero-initialized on allocation, and is provided to the user as such. Nonsane 
allocation request (such as zero-size allocations) are rejected. 

When memory blocks allocated with `zalloc` are freed, they are once again zeroed to erase potentially sensitive data and
to improve fault detection. Instead of reading garbage data in the case of a fault condition, the presence of 
continuous regions of zeroed memory can be clearly observed.

Furthermore, `zfree` guards against double-frees, and repeatedly freeing an already freed block has no effect.  Freeing
`null` has no effect. To prevent pointer reuse, `zfree` also explicitly nulls out the pointer it has just freed.

`zsize` can be used to retrieve the size of an allocated memory region after the fact.

### Implementation?
All memory blocks allocated by `zalloc` have a memory header located directly before the user-allocated memory pointed
to by the pointer returned by `zalloc`.  This header contains information about the memory block that `zalloc` uses to
free the memory in a safe and well-defined manner.

Currently, this header contains two fields - a magic signature that marks the region as being allocated by `zalloc`, and
the byte size of the following memory region. The header and its layout is to be considered an internal implementation
detail, and should not be accessed by consumers.