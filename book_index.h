#ifndef INF2_LABO5_BOOK_INDEX_H
#define INF2_LABO5_BOOK_INDEX_H

#include "heading.h"



struct {
    struct Heading* firstHeading;
} Heading_index;


/**
 * Crée l'index à partir du fichier donné
 * @param filename_text : le fichier texte à ouvrir
 * @param filename_stopword : fichier de mots blacklistés
 */
void createIndex(const char filename_text[],const char filename_stopword[]);

/**
 * Cherche un mot dans l'index
 * @param word : mot à rechercher
 * @return pointeur vers le mot trouvé ou NULL si le mot n'existe pas
 */
struct Heading* findWord(char const word[]);

/**
 * Remplit un index vide avec les mots du texte passé en paramètre
 * @param text : tableau de chaînes de caractères, chacune correspondant à une ligne dans un texte
 * @param lineCount : nombre de lignes du texte
 * @details Crée un Heading pour chaque mot du texte.Le texte est passé sous forme de tableau de char*
 * afin de pouvoir compter facilement la ligne lorsqu'un mot est traité
 */
void fillIndex(char** text, unsigned const lineCount, char** stopwords, unsigned const swCount);

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
 * Affiche l'index
 */
void displayIndex();

/**
 * Ecrit l'index dans le fichier donné
 * @param filename : fichier où enregistrer l'index
 * @details Si le fichier existe déjà, son contenu sera écrasé. Sinon un nouveau fichier est créé
 */
void saveIndex(char const filename[]);

/**
 * Lit le fichier donné et stocke chaque ligne dans une ligne du tableau de destination.
 * Compte également le nombre de lignes.
 * @param filename : nom du fichier à lire
 * @param dest : tableau de chaînes de caractères, rempli par cette fonction
 * @param lineNb : comptage du nombre de lignes, rempli par cette fonction
 */
void readFile(const char filename[], char*** dest, size_t *lineNb);


/**
 * Dans Heading_index, on cherche le mot le plus grand, mais plus petit que le mot passé en paramétre
 * @param word Le mot à comparer
 * @param wordSize taille du mot
 * @return  NULL, s'il n'y a pas de mot.
 *          Sinon le mot avant celui qui est plus grand que le mot passé en paramettre
 *          Si tout les mots sont plus petit, on retournee le dernier mot de Heading_index
 */
struct Heading *beforeBiggerWord(const char *word);

#endif //INF2_LABO5_BOOK_INDEX_H
