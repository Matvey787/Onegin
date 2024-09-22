#include <stdio.h>
#include <stdlib.h>
#include "../h_files/structs.h"
#include "../h_files/fillArrayOfStrings.h"

void fillArraysInStruct(s_string** stringArray, char* buffer, size_t numOfStrings){

    // allocate memory for array of structs
    *stringArray = (s_string*)calloc(numOfStrings, sizeof(s_string));

    // fill our array

    int needNewStartPtr = 0; // flag if we write string from buffer to array of structs and need new pointer to string
    char* ptr_startOfStr = buffer; // pointer to start of string
    size_t indexStr = 0; // current index of string

    for (size_t i = 0;  indexStr < numOfStrings; i++){

        if (needNewStartPtr) {ptr_startOfStr = buffer + i; needNewStartPtr = 0; }

        if (buffer[i] == '\n'){
            buffer[i] = '\0';
            (*stringArray)[indexStr].string = ptr_startOfStr;
            (*stringArray)[indexStr++].length = (size_t)(buffer + i - ptr_startOfStr + 1);

            needNewStartPtr = 1;

        } 

    }
}

void fillArrayOfPointers(char*** stringArray, char* buffer, size_t numOfStrings){
    // allocate memory for array of structs
    *stringArray = (char**)calloc(numOfStrings, sizeof(char*));

    // fill our array

    int needNewStartPtr = 0; // flag if we write string from buffer to array of structs and need new pointer to string
    char* ptr_startOfStr = buffer; // pointer to start of string
    size_t indexStr = 0; // current index of string

    for (size_t i = 0;  indexStr < numOfStrings; i++){

        if (needNewStartPtr) {ptr_startOfStr = buffer + i; needNewStartPtr = 0; }

        if (buffer[i] == '\n' || buffer[i] == '\0'){
            buffer[i] = '\0';
            (*stringArray)[indexStr++] = ptr_startOfStr;
            needNewStartPtr = 1;
        } 

    }
}