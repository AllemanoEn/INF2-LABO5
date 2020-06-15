#include <stdio.h>
#include "book_index.h"
#include "heading.h"

int main() {

    char** text = NULL;
    size_t lines = 0;
    struct Heading index = { NULL };
    readFile("text.txt", &text, &lines);
    fillIndex(text, lines);


    return 0;



}
