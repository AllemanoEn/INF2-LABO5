/// \file definition.cpp
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 22.03.2020
///
/// Remarque :
///
/// Compilateur : MinGw-g++ 6.3.0
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "book_index.h"
#include "heading.h"

const int MAX_SIZE_WORD = 3;

/* book_index.h */
void createIndex(const char filename_text[],const char filename_stopword[]){
    char** text = NULL;
    size_t text_lines = 0;
    char** stopwords = NULL;
    size_t stopwords_lines = 0;

    readFile(filename_text, &text, &text_lines);
    readFile(filename_stopword, &stopwords, &stopwords_lines);

    fillIndex(text, text_lines, stopwords, stopwords_lines);

    // Libère la mémoire utilisée par le stockage du texte
    for(size_t i = 0; i < text_lines; ++i)
        free(text[i]);
    for(size_t j = 0; j < stopwords_lines; ++j)
        free(stopwords[j]);

    free(text);
    free(stopwords);
}

struct Heading* findWord(char const word[]){
    if(Heading_index.firstHeading == NULL)
        return NULL;
    struct Heading* ptr = Heading_index.firstHeading;

    while(ptr != NULL && strcmp(word, ptr->word)){
        ptr = ptr->next;
    }

    return ptr;
}


struct Heading *beforeBiggerWord(const char *word) {
    if (Heading_index.firstHeading == NULL)
        return NULL;

    struct Heading *ptr = Heading_index.firstHeading;
    while (ptr->next != NULL) {
        if (strcmp(ptr->next->word, word) > 0) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return ptr;
}

bool binarySearchStopWord(const char *word_to_find, char** stopwords, int lineCount_stopwords){

    int iLePlusPetit = 0;
    int iLePlusGrand = lineCount_stopwords - 1;

    while (iLePlusPetit <= iLePlusGrand) {
        int mid = iLePlusPetit + (iLePlusGrand - iLePlusPetit) / 2;

        if (strcmp(word_to_find,stopwords[mid]) == 0) {
            return true;
        }

        if (strcmp(word_to_find,stopwords[mid]) > 0) {
            iLePlusPetit = mid + 1;
        } else {
            iLePlusGrand = mid - 1;
        }
    }
    return false;
}

void fillIndex(char** text, unsigned const lineCount, char** stopwords, unsigned const swCount){

    const char DELIM[] = "0123456789`~$^+=<>\"!@#&()-[{}]:;',?/*. \n";
    for(size_t i = 0; i < lineCount; ++i)
    {
        char* token = strtok(text[i], DELIM);
        printf("%d/%d\n", i, lineCount); // test
        while(token != NULL){
            unsigned tokenLength = strlen(token);
            token = to_lower(token, tokenLength);
            if(!binarySearchStopWord(token, stopwords, swCount)){
                struct Heading *word = createWord(token, tokenLength, i);
                saveWord(word);
            }

            token = strtok(NULL, DELIM);
        }

    }
}

void printIndex(FILE* stream){
    struct Heading* ptr = Heading_index.firstHeading;

    if(ptr == NULL){
        return;
    }

    do
    {
        displayWord(ptr, stream);
        fprintf(stream, ", ");
        displayLines(ptr->lines, stream, true);
        ptr = ptr->next;
        fprintf(stream,"\n");
    } while(ptr != NULL );

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
    for(unsigned i = 0; i < count; ++i){

        fgets (linestr , 100 , file); // récupération de la ligne

        unsigned lineSize = strlen(linestr);
        if(lineSize != 0 && linestr[lineSize - 1] == '\n'){
            linestr[lineSize - 1] = '\0';
            lineSize--;
        }

        char* l = malloc(sizeof(char) * lineSize + 1); // allocation de la mémoire
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
    loc->lineNumber = lineNb;

    size_t headingSize = sizeof(struct Heading);
    struct Heading* wordHeading = malloc(headingSize);
    wordHeading->word = word;
    wordHeading->wordSize = wordSize;
    wordHeading->lines = loc;

    return wordHeading;
}

void displayWord(struct Heading *word, FILE* stream){
    fprintf(stream,"%s",word->word);
}

void saveWord(struct Heading *word) {

    //Ne prend pas en compte les mots de moins de  MAX_SIZE_WORD lettress
    if (strlen(word->word) < MAX_SIZE_WORD)
        return;

    //Si premier mot de la liste, on l'ajoute
    if (Heading_index.firstHeading == NULL) {
        Heading_index.firstHeading = word;
        return;
    }

    //On pourrait se passer des deux conditions suivantes avec un avant_premier
    //On test le premier mot
    //si c'est le mot, on lui ajoute la ligne
    if (strcmp(Heading_index.firstHeading->word, word->word) == 0) {
        addLocation(&(Heading_index.firstHeading->lines), word->lines->lineNumber);
        destroyWord(word);
        return;
    }
    //s'il est plus grand, on doit mettre le nouveau mot au début
    if (strcmp(Heading_index.firstHeading->word, word->word) > 0) {
        word->next = Heading_index.firstHeading;
        Heading_index.firstHeading = word;
        return;
    }
    //Si le mot est déjà dedans, on ajoute simplement la ligne
    struct Heading *wordPos = beforeBiggerWord(word->word);
    if (strcmp(word->word, wordPos->word) == 0) {
        addLocation(&(wordPos->lines), word->lines->lineNumber);
        destroyWord(word);
        return;
    }
    word->next = wordPos->next;
    wordPos->next = word;
}


void addLocation(struct Location** locations, unsigned const lineNb){

    if ((*locations)->lineNumber == lineNb)
        return;

    size_t locSize = sizeof(struct Location);
    struct Location* loc = malloc(locSize * 2);
    loc->lineNumber = lineNb;
    loc->next = *locations;

    *locations = loc;
}

char* to_lower(char word[], unsigned const size){
    char* temp = malloc(sizeof(char)*size);
    for (unsigned i = 0; i < size + 1; ++i) {
        *(temp+i) = (char) tolower(word[i]);
    }
    return temp;
}

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
