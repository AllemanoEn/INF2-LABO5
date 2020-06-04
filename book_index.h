#ifndef INF2_LABO5_BOOK_INDEX_H
#define INF2_LABO5_BOOK_INDEX_H

#include "heading.h"

struct Heading* createIndex(const char filename[], unsigned const size);
void fillIndex(struct Heading* index, const char text[], unsigned const txtSize);
void displayIndex(struct Heading* index);
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize);




#endif //INF2_LABO5_BOOK_INDEX_H
