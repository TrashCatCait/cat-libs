#include <stdint.h>
#include <stdio.h>
#include "vector.h"

int main(int argc, char **argv) {
    uint32_t *data = vector_create(uint32_t);
    uint32_t num = 240; 
    
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
    vector_add(uint32_t, data, 2000);
    
    printf("VECTOR BEFORE DELETE:\n");
    for(uint64_t i = 0; i < vector_get_size(data); i++) {
	printf("%d\n", data[i]);
    }

    vector_remove_multi(data, 1, 2);

    printf("VECTOR AFTER DELETE:\n");
    for(uint64_t i = 0; i < vector_get_size(data); i++) {
	printf("%d\n", data[i]);
    }
    
    if(data != NULL) {
	vector_free(data);
    }
    return 0;
}
