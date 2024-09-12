#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void sortStrings(char** stringArray, size_t size);
int needToSwap(char* firstStr, char* secondStr);
void printArray(char** stringArray, size_t size);
int my_strcmp(char* firstStr, char* secondStr);
void getStrings(char*** stringArray, size_t* size, FILE* rFile);

const int startMemForPointers = 8;

struct s_text {
    char** stringArray;
    size_t numStr;
};

int main(){

    const char* filename = "/home/matvey/Рабочий стол/C/sortStrings/txt_files/text.txt";
    FILE* rFile = fopen(filename, "r");

    s_text text = {(char**)calloc(1, startMemForPointers), 0};


    char** stringArray = (char**)calloc(1, startMemForPointers);
    size_t readedStrings = 0;

    getStrings(&stringArray, &readedStrings, rFile);
    //printf("%s", stringArray[0]);
    sortStrings(stringArray, readedStrings);
    printArray(stringArray, readedStrings);
    fclose(rFile);
    return 0;
}

void getStrings(char*** stringArray, size_t* size, FILE* rFile){
    assert(*stringArray != NULL);
    assert(size != NULL);
    assert(rFile != NULL);
    // FIXME assert
    // FIXME ded flags
    //char** stringArr = stringArray;
    char* buffer = NULL;
    size_t len = 0;
    ssize_t readedChars = 0;
    size_t memForPointers = startMemForPointers;
    size_t readedStrings = 0;
    
    while ((readedChars = getline(&buffer, &len, rFile)) != EOF ){
        ++readedStrings;
        //printf("%s\n", buffer);
        if (readedStrings * sizeof(char*) >  memForPointers){
            memForPointers = memForPointers*4;
            *stringArray = (char**)realloc(*stringArray, memForPointers);
        }
        (*stringArray)[readedStrings-1] = (char*)realloc((*stringArray)[readedStrings-1], readedChars*sizeof(char) - 1);

        for (int i = 0; i < readedChars - 1; i++)
            (*stringArray)[readedStrings-1][i] = buffer[i];
            
        (*stringArray)[readedStrings-1][readedChars - 1] = '\0';
        printf("%s %d\n", (*stringArray)[readedStrings-1], (int)readedStrings);
    }
    printf("ok2");
    *size = readedStrings;
}

void sortStrings(char** stringArray, size_t size){
    char* swapStr  = NULL;
    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size - 1; j++)
            if (needToSwap(stringArray[j], stringArray[j+1])){
                swapStr = stringArray[j];
                stringArray[j] = stringArray[j+1];
                stringArray[j+1] = swapStr;
            }
    }
}

int needToSwap(char* firstStr, char* secondStr){
    if (my_strcmp(firstStr, secondStr) < 0)
        return 1;
    return 0;
}

void printArray(char** stringArray, size_t size){
    for (size_t i = 0; i < size; i++){
        printf("%s", stringArray[i]);
        printf("\n");
    }
}

int my_strcmp(char* firstStr, char* secondStr){

    int firstStrEmpty = 0;
    int secondStrEmpty = 0;

    for (int i = 0, j = 0; !firstStrEmpty && !secondStrEmpty; i++, j++){
        
        // first str
        if (!isalpha(firstStr[i]) && firstStr[i] != '\0') { ++i; --j; continue; };
        if (firstStr[i] == '\0') {firstStrEmpty = 1;}

        // second str
        if (!isalpha(secondStr[j]) && secondStr[j] != '\0') { --i; ++j; continue; };
        if (secondStr[j] == '\0') {secondStrEmpty = 1;}

        // if everithing is fine
        if (tolower(firstStr[i]) != tolower(secondStr[j])) return tolower(firstStr[i]) - tolower(secondStr[j]);

    }
    return 0;
}