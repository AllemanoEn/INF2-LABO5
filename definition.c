#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "book_index.h"
#include "heading.h"





/* book_index.h */
struct Heading* createIndex(const char filename[], unsigned const size){}
struct Heading* findWord(struct Heading *index, char const word[], unsigned const wordSize){}

void fillIndex(struct Heading* index, const char** text, unsigned const lineCount){

    const char DELIM[] = "0123456789`~$^+=<>“!@#&()–[{}]:;',?/* \n";
    for(int i = 0; i < lineCount; ++i)
    {
        char* token = strtok(text[i], DELIM);

        while(token != NULL){
            printf("%s , l=%d\n", token, i);
            token = strtok(NULL, DELIM);
        }
        printf("\n------------------------------\n");

    }
}

void test(){
    const size_t lineCount = 2;
    char l1[] = "The five boxing\n"
                "wizards jump quickly.\n"
                "Pack my box with five\n"
                "dozen liquor jugs.";
    char l2[] = "Test 123 456";

    char* str[] = { l1, l2 } ;
    const char DELIM[] = "0123456789`~$^+=<>“!@#&()–[{}]:;',?/* \n";
    for(int i = 0; i < lineCount; ++i)
    {
        char* token = strtok(str[i], DELIM);

        while(token != NULL){
            printf("%s , l=%d\n", token, i);
            token = strtok(NULL, DELIM);
        }
        printf("\n------------------------------\n");

    }



    /*const char DELIM[] = "0123456789`~$^+=<>“!@#&()–[{}]:;',?/* \n";
    const char LINE[] = "\n";
    char* line = str;
    char* linetok = strtok(line, LINE);
    unsigned lineCount = 0;

    while(line != NULL){

        char* token = malloc(sizeof(char*));
        token = strtok(linetok, DELIM);

        while(token != NULL){
            printf("%s , l=%d\n", token, lineCount);
            token = strtok(NULL, DELIM);
        }

        line = strchr(line, '\n');
        linetok = strtok(line, LINE);
        lineCount++;
    }*/


}
void displayIndex(struct Heading* index){}
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize){}










/* heading.h */
struct Heading* createWord(char const word[], unsigned const wordSize, unsigned const lineNb){

}

void displayWord(struct Heading *word){}
void saveWord(struct Heading *index, struct Heading *word){}
void destroyWord(struct Heading *word, struct Heading *index){}

void addLocation(struct Location *locations, unsigned const lineNb){} // ajoute au début de la liste

char* to_lower(char word[], unsigned const size){} // transforme tous les caractères en minuscule
void displayLines(struct Location *firstLocation){} // récursive pour afficher la liste de la fin au début