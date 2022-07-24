#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#include "vector.h" 

/*
 * Simple C vector library 
 *
 */

vec_data *_i_vector_create(size_t size) {
    printf("%lu\n", size);
    
    //Allocate vector data structure + sizeof data type in the vector 
    struct vector *vec = calloc(1, sizeof(struct vector) + size);
    vec->type_size = size;
    vec->length = size; //vec->data has 1 entry free to use  
    vec->size = 0; //vec->data has no entries yet
    printf("VECTOR ALLOCATED: %p\n", vec);
    return &vec->data; //return vec->data 
}

//Pass in the vector data to get the vector structure 
vector_t *vector_get_struct(void *vec_data) {
    return vec_data - offsetof(struct vector, data);
}

void vector_free(void *vec_data) {
    struct vector *vec = vector_get_struct(vec_data);
    printf("size %lu, length %lu\nptr %p\n", vec->size, vec->length, vec);
    for(int i = 0; i < vec->size; i++) {
        printf("Data: %d\n", ((uint32_t *)&vec->data)[i]);
    }
    free(vec);
}


uint64_t vector_get_size(void *vec_data) {
    return vector_get_struct(vec_data)->size;
}

uint64_t vector_get_len(void *vec_data) {
    return vector_get_struct(vec_data)->length;
}

bool vector_has_space(vector_t *vec) {
    return (vec->size * vec->type_size) < vec->length;
}

/* vector realloc will attempt to reallocate the vector and if there is an error will 
 * free the vector and all memory used by it and return NULL to the caller
 * leaving the choice to the caller how the program should respond. 
 */
vector_t *vector_realloc(vector_t *vec) {
    vector_t *new_vec = realloc(vec, sizeof(vector_t) + vec->length + vec->type_size);
    if(new_vec == NULL) {
	return NULL;
    }
    new_vec->length += new_vec->type_size;

    return new_vec;
}


//Add value onto the end of the vector
//returns the address of where to write the value 
//this is done to avoid the value having to be passed as a pointer
vec_data *_i_vector_add(void **vec_data) {
    vector_t *vec = vector_get_struct(*vec_data);

    if(!vector_has_space(vec)) {
        vec = vector_realloc(vec);
	if(vec == NULL) {
	    *vec_data = NULL;
	    return NULL;
	}
        *vec_data = &vec->data;
    } else { 
        printf("Has space\n");
    }

    return (void *)(((uint64_t)*vec_data) + (vec->type_size * vec->size++));
}

//vector remove is a function that takes in a vector postion and a vector then remove that postion in the vector
vector_status _i_vector_remove(void **vec_data, uint64_t pos, uint64_t length) {
    vector_t *vec = vector_get_struct(*vec_data); //get the vector struct 

    if(pos >= vec->size || pos + length > vec->size) {
        return VEC_OOB_ERR; //return error to the user 
    }
    
    //Move entries and reduce vector size to "remove an entry" shift entries above
    //pos along take up that place 
    memmove((void*)(((uint64_t)*vec_data) + (pos * vec->type_size)),
	    (void*)(((uint64_t)*vec_data) + ((pos + length) * vec->type_size)),
	    (vec->size - pos - length) * vec->type_size);
    
    //currently we don't free the memory yet opting to keep it so that if vector add is called reallocation is unneeded 
    vec->size -= length;

    return VEC_SUCCESS;
}



int main(int argc, char **argv) {
    uint32_t *data = vector_create(uint32_t);
    uint32_t num = 240; 
    int num2; 
    vector_add(uint32_t, data, num);
    vector_add(uint32_t, data, 800);
    if(data == NULL) {
	printf("Allocation Error\n");
	return 1;
    } 
    vector_add(uint32_t, data, 909);
    if(data == NULL) {
	printf("Allocation Error\n");
	return 1;
    }
    vector_remove(data, 0);
    vector_add(uint32_t, data, 2000);
    vector_remove_multi(data, 0, 3);
    if(data != NULL) {
	vector_free(data);
    }
    return 0;
}
