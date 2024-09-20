#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "../h_files/structs.h"
#include "../h_files/comparators.h"
#include "../h_files/qSort.h"


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

    //------------------------work with files-------------------------------

    // LINK /home/matvey/Рабочий стол/C/sortStrings/txt_files/text.txt 
    const char* textFileName = "txt_files/text.txt";
    // LINK /home/matvey/Рабочий стол/C/sortStrings/txt_files/repairedText.txt 
    const char* repairedTextFileName = "txt_files/repairedText.txt";
    FILE* rFile = fopen(textFileName, "rb");
    FILE* wFile = fopen(repairedTextFileName, "w");
    if (rFile == NULL){printf("can't open read_File\n"); return 1; }
    if (wFile == NULL){printf("can't open write_File\n"); return 1; }
    

    //------------------create array for strings-----------------------------------

    size_t readedStrings = getNumberOfStrings(rFile);
    s_string* stringArray = (s_string*)calloc(readedStrings, sizeof(s_string));
    assert(stringArray != NULL && "fatal realloc");
    char** correctOrder = (char**)calloc(readedStrings, sizeof(char*)); // array for saving correct order
    if (stringArray == NULL){printf("can't allocate memory\n"); return 1; }
    if (correctOrder == NULL){printf("can't allocate memory\n"); return 1; }


    //-------------------work with array----------------------------------------

    getStrings(stringArray, &readedStrings, rFile, correctOrder);
    printArrayOfStructs(stringArray, readedStrings);

    //sortStrings(stringArray2, readedStrings); // another type of sort
    quickSort(stringArray, 0, (long int)readedStrings-1, sizeof(s_string), typeStruct_FTSH); // quick sort

    printArrayOfStructs(stringArray, readedStrings);
    writeRepairedText((char**)correctOrder, wFile, readedStrings);
    
    for (size_t i = 0; i < readedStrings; i++)
        free(stringArray[i].stringArray);
    free(stringArray);
    free(correctOrder);

    return 0;
}

void getStrings(s_string* stringArray, size_t* size, FILE* rFile, char** correctOrder){
    assert(stringArray != NULL);
    assert(size != NULL);
    assert(rFile != NULL);

    char* buffer = NULL;
    size_t len = 0;
    ssize_t readedChars = 0;
    size_t readedStrings = 0;
    
    while ((readedChars = getline(&buffer, &len, rFile)) != EOF ){
        ++readedStrings;
        stringArray[readedStrings-1].stringArray = (char*)realloc(stringArray[readedStrings-1].stringArray, (long unsigned int)readedChars*sizeof(char));
        
        correctOrder[readedStrings-1] = stringArray[readedStrings-1].stringArray;

        for (int i = 0; i < readedChars - 1; i++)
            stringArray[readedStrings-1].stringArray[i] = buffer[i];
            
        stringArray[readedStrings-1].stringArray[readedChars - 1] = '\0';
        stringArray[readedStrings-1].lenOfStr = (long unsigned int)readedChars - 1;
    }
    *size = readedStrings;
    free(buffer);
    fclose(rFile);
}

size_t getNumberOfStrings(FILE* rFile){
    size_t numberOfStrings = 0;
    fseek(rFile, 0, SEEK_END);

    size_t size = (size_t)ftell(rFile);
    char* text = (char*)calloc((size_t)ftell(rFile), sizeof(char));
    
    fseek(rFile, 0, SEEK_SET);
    fread(text, sizeof(char), size, rFile);
    
    for (size_t i = 0; i<size; i++){
        if (text[i] == '\n') ++numberOfStrings;
    }
    
    fseek(rFile, 0, SEEK_SET);
    free(text);
    
    return numberOfStrings;
}

void printArrayOfStructs(s_string* array, size_t size){
    printf("----------\n");
    for (size_t i = 0; i < size; i++)
        printf("string: %s len: %ld\n", array[i].stringArray, (long int)array[i].lenOfStr);\
    printf("----------\n");
}

void writeRepairedText(char** stringArray, FILE* file, size_t size){
    for (size_t i = 0; i<size; i++){
        fputs(stringArray[i], file);
        fputs("\n", file);
    }   
    fclose(file);
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

