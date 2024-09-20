#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../h_files/structs.h"
#include "../h_files/comparators.h"
#include "../h_files/qSort.h"

static void mySwap(void* a, void* b, size_t elemMemory);

void quickSort(void* data, long int left, long int right, size_t sizeOftype, int (*compareFunc)(void*, void*)){
    assert(data != NULL);

    if (left > right)
        return;

    long int pivot = (left+right)/2;
    long int i = left;
    long int j = right;

    while (i <= j){
        while (compareFunc((char*)data + (size_t)i*sizeOftype, (char*)data + (size_t)pivot*sizeOftype)) i++;

        while (!compareFunc((char*)data + (size_t)j*sizeOftype, (char*)data + (size_t)pivot*sizeOftype) && (j != pivot)) j--;

        if (i <= j){
            mySwap((char*)data + (size_t)i*sizeOftype, (char*)data + (size_t)j*sizeOftype, sizeOftype);
            i++;
            j--;
        }

    }
    quickSort(data, left, j, sizeOftype, compareFunc);
    quickSort(data, i, right, sizeOftype, compareFunc);
}

static void mySwap(void* a, void* b, size_t elemMemory){
    assert("mySwap: first element is null pointer" && a != NULL);
    assert("mySwap: second element is null pointer" && b != NULL);
    size_t summ = 0;

    uint64_t* a_long = (uint64_t*)a;
    uint64_t* b_long = (uint64_t*)b;


    while (summ + sizeof(uint64_t) <= elemMemory){

        uint64_t buf = *a_long;
        *a_long = *b_long;
        *b_long = buf;

        a_long += 1;
        b_long += 1;
        summ += sizeof(uint64_t);

    }
    uint32_t* a_int = (uint32_t*)a_long;
    uint32_t* b_int = (uint32_t*)b_long;

    if (summ + sizeof(uint32_t) <= elemMemory){

        uint32_t buf = *a_int;
        *a_int = *b_int;
        *b_int = buf;

        a_int += 1;
        b_int += 1;
        summ += sizeof(uint32_t);

    }

    uint16_t* a_short = (uint16_t*)a_int;
    uint16_t* b_short = (uint16_t*)b_int;

    if (summ + sizeof(uint16_t) <= elemMemory){

        uint16_t buf = *a_short;
        *a_short = *b_short;
        *b_short = buf;

        a_short += 1;
        b_short += 1;
        summ += sizeof(uint16_t);

    }

    uint8_t* a_char = (uint8_t*)a_short;
    uint8_t* b_char = (uint8_t*)b_short;

    if (summ + sizeof(uint8_t) <= elemMemory){

        uint8_t buf = *a_char;
        *a_char = *b_char;
        *b_char = buf;

        a_char += 1;
        b_char += 1;
        summ += sizeof(uint8_t);

    }
}