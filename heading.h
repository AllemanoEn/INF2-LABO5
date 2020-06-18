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
    unsigned wordSize;
    struct Location* lines;
};

/**
 * Crée un nouveau heading dont le prochain heading et null avec son mot,
 * la taille de son mot et son numéro de ligne
 * @param word mot
 * @param wordSize taille du mot
 * @param lineNb sa ligne
 * @return un heading dont le prochain heading et null avec son mot,
 * la taille de son mot et son numéro de ligne
 */
struct Heading* createWord(char word[], unsigned const wordSize, unsigned const lineNb);

/**
 * Affiche le mot du Heading dand le flux
 * @param word
 * @param stream
 */
void displayWord(struct Heading *word, FILE* stream);

/**
 * Place un mot dans la chaîne de heading au bon endroit dans l'ordre alphabétique
 * Si le mot est déjà contenu dans la chaîne, place une nouvelle location dans ce mot
 * @param word Le premier Heading d'une chaîne de heading
 */
void saveWord(struct Heading *word);

/**
 * Détruit la chaîne de Heading (avec les locations)
 * @param word premier Heading
 */
void destroyWord(struct Heading *word);

/**
 * Détruit la chaîne de location
 * @param loc la première location
 */
void destroyLocations(struct Location *loc);

/**
 * Ajoute une nouvelle location au début d'une liste chaînée de locations
 * si la ligne de la première location n'est pas la même.
 * @param locations nouvelle location
 * @param lineNb numéro de la nouvelle ligne
 */
void addLocation(struct Location* *locations, unsigned const lineNb); // ajoute au début de la liste

/**
 * Met une chaîne de caractères en minuscule
 * @param word le mot à mettre en minuscule
 * @param size la taille de la chaîne
 * @return la chaîne avec toute les lettre en minuscule
 */
char* to_lower(char word[], unsigned const size); // transforme tous les caractères en minuscule

/**
 * Affiche les lignes de la chaîne location, en commencant par la dernière location
 * de la liste chaînée. (normalement la dernière location à la ligne la plus faible.
 * @param firstLocation la première location de la chaîne.
 * @param stream le flux
 * @param isFirstDisplayedLine si c'est la ligne de dernière location, pas de virgule
 */
void displayLines(struct Location *firstLocation, FILE* stream, bool isFirstDisplayedLine);

#endif //INF2_LABO5_HEADING_H
