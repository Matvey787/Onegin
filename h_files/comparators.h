#ifndef COMPARATORS
#define COMPARATORS

#include <stdio.h>
int compareIntTypes(void* a, void* b);
int compareDoubleTypes(void* a, void* b);
int compareStringTypes(void* a, void* b);
int my_strcmp2(void* firstStr, void* secondStr);
int my_strcmp(void* firstStr, void* secondStr);
#endif