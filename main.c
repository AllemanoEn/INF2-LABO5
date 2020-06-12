#include <stdio.h>
#include "book_index.h"
#include "heading.h"

int main() {
    char s[] = "The five boxing\n"
              "wizards jump quickly.\n"
              "Pack my box with five\n"
              "dozen liquor jugs.";

    //test();
    char** text = NULL;
    size_t lines = 0;
    readFile("macbeth.txt", text, lines);
    return 0;
}
