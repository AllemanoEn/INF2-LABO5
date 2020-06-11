#ifndef INF2_LABO5_BOOK_INDEX_H
#define INF2_LABO5_BOOK_INDEX_H

#include "heading.h"

struct {
    struct Heading* firstHeading;
} Index;

struct Heading* createIndex(const char filename[], unsigned const size);
struct Heading* findWord(struct Heading *index, char const word[], unsigned const wordSize);
void fillIndex(struct Heading* index, const char** text, unsigned const lineCount);
void displayIndex(struct Heading* index);
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize);

void test();

char** readFile(const char filename[]);

#endif //INF2_LABO5_BOOK_INDEX_H
