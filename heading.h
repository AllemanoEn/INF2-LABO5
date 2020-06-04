#ifndef INF2_LABO5_HEADING_H
#define INF2_LABO5_HEADING_H

struct Line {
    struct Line* next;
    unsigned int lineNumber;
};

struct Heading{
    struct Heading* next;
    char word;
    struct Line* first;
};

#endif //INF2_LABO5_HEADING_H
