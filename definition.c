#include <string.h>
#include <stdio.h>
#include "book_index.h"
#include "heading.h"





/* book_index.h */
struct Heading* createIndex(const char filename[], unsigned const size){}
struct Heading* findWord(struct Heading *index, char const word[], unsigned const wordSize){}

void fillIndex(struct Heading* index, const char text[], unsigned const txtSize){
    char str[] = "Test 123 Test\nBonjour";
    const char DELIM[] = "0123456789`~$^+=<>“!@#&()–[{}]:;',?/*";// "0123456789`~$^+=<>“!@#&()–[{}]:;',?/* \n";
    char* token = strtok(str, DELIM);
    unsigned count = 0;
    while(token != NULL){
        if(strlen(token) > 2);{
            // find le mot
            createWord(token, strlen(token),0);
        }

        token = strtok(NULL, DELIM);

    }

}

void test(){
    char str[] = "The five boxing\n"
                 "wizards jump quickly.\n"
                 "Pack my box with five\n"
                 "dozen liquor jugs.";

    const char DELIM[] = "0123456789`~$^+=<>“!@#&()–[{}]:;',?/* \n";// "0123456789`~$^+=<>“!@#&()–[{}]:;',?/* \n";
    const char LINE[] = "\n";
    char* line = strtok(str, LINE);

    unsigned lineCount = 0;

    while(line != NULL){

        //char* token = strtok(line, DELIM);
        printf("%s , l=%d\n", line, lineCount);
        /*while(token != NULL){
            printf("%s , l=%d\n", token, lineCount);
            token = strtok(NULL, DELIM);
        }/*/
        line = strtok(NULL, LINE);
        lineCount++;
    }

    while(line != NULL){

        //char* token = strtok(line, DELIM);
        printf("%s , l=%d\n", line, lineCount);
        /*while(token != NULL){
            printf("%s , l=%d\n", token, lineCount);
            token = strtok(NULL, DELIM);
        }/*/
        line = strtok(NULL, LINE);
        lineCount++;
    }


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