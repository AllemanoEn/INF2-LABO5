/// \file heading.h
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 19.06.2020
///
/// Compilateur : MinGw-g++ 6.3.0


#ifndef INF2_LABO5_HEADING_H
#define INF2_LABO5_HEADING_H
#include <stdbool.h>

struct Location {
    size_t lineNumber;
    struct Location* next;
};

struct Heading {
    struct Heading* next;
    struct Location* lines;
    char* word;
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
struct Heading* createWord(char word[], size_t const lineNb);

/**
 * Ajoute une nouvelle location au début d'une liste chaînée de locations
 * si la ligne de la première location n'est pas la même.
 * @param locations nouvelle location
 * @param lineNb numéro de la nouvelle ligne
 */
void addLocation(struct Location* *locations, size_t const lineNb); // ajoute au début de la liste

/**
 * Place un mot dans la chaîne de heading au bon endroit dans l'ordre alphabétique
 * Si le mot est déjà contenu dans la chaîne, place une nouvelle location dans ce mot
 * @param word Le premier Heading d'une chaîne de heading
 */
void saveWord(struct Heading *word);

/**
 * Affiche le mot du Heading dand le flux
 * @param word
 * @param stream
 */
void displayWord(struct Heading *word, FILE* stream);

/**
 * Affiche les lignes de la chaîne location, en commencant par la dernière location
 * de la liste chaînée. (normalement la dernière location à la ligne la plus faible.
 * @param firstLocation la première location de la chaîne.
 * @param stream le flux
 * @param isFirstDisplayedLine si c'est la ligne de dernière location, pas de virgule
 */
void displayLines(struct Location *firstLocation, FILE* stream, bool isFirstDisplayedLine);

/**
 * Met une chaîne de caractères en minuscule
 * @param word le mot à mettre en minuscule
 * @param size la taille de la chaîne
 * @return la chaîne avec toute les lettre en minuscule
 */
char* to_lower(char word[], size_t const size); // transforme tous les caractères en minuscule

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

#endif //INF2_LABO5_HEADING_H
