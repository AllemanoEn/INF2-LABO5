#ifndef INF2_LABO5_HEADING_H
#define INF2_LABO5_HEADING_H


struct Location {
    struct Location* next;
    unsigned int lineNumber;
};

struct Heading{
    struct Heading* next;
    char* word;
    unsigned const wordSize;
    struct Location* lines;
};

struct Heading* createWord(char const word[], unsigned const wordSize, unsigned const lineNb);
struct Heading* findWord(struct Heading *index, char const word[], unsigned const wordSize);
void displayWord(struct Heading *word);
void saveWord(struct Heading *index, struct Heading *word);
void destroyWorld(struct Heading *word, struct Heading *index);

void addLocation(struct Location *locations, unsigned const lineNb); // ajoute au début de la liste

char* to_lower(char word[], unsigned const size);
void displayLines(struct Location *firstLocation); // récursive pour afficher la liste de la fin au début

#endif //INF2_LABO5_HEADING_H
