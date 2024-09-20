#ifndef QSORT
#define QSORT
#include <stdio.h>
void quickSort(void* data, long int left, long int right, size_t sizeOftype, int (*compareFunc)(void*, void*));

#endif