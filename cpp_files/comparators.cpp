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

const double compareDoubleNumbers = 0.0001;

int compareIntTypes(void* a, void* b){
    return *(const int*)a > *(const int*)b;
}

int compareDoubleTypes(void* a,void* b){
    printf("%.1f %.1f %d\n", *(const double*)a, *(const double*)b,((*(const double*)a - *(const double*)b) > 0.000001));
    return (*(const double*)a - *(const double*)b) > compareDoubleNumbers;
}

int compareStringTypes(void* a,void* b){
    return strcmp(*(const char**)a, *(const char**)b) > 0 ? 1 : 0;
}

int my_strcmp(void* firstStr, void* secondStr){

    s_string* str1 = (s_string*)firstStr;
    s_string* str2 = (s_string*)secondStr;

    for (int i = 0, j = 0; (str1->stringArray)[i] != '\0' && (str2->stringArray)[j] != '\0'; i++, j++){

        // first str
        if (!isalpha((str1->stringArray)[i]) && (str1->stringArray)[i] != '\0') { ++i; --j; continue; };

        // second str
        if (!isalpha((str2->stringArray)[j]) && (str2->stringArray)[j] != '\0') { --i; ++j; continue; };

        // if everithing is fine
        if (tolower(str1->stringArray[i]) != tolower(str2->stringArray[j])) 
            return (tolower(str1->stringArray[i]) - tolower(str2->stringArray[j])) > 0 ? 0 : 1;

    }
    return 0;
}

int my_strcmp2(void* firstStr, void* secondStr){

    s_string* str1 = (s_string*)firstStr;
    s_string* str2 = (s_string*)secondStr;

     for (size_t i = str1->lenOfStr, j = str2->lenOfStr; i > 0 && j > 0; i--, j--){
        
        // first str
        if (!isalpha(str1->stringArray[i]) && (str1->stringArray[i] != '\0')) { --i; ++j; continue; };

        // second str
        if (!isalpha(str2->stringArray[j]) && (str2->stringArray[j] != '\0')) { ++i; --j; continue; };

        // if everithing is fine
        if (tolower(str1->stringArray[i]) != tolower(str2->stringArray[j])){
            //printf("| %c %c %d\n", firstStr->stringArray[i], secondStr->stringArray[j], (firstStr->stringArray[i]) - tolower(secondStr->stringArray[j]));
            return (tolower(str1->stringArray[i]) - tolower(str2->stringArray[j])) > 0 ? 1 : 0;
        }

    }
    return 0;
}

