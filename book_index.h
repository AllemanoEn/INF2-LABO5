#ifndef INF2_LABO5_BOOK_INDEX_H
#define INF2_LABO5_BOOK_INDEX_H

#include "heading.h"

struct {
    struct Heading* firstHeading;
} Heading_index;

struct Heading* createIndex(const char filename[], unsigned const size);
struct Heading* findWord(struct Heading *index, char const word[], unsigned const wordSize);
void fillIndex(const char** text, unsigned const lineCount);
void displayIndex();
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize);

void test();


void readFile(const char filename[], char*** dest, size_t *lineNb);

#endif //INF2_LABO5_BOOK_INDEX_H
