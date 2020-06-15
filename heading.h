#ifndef INF2_LABO5_HEADING_H
#define INF2_LABO5_HEADING_H

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

void displayWord(struct Heading *word);
void saveWord(struct Heading *word);
void destroyWord(struct Heading *word, struct Heading *index);

void addLocation(struct Location *locations, unsigned const lineNb); // ajoute au début de la liste

char* to_lower(char word[], unsigned const size); // transforme tous les caractères en minuscule
void displayLines(struct Location *firstLocation); // récursive pour afficher la liste de la fin au début

#endif //INF2_LABO5_HEADING_H
