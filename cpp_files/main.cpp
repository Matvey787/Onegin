#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

struct s_string {
    char* stringArray;
    size_t lenOfStr;
};



void writeRepairedText(char** stringArray, FILE* file, size_t size);
int needToSwap(s_string* firstStr, s_string* secondStr);
static void mySwap(void* a, void* b, size_t elemMemory);
void sortStrings(s_string* stringArray, size_t size);
void getStrings(s_string* stringArray, size_t* size, FILE* rFile, char** correctOrder);
void printArrayOfStructs(s_string* array, size_t size);
int my_strcmp2(s_string* firstStr, s_string* secondStr);
int my_strcmp(char* firstStr, char* secondStr);
size_t getNumberOfStrings(FILE* rFile);


int main(){

    // LINK /home/matvey/Рабочий стол/C/sortStrings/txt_files/text.txt 
    const char* textFileName = "/home/matvey/Рабочий стол/C/sortStrings/txt_files/text.txt";

    // LINK /home/matvey/Рабочий стол/C/sortStrings/txt_files/repairedText.txt 
    const char* repairedTextFileName = "/home/matvey/Рабочий стол/C/sortStrings/txt_files/repairedText.txt";
    
    FILE* rFile = fopen(textFileName, "rb");
    FILE* wFile = fopen(repairedTextFileName, "w");
    assert(rFile != NULL && "can't open read_File");
    assert(wFile != NULL && "can't open write_File");

    assert(wFile != NULL && "can't allocate memory");

    size_t readedStrings = getNumberOfStrings(rFile);

    s_string* stringArray2 = (s_string*)calloc(readedStrings, sizeof(s_string));
    assert(stringArray2 != NULL && "fatal realloc");

    printf("%ld\n", readedStrings);
    char** correctOrder = (char**)calloc(readedStrings, sizeof(char*));

    getStrings(stringArray2, &readedStrings, rFile, correctOrder);
    
    printArrayOfStructs(stringArray2, readedStrings);

    sortStrings(stringArray2, readedStrings);
    printArrayOfStructs(stringArray2, readedStrings);
    writeRepairedText((char**)correctOrder, wFile, readedStrings);

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
        stringArray[readedStrings-1].stringArray = (char*)realloc(stringArray[readedStrings-1].stringArray, readedChars*sizeof(char) - 1);
        
        correctOrder[readedStrings-1] = stringArray[readedStrings-1].stringArray;

        for (int i = 0; i < readedChars - 1; i++)
            stringArray[readedStrings-1].stringArray[i] = buffer[i];
            
        stringArray[readedStrings-1].stringArray[readedChars - 1] = '\0';
        stringArray[readedStrings-1].lenOfStr = readedChars - 1;
    }
    *size = readedStrings;
    fclose(rFile);
}

size_t getNumberOfStrings(FILE* rFile){
    size_t numberOfStrings = 0;
    fseek(rFile, 0, SEEK_END);
    size_t size = ftell(rFile);
    char* text = (char*)calloc(ftell(rFile), sizeof(char));
    fseek(rFile, 0, SEEK_SET);
    fread(text, sizeof(char), size, rFile);
    for (size_t i = 0; i<size; i++){
        if (text[i] == '\n') ++numberOfStrings;
    }
    fseek(rFile, 0, SEEK_SET);
    free(text);
    return numberOfStrings;
}

void sortStrings(s_string* stringArray, size_t size){
    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size - i - 1; j++){
            //printf("now %s %s ", stringArray[j].stringArray, stringArray[j+1].stringArray);
            if (needToSwap(stringArray+j, stringArray + j + 1)){
                //printf("need to swap %s %s\n", stringArray[j].stringArray, stringArray[j+1].stringArray);
                mySwap(&stringArray[j], &stringArray[j+1], sizeof(s_string*));
            }
        }
    }
}

int needToSwap(s_string* firstStr, s_string* secondStr){
    if ( /* my_strcmp(firstStr->stringArray, secondStr->stringArray) */ my_strcmp2(firstStr, secondStr) < 0)
        return 1;
    return 0;
}

void printArrayOfStructs(s_string* array, size_t size){
    printf("----------\n");
    for (size_t i = 0; i < size; i++)
        printf("string: %s len: %ld\n", array[i].stringArray, array[i].lenOfStr);\
    printf("----------\n");
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

int my_strcmp2(s_string* firstStr, s_string* secondStr){

    for (size_t i = firstStr->lenOfStr, j = secondStr->lenOfStr; i > 0 && j > 0; i--, j--){
        
        // first str
        if (!isalpha(firstStr->stringArray[i]) && firstStr->stringArray[i] != '\0') { --i; ++j; continue; };

        // second str
        if (!isalpha(secondStr->stringArray[j]) && secondStr->stringArray[j] != '\0') { ++i; --j; continue; };

        // if everithing is fine
        if (tolower(firstStr->stringArray[i]) != tolower(secondStr->stringArray[j])){
            //printf("| %c %c %d\n", firstStr->stringArray[i], secondStr->stringArray[j], (firstStr->stringArray[i]) - tolower(secondStr->stringArray[j]));
            return tolower(firstStr->stringArray[i]) - tolower(secondStr->stringArray[j]);
        }

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

static void mySwap(void* a, void* b, size_t elemMemory){
    assert("mySwap: first element is null pointer" && a != NULL);
    assert("mySwap: second element is null pointer" && b != NULL);
    size_t summ = 0;

    uint64_t* a_long = (uint64_t*)a;
    uint64_t* b_long = (uint64_t*)b;


    while (summ + sizeof(uint64_t) <= elemMemory){

        uint64_t buf = *a_long;
        *a_long = *b_long;
        *b_long = buf;

        a_long += 1;
        b_long += 1;
        summ += sizeof(uint64_t);

    }
    uint32_t* a_int = (uint32_t*)a_long;
    uint32_t* b_int = (uint32_t*)b_long;

    if (summ + sizeof(uint32_t) <= elemMemory){

        uint32_t buf = *a_int;
        *a_int = *b_int;
        *b_int = buf;

        a_int += 1;
        b_int += 1;
        summ += sizeof(uint32_t);

    }

    uint16_t* a_short = (uint16_t*)a_int;
    uint16_t* b_short = (uint16_t*)b_int;

    if (summ + sizeof(uint16_t) <= elemMemory){

        uint16_t buf = *a_short;
        *a_short = *b_short;
        *b_short = buf;

        a_short += 1;
        b_short += 1;
        summ += sizeof(uint16_t);

    }

    uint8_t* a_char = (uint8_t*)a_short;
    uint8_t* b_char = (uint8_t*)b_short;

    if (summ + sizeof(uint8_t) <= elemMemory){

        uint8_t buf = *a_char;
        *a_char = *b_char;
        *b_char = buf;

        a_char += 1;
        b_char += 1;
        summ += sizeof(uint8_t);

    }
}