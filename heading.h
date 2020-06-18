/// \file heading.h
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 18.06.2020
///
/// \brief \b Laboratoire \b 06
/// \brief Contient les prototypes heading
///
/// Remarque :
///
/// Compilateur : MinGw-g++ 6.3.0
#ifndef INF2_LABO5_HEADING_H
#define INF2_LABO5_HEADING_H
#include <stdbool.h>

struct Location {
    struct Location* next;
    unsigned int lineNumber;
};

struct Heading {
    struct Heading* next;
    char* word;
    unsigned const wordSize;
    struct Location* lines;
};

struct Heading* createWord(char word[], unsigned const wordSize, unsigned const lineNb);

void displayWord(struct Heading *word, FILE* stream);
void saveWord(struct Heading *word);
void destroyWord(struct Heading *word);
void destroyLocations(struct Location *loc);

void addLocation(struct Location* *locations, unsigned const lineNb); // ajoute au début de la liste

char* to_lower(char word[], unsigned const size); // transforme tous les caractères en minuscule
void displayLines(struct Location *firstLocation, FILE* stream, bool isFirstDisplayedLine);

#endif //INF2_LABO5_HEADING_H
