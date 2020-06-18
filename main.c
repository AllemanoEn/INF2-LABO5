#include <stdio.h>
#include "book_index.h"
#include "heading.h"

int main() {

    createIndex("text.txt");
    //displayIndex();
    saveIndex("saved.txt");

    return 0;



}
