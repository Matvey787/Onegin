#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "../h_files/structs.h"
#include "../h_files/comparators.h"
#include "../h_files/qSort.h"
#include "../h_files/getFileStrings.h"
#include "../h_files/fillArrayOfStrings.h"
#include "../h_files/writeStringsToFile.h"

void writeRepairedText(char** stringArray, FILE* file, size_t size);
void getStrings(s_string* stringArray, size_t* size, FILE* rFile, char** correctOrder);
void printArrayOfStructs(s_string* array, size_t size);

size_t getNumberOfStrings(FILE* rFile);


typedef int(* t_compIntFunc)( void* a,  void* b);
typedef int(* t_compDblFunc)( void* a,  void* b);
typedef int(* t_compStrFunc)( void* a,  void* b);
typedef int(* t_compStructs)( void* a,  void* b);

int main(){
    t_compIntFunc typeInt = compareIntTypes;
    t_compDblFunc typeDbl = compareDoubleTypes;
    t_compStrFunc typeStr = compareStringTypes;
    t_compStructs typeStruct_FTSH = my_strcmp; // from the start (higer -> lower)
    t_compStructs typeStruct_FTEH = my_strcmp2; // from the end (higer -> lower)

    assert(typeInt != NULL);
    assert(typeDbl != NULL);
    assert(typeStr != NULL);
    assert(typeStruct_FTSH != NULL);
    assert(typeStruct_FTEH != NULL);

    //------------------------files-------------------------------

    // LINK /home/matvey/Рабочий стол/C/sortStrings/txt_files/text.txt 
    // LINK /home/matvey/Рабочий стол/C/sortStrings/txt_files/repairedText.txt 
    

    //------------------create array for strings-----------------------------------
    char* buffer = NULL;
    size_t readedStrings = getFileStrings(&buffer, "txt_files/text.txt"); // get all strings from file

    
    s_string* stringArray = NULL;

    fillArraysInStruct(&stringArray, buffer, readedStrings);

    if (stringArray == NULL){printf("can't allocate memory\n"); return 1; }


    char** correctOrder = NULL; // array for saving correct order of strings
    fillArrayOfPointers(&correctOrder, buffer, readedStrings); // save correct order by pointers

    if (correctOrder == NULL){printf("can't allocate memory\n"); return 1; }


    //-------------------work with array----------------------------------------

    printArrayOfStructs(stringArray, readedStrings);

    quickSort(stringArray, 0, (long int)readedStrings-1, sizeof(s_string), typeStruct_FTSH); // quick sort

    printArrayOfStructs(stringArray, readedStrings);

    writeRepairedText(correctOrder, readedStrings, "txt_files/repairedText.txt");

    free(stringArray);
    free(correctOrder);
    free(buffer);
    return 0;
}


void printArrayOfStructs(s_string* array, size_t size){
    printf("----------\n");
    for (size_t i = 0; i < size; i++)
        printf("string: %s len: %ld\n", array[i].string, (long int)array[i].length);\
    printf("----------\n");
}


//  another type of sort (view mySwap in project)

/* 
int needToSwap(s_string* firstStr, s_string* secondStr);
void sortStrings(s_string* stringArray, size_t size);

void sortStrings(s_string* stringArray, size_t size){
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size - i - 1; j++)
            if (needToSwap(stringArray+j, stringArray + j + 1))
                mySwap(&stringArray[j], &stringArray[j+1], sizeof(s_string*));
} 

int needToSwap(s_string* firstStr, s_string* secondStr){
    if (my_strcmp2(firstStr, secondStr) < 0)
        return 1;
    return 0;
}
*/

