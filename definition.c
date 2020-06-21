<<<<<<< HEAD
/// \file definition.cpp
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 22.03.2020
///
/// Remarque :
///
/// Compilateur : MinGw-g++ 6.3.0
=======
/// \file definition.c
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 19.06.2020
///
/// Compilateur : MinGw-g++ 6.3.0


>>>>>>> master
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "book_index.h"
#include "heading.h"

const size_t MAX_SIZE_WORD = 3;


/*  ---------- book_index.h ---------- */

void createIndex(const char filename_text[],const char filename_stopword[]){

    char** text = NULL;
    size_t text_lines = 0;
    readFile(filename_text, &text, &text_lines);

    char** stopwords = NULL;
    size_t stopwords_lines = 0;
    readFile(filename_stopword, &stopwords, &stopwords_lines);


    fillIndex(text, text_lines, stopwords, stopwords_lines);


    // Libère la mémoire utilisée par le stockage du texte et des stopwords
    for(size_t i = 0; i < text_lines; ++i)
        free(text[i]);
    for(size_t j = 0; j < stopwords_lines; ++j)
        free(stopwords[j]);

    free(text);
    free(stopwords);
}

void fillIndex(char** text, size_t const lineCount, char** stopwords, size_t const swCount){

    const char DELIM[] = "0123456789`~$^+=<>\"!@#&()-[{}]:;',?/*. \n";

    for(size_t i = 0; i < lineCount; ++i)
    {
        char* token = strtok(text[i], DELIM);

        while(token != NULL){ // Pour chaque mot de la ligne

            token = to_lower(token, strlen(token));

            if(!binarySearchStopWord(token, stopwords, (int)swCount)){
                // On crée le Heading seulement si le mot n'est pas un stopword
                struct Heading *word = createWord(token, i);
                saveWord(word);
            }
            token = strtok(NULL, DELIM);
        }
    }
}

void destroyIndex(){
    destroyList(heading_index.firstHeading);
}

void destroyList(struct Heading* word) {
    if(word->next != NULL){
        destroyList(word->next);
        destroyWord(word);
    }
}

void printIndex(FILE* stream){

    struct Heading* ptr = heading_index.firstHeading;

    if(ptr == NULL){
        return;
    }

    do // Affiche le mot et les lignes de chaque heading
    {
        displayWord(ptr, stream);
        fprintf(stream, ", ");
        displayLines(ptr->lines, stream, true);
        fprintf(stream,"\n");

        ptr = ptr->next;

    } while(ptr != NULL );

}

void displayIndex(){
    printIndex(stdout);
}

void saveIndex(char const filename[]){

    FILE* file = fopen(filename, "w");

    if(file == NULL){
        perror(filename);
        return;
    }
    printIndex(file);

    fclose(file);

}

void readFile(const char filename[], char*** dest, size_t* lineNb){

    FILE* file;
    #define LINE_MAX_LENGTH 100

    char linestr [LINE_MAX_LENGTH];


    file = fopen (filename , "r");

    if(file == NULL)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }


    // Comptage des lignes
    unsigned count = 1;
    char c = (char)getc(file);

    while(c != EOF)
    {
        if(c == '\n')
            ++count;
        c = (char)getc(file);
    }

    rewind(file);

    // Stockage de chaque ligne dans le tableau de pointeurs t
    char** t = malloc(sizeof(char*) * count);

    for(size_t i = 0; i < count; ++i){

        fgets (linestr , LINE_MAX_LENGTH , file); // récupération de la ligne

        size_t lineSize = strlen(linestr);
        if(lineSize != 0 && linestr[lineSize - 1] == '\n'){
            // Suppression du caractère de fin de ligne
            linestr[lineSize - 1] = '\0';
            --lineSize;
        }

        char* l = malloc(sizeof(char) * lineSize + 1);

        strcpy(l, linestr); // copie des données
        t[i] = l;
    }

    *dest = t;
    *lineNb = count;
}

struct Heading* findWord(char const word[]){

    if(heading_index.firstHeading == NULL)
        return NULL;

    struct Heading* ptr = heading_index.firstHeading;

    while(ptr != NULL && strcmp(word, ptr->word) != 0){
        ptr = ptr->next;
    }

    return ptr;
}

struct Heading* beforeBiggerWord(const char *word) {

    if (heading_index.firstHeading == NULL)
        return NULL;

    // Boucle jusqu'à s'arrêter avant le premier mot plus grand que word
    struct Heading *ptr = heading_index.firstHeading;
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



/* ---------- heading.h ---------- */

struct Heading* createWord(char word[], size_t const lineNb){

    struct Location* loc = malloc(sizeof(struct Location));
    loc->lineNumber = lineNb;

    struct Heading* wordHeading = malloc(sizeof(struct Heading));
    wordHeading->word = word;
    wordHeading->lines = loc;

    return wordHeading;
}

void addLocation(struct Location** locations, size_t const lineNb){

    // Pas d'ajout si la ligne est déjà présente dans la liste
    if ((*locations)->lineNumber == lineNb)
        return;

    // Ajoute la Location au début de la chaîne
    size_t locSize = sizeof(struct Location);
    struct Location* loc = malloc(locSize * 2);
    loc->lineNumber = lineNb;
    loc->next = *locations;

    *locations = loc;
}

void saveWord(struct Heading *word) {

    // Ne prend pas en compte les mots de moins de MAX_SIZE_WORD lettres
    if (strlen(word->word) < MAX_SIZE_WORD)
        return;

    // Si c'est le premier mot de la liste, on l'ajoute
    if (heading_index.firstHeading == NULL) {
        heading_index.firstHeading = word;
        return;
    }

    // On pourrait se passer des deux conditions suivantes avec un avant_premier
    // On test le premier mot
    // Si c'est le mot, on lui ajoute la ligne
    if (strcmp(heading_index.firstHeading->word, word->word) == 0) {
        addLocation(&(heading_index.firstHeading->lines), word->lines->lineNumber);
        destroyWord(word);
        return;
    }

    // S'il est plus grand, on doit mettre le nouveau mot au début
    if (strcmp(heading_index.firstHeading->word, word->word) > 0) {
        word->next = heading_index.firstHeading;
        heading_index.firstHeading = word;
        return;
    }

    // Si le mot est déjà dedans, on ajoute simplement la ligne
    struct Heading *wordPos = beforeBiggerWord(word->word);
    if (strcmp(word->word, wordPos->word) == 0) {
        addLocation(&(wordPos->lines), word->lines->lineNumber);
        destroyWord(word);
        return;
    }
    word->next = wordPos->next;
    wordPos->next = word;
}

void displayWord(struct Heading *word, FILE* stream){
    fprintf(stream,"%s",word->word);
}

void displayLines(struct Location *firstLocation, FILE* stream, bool isFirstDisplayedLine){

    if(firstLocation == NULL)
        return;

    // Affiche les lignes depuis la fin de la chaîne vers le début
    displayLines(firstLocation->next, stream,false);
    fprintf(stream,"%u", (unsigned)firstLocation->lineNumber + 1);

    if(!isFirstDisplayedLine)
        fprintf(stream,", ");

}

char* to_lower(char word[], size_t const size){

    char* low = malloc(sizeof(char) * size);

    for (unsigned i = 0; i < size + 1; ++i) {
        low[i] = (char) tolower(word[i]);
    }
    return low;
}

void destroyWord(struct Heading *word){
    free(word->word);
    destroyLocations(word->lines);
    free(word->lines);
    free(word);
}

void destroyLocations(struct Location *loc) {
    if (loc->next == NULL)
        return;

    // Détruit les maillons de la chaîne depuis la fin
    destroyLocations(loc->next);
    free(loc->next);
}
