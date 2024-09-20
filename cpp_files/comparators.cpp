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


int compareIntTypes(void* a, void* b){
    return *(const int*)a > *(const int*)b;
}

int compareDoubleTypes(void* a,void* b){
    printf("%.1f %.1f %d\n", *(const double*)a, *(const double*)b,((*(const double*)a - *(const double*)b) > 0.000001));
    return (*(const double*)a - *(const double*)b) > 0.000000000001;
}

int compareStringTypes(void* a,void* b){
    return strcmp(*(const char**)a, *(const char**)b) > 0 ? 1 : 0;
}

int my_strcmp(void* firstStr, void* secondStr){

    for (int i = 0, j = 0; ((s_string*)firstStr)->stringArray[i] != '\0' && ((s_string*)secondStr)->stringArray[j] != '\0'; i++, j++){
        
        // first str
        if (!isalpha(((s_string*)firstStr)->stringArray[i]) && ((s_string*)firstStr)->stringArray[i] != '\0') { ++i; --j; continue; };

        // second str
        if (!isalpha(((s_string*)secondStr)->stringArray[j]) && ((s_string*)secondStr)->stringArray[j] != '\0') { --i; ++j; continue; };

        // if everithing is fine
        if (tolower(((s_string*)firstStr)->stringArray[i]) != tolower(((s_string*)secondStr)->stringArray[j])) 
            return (tolower(((s_string*)firstStr)->stringArray[i]) - tolower(((s_string*)secondStr)->stringArray[j])) > 0 ? 0 : 1;

    }
    return 0;
}

int my_strcmp2(void* firstStr, void* secondStr){

     for (size_t i = ((s_string*)firstStr) ->lenOfStr, j = ((s_string*)secondStr)->lenOfStr; i > 0 && j > 0; i--, j--){
        
        // first str
        if (!isalpha(((s_string*)firstStr)->stringArray[i]) && ((s_string*)firstStr)->stringArray[i] != '\0') { --i; ++j; continue; };

        // second str
        if (!isalpha(((s_string*)secondStr)->stringArray[j]) && ((s_string*)secondStr)->stringArray[j] != '\0') { ++i; --j; continue; };

        // if everithing is fine
        if (tolower(((s_string*)firstStr)->stringArray[i]) != tolower(((s_string*)secondStr)->stringArray[j])){
            //printf("| %c %c %d\n", firstStr->stringArray[i], secondStr->stringArray[j], (firstStr->stringArray[i]) - tolower(secondStr->stringArray[j]));
            return (tolower(((s_string*)firstStr)->stringArray[i]) - tolower(((s_string*)secondStr)->stringArray[j])) > 0 ? 1 : 0;
        }

    }
    return 0;
}

