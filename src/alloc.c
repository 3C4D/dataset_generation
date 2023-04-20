// Enzo CADONI - LIS - 2022/2023
// Safe allocation functions

#include <stdlib.h>
#include <stdio.h>

// Allocate chunks and verify the allocation
//   - size : size to allocate
void *safe_alloc(size_t size){
  void *ptr = malloc(size);
  if(ptr == NULL){
    perror("Allocation ");
    exit(-1);
  }
  return ptr;
}