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

    }
}

void displayIndex(struct Heading* index){}
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize){}



void readFile(const char filename[], char** dest, size_t *lineNb){
    FILE * file;
    char linestr [100];

    file = fopen (filename , "r");

    if(file == NULL)
        exit(EXIT_FAILURE);

    // comptage des lignes
    unsigned count = 0;
    char c = getc(file);
    while(c != EOF)
    {
        if(c == '\n')
            ++count;
        c = getc(file);
    }

    rewind(file);

    char** t = malloc(sizeof(char*) * count);
    for(int i = 0; i < count; ++i){
        unsigned linelen = strlen(linestr);
        fgets (linestr , 100 , file);
        char* l = malloc(sizeof(char) * strlen(linestr));
        strcpy(l, linestr);
        t[i] = l;
    }


    dest = t;
    lineNb = count;

    test(t, lineNb);


}
void test(const char** text, unsigned const lineCount){

    const char DELIM[] = "0123456789`~$^+=<>“!@#&()–[{}]:;',?/* \n";

    for(int i = 0; i < lineCount; ++i) {
        char *token = strtok(text[i], DELIM);

        while (token != NULL) {
            printf("%s , l=%d\n", token, i);
            token = strtok(NULL, DELIM);
        }
    }
}




/* heading.h */
struct Heading* createWord(char const word[], unsigned const wordSize, unsigned const lineNb){

}

void displayWord(struct Heading *word){}
void saveWord(struct Heading *index, struct Heading *word){}
void destroyWord(struct Heading *word, struct Heading *index){}

void addLocation(struct Location *locations, unsigned const lineNb){} // ajoute au début de la liste

char* to_lower(char word[], unsigned const size){} // transforme tous les caractères en minuscule
void displayLines(struct Location *firstLocation){} // récursive pour afficher la liste de la fin au début