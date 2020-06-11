#include "book_index.h"
#include "heading.h"





/* book_index.h */
struct Heading* createIndex(const char filename[], unsigned const size);
struct Heading* findWord(struct Heading *index, char const word[], unsigned const wordSize);
void fillIndex(struct Heading* index, const char text[], unsigned const txtSize);
void displayIndex(struct Heading* index);
void saveIndex(struct Heading* index, char const filename[], unsigned const fnSize);










/* heading.h */
struct Heading* createWord(char const word[], unsigned const wordSize, unsigned const lineNb);

void displayWord(struct Heading *word);
void saveWord(struct Heading *index, struct Heading *word);
void destroyWord(struct Heading *word, struct Heading *index);

void addLocation(struct Location *locations, unsigned const lineNb); // ajoute au début de la liste

char* to_lower(char word[], unsigned const size); // transforme tous les caractères en minuscule
void displayLines(struct Location *firstLocation); // récursive pour afficher la liste de la fin au début