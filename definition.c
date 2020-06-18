#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "book_index.h"
#include "heading.h"



/* book_index.h */
void createIndex(const char filename_text[],const char filename_index[],const char filename_stopword[]){
    char** text = NULL;
    size_t lines = 0;

    readFile(filename_text, &text, &lines);
    fillIndex(text, lines);

    // Libère la mémoire utilisée par le stockage du texte
    for(size_t i = 0; i < lines; ++i)
        free(text[i]);
    free(text);
}

struct Heading* findWord(char const word[], unsigned const wordSize){
    if(Heading_index.firstHeading == NULL)
        return NULL;
    struct Heading* ptr = Heading_index.firstHeading;

    while(ptr != NULL && strcmp(word, ptr->word)){
        ptr = ptr->next;
    }

    return ptr;
}

void fillIndex(char** text, unsigned const lineCount){

    const char DELIM[] = "0123456789`~$^+=<>“!@#&()–[{}]:;',?/*. \n";
    for(int i = 0; i < lineCount; ++i)
    {
        char* token = strtok(text[i], DELIM);

        while(token != NULL){
            struct Header *word = createWord(token, strlen(token), i);
            saveWord(word);

            token = strtok(NULL, DELIM);
        }

    }
}

void printIndex(FILE* stream){
    struct Heading* ptr = Heading_index.firstHeading;

    while(ptr->next != NULL )
    {
        displayWord(ptr, stream);
        fprintf(stream, ", ");
        displayLines(ptr->lines, stream, true);
        ptr = ptr->next;
        fprintf(stream,"\n");
    }

}

void displayIndex(){
    printIndex(stdout);
}

void saveIndex(char const filename[]){

    FILE* file = fopen(filename, "w");
    if(file == NULL)
    {
        perror("Error ");
        return;
    }
    printIndex(file);
    fclose(file);

}

void readFile(const char filename[], char*** dest, size_t* lineNb){
    FILE * file;
    char linestr [100];

    file = fopen (filename , "r");

    if(file == NULL)
    {
        perror("Error ");
        exit(EXIT_FAILURE);
    }


    // comptage des lignes
    unsigned count = 1;
    char c = (char)getc(file);
    while(c != EOF)
    {
        if(c == '\n')
            ++count;
        c = (char)getc(file);
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

    *dest = t;
    *lineNb = count;
}


void destroyIndex(){
    destroyList(Heading_index.firstHeading);
}

void destroyList(struct Heading* word) {

    if(word->next != NULL){
        destroyList(word->next);
        destroyWord(word);
    }
}



/* heading.h */
struct Heading* createWord(char word[], unsigned const wordSize, unsigned const lineNb){

    size_t locSize = sizeof(struct Location);
    struct Location* loc = malloc(locSize);
    struct Location locStack = {NULL, lineNb};
    memcpy(loc, &locStack, locSize);

    size_t headingSize = sizeof(struct Heading);
    struct Heading* wordHeading = malloc(headingSize);

    struct Heading WordStack = {NULL, to_lower(word, wordSize), wordSize, loc};
    memcpy(wordHeading, &WordStack, headingSize);

    return wordHeading;
}

void displayWord(struct Heading *word, FILE* stream){
    fprintf(stream,"%s",word->word);
}

void saveWord(struct Heading *word){
    if(strlen(word->word) < 3)
        return;

    if(Heading_index.firstHeading == NULL)
    {
        Heading_index.firstHeading = word;
        return;
    }

    struct Heading* wordPos = findWord(word->word, word->wordSize);
    if(wordPos != NULL)
    {
       addLocation(&(wordPos->lines), word->lines->lineNumber);
       return;
    }

    struct Heading* ptr = Heading_index.firstHeading;

    while(ptr->next != NULL ) { // positionne le pointeur sur le dernier Heading
        ptr = ptr->next;
    }

    ptr->next = word;
}

void addLocation(struct Location** locations, unsigned const lineNb){
    size_t locSize = sizeof(struct Location);
    struct Location* loc = (struct Location*) malloc(locSize);
    loc->lineNumber = lineNb;
    loc->next = *locations;

    *locations = loc;
}

char* to_lower(char word[], unsigned const size){
    char* temp = malloc(sizeof(char)*size); //Attention, il faudra free après
    for (unsigned i = 0; i < size + 1; ++i) {
        *(temp+i) = (char) tolower(word[i]);
    }
    return temp;
} // transforme tous les caractères en minuscule

void displayLines(struct Location *firstLocation, FILE* stream, bool isFirstDisplayedLine){

    if(firstLocation == NULL)
        return;

    displayLines(firstLocation->next, stream,false);
    fprintf(stream,"%d", firstLocation->lineNumber + 1);
    if(!isFirstDisplayedLine)
        fprintf(stream,", ");

}


void destroyWord(struct Heading *word){
    free(word->word);
    destroyLocations(word->lines);
    free(word->lines);
    free(word);
}

void destroyLocations(struct Location *loc) {

    if (loc->next != NULL) {
        destroyLocations(loc->next);
        free(loc->next);
    }

}

