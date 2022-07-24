# C Vectors:

A basic implementation of vectors in C

# Problems currently:
- Vector add error checking is a little messy
- Users adding the wrong type to a vector could cause issues

# How it works:
The library defines a basic vector structure. As can be seen below. This structure works by holding metadata on the vector and the actual data itself.
```c 

typedef struct {
    uint32_t type_size; 
    uint64_t size; //Number of elements used 
    uint64_t length; //bytes allocated in data 
    void *data; //actual data ptr 
} vector_t;
```
`type_size` is the size of the type in the vector e.g. 4 for a `uint32_t`, `size` is the number of elements used in that vector, `length` is the number of bytes actually allocated so for a "full" vector `size * type_size` should equal `length`. Then finally `data` is at the start address of the array so we take the memory location of `data`, e.g. `&data` to get a pointer to the vector data area that we then cast to a type pointer for the type stored in that vector. 

The code is designed in a way that it could just be dropped into any project with minimal effort.

## Problems and Assumptions:
- Vectors can't remove entries(yet...)
- Vector add error checking not yet working 
- It assumes users will input the correct type for each vector operation 

## How to use:
Simply include `vector.c & vector.h` in your project.

### Best Practices: 
We recommend using the internal built in functions above when working with these vectors however this is not needed and they can be accessed however you want or with custom functions to implement your own custom behaviour for your unique use cases.

Along with this, Best practices of course would state to ensure you are checking all error codes returned by all functions before you assume anything has worked 
