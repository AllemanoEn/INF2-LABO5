#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "book_index.h"
#include "heading.h"





/* book_index.h */
struct Heading* createIndex(const char filename[], unsigned const size){}
struct Heading* findWord(struct Heading *index, char const word[], unsigned const wordSize){}

void fillIndex(const char** text, unsigned const lineCount){

    const char DELIM[] = "0123456789`~$^+=<>“!@#&()–[{}]:;',?/* \n";
    for(int i = 0; i < lineCount; ++i)
    {
        char* token = strtok(text[i], DELIM);

        while(token != NULL){
            //printf("%s , l=%d\n", token, i);
            struct Header *word = createWord(token, strlen(token), i);
            saveWord(word);
            token = strtok(NULL, DELIM);
        }

    }
}

void displayIndex(struct Heading* index){}
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize){}



void readFile(const char filename[], char*** dest, size_t *lineNb){
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

    // stockage de chaque ligne dans le tableau de pointeurs t
    char** t = malloc(sizeof(char*) * count);
    for(int i = 0; i < count; ++i){

        fgets (linestr , 100 , file); // récupération de la ligne

        char* l = malloc(sizeof(char) * strlen(linestr) + 1); // allocation de la mémoire
        // remarque: le "+1" sert à éviter une erreur (https://zestedesavoir.com/forums/sujet/10773/erreur-dans-realloc-sysmalloc-assertion-failed/)

        strcpy(l, linestr); // copie des données
        t[i] = l;
    }

    *dest = &t;
    *lineNb = count;

}

/* heading.h */
struct Heading* createWord(char const word[], unsigned const wordSize, unsigned const lineNb){

    size_t locSize = sizeof(unsigned) + sizeof(struct Location*);
    struct Location* loc = malloc(locSize);
    struct Location locStack = {NULL, lineNb};
    memcpy(loc, &locStack, locSize);

    size_t headingSize = sizeof(struct Header*) +
                         sizeof(char) * wordSize +
                         sizeof(unsigned)  +
                         sizeof(struct Location*);
    struct Heading* wordHeading = malloc(headingSize);
    struct Heading WordStack = { NULL, word, wordSize, &loc};
    memcpy(wordHeading, &WordStack, headingSize);

    return wordHeading;
}

void displayWord(struct Heading *word){}
void saveWord(struct Heading *word){
    printf("Mot: %s\n", word->word);
}
void destroyWord(struct Heading *word, struct Heading *index){}

void addLocation(struct Location *locations, unsigned const lineNb){} // ajoute au début de la liste

char* to_lower(char word[], unsigned const size){
    char* temp = malloc(sizeof(char)*size);//Attention, il faudra free après
    for (unsigned i = 0; i < size; ++i) {
        *(temp+i) = (char) tolower(word[i]);
    }
    return temp;
} // transforme tous les caractères en minuscule

void displayLines(struct Location *firstLocation){} // récursive pour afficher la liste de la fin au début