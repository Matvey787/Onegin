#ifndef FILLARRAYOFSTRINGS
#define FILLARRAYOFSTRINGS

#include <stdio.h>
#include "../h_files/structs.h"

void fillArraysInStruct(s_string** stringArray, char* buffer, size_t numOfStrings);
void fillArrayOfPointers(char*** stringArray, char* buffer, size_t numOfStrings);

#endif