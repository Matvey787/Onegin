#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void sortStrings(char** stringArray, size_t size);
int needToSwap(char* firstStr, char* secondStr);
void printArray(char** stringArray, size_t size);
int my_strcmp(char* firstStr, char* secondStr);
void getStrings(char*** stringArray, size_t* size, FILE* rFile, char** correctOrder);
void printOneDemArray(int64_t* array, int size);
void writeRepairedText(char** stringArray, FILE* file, size_t size);

const int startMemForPointers = 8;

struct s_text {
    char** stringArray;
    size_t numStr;
};

int main(){

    const char* textFileName = "/home/matvey/Рабочий стол/C/sortStrings/txt_files/text.txt";
    const char* repairedTextFileName = "/home/matvey/Рабочий стол/C/sortStrings/txt_files/repairedText.txt";
    
    FILE* rFile = fopen(textFileName, "rb");
    FILE* wFile = fopen(repairedTextFileName, "w");
    assert(rFile != NULL && "can't open read_File");
    assert(wFile != NULL && "can't open write_File");
    //s_text text = {(char**)calloc(1, startMemForPointers), 0};


    char** stringArray = (char**)calloc(1, startMemForPointers);
    assert(wFile != NULL && "can't allocate memory");

    size_t readedStrings = 0;
    char* correctOrder[100] = {};

    getStrings(&stringArray, &readedStrings, rFile, correctOrder);

    printOneDemArray((int64_t*)correctOrder, 100);

    sortStrings(stringArray, readedStrings);
    printArray(stringArray, readedStrings);

    printf("Correct order:\n");
    printArray((char**)correctOrder, readedStrings);

    writeRepairedText((char**)correctOrder, wFile, readedStrings);

    return 0;
}

void getStrings(char*** stringArray, size_t* size, FILE* rFile, char** correctOrder){
    assert(*stringArray != NULL);
    assert(size != NULL);
    assert(rFile != NULL);

    char* buffer = NULL;
    size_t len = 0;
    ssize_t readedChars = 0;
    size_t memForPointers = startMemForPointers;
    size_t readedStrings = 0;
    
    while ((readedChars = getline(&buffer, &len, rFile)) != EOF ){

        if (++readedStrings * sizeof(char*) >  memForPointers){
            memForPointers = memForPointers*4;
            *stringArray = (char**)realloc(*stringArray, memForPointers);
            assert(*stringArray != NULL && "fatal realloc");
        }
        (*stringArray)[readedStrings-1] = (char*)realloc((*stringArray)[readedStrings-1], readedChars*sizeof(char) - 1);
        
        correctOrder[readedStrings-1] = (*stringArray)[readedStrings-1];

        for (int i = 0; i < readedChars - 1; i++)
            (*stringArray)[readedStrings-1][i] = buffer[i];
            
        (*stringArray)[readedStrings-1][readedChars - 1] = '\0';
    }
    *size = readedStrings;
    fclose(rFile);
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

void printOneDemArray(int64_t* array, int size){
    int i = 0;
    while (array[i] && (i < size)) {printf("%ld ", array[i]); i++;};
    printf("\n");
}

int my_strcmp(char* firstStr, char* secondStr){

    for (int i = 0, j = 0; firstStr[i] != '\0' && secondStr[j] != '\0'; i++, j++){
        
        // first str
        if (!isalpha(firstStr[i]) && firstStr[i] != '\0') { ++i; --j; continue; };

        // second str
        if (!isalpha(secondStr[j]) && secondStr[j] != '\0') { --i; ++j; continue; };

        // if everithing is fine
        if (tolower(firstStr[i]) != tolower(secondStr[j])) return tolower(firstStr[i]) - tolower(secondStr[j]);

    }
    return 0;
}

void writeRepairedText(char** stringArray, FILE* file, size_t size){
    for (size_t i = 0; i<size; i++){
        fputs(stringArray[i], file);
        fputs("\n", file);
    }   
    fclose(file);
}