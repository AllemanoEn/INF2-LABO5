#include <stdio.h>
#include "book_index.h"
#include "heading.h"

int main() {
    char s[] = "The five boxing\n"
              "wizards jump quickly.\n"
              "Pack my box with five\n"
              "dozen liquor jugs.";

    readFile("text.txt");
    return 0;
}
