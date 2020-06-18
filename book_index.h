#ifndef INF2_LABO5_BOOK_INDEX_H
#define INF2_LABO5_BOOK_INDEX_H

#include "heading.h"

struct {
    struct Heading* firstHeading;
} Heading_index;

void createIndex(const char filename_text[],const char filename_index[],const char filename_stopword[]);
struct Heading* findWord(char const word[], unsigned const wordSize);
void fillIndex(char** text, unsigned const lineCount);
void destroyIndex();
void destroyList(struct Heading* word);

void printIndex(FILE* stream); // Affiche ou écrit l'index en fonction du stream passé en paramètre
void displayIndex();
void saveIndex(char const filename[]);

void readFile(const char filename[], char*** dest, size_t *lineNb);

#endif //INF2_LABO5_BOOK_INDEX_H
