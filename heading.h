#ifndef INF2_LABO5_HEADING_H
#define INF2_LABO5_HEADING_H

struct Location {
    struct Location* next;
    unsigned int lineNumber;
};

struct Heading{
    struct Heading* next;
    char word;
    struct Location* first;
};

#endif //INF2_LABO5_HEADING_H
