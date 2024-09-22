#include <stdio.h>
#include "../h_files/writeStringsToFile.h"


void writeRepairedText(char** stringArray, size_t size, const char* file_name){
    FILE* wFile = fopen(file_name, "w");
    for (size_t i = 0; i<size; i++){
        fputs(stringArray[i], wFile);
        fputs("\n", wFile);
    }   
    fclose(wFile);
}