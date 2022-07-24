#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
    VEC_SUCCESS = 0,
    VEC_OOB_ERR, //OOB = Out of bounds
} vector_status;

typedef struct vector {
    uint32_t type_size; 
    uint64_t size; //Number of elements used 
    uint64_t length; //bytes allocated in data 
    void *data; //actual data ptr 
} vector_t;

typedef void vec_data;



vec_data *_i_vector_create(size_t size);
//Pass in the vector data to get the vector structure 
vector_t *vector_get_struct(void *vec_data);
void vector_free(void *vec_data);
uint64_t vector_get_size(void *vec_data);
uint64_t vector_get_len(void *vec_data);
bool vector_has_space(vector_t *vec);
vector_t *vector_realloc(vector_t *vec);
//Add value onto the end of the vector
vec_data *_i_vector_add(void **vec_data);
vector_status _i_vector_remove(void **vec_data, uint64_t pos, uint64_t length);

//Make this less complex somehow/get the return value back into the hands of the user
#define vector_add(type, vec, value) {\
    type *v = _i_vector_add((void**)&vec);\
    if(v != NULL) {\
	printf("%p\n", v);\
	v[0] = value; \
    } \
}

#define vector_create(type) ((type *) _i_vector_create(sizeof(type)))

#define vector_remove(vec, pos) _i_vector_remove((void**)&vec, pos, 1)
#define vector_remove_multi(vec, pos, len) _i_vector_remove((void**)&vec, pos, len) 
