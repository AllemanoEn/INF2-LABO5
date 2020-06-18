#include <stdio.h>
#include "book_index.h"
#include "heading.h"

int main(int argc, char *argv[]) {

    /*
    if (argc == 3){
        createIndex(argv[0],argv[2]);
        saveIndex(argv[1]);

    }
     */

    createIndex("text.txt","stopword.txt");
    displayIndex();



    return 0;



}
