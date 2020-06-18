#ifndef INF2_LABO5_BOOK_INDEX_H
#define INF2_LABO5_BOOK_INDEX_H

#include "heading.h"

struct {
    struct Heading* firstHeading;
} Heading_index;

void createIndex(const char filename[]);
struct Heading* findWord(char const word[], unsigned const wordSize);
void fillIndex(char** text, unsigned const lineCount);
void displayIndex();
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize);


void readFile(const char filename[], char*** dest, size_t *lineNb);

#endif //INF2_LABO5_BOOK_INDEX_H
