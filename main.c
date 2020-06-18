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

    /*const char* helpArg = "-h";
    if(argc == 2 && !strcmp(argv[1], helpArg))
    {
        // TODO: Afficher l'aide
        printf("\ngit gud\n");
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

        //printf("%s\n%s\n%s", textFile, indexFile, stopWords);
        createIndex(textFile, stopWords);
        displayIndex();
        saveIndex(indexFile);
        destroyIndex();
    }*/

    createIndex("text.txt", "stopwords.txt");
    displayIndex();
    destroyIndex();

    return 0;


}
