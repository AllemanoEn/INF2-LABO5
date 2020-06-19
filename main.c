/// \file main.c
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 19.06.2020
///
/// Remarque concernant l'indexage de l'ensemble des oeuvres de Shakespeare:
/// Malheureusement notre code ne fonctionne pas avec les fichiers trop longs à cause
/// d'une erreur de malloc que nous n'avons pas pu résoudre.
/// Cependant pour les fichiers "normaux" le programme fonctionne correctement.
///
/// Compilateur : MinGw-g++ 6.3.0


#include <stdio.h>
#include <string.h>
#include "book_index.h"
#include "heading.h"

bool checkFileExists(const char *filename){

    FILE* open = fopen(filename, "r");
    bool fileexist = (open != NULL);
    fclose(open);
    return fileexist;

}

int main(int argc, char *argv[]) {

    if(argc == 2 && !strcmp(argv[1],"-h"))
    {

        printf("-------------------------------------------------------------\n"
               "Pour utiliser cette executable, vous devez entrer 3 arguments\n\n"
               "arg 1 : chemin du fichier ou se trouve le texte.\n"
               "arg 2 : chemin du fichier de stockage du futur index.\n"
               "arg 3 : chemin du fichier des mots à exclure.\n"
               "-------------------------------------------------------------\n");
        return 0;
    }

    else if(argc == 4)
    {
        char* textFile = argv[1];
        char* indexFile = argv[2];
        char* stopWords = argv[3];


        // Vérifie si IndexFile existe déjà
        if(checkFileExists(indexFile))
        {
            printf("Le fichier d'index \"%s\" existe déjà.\nVoulez-vous quand même procéder à l'écriture ? (y - n)\n", indexFile);
            char confirm = (char)getchar();
            if(confirm != 'y')
                return 0;
        }

        createIndex(textFile, stopWords);
        displayIndex();
        saveIndex(indexFile);
        destroyIndex();
    }

    return 0;

}
