// Enzo CADONI - LIS - 2022/2023
// Safe allocation function prototypes

#ifndef ALLOC_H_
#define ALLOC_H_

#include <stdlib.h>

// Allocate chunks and verify the allocation
//   - size : size to allocate
void *safe_alloc(size_t size);

#endif