#include <stdio.h>
#include "book_index.h"

int main(int argc, char *argv[]) {

    /*
    if (argc == 3){
        createIndex(argv[0],argv[1],argv[2]);
    }
     */

    createIndex("text.txt","index.txt","stopword.txt");
    displayIndex();
    destroyIndex();


    return 0;



}
