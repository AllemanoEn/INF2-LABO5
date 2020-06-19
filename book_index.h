/// \file book_index.h
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 19.06.2020
///
/// Compilateur : MinGw-g++ 6.3.0


#ifndef INF2_LABO5_BOOK_INDEX_H
#define INF2_LABO5_BOOK_INDEX_H

#include "heading.h"


struct {
    struct Heading* firstHeading;
} heading_index;

/**
 * Crée l'index à partir du fichier donné
 * @param filename_text le fichier texte à ouvrir
 * @param filename_stopword fichier de mots blacklistés
 */
void createIndex(const char filename_text[],const char filename_stopword[]);

/**
 * Remplit un index vide avec les mots du texte passé en paramètre
 * @param text tableau de chaînes de caractères, chacune correspondant à une ligne dans un texte
 * @param lineCount nombre de lignes du texte
 * @details Crée un Heading pour chaque mot du texte.
 *          Le texte est passé sous forme de tableau de char*
 *          afin de pouvoir compter facilement la ligne lorsqu'un mot est traité
 */
void fillIndex(char** text, size_t const lineCount, char** stopwords, size_t const swCount);

/**
 * Libère la mémoire allouée à l'ensemble de l'index
 * @details Ne fait qu'appeler la fonction destroyList
 *          à partir du début de la liste chaînée
 */
void destroyIndex();

/**
 * Détruit tous les Headings à partir d'un maillon d'une liste chaînée.
 * @param word Début de la liste de Headings à supprimer
 * @details La destruction se fait de la fin vers le début de la liste
 */
void destroyList(struct Heading *word);

/**
 * Ecrit l'index dans le flux de sortie
 * @param stream flux de sortie
 * @details par exemple, on passe stdout pour afficher dans la console,
 *          ou un flux de fichier pour y écrire
 */
void printIndex(FILE *stream);

/**
 * Affiche l'index
 */
void displayIndex();

/**
 * Ecrit l'index dans le fichier donné
 * @param filename fichier où enregistrer l'index
 * @details Si le fichier existe déjà, son contenu sera écrasé.
 *          Sinon un nouveau fichier est créé
 */
void saveIndex(char const filename[]);

/**
 * Lit le fichier donné et stocke chaque ligne dans une ligne du tableau de destination.
 * Compte également le nombre de lignes.
 * @param filename nom du fichier à lire
 * @param dest tableau de chaînes de caractères, rempli par cette fonction
 * @param lineNb comptage du nombre de lignes, rempli par cette fonction
 */
void readFile(const char filename[], char*** dest, size_t *lineNb);

/**
 * Cherche un mot dans l'index
 * @param word mot à rechercher
 * @return pointeur vers le mot trouvé ou NULL si le mot n'existe pas
 */
struct Heading* findWord(char const word[]);


/**
 * Dans heading_index, on cherche le mot le plus grand, mais plus petit que le mot passé en paramétre
 * @param word Le mot à comparer
 * @param wordSize taille du mot
 * @return  NULL, s'il n'y a pas de mot.
 *          Sinon le mot avant celui qui est plus grand que le mot passé en paramettre
 *          Si tout les mots sont plus petit, on retournee le dernier mot de heading_index
 */
struct Heading* beforeBiggerWord(const char *word);

/**
 * Effectue une recherche dichotomique pour savoir si un mot se trouve dans la liste de stopwords
 * @param word_to_find Le mot à chercher
 * @param stopwords tableau de chaînes de caractères
 * @param lineCount_stopwords taille du tableau stopwords
 * @return true si le mot existe dans la liste de stopwords, false si non
 */
bool binarySearchStopWord(const char *word_to_find, char** stopwords, int lineCount_stopwords);

#endif //INF2_LABO5_BOOK_INDEX_H
