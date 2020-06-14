#include <stdio.h>
#include "book_index.h"
#include "heading.h"

int main() {
    char s[] = "The five boxing\n"
              "wizards jump quickly.\n"
              "Pack my box with five\n"
              "dozen liquor jugs.";
    char m[] = "CetTe PHrase A DES MajUSCulEs";

    unsigned taille = sizeof(m)/sizeof(char );

    //test();
    //char** text = NULL;
    //size_t lines = 0;
    //readFile("macbeth.txt", text, lines);
    char* r = to_lower(m,taille);

    for (unsigned i = 0; i < taille; ++i) {
        printf("%c",*(r+i));
    }

    return 0;



}
