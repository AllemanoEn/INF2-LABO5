#ifndef INF2_LABO5_BOOK_INDEX_H
#define INF2_LABO5_BOOK_INDEX_H

#include "heading.h"

struct {
    struct Heading* firstHeading;
} Heading_index;

void createIndex(const char filename_text[],const char filename_stopword[]);
struct Heading* findWord(char const word[], unsigned const wordSize);

/**
 * Crée l'index à partir du fichier donné
 * @param filename_text : le fichier texte à ouvrir
 * @param filename_stopword : fichier de mots blacklistés
 */
void createIndex(const char filename_text[],const char filename_stopword[]);

/**
 * Cherche un mot dans l'index
 * @param word : mot à rechercher
 * @param wordSize : taille du mot recherché
 * @return pointeur vers le mot trouvé ou NULL si le mot n'existe pas
 */
struct Heading* findWord(char const word[], unsigned const wordSize); // todo: wordSize pas nécessaire

/**
 * Remplit un index vide avec les mots du texte passé en paramètre
 * @param text : tableau de chaînes de caractères, chacune correspondant à une ligne dans un texte
 * @param lineCount : nombre de lignes du texte
 * @details Crée un Heading pour chaque mot du texte.Le texte est passé sous forme de tableau de char*
 * afin de pouvoir compter facilement la ligne lorsqu'un mot est traité
 */
void fillIndex(char** text, unsigned const lineCount);

/**
 * Libère la mémoire allouée à l'ensemble de l'index
 * @details Ne fait qu'appeler la fonction destroyList à partir du début de la liste chaînée
 */
void destroyIndex();

/**
 * Détruit tous les Headings à partir d'un maillon d'une liste chaînée
 * @param word : Début de la liste de Headings à supprimer
 */
void destroyList(struct Heading* word);

/**
 * Ecrit l'index dans le flux de sortie
 * @param stream : flux de sortie
 * @details : par exemple, on passe stdout pour afficher dans la console, ou un flux de fichier pour y écrire
 */
void printIndex(FILE* stream); // Affiche ou écrit l'index en fonction du stream passé en paramètre

/**
 *
 */
void displayIndex();
void saveIndex(char const filename[]);

void readFile(const char filename[], char*** dest, size_t *lineNb);

#endif //INF2_LABO5_BOOK_INDEX_H
