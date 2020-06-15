#include <stdio.h>
#include "book_index.h"
#include "heading.h"

int main() {

    char** text = NULL;
    size_t lines = 0;
    struct Heading index = { NULL };
    readFile("text.txt", &text, &lines);
    fillIndex(text, lines);
    struct Heading* p = findWord("The", 3);

    return 0;



}
