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

void displayIndex(struct Heading* index){}
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize){}



char** readFile(const char filename[]){
    FILE *file;
    file = fopen(filename, "r");
    if(file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    char line[60];
    unsigned count = 0;

    /*while(line != EOF)
    {
        fgets(line, -1u, file);
        ++count;
    }*/
    for (char c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    char** tab = malloc(count * sizeof(char*));

    for(int i = 0; i < count; ++i){
        tab[i] = fgets(line, -1u, file);
        printf("%s\n", tab[i]);
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