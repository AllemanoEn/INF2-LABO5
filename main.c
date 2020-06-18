#include <stdio.h>
#include <string.h>
#include "book_index.h"

bool checkFileExists(const char* filename){

    FILE* open = fopen(filename, "r");
    bool fileexist = open != NULL;
    fclose(open);
    return fileexist;

}

int main(int argc, char *argv[]) {

    if(argc == 2 && !strcmp(argv[1], "-h"))
    {
        // TODO: Afficher l'aide
        printf("-------------------------------------------------------------\n"
               "Pour utiliser cette executable, vous devez entrer 3 arguments\n\n"
               "arg 1 : chemin du fichier ou se trouve le texte.\n"
               "arg 2 : chemin du fichier de stockage du futur index.\n"
               "arg 3 : chemin du fichier des mots à exclure."
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
